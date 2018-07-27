#include "Material.h"
#include "../Timer.h"

void CMaterial::RaportUpdates()
{
    char counter = 0;

    printf_s("========================\n");

    while(!m_updateRaports.empty())
    {
        printf("Uniform %s updated.\n", m_updateRaports.front().c_str());
        m_updateRaports.pop();
        counter++;
    }
    printf("Unique uniforms updated: %d\n", counter);

    for (auto it = m_updatedArray.begin(); it < m_updatedArray.end(); it++)
    {
        *it = false;
    }
}

CMaterial::CMaterial(const std::string& vertexSource, const std::string& fragmentSource)
{
    LoadShaderFromFile(vertexSource, fragmentSource);
    m_updatedArray.resize(sizeof(SBasicUniforms)/sizeof(unsigned int));
    name = vertexSource;
}

CMaterial::~CMaterial()
{
	delete m_shader;
}

void CMaterial::LoadShaderFromFile(const std::string& vertexSource, const std::string& fragmentSource)
{
	m_shader = new CShader(vertexSource.c_str(), fragmentSource.c_str());
	GetUniformsLocations();
}

void CMaterial::SetShader(CShader* shader)
{
    m_shader = shader;
}

void CMaterial::SetUniforms(const SBasicUniforms& uniforms)
{
    m_uniforms = uniforms;
}

void CMaterial::UpdateModelMatrix(const glm::mat4& model)
{
    m_shader->setMat4(m_uniforms.modelMatrix, model);
    if (m_updatedArray[0] == false)
    {
        m_updatedArray[0] = true;
        m_updateRaports.push(s(model));
    }
}

void CMaterial::UpdateViewMatrix(const glm::mat4& view)
{
	m_shader->setMat4(m_uniforms.viewMatrix, view);
    if (m_updatedArray[1] == false)
    {
        m_updatedArray[1] = true;
        m_updateRaports.push(s(view));
    }
}

void CMaterial::UpdateProjectionMatrix(const glm::mat4& projection)
{
    m_shader->setMat4(m_uniforms.projectionMatrix, projection);
    if (m_updatedArray[2] == false)
    {
        m_updatedArray[2] = true;
        m_updateRaports.push(s(projection));
    }
}

void CMaterial::UpdateLightPos(const glm::vec3& light_pos)
{
    m_shader->setVec3(m_uniforms.lightPosition, light_pos);
    if (m_updatedArray[3] == false)
    {
        m_updatedArray[3] = true;
        m_updateRaports.push(s(light_pos));
    }
}

void CMaterial::UpdateCameraPos(const glm::vec3& camera_pos)
{
    m_shader->setVec3(m_uniforms.cameraPosition, camera_pos);
    if (m_updatedArray[4] == false)
    {
        m_updatedArray[4] = true;
        m_updateRaports.push(s(camera_pos));
    }
}

void CMaterial::UpdateLightColor(const glm::vec3& light_color)
{
    m_shader->setVec3(m_uniforms.lightColor, light_color);
    if (m_updatedArray[5] == false)
    {
        m_updatedArray[5] = true;
        m_updateRaports.push(s(light_color));
    }
}

void CMaterial::UpdateAmbientStrength(const float ambient_str)
{
    m_shader->setFloat(m_uniforms.ambientStrength, ambient_str);
    if (m_updatedArray[6] == false)
    {
        m_updatedArray[6] = true;
        m_updateRaports.push(s(ambient_str));
    }
}

void CMaterial::UpdateSpecularStrength(const float specular_str)
{
    m_shader->setFloat(m_uniforms.specularStrength, specular_str);
    if (m_updatedArray[7] == false)
    {
        m_updatedArray[7] = true;
        m_updateRaports.push(s(specular_str));
    }
}

void CMaterial::UpdateShininess(const float shininess)
{
    m_shader->setFloat(m_uniforms.shininess, shininess);
    if (m_updatedArray[8] == false)
    {
        m_updatedArray[8] = true;
        m_updateRaports.push(s(shininess));
    }
}

void CMaterial::UpdateObjectColor(const glm::vec3& object_color)
{
    m_shader->setVec3(m_uniforms.objectColor, object_color);
    if (m_updatedArray[9] == false)
    {
        m_updatedArray[9] = true;
        m_updateRaports.push(s(object_color));
    }
}

void CMaterial::Update()
{
    counter += g_mainTimer.deltaTime;
    if (counter >= 10.0)
    {
        printf_s("\n\n%s\n\n", name.c_str());
        RaportUpdates();
        counter = 0.0;
    }
}

void CMaterial::GetUniformsLocations()
{
	m_shader->use();
    unsigned int program = m_shader->getProgramID();
	m_uniforms.SetAll(
		glGetUniformLocation(program, "u_model"),
		glGetUniformLocation(program, "u_view"),
		glGetUniformLocation(program, "u_projection"),
		glGetUniformLocation(program, "u_lightPos_worldspace"),
		glGetUniformLocation(program, "u_lightColor"),
		glGetUniformLocation(program, "u_ambientStrength"),
        glGetUniformLocation(program, "u_specularStrength"),
        glGetUniformLocation(program, "u_shininess"),
		glGetUniformLocation(program, "u_viewPos"),
		glGetUniformLocation(program, "u_objectColor")
	);
    //m_shader->disable();
}
