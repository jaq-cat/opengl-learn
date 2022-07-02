#include  "shaders.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* shd_load(char *filename) {
  char* buffer = {0};
  unsigned long length = 0;
  FILE *file = fopen(filename, "rb");

  if (file) {
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = malloc(length+1);
    if (buffer) {
      fread(buffer, 1, length, file);
    }
    fclose(file);
  }

  buffer[length] = '\0';

  return strdup(buffer);
}

GLuint shd_compile(const GLchar src[], GLenum type) {

  GLuint id = glCreateShader(type);
  glShaderSource(id, 1, &src, NULL);
  glCompileShader(id);

  GLint result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int len;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
    char *msg = malloc(len*sizeof(char));

    glGetShaderInfoLog(id, len, &len, msg);
    printf("[!] Failed to compile shader: \n");
    printf("%s\n", msg);

    free(msg);

    glDeleteShader(id);
    return 0;
  }

  return id;
}

GLuint shd_create(char *vertex, char *frag) {
  GLuint program = glCreateProgram();
  GLuint vs = shd_compile(vertex, GL_VERTEX_SHADER);
  GLuint fs = shd_compile(frag, GL_FRAGMENT_SHADER);

  // create program
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  GLint result;
  int infoLogLen;
  glGetProgramiv(program, GL_LINK_STATUS, &result);
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);

  if (infoLogLen > 0) {
    char *errorMessage = malloc(infoLogLen*sizeof(char));
    glGetProgramInfoLog(program, infoLogLen, NULL, &errorMessage[0]);
    fprintf(stderr, "Error linking shaders: %s\n", &errorMessage[0]);
    free(errorMessage);
  }

  // delete shaders
  glDetachShader(program, vs);
  glDetachShader(program, fs);
  glDeleteShader(vs);
  glDeleteShader(fs);
  free(vertex);
  free(frag);

  return program;
}
