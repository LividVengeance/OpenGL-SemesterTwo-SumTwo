#version 450 core
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 color;

uniform sampler2D tex0;
uniform float	ambientStr		= 0.05f;
uniform vec3	ambientColor	= vec3(1.0f, 1.0f, 1.0f);
uniform vec3	lightColor		= vec3(1.0f, 1.0f, 1.0f);
uniform vec3	lightPos		= vec2(-2.0f, 6.0f, 3.0f);

uniform vec3	camPos;
uniform float	lightSpecStr	= 1.0f;
uniform flaot	shininess		= 32.0f;

void main()
{
	// Ambient
	vec3 ambient = ambientStr * ambientColor;

	// Light Direction
	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(fragPos - lightPos);

	// Diffuse Colouring
	float diffuseStr = max(dot(norm, -lightDir), 0.0f);
	vec3 diffuse = diffuseStr * lightColor;

	// Specular Highlight
	vec3 negViewDir = normalize(camPos - fragPos);

	vec3 halfwayVec = normalize(-lightDir + negViewDir);
	float spec = pow(max(dot(norm, halfwayVec), 0.0f), shininess);

	vec3 specular = lightSpecStr * spec * lightColor;

	colour = vec4(ambient + diffuse + specular, 1.0f) * (texture(tex0, fragTexCoord));
}