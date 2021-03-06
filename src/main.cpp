#include <iostream>
#include <string>
#include <string_view>

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/transform.hpp>

#include "common/shaders.hpp"
#include "common/objects.hpp"

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::pair;

using namespace glm;

#define WIDTH (640.f * 1.8f)
#define HEIGHT (480.f * 1.8f)

int main(int argc, char** argv) {
    glewExperimental = GL_TRUE; // initialize glfw
    if (!glfwInit()) {
        cerr <<  "Failed to initialize GLFW" << endl;
        return -1;
    }
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // no resize/decorate
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

    GLFWwindow *win = glfwCreateWindow(WIDTH, HEIGHT, "Hello, OpenGL!", NULL, NULL); // initialize window
    if (win == NULL) {
        cerr << "Failed to initialize GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(win);

    // glew
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialzie GLEW" << endl;
        glfwTerminate();
        return -1;
    }

    // print opengl info
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << endl;
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

    glfwSetInputMode(win, GLFW_STICKY_KEYS, GL_TRUE);

    // vao
    GLuint vaId;
    glGenVertexArrays(1, &vaId);
    glBindVertexArray(vaId);

    // create objects
    static const GLfloat triangleData[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

    static const GLfloat cubeData[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    GLuint cube = createObject(cubeData, sizeof(cubeData));
    GLuint triangle = createObject(triangleData, sizeof(triangleData));
    GLuint programId = setupShaders("src/shaders/vertex.glsl", "src/shaders/frag.glsl");

    // matrix stuff
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), WIDTH/HEIGHT, 0.1f, 100.f); // projection matrix

    glm::mat4 view = glm::lookAt(
        glm::vec3(2, 2, 5), // world space
        glm::vec3(0, 0, 0), // looking at 0, 0, 0
        glm::vec3(0, 1, 0)); // head up (0, -1, 0 to look upside down)

    glm::mat4 triangleMat = glm::translate(glm::vec3(-1.5f, 0.f, 0.f)); // identity matrix (model is at the origin)
    glm::mat4 cubeMat = glm::translate(glm::vec3(1.5f, 0.f, 0.f)); // identity matrix (model is at the origin)

    glm::mat4 triMvp = projection * view * triangleMat;
    glm::mat4 cubeMvp = projection * view * cubeMat;

    GLuint matrixId = glGetUniformLocation(programId, "MVP");

    // z buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // main loop
    while (!glfwWindowShouldClose(win)) {
        // clear
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // shaders
        glUseProgram(programId);

        // draw objects
        drawObject(sizeof(cubeData), cube, matrixId, &cubeMvp[0][0]);
        drawObject(sizeof(triangleData), triangle, matrixId, &triMvp[0][0]);

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
