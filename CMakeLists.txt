cmake_minimum_required(VERSION 4.0.0)
project(Imaginate)

add_executable(Imaginate
    src/main.cpp
    src/Window.cpp
    external/glad/src/glad.c
    src/ImageLoader.cpp
    src/GameObject.cpp
)

include_directories(
    include
    external
    external/glfw/include
    external/glad/include
    external/assimp/include
)

target_link_directories(
    Imaginate PRIVATE 
    external/glfw/lib-universal
    external/assimp/build/bin
)

target_link_libraries(Imaginate PRIVATE
    glfw3
    assimp
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreFoundation"
)