#include "init.h"
#include "vbo.h"
#include <stdio.h>

int main() {
    GLFWwindow *win;
    int result = init(&win);
    if (result > 0) {
        fprintf(stderr, "[!] Failed to initialize ");
        switch (result) {
            case E_GLFW_INIT:
                fprintf(stderr, "GLFW");
                break;
            case E_GLFW_WIN:
                fprintf(stderr, "GLFW Window");
                break;
            case E_GLEW_INIT:
                fprintf(stderr, "GLEW");
                break;
        }
        fprintf(stderr, "\n");
        return -1;
    }

    fprintf(stderr, "Renderer: %s\n", glGetString(GL_RENDERER));
    fprintf(stderr, "OpenGL vendor: %s\n", glGetString(GL_VENDOR));
    fprintf(stderr, "OpenGL version: %s\n", glGetString(GL_VERSION));

    GLfloat positions[] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    GLuint tri = VBO.create(positions, sizeof(positions));

    // how to use positions in the shader
    VBO.bind(tri);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        2, // 2 numbers per attribute
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        sizeof(GLfloat)*2, // bytes to next attribute
        0
    );

    while (!glfwWindowShouldClose(win)) {
        // clear
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw stuff
        glFlush();

        VBO.bind(tri);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        VBO.unbind();

        // show stuff
        glfwSwapBuffers(win);

        glfwPollEvents();
        // close window
        if (glfwGetKey(win, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(win, 1);
    }
    glfwTerminate();
    return 0;
}
