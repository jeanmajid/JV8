#include "TestTexture2D.hpp"
#include <glad/glad.h>
#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../core/Renderer.hpp"

namespace test {
	TestTexture2D::TestTexture2D() : translationA(200, 200, 0), translationB(400, 200, 0) {
		float positions[] = {
		 -50.0f, -50.0f, 0.0f, 0.0f,
		  50.0f, -50.0f, 1.0f, 0.0f,
		  50.0f, 50.0f, 1.0f, 1.0f,
		 -50.5f, 50.0f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		vertexArray = std::make_unique<VertexArray>();
		vertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

		vertexBufferLayout = std::make_unique<VertexBufferLayout>();
		vertexBufferLayout->push<float>(2);
		vertexBufferLayout->push<float>(2);
		vertexArray->addBuffer(*vertexBuffer, *vertexBufferLayout);

		indexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		shader = std::make_unique<Shader>("C:/Users/jeanh/Documents/GitHub/JV8/res/shaders/basic.shader");
		shader->bind();
		// shader.setUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

		texture = std::make_unique<Texture>("C:/Users/jeanh/Documents/GitHub/JV8/res/textures/test.png");
		texture->bind();
		shader->setUniform1i("u_Texture", 0);
	}

	TestTexture2D::~TestTexture2D() {

	}

	void TestTexture2D::onUpdate(float deltaTime) {
	}

	void TestTexture2D::onRender() {
		glm::mat4 projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
			glm::mat4 mvp = projection * view * model;
			shader->setUniformMat4f("u_MVP", mvp);

			Renderer::draw(*vertexArray, *indexBuffer, *shader);
		}
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
			glm::mat4 mvp = projection * view * model;
			shader->setUniformMat4f("u_MVP", mvp);

			Renderer::draw(*vertexArray, *indexBuffer, *shader);
		}
	}

	void TestTexture2D::onImGuiRender() {
		ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000 / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}