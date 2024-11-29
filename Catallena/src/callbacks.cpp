#include "callbacks.h"
#include <iostream>

void error_callback(int error, const char* message)
{
	std::cout << "GLFW error " << error << ": " << message << "\n";
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	const char* key_name = glfwGetKeyName(key, scancode);
	if (!key_name)
	{
		key_name = "unknown key";
	}
	switch (action)
	{
	case GLFW_PRESS:
		std::cout << key_name << " was pressed\n";
		break;
	case GLFW_RELEASE:
		std::cout << key_name << " was released\n";
		break;
	case GLFW_REPEAT:
		std::cout << key_name << " was repeated\n";
		break;
	}
}