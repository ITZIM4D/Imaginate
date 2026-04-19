#include <InputManager.h>

InputManager::InputManager(GLFWwindow* window, Camera& camera, float& deltaTime, int screenWidth, int screenHeight) : window_(window),
    camera_(camera), deltaTime_(deltaTime), firstMouse_(true), lastX_((float) screenWidth / 2),
    lastY_((float) screenHeight / 2) {
    // Mouse input options
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetWindowUserPointer(window_, this);
}

void InputManager::processInput() {
    // Exit window with esc
    if (glfwGetKey(window_, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window_, true);
    }

    // Move using WASD
    if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS) {
        camera_.ProcessKeyboard(FORWARD, deltaTime_);
    }
    if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS) {
        camera_.ProcessKeyboard(BACKWARD, deltaTime_);
    }
    if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) {
        camera_.ProcessKeyboard(LEFT, deltaTime_);
    }
    if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) {
        camera_.ProcessKeyboard(RIGHT, deltaTime_);
    }
}

void InputManager::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    InputManager* self = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (self->firstMouse_) {
        self->lastX_ = xpos;
        self->lastY_ = ypos;
        self->firstMouse_ = false;
    }

    float xoffset = xpos - self->lastX_;
    float yoffset = self->lastY_ - ypos; // reversed since y-coordinates go from bottom to top

    self->lastX_ = xpos;
    self->lastY_ = ypos;

    self->camera_.ProcessMouseMovement(xoffset, yoffset);
}

void InputManager::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    InputManager* self = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    self->camera_.ProcessMouseScroll(static_cast<float>(yoffset));
} 

bool InputManager::KeyIsDown(int keycode) {
    return glfwGetKey(window_, keycode) == GLFW_PRESS;
    
}