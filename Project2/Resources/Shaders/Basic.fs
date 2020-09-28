#version 450 core

in vec3 fragColor;
in vec2 fragTexCoord;

out vec4 color;

uniform float currentTime;
uniform sampler2D tex;
uniform sampler2D tex1;

void main()
{
	color = texture(tex, fragTexCoord);
}