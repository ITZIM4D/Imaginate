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

#include <Window.h>
#include <Shader.h>
#include <Camera.h>
#include <Model.h>
#include <GameObject.h>
#include <ScriptManager.h>

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// Keep track of time 
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool firstMouse = true;
float lastX = (float) SCREEN_WIDTH / 2;
float lastY = (float) SCREEN_WIDTH / 2;

int main() {
    Window currWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
    GLFWwindow* window = currWindow.getWindow();

    // Script Manager
    ScriptManager scriptManager;
    scriptManager.loadScript("Hello World", "../assets/scripts/test.lua");
    scriptManager.runScript("Hello World");

    // Mouse input options
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    stbi_set_flip_vertically_on_load(true);
    
    // Compile shaders
    Shader defaultShader("../src/shaders/shader.vs", "../src/shaders/shader.fs");
    Shader lightShader("../src/shaders/shader.vs", "../src/shaders/lightShader.fs");

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    GameObject cube("../assets/models/cube/Cube.obj");
    GameObject lightCube("../assets/models/cube/Cube.obj");

    // Model matrix to transform to world space (Because there is a model matrix for each object)
    glm::mat4 cubeModel = glm::mat4(1.0f);
    cube.translate(cubeModel, glm::vec3(0.0f, -2.0f, -3.0f));

    glm::mat4 lightModel = glm::mat4(1.0f);
    lightCube.translate(lightModel, glm::vec3(3.0f, 2.0f, 0.0f));
    lightCube.scale(lightModel, glm::vec3(0.5f));
    glm::vec3 lightPos = lightCube.getPos();

    while(!glfwWindowShouldClose(window)) {
        // Per frame time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // input
        processInput(window);

        // Rendering
        glClearColor(0.44f, 0.82f, 0.88f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        defaultShader.use();

        // View matrix 
        glm::mat4 view = camera.GetViewMatrix();

        // Projection matrix for perspective
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), ((float) SCREEN_WIDTH / (float) SCREEN_HEIGHT), 0.1f, 100.0f);

        // Send matrix uniforms to shader
        defaultShader.setVec3("viewPos", camera.Position);
        defaultShader.setVec3("lightPos", lightPos);
        defaultShader.setVec3("lightColor", glm::vec3(1.0f));
        defaultShader.setMat4("model", cubeModel);
        defaultShader.setMat4("view", view);
        defaultShader.setMat4("projection", projection);

        cube.Draw(defaultShader);

        lightShader.use();
        
        lightShader.setMat4("model", lightModel);
        lightShader.setMat4("view", view);
        lightShader.setMat4("projection", projection);
        lightCube.Draw(lightShader);

        // Check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// Process Input
void processInput(GLFWwindow* window) {

    // Exit window with esc
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }

    // Move using WASD
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
