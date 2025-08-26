#pragma once

#include "Test.hpp"

#include "../core/VertexBuffer.hpp"
#include "../core/VertexArray.hpp"
#include "../core/VertexBufferLayout.hpp"
#include "../core/Texture.hpp"
#include "../core/IndexBuffer.hpp"
#include "../core/Shader.hpp"
#include "../graphics/Camera.hpp"

#include <memory>

namespace test {

	class Test3D : public Test {
	public:
		Test3D();
		~Test3D();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	private:
		std::unique_ptr <VertexArray> vertexArray;
		std::unique_ptr <VertexBuffer> vertexBuffer;
		std::unique_ptr <VertexBufferLayout> vertexBufferLayout;
		std::unique_ptr <IndexBuffer> indexBuffer;
		std::unique_ptr <Shader> shader;
		std::unique_ptr <Texture> texture;
		glm::vec3 translationA, translationB;
	};
}