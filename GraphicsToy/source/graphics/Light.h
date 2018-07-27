#pragma once

#include "../UniformChangesEvent.h"

#include "glm/glm.hpp"


class CLight : public IUniformChangesEvent
{
public:
	CLight() = default;
	CLight(const glm::vec3& light_position, const glm::vec3& camera_position, const glm::vec3& light_color, const float ambient_strength)
		:
		m_light_position(light_position),
		m_camera_position(camera_position),
		m_light_color(light_color),
		m_ambientStrength(ambient_strength),
		b_needsUpdate(true)
	{}

	void Update();
	
	void SetLightPosition(const glm::vec3& position);
	void SetCameraPosition(const glm::vec3& position);
	void SetLightColor(const glm::vec3& color);
	void SetAmbientStrength(const float ambient_strength);
	void SetUpdateStatus(const bool needsUpdate);

	inline glm::vec3 GetLightPosition() const { return m_light_position; }
	inline glm::vec3 GetCameraPosition()const { return m_camera_position; }
	inline glm::vec3 GetLightColor() const { return m_light_color; }
	inline float GetAmbientStrength() const { return m_ambientStrength; }
	inline bool GetUpdateStatus() const { return b_needsUpdate; }

	// Interface implementation
	virtual void Notify() override;

private:
	glm::vec3 m_light_position;
	glm::vec3 m_camera_position;
	glm::vec3 m_light_color;
	float m_ambientStrength;
	bool b_needsUpdate;
};