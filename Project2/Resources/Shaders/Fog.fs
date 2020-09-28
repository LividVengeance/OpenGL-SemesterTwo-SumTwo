#version 450 core

in vec3 fragColor;
in vec2 fragTexCoord;
in vec4 worldPos;

out vec4 color;

uniform float currentTime;
uniform sampler2D tex;
uniform sampler2D tex1;
uniform vec3 camPos;

void main()
{
    float d = distance(worldPos.xyz, camPos);
    float lerp = (d - 5.0f)/10.f;
    lerp = clamp(lerp, 0.0, 1.0);

    vec4 vFogColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);

    color = mix(texture(tex, fragTexCoord), vFogColor, lerp);
}