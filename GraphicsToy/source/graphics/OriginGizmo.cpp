#include "OriginGizmo.h"

#include "Shader.h"


COriginGizmo::COriginGizmo() :
	m_shader(nullptr)
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(float), &axes[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	LoadShader();
}

COriginGizmo::~COriginGizmo()
{
	delete m_shader;
}

void COriginGizmo::LoadShader()
{
	m_shader = new CShader("source/resources/shaders/lines.vert", "source/resources/shaders/lines.frag");
	GetUniformsFromShader();
}

void COriginGizmo::GetUniformsFromShader()
{
	axisProjMatID = glGetUniformLocation(m_shader->getProgramID(), "u_projection");
	axisViewMatID = glGetUniformLocation(m_shader->getProgramID(), "u_view");
	axisModelMatID = glGetUniformLocation(m_shader->getProgramID(), "u_model");
}

void COriginGizmo::UpdateMatrices(const glm::mat4& projection_matrix, const glm::mat4& view_matrix, const glm::mat4& model_matrix)
{
	m_shader->use();
	glUniformMatrix4fv(axisProjMatID, 1, GL_FALSE, &projection_matrix[0][0]);
	glUniformMatrix4fv(axisViewMatID, 1, GL_FALSE, &view_matrix[0][0]);
	glUniformMatrix4fv(axisModelMatID, 1, GL_FALSE, &model_matrix[0][0]);
    m_shader->disable();    
}

void COriginGizmo::Update(const glm::mat4& view_matrix, const glm::mat4& model_matrix)
{
	m_shader->use();
	glUniformMatrix4fv(axisViewMatID, 1, GL_FALSE, &view_matrix[0][0]);
	glUniformMatrix4fv(axisModelMatID, 1, GL_FALSE, &model_matrix[0][0]);
    m_shader->disable();    
}

void COriginGizmo::Draw(unsigned int shader)
{
	glUseProgram(shader);
	glBindVertexArray(m_vao);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);   
    glUseProgram(0);        
}

void COriginGizmo::Draw()
{
	glDisable(GL_DEPTH_TEST);
	Draw(*m_shader);
	glEnable(GL_DEPTH_TEST);
}
