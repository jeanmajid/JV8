#include "Test3D.hpp"
#include <glad/glad.h>
#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../core/Renderer.hpp"

namespace test {
	Test3D::Test3D() : translationA(0, 0, 0), translationB(0, 0, 0) {
		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

        unsigned int indices[] = {
            0, 1, 2,    2, 5, 0,
            6, 7, 8,    8, 11, 6,
            12, 13, 14, 14, 17, 12,
            18, 19, 20, 20, 23, 18,
            24, 25, 26, 26, 29, 24,
            30, 31, 32, 32, 35, 30
        };

		vertexArray = std::make_unique<VertexArray>();
		vertexBuffer = std::make_unique<VertexBuffer>(vertices, 36 * 5 * sizeof(float));

		vertexBufferLayout = std::make_unique<VertexBufferLayout>();
		vertexBufferLayout->push<float>(3);
		vertexBufferLayout->push<float>(2);
		vertexArray->addBuffer(*vertexBuffer, *vertexBufferLayout);

		indexBuffer = std::make_unique<IndexBuffer>(indices, 36);

		shader = std::make_unique<Shader>("C:/Users/jeanh/Documents/GitHub/JV8/res/shaders/basic.shader");
		shader->bind();
		// shader.setUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

		texture = std::make_unique<Texture>("C:/Users/jeanh/Documents/GitHub/JV8/res/textures/test.png");
		texture->bind();
		shader->setUniform1i("u_Texture", 0);
	}

	Test3D::~Test3D() {

	}

	void Test3D::onUpdate(float deltaTime) {
	}

	void Test3D::onRender() {
		glm::mat4 projection = glm::perspective(
			glm::radians(45.0f),       // Field of view (in radians)
			960.0f / 540.0f,           // Aspect ratio
			0.1f,                      // Near plane
			100.0f                     // Far plane
		);
		glm::mat4 view = test::camera.GetViewMatrix();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
			glm::mat4 mvp = projection * view * model;
			shader->setUniformMat4f("u_MVP", mvp);

			Renderer::drawArrays(*vertexArray, *shader, 36);
		}
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
			glm::mat4 mvp = projection * view * model;
			shader->setUniformMat4f("u_MVP", mvp);

			Renderer::drawArrays(*vertexArray, *shader, 36);
		}
	}

	void Test3D::onImGuiRender() {
		ImGui::SliderFloat3("Translation A", &translationA.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("Translation B", &translationB.x, -5.0f, 5.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000 / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}