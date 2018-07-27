#include "Scene.h"


void CScene::Init()
{
	for (auto model : m_modelsOnScene)
	{
		CModel* ptr = &model;
		m_drawCmd.push_back(new CDrawModelCmd(ptr));
	}
}

void CScene::Update()
{
	if (m_point1.GetUpdateStatus() == true)
		m_point1.Update();
	if (m_point2.GetUpdateStatus() == true)
		m_point2.Update();

	for (auto model : m_modelsOnScene)
	{
		model.Update();
	}
}

void CScene::DrawSceneElements()
{
	for (auto cmd : m_drawCmd)
	{
		cmd->execute();
	}
}

void CScene::AddModel(const CModel& model)
{
	m_modelsOnScene.push_back(model);
}

void CScene::AddLight(const CLight& light)
{
	m_point2 = m_point1;
	m_point1 = light;
}

void CScene::CreateShader(const std::string& vertex_source, const std::string& fragment_source)
{
	m_shaders.push_back(new CShader(vertex_source.c_str(), fragment_source.c_str()));
}
