#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "TextureType.h"
#include <U>
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
        u32 id;
        TextureType type;
        std::string path;
    };

    struct Mesh
    {
        std::vector<Vertex> vertices;
        std::vector<u32> indices;
        std::vector<Texture> textures;
        glm::vec3 boundingBoxMin {};
        glm::vec3 boundingBoxMax {};
        Mesh(std::vector<Vertex> vertices, std::vector<u32> indices, std::vector<Texture> textures
        );
        u32 VBO, VAO, EBO;

    private:

        void setupMesh();
        void setupBoundingBoxValues();
    };
}
