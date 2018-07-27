#include "Asteroid.h"



Object::CAsteroid::CAsteroid(const std::string& name, CMaterial* material /*= nullptr*/)
    :
    Super()
{
    Super::Name(name);

    CModel* model = new CModel(asteroid_mesh);
    if (material != nullptr)
    {
        Super::SetMaterial(material);
    }
    else
    {
        CMaterial* material = new CMaterial(asteroid_vs, asteroid_fs);
        Super::SetMaterial(material);
    }

    Super::SetModel(model);
}

Object::CAsteroid::~CAsteroid()
{
	// HACK : for a moment
	// there is a problem with material or shader class
	// more information in commit c32fe17
    //delete &GetModel();
    //delete &GetMaterial();
}

void Object::CAsteroid::Init(glm::mat4 projection, CLight* pointLight)
{
    Super::GetModel().transformOrigin.UpdateMatrices(
        projection, 
        glm::mat4{ 1.0f }, 
        glm::mat4{ 1.0f }
    );

    Super::SetPointLight(pointLight);

    Super::GetModel().Attach(&GetMaterial());
    Super::GetPointLight().Attach(&GetMaterial());
}

void Object::CAsteroid::Update(glm::vec3 attractor)
{
    Super::Update();
    Super::Translate(m_traj.Update());
 
    m_traj.BindAttractor(attractor);

    m_position = glm::vec3{
        this->GetModel().GetModelMat()[3].x,
        this->GetModel().GetModelMat()[3].y,
        this->GetModel().GetModelMat()[3].z
    };
}

void Object::CAsteroid::Draw()
{
    Super::Draw();
}

void Object::CAsteroid::Draw(unsigned int shaderID)
{
    Super::Draw(shaderID);
}

glm::vec3* Object::CAsteroid::GetPosition()
{
    return &m_position;
}
