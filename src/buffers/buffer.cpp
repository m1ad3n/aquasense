#include "buffers/buffer.h"
#include "deps.h"

using namespace as;

Buffer::Buffer(unsigned int target, void* data, unsigned int size) : BufferBase((target == GL_ARRAY_BUFFER) ? "Vertex" : "Index") {
	this->TARGET = target;
	this->m_data = data;
	this->m_size = size;
	glGenBuffers(1, &this->ID);
    glBindBuffer(this->TARGET, this->ID);
    glBufferData(this->TARGET, size, data, GL_STATIC_DRAW);
	this->Unbind();
}

Buffer::Buffer(unsigned int target, void* data, unsigned int size, long draw_method) {
	this->TARGET = target;
	this->m_data = data;
	this->m_size = size;
	glGenBuffers(1, &this->ID);
    glBindBuffer(this->TARGET, this->ID);
    glBufferData(this->TARGET, size, data, draw_method);
	this->Unbind();
}

BufferBase::~BufferBase()
{
	std::cout << m_type <<  " buffer [" << std::hex << this << "] destroyed" << std::endl;
}

Buffer::~Buffer() {
	this->Delete();
}

void* Buffer::GetData() {
	return this->m_data;
}

unsigned int Buffer::GetSize() {
	return this->m_size;
}

void Buffer::Bind() {
	glBindBuffer(this->TARGET, this->ID);
}

void Buffer::Unbind() {
	glBindBuffer(this->TARGET, 0);
}

void Buffer::Delete() {
	glDeleteBuffers(1, &this->ID);
}
