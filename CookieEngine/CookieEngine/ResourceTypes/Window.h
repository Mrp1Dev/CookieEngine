#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace cookie
{
	class Window
	{
	public:
		i32 width {};
		i32 height {};
		GLFWwindow* glfwWindow { nullptr };
	};
}