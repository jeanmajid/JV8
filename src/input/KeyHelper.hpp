#pragma once
#include <GLFW/glfw3.h>

class KeyHelper {
public:
    static bool keys[1024];
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
