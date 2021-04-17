#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>



void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void i(int*& ptr)
{
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(1280, 720, "window 1", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW Window.\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}
	glViewport(0, 0, 1280, 720);

	
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.7, 0.7, 0.7, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);






		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

