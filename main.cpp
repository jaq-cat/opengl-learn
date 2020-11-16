#include <iostream>
#include <GLFW/glfw3.h>

#define WIDTH 640
#define HEIGHT 480

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
    GLFWwindow* win;
    if (!glfwInit())
        return -1;
    win = glfwCreateWindow(WIDTH, HEIGHT, "Hello, world!", NULL, NULL);
    if (!win) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(win);
    while (!glfwWindowShouldClose(win)) {
        display();
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
