#include "TestClearColor.hpp"
#include <glad/glad.h>
#include <imgui.h>

namespace test {
	TestClearColor::TestClearColor() : color{ 0.2f, 0.3f, 0.8f, 1.0f } {
	}

	TestClearColor::~TestClearColor() {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void TestClearColor::onUpdate(double deltaTime) {
	}

	void TestClearColor::onRender() {
		glClearColor(color[0], color[1], color[2], color[3]);
	}

	void TestClearColor::onImGuiRender() {
		ImGui::ColorEdit4("Clear Color", color);
	}
}