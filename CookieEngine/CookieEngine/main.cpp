#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "IO/AssetManager.h"
#include <cookie/Camera.h>
#include "ECS/World.h"
#include "Rendering/ModelRenderingSystem.h"
namespace ck = cookie;

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
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

	Camera camera {};
	ck::ShaderData shaderData =
		ck::AssetManager::GetShader("vertex_shader.glsl", "fragment_shader.glsl");
	glm::mat4 projection =
		glm::perspective(glm::radians(camera.Zoom), (float)1280 / (float)720, 0.1f, 100.0f);
	shaderData.shader->SetMat4("projection", projection);
	ck::World world(ck::ModelRenderingSystem {});
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 2.5f));
	shaderData.shader->SetMat4("model", model);
	world.EnqueueEntitySpawn(ck::AssetManager::GetModel("backpack.obj", true), shaderData);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.7, 0.7, 0.7, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glm::mat4 view = camera.GetViewMatrix();
		shaderData.shader->SetMat4("view", view);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

