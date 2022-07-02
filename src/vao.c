#include "vao.h"

int vao_create(GLfloat data[], GLuint size) {
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

void vao_attr(GLuint i, GLuint n, GLenum type, GLenum normalized, GLuint stride) {
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(
        i,
        n, // numbers per attribute
        type, // type
        normalized, // normalized?
        stride, // bytes to next attribute
        NULL
    );

}
