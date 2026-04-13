#include <ScriptManager.h>

ScriptManager::ScriptManager() {
    lua_.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);
}

bool ScriptManager::loadScript(const std::string& name, const std::string& path) {
    sol::load_result script = lua_.load_file("../assets/scripts/" + path);
    if (script.valid()) {
        sol::protected_function function = script;
        scripts_[name] = function;
        return true;
    } else {
        std::cerr << "Failed to load script: " << sol::error(script).what() << std::endl;
        return false;
    }
}

void ScriptManager::runScript(const std::string& name) {
    auto it = scripts_.find(name);
    if (it == scripts_.end()) {
        std::cerr << "Script not found: " << name << std::endl;
        return;
    }

    if (!it->second.valid()) {
        std::cerr << "Invalid script: " << name << std::endl;
        return;
    }

    sol::protected_function_result result = it->second();
    if (!result.valid()) {
        sol::error err = result;
        std::cerr << "Runtime error: " << err.what() << std::endl;
    }
}