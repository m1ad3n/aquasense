#include "buffer.h"
#include "deps.h"

using namespace as;

VertexBuffer::VertexBuffer(std::vector<Vertex>& data) : BufferBase("Vertex") {
	GLCall(glGenBuffers(1, &this->ID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->ID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), data.data(), GL_STATIC_DRAW));
	this->Unbind();
}

VertexBuffer::VertexBuffer(std::vector<Vertex>& data, long draw_method) : BufferBase("Vertex") {
	GLCall(glGenBuffers(1, &this->ID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->ID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), data.data(), draw_method));
	this->Unbind();
}

BufferBase::~BufferBase()
{
	std::cout << m_type <<  " buffer [" << std::hex << this << "] destroyed" << std::endl;
}

VertexBuffer::~VertexBuffer() {
	this->Delete();
}

void VertexBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void VertexBuffer::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Delete() {
	glDeleteBuffers(1, &this->ID);
}


IndexBuffer::IndexBuffer(std::vector<unsigned int>& data) : BufferBase("Index") {
	GLCall(glGenBuffers(1, &this->ID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), GL_STATIC_DRAW));
	this->Unbind();
	this->indicies = data.size();
}

IndexBuffer::IndexBuffer(std::vector<unsigned int>& data, long draw_method) : BufferBase("Index") {
	GLCall(glGenBuffers(1, &this->ID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), draw_method));
	this->Unbind();
	this->indicies = data.size();
}

IndexBuffer::~IndexBuffer() {
	this->Delete();
}

void IndexBuffer::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
}

void IndexBuffer::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::Delete() {
	glDeleteBuffers(1, &this->ID);
}

int IndexBuffer::GetIndicies() {
	return this->indicies;
}