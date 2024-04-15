#include "renderer/renderer.h"
#include "deps.h"
#include <glm/glm.hpp>

using namespace as;

void Renderer::Clear(float red, float green, float blue, float alpha) {
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GLCall(glClearColor(red, green, blue, alpha));
}

void Renderer::Draw(VertexArray* vao, unsigned int method, Shader* shader, int count)
{
    shader->Bind();
    vao->Bind(true);

    (count == 0) ? count = vao->GetIndicies() : count = count;

    GLCall(glDrawElements(method, count, GL_UNSIGNED_INT, nullptr));
}