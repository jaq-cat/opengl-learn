#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include "../headers/util.hpp"

void makeObject(GLfloat points[], size_t points_size, GLfloat colors[], size_t colors_size, GLuint &vao);

void makeShaders(GLuint &shader_program);
