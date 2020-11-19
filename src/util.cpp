#include <fstream>
#include <sstream>
#include "../headers/util.hpp"

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

void printProgramInfoLog(GLuint program) {
  int maxLength = 2048;
  int actualLength = 0;
  char programLog[2048];
  glGetProgramInfoLog(program, maxLength, &actualLength, programLog);
  printf("program info log for GL index %u:\n%s", program, programLog);
}


void linkProgram(GLuint &shader_program) {
    glLinkProgram(shader_program);
    int params = -1;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &params);
    if (params != GL_TRUE) {
        fprintf(stderr, "ERROR: Failed to link shader program %u\n", shader_program);
        printProgramInfoLog(shader_program);
    }
}

void compileShader(GLuint &fs) {
    glCompileShader(fs);
    int params = -1;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE) {
        fprintf(stderr, "ERROR: GL shader %i failed to compile\n", fs);
        printShaderInfoLog(fs);
    }
}
