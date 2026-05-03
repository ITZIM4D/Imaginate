#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"

struct Object {
    std::shared_ptr<GameObject> object_;
    Shader shader_;
};

class Scene {
    public:
        // TODO: make objects private in the future
        std::unordered_map<std::string, Object> objects_;
        /**
         * @brief Adds an object to the scene
         * 
         * @param object A pointer to the GameObject
         * @param shader The shader is to be used to draw the object
         */
        void addObject(std::string objectName, std::shared_ptr<GameObject> object, Shader shader);

        /**
         * @brief Sets a mat4 object
         * 
         * @param objectName name of the object you want to set the matrix for
         * @param value value to set the uniform as
         * @param uniformName name of the shader uniform that is being updated
         */
        void setMat4(std::string objectName, std::string uniformName, glm::mat4 value);

        /**
         * @brief sets vec3 object
         * 
         * @param objectName name of the object you want to set the vec3 for
         * @param value value to set the uniform as
         * @param uniformName name of the shader uniform that is being updated
         */
        void setVec3(std::string objectName, std::string uniformName, glm::vec3 value);

        /**
         * @brief sets the only light position (Only the one currently)
         * 
         * @param newLightPos The new position to change the light to being
         */
        void setLightPos(glm::vec3 newLightPos) {lightPos_ = newLightPos;}

        /**
         * @brief Renders the current scene
         * 
         * @param camera The camera object that is being used
         * @param screenWidth The size of the x axis of the screen
         * @param screenHeight The size of the y axis of the screen
         */
        void render(Camera& camera, int screenWidth, int screenHeight);

        /**
         * @brief Runs all scripts in the scene
         */
        void runScripts();

    private:
        std::unordered_map<std::string, Shader> shaders_;
        glm::vec3 lightPos_;
        
};

#endif