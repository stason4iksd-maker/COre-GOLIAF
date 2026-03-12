cmake_minimum_required(VERSION 3.20)

project(COreGOLIAF VERSION 0.2.0 LANGUAGES CXX)

# --- Compiler setup ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

message(STATUS "Generator: ${CMAKE_GENERATOR}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ compiler ID: ${CMAKE_CXX_COMPILER_ID}")

if(WIN32 AND CMAKE_GENERATOR MATCHES "Ninja" AND NOT MSVC)
    message(WARNING
        "Ninja generator is active but MSVC was not detected. "
        "If you need Ninja+MSVC, run from 'x64 Native Tools Command Prompt for VS' "
        "or call vcvars64.bat before configuring.")
endif()

# --- Expandable engine modules ---
add_library(engine_modules STATIC
    engine/renderer/RendererStub.cpp
    engine/physics/PhysicsStub.cpp
    engine/audio/AudioStub.cpp
)

target_include_directories(engine_modules PUBLIC engine)

# --- Targets ---
add_executable(Dev src/dev_main.cpp)
add_executable(Player src/player_main.cpp)
add_executable(LanServer src/server_main.cpp)

target_link_libraries(Dev PRIVATE engine_modules)
target_link_libraries(Player PRIVATE engine_modules)
target_link_libraries(LanServer PRIVATE engine_modules)

# Force runtime output to build/bin for single- and multi-config generators.
foreach(target Dev Player LanServer)
    set_target_properties(${target} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/bin"
    )
endforeach()
