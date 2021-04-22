#include "Cookie.h"

Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
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
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Cookie", nullptr, nullptr);
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}
	glViewport(0, 0, 1280, 720);
	glEnable(GL_DEPTH_TEST);

	ck::ShaderData shaderData =
		ck::AssetManager::GetShader("vertex_shader.glsl", "fragment_shader.glsl");
	ck::World world(
		ck::SetModelMatricesSystem {},
		ck::SetPerspectiveMatrixSystem {},
		ck::ModelRenderingSystem {}
	);

	//InitGame(&world);
	world.EnqueueEntitySpawn(
		ck::AssetManager::GetModel("backpack/backpack.obj", true),
		ck::AssetManager::GetShader("vertex_shader.glsl", "fragment_shader.glsl"),
		ck::TransformData {
			glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::fquat(glm::vec3(0, 0, 0))
		}
	);
	world.EnqueueEntitySpawn(
		ck::AssetManager::GetModel("backpack/backpack.obj", true),
		ck::AssetManager::GetShader("vertex_shader.glsl", "fragment_shader.glsl"),
		ck::TransformData {
			glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f), glm::fquat(glm::vec3(0, 45, 0))
		}
	);
	world.EnqueueEntitySpawn(
		ck::AssetManager::GetModel("backpack/backpack.obj", true),
		ck::AssetManager::GetShader("vertex_shader.glsl", "fragment_shader.glsl"),
		ck::TransformData {
			glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f), glm::fquat(glm::vec3(0, 90, 0))
		}
	);

	world.EnqueueEntitySpawn(ck::CameraData { 60.0f, true });
	world.StartSystems();
	float lastFrame { static_cast<float>(glfwGetTime()) };

	while (!glfwWindowShouldClose(window))
	{
		deltaTime = glfwGetTime() - lastFrame;
		lastFrame = glfwGetTime();

		processInput(window);

		glClearColor(0.1f, 0.2f, 0.2f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 view = camera.GetViewMatrix();
		shaderData.shader->SetMat4("view", view);
		world.UpdateSystems();
		std::cout << camera.Position.x << ' ' << camera.Position.y << ' ' << camera.Position.z << '\n';

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