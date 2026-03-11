# COre-GOLIAF

Минимальный рабочий каркас кроссплатформенного C++17 проекта 3D-движка с тремя целями сборки:

- `Dev` — среда разработки (runtime + инструменты редактора/компиляции ассетов)
- `Player` — standalone runtime
- `LanServer` — облегчённый LAN-сервер (stub)

## Требования

- CMake 3.20+
- Компилятор C++17
- Visual Studio 2022 (для Windows)

## Сборка (Visual Studio 2022)

```bash
cmake -S . -B build -G "Visual Studio 17 2022"
cmake --build build --config Debug
```

Исполняемые файлы будут в каталоге:

- `build/bin/Dev.exe`
- `build/bin/Player.exe`
- `build/bin/LanServer.exe`

## Сборка (Linux/macOS)

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
```

## Структура проекта

```text
.
├── CMakeLists.txt
├── assets/
├── audio/
├── ecs/
├── editor/
│   ├── level_editor/
│   └── menu_editor/
├── engine/
├── physics/
├── player/
├── render/
├── server/
├── include/core/
└── src/
    ├── audio/
    ├── dev/
    ├── ecs/
    ├── editor/
    │   ├── level_editor/
    │   └── menu_editor/
    ├── engine/
    ├── physics/
    ├── player/
    ├── render/
    ├── server/
    └── tools/
```

## Что уже реализовано

- Валидный `CMakeLists.txt` с таргетами `Dev`, `Player`, `LanServer`
- Общая библиотека `engine_core`
- Минимальные примеры исходников, которые успешно компилируются
