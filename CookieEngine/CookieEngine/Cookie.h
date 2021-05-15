#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "IO/AssetManager.h"
#include "ECS/World.h"
#include "Rendering/ModelRenderingSystem.h"
#include "Rendering/SetPerspectiveMatrixSystem.h"
#include "ResourceTypes/Time.h"
#include "Rendering/SetViewMatrixSystem.h"
namespace ck = cookie;

void addResources(ck::World* world);
void updateTime(ck::Time* time, float* lastFrame);
void processInput(GLFWwindow* window);
void InitGame(ck::World* ecsWorld);





