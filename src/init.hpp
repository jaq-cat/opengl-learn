#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include "util.hpp"

using std::pair;


:oid initStuff(float points[], size_t points_size, float colors[], size_t colors_size, GLuint &shader_program, GLuint &vao) {
    // vertex buffer objects
    // points
    GLuint pvbo = 0;
    glGenBuffers(1, &pvbo);
    glBindBuffer(GL_ARRAY_BUFFER, pvbo);
    glBufferData(GL_ARRAY_BUFFER, points_size, points, GL_STATIC_DRAW);
    // colors
    GLuint cvbo = 0;
    glGenBuffers(1, &cvbo);
    glBindBuffer(GL_ARRAY_BUFFER, cvbo);
    glBufferData(GL_ARRAY_BUFFER, colors_size, colors, GL_STATIC_DRAW);

    // vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, pvbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, cvbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

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

    shader_program = glCreateShader();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);
    params = -1;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &params);
    if (GL_TRUE != params) {
        fprintf(stderr, "ERROR: Failed to link shader program %u\n", shader_program);
        printProgramInfoLog(shader_program);
    }
}
