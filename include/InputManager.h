#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <iostream>
#include <Camera.h>
#include <GLFW/glfw3.h>

class InputManager {
    public:
        InputManager(GLFWwindow* window, Camera& camera, float& deltaTime, int screenWidth, int screenHeight);
        void processInput();
        static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    private:
        GLFWwindow* window_;
        Camera& camera_;
        float& deltaTime_;
        bool firstMouse_;
        float lastX_;
        float lastY_;
};

#endif