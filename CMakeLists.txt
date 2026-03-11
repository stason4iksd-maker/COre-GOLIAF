cmake_minimum_required(VERSION 3.20)

project(COreGOLIAF VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(engine_core
    src/engine/Engine.cpp
    src/render/Renderer.cpp
    src/physics/PhysicsSystem.cpp
    src/audio/AudioSystem.cpp
    src/ecs/EcsWorld.cpp
)

target_include_directories(engine_core PUBLIC include)

add_executable(Dev
    src/dev/main.cpp
    src/editor/level_editor/LevelEditor.cpp
    src/editor/menu_editor/MenuEditor.cpp
    src/tools/AssetCompiler.cpp
)
target_link_libraries(Dev PRIVATE engine_core)

add_executable(Player
    src/player/main.cpp
)
target_link_libraries(Player PRIVATE engine_core)

add_executable(LanServer
    src/server/main.cpp
)
target_link_libraries(LanServer PRIVATE engine_core)

set_target_properties(Dev Player LanServer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
