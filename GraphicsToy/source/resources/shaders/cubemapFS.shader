#version 440 core
in vec3 out_normal;
in vec3 out_position;

out vec4 fragColor;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{
	vec3 I = normalize(out_position - cameraPos);
	vec3 R = reflect(I, normalize(out_normal));
	fragColor = vec4(texture(skybox, R).rgb, 1.0);
}