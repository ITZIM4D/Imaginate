#include "Scene.h"

void Scene::addObject(std::string objectName, std::shared_ptr<GameObject> object, Shader shader) {
    Object tempObject = {object, shader};
    if (!(objects_.try_emplace(objectName, tempObject)).second) {
        std::cerr << objectName << " already exists. Please make the object name unique" << std::endl;
    }
}

void Scene::setMat4(std::string objectName, std::string uniformName, glm::mat4 value) {
    if (objects_.find(objectName) != objects_.end()) {
        objects_.at(objectName).shader_.use();
        objects_.at(objectName).shader_.setMat4(uniformName, value);
    } else {
        std::cerr << objectName << " Not in objects_ map" << std:: endl;
    }
}

void Scene::setVec3(std::string objectName, std::string uniformName, glm::vec3 value) {
    if (objects_.find(objectName) != objects_.end()) {
        objects_.at(objectName).shader_.use();
        objects_.at(objectName).shader_.setVec3(uniformName, value);
    } else {
        std::cerr << objectName << " Not in objects_ map" << std:: endl;
    }
}

void Scene::render(Camera& camera, int screenWidth, int screenHeight) {
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), ((float) screenWidth / (float) screenHeight), 0.1f, 100.0f);

    for (auto& [name, obj] : objects_) {
        Shader& shader = obj.shader_;
        shader.use();

        // Core matrics
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setMat4("model", obj.object_->getModelMatrix());
        shader.setVec3("lightPos", lightPos_);

        shader.setVec3("viewPos", camera.Position);

        obj.object_->Draw(shader);
    }
}

void Scene::runScripts() {
    for (auto& [name, obj] : objects_) {
        obj.object_->runScripts();
    }
}