#include <ScriptManager.h>

ScriptManager::ScriptManager() {
    lua_.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);
}

bool ScriptManager::loadScript(const std::string& name, const std::string& path) {
    sol::load_result script = lua_.load_file(path);
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
    scripts_[name]();
}