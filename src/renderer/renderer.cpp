#include "renderer/renderer.h"
#include "deps.h"

using namespace as;

void Renderer::Clear(float red, float green, float blue, float alpha) {
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GLCall(glClearColor(red, green, blue, alpha));
}

void Renderer::Draw(VertexArray* vao, unsigned int method, Shader* shader, int count)
{
    shader->Bind();
    vao->Bind(true);

    if (count == 0 || count > vao->GetIndicies())
        count = vao->GetIndicies();

    GLCall(glDrawElements(method, count, GL_UNSIGNED_INT, nullptr));
}

void Renderer::Quad(VertexArray* vao, Shader* shader_object, Texture* texture_object, const char* texture_uniform, int texture_index)
{
    vao->Bind(true);
    shader_object->Bind();

    if (texture_object)
    {
        texture_object->Bind(texture_index);
        shader_object->SetInt(texture_uniform, texture_index);
    }
    GLCall(glDrawElements(GL_TRIANGLES, vao->GetIndicies(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Quad(VertexArray* vao, int indicies_count, Shader* shader_object, Texture* texture_object, const char* texture_uniform, int texture_index)
{
    shader_object->Bind();
    vao->Bind(true);

    if (texture_object)
    {
        texture_object->Bind(texture_index);
        shader_object->SetInt(texture_uniform, texture_index);
    }
    if (indicies_count == 0 || indicies_count > vao->GetIndicies())
            indicies_count = vao->GetIndicies();

    GLCall(glDrawElements(GL_TRIANGLES, indicies_count, GL_UNSIGNED_INT, nullptr));
}

void Renderer::Background(int width, int height, Shader* shader, Texture* texture)
{
    static std::vector<Vertex> vertecies;
    static std::vector<unsigned int> indicies;
    static VertexArray* vao;

    if (vertecies.size() == 0)
    {
        vertecies.push_back(Vertex(glm::vec3(0.0f, 0.0f, -0.5f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)));
        vertecies.push_back(Vertex(glm::vec3((float)width, 0.0f, -0.5f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)));
        vertecies.push_back(Vertex(glm::vec3((float)width, (float)height, -0.5f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)));
        vertecies.push_back(Vertex(glm::vec3(0.0f, (float)height, -0.5f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)));
    }

    if (indicies.size() == 0)
    {
        indicies.push_back(0);
        indicies.push_back(1);
        indicies.push_back(2);
        indicies.push_back(0);
        indicies.push_back(2);
        indicies.push_back(3);
    }

    if (!vao)
    {
        vao = new VertexArray();
        vao->AddVertexBuffer(new VertexBuffer(vertecies));
        vao->AddIndexBuffer(new IndexBuffer(indicies));

        vao->Push(3, (void*)offsetof(as::Vertex, position));
        vao->Push(4, (void*)offsetof(as::Vertex, color));
        vao->Push(2, (void*)offsetof(as::Vertex, texCoords));
    }

    Renderer::Quad(vao, shader, texture);
}