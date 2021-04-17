#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace cookie
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	struct Texture
	{
		unsigned int Id;
		std::string Type;
		std::string Path;
	};
	struct Mesh
	{
		std::vector<Vertex> Vertices;
		std::vector<unsigned int> Indices;
		std::vector<Texture> Textures;
		unsigned int VBO, VAO, EBO;
	};
}
