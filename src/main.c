#include "init.h"
#include <stdio.h>

int main() {
    GLFWwindow *win;
    int result = init(win);
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

    while (!glfwWindowShouldClose(win)) {
        // clear
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw stuff
        glFlush();
        glfwPollEvents();

        // show stuff
        glfwSwapBuffers(win);

        // close window
        if (glfwGetKey(win, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(win, 1);
    }
    glfwTerminate();
    return 0;
}
