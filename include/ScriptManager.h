#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

class ScriptManager {
    public:
        sol::state lua_;

        /**
         * @brief Opens libraries to script and runs the script
         */
        ScriptManager();

        /**
         * @brief Loads script file
         * 
         * @param name Name of the script to be stored as
         * @param path Path to the script
         * 
         * @returns A boolean of whether or not the script successfully loaded
         */
        bool loadScript(const std::string& name, const std::string& path);

        /**
         * @brief Runs specified script
         * 
         * @param name Name of the script to be run
         */
        void runScript(const std::string& name);
    
    private:
        std::unordered_map<std::string, sol::protected_function> scripts_;
};

#endif