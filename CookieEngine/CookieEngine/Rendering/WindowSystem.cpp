#include "WindowSystem.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Usings.h>
namespace cookie
{
    void WindowSystem::Update(World* world)
    {
        auto* window { world->GetResource<Window>() };
        i32 width {};
        i32 height {};
        glfwGetWindowSize(window->glfwWindow, &width, &height);
        glViewport(0, 0, width, height);
        window->width = width;
        window->height = height;
    }
}