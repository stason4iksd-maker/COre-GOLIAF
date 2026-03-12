# COre-GOLIAF

COre-GOLIAF is a modular C++17 starter 3D engine with:
- OpenGL rendering (triangle)
- GLFW windowing
- Dear ImGui editor UI (Dev)
- ECS + Scene JSON serialization
- Lua scripting with hot-reload
- TCP LAN server + test client packet from Player

## Build

```bash
cmake -S . -B build -G Ninja
cmake --build build
```

Binaries:
- `build/bin/Dev`
- `build/bin/Player`
- `build/bin/LanServer`

## Run

1. Run server first:
```bash
./build/bin/LanServer
```
2. Run player:
```bash
./build/bin/Player
```
3. Run dev editor:
```bash
./build/bin/Dev
```

## Structure

- `src/core` - app loop, window, logger, timer
- `src/renderer` - OpenGL renderer, shader, mesh
- `src/ecs` - entity/component/registry systems
- `src/scene` - scene container + JSON load/save
- `src/scripting` - Lua VM and script updates
- `src/network` - TCP server
- `src/editor` - ImGui integration and panels
- `src/apps` - app entry points
- `assets` - shaders/scenes/scripts

## Notes

- Dev shows ImGui menu + Hierarchy/Inspector/Asset Browser.
- Player loads scene and applies Lua script update to transforms.
- LanServer listens on `127.0.0.1:12345` and echoes JSON payloads.
