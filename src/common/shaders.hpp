#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

using std::string;
using std::ifstream;
using std::stringstream;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;


GLuint setupShaders(const char *vertexPath, const char *fragPath);
