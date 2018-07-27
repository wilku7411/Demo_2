#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 passedFragPos;
out vec3 passedNormal;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

void main()
{
    passedFragPos = vec3(u_model * vec4(aPos, 1.0));
    passedNormal = mat3(transpose(inverse(u_model))) * aNormal;  
   
    gl_Position = u_projection * u_view * u_model * vec4(position, 1.0);
}