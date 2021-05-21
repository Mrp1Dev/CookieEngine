#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
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
		Mesh(
			std::vector<Vertex> vertices,
			std::vector<unsigned int> indices,
			std::vector<Texture> textures
		) : Vertices { vertices }, Indices { indices }, Textures { textures }
		{
			setupMesh();
		};
		unsigned int VBO, VAO, EBO;

	private:

		void setupMesh();
	};
}
