#version 440 core
layout(location = 0) in vec3 samplerVectors;

out vec3 texCoords;

uniform mat4 u_projection;
uniform mat4 u_view;

void main()
{
	texCoords = samplerVectors;
	vec4 resultPos = u_projection * u_view * vec4(samplerVectors, 1.0);
	gl_Position = resultPos.xyww;
}