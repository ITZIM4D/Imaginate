#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>

#include "stb_image.h"
#include "Game.h"
#include "Engine.h"

int main() {
    Engine engine(800, 600);
    Game game(engine);
    game.init();
    game.run();
    return 0;
}


