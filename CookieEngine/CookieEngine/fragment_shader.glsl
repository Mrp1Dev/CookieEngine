#version 330 core

struct Material{
    sampler2D texture_diffuse0;
    vec4 baseColor;
    bool hasTexture;
};

out vec4 FragColor;

in vec2 TexCoords;

uniform Material material;

void main()
{    
    FragColor =
        material.hasTexture ?
        texture(material.texture_diffuse0, TexCoords) * material.baseColor 
        : material.baseColor;
}
