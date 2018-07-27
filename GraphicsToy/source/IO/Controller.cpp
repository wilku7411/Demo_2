#include "Controller.h"

STimer g_mainTimer = STimer();

void CController::InputUpdate()
{
    short reverse = 1;

    if (glfwGetKey(m_windowRef->GetWindow(), GLFW_KEY_W))
    {
        *m_modelRef = glm::translate(*m_modelRef, (float)g_mainTimer.deltaTime * 200.0f * glm::vec3{ 0.0f, 0.0f, -0.1f });
    }
    if (glfwGetKey(m_windowRef->GetWindow(), GLFW_KEY_S))
    {
        reverse = -1;
        *m_modelRef = glm::translate(*m_modelRef, (float)g_mainTimer.deltaTime * 200.0f  * glm::vec3{ 0.0f, 0.0f, 0.1f });
    }
    if (glfwGetKey(m_windowRef->GetWindow(), GLFW_KEY_A))
    {
		*m_modelRef = glm::translate(*m_modelRef, (float)g_mainTimer.deltaTime * 200.0f  * glm::vec3{ -0.1f, 0.0f, 0.0f });
    }
    if (glfwGetKey(m_windowRef->GetWindow(), GLFW_KEY_D))
    {
		*m_modelRef = glm::translate(*m_modelRef, (float)g_mainTimer.deltaTime * 200.0f  * glm::vec3{ 0.1f, 0.0f, 0.0f });
    }

    if (glfwGetKey(m_windowRef->GetWindow(), GLFW_KEY_Q))
    {
		*m_modelRef = glm::rotate(*m_modelRef, glm::radians(0.4f * reverse) * (float)g_mainTimer.deltaTime * 200.0f, glm::vec3{ 0.0f, 1.0f, 0.0f });
    }
    if (glfwGetKey(m_windowRef->GetWindow(), GLFW_KEY_E))
    {
        *m_modelRef = glm::rotate(*m_modelRef, glm::radians(-0.4f * reverse) * (float)g_mainTimer.deltaTime * 200.0f, glm::vec3{ 0.0f, 1.0f, 0.0f });
    }

    if (glfwGetKey(*m_windowRef, GLFW_KEY_DOWN))
    {
		*m_viewRef = glm::translate(*m_viewRef, (float)g_mainTimer.deltaTime * 20.0f * glm::vec3{ 0.0f, 0.0f, -0.1f });
    }
    if (glfwGetKey(*m_windowRef, GLFW_KEY_UP))
    {
		*m_viewRef = glm::translate(*m_viewRef, (float)g_mainTimer.deltaTime * 20.0f * glm::vec3{ 0.0f, 0.0f, 0.1f });
    }
    if (glfwGetKey(*m_windowRef, GLFW_KEY_RIGHT))
    {
		*m_viewRef = glm::translate(*m_viewRef, (float)g_mainTimer.deltaTime * 20.0f * glm::vec3{ -0.1f, 0.0f, 0.0f });
    }
    if (glfwGetKey(*m_windowRef, GLFW_KEY_LEFT))
    {
		*m_viewRef = glm::translate(*m_viewRef, (float)g_mainTimer.deltaTime * 20.0f * glm::vec3{ 0.1f, 0.0f, 0.0f });
    }
}
