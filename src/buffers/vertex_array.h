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

    void AddVertexBuffer(void* data, unsigned int size, unsigned int stride);
    void AddIndexBuffer(void* data, int count);

    void Push(unsigned int count);
    int GetIndicies();

    void Bind(bool bind_ibo);
    void Bind() override { this->Bind(false); }
    void Unbind() override;
    void Delete() override;

private:
    VertexBuffer* vbo;
    IndexBuffer* ibo;

    int indicies = 0;
    unsigned int stride = 0;
    unsigned int layout = 0;
    unsigned int layout_offset = 0;
};

}

#endif
