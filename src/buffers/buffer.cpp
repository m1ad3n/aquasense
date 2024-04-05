#include "buffer.h"
#include "../deps.h"

Buffer::Buffer(unsigned int target, void* data, unsigned int size) {	
	this->TARGET = target;
	glGenBuffers(1, &this->ID);
    glBindBuffer(this->TARGET, this->ID);
    glBufferData(this->TARGET, size, data, GL_STATIC_DRAW);
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