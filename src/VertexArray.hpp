#pragma once
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray {
private:
	unsigned int rendererId;
public:

	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout layout);

	void bind() const;
	void unbind() const;
};