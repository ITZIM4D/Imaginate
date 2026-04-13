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
         * @brief Sets the model matrix of an object's shader
         * 
         * @param modelMatrix the model matrix to set for the object
         * @param objectName name of the object you want to set the matrix for 
         */
        void setModelMatrix(glm::mat4 modelMatrix, std::string objectName);

        /**
         * @brief Sets the view matrix of an object 
         * 
         * @param viewMatrix the view matrix to set for the object
         * @param objectName name of the object you want to set the matrix for 
         */
        void setViewMatrix(glm::mat4 viewMatrix, std::string objectName);

        /**
         * @brief Sets the projection matrix of an object 
         * 
         * @param projectionMatrix the projection matrix to set for the object
         * @param objectName name of the object you want to set the matrix for 
         */
        void setProjectionMatrix(glm::mat4 projectionMatrix, std::string objectName);

        /**
         * @brief Draws all objects in the scene
         */
        void drawScene();

    private:
        std::unordered_map<std::string, Shader> shaders_;
        
};

#endif