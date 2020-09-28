#version 450 core

in vec2 fragTexCoord;

out vec4 colour;

uniform sampler2D tex;
uniform vec3 textColour;

void main()
{
	vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(tex, fragTexCoord).r);
	colour = vec4(textColour, 1.0f) * sampled;
}