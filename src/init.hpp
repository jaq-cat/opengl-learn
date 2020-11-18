#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include "util.hpp"

using std::pair;

void makeObject(GLfloat points[], size_t points_size, GLfloat colors[], size_t colors_size, GLuint &shader_program, GLuint &vao) {
    // VAOs
    glGenVertexArrays(sizeof(vao) / sizeof(GLuint), &vao);
    glBindVertexArray(vao);

    // VBOs
    GLuint vbos[] = {0, 0};
    glGenBuffers(2, vbos);
    // bind points to VBO 0
    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, points_size, points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); // bind this to index 0
    glEnableVertexAttribArray(0); // enable (shaders)
    // bind colors to VBO 1
    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
    glBufferData(GL_ARRAY_BUFFER, colors_size, colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL); // bind this to index 1
    glEnableVertexAttribArray(1); // enable (shaders)

    // shaders
    std::string vs_string, fs_string;
    const char* vs_c = (vs_string = load_file("shaders/vertex_shader.glsl")).c_str();
    const char* fs_c = (fs_string = load_file("shaders/fragment_shader.glsl")).c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_c, NULL);
    compileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_c, NULL);
    compileShader(fs);

    shader_program = glCreateProgram();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    linkProgram(shader_program);
}
