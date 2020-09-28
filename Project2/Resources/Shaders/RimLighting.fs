#version 450 core
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 colour;

uniform sampler2D tex0;
uniform float    ambientStr        = 0.15f;
uniform vec3    ambientColor    = vec3(1.0f, 1.0f, 1.0f);
uniform vec3    lightColour        = vec3(1.0f, 1.0f, 1.0f);
uniform vec3    lightPos        = vec3(-2.0f, 6.0f, 3.0f);
uniform int        rimExponent        = 4;
uniform vec3    rimColour        = vec3(1.0f, 0.0f, 0.0f);

uniform vec3    camPos;
uniform float    lightSpecStr    = 1.0f;
uniform float    shininess        = 32.0f;

void main()
{
    // Ambient
    vec3 ambient = ambientStr * ambientColor;

    // Light Direction
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(fragPos - lightPos);

    // Diffuse Colouring
    float diffuseStr = max(dot(norm, -lightDir), 0.0f);
    vec3 diffuse = diffuseStr * lightColour;

    // Specular Highlight
    vec3 negViewDir = normalize(camPos - fragPos);
    vec3 reflectDir = reflect(lightDir, norm);

    vec3 halfwayVec = normalize(-lightDir + negViewDir);
    float spec = pow(max(dot(negViewDir, reflectDir), 0.0f), shininess);

    vec3 specular = lightSpecStr * spec * lightColour;

    // Rim Lighting
    float rimFactor = 1.0 - dot(norm, negViewDir);    // Calculate the rim factor
    rimFactor = smoothstep(0.0f, 1.0f, rimFactor);    // Contrain it to the exponent
    rimFactor = pow(rimFactor, rimExponent);        // Raise it to the rim exponent
    vec3 rim = rimFactor * rimColour * lightColour;    //

    colour = vec4(ambient + diffuse + specular + rim, 1.0f) * (texture(tex0, fragTexCoord));
}