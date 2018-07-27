#include "Shader.h"
#include <errno.h>

#include <glad/glad.h>

std::string CShader::readFileContent(const char* filePath)
{
	FILE* file = fopen(filePath, "rt");
	
	if (!file)
	{
		printf("%s", strerror(errno));
		return strerror(errno);
	}

	fseek(file, 0, SEEK_END);
	unsigned long length = ftell(file);
	char* contents = new char[length + 1];
	memset(contents, 0, length + 1);
	fseek(file, 0, SEEK_SET);
	fread(contents, 1, length, file);
	fclose(file);

	std::string result(contents);
	delete[] contents;
	return result;
}

GLuint CShader::makeShader(const std::string& source, const EShaderType type)
{
    const char* shader = source.c_str();

    GLuint shaderHandle = glCreateShader((unsigned int)type);
    glShaderSource(shaderHandle, 1, &shader, NULL);

    glCompileShader(shaderHandle);

    GLint success;
    char infoLog[512];
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);

    // In case of compilation errors - create compilation log.
    if (!success)
    {
        glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);
        std::cout << 
            "ERROR::SHADER::" << (type == EShaderType::VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shaderHandle;

}

GLuint CShader::makeVertexShader(const std::string& vert)
{
	const char* vertex = vert.c_str();

	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertex, NULL);

	glCompileShader(vertShader);

	GLint success;
	char infoLog[512];
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);

    // In case of compilation errors - create compilation log.
	if (!success)
	{
		glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return vertShader;

}

GLuint CShader::makeFragmentShader(const std::string& frag)
{
	const char* fragment = frag.c_str();

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragment, NULL);

	glCompileShader(fragShader);

	GLint success;
	char infoLog[512];
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

    // In case of compilation errors - create compilation log.
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return fragShader;
}

GLuint CShader::makeShaderPorgram(const GLuint& vertexShader, const GLuint& fragmentShader)
{
	GLint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	GLint success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    // In case of compilation errors - create compilation log.
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return -1;
	}

	return shaderProgram;
}

/*
	Creates, compiles and link shaders
	also create shader program
*/
CShader::CShader(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource)
	:
	m_programId(0),
	m_bound(false)
{
	std::string vertexSource = readFileContent(vertexShaderSource);
	std::string fragmentSource = readFileContent(fragmentShaderSource);
	
	m_programId = makeShaderPorgram(
        makeShader(vertexSource, EShaderType::VERTEX_SHADER),
        makeShader(fragmentSource, EShaderType::FRAGMENT_SHADER)
	);
}

void CShader::use()
{
	m_bound = true;
	glUseProgram(m_programId);
}

void CShader::disable()
{
	m_bound = false;
	glUseProgram(0);
}

GLuint CShader::getProgramID() const
{
	return m_programId;
}

CShader& CShader::operator=(const CShader& rhs)
{
	this->m_programId = rhs.getProgramID();
	this->m_bound = false;
	return *this;
}

void CShader::setBool(const unsigned int uniformLocation, bool value)
{
	if (!m_bound)
		use();
	glUniform1i(uniformLocation, (int)value);
	disable();
}

void CShader::setInt(const unsigned int uniformLocation, int value)
{
	if (!m_bound)
		use();
	glUniform1i(uniformLocation, value);
	disable();
}

void CShader::setFloat(const unsigned int uniformLocation, float value)
{
	if (!m_bound)
		use();
	glUniform1f(uniformLocation, value);
	disable();
}

void CShader::setVec2(const unsigned int uniformLocation, const glm::vec2 &value)
{
	if (!m_bound)
		use();
	glUniform3fv(uniformLocation, 1, &value[0]);
	disable();
}

void CShader::setVec2(const unsigned int uniformLocation, float x, float y)
{
	if (!m_bound)
		use();
	glUniform2f(uniformLocation, x, y);
	disable();
}

void CShader::setVec3(const unsigned int uniformLocation, const glm::vec3 &value)
{
	if (!m_bound)
		use();
	glUniform3fv(uniformLocation, 1, &value[0]);
	disable();
}

void CShader::setVec3(const unsigned int uniformLocation, float x, float y, float z)
{
	if (!m_bound)
		use();
	glUniform3f(uniformLocation, x, y, z);
	disable();
}

void CShader::setVec4(const unsigned int uniformLocation, const glm::vec4 &value)
{
	if (!m_bound)
		use();
	glUniform4fv(uniformLocation, 1, &value[0]);
	disable();
}

void CShader::setVec4(const unsigned int uniformLocation, float x, float y, float z, float w)
{
	if (!m_bound)
		use();
	glUniform4f(uniformLocation, x, y, z, w);
	disable();
}

void CShader::setMat2(const unsigned int uniformLocation, const glm::mat2 &mat)
{
	if (!m_bound)
		use();
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &mat[0][0]);
	disable();
}

void CShader::setMat3(const unsigned int uniformLocation, const glm::mat3 &mat)
{
	if (!m_bound)
		use();
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &mat[0][0]);
	disable();
}

void CShader::setMat4(const unsigned int uniformLocation, const glm::mat4 &mat)
{
	if (!m_bound)
		use();
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &mat[0][0]);
	disable();
}
