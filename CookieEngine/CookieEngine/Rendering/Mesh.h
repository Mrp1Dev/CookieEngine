#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "TextureType.h"
namespace cookie
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
	};

	struct Texture
	{
		unsigned int id;
		TextureType type;
		std::string path;
	};

	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;
		Mesh(
			std::vector<Vertex> vertices,
			std::vector<unsigned int> indices,
			std::vector<Texture> textures
		) : vertices { vertices }, indices { indices }, textures { textures }
		{
			setupMesh();
		};
		unsigned int VBO, VAO, EBO;

	private:

		void setupMesh();
	};
}
