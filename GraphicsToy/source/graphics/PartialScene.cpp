#include "PartialScene.h"

void CPartialScene::Init(CModel* model, CMaterial* material, CLight* point_light)
{
	SetModel(model);
	SetMaterial(material);
	SetPointLight(point_light);
}

void CPartialScene::UpdateInput()
{
    if(m_controllerToUse != nullptr)
        m_controllerToUse->InputUpdate();
}

void CPartialScene::Update()
{
    m_pointLight->Update();
	m_psRootModel->Update();
    m_basicMaterial->Update();
}

void CPartialScene::Draw()
{
    m_psRootModel->Draw(m_basicMaterial->GetShader());
}

void CPartialScene::Draw(unsigned int shaderID)
{
    m_psRootModel->Draw(shaderID);
}

void CPartialScene::DrawDebugGizmos()
{
    m_psRootModel->DrawDebugGizmos();
}

void CPartialScene::AttachController(CController* controller)
{
    m_controllerToUse = controller;
}

void CPartialScene::Translate(const glm::vec3 translation)
{
    glm::mat4 model;
    model = glm::translate(model, translation);
    m_psRootModel->SetModelMat(model);
}

CPartialScene& CPartialScene::operator=(CPartialScene& other)
{
	this->m_pointLight = &other.GetPointLight();
	this->m_psRootModel = &other.GetModel();
	this->m_basicMaterial = &other.GetMaterial();
	this->m_controllerToUse = nullptr;
	this->m_mainProjectionMatrix = other.Projection();
	this->m_name = GenerateDefaultName();

	return *this;
}
