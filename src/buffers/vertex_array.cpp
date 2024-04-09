#include "buffers/vertex_array.h"
#include "buffers/buffer.h"
#include "deps.h"

using namespace as;

VertexArray::VertexArray() : BufferBase("Vertex Array") {
    GLCall(glGenVertexArrays(1, &this->ID));
    GLCall(glBindVertexArray(this->ID));
    this->Unbind();
    this->layout_offset = 0;
    this->layout = 0;
}

void VertexArray::AddVertexBuffer(void* data, unsigned int size, unsigned int stride) {
    this->Bind();
    this->vbo = new VertexBuffer(GL_ARRAY_BUFFER, data, size);
    this->stride = (stride * sizeof(float));
    this->Unbind();
}

void VertexArray::AddIndexBuffer(void* data, int count) {
    this->Bind();
    this->ibo = new IndexBuffer(GL_ELEMENT_ARRAY_BUFFER, data, count * sizeof(unsigned int));
    this->indicies = count;
    this->Unbind();
}

void VertexArray::Push(unsigned int count) {
    this->Bind(true);
    this->vbo->Bind();

    GLCall(glEnableVertexAttribArray(this->layout));
    GLCall(glVertexAttribPointer(this->layout, count, GL_FLOAT, GL_FALSE, this->stride, (void*)(this->layout_offset * sizeof(float))));

    this->layout_offset += count;
    this->layout++;
    this->Unbind();
}

VertexArray::~VertexArray() {
    this->Delete();
    delete vbo;
    delete ibo;
}

void VertexArray::Delete() {
    glDeleteVertexArrays(1, &this->ID);
}

void VertexArray::Bind(bool bind_ibo) {
    glBindVertexArray(this->ID);
    if (bind_ibo) this->ibo->Bind();
}

void VertexArray::Unbind() {
    GLCall(glBindVertexArray(0));
}

int VertexArray::GetIndicies() {
    return this->indicies;
}
