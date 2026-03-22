#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <iostream>

#include <stb_image.h>
#include <glad/glad.h>

class Texture {
    private:
        int width, height, nrChannels;
        unsigned char* data;
        GLuint id = 0;
        std::string path;

    public:
        /**
         * @brief Prepares a texture to be loaded
         * 
         * @param textureName the name and extension of the texture in the /assets/textures folder
         */
        Texture(std::string &textureName) {
            path = "../assets/textures/" + textureName;
        }

        ~Texture() {
            if (id != 0) {
                glDeleteTextures(1, &id);
            }
        }

        /**
         * @brief loads texture
         * 
         * @returns int value to store texture
         */
        GLuint loadTexture() {
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);

            // Wrapping/filtering options
            stbi_set_flip_vertically_on_load(true);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // Load and generate texture
            data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
            if (data) {
                GLenum format;
                if (nrChannels == 1) format = GL_RED;
                else if (nrChannels == 3) format = GL_RGB;
                else if (nrChannels == 4) format = GL_RGBA;

                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);

            return id;
        }
};

#endif