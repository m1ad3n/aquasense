#include "renderer/renderer.h"
#include "deps.h"
#include <glm/glm.hpp>

using namespace as;

void Renderer::Clear(float red, float green, float blue, float alpha) {
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GLCall(glClearColor(red, green, blue, alpha));
}

void Renderer::Draw(VertexArray* vao, int indicies_to_draw, Shader* shader)
{
    shader->Bind();
    vao->Bind(true);
    GLCall(glDrawElements(GL_TRIANGLES, indicies_to_draw, GL_UNSIGNED_INT, nullptr));
}
