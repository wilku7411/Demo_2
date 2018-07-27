#include "Model.h"

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

#include "stb_image.h"

CModel::CModel(const std::string& path, bool gamma /*= false*/)
	:
	m_gammaCorrection(gamma),
	transformOrigin(COriginGizmo()),
    m_objectColor(glm::vec3{0.1f, 0.3f, 0.1f})
{
    loadModel(path);
	m_model = glm::mat4(1.0f);
}

CModel::CModel(const CModel& other)
{
    *this = other;
}

void CModel::Update()
{
	transformOrigin.Update(m_view, m_model);
	Notify();
}

void CModel::Draw(CMaterial material)
{
    Draw(material.GetShader());
}

void CModel::Draw(CShader* shader)
{
    for (unsigned int i = 0; i < m_meshes.size(); i++)
        m_meshes[i].Draw(*shader);
}

void CModel::Draw(unsigned int shaderID)
{
    for (unsigned int i = 0; i < m_meshes.size(); i++)
        m_meshes[i].Draw(shaderID);
}

void CModel::DrawDebugGizmos()
{
	transformOrigin.Draw();
}

void CModel::Notify()
{
	if(m_observers.size() != 0)
	{
		for (auto sub : m_observers)
		{
			sub->UpdateModelMatrix(m_model);
			sub->UpdateViewMatrix(m_view);
			sub->UpdateObjectColor(GetObjectColor());
		}
	}
}

CModel& CModel::operator=(const CModel& rhs)
{
    this->m_textures = rhs.m_textures;
    this->m_directory = rhs.m_directory;
	loadModel(m_directory);
    
    this->SetObjectColor(rhs.GetObjectColor());

    this->m_view = rhs.m_view;
    this->m_model = rhs.m_model;

    this->transformOrigin = rhs.transformOrigin;
    this->m_gammaCorrection = rhs.m_gammaCorrection;

	return *this;
}

void CModel::loadModel(const std::string &path)
{
	Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs );
 
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    
    m_directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void CModel::processNode(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
    }
  
	for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

}

CMesh CModel::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<SVertexData> vertices;
    std::vector<unsigned int> indices;
    
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        SVertexData vertex;
        glm::vec3 vector; 
                          
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
		/*
		 *
		 * TODO : checking meshes vertices to update extents
		 *
		 **/

        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;
        
        // texture coordinates
        if (mesh->mTextureCoords[0]) 
        {
            glm::vec2 vec;
			// as for now, no support for multiple textures 
			vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.uvs = vec;
        }
        else
        {
            vertex.uvs = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    return CMesh(vertices, indices);
}
   
std::vector<STexture> CModel::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<STexture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        
        bool skip = false;
        for (unsigned int j = 0; j < m_textures.size(); j++)
        {
            if (std::strcmp(m_textures[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(m_textures[j]);
                skip = true; 
                break;
            }
        }
        if (!skip)
        {   
            STexture texture;
            texture.id = TextureFromFile(str.C_Str(), this->m_directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            m_textures.push_back(texture);  
        }
    }
    return textures;
}

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma)
{
	std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}