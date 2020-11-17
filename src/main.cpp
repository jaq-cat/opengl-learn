#include <iostream>
#include <string>
#include <string_view>
#include <cmath>
#include "util.hpp"
#include "init.hpp"

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

using std::string;
using std::cout;
using std::endl;

#define WIDTH 640
#define HEIGHT 640
//#define HEIGHT 480

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

    // extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    // configure sheet
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glLineWidth(1);

    int width, height;
    glfwGetFramebufferSize(win, &width, &height);
    glViewport(0, 0, width, height);

    // version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    cout << "Renderer: " << renderer << endl;
    cout << "OpenGL version: " << version << endl;

    // triangle
    float points[] = {
         0.0,  0.5,  0.0,
         0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0,
         //0.0, -1.0, 0.0,
    };

    float colors[] = {
        1.0, 0.0, 0.0, // RGB instead of XYZ
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0
    };

    initStuff(points, sizeof(points), colors, sizeof(colors));

    // main loop
    while (!glfwWindowShouldClose(win)) {
        // update

        // draw
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        // poll events
        glfwPollEvents();

        // show stuff
        glfwSwapBuffers(win);
    }

    glfwTerminate();
    return 0;
}
