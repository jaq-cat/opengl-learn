#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

using std::string;
using std::cout;
using std::endl;

#define WIDTH 640
#define HEIGHT 640
//#define HEIGHT 480

std::string load_file(const std::string& path) {
    auto ss = std::ostringstream{};
    std::ifstream file(path);
    ss << file.rdbuf();
    return ss.str();
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

    string vs_string = load_file("shaders/vertex_shader.glsl");
    string fs_string = load_file("shaders/fragment_shader.glsl");
    const char* vs_c = vs_string.c_str();
    const char* fs_c = fs_string.c_str();

    cout << vs_c << endl;
    cout << fs_c << endl;

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_c, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_c, NULL);
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
