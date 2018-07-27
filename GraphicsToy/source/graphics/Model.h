#pragma once

#include "Material.h"
#include "Mesh.h"
#include "OriginGizmo.h"
#include "../UniformChangesEvent.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <unordered_map>
#include <queue>
#include <vector>

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gammaCorrection = false);

class CModel : public IUniformChangesEvent
{
public:
    CModel() = default;
    CModel(const CModel& other);
    CModel(const std::string& path, bool gammaCorrection = false);
	
    virtual ~CModel() = default;

	void Update();

	void Draw(CMaterial material);
	void Draw(CShader* shader);
    void Draw(unsigned int shaderID);
	void DrawDebugGizmos();

    CModel& operator=(const CModel& rhs);

	inline glm::mat4 GetModelMat() const			 { return m_model; };
	inline glm::mat4& GetModelMatRef()				 { return m_model; };
	inline void SetModelMat(const glm::mat4& matrix) { m_model = matrix; };
	
	inline glm::mat4 GetViewMat() const				 { return m_view; };
    inline glm::mat4& GetViewMatRef()                { return m_view; };
    inline void SetViewMat(const glm::mat4& matrix)	 { m_view = matrix; };

	// Interface implementation
	void Notify() override;

	glm::vec3 GetObjectColor() const { return m_objectColor; }
	void SetObjectColor(glm::vec3 val) { m_objectColor = val; }
public:
	COriginGizmo transformOrigin;

private:
    void loadModel(const std::string& path);
    void processNode(aiNode *node, const aiScene *scene);
    CMesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<STexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

private:
    std::vector<STexture> m_textures;
    std::vector<CMesh> m_meshes;

	glm::vec3 m_objectColor;
	
	glm::mat4 m_view, m_model;

    std::string m_directory;
    bool m_gammaCorrection;
};