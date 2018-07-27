#pragma once

#include "Shader.h"
#include "Uniforms.h"
#include "../UniformChangesEvent.h"

#include <queue>

#ifndef s(x)
#define s(x) #x
#endif

class CMaterial : public IUniformChangesEventObserver
{
private:
	void RaportUpdates();

public:
	CMaterial() :
		m_shader(nullptr),
		m_uniforms(),
		m_updateRaports(),
		m_updatedArray()
	{};
    CMaterial(const std::string& vertexSource, const std::string& fragmentSource);
	~CMaterial();

	void LoadShaderFromFile(const std::string& vertexSource, const std::string& fragmentSource);

	inline CShader* GetShader() { return m_shader; }
    inline SBasicUniforms Uniform() { return m_uniforms; }

    void SetShader(CShader* shader);
    void SetUniforms(const SBasicUniforms& uniforms);

	CMaterial& operator=(const CMaterial& other) = default;

	// Interface implementation
	void UpdateModelMatrix(const glm::mat4& model) override;
	void UpdateViewMatrix(const glm::mat4& view) override;
	void UpdateProjectionMatrix(const glm::mat4& projection) override;
	void UpdateLightPos(const glm::vec3& light_pos) override;
	void UpdateCameraPos(const glm::vec3& camera_pos) override;
	void UpdateLightColor(const glm::vec3& light_color) override;
	void UpdateAmbientStrength(const float ambient_str) override;
    void UpdateSpecularStrength(const float specular_str) override;
    void UpdateObjectColor(const glm::vec3& object_color) override;
    void UpdateShininess(const float shininess) override;

    // Methods
    void Update();

private:
	void GetUniformsLocations();

private:
	CShader* m_shader;
	SBasicUniforms m_uniforms;
    std::queue<std::string> m_updateRaports;
    std::vector<bool> m_updatedArray;
    float counter = 0;
    std::string name;
};

