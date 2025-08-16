#include "VertexArray.hpp"
#include <glad/glad.h>

VertexArray::VertexArray() {
	glGenVertexArrays(1, &rendererId);
	glBindVertexArray(rendererId);
}
VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &rendererId);
}

void VertexArray::addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout layout) {
	vertexBuffer.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.getStride(), reinterpret_cast<const void*>(static_cast<uintptr_t>(offset)));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::bind() const {
	glBindVertexArray(rendererId);
}
void VertexArray::unbind() const {
	glBindVertexArray(0);
}