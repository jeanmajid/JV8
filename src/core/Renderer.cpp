#include "Renderer.hpp"

void Renderer::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) {
	shader.bind();
	vertexArray.bind();
	indexBuffer.bind();

	glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::drawArrays(const VertexArray& vertexArray, const Shader& shader, unsigned int count) {
	vertexArray.bind();
	shader.bind();

	glDrawArrays(GL_TRIANGLES, 0, count);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}