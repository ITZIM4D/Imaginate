#include <Scene.h>

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

void Scene::drawScene() {
    for (auto i : objects_) {
        i.second.shader_.use();
        i.second.object_->Draw(i.second.shader_);
    }
}