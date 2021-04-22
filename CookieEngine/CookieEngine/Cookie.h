#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "IO/AssetManager.h"
#include <cookie/Camera.h>
#include "ECS/World.h"
#include "Rendering/ModelRenderingSystem.h"
#include "Rendering/SetPerspectiveMatrixSystem.h"
#include "Rendering/SetModelMatricesSystem.h"
namespace ck = cookie;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

void InitGame(ck::World* ecsWorld);



int main();




