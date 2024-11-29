#pragma once

#include <GLFW/glfw3.h>

void error_callback(int error, const char* message);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);