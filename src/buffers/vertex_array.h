#ifndef AQUASENSE_VERTEX_ARRAY
#define AQUASENSE_VERTEX_ARRAY

#include "buffers/buffer.h"

namespace as
{

class VertexArray : public BufferBase
{
public:
    unsigned int ID;

    VertexArray();
    ~VertexArray() override;

    void AddVertexBuffer(VertexBuffer* vbo);
    void AddIndexBuffer(IndexBuffer* ibo);

    void Push(unsigned int count, void* offset);
    int GetIndicies();

    void Bind(bool bind_ibo);
    void Bind() override { this->Bind(false); }
    void BindVBO() { this->vbo->Bind(); }

    void Unbind() override;
    void Delete() override;

private:
    VertexBuffer* vbo;
    IndexBuffer* ibo;

    unsigned int layout = 0;
};

}

#endif
