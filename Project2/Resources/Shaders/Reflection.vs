#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;



out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

uniform float currentTime;

void main()
{
    gl_Position = proj * view * model * vec4(position, 1.0f);
    fragPos = vec3(model * vec4(position, 1.0f));
    fragNormal = mat3(transpose(inverse(model))) * normal;
    fragTexCoord = texCoord;
}