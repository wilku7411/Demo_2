#pragma once

#include "IO/Window.h"
#include "graphics/Material.h"

#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

class CGui
{
public:
	CGui(CWindow* window);
	void AddLightInformation(glm::vec3* lightpos, glm::vec3* lightColor);
	void Draw(CMaterial* material = nullptr);
	void Destroy();

private:
	CWindow* m_windowRef;
	ImVec4 m_clearColor;
	glm::vec3* m_lightPos;
	glm::vec3* m_lightColor;
	float ambientStrength = 0.4f;
	float specularStrength = 0.5;
	float shininess = 2.0f;
};
