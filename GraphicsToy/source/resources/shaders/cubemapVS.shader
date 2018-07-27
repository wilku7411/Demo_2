#version 440 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 out_normal;
out vec3 out_position;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	out_normal = mat3(transpose(inverse(u_model))) * normal;
	out_position = vec3(u_model * vec4(position, 1.0));
	gl_Position = u_projection * u_view * u_model * vec4(position, 1.0);
}