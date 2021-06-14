#include "init.h"
#include <stdio.h>

GLuint _triangleVBO() {

    GLfloat positions[] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions)/sizeof(GLfloat), positions, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vbo;
}

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

    int triangle = _triangleVBO();

    while (!glfwWindowShouldClose(win)) {
        // clear
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw stuff
        glFlush();

        glBindBuffer(GL_ARRAY_BUFFER, triangle);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

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
