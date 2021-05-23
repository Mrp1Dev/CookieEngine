#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ProjectionViewMatrix;
void main()
{
    TexCoords = aTexCoords;
    Normal = (ModelMatrix * vec4(aNormal, 1.0)).xyz;
    FragPos =  (ModelMatrix * vec4(aPos, 1.0)).xyz;
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(aPos, 1.0);
}