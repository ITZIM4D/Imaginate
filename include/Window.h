#ifndef WINDOW_H
#define WINDOW_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window {
    public:
        /**
         * @brief Creates a window and context
         * 
         * @param width Width of the window
         * @param height Height of the window
         */
        Window(int width, int height);

        /**
         * @brief returns pointer to window
         * 
         * @returns Pointer to the window
         */
        GLFWwindow* getWindow();

    private:
        // Variables
        GLFWwindow* window;

        /**
         * @brief callback when window changes size
         * 
         * @param window Pointer to the window being changed
         * @param width New width of the window
         * @param height New height of the window
         */
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    
};

#endif