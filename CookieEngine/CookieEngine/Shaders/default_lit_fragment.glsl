#version 330 core

#define MAX_DIFFUSE_TEXTURE_COUNT 32
#define MAX_SPECULAR_TEXTURE_COUNT 32

struct MaterialType 
{
    sampler2D diffuseTextures[MAX_DIFFUSE_TEXTURE_COUNT];
    sampler2D specularTextures[MAX_SPECULAR_TEXTURE_COUNT];
    vec4 baseColor;
    int diffuseTextureCount;
    int specularTextureCount;
};

struct DirectionalLightType
{
    vec3 direction;
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
};

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;

uniform MaterialType Material;
uniform DirectionalLightType DirectionalLight;

vec3 calulateDirectionalLight(DirectionalLightType light, vec3 normal, vec3 baseDiffuseColor)
{
    vec3 lightDir = -light.direction;
    float diffuseStrength = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diffuseStrength * baseDiffuseColor * light.diffuseColor;
    vec3 ambient = light.ambientColor * baseDiffuseColor;
    return diffuse + ambient;
}

void main()
{    
    vec3 baseDiffuseColor = texture(Material.diffuseTextures[0], TexCoords).xyz;
    vec3 normal = normalize(Normal);
    FragColor = vec4(calulateDirectionalLight(DirectionalLight, normal, baseDiffuseColor), 1.0);
}


