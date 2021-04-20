#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "IO/AssetManager.h"
#include <cookie/Camera.h>
#include "ECS/World.h"
#include "Rendering/ModelRenderingSystem.h"
namespace ck = cookie;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 1280 / 2.0f;
float lastY = 720 / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;

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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}
	glViewport(0, 0, 1280, 720);

	
	ck::ShaderData shaderData =
		ck::AssetManager::GetShader("vertex_shader.glsl", "fragment_shader.glsl");
	glm::mat4 projection =
		glm::perspective(glm::radians(camera.Zoom), (float)1280 / (float)720, 0.1f, 100.0f);
	shaderData.shader->SetMat4("projection", projection);
	ck::World world(ck::ModelRenderingSystem {});
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 25.0f));
	shaderData.shader->SetMat4("model", model);
	world.EnqueueEntitySpawn(ck::AssetManager::GetModel("backpack/backpack.obj", true), shaderData);
	world.StartSystems();
	float lastFrame { static_cast<float>(glfwGetTime()) };

	while (!glfwWindowShouldClose(window))
	{
		deltaTime = glfwGetTime() - lastFrame;
		lastFrame = glfwGetTime();
		processInput(window);
		glClearColor(0.1f, 0.2f, 0.2f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glm::mat4 view = camera.GetViewMatrix();
		shaderData.shader->SetMat4("view", view);
		world.UpdateSystems();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

