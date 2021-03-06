#include "common/objects.hpp"

GLuint createObject(const GLfloat vb_data[], const int vb_data_sizeof) {
    GLuint vb;
    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, vb_data_sizeof, vb_data, GL_STATIC_DRAW);

    return vb;
}

void drawObject(const GLfloat objSize, const GLuint objId, const GLuint matrixId, const GLfloat *objMvp) {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, objId);
    glVertexAttribPointer(
        0, // layout(location = 0) in vertex shader
        3, // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0, // stride
        NULL // array buffer offset
    );
    glDrawArrays(GL_TRIANGLES, 0, objSize/sizeof(GLfloat)/3);
    glDisableVertexAttribArray(0);
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, objMvp);
}
