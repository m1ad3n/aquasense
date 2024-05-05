#include "deps.h"
#include "macros.h"
#include <sstream>
#include "buffers/shader.h"

using namespace as;

/**
 * @brief      Functions that checks for shader compilation errors
 *
 * @param[in]  shader  The shader ID
 * @param[in]  type    The shader type
 *
 * @return     void
 */
int Shader::checkCompileErrors(unsigned int shader, const std::string& type) {
    int success;
    char infoLog[1024];
    if (type.compare("PROGRAM")) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "OPENGL SHADER ERROR: Shader compilation error of type: " << type << std::endl;
            if (strlen(infoLog) > 0)
                std::cerr << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "OPENGL SHADER ERROR: Program linking error of type: " << type << std::endl;
            if (strlen(infoLog) > 0)
                std::cerr << infoLog << std::endl;
        }
    }
    return success;
}

Shader::Shader(const char* vertex_code, const char* fragment_code) : BufferBase("Shader") {
    unsigned int vertex, fragment;

    // Vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    GLCall(glShaderSource(vertex, 1, &vertex_code, NULL));
    GLCall(glCompileShader(vertex));
    if (checkCompileErrors(vertex, "VERTEX") == GL_FALSE) {
        glDeleteProgram(vertex);
    }

    // Fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    GLCall(glShaderSource(fragment, 1, &fragment_code, NULL));
    GLCall(glCompileShader(fragment));
    if (checkCompileErrors(fragment, "FRAGMENT") == GL_FALSE) {
        glDeleteProgram(vertex);
        glDeleteProgram(fragment);
    }

    // Shader program
    this->ID = glCreateProgram();
    GLCall(glAttachShader(this->ID, vertex));
    GLCall(glAttachShader(this->ID, fragment));
    GLCall(glLinkProgram(this->ID));

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    if (checkCompileErrors(this->ID, "PROGRAM") == GL_FALSE) {
        std::cerr << "SHADER ERROR: shader creation failed" << std::endl;
    }
}

void Shader::Bind() {
    glUseProgram(this->ID);
}

void Shader::Unbind() {
    glUseProgram(0);
}

void Shader::SetBool(const char* name, int value) {
    glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetMat4(const char* name, float* value) {
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, value);
}

void Shader::SetInt(const char* name, int value) {
    glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetFloat(const char* name, float value) {
    glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetVec2(const char* name, float values[2]) {
    glUniform2f(glGetUniformLocation(this->ID, name), values[0], values[1]);
}

void Shader::SetVec3(const char* name, float values[3]) {
    glUniform3f(glGetUniformLocation(this->ID, name), values[0], values[1], values[2]);
}

void Shader::SetVec4(const char* name, float values[4]) {
    glUniform4f(glGetUniformLocation(this->ID, name), values[0], values[1], values[2], values[3]);
}

void Shader::Delete() {
    glDeleteProgram(this->ID);
}
