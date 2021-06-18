#include "Mesh.h"
#include <ckMath.h>
namespace cookie
{
	Mesh::Mesh(std::vector<Vertex> vertices,
		std::vector<u32> indices,
		std::vector<Texture> textures) : vertices { vertices }, indices { indices }, textures { textures }
	{
		setupMesh();
		setupBoundingBoxValues();
	}
	void Mesh::setupMesh()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32),
			&indices[0], GL_STATIC_DRAW
		);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

		glBindVertexArray(0);
	}

	void Mesh::setupBoundingBoxValues()
	{
		glm::vec3 min { math::Vector3::Splat(std::numeric_limits<f32>::max()) };
		glm::vec3 max { math::Vector3::Splat(-std::numeric_limits<f32>::max()) };
		for (auto& vert : vertices)
		{
			auto pos = vert.position;
			if (pos.x < min.x) min.x = pos.x;
			if (pos.y < min.y) min.y = pos.y;
			if (pos.z < min.z) min.z = pos.z;
			if (pos.x > max.x) max.x = pos.x;
			if (pos.y > max.y) max.y = pos.y;
			if (pos.z > max.z) max.z = pos.z;
		}
		boundingBoxMax = max;
		boundingBoxMin = min;
	}
}