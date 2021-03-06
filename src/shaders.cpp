#include "common/shaders.hpp"

string readFile(const char *filepath) {
    string str;
    ifstream fileStream(filepath, std::ios::in);
    if (fileStream.is_open()) {
        std::stringstream sstr;
        sstr <<  fileStream.rdbuf();
        str = sstr.str();
        fileStream.close();
    } else
        cerr << "Unable to open file " << filepath << endl;

    return str;
}

void compileShader(const GLuint &shaderId, const char *filepath) {

    GLint result = GL_FALSE;
    int infoLogLen;

    // Get shader source code and turn it into a C string
    string shaderCode = readFile(filepath);
    char const *shaderCodePointer = shaderCode.c_str();

    // Compile the shader
    cout << "Compiling " << filepath << endl;
    glShaderSource(shaderId, 1, &shaderCodePointer, NULL);
    glCompileShader(shaderId);

    // Check for and print any shader errors
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLen);
    if (infoLogLen > 0) {
        std::vector<char> errorMessage(infoLogLen+1);
        glGetShaderInfoLog(shaderId, infoLogLen, NULL, &errorMessage[0]);
        cerr << &errorMessage[0] << endl;
    }
    cout << "Done" << endl;
}

GLuint createShaderProgram(vector<GLuint> shaderIds) {
    // Create program and attach shaders
    GLuint programId = glCreateProgram();
    for (GLuint shaderId : shaderIds)
        glAttachShader(programId, shaderId);
    glLinkProgram(programId);

    // Check for and print any program errors
    GLint result = GL_FALSE;
    int infoLogLen;
    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLen);

    if (infoLogLen > 0) {
        std::vector<char> errorMessage(infoLogLen+1);
        glGetProgramInfoLog(programId, infoLogLen, NULL, &errorMessage[0]);
        cerr << &errorMessage[0] << endl;
    }

    return programId;
}

GLuint setupShaders(const char *vertexPath, const char *fragPath) {
    // Create shader objects
    GLuint vertexId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragId = glCreateShader(GL_FRAGMENT_SHADER);

    // Compile shaders
    compileShader(vertexId, vertexPath);
    compileShader(fragId, fragPath);

    // Link program
    GLuint programId = createShaderProgram(vector<GLuint> {vertexId, fragId});

    // Detach and delete shaders
    glDetachShader(programId, vertexId);
    glDetachShader(programId, fragId);
    glDeleteShader(vertexId);
    glDeleteShader(fragId);

    return programId;
}
