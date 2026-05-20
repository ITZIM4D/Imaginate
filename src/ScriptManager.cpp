#include "ScriptManager.h"
#include "GameObject.h"

ScriptManager::ScriptManager(std::shared_ptr<InputManager> inputManager) : inputManager_(inputManager) {
    lua_.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);
    setFunctions();
    setEnums();
    setUserTypes();
}

bool ScriptManager::loadScript(const std::string& name, const std::string& path) {
    std::string fullPath = std::string(PROJECT_ROOT) + "/assets/scripts/" + path;
    sol::load_result script = lua_.load_file(fullPath);     
    if (script.valid()) {
        scripts_[name] = script;
        return true;
    } else {
        std::cerr << "Failed to load script: " << sol::error(script).what() << std::endl;
        return false;
    }
}

void ScriptManager::runScript(const std::string& name, GameObject& obj) {
    auto it = scripts_.find(name);
    if (it == scripts_.end()) {
        std::cerr << "Script not found: " << name << std::endl;
        return;
    }
    
    sol::environment env(lua_, sol::create, lua_.globals());
    env["self"] = &obj; 

    if (!it->second.valid()) {
        std::cerr << "Invalid script: " << name << std::endl;
        return;
    }

    sol::protected_function_result result = it->second(env);
    if (!result.valid()) {
        sol::error err = result;
        std::cerr << "Runtime error: " << err.what() << std::endl;
    }

    // Call update()
    sol::function update = env["update"];
    if (update.valid()) {
        sol::protected_function_result updateResult = update();
        if (!updateResult.valid()) {
            sol::error err = updateResult;
            std::cerr << "Update error: " << err.what() << std::endl;
        }
    }
}

void ScriptManager::setFunctions() {
    lua_.set_function("KeyIsDown", [&] (const int keycode) {
        return inputManager_->KeyIsDown(keycode);
    });
}

void ScriptManager::setEnums() {
    lua_.new_enum<int>("KEYBOARD", {
        {"SPACE", GLFW_KEY_SPACE},
        {"W", GLFW_KEY_W},
        {"A", GLFW_KEY_A},
        {"S", GLFW_KEY_S},
        {"D", GLFW_KEY_D}
    });
}

void ScriptManager::setUserTypes() {
    lua_.new_usertype<glm::vec3>("vec3",
        sol::constructors<glm::vec3(), glm::vec3(float), glm::vec3(float, float, float)>(),
        "x", &glm::vec3::x,
        "y", &glm::vec3::y,
        "z", &glm::vec3::z,
        sol::meta_function::addition, sol::overload( [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 {return v1 + v2;} ),
        sol::meta_function::subtraction, sol::overload( [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 {return v1 - v2;} ),
        sol::meta_function::multiplication, sol::overload(
            [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 {return v1 * v2;},
            [](const glm::vec3& v1, float f) -> glm::vec3 {return v1 * f;},
            [](float f, const glm::vec3& v1) -> glm::vec3 {return f * v1;}
        )
    );

    lua_.new_usertype<GameObject>("GameObject",
        "position", &GameObject::pos_,
        "rotation", &GameObject::rotation_,
        "scale", &GameObject::scale_
    );
}

void ScriptManager::attachScript(const std::string& name, GameObject &obj) {
    auto it = scripts_.find(name);
    if (it == scripts_.end()) {
        std::cerr << "Script not found: " << name << std::endl;
        return;
    }

    sol::environment env(lua_, sol::create, lua_.globals());
    env["self"] = &obj;

    // Run script
    sol::protected_function_result result = it->second(env);
    if (!result.valid()) {
        sol::error err = result;
        std::cerr << "Runtime error: " << err.what() << std::endl;
        return;
    }

    // Store in object
    ScriptInstance instance;
    instance.env = env;
    instance.update = env["update"];
    obj.scriptInstances_.push_back(std::move(instance));
}

void ScriptManager::updateScript(GameObject& obj) {
    for (auto& script : obj.scriptInstances_) {
        if (script.update.valid()) {
            sol::protected_function_result result = script.update(&obj);
            if (!result.valid()) {
                sol::error err = result;
                std::cerr << "Update error: " << err.what() << std::endl;
            }
        }
    }
}
