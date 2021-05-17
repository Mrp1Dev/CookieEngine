#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace cookie
{
	class Window
	{
	public:
		int width {};
		int height {};
		GLFWwindow* glfwWindow { nullptr };
	};
}