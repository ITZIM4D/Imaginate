#include "Game.h"
#include "Engine.h"
#include <nlohmann/json.hpp>
#include <filesystem>

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

Game::Game(Engine& engine) : engine_(engine), scriptManager_ (engine.getScriptManager()), scenes_(engine.getScenes()) {}

void Game::init() {
    // Setup methods
    setupScripts();
    setupShaders();
    setupScenes();

    engine_.init();
}

void Game::setActiveScene(std::string sceneName) {
    activeScene_ = &scenes_.at(sceneName);
    engine_.initScene(sceneName);
}

void Game::setupScenes() {
    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(std::string(PROJECT_ROOT) + "/scenes/")) {
        if (!dirEntry.is_regular_file()) continue;
        if (dirEntry.path().extension() != ".json") continue;

        std::ifstream f(dirEntry.path());
        if (!f.is_open()) {
            std::cerr << "Error opening file: " << dirEntry.path() << std::endl;
            continue; 
        }

        try {
            nlohmann::json json;
            f >> json;

            // Create scene with name
            scenes_.try_emplace(json["sceneName"]);

            // For each object
            for (auto object : json["objects"]) {
                // Create variables
                float x, y, z;
                std::string shaderName;
                glm::mat4 model;
                glm::vec3 tempVec3; 

                // Create and add the object
                if (object["shaderName"] == "") {
                   shaderName = "defaultShader";
                } else {
                    shaderName = object["shaderName"];
                }
                GameObject gameObject(object["objectPath"], *engine_.getScriptManager());
                scenes_.at(json["sceneName"]).addObject(object["objectName"], std::make_shared<GameObject>(gameObject), shaders_.at(shaderName));             
                
                x = json["lightPos"][0];
                y = json["lightPos"][1];
                z = json["lightPos"][2];
                scenes_.at(json["sceneName"]).setLightPos(glm::vec3(x, y, z));

                // Set model matrices for each object
                if (!(object["position"] == std::vector<float>({0.0, 0.0, 0.0}))) {
                    x = object["position"][0];
                    y = object["position"][1];
                    z = object["position"][2];
                    model = glm::mat4(1.0f); 
                    scenes_.at(json["sceneName"]).objects_.at(object["objectName"]).object_->translate(model, glm::vec3(x, y, z)); 
                }
                if (!(object["rotation"] == std::vector<float>({0.0, 0.0, 0.0}))) {
                    x = object["rotation"][0];
                    y = object["rotation"][1];
                    z = object["rotation"][2];
                    model = glm::mat4(1.0f);
                    scenes_.at(json["sceneName"]).objects_.at(object["objectName"]).object_->rotateX(model, x);
                    scenes_.at(json["sceneName"]).objects_.at(object["objectName"]).object_->rotateY(model, y);
                    scenes_.at(json["sceneName"]).objects_.at(object["objectName"]).object_->rotateZ(model, z);
                }
                if (!(object["scale"] == std::vector<float>({0.0, 0.0, 0.0}))) {
                    x = object["scale"][0];
                    y = object["scale"][1];
                    z = object["scale"][2];
                    model = glm::mat4(1.0f);
                    scenes_.at(json["sceneName"]).objects_.at(object["objectName"]).object_->scale(model, glm::vec3(x, y, z));
                }

            }
        } catch (const nlohmann::json::parse_error& e) {
            std::cerr << "JSON parse error in " << dirEntry.path() << ": " << e.what() << std::endl;
        }
    }

    // Set initial scene
    setActiveScene("Test");

    // Add scripts to objects
    activeScene_->objects_.at("cube").object_->addScript("bird");
}

void Game::setupShaders() {
    // Compile Shaders and add to shader map
    shaders_.try_emplace("defaultShader", "shader.vs", "shader.fs");
    shaders_.try_emplace("lightShader", "shader.vs", "lightShader.fs");

    for (auto i : shaders_) {
        i.second.use();
        i.second.setVec3("lightPos", glm::vec3(3.0f, 2.0f, 0.0f));
        i.second.setVec3("lightColor", glm::vec3(1.0f));
    }
}

void Game::setupScripts() {
    scriptManager_->loadScript("bird", "bird.lua");
}

void Game::update(float deltaTime) {
    activeScene_->runScripts();
    deltaTime_ = deltaTime;
    // Game logic here
}

void Game::run() {
    engine_.run(*this);
}
