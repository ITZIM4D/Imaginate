#include <Scene.h>

void Scene::addObject(std::string objectName, std::shared_ptr<GameObject> object, Shader shader) {
    Object tempObject = {object, shader};
    if (!(objects_.try_emplace(objectName, tempObject)).second) {
        std::cerr << objectName << " already exists. Please make the object name unique" << std::endl;
    }
}

// set matrixes in here for the shader that is in the object
// change in engine to use the setter function

void Scene::setModelMatrix(glm::mat4 modelMatrix, std::string objectName) {
    if (objects_.find(objectName) != objects_.end()) {
        objects_.at(objectName).shader_.setMat4("model", modelMatrix);
    } else {
        std::cerr << objectName << " Not in objects_ map" << std:: endl;
    }
}

void Scene::setViewMatrix(glm::mat4 viewMatrix, std::string objectName) {
    if (objects_.find(objectName) != objects_.end()) {
        objects_.at(objectName).shader_.setMat4("view", viewMatrix);
    } else {
        std::cerr << objectName << " Not in objects_ map" << std:: endl;
    }
}

void Scene::setProjectionMatrix(glm::mat4 projectionMatrix, std::string objectName) {
    if (objects_.find(objectName) != objects_.end()) {
        objects_.at(objectName).shader_.setMat4("projection", projectionMatrix);
    } else {
        std::cerr << objectName << " Not in objects_ map" << std:: endl;
    }
}

void Scene::drawScene() {
    for (auto i : objects_) {
        i.second.shader_.use();
        i.second.object_->Draw(i.second.shader_);
    }
}