#include "Cookie.h"


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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}
	glViewport(0, 0, 1280, 720);
	glEnable(GL_DEPTH_TEST);

	ck::World world(
		ck::SetPerspectiveMatrixSystem {},
		ck::SetViewMatrixSystem {},
		ck::ModelRenderingSystem {}
	);

	addResources(&world);
	InitGame(&world);
	world.EnqueueEntitySpawn(ck::CameraData { 90.0f, true }, ck::TransformData {});
	world.StartSystems();

	float lastFrame { static_cast<float>(glfwGetTime()) };
	while (!glfwWindowShouldClose(window))
	{
		updateTime(world.GetResource<ck::Time>(), &lastFrame);
		std::cout << "FPS: " << 1.0f / world.GetResource<ck::Time>()->deltaTime << '\n';
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

void addResources(ck::World* world)
{
	world->AddResource(ck::Time {});
}

void updateTime(ck::Time* time, float* lastFrame)
{
	time->time = glfwGetTime();
	time->deltaTime = glfwGetTime() - *lastFrame;
	*lastFrame = glfwGetTime();
}



