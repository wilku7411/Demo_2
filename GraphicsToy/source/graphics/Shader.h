#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <glm/glm.hpp>

#include <glad/glad.h>

class CShader
{
public:
    enum class EShaderType
    {
        VERTEX_SHADER    = GL_VERTEX_SHADER,
        FRAGMENT_SHADER  = GL_FRAGMENT_SHADER
    };

	CShader() = delete;
	CShader(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource);
	
	void use();
	void disable();
	GLuint getProgramID() const;
    inline operator unsigned int() const { return m_programId; };
	CShader& operator=(const CShader& rhs);

	void setBool(const unsigned int uniformLocation, bool value);
	void setInt(const unsigned int uniformLocation, int value);
	void setFloat(const unsigned int uniformLocation, float value);
	void setVec2(const unsigned int uniformLocation, const glm::vec2 &value);
	void setVec2(const unsigned int uniformLocation, float x, float y);
	void setVec3(const unsigned int uniformLocation, const glm::vec3 &value);
	void setVec3(const unsigned int uniformLocation, float x, float y, float z);
	void setVec4(const unsigned int uniformLocation, const glm::vec4 &value);
	void setVec4(const unsigned int uniformLocation, float x, float y, float z, float w);
	void setMat2(const unsigned int uniformLocation, const glm::mat2 &mat);
	void setMat3(const unsigned int uniformLocation, const glm::mat3 &mat);
	void setMat4(const unsigned int uniformLocation, const glm::mat4 &mat);
private: 
	std::string readFileContent(const char* filePath);
    GLuint makeShader(const std::string& source, const EShaderType type);
	GLuint makeVertexShader(const std::string& vert);
	GLuint makeFragmentShader(const std::string& frag);
	GLuint makeShaderPorgram(const GLuint& vertexShader, const GLuint& fragmentShader);

private: 
	GLuint m_programId;
	bool m_bound;
};

