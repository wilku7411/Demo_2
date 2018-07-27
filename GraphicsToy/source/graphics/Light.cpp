#include "Light.h"


void CLight::Update()
{
	if (b_needsUpdate)
	{
		Notify();
		b_needsUpdate = false;
	}
}

void CLight::SetLightPosition(const glm::vec3& position)
{
	m_light_position = position;
	b_needsUpdate = true;
}

void CLight::SetCameraPosition(const glm::vec3& position)
{
	m_camera_position = position;
	b_needsUpdate = true;
}

void CLight::SetLightColor(const glm::vec3& color)
{
	m_light_color = color;
	b_needsUpdate = true;
}

void CLight::SetAmbientStrength(const float ambient_strength)
{
	m_ambientStrength = ambient_strength;
	b_needsUpdate = true;
}

void CLight::SetUpdateStatus(const bool needsUpdate)
{
	b_needsUpdate = needsUpdate;
}

void CLight::Notify()
{
	if (m_observers.size() != 0)
	{
		for (auto sub : m_observers)
		{
			sub->UpdateLightPos(m_light_position);
			sub->UpdateCameraPos(m_camera_position);
			sub->UpdateLightColor(m_light_color);
			sub->UpdateAmbientStrength(m_ambientStrength);
		}
	}
}
