#ifndef GAME_H
#define GAME_H

#include <unordered_map>
#include <string>

#include "Scene.h"
#include "Shader.h"
#include "ScriptManager.h"
#include "GameObject.h"

class Engine;

// Struct to store variables specific to the game
struct GameVars {
    int score = 0;
};

class Game {
    public:
        GameVars gameVars;

        Game(Engine& engine);
        void init();
        void run();
        void update(float deltaTime);

    private:
        Engine& engine_;
        Scene* activeScene_;
        std::shared_ptr<ScriptManager> scriptManager_;
        std::unordered_map<std::string, Shader> shaders_;
        std::unordered_map<std::string, Scene>& scenes_;
        float deltaTime_;

        void setActiveScene(std::string sceneName);
        void setupScenes();
        void setupShaders();
};

#endif
