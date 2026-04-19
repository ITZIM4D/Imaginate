cmake_minimum_required(VERSION 4.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
project(Imaginate)

include(FetchContent)

FetchContent_Declare(
    lua
    GIT_REPOSITORY https://github.com/walterschell/Lua
    GIT_TAG 504ef66d500fa1fb4f1684b6617b01342eee704a
    GIT_SHALLOW FALSE
    GIT_PROGRESS TRUE
    )
set(LUA_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(lua)

FetchContent_Declare(
    sol2
    GIT_REPOSITORY https://github.com/yig/sol2
    GIT_TAG cs425-2025
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    )
FetchContent_MakeAvailable(sol2)

add_executable(Imaginate
    src/main.cpp
    src/Window.cpp
    external/glad/src/glad.c
    src/ImageLoader.cpp
    src/GameObject.cpp
    src/ScriptManager.cpp
    src/Engine.cpp
    src/InputManager.cpp
    src/Scene.cpp
)

include_directories(
    include
    external
    external/glfw/include
    external/glad/include
    external/assimp/include
    external/sol/include
)

target_link_directories( Imaginate PRIVATE 
    external/glfw/lib-universal
    external/assimp/bin
)

target_link_libraries(Imaginate PRIVATE
    sol2
    lua_static
    glfw3
    assimp
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreFoundation"
)