#include "Engine.h"
#include "Game.h"

Engine::Engine(int screenWidth, int screenHeight) : deltaTime_(0.0), lastFrame_(0.0), 
    screenWidth_(screenWidth), screenHeight_(screenHeight) {
        currWindow_ = std::make_shared<Window>(screenWidth_, screenHeight_); // Normal window object
        window_ = currWindow_->getWindow(); // GLFW window object (Context maybe?)
        camera_ = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
        inputManager_ = std::make_shared<InputManager>(window_, camera_, deltaTime_, screenWidth_, screenHeight_);
        scriptManager_ = std::make_shared<ScriptManager>(inputManager_);
}

void Engine::run(Game& game) {
    init();

    while (!glfwWindowShouldClose(window_)) {
        update();
        game.update(deltaTime_);
        render();
    }
    shutdown();
}

void Engine::init() {
    stbi_set_flip_vertically_on_load(true);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
}

void Engine::update() {
    // Per frame time logic
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime_ = currentFrame - lastFrame_;
    lastFrame_ = currentFrame;

    // Poll events and run scripts
    glfwPollEvents();
    
    // Run scripts for each object
    for (auto i : currScene_->objects_) {
        i.second.object_->runScripts();
    }

    // input
    inputManager_->processInput();
}

void Engine::render() {
    glClearColor(0.44f, 0.82f, 0.88f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    currScene_->render(camera_, screenWidth_, screenHeight_);

    // Check and call events and swap buffers
    glfwSwapBuffers(window_);
}

void Engine::shutdown() {
    glfwTerminate();
}

void Engine::initScene(std::string sceneName) {
    if (scenes_.find(sceneName) != scenes_.end()) {
        currScene_ = &scenes_.at(sceneName);
    } else {
        std::cerr << "Scene: " << sceneName << " doesn\'t exist in scenes" << std::endl;
    }
}