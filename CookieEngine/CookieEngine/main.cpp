#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Cookie.h"
#include <Math/Mathf.h>
#include "Resources.h"
#include "Input/InitializeInputSystem.h"
#include "Input/SetInputKeysSystem.h"
#include "Input/SetMouseInputSystem.h"
#include "Rendering/Lighting/DirectionalLightSystem.h"
#include "Rendering/Lighting/PointLightSystem.h"
#include "Rendering/WindowSystem.h"
#include "Rendering/ModelRenderingSystem.h"
#include "Rendering/SetProjectionViewMatrices.h"
#include "Physics/PhysicsSystem.h"
using namespace ck;
using namespace ck::physics;
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void addResources(World* world, Window window)
{
    world->AddResource(Time {});
    world->AddResource(window);
}

void updateTime(Time* time, f32* lastFrame)
{
    time->time = scast<f32>(glfwGetTime());
    time->deltaTime = scast<f32>(glfwGetTime()) - *lastFrame;
    *lastFrame = scast<f32>(glfwGetTime());
}

GLFWwindow* InitWindow(i32 w, i32 h)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(w, h, "Cookie", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW Window.\n";
        glfwTerminate();
        return nullptr;
    }
    return window;
}

i32 InitOpengl(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    glFrontFace(GL_CW);//reverses winding
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    return 1;
}

i32 main()
{
    constexpr i32 BASE_WIDTH = 1280;
    constexpr i32 BASE_HEIGHT = 720;
    constexpr f32 DEFAULT_FIXED_DT = 1.0f / 144.0f;
    auto* window = InitWindow(BASE_WIDTH, BASE_HEIGHT);
    if (window == nullptr) return -1;
    if (InitOpengl(window) == -1) return -1;

    World world {};

    addResources(&world, Window { BASE_WIDTH, BASE_HEIGHT, window });
    world.AddSystem(InitializeInputSystem {});
    world.AddSystem(SetInputKeysSystem {});
    world.AddSystem(SetMouseInputSystem {});

    InitGame(&world);

    world.AddSystem(PhysicsSystem {});

    world.AddSystem(DirectionalLightSystem {});
    world.AddSystem(SetProjectionViewMatrices {});
    world.AddSystem(ModelRenderingSystem {});
    world.AddSystem(PointLightSystem {});

    world.AddSystem(WindowSystem {});

    world.StartSystems();

    f32 lastFrame { scast<f32>(glfwGetTime()) };
    f32 accumulator { 0.0f };
    auto* timeResource = world.GetResource<Time>();
    timeResource->fixedDeltaTime = DEFAULT_FIXED_DT;
    while (!glfwWindowShouldClose(window))
    {
        updateTime(timeResource, &lastFrame);
        std::cout << "Frame Time: " << timeResource->deltaTime << ", FPS: " << 1.0f / timeResource->deltaTime  << '\n';
        accumulator += timeResource->deltaTime;
        processInput(window);

        glClearColor(0.78f, 0.96f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        while (accumulator >= timeResource->fixedDeltaTime)
        {
            world.FixedUpdateSystems();
            accumulator -= timeResource->fixedDeltaTime;
        }
        world.UpdateSystems();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}




