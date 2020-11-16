#include <fstream>
#include <iostream>
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

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

    // only draw closer values
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    int width, height;
    glfwGetFramebufferSize(win, &width, &height);
    glViewport(0, 0, width, height);

    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    cout << "Renderer: " << renderer << endl;
    cout << "OpenGL version: " << version << endl;

    /* 
     * stuff
     * */
    float points[] = {
         0.0, 0.5,  0.0,
         0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0
    };

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    const char* vertex_shader =
    "#version 400\n"
    "in vec3 vp;"
    "void main() {"
    "  gl_Position = vec4(vp, 1.0);"
    "}";

    const char* fragment_shader =
    "#version 400\n"
    "out vec4 frag_colour;"
    "void main() {"
    "  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
    "}";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);

    while (!glfwWindowShouldClose(win)) {
        // wipe drawing surface
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // use shaders
        glUseProgram(shader_program);
        // bind VAO
        glBindVertexArray(vao);
        // draw
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // poll events
        glfwPollEvents();
        // show stuff
        glfwSwapBuffers(win);
    }

    glfwTerminate();
    return 0;
}
