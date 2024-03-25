/**
  * @author Mladen Stanimirovic
  * @file aquasense.c
  * @brief Main C source file for this project
  */

#include "deps.h"
#include "macros.h"
#include "shader/shader.h"
#include "buffer/buffer.h"
#include "cvec/cvec.h"
#include <stdio.h>

/**
 * Window ptr
 */
GLFWwindow* window;

/**
 * Vertex data for the triangle
 */
float vertecies[8] = {
    -0.5f, -0.5f, // 0
     0.5f, -0.5f, // 1
     0.5f,  0.5f, // 2
    -0.5f,  0.5f, // 3
};

unsigned int indicies[3] = {
    2, 3, 0
};

/**
 * Triangle color data
 */
float colors[4] = {
    1.0f, 0.0f, 1.0f, 1.0f
};

/**
 * @brief      Error callback function for GLFW
 *
 * @param[in]  error        The error
 * @param[in]  description  The description
 */
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW ERROR: %s\n", description);
}

/**
 * @brief      keyboard handler for glfw 
 *
 * @param      window    The window
 * @param[in]  key       The key
 * @param[in]  scancode  The scancode
 * @param[in]  action    The action
 * @param[in]  mods      The mods
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    else if (key == GLFW_KEY_ENTER && action == GLFW_REPEAT)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

/**
 * @brief      Initialize GLFW window
 */
static bool asInitGlfw() {
    if (!glfwInit()) return false;

    window = glfwCreateWindow(640, 480, "AquaSense", NULL, NULL);
    if (!window) { glfwTerminate(); return false; }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetErrorCallback(error_callback);

    return true;
}

static void cleanupAndExit(cvec* buffersVec, cvec* shadersVec) {
    int id;

    // buffers cleanup
    if (buffersVec) {
        for (int i = 0; i < cvec_size(buffersVec); i++)
            sBuffer_destroy((ASBuffer*)cvec_at(buffersVec, i));
        fprintf(stdout, "OPENGL BUFFERS: Memory released\n");
    }

    // shaders cleanup
    if (shadersVec) {
        for (int i = 0; i < cvec_size(shadersVec); i++)
            sShader_destroy((ASShader*)cvec_at(shadersVec, i));
        fprintf(stdout, "OPENGL SHADERS: Memory released\n");
    }

    // cleanup glfw window
    glfwDestroyWindow(window);
    glfwTerminate();
    fprintf(stdout, "GLFW: Memory released\n");

    // free the memory
    cvec_free(buffersVec);
    cvec_free(shadersVec);

    // terminates the application
    fprintf(stdout, "AQUASENSE: Goodbye!\n");
    exit(0);
}

/**
 * @brief      main function (_start)
 *
 * @param[in]  argc  The count of arguments
 * @param      argv  The arguments array
 *
 * @return     exit status
 */
int main(int argc, char *argv[]) {
    
    if (!asInitGlfw()) return -1;
    else fprintf(stdout, "AQUASENSE: Window initialized\n");

    // initializing opengl (glew)
    int glew_error_code = glewInit();
    if (glew_error_code != GLEW_OK) {
        fprintf(stderr, "OPENGL ERROR: glewInit() is not working properly\n");
        cleanupAndExit(NULL, NULL);
    }

    // details about opengl
    printf("OpenGL Version %s\n", glGetString(GL_VERSION));

    // creating a vertex buffer
    VertexBuffer* vbo = sBuffer_new(GL_ARRAY_BUFFER, vertecies, sizeof(vertecies));
    if (!vbo) cleanupAndExit(NULL, NULL);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    IndexBuffer* ibo = sBuffer_new(GL_ELEMENT_ARRAY_BUFFER, indicies, sizeof(indicies));
    if (!ibo) { cleanupAndExit(cvec_from(1, vbo), NULL); }

    // create and compile vertex and fragment shaders
    ASShader* sMainShader = sShader_new("../resources/VertexShader.vert", "../resources/FragmentShader.frag");
    if (!sMainShader) cleanupAndExit(cvec_from(2, vbo, ibo), NULL);

    // main application loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);

        sShader_use(sMainShader);
        sShader_setVec4(sMainShader, "ell_color", colors);

        GLClearErrors();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
        GLCheckError();

        // glfw swap front and back buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // EXIT
    cleanupAndExit(cvec_from(2, vbo, ibo), cvec_from(1, sMainShader));
}
