/**
 * @author Mladen Stanimirovic
 * @file buffer.h
 *
 * @brief Header file containing all the important buffers
 */

#ifndef AQUASENSE_BUFFERS
#define AQUASENSE_BUFFERS

class BufferBase {
public:
    virtual ~BufferBase() {};
    virtual void Bind() {};
    virtual void Unbind() {};
    virtual void Delete() {};
};

class Buffer : public BufferBase {
public:
    unsigned int ID;
    unsigned int TARGET;

    Buffer(unsigned int target, void* data, unsigned int size);
    ~Buffer() override {};

    void Bind() override;
    void Unbind() override;
    void Delete() override;
};

typedef Buffer VertexBuffer;
typedef Buffer IndexBuffer;

#endif