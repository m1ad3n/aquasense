/**
 * @author Mladen Stanimirovic
 * @file buffer.h
 *
 * @brief Header file containing all the important buffers
 */

#ifndef AQUASENSE_BUFFERS
#define AQUASENSE_BUFFERS

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace as
{

typedef struct Vertex {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texCoords;

    Vertex(glm::vec3 __pos, glm::vec4 __color, glm::vec2 __texCoords) : position(__pos), color(__color), texCoords(__texCoords) {
    }
} Vertex;

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

class VertexBuffer : public BufferBase {
public:

    VertexBuffer(std::vector<Vertex>& data);
    VertexBuffer(std::vector<Vertex>& data, long draw_method);
    ~VertexBuffer() override;

    void Bind() override;
    void Unbind() override;
    void Delete() override;

private:
    unsigned int ID;
    float* vertices;
};

class IndexBuffer : public BufferBase {
public:
    
    IndexBuffer(std::vector<unsigned int>& data);
    IndexBuffer(std::vector<unsigned int>& data, long draw_method);
    ~IndexBuffer() override;

    void Bind() override;
    void Unbind() override;
    void Delete() override;

    int GetIndicies();

private:
    unsigned int ID;
    int indicies;
};

}

#endif
