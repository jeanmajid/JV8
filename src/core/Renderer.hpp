#pragma once
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

class Renderer {
public:
	static void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader);
	static void clear();
};