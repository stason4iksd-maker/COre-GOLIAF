#include "core/Application.h"
#include "core/Logger.h"
#include "renderer/Renderer.h"
#include "scene/Scene.h"
#include "scene/SceneSerializer.h"
#include "scripting/LuaVM.h"
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

static void SendTestPacket() {
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
#endif
    int s = static_cast<int>(socket(AF_INET, SOCK_STREAM, 0));
    if (s < 0) return;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    if (connect(s, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == 0) {
        const char* msg = "{\"type\":\"connect\",\"payload\":{\"player\":\"local\"}}";
        send(s, msg, static_cast<int>(strlen(msg)), 0);
        char buffer[512]{};
        int n = static_cast<int>(recv(s, buffer, sizeof(buffer)-1, 0));
        if (n > 0) goliaf::core::Logger::Log("Player", std::string("Server reply: ") + std::string(buffer, buffer + n));
    }
#ifdef _WIN32
    closesocket(s);
    WSACleanup();
#else
    close(s);
#endif
}

int main() {
    goliaf::core::Logger::Log("Player", "Runtime initialized");

    goliaf::core::Application app;
    if (!app.Initialize("COre-GOLIAF Player", 1280, 720)) return 1;

    goliaf::renderer::Renderer renderer;
    if (!renderer.Initialize(app.GetWindow().Handle(), "assets/shaders")) return 2;

    goliaf::scene::Scene scene("PlayerScene");
    goliaf::scene::SceneSerializer serializer;
    serializer.Load(scene, "assets/scenes/level1.scene.json");

    goliaf::scripting::LuaVM lua;
    lua.Initialize();

    SendTestPacket();

    app.Run([&](float dt) {
        for (const auto& e : scene.GetRegistry().Entities()) {
            if (auto* sc = scene.GetRegistry().GetScript(e.id)) {
                lua.UpdateEntity(scene.GetRegistry(), e.id, dt, sc->path);
            }
        }
    }, [&]() {
        renderer.BeginFrame(0.08f, 0.07f, 0.10f, 1.0f);
        renderer.RenderTriangle();
    });

    app.Shutdown();
    return 0;
}
