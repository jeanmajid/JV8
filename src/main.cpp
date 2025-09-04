#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>

#include "./debug/callback.hpp"
#include "core/Renderer.hpp"
#include "core/VertexBuffer.hpp"
#include "core/IndexBuffer.hpp"
#include "core/VertexArray.hpp"
#include "core/Shader.hpp"
#include "core/Texture.hpp"
#include "input/KeyHelper.hpp"
#include "graphics/Camera.hpp"

#include "tests/TestClearColor.hpp"
#include "tests/TestTexture2D.hpp"
#include "tests/Test3D.hpp"
#include "tests/Test.hpp"

int main(void) {
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

#if _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mods) {
		KeyHelper::keyCallback(w, key, scancode, action, mods);
		});

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD\n";
		return -1;
	}

#if _DEBUG
	if (glDebugMessageCallback) {
		std::cout << "Register OpenGL debug callback " << std::endl;
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(openglCallbackFunction, nullptr);
		GLuint unusedIds = 0;
		glDebugMessageControl(GL_DONT_CARE,
			GL_DONT_CARE,
			GL_DONT_CARE,
			0,
			&unusedIds,
			true);
	}
	else
		std::cout << "glDebugMessageCallback not available" << std::endl;
#endif

	std::cout << glGetString(GL_VERSION) << std::endl;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Imgui setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	// Test setup
	test::Test* currentTest = nullptr;
	test::TestMenu* testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;

	testMenu->registerTest<test::TestClearColor>("Clear Color");
	testMenu->registerTest<test::TestTexture2D>("Texture 2D");
	testMenu->registerTest<test::Test3D>("Test 3D");

	const double targetFrameTime = 1.0f / 60.0f;
	double nextFrameTime = glfwGetTime();

	double lastFrame = nextFrameTime;
	double deltaTime = 0.0f;

	int frames = 0;
	double lastFPSTime = nextFrameTime;
	double fps = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();

		if (currentTime < nextFrameTime) {
			double sleepTime = nextFrameTime - currentTime;
			std::this_thread::sleep_for(std::chrono::microseconds((int)(sleepTime * 1e6)));
			continue;
		}
		nextFrameTime += targetFrameTime;

		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		frames++;
		if (currentTime - lastFPSTime >= 1.0f) {
			fps = frames / (currentTime - lastFPSTime);
			frames = 0;
			lastFPSTime = currentTime;
			glfwSetWindowTitle(window, std::to_string(fps).c_str());
		}

		Renderer::clear();

		Camera::processMovement(deltaTime);

		currentTest->onUpdate(deltaTime);
		currentTest->onRender();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (currentTest != testMenu && ImGui::Button("Back")) {
			delete currentTest;
			currentTest = testMenu;
		}
		currentTest->onImGuiRender();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	if (currentTest != testMenu) {
		delete testMenu;
	}
	delete currentTest;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}
