#pragma once
#include <string>
#include <vector>
#include "Mesh.h"

namespace cookie
{
	struct ModelData
	{
		std::vector<Mesh> meshes;
		std::vector<Texture> loadedTextures;
		std::string directory;
		std::string path;
		bool loaded { false };
		ModelData(std::string path) : path { path }
		{
		};
	};
}