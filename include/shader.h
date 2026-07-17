//
// Created by stefano on 23/06/26.
//

#ifndef SHADER_H
#define SHADER_H

#include <thirdparty/glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>


class Shader {
public:
    // the program ID
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    // use/activate the shader
    void use() const;

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4f(const std::string &name, glm::mat4 value) const;
    void setVec3f(const std::string &name, float n1, float n2, float n3) const;
    void setVec3f(const std::string &name, glm::vec3 value) const;

    bool getBool(const std::string &name) const;
    int getInt(const std::string &name) const;
    float getFloat(const std::string &name) const;

    unsigned int getID() const;

private:
    unsigned int ID;
    static std::string readShaderSource(const std::string& filePath);
};


#endif
