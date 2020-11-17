#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

std::string load_file(const std::string& path) {
    auto ss = std::ostringstream{};
    std::ifstream file(path);
    ss << file.rdbuf();
    return ss.str();
}

void printShaderInfoLog(GLuint vs) {
    int maxLength = 2048;
    int actLength = 0;
    char shaderLog[maxLength];
    glGetShaderInfoLog(vs, maxLength, &actLength, shaderLog);
    std::cout << "Shader info for GL index " << vs << " " << shaderLog << std::endl;
}
