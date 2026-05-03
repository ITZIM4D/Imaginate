#ifndef GAME_H
#define GAME_H

#include <unordered_map>
#include <string>

#include "Scene.h"
#include "Shader.h"
#include "ScriptManager.h"
#include "GameObject.h"

class Engine;

class Game {
    public:
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
        void setupScripts();
};

#endif