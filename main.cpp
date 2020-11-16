#include <iostream>
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include "math_3d.hpp"

#define WIDTH 640
#define HEIGHT 640
//#define HEIGHT 480

void display() {
    glClearColor(0.0, 1.0, 0.0, 1.0); // dark purple background
    glClear(GL_COLOR_BUFFER_BIT); // clear color buffer
    glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(-0.5, 0.5);
    glEnd();

    glFlush(); // render
}

int main(int argc, char** argv) {
    // initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW");
        return -1;
    }
    GLFWwindow* win;

    // initialize window
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    win = glfwCreateWindow(WIDTH, HEIGHT, "Hello, OpenGL!", NULL, NULL);
    if (!win) {
        fprintf(stderr, "Failed to initialize GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(win);

    int width, height;
    glfwGetFramebufferSize(win, &width, &height);
    glViewport(0, 0, width, height);

    glfwSwapInterval(1);
    // main loop
    double time;
    while (!glfwWindowShouldClose(win)) {
        // update
        time = glfwGetTime();
        // render
        display();
        // swap buffers
        glfwSwapBuffers(win);
        // poll events
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
