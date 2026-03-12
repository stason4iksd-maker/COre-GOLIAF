cmake_minimum_required(VERSION 3.20)

project(COreGOLIAF VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

message(STATUS "Generator: ${CMAKE_GENERATOR}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} (${CMAKE_CXX_COMPILER})")

if(WIN32 AND CMAKE_GENERATOR MATCHES "Ninja" AND NOT MSVC)
    message(WARNING "Ninja detected without MSVC. Use 'x64 Native Tools Command Prompt for VS' (or vcvars64.bat) for Ninja+MSVC.")
endif()

add_library(engine_shared STATIC
    src/engine/renderer/RendererStub.cpp
    src/engine/physics/PhysicsStub.cpp
    src/engine/audio/AudioStub.cpp
)
target_include_directories(engine_shared PUBLIC src/engine)

add_executable(Dev src/dev/main.cpp)
add_executable(Player src/player/main.cpp)
add_executable(LanServer src/server/main.cpp)

target_link_libraries(Dev PRIVATE engine_shared)
target_link_libraries(Player PRIVATE engine_shared)
target_link_libraries(LanServer PRIVATE engine_shared)

foreach(target Dev Player LanServer)
    set_target_properties(${target} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/bin"
    )
endforeach()
