#include "deps.h"
#include "macros.h"

int main(int argc, char *argv[]) {

    if (!glfwInit()) {
        GLFW_ERROR("Failed to initialize glfw");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Basic OpenGL Window", NULL, NULL);
    if (!window) {
        GLFW_ERROR("Failed to create a window");
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
