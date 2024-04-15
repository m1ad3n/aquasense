/**
  * @author Mladen Stanimirovic
  * @file aquasense.c
  * @brief Main C++ source file for this project
  */

#include "deps.h"
#include "macros.h"
#include "buffers/buffer.h"
#include "buffers/shader.h"
#include "buffers/texture.h"
#include "renderer/renderer.h"
#include "buffers/vertex_array.h"

/**
 * Window ptr
 */
GLFWwindow* window;

#define WIDTH  700
#define HEIGHT 700

int texture_pos = 0;

/**
 * Vertex data for the triangle
 */
float vertecies[] = {
    // VERTEX POINTS                            // TEXTURE CORDINATES
            0.0f,           0.0f, 0.0f,         0.0f, 0.0f,
    (float)WIDTH,           0.0f, 0.0f,         1.0f, 0.0f,
    (float)WIDTH,  (float)HEIGHT, 0.0f,         1.0f, 1.0f,
            0.0f,  (float)HEIGHT, 0.0f,         0.0f, 1.0f
};

unsigned int indicies[] = {
    0, 1, 2,
    0, 2, 3
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
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        (texture_pos > 0) ? texture_pos-- : texture_pos = texture_pos;
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        (texture_pos < 2 - 1) ? texture_pos++ : texture_pos = texture_pos;
}
/**
 * @brief      Initialize GLFW window
 * @return     status
 */
static bool asInitGlfw() {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "AquaSense", NULL, NULL);
    if (!window) { glfwTerminate(); return false; }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
	glfwSwapInterval(1);

    return true;
}

static void cleanupAndExit(std::vector<as::BufferBase*> buffers) {
    for (auto it : buffers)
        delete it;

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
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_DEPTH_TEST));

    // creating a vertex array and binding the buffers to it
    as::VertexArray* va_object = new as::VertexArray();
    va_object->AddVertexBuffer(vertecies, sizeof(vertecies), 5);
    va_object->AddIndexBuffer(indicies, 6);

    // vertex pointer layout
    va_object->Push(3);
    va_object->Push(2);

    const char* shader_path = "../resources/AShader";
    as::Shader *main_shader = new as::Shader(shader_path);

    // first bricks texture (index 0)
    const char* full_tanks_texture_path = "../resources/full.jpeg";
    as::Texture* full_tanks_texture = new as::Texture(full_tanks_texture_path, GL_REPEAT);

    const char* empty_tanks_texture_path = "../resources/empty.jpeg";
    as::Texture* empty_tanks_texture = new as::Texture(empty_tanks_texture_path, GL_REPEAT);

    // pushing all the buffers for deletion
    std::vector<as::BufferBase*> buffers;
    buffers.push_back(va_object);
    buffers.push_back(main_shader);
    buffers.push_back(empty_tanks_texture);
    buffers.push_back(full_tanks_texture);

    // unbind everything
    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glm::mat4 projection = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT);
    double prev_time = glfwGetTime();

    // main application loop
    while (!glfwWindowShouldClose(window))
    {
        as::Renderer::Clear(1.0f, 1.0f, 1.0f, 1.0f);

        // bind the shader and set all the uniforms
        main_shader->Bind();
        main_shader->SetMat4("u_MVP", glm::value_ptr(projection));

        // bind the textures
        full_tanks_texture->Bind(0);
        empty_tanks_texture->Bind(1);

        // double current_time = glfwGetTime();
        // if (current_time - prev_time >= (double)2) {
        //     prev_time = current_time;
        //     (texture_pos == 0) ? texture_pos++ : texture_pos--;
        // }

        main_shader->SetInt("tex0", texture_pos);
        as::Renderer::Draw(va_object, GL_TRIANGLES, main_shader);

        // glfw swap front and back buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // EXIT
    cleanupAndExit(buffers);
}
