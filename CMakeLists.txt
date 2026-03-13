cmake_minimum_required(VERSION 3.20)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

project(COreGOLIAF VERSION 0.2.0 LANGUAGES CXX)

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

add_library(engine_modules STATIC
    engine/renderer/RendererStub.cpp
    engine/physics/PhysicsStub.cpp
    engine/audio/AudioStub.cpp
)

target_include_directories(engine_modules PUBLIC engine)

add_library(game_engine_lib STATIC
    src/ResourceManager.cpp
    src/Scene.cpp
    src/Renderer.cpp
    src/PhysicsSystem.cpp
    src/InputManager.cpp
    src/AudioManager.cpp
    src/SceneManager.cpp
)

target_include_directories(game_engine_lib PUBLIC src)

add_executable(game_engine src/main.cpp)
target_link_libraries(game_engine PRIVATE game_engine_lib)

add_executable(Dev src/dev_main.cpp)
add_executable(Player src/player_main.cpp)
add_executable(LanServer src/server_main.cpp)

target_link_libraries(Dev PRIVATE engine_modules)
target_link_libraries(Player PRIVATE engine_modules)
target_link_libraries(LanServer PRIVATE engine_modules)

foreach(target Dev Player LanServer game_engine)
    set_target_properties(${target} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/bin"
    )
endforeach()

enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(runTests
    tests/test_ResourceManager.cpp
    tests/test_Physics.cpp
    tests/test_Renderer.cpp
    tests/test_Scene.cpp
)
target_include_directories(runTests PRIVATE src)
target_link_libraries(runTests PRIVATE game_engine_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(runTests)
