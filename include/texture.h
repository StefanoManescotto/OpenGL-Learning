//
// Created by stefano on 26/06/26.
//

#ifndef GFXENGINE_TEXTURE_H
#define GFXENGINE_TEXTURE_H

#include <string>
#include <thirdparty/stb_image.h>
#include <thirdparty/glad/glad.h>

struct TextureConfig {
    std::string rootPath  = RESOURCES_DIR;
    GLenum wrapS          = GL_REPEAT;
    GLenum wrapT          = GL_REPEAT;
    GLenum minFilter      = GL_LINEAR_MIPMAP_LINEAR;
    GLenum magFilter      = GL_LINEAR;
    GLint internalFormat  = GL_RGB;
    GLint format          = GL_RGB;
};

class Texture {
public:
    Texture(
        const std::string& texturePath,
        const TextureConfig &config ={}
    );
    ~Texture();

    void bind() const;
    void unbind() const;

    unsigned int getID() const;

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

private:
    unsigned int ID = 0;
};


#endif //GFXENGINE_TEXTURE_H
