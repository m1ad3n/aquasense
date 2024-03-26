#include "shader.h"
#include "../deps.h"

/**
 * @brief      Function that reads data from file
 *
 * @param[in]  _path  The file path
 *
 * @return     File data as char* (string)
 */
char* sReadDataFromFile(const char* _path) {
    FILE* fptr;
    fptr = fopen(_path, "r");
    if (!fptr) {
        fprintf(stderr, "FILE ERROR: Failed to open %s\n", _path);
        return NULL;
    }
    
    fseek(fptr, 0, SEEK_END);
    size_t fSize = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    char* data = NULL;
    data = (char*)malloc(fSize + 1);
    
    fread(data, fSize, 1, fptr);
    fclose(fptr);

    data[fSize] = '\0';
    return data;
}

/**
 * @brief      Functions that checks for shader compilation errors
 *
 * @param[in]  shader  The shader ID
 * @param[in]  type    The shader type
 *
 * @return     void
 */
void sShader_checkCompileErrors(unsigned int shader, const char* type) {
    int success;
    char infoLog[1024];
    if (strcmp(type, "PROGRAM") != 0) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            fprintf(stderr, "OPENGL SHADER ERROR: Shader compilation error of type: %s\n", type);
            if (strlen(infoLog) > 0)
                fprintf(stderr, "%s\n", infoLog);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            fprintf(stderr, "OPENGL SHADER ERROR: Program linking error of type: %s\n", type);
            if (strlen(infoLog) > 0)
                fprintf(stderr, "%s\n", infoLog);
        }
    }
}

/**
 * @brief      Load both shaders and compiles them
 *
 * @param[in]  _vpath  The vertex shader path
 * @param[in]  _fpath  The fragment shader path
 *
 * @return     Pointer to a new sShader variable
 */
struct sShader* sShader_new(const char* _vpath, const char* _fpath) {
    struct sShader* shader = (struct sShader*)malloc(sizeof(struct sShader));

    char* vertexCode = sReadDataFromFile(_vpath);
    char* fragmentCode = sReadDataFromFile(_fpath);

    unsigned int vertex, fragment;
    
    // Vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);
    sShader_checkCompileErrors(vertex, "VERTEX");
    
    // Fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);
    sShader_checkCompileErrors(fragment, "FRAGMENT");
    
    // Shader program
    shader->ID = glCreateProgram();
    glAttachShader(shader->ID, vertex);
    glAttachShader(shader->ID, fragment);
    glLinkProgram(shader->ID);
    sShader_checkCompileErrors(shader->ID, "PROGRAM");
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    free(vertexCode);
    free(fragmentCode);

    return shader;
}

/**
 * @brief      Tells OpenGL to use the given shader
 *
 * @param[in]  shader  The shader
 * @return     void
 */
void sShader_use(const struct sShader* shader) {
    glUseProgram(shader->ID);
}

/**
 * @brief      Creates a new bool uniform (OpenGL Shader Global Variable)
 *
 * @param[in]  shader  The shader
 * @param[in]  name    The uniform name
 * @param[in]  value   The uniform value
 *
 * @return     void
 */
void sShader_setBool(const struct sShader* shader, const char* name, int value) {
    glUniform1i(glGetUniformLocation(shader->ID, name), value);
}

/**
 * @brief      Creates a new int uniform (OpenGL Shader Global Variable)
 *
 * @param[in]  shader  The shader
 * @param[in]  name    The uniform name
 * @param[in]  value   The uniform value
 *
 * @return     void
 */
void sShader_setInt(const struct sShader* shader, const char* name, int value) {
    glUniform1i(glGetUniformLocation(shader->ID, name), value);
}

/**
 * @brief      Creates a new float uniform (OpenGL Shader Global Variable)
 *
 * @param[in]  shader  The shader
 * @param[in]  name    The uniform name
 * @param[in]  value   The uniform value
 *
 * @return     void
 */
void sShader_setFloat(const struct sShader* shader, const char* name, float value) {
    glUniform1f(glGetUniformLocation(shader->ID, name), value);
}

/**
 * @brief      Creates a new vec4 uniform (OpenGL Shader Global Variable)
 *
 * @param[in]  shader  The shader
 * @param[in]  name    The uniform name
 * @param[in]  values  The uniform values
 *
 * @return     void
 */
void sShader_setVec4(const struct sShader* shader, const char* name, float values[4]) {
    glUniform4f(glGetUniformLocation(shader->ID, name), values[0], values[1], values[2], values[3]);
}

/**
 * @brief      Tells OpenGL to remove given shader and deallocate its memory 
 *
 * @param      shader  The shader
 * @return     void
 */
void sShader_destroy(struct sShader* shader) {
    glDeleteProgram(shader->ID);
    free(shader);
}