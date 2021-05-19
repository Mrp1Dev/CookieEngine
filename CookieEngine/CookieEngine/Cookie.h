#pragma once
#define GLM_FORCE_LEFT_HANDED
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "IO/AssetManager.h"
#include "ECS/World.h"
#include "Rendering/ModelRenderingSystem.h"
#include "Rendering/SetPerspectiveMatrixSystem.h"
#include "Rendering/SetViewMatrixSystem.h"
#include "Resources.h"
#include "Input/InitializeInputSystem.h"
#include "Input/SetInputKeysSystem.h"
namespace ck = cookie;

void addResources(ck::World* world, ck::Window window);
void updateTime(ck::Time* time, float* lastFrame);
void processInput(GLFWwindow* window);
void InitGame(ck::World* ecsWorld);





