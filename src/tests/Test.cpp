#include "Test.hpp"
#include <imgui.h>

namespace test {
	TestMenu::TestMenu(Test*& currentTestPointer) : currentTest(currentTestPointer) {
	}
	TestMenu::~TestMenu() {
	}
	void TestMenu::onImGuiRender() {
		for (auto& test : tests) {
			if (ImGui::Button(test.first.c_str())) {
				currentTest = test.second();
			}
		}
	}
}