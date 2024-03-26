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

#ifdef _WIN32
#   define FRAGMENT_SHADER 	"..\\resources\\FragmentShader.frag"
#   define VERTEX_SHADER	"..\\resources\\VertexShader.vert"
#else
#   define FRAGMENT_SHADER	"../resources/FragmentShader.frag"
#   define VERTEX_SHADER	"../resources/VertexShader.vert"
#endif

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

unsigned int indicies[6] = {
    1, 2, 3,
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
 * @return     void
 */
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW ERROR [%d]: %s\n", error, description);
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
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    else if (key == GLFW_KEY_ENTER && action == GLFW_REPEAT)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

/**
 * @brief      Initialize GLFW window
 * @return     status
 */
static bool asInitGlfw(unsigned short _width, unsigned short _height) {
    if (!glfwInit()) return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(_width, _height, "AquaSense", NULL, NULL);
    if (!window) { glfwTerminate(); return false; }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetErrorCallback(error_callback);

    return true;
}

/**
 * @brief      Deallocates all used memory and exits the application
 *
 * @param      buffersVec  The buffers vector
 * @param      shadersVec  The shaders vector
 * @return     void
 */
static void cleanupAndExit(cvec* buffersVec, cvec* shadersVec) {
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
    
    if (!asInitGlfw(640, 480)) return -1;
    else fprintf(stdout, "AQUASENSE: Window initialized\n");

    // initializing opengl (glew)
    int glew_error_code = glewInit();
    if (glew_error_code != GLEW_OK) {
        fprintf(stderr, "OPENGL ERROR: glewInit() is not working properly\n");
        cleanupAndExit(NULL, NULL);
    }

    // details about opengl
    printf("OpenGL Version %s\n", glGetString(GL_VERSION));

    // vertex array object
    unsigned int vao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    // creating a vertex buffer
    VertexBuffer* vbo = sBuffer_new(GL_ARRAY_BUFFER, vertecies, sizeof(vertecies));
    if (!vbo) cleanupAndExit(NULL, NULL);

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL));

    IndexBuffer* ibo = sIndexBuffer_new(indicies, 6);
    if (!ibo) { cleanupAndExit(cvec_from(1, vbo), NULL); }

    // create and compile vertex and fragment shaders
    ASShader* sMainShader = sShader_new(VERTEX_SHADER, FRAGMENT_SHADER);
    if (!sMainShader) cleanupAndExit(cvec_from(2, vbo, ibo), NULL);

    // unbind everything
    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // main application loop
    while (!glfwWindowShouldClose(window)) {
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        GLCall(glClearColor(0.0, 0.0, 0.0, 1.0));

        sShader_use(sMainShader);
        sShader_setVec4(sMainShader, "ell_color", colors);

        // now we need to bind only the vertex array object
        glBindVertexArray(vao);
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));

        // glfw swap front and back buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // EXIT
    cleanupAndExit(cvec_from(2, vbo, ibo), cvec_from(1, sMainShader));
}
