#version 450 core;
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 color;

uniform sampler2D tex0;
uniform float	ambientStr		= 0.05f;
uniform vec3	ambientColor	= vec3(1.0f, 1.0f, 1.0f);

void main()
{
	// Ambient
	vec3 ambient = ambientStr * ambientColor;

	color = vec4(ambient, 1.0f) * (texture(tex0, fragTexCoord));
}