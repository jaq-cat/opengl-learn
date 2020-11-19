#pragma once
#include <string>
#include <iostream>

#include <GL/glew.h>

std::string load_file(const std::string& path);

void printShaderInfoLog(GLuint vs);

void printProgramInfoLog(GLuint program);

void linkProgram(GLuint &shader_program);

void compileShader(GLuint &fs);
