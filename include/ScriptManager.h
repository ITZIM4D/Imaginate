#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include "InputManager.h"

class ScriptManager {
    public:
        sol::state lua_;

        /**
         * @brief Opens libraries to script and runs the script
         */
        ScriptManager(std::shared_ptr<InputManager> inputManager);

        /**
         * @brief Loads script file
         * 
         * @param name Name of the script to be stored as
         * @param path Path to the script with the scripts folder being the root
         * 
         * @returns A boolean of whether or not the script successfully loaded
         */
        bool loadScript(const std::string& name, const std::string& path);

        /**
         * @brief Executes a loaded Lua script with validation and error handling.
         *
         * Searches for the script by name in the internal container. If the script
         * is not found or is invalid, an error message is printed and execution is
         * aborted. If found, the script is invoked using sol::protected_function,
         * and any runtime errors are captured and reported.
         *
         * @param name The identifier of the script to execute.
         */
        void runScript(const std::string& name);
    
    private:
        std::unordered_map<std::string, sol::protected_function> scripts_;
        std::shared_ptr<InputManager> inputManager_;
        
        /**
         * @brief Sets all of the lua functions
         */
        void setFunctions();

        /**
         * @brief Sets all of the lua enums
         */
        void setEnums();

        /**
         * @brief Sets all of the lua usertypes
         */
        void setUserTypes();

};

#endif