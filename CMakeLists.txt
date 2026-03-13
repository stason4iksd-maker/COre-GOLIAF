cmake_minimum_required(VERSION 3.21)
project(COre_GOLIAF LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

# GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_X11 OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# GLAD
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

# ImGui
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.90.8
)
FetchContent_MakeAvailable(imgui)

add_library(imgui_lib
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui_lib PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)
target_compile_definitions(imgui_lib PUBLIC GLFW_INCLUDE_NONE IMGUI_IMPL_OPENGL_LOADER_GLAD)
target_link_libraries(imgui_lib PUBLIC glfw glad)

# Lua
FetchContent_Declare(
  lua
  GIT_REPOSITORY https://github.com/lua/lua.git
  GIT_TAG v5.4.6
)
FetchContent_MakeAvailable(lua)

file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS src/core/*.cpp src/render/*.cpp src/editor/*.cpp src/ecs/*.cpp src/scripting/*.cpp src/network/*.cpp src/assets/*.cpp src/physics/*.cpp src/audio/*.cpp)

add_library(engine_core ${CORE_SOURCES})
target_include_directories(engine_core PUBLIC include ${lua_SOURCE_DIR})
file(GLOB LUA_SRC ${lua_SOURCE_DIR}/*.c)
list(REMOVE_ITEM LUA_SRC ${lua_SOURCE_DIR}/lua.c ${lua_SOURCE_DIR}/luac.c ${lua_SOURCE_DIR}/onelua.c ${lua_SOURCE_DIR}/all.c)
add_library(lua_lib ${LUA_SRC})
target_include_directories(lua_lib PUBLIC ${lua_SOURCE_DIR})

target_link_libraries(engine_core PUBLIC glfw glad imgui_lib lua_lib)
if(UNIX AND NOT APPLE)
  target_link_libraries(engine_core PUBLIC dl pthread)
endif()

add_executable(Dev.exe src/app/dev_main.cpp)
target_link_libraries(Dev.exe PRIVATE engine_core)

add_executable(Player.exe src/app/player_main.cpp)
target_link_libraries(Player.exe PRIVATE engine_core)

add_executable(LanServer.exe src/app/server_main.cpp)
target_link_libraries(LanServer.exe PRIVATE engine_core)

file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
