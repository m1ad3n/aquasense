/**
  * @author Mladen Stanimirovic
  * @file aquasense.c
  * @brief Main C source file for this project
  */

#include "deps.h"
#include "macros.h"
#include "buffers/buffer.h"
#include "buffers/shader.h"
#include "buffers/texture.h"
#include "string_functions.h"
/**
 * Window ptr
 */
GLFWwindow* window;

#define WIDTH  640
#define HEIGHT 480

/**
 * Vertex data for the triangle
 */
float square_vertecies[20] = {
    // CORDS                // TEXTURE CORDS
    -0.5f,  -0.5f, 1.0f,     0.0f, 0.0f,       // 0
    0.5f, -0.5f, 1.0f,     1.0f, 0.0f,       // 1
    0.5f,  0.5f, 1.0f,     1.0f, 1.0f,       // 2
    -0.5f,  0.5f, 1.0f,     0.0f, 1.0f        // 3
};

unsigned int square_indicies[6] = {
    0, 1, 2,
    0, 3, 2
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
static bool asInitGlfw() {
    if (!glfwInit()) return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "AquaSense", NULL, NULL);
    if (!window) { glfwTerminate(); return false; }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetErrorCallback(error_callback);
	glfwSwapInterval(1);

    return true;
}

static void cleanupAndExit(std::vector<BufferBase*> buffers) {
    for (auto it : buffers)
        it->Delete();

    // cleanup glfw window
    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "GLFW: Window memory released" << std::endl;

    // terminates the application
    std::cout << "AQUASENSE: Goodbye!" << std::endl;
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
    }
    printf("OpenGL Version %s\n", glGetString(GL_VERSION));

    GLCall(glEnable(GL_BLEND));

    std::vector<BufferBase*> buffers;

    // vertex array object
    unsigned int square_vao;
    GLCall(glGenVertexArrays(1, &square_vao));
    GLCall(glBindVertexArray(square_vao));

    // creating a vertex buffer
    VertexBuffer square_vbo(GL_ARRAY_BUFFER, square_vertecies, sizeof(square_vertecies));
    buffers.push_back(&square_vbo);

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0));
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));

    IndexBuffer square_ibo(GL_ELEMENT_ARRAY_BUFFER, square_indicies, 6 * sizeof(unsigned int));
    buffers.push_back(&square_ibo);

    Path shader_path; shader_path >> ".." >> "resources" >> "Square.shader";
    Shader sSquareShader(shader_path);
    buffers.push_back(&sSquareShader);

    Path texture_path; texture_path >> ".." >> "resources" >> "cat.jpg";
    Texture square_texture(texture_path, GL_CLAMP_TO_EDGE);
    buffers.push_back(&square_texture);

    square_texture.Bind(1);
    sSquareShader.SetInt("tex0", 1);
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));

    // unbind everything
    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // main application loop
    while (!glfwWindowShouldClose(window)) {
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        GLCall(glClearColor(0.0, 0.0, 0.0, 1.0));

        // bind the shader and set all the uniforms
        sSquareShader.Bind();

        // bind the textures
        square_texture.Bind();

        // now we need to bind only the vertex array object
        GLCall(glBindVertexArray(square_vao));
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));

        // glfw swap front and back buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // EXIT
    cleanupAndExit(buffers);
}
