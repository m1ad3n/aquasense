#include "buffers/vertex_array.h"
#include "buffers/buffer.h"
#include "deps.h"

using namespace as;

VertexArray::VertexArray() : BufferBase("Vertex Array") {
    GLCall(glGenVertexArrays(1, &this->ID));
    GLCall(glBindVertexArray(this->ID));
    this->layout = 0;
}

void VertexArray::AddVertexBuffer(VertexBuffer* vbo) {
    this->Bind();
    this->vbo = vbo;
    this->Unbind();
}

void VertexArray::AddIndexBuffer(IndexBuffer* ibo) {
    this->Bind();
    this->ibo = ibo;
    this->Unbind();
}

void VertexArray::Push(unsigned int count, void* offset) {
    this->Bind();
    this->vbo->Bind();

    GLCall(glEnableVertexAttribArray(this->layout));
    GLCall(glVertexAttribPointer(this->layout, count, GL_FLOAT, GL_FALSE, sizeof(Vertex), offset));

    this->layout++;
    this->Unbind();
}

VertexArray::~VertexArray() {
    this->Delete();
    if (vbo) delete vbo;
    if (ibo) delete ibo;
}

void VertexArray::Delete() {
    GLCall(glDeleteVertexArrays(1, &this->ID));
}

void VertexArray::Bind(bool bind_ibo) {
    GLCall(glBindVertexArray(this->ID));
    if (bind_ibo) this->ibo->Bind();
}

void VertexArray::Unbind() {
    GLCall(glBindVertexArray(0));
}

int VertexArray::GetIndicies() {
    return this->ibo->GetIndicies();
}
