#include <GameObject.h>

GameObject::GameObject(const char* modelPath, ScriptManager& scriptManager) : model_(modelPath), pos_(glm::vec3(0)),
 rotation_(glm::vec3(0)), scale_(glm::vec3(1)), scriptManager_(scriptManager) {};

void GameObject::translate(glm::mat4 &ModelMatrix, glm::vec3 translation) {
    pos_ += translation; // Update object position variable
    ModelMatrix = glm::translate(ModelMatrix, translation);
}

void GameObject::rotateX(glm::mat4 &ModelMatrix, GLfloat angle) { 
    rotation_.x += fmodl(angle, 360.0f);
    rotation_.x = fmodl(rotation_.x, 360.0f);
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(angle), glm::vec3(1, 0, 0));
}

void GameObject::rotateY(glm::mat4 &ModelMatrix, GLfloat angle) { 
    rotation_.y += fmodl(angle, 360.0f);
    rotation_.y = fmodl(rotation_.y, 360.0f);
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(angle), glm::vec3(0, 1, 0));
}

void GameObject::rotateZ(glm::mat4 &ModelMatrix, GLfloat angle) { 
    rotation_.z += fmodl(angle, 360.0f);
    rotation_.z = fmodl(rotation_.z, 360.0f);
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(angle), glm::vec3(0, 0, 1));
}

void GameObject::scale(glm::mat4 &ModelMatrix, glm::vec3 scale_vector) {
    scale_ *= scale_vector;
    ModelMatrix = glm::scale(ModelMatrix, scale_vector);
}

void GameObject::Draw(Shader &shader) {
    model_.Draw(shader);
}

void GameObject::addScript(const std::string& name) {
    scripts_.push_back(name);
}

void GameObject::runScripts() {
    for (auto i : scripts_) {
        scriptManager_.runScript(i);
    }
}

