#include "Cookie.h"


int main()
{
	constexpr int BASE_WIDTH = 1280;
	constexpr int BASE_HEIGHT = 720;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(BASE_WIDTH, BASE_HEIGHT, "Cookie", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW Window.\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}
	glViewport(0, 0, BASE_WIDTH, BASE_HEIGHT);
	glFrontFace(GL_CW);//reverses winding
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	ck::World world(
		ck::SetPerspectiveMatrixSystem {},
		ck::SetViewMatrixSystem {},
		ck::ModelRenderingSystem {},
		ck::InitializeInputSystem {},
		ck::SetInputKeysSystem {},
		ck::SetMouseInputSystem {},
		ck::DirectionalLightSystem {},
		ck::PointLightSystem {}
	);

	addResources(&world, ck::Window { BASE_WIDTH, BASE_HEIGHT, window });
	InitGame(&world);

	world.StartSystems();

	float lastFrame { static_cast<float>(glfwGetTime()) };
	while (!glfwWindowShouldClose(window))
	{
		updateTime(world.GetResource<ck::Time>(), &lastFrame);
		std::cout << "FPS: " << (int)(1.0f / world.GetResource<ck::Time>()->deltaTime) << '\n';
		processInput(window);

		glClearColor(0.1f, 0.2f, 0.2f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
}

void addResources(ck::World* world, ck::Window window)
{
	world->AddResource(ck::Time {});
	world->AddResource(window);
}

void updateTime(ck::Time* time, float* lastFrame)
{
	time->time = glfwGetTime();
	time->deltaTime = glfwGetTime() - *lastFrame;
	*lastFrame = glfwGetTime();
}



