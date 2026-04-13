#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// string cast for debugging
// #define GLM_ENABLE_EXPERIMENTAL
// #include <glm/gtx/string_cast.hpp>

#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <Engine.h>

int main() {
    Engine engine(800, 600);
    engine.run();
    return 0;
}


