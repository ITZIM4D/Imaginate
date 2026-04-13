#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Model.h>
#include <math.h>
#include <ScriptManager.h>

/**
 * @class GameObject
 * 
 * @brief Represents an object in the scene
 */
class GameObject {
    public:
        /**
         * @brief Instantiates a model with default values
         * 
         * @param modelPath path to the model that is to be created
         * @param scriptManager script manager for objects scripts
         */
        GameObject(std::string modelPath, ScriptManager& scriptManager);

        /**
         * @brief Translates the model by a vec3 amount and sets the given matrix to that
         * 
         * @param view A reference to the mat4 whose location is going to be changed (The model matrix)
         * @param translation The vec3 to translate the view by
         */
        void translate(glm::mat4 &view, glm::vec3 translation);

        /**
         * @brief rotates the model by the specified angle around the x axis
         * 
         * @param view A reference to the mat 4 whose rotation is going to be changed (The model matrix)
         * @param angle The angle in degrees to rotate by
         */
        void rotateX(glm::mat4 &view, GLfloat angle);

        /**
         * @brief rotates the model by the specified angle around the y axis
         * 
         * @param ModelMatrix A reference to the mat 4 whose rotation is going to be changed (The model matrix)
         * @param angle The angle in degrees to rotate by
         */
        void rotateY(glm::mat4 &ModelMatrix, GLfloat angle);

        /**
         * @brief rotates the model by the specified angle around the z axis
         * 
         * @param ModelMatrix A reference to the mat 4 whose rotation is going to be changed (The model matrix)
         * @param angle The angle in degrees to rotate by
         */
        void rotateZ(glm::mat4 &ModelMatrix, GLfloat angle);

        /**
         * @brief rotates the model by a 
         * 
         * @param ModelMatrix A reference to the mat 4 whose rotation is going to be changed (The model matrix)
         * @param scale_vector The vector that the object will be scaled by
         */
        void scale(glm::mat4 &ModelMatrix, glm::vec3 scale_vector);

        /**
         * @brief Getter method for GameObject's position
         * 
         * @returns The position of the object as a vec3
         */
        glm::vec3 getPos() const {return pos_;}

        /**
         * @brief Getter method for GameObject's rotation
         * 
         * @returns The rotation of the object as a vec3
         */
        glm::vec3 getRotation() {return rotation_;}

        /**
         * @brief Getter method for GameObject's scale
         * 
         * @returns the scale of the object as a vec3
         */
        glm::vec3 getScale() {return scale_;}

        /**
         * @brief invokes the model's draw function with the passed in shader
         * 
         * @param shader The shader that is being used to draw
         */
        void Draw(Shader &shader);

        /**
         * @brief Adds a script to be tied to the object
         * 
         * @param name Name of the script to be added
         */
        void addScript(const std::string& name);

        /**
         * @brief Runs all scripts in the scripts vector
         */
        void runScripts();

    private:
        /******* Private Variables *******/
        GameObject* parent_;
        Model model_;
        glm::vec3 pos_; // The global position of the object
        glm::vec3 rotation_; // The current rotation of the object
        glm::vec3 scale_; // The current scale of the object
        ScriptManager& scriptManager_;
        std::vector<std::string> scripts_; // A vector of the scripts that the object has
        
};

#endif