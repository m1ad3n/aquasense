/**
  * @author Mladen Stanimirovic
  * @file aquasense.c
  * @brief Main C source file for this project
  */

#include "deps.h"
#include "macros.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>

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
 * Vertex data for the triangle
 */
float positions[6] = {
    -0.5f, -0.5f,
     0.0f,  0.5f,
     0.5f, -0.5f
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

    // initializing opengl (glew)
    int error_code = glewInit();
    if (error_code != GLEW_OK) {
        fprintf(stderr, "OPENGL ERROR: something wrong with glewInit()\n");
        goto glfw_cleanup_and_exit;
    }

    // details about opengl
    printf("OpenGL Version %s\n", glGetString(GL_VERSION));

    // generating a vertex buffer and binding it
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), NULL);

    // main application loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);

        glColor3f(0.0, 0.0, 1.0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw stuff
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

glfw_cleanup_and_exit:
    // glfw memory cleanup 
    glfwDestroyWindow(window);
    glfwTerminate();

    // message for developers
    printf("GLFW: Memory successfully released\n");

    // exit status
    return EXIT_SUCCESS;
}
