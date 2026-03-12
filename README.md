# COre-GOLIAF

COre-GOLIAF is a modular C++17 game engine foundation with:
- real OpenGL 3.3 rendering (cube)
- GLFW window + input
- Dear ImGui editor UI
- ECS + scene JSON serialization
- Lua scripting with hot-reload
- TCP LAN server/client transform sync baseline

## Build

```bash
cmake -S . -B build -G Ninja
cmake --build build
```

## Outputs

- `build/bin/Dev`
- `build/bin/Player`
- `build/bin/LanServer`

## Run

```bash
./build/bin/LanServer
./build/bin/Player
./build/bin/Dev
```

## Architecture

- `src/core`: Application, WindowGLFW, Logger, Timer, Input
- `src/renderer`: Renderer, Shader, Mesh, Camera
- `src/ecs`: Entity/Component/Registry/Systems
- `src/scene`: Scene + SceneSerializer
- `src/scripting`: LuaVM
- `src/network`: TcpServer + NetworkClient
- `src/editor`: EditorApp + ImGuiIntegration
- `src/apps`: dev_main, player_main, server_main

## Notes

- Dev renders scene and editor panels (menu/hierarchy/inspector/assets/viewport panel).
- Player renders loaded scene and updates camera with WASD/mouse.
- LanServer listens on `127.0.0.1:12345`, accepts multiple clients and responds with snapshots.
