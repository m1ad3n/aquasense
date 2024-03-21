#include "shader.h"
#include <stdio.h>
#include <stdlib.h>

sShader* sShader_new(const char* _vpath, const char* _fpath) {
    sShader* shader = (sShader*)malloc(sizeof(sShader));

    FILE* vShaderFile;
    FILE* fShaderFile;
    char* vertexCode = NULL;
    char* fragmentCode = NULL;
    
    vShaderFile = fopen(_vpath, "r");
    if (!vShaderFile) {
        fprintf(stderr, "SHADER ERROR: Failed to open vertex shader file: %s\n", _vpath);
        return NULL;
    }
    fseek(vShaderFile, 0, SEEK_END);
    long vSize = ftell(vShaderFile);
    fseek(vShaderFile, 0, SEEK_SET);
    vertexCode = (char*)malloc(vSize + 1);
    fread(vertexCode, 1, vSize, vShaderFile);
    fclose(vShaderFile);
    vertexCode[vSize] = '\0';
    
    fShaderFile = fopen(_fpath, "r");
    if (!fShaderFile) {
        fprintf(stderr, "SHADER ERROR: Failed to open fragment shader file: %s\n", _fpath);
        free(vertexCode);
        return NULL;
    }
    fseek(fShaderFile, 0, SEEK_END);
    long fSize = ftell(fShaderFile);
    fseek(fShaderFile, 0, SEEK_SET);
    fragmentCode = (char*)malloc(fSize + 1);
    fread(fragmentCode, 1, fSize, fShaderFile);
    fclose(fShaderFile);
    fragmentCode[fSize] = '\0';

    unsigned int vertex, fragment;
    int success;
    
    // Vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);
    // checkCompileErrors(vertex, "VERTEX");
    
    // Fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);
    // checkCompileErrors(fragment, "FRAGMENT");
    
    // Shader program
    shader->ID = glCreateProgram();
    glAttachShader(shader->ID, vertex);
    glAttachShader(shader->ID, fragment);
    glLinkProgram(shader->ID);
    // checkCompileErrors(shader->ID, "PROGRAM");
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    free(vertexCode);
    free(fragmentCode);

    return shader;
}

void sShader_use(const sShader* shader) {
    glUseProgram(shader->ID);
}

void sShader_setBool(const sShader* shader, const char* name, bool value) {
    glUniform1i(glGetUniformLocation(shader->ID, name), (int)value);
}

void sShader_setInt(const sShader* shader, const char* name, int value) {
    glUniform1i(glGetUniformLocation(shader->ID, name), value);
}

void sShader_setFloat(const sShader* shader, const char* name, float value) {
    glUniform1f(glGetUniformLocation(shader->ID, name), value);
}

void sShader_setVec4(const sShader* shader, const char* name, float values[4]) {
    glUniform4f(glGetUniformLocation(shader->ID, name), values[0], values[1], values[2], values[3]);
}

void sShader_destroy(sShader* shader) {
    glDeleteProgram(shader->ID);
    free(shader);
}