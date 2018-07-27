#pragma once

#include "Light.h"
#include "Model.h"
#include "../DrawModelCmd.h"

class CScene
{
public:
	CScene()
		:
		m_modelsOnScene(0)
	{}

	void Init();
	void Update();
	void DrawSceneElements();

	void AddModel(const CModel& model);
	void AddLight(const CLight& light);
	void CreateShader(const std::string& vertex_source, const std::string& fragment_source);

private:
	std::vector<CModel> m_modelsOnScene;
	CLight m_point1, m_point2;
	std::vector<CShader*> m_shaders;
	std::vector<ICommand*> m_drawCmd;
};