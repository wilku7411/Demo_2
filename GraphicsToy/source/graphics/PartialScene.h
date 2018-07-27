#pragma once

#include "../IO/Controller.h"
#include "Material.h"
#include "Model.h"
#include "Light.h"

/* The idea behind this class was to create a sort of prefab that would be created out of some basic components, that renderable object might have
   for now, it possesses pointers to: 
 - model, 
 - point,
 - material = shader + uniforms 
 - controller.
   Notice that all of those components are only pointers, PartialScene does not own this resource, so it's important to create all of those beforehand.  
*/
class CPartialScene
{
public:
	CPartialScene()
		:
		m_pointLight(nullptr),
		m_psRootModel(nullptr),
		m_basicMaterial(nullptr),
		m_controllerToUse(nullptr),
		m_name("INVALID NAME")
	{
		m_name = GenerateDefaultName();
		printf("\nCreated empty CPartialScene instance.\n");
        printf("Name: [%s]\n", m_name.c_str());
	};

	inline std::string GenerateDefaultName()
	{
		static unsigned int psNum = 0;
		std::string result("Default scene name, ID : ");
		result += std::to_string(psNum++);
		return result;
	}

	void Init(CModel* model, CMaterial* material, CLight* point_light);
 
	void UpdateInput();
    void Update();
	
	void Draw();
    void Draw(unsigned int shaderID);
    void DrawDebugGizmos();

    void AttachController(CController* controller);
    
	CPartialScene& operator=(CPartialScene& other);

	inline void SetPointLight(CLight* point)	 { m_pointLight = point; };
	inline void SetModel(CModel* model)			 { m_psRootModel = model; };
	inline void SetMaterial(CMaterial* material) { m_basicMaterial = material; };
    inline void Projection(const glm::mat4 val)  { m_mainProjectionMatrix = val; }
	inline void Name(std::string val)			 { 
												 	 printf_s("\nName changed!\n\tPrevious scene name [%s]\n\tCurrent name:[%s]\n", m_name.c_str(), val.c_str()); 
												 	 m_name = val;
												 }

	inline CLight& GetPointLight()	    { return *m_pointLight; };
	inline CModel& GetModel()		    { return *m_psRootModel; };
	inline CMaterial& GetMaterial()     { return *m_basicMaterial; };
    inline glm::mat4 Projection() const { return m_mainProjectionMatrix; }
	inline std::string Name() const		{ return m_name; }

    void Translate(const glm::vec3 translation);

private:
    CLight* m_pointLight;
	CModel* m_psRootModel;
	CMaterial* m_basicMaterial;
    CController* m_controllerToUse;
    glm::mat4 m_mainProjectionMatrix;
    std::string m_name;
};