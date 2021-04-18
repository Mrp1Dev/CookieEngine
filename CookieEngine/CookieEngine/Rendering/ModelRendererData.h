#pragma once
#include <string>
#include <vector>
#include "Model.h"
#include "../ECS/Ref.h"
namespace cookie
{
	struct ModelRendererData
	{
		Model* model;
		bool enabled;
	};
}