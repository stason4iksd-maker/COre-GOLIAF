cmake_minimum_required(VERSION 3.24)
project(COre_GOLIAF LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

# GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# GLEW
FetchContent_Declare(
  glew
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
  GIT_TAG glew-cmake-2.2.0
)
set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(ONLY_LIBS ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glew)

# IMGUI
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.91.9b
)
FetchContent_MakeAvailable(imgui)
add_library(imgui_lib
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui_lib PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)
target_compile_definitions(imgui_lib PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLEW)
target_link_libraries(imgui_lib PUBLIC glfw libglew_static)

# Lua
FetchContent_Declare(
  lua
  GIT_REPOSITORY https://github.com/walterschell/Lua.git
  GIT_TAG v5.4.6
)
FetchContent_MakeAvailable(lua)

# nlohmann_json
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

if(WIN32)
  set(PLATFORM_LIBS ws2_32 opengl32)
else()
  find_package(OpenGL REQUIRED)
  set(PLATFORM_LIBS OpenGL::GL)
endif()

set(CORE_SOURCES
  src/core/Application.cpp
  src/core/WindowGLFW.cpp
  src/core/Logger.cpp
  src/core/Timer.cpp
)
set(RENDERER_SOURCES
  src/renderer/Renderer.cpp
  src/renderer/GLUtils.cpp
  src/renderer/Mesh.cpp
  src/renderer/Shader.cpp
)
set(ECS_SOURCES
  src/ecs/Entity.cpp
  src/ecs/Component.cpp
  src/ecs/System.cpp
  src/ecs/Registry.cpp
)
set(SCENE_SOURCES
  src/scene/Scene.cpp
  src/scene/SceneSerializer.cpp
)
set(SCRIPTING_SOURCES
  src/scripting/LuaVM.cpp
  src/scripting/ScriptComponent.cpp
)
set(NETWORK_SOURCES
  src/network/TcpServer.cpp
)
set(EDITOR_SOURCES
  src/editor/EditorApp.cpp
  src/editor/ImGuiIntegration.cpp
)

add_library(goliaf_engine STATIC
  ${CORE_SOURCES}
  ${RENDERER_SOURCES}
  ${ECS_SOURCES}
  ${SCENE_SOURCES}
  ${SCRIPTING_SOURCES}
  ${NETWORK_SOURCES}
  ${EDITOR_SOURCES}
)
target_include_directories(goliaf_engine PUBLIC src)
target_link_libraries(goliaf_engine PUBLIC glfw libglew_static imgui_lib lua_static nlohmann_json::nlohmann_json ${PLATFORM_LIBS})

add_executable(Dev src/apps/dev_main.cpp)
add_executable(Player src/apps/player_main.cpp)
add_executable(LanServer src/apps/server_main.cpp)

target_link_libraries(Dev PRIVATE goliaf_engine)
target_link_libraries(Player PRIVATE goliaf_engine)
target_link_libraries(LanServer PRIVATE goliaf_engine)

foreach(t Dev Player LanServer)
  set_target_properties(${t} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/bin)
endforeach()

add_custom_target(copy_assets ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
)
add_dependencies(Dev copy_assets)
add_dependencies(Player copy_assets)
