#include "deps.h"
#include "macros.h"
#include <GLFW/glfw3.h>

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW ERROR: %s\n", description);
}

int main(int argc, char *argv[]) {

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(640, 480, "Basic OpenGL Window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // application loop (prevents window from closing)
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw memory cleanup 
    glfwDestroyWindow(window);
    glfwTerminate();

    // 0
    return EXIT_SUCCESS;
}
