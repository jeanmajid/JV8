#pragma once
#include <functional>
#include <string>
#include "../graphics/Camera.hpp"

namespace test {
	static Camera camera;

	class Test {
	public:
		Test() {}
		virtual ~Test() {}

		virtual void onUpdate(float deltaTime) {}
		virtual void onRender() {}
		virtual void onImGuiRender() {}
	};

	class TestMenu : public Test {
	public:
		TestMenu(Test*& currentTestPointer);
		~TestMenu();

		void onImGuiRender() override;

		template<typename T>
		void registerTest(const std::string& name);
	private:
		Test*& currentTest;
		std::vector <std::pair<std::string, std::function<Test* ()>>> tests;
	};

	template<typename T>
	inline void TestMenu::registerTest(const std::string& name)
	{
		tests.push_back(std::make_pair(name, []() { return new T(); }));
	}
}