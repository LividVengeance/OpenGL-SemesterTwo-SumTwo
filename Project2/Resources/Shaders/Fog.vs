#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 fragColor;
out vec2 fragTexCoord;
out vec4 worldPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    vec4 worldPos = model * vec4(position, 1.0);
    gl_Position = proj * view * worldPos;

    fragColor = color;
    fragTexCoord = texCoord;
}