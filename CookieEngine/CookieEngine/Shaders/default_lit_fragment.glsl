#version 330 core

#define MAX_DIFFUSE_TEXTURE_COUNT 32
#define MAX_SPECULAR_TEXTURE_COUNT 32
#define MAX_POINT_LIGHT_COUNT 8
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

struct PointLightType
{
    vec3 position;
    vec3 diffuseColor;
    vec3 specularColor;
};

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform MaterialType Material;
uniform DirectionalLightType DirectionalLight;
uniform PointLightType PointLights[MAX_POINT_LIGHT_COUNT];
uniform int PointLightCount;

vec3 calulateDirectionalLight(DirectionalLightType light, vec3 normal, vec3 baseDiffuseColor)
{
    vec3 lightDir = -light.direction;
    float diffuseStrength = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diffuseStrength * baseDiffuseColor * light.diffuseColor;
    vec3 ambient = light.ambientColor * baseDiffuseColor;
    return diffuse + ambient;
}

vec3 calculatePointLighting(PointLightType light, vec3 normal, vec3 baseDiffuseColor)
{
    vec3 dir = light.position - FragPos;
    float diffuseStrength = max(dot(dir, normal), 0.0);
    return diffuseStrength * light.diffuseColor * baseDiffuseColor;
}

void main()
{    
    vec3 res;
    vec3 baseDiffuseColor = texture(Material.diffuseTextures[0], TexCoords).xyz;
    vec3 normal = normalize(Normal);
    res += calulateDirectionalLight(DirectionalLight, normal, baseDiffuseColor);
    for(int i = 0; i < PointLightCount; i++)
        res += calculatePointLighting(PointLights[i], normal, baseDiffuseColor);
    FragColor = vec4(res, 1.0);
}


