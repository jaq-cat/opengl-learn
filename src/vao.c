#include "vao.h"

int vao_create() {
  GLuint vao;
  glGenVertexArrays(1, &vao);
  return vao;
}

void vao_bind(GLuint vao) {
  glBindVertexArray(vao);
}

void vao_unbind() {
  glBindVertexArray(0);
}

void vao_enable(GLuint i) {
  glEnableVertexAttribArray(i);
}

void vao_disable(GLuint i) {
  glDisableVertexAttribArray(i);
}

void vao_attr(GLuint i, GLuint n, GLenum type, GLenum normalized, GLuint stride) {
  glVertexAttribPointer(
      i,
      n, // number of items per attribute
      type,
      normalized, // normalized?
      stride, // size of entire vertex
      NULL
      );
}
