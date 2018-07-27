#pragma once

#include <vector>
#include "glm/glm.hpp"

class IUniformChangesEventObserver
{
public:
	virtual void UpdateModelMatrix(const glm::mat4& model) = 0;
	virtual void UpdateViewMatrix(const glm::mat4& view) = 0;
	virtual void UpdateProjectionMatrix(const glm::mat4& projection) = 0;

	virtual void UpdateLightPos(const glm::vec3& light_pos) = 0;
	virtual void UpdateCameraPos(const glm::vec3& camera_pos) = 0;
	virtual void UpdateLightColor(const glm::vec3& light_color) = 0;
	
    virtual void UpdateAmbientStrength(const float ambient_str) = 0;
    virtual void UpdateSpecularStrength(const float specular_str) = 0;
    virtual void UpdateShininess(const float shininess) = 0;

	virtual void UpdateObjectColor(const glm::vec3& object_color) = 0;
};

class IUniformChangesEvent
{
public:
	virtual void Attach(IUniformChangesEventObserver* observer)
	{
		m_observers.push_back(observer);
	}

	virtual void Detach(IUniformChangesEventObserver* observer)
	{
		if (m_observers.size() != 0)
		{
			for (auto it = m_observers.begin(); it == m_observers.end(); it++)
			{
				if (*it == observer)
				{
					m_observers.erase(it);
				}
			}
		}
		else
		{
			printf("Error, no observers on observers list!");
		}
	}

	virtual void Notify() = 0;

protected:
	std::vector<IUniformChangesEventObserver*> m_observers;
};
