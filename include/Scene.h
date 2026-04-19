#ifndef SCENE_H
#define SCENE_H

#include <GameObject.h>

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
         * @brief Draws all objects in the scene
         */
        void drawScene();

    private:
        std::unordered_map<std::string, Shader> shaders_;
        
};

#endif