# COre-GOLIAF

Стартовый каркас 3D-движка на C++17 + CMake с тремя сборочными целями:
- `Dev` — dev-среда (редактор уровней/меню, asset pipeline, debug tools) в виде stubs
- `Player` — standalone runtime stub
- `LanServer` — LAN server stub

## Структура проекта

```text
COre-GOLIAF/
├─ src/
│  ├─ dev/
│  │   └─ main.cpp
│  ├─ player/
│  │   └─ main.cpp
│  ├─ server/
│  │   └─ main.cpp
│  └─ engine/
│      ├─ renderer/
│      │   ├─ RendererStub.h
│      │   └─ RendererStub.cpp
│      ├─ physics/
│      │   ├─ PhysicsStub.h
│      │   └─ PhysicsStub.cpp
│      └─ audio/
│          ├─ AudioStub.h
│          └─ AudioStub.cpp
├─ assets/
└─ CMakeLists.txt
```

## Сборка (Ninja)

```bash
cmake -S . -B build -G Ninja
cmake --build build
```

## Сборка таргетов по отдельности

```bash
cmake --build build --target Dev
cmake --build build --target Player
cmake --build build --target LanServer
```

## Visual Studio / MSVC

```bash
cmake -S . -B build -G "Visual Studio 17 2022"
cmake --build build --config Debug
```

> Для Ninja + MSVC на Windows запускайте из *x64 Native Tools Command Prompt for VS* (или после `vcvars64.bat`).

## Выходные файлы

Все exe складываются в `build/bin/`:
- `Dev(.exe)`
- `Player(.exe)`
- `LanServer(.exe)`

## Проверка запуска

- `Dev` печатает `Dev build started`
- `Player` печатает `Player build started`
- `LanServer` печатает `LAN server started`
