# COre-GOLIAF

Next-stage modular C++17 engine scaffold with three runnable targets:
- `Dev` (editor/dev tools)
- `Player` (runtime)
- `LanServer` (LAN server)

## Project Structure

```text
COre-GOLIAF/
├─ engine/
│  ├─ core/
│  ├─ renderer/
│  ├─ ecs/
│  ├─ physics/
│  ├─ audio/
│  └─ scene/
├─ src/
│  ├─ dev/
│  ├─ player/
│  └─ server/
├─ assets/
│  ├─ models/
│  ├─ textures/
│  └─ sounds/
└─ CMakeLists.txt
```

## Build

```bash
cmake -S . -B build -G Ninja
cmake --build build
```

Targets:

```bash
cmake --build build --target Dev
cmake --build build --target Player
cmake --build build --target LanServer
```

Binaries are generated in `build/bin/`.

## Current capabilities (stub stage)

- Engine core: `Application`, `Window`, `Logger`, `Timer`
- Renderer modules: `Renderer`, `Shader`, `Mesh`, `Camera`, `Texture`
- ECS skeleton: `Entity`, `Component`, `System`, `EcsWorld`
- Scene skeleton: `Scene`, `SceneLoader`, `SceneSerializer`
- Dev editor modules: editor shell, level/menu editors, debug tools, asset pipeline
- LAN server modules: `NetworkServer`, `ClientConnection`, `Packet`

All subsystems print clear initialization logs for visibility.
