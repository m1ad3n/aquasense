/**
  * @author Mladen Stanimirovic
  * @file aquasense.c
  * @brief Main C source file for this project
  */

#include "deps.h"
#include "macros.h"
#include "shader/shader.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

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
 * Vertex data for the triangle
 */
float positions[12] = {
    -0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
};

/**
 * Triangle color data
 */
float colors[4] = {
    1.0f, 0.0f, 0.0f, 1.0f
};

/**
 * @brief      main function (_start)
 *
 * @param[in]  argc  The count of arguments
 * @param      argv  The arguments array
 *
 * @return     exit status
 */
int main(int argc, char *argv[]) {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(640, 480, "AquaSense", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    // initializing opengl (glew)
    int error_code = glewInit();
    if (error_code != GLEW_OK) {
        fprintf(stderr, "OPENGL ERROR: something wrong with glewInit()\n");
        goto glfw_cleanup_and_exit;
    }

    // details about opengl
    printf("OpenGL Version %s\n", glGetString(GL_VERSION));

    unsigned int vertex_array_id;
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    // generating a vertex buffer and binding it
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // create and compile vertex and fragment shaders
    sShader* sMainShader = sShader_new("./resources/FragmentShader.frag", "./resources/VertexShader.vert");

    // check if all went well
    if (!sMainShader)
        goto glfw_cleanup_and_exit;

    // main application loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);

        sShader_use(sMainShader);
        sShader_setVec4(sMainShader, "color", colors);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(vertex_array_id);

        // glfw stuff
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    sShader_destroy(sMainShader);
    printf("OPENGL: Shader memory released\n");

glfw_cleanup_and_exit:
    // glfw memory cleanup 
    glfwDestroyWindow(window);
    glfwTerminate();

    // message for developers
    printf("GLFW: Window memory successfully released\n");

    // exit status
    return EXIT_SUCCESS;
}
