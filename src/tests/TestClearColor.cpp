#include "TestClearColor.h"
#include <glad/glad.h>
#include <imgui.h>

namespace test {
	test::TestClearColor::TestClearColor() : color{ 0.2f, 0.3f, 0.8f, 1.0f } {
	}

	test::TestClearColor::~TestClearColor() {
	}

	void test::TestClearColor::onUpdate(float deltaTime) {
	}

	void test::TestClearColor::onRender() {
		glClearColor(color[0], color[1], color[2], color[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void test::TestClearColor::onImGuiRender() {
		ImGui::ColorEdit4("Clear Color", color);
	}
}