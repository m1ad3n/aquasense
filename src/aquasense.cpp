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
#include "renderer/renderer.h"
#include "buffers/vertex_array.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * Window ptr
 */
GLFWwindow* window;

#define WIDTH  640
#define HEIGHT 480

/**
 * Vertex data for the triangle
 */
float vertecies[] = {
    // CORDS                // TEXTURE CORDS
    -0.5f, 0.0f,  0.5f,     0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,     5.0f, 0.0f,
     0.5f, 0.0f, -0.5f,     0.0f, 0.0f,
     0.5f, 0.0f,  0.5f,     5.0f, 0.0f,
     0.0f, 0.8f,  0.0f,     2.5f, 5.0f
};

unsigned int indicies[] = {
    0,1,2,
    0,2,3,
    0,1,4,
    1,2,4,
    2,3,4,
    3,0,4
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
    va_object->AddIndexBuffer(indicies, 18);

    // vertex pointer layout
    va_object->Push(3);
    va_object->Push(2);

    as::Path shader_path; shader_path << ".." << "resources" << "Square.shader";
    as::Shader *main_shader = new as::Shader(shader_path);

    // first bricks texture (index 0)
    as::Path texture_path; texture_path << ".." << "resources" << "bricks.jpg";
    as::Texture* main_texture = new as::Texture(texture_path, GL_REPEAT);

    // second cat texture (index 1)
    as::Path cat_texture_path; cat_texture_path << ".." << "resources" << "cat.jpg";
    as::Texture* cat_texture = new as::Texture(cat_texture_path, GL_REPEAT);

    // pushing all the buffers for deletion
    std::vector<as::BufferBase*> buffers;
    buffers.push_back(va_object);
    buffers.push_back(main_shader);
    buffers.push_back(main_texture);
    buffers.push_back(cat_texture);

    // unbind everything
    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 result;

    projection = glm::perspective(glm::radians(45.0f), (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);

    float rotation = 0.1f;
    double prev_time = glfwGetTime(), current_time;

    // main application loop
    while (!glfwWindowShouldClose(window))
    {
        as::Renderer::Clear(0.0f, 0.0f, 0.0f, 1.0f);

        //
        // first pyramid
        //

        // math for object rotation
        current_time = glfwGetTime();
        if (current_time - prev_time >= ((float)1 / 60)) {
            prev_time = current_time;
            (rotation >= 360.0f) ? rotation = 0.5 : rotation += 0.5f;
        }
        view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.4f, -3.0f));
        model = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        result = projection * view * model;

        // bind the shader and set all the uniforms
        main_shader->Bind();
        main_shader->SetMat4("u_MVP", glm::value_ptr(result));

        // bind the textures
        main_texture->Bind(0);
        main_shader->SetInt("tex0", 0);

        as::Renderer::Draw(va_object, va_object->GetIndicies(), main_shader);

        //
        // second pyramid
        //
        model = glm::mat4(1.0f);
        view = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, -0.4f, -5.1f));
        result = projection * view * model;

        // shader and matrix values for second pyramid
        main_shader->Bind();
        main_shader->SetMat4("u_MVP", glm::value_ptr(result));

        cat_texture->Bind(1);
        main_shader->SetInt("tex0", 1);

        as::Renderer::Draw(va_object, va_object->GetIndicies(), main_shader);

        // glfw swap front and back buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // EXIT
    cleanupAndExit(buffers);
}
