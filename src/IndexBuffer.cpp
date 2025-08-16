#include "IndexBuffer.hpp"
#include <glad/glad.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : count(count) {
	glGenBuffers(1, &renderer_Id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_Id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}
IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &renderer_Id);
}

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_Id);
}
void IndexBuffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}