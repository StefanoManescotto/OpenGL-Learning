//
// Created by stefano on 23/06/26.
//

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


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

private:
    unsigned int ID;
    static std::string readShaderSource(const std::string& filePath);
};


#endif
