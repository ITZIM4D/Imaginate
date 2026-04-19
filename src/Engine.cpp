#include <Engine.h>

Engine::Engine(int screenWidth, int screenHeight) : deltaTime_(0.0), lastFrame_(0.0), 
    screenWidth_(screenWidth), screenHeight_(screenHeight) {
        currWindow_ = std::make_shared<Window>(screenWidth_, screenHeight_); // Normal window object
        window_ = currWindow_->getWindow(); // GLFW window object (Context maybe?)
        camera_ = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
        inputManager_ = std::make_shared<InputManager>(window_, camera_, deltaTime_, screenWidth_, screenHeight_);
        scriptManager_ = std::make_shared<ScriptManager>(inputManager_);
        
        // TODO: This is the scene testing, not a final product
        Scene test;
        scenes_["Test"] = test;
        initScene("Test");
}

void Engine::run() {
    init();

    while (!glfwWindowShouldClose(window_)) {
        update();
        render();
    }
    shutdown();
}

void Engine::init() {
    scriptManager_->loadScript("Hello World", "test.lua");
    scriptManager_->runScript("Hello World");

    stbi_set_flip_vertically_on_load(true);

    // Compile Shaders and add to shader map
    shaders_.try_emplace("defaultShader", "shader.vs", "shader.fs");
    shaders_.try_emplace("lightShader", "shader.vs", "lightShader.fs");

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // TODO: in the future add init scene and possibly delete scene
    GameObject cube("cube/Cube.obj", *scriptManager_);
    GameObject lightCube("cube/Cube.obj", *scriptManager_);

    scenes_["Test"].addObject("cube", std::make_shared<GameObject>(cube), shaders_.at("defaultShader"));
    scenes_["Test"].addObject("lightCube", std::make_shared<GameObject>(lightCube), shaders_.at("lightShader"));

    // Model matrix to transform to world space (Because there is a model matrix for each object)
    glm::mat4 cubeModel = glm::mat4(1.0f);
    scenes_["Test"].objects_.at("cube").object_->translate(cubeModel, glm::vec3(0.0f, -2.0f, -3.0f));

    glm::mat4 lightModel = glm::mat4(1.0f);
    scenes_["Test"].objects_.at("lightCube").object_->translate(lightModel, glm::vec3(3.0f, 2.0f, 0.0f));
    scenes_["Test"].objects_.at("lightCube").object_->scale(lightModel, glm::vec3(0.5f));
}

void Engine::update() {
    // Go through scene stuff as well? like scenes_[0].scripts
    // Per frame time logic
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime_ = currentFrame - lastFrame_;
    lastFrame_ = currentFrame;

    // Poll events and run scripts
    glfwPollEvents();
    // Run scripts (May have to be done after shader stuff)
    scriptManager_->loadScript("test", "test.lua");
    currScene_->objects_.at("cube").object_->addScript("test");
    currScene_->objects_.at("cube").object_->runScripts();

    // input
    inputManager_->processInput();
}

void Engine::render() {
    glClearColor(0.44f, 0.82f, 0.88f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Light position
    glm::vec3 lightPos = scenes_["Test"].objects_.at("lightCube").object_->getPos();

    // View matrix 
    glm::mat4 view = camera_.GetViewMatrix();

    // Projection matrix for perspective
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(camera_.Zoom), ((float) screenWidth_ / (float) screenHeight_), 0.1f, 100.0f);

    // Send matrix uniforms to shader
    currScene_->setVec3("cube", "viewPos", camera_.Position);
    currScene_->setVec3("cube", "lightPos", lightPos);
    currScene_->setVec3("cube", "lightColor", glm::vec3(1.0f));
    currScene_->setMat4("cube", "model", glm::translate(glm::mat4(1.0f), scenes_["Test"].objects_.at("cube").object_->getPos()));
    currScene_->setMat4("cube", "view", view);
    currScene_->setMat4("cube", "projection", projection);

    currScene_->setMat4("lightCube", "model", glm::translate(glm::mat4(1.0f), scenes_["Test"].objects_.at("lightCube").object_->getPos()));
    currScene_->setMat4("lightCube", "view", view);
    currScene_->setMat4("lightCube", "projection", projection);  

    scenes_["Test"].drawScene();

    // Check and call events and swap buffers
    glfwSwapBuffers(window_);
}

void Engine::shutdown() {
    glfwTerminate();
}

void Engine::initScene(std::string sceneName) {
    if (scenes_.find(sceneName) != scenes_.end()) {
        currScene_ = &scenes_.at("Test");
    } else {
        std::cerr << "Scene: " << sceneName << " doesn\'t exist in scenes" << std::endl;
    }
}