#include "VertexBuffer.hpp"
#include <glad/glad.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	glGenBuffers(1, &renderer_Id);
	glBindBuffer(GL_ARRAY_BUFFER, renderer_Id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &renderer_Id);
}

void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, renderer_Id);
}
void VertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}