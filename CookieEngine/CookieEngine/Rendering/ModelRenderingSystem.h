#pragma once
#include "../ECS/World.h"
#include "ModelRendererData.h"
#include "ShaderData.h"
#include "TransformData.h"
#include "BaseColorData.h"

namespace cookie
{
	class ModelRenderingSystem : public System
	{
	public:
		virtual void Update(World* world) override;
		void DrawMesh(Shader* shader, Mesh& mesh);
	};
}
