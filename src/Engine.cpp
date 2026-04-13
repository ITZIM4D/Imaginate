#include <Engine.h>

Engine::Engine(int screenWidth, int screenHeight) : deltaTime_(0.0), lastFrame_(0.0), 
    screenWidth_(screenWidth), screenHeight_(screenHeight) {
        currWindow_ = std::make_shared<Window>(screenWidth_, screenHeight_); // Normal window object
        window_ = currWindow_->getWindow(); // GLFW window object (Context maybe?)
        camera_ = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
        inputManager_ = std::make_shared<InputManager>(window_, camera_, deltaTime_, screenWidth_, screenHeight_);
        scriptManager_ = std::make_shared<ScriptManager>();
        
        // TODO: This is the scene testing, not a final product
        Scene test;
        scenes_["Test"] = test;
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
    // scriptManager_->loadScript("test", "test.lua");
    // scenes_.addScript("test");
    // cube.runScripts();

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

    shaders_.at("defaultShader").use();
    // Send matrix uniforms to shader
    shaders_.at("defaultShader").setVec3("viewPos", camera_.Position);
    shaders_.at("defaultShader").setVec3("lightPos", lightPos);
    shaders_.at("defaultShader").setVec3("lightColor", glm::vec3(1.0f));
    shaders_.at("defaultShader").setMat4("model", glm::translate(glm::mat4(1.0f), scenes_["Test"].objects_.at("cube").object_->getPos()));
    shaders_.at("defaultShader").setMat4("view", view);
    shaders_.at("defaultShader").setMat4("projection", projection);

    shaders_.at("lightShader").use();
    shaders_.at("lightShader").setMat4("model", glm::translate(glm::mat4(1.0f), scenes_["Test"].objects_.at("lightCube").object_->getPos()));
    shaders_.at("lightShader").setMat4("view", view);
    shaders_.at("lightShader").setMat4("projection", projection);

    

    scenes_["Test"].drawScene();
    
    // lightShader.setMat4("model", lightModel);
    // lightShader.setMat4("view", view);
    // lightShader.setMat4("projection", projection);
    // lightCube.Draw(lightShader);

    // Check and call events and swap buffers
    glfwSwapBuffers(window_);
}

void Engine::shutdown() {
    glfwTerminate();
}

void Engine::initScene(Scene scene) {

}