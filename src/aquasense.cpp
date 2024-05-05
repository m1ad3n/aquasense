/**
  * @author Mladen Stanimirovic
  * @file aquasense.c
  * @brief Main C++ source file for this project
  */

#include "deps.h"
#include "macros.h"
#include "aquasense.h"
#include "buffers/buffer.h"
#include "buffers/shader.h"
#include "buffers/texture.h"
#include "renderer/renderer.h"
#include "buffers/vertex_array.h"

/**
 * Window ptr
 */
GLFWwindow* window;

/**
 * Vertex data for the triangle
 */
std::vector<as::Vertex> vertices;
std::vector<unsigned int> indicies;

/**
 * @brief      Error callback function for GLFW
 *
 * @param[in]  error        The error
 * @param[in]  description  The description
 * @return     void
 */
static void error_callback(int error, const char* description)
{
    std::cerr << "GLFW ERROR [" << error << "]: " << description << std::endl;
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
    /* must be set before initializing glfw */
    glfwSetErrorCallback(error_callback);

    /* initialize glfw library */
    if (!glfwInit()) {
        return false;
    }

    /* create glfw window and check for errors */
    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    if (!window) { glfwTerminate(); return false; }

    /* This function makes the OpenGL or OpenGL ES context of the specified window current on the calling thread */
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    /* enable vsync if needed */
    #ifdef VSYNC
	   glfwSwapInterval(1);
    #endif

    return true;
}

/**
 * @brief      deletes all the buffers and then exits the app
 *
 * @param[in]  buffers  The buffers
 */
static void cleanupAndExit(std::vector<as::BufferBase*> buffers) {
    for (auto it : buffers)
        delete it;

    /* cleanup glfw window */
    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "GLFW: Window memory released" << std::endl;

    /* terminates the application */
    std::cout << TITLE << ": Goodbye!" << std::endl;
    exit(0);
}

/**
 * @brief      Appends animation vertices.
 *
 * @param      vertices           The vertices
 * @param      indicies           The indicies
 * @param[in]  iterations         The iterations (how much lines should be added)
 * @param[in]  increasment        The increasment (by how much pixels each line needs to be above the last one)
 * @param[in]  index_to_increase  The index to increase (x or y cordinate)
 */
static void append_animation_vertices(std::vector<as::Vertex>& vertices, std::vector<unsigned int>& indicies, size_t iterations, float increasment, int index_to_increase = 1) {
    for (int y = 0; y < iterations; y++)
    {
        size_t size = vertices.size();
        for (int i = size - 2; i < size; i++)
        {
            as::Vertex tmp = vertices[i];
            tmp.position[index_to_increase] += increasment;
            tmp.color = glm::vec4(0.0f, 0.0f, 0.8f, 0.3f);
            vertices.push_back(tmp);
        }

        /* generate the indicies (SHOULD BE REMOVED) */
        indicies.push_back(size);
        indicies.push_back(size + 1);
    }
}

/**
 * @brief      Appends an animation.
 *
 * @param      vertices     The vertices
 * @param      indicies     The indicies
 * @param[in]  iterations   The iterations (how much circles should be added)
 * @param[in]  increasment  The increasment (by how much pixels each circle need to be above the last one)
 * @param[in]  pos_x        The position x (x cordinate for the center of the circle)
 * @param[in]  pos_y        The position y (y cordinate for the center of the circle)
 * @param[in]  xr           x cordinate radius
 * @param[in]  yr           y cordinate radius
 */
static void append_animation(std::vector<as::Vertex>& vertices, std::vector<unsigned int>& indicies, size_t iterations, float increasment, float pos_x, float pos_y, float xr, float yr) {
    for (int y = 0; y < iterations; y++)
    {
        /**
         * remember the initial count of the vertices and increase the pos_y
         * (every circle will be slightly above than the previous thus creating the animation)
         */
        size_t size = vertices.size();
        pos_y += increasment;

        for (float theta = 0; theta <= 360.0f; theta += 0.1)
        {
            /* angle */
            float angle = theta * M_PI / 180.0;

            /* generate X and Y cordinates for the vertex point */
            float x = pos_x + (xr * cos(angle));
            float y = pos_y + (yr * sin(angle));

            /* different colors for top and bottom side of the circle */
            float color = (theta >= 180) ? 0.6f : 0.8f;

            vertices.push_back(as::Vertex(glm::vec3(x, y, 0.0f), glm::vec4(0.0f, 0.0f, color, color - 0.1f), glm::vec2(0.0f, 0.0f)));
        }

        /* new indicies for the circle */
        for (int i = size; i < vertices.size(); i++)
        {
            indicies.push_back(i);
            indicies.push_back(i + 1);
        }
    }
}

/**
 * @brief      Check if the given time is passed from the last time you called this function
 *
 * @param[in]  time  The time in seconds
 *
 * @return     returns true if certain time is passed
 */
static bool time_passed(float time) {
    /* is set only the first time you call this function */
    static float prev_time;
    if (prev_time == 0.0)
        prev_time = glfwGetTime();

    float current_time = glfwGetTime();
    if (current_time - prev_time >= time)
    {
        prev_time = current_time;
        return true;
    }
    return false;
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
    else std::cout << "AQUASENSE: Window initialized" << std::endl;

    // initializing opengl (glew)
    int glew_error_code = glewInit();
    if (glew_error_code != GLEW_OK) {
        std::cerr << "OPENGL ERROR: glewInit() is not working properly" << std::endl;
    }
    std::cout << "OpenGL Version " << glGetString(GL_VERSION) << std::endl;

    /**
     * Enable all the OpenGL features
     */
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glLineWidth(LINE_WIDTH));

    /**
     * Water tank variables and parameters
     */
    float
        tank_height = 400.0f,
        tank_width = 300.0f,
        tank_pos_x = (WIDTH / 2) - (tank_width / 2),
        tank_pos_y = (HEIGHT / 2) - (tank_height / 2),
        tank_yr = 40.0f,
        tank_xr = (tank_width / 2);

    /**
     * top circle
     */
    for (float theta = 1; theta <= 360.0f; theta += 0.1)
    {

        float angle = theta * M_PI / 180.0;

        float x = (tank_pos_x + tank_xr) + (tank_xr * cos(angle));
        float y = (tank_pos_y + tank_height) + (tank_yr * sin(angle));

        vertices.push_back(as::Vertex(glm::vec3(x, y, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)));
    }

    /**
     * bottom circle
     */
    for (float theta = -1; theta >= -180.0f; theta -= 0.1)
    {

        float angle = theta * M_PI / 180.0;

        float x = (tank_pos_x + tank_xr) + (tank_xr * cos(angle));
        float y = (tank_pos_y) + (tank_yr * sin(angle));

        vertices.push_back(as::Vertex(glm::vec3(x, y, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)));
    }

    /**
     * generate indicies for the circle
     */
    for (int i = 0; i < vertices.size() - 1; i++)
    {
        indicies.push_back(i);
        indicies.push_back(i + 1);
    }

    /**
     * left and right "walls"
     */
    vertices.push_back(as::Vertex(glm::vec3(tank_pos_x, tank_pos_y + tank_height, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)));
    vertices.push_back(as::Vertex(glm::vec3(tank_pos_x + tank_width, tank_pos_y + tank_height, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)));
    vertices.push_back(as::Vertex(glm::vec3(tank_pos_x, tank_pos_y, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)));
    vertices.push_back(as::Vertex(glm::vec3(tank_pos_x + tank_width, tank_pos_y, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)));

    indicies.push_back(vertices.size() - 4); indicies.push_back(vertices.size() - 2);
    indicies.push_back(vertices.size() - 3); indicies.push_back(vertices.size() - 1);

    /**
     * water variables (speed, etc.)
     */
    int start_index = indicies.size();
    int water_level = start_index;
    bool water_rising = true;
    unsigned int water_level_update = 10; // milliseconds

    /**
     * generate circles for the animation purpse
     */
    float increasment = LINE_WIDTH;
    int iterations = (tank_height) / increasment;
    append_animation(vertices, indicies, iterations - 2, increasment, (tank_pos_x + tank_xr), tank_pos_y, (tank_xr - 5.0f), tank_yr - 5.0f);

    /* creating a vertex array and binding the buffers to it */
    as::VertexArray* va_object = new as::VertexArray();
    va_object->AddVertexBuffer(new as::VertexBuffer(vertices));
    va_object->AddIndexBuffer(new as::IndexBuffer(indicies));

    /* vertex attrib pointer layout */
    va_object->Push(3, (void*)offsetof(as::Vertex, position));
    va_object->Push(4, (void*)offsetof(as::Vertex, color));
    va_object->Push(2, (void*)offsetof(as::Vertex, texCoords));

    /* generate a shader object */
    const char* shader_path = "../resources/AShader";
    as::Shader* main_shader = new as::Shader(VERTEX_SHADER_CODE, FRAGMENT_SHADER_CODE);

    /* pushing all the buffers for deletion */
    std::vector<as::BufferBase*> buffers;
    buffers.push_back(va_object);
    buffers.push_back(main_shader);

    /* unbind every buffer and shader */
    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /* projection matrix (x = 0, y = 0 is the bottom left, and x = WIDTH, y = HEIGHT is top right) */
    glm::mat4 projection = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT);

    /* main application loop */
    while (!glfwWindowShouldClose(window))
    {
        /* clears the screen and sets background color (grayish) */
        as::Renderer::Clear(0.8f, 0.8f, 0.8f, 1.0f);

        /* bind the shader and set all the uniforms */
        main_shader->Bind();
        main_shader->SetMat4("u_MVP", glm::value_ptr(projection));

        /* check if the water should be rising or not */
        if (water_level >= indicies.size() && water_rising) water_rising = false;
        else if (water_level <= start_index) water_rising = true;

        /* 7180 is the indicies count for one circle */
        (water_rising) ? water_level += 7180 : water_level -= 7180;

        /* main_shader->SetInt("textureIndex", 0); */
        as::Renderer::Draw(va_object, GL_LINES, main_shader, water_level);

        /* reduce cpu usage */
        std::this_thread::sleep_for (std::chrono::milliseconds(water_level_update));

        /* glfw swap front and back buffers */
        glfwSwapBuffers(window);

        /* glfw check for events (user input etc.) */
        glfwPollEvents();
    }

    // EXIT
    cleanupAndExit(buffers);
}
