#include "Gui.h"

CGui::CGui(CWindow* window) 
	:
	m_windowRef(window)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfwGL3_Init(window->GetWindow(), true);
	ImGui::StyleColorsDark();

	m_clearColor.x = window->GetBackgroundColor()[0];
	m_clearColor.y = window->GetBackgroundColor()[1];
	m_clearColor.z = window->GetBackgroundColor()[2];
	m_clearColor.w = window->GetBackgroundColor()[3];
}

void CGui::AddLightInformation(glm::vec3* lightpos, glm::vec3* lightColor)
{
	m_lightPos = lightpos;
	m_lightColor = lightColor;
}

void CGui::Draw(CMaterial* material /*= nullptr*/)
{
	ImGui_ImplGlfwGL3_NewFrame();

	{
		ImGui::Begin("Helper window");
		ImGui::ColorEdit3("Background color", (float*)&m_clearColor);
		m_windowRef->SetBackgroundColor((float*)&m_clearColor);


		// testint changing uniform
		if (material != nullptr)
		{
			ImGui::SliderFloat("Ambient strength", &ambientStrength, 0.0f, 1.0f);
			material->UpdateAmbientStrength(ambientStrength);

			ImGui::SliderFloat("Specular strength", &specularStrength, 0.0f, 1.0f);
			material->UpdateSpecularStrength(specularStrength);

			ImGui::SliderFloat("Shininess", &shininess, 0.1f, 8.0f);
			material->UpdateShininess(shininess);
		}

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

void CGui::Destroy()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}
