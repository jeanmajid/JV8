#pragma once

#include "Test.hpp"

namespace test {

	class TestClearColor : public Test {
	public:
		TestClearColor();
		~TestClearColor();
		
		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	private:
		float color[4];

	};
}