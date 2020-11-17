#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include "util.hpp"


void initStuff(float points[], size_t points_size, float colors[], size_t colors_size) {
    // points VBO
    GLuint pvbo = 0;
    glGenBuffers(1, &pvbo);
    glBindBuffer(GL_ARRAY_BUFFER, pvbo);
    glBufferData(GL_ARRAY_BUFFER, points_size, points, GL_STATIC_DRAW);
    // colors VBO
    GLuint cvbo = 0;
    glGenBuffers(1, &cvbo);
    glBindBuffer(GL_ARRAY_BUFFER, cvbo);
    glBufferData(GL_ARRAY_BUFFER, colors_size, colors, GL_STATIC_DRAW);
    
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, pvbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // shaders
    std::string vs_string, fs_string;
    const char* vs_c = (vs_string = load_file("shaders/vertex_shader.glsl")).c_str();
    const char* fs_c = (fs_string = load_file("shaders/fragment_shader.glsl")).c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_c, NULL);
    glCompileShader(vs);
    int params = -1;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
    if (GL_TRUE != params) {
        fprintf(stderr, "ERROR: GL shader %i failed to compile\n", vs);
        printShaderInfoLog(vs);
    }
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_c, NULL);
    glCompileShader(fs);
    params = -1;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &params);
    if (GL_TRUE != params) {
        fprintf(stderr, "ERROR: GL shader %i failed to compile\n", fs);
        printShaderInfoLog(fs);
    }

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);
    params = -1;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &params);
    if (GL_TRUE != params) {
        fprintf(stderr, "ERROR: Failed to link shader program %u\n", shader_program);
        printProgramInfoLog(shader_program);
    }

    glUseProgram(shader_program);
    glBindVertexArray(vao);
}
