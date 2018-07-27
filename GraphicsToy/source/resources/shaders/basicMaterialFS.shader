#version 440 core

in vec3 passedFragPos;
in vec3 passedNormal;

out FragColor;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
}

struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
}

uniform vec3 u_cameraPos;
uniform Material u_material;
uniform Light u_light;

void main()
{
	// Ambient lighting
	vec3 amb = light.ambient * u_material.ambient;

	// Diffuse lighting
	vec3 norm = normalize(passedNormal);
	vec3 lightDir = normalize(u_light.position - passedFragPos);
	vec3 diff = max(dot(norm, lightDir), 0.0);
	diffuse = u_light.diffuse * (diff * u_material.diffuse);

	// Specular 
	vec3 viewDir = normalize(u_cameraPos - passedFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	vec3 spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
	specular = u_light.specular * (spec* u_material.specular);

	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result, 1.0);

}