# COre-GOLIAF

Минимальный рабочий каркас 3D-движка на C++17/CMake с тремя целями:

- **Dev** — development tools (уровневый редактор, asset pipeline, debug tools) как расширяемые stubs
- **Player** — standalone runtime
- **LanServer** — простой LAN server stub

## Рабочая структура

```text
COre-GOLIAF/
├─ src/
│  ├ dev_main.cpp
│  ├ player_main.cpp
│  └ server_main.cpp
├─ assets/
├─ engine/
│  ├ renderer/
│  ├ physics/
│  └ audio/
└─ CMakeLists.txt
```

## Сборка (Ninja)

```bash
cmake -S . -B build -G Ninja
cmake --build build
```

## Сборка (Visual Studio / MSVC)

Для Visual Studio 2026 используйте соответствующий установленный генератор CMake. Если доступен только Visual Studio 2022, можно использовать его генератор.

```bash
cmake -S . -B build -G "Visual Studio 17 2022"
cmake --build build --config Debug
```

## Ninja + MSVC на Windows

Если хотите именно Ninja + MSVC, запускайте команды из **x64 Native Tools Command Prompt for VS** (или после `vcvars64.bat`). Тогда CMake автоматически подхватит MSVC.

## Бинарники

После сборки все exe находятся в:

- `build/bin/Dev.exe`
- `build/bin/Player.exe`
- `build/bin/LanServer.exe`

## Проверка запуска

Каждый exe сразу печатает сообщение в консоль:

- Dev: `Dev build started`
- Player: `Player build started`
- LanServer: `LAN server started`

и ждёт Enter, чтобы окно не закрывалось мгновенно.
