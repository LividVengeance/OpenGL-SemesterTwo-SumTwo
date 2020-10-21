#version 330 core
layout (points) in; // receiving in points
layout (triangle_strip, max_vertices = 4) out; // sending out triangle strips

uniform mat4 vp;
uniform vec3 vQuad1, vQuad2;

out GS_FS_VERTEX
{
	vec2 texcoord;
}gs_out;

void main()
{
	float size = 0.1;

	vec3 p1 = gl_in[0].gl_Position.xyz +(-vQuad1-vQuad2)* size;
	gl_Position = vp * vec4(p1, 1.0f);
	gs_out.texcoord = vec2(0.0f, 0.0f); EmitVertex();

	vec3 p2 = gl_in[0].gl_Position.xyz + (-vQuad1+vQuad2)* size;
	gl_Position = vp * vec4(p2, 1.0f);
	gs_out.texcoord = vec2(0.0f, 1.0f); EmitVertex();

	vec3 p3 = gl_in[0].gl_Position.xyz + (vQuad1-vQuad2)* size;
	gl_Position = vp * vec4(p3, 1.0f);
	gs_out.texcoord = vec2(1.0f, 0.0f); EmitVertex();

	vec3 p4 = gl_in[0].gl_Position.xyz + (vQuad1+vQuad2)* size;
	gl_Position = vp * vec4(p4, 1.0f);
	gs_out.texcoord = vec2(1.0f, 1.0f); EmitVertex();

	EndPrimitive();
}