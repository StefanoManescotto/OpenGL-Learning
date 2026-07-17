//
// Created by stefano on 26/06/26.
//

#define STB_IMAGE_IMPLEMENTATION

#include "../include/texture.h"

#include <iostream>
#include <ostream>

Texture::Texture(const std::string &texturePath, const TextureConfig &config) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, config.wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, config.wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, config.minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, config.magFilter);

    // Load the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load((config.rootPath + texturePath).c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        GLenum format = GL_RGB;
        GLenum internalFormat = GL_RGB;

        if (nrChannels == 1) {
            format = GL_RED;
            internalFormat = GL_RED;
        } else if (nrChannels == 3) {
            format = GL_RGB;
            internalFormat = GL_RGB;
        } else if (nrChannels == 4) {
            format = GL_RGBA;
            internalFormat = GL_RGBA;
        }

        // 2. IMPORTANT: If the width is not a multiple of 4, 3-channel RGB images
        // will still look skewed unless we set the unpack alignment to 1.
        if (nrChannels == 3) {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        } else {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // Default OpenGL alignment
        }

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    } else {
        std::cout << "Failed to load texture: " << texturePath << std::endl;
    }
    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &ID);
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::getID() const {
    return ID;
}
