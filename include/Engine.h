#ifndef ENGINE_H
#define ENGINE_H

#include <Camera.h>
#include <Window.h>
#include <InputManager.h>
#include <ScriptManager.h>
#include <Scene.h>
#include <stb_image.h>
#include <Shader.h>
#include <GameObject.h>

class Engine {
    public:
        /**
         * @brief Constructor that will instantiate the engine
         * 
         * @param screenWidth Width of the window to be created
         * @param screenHeight Height of the window to be created
         */
        Engine(int screenWidth, int screenHeight);
        
        /**
         * @brief Runs the engine
         */
        void run();

        /**
         * @brief Returns the width of the screen
         */
        int getScreenWidth() {return screenWidth_;}

        /**
         * @brief Returns the height of the screen
         */
        int getScreenHeight() {return screenHeight_;}

    private:
        float deltaTime_; // Change in time
        float lastFrame_; // Time of last frame
        int screenWidth_; // Width of window
        int screenHeight_; // Height of window
        std::shared_ptr<Window> currWindow_; // Current window object
        GLFWwindow* window_; // Current GLFW window object
        Camera camera_;
        std::shared_ptr<InputManager> inputManager_;
        std::shared_ptr<ScriptManager> scriptManager_;
        std::unordered_map<std::string, Scene> scenes_;
        std::unordered_map<std::string, Shader> shaders_;
        Scene* currScene_;

        /**
         * @brief initial setup for the Engine (Runs Once)
         */
        void init();

        /**
         * @brief Updates everything once per frame
         */
        void update();
        
        /**
         * @brief Does all rendering
         */
        void render();

        /**
         * @brief Does everything necessary for shutting down
         */
        void shutdown();

        /**
         * @brief Initializes the specified scene
         * 
         * @param scene Scene to be initialized
         */
        void initScene(std::string sceneName);
};

#endif