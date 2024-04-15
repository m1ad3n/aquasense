/**
 * @author Mladen Stanimirovic
 * @file buffer.h
 *
 * @brief Header file containing all the important buffers
 */

#ifndef AQUASENSE_BUFFERS
#define AQUASENSE_BUFFERS

#include <string>

namespace as
{

class BufferBase {
public:
    BufferBase() : m_type("Unknown") {}
    BufferBase(std::string buffer_type) : m_type(buffer_type) {};
    virtual ~BufferBase();
    virtual void Bind() {};
    virtual void Unbind() {};
    virtual void Delete() {};

protected:
    std::string m_type;
};

class Buffer : public BufferBase {
public:
    unsigned int ID;
    unsigned int TARGET;

    Buffer(unsigned int target, void* data, unsigned int size);
    Buffer(unsigned int target, void* data, unsigned int size, long draw_method);
    ~Buffer() override;

    void Bind() override;
    void Unbind() override;
    void Delete() override;

    void* GetData();
    unsigned int GetSize();

private:
    void* m_data;
    unsigned int m_size;
};

typedef Buffer VertexBuffer;
typedef Buffer IndexBuffer;

}

#endif
