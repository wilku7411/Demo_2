#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class CShader;


const float axes[36] =
{
    // xyz				rgb
    0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,

    0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,	0.0f, 1.0f, 0.0f,

    0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,	0.0f, 0.0f, 1.0f
};

const unsigned int indices[6] =
{
    0, 1,
    2, 3,
    4, 5
};

class COriginGizmo
{

public:
	COriginGizmo();
	virtual ~COriginGizmo();

	void LoadShader();
	void GetUniformsFromShader();
	
	void UpdateMatrices(const glm::mat4& projection_matrix, const glm::mat4& view_matrix, const glm::mat4& model_matrix);
	void Update(const glm::mat4& view_matrix, const glm::mat4& model_matrix);
	
	void Draw();
	void Draw(unsigned int shader);

public:
	union 
	{
		unsigned int MVP[3];
		struct { unsigned int axisProjMatID, axisViewMatID, axisModelMatID; };
	};

private:
	unsigned int m_vao, m_vbo, m_ebo;
	CShader* m_shader;
};
