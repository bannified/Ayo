#include "ayopch.h"
#include "Model.h"

#include "Ayo/Renderer/Texture.h"
#include "Ayo/Renderer/Materials/StandardMaterial.h"

#include "glm/glm.hpp"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

Ayo::Model::~Model()
{

}

void Ayo::Model::Draw(const std::shared_ptr<Shader>& shader)
{
    for (unsigned int i = 0; i < m_Meshes.size(); i++) {
        m_Meshes[i]->Draw(shader);
    }
}

Ayo::Model::Model(const std::string& path)
{
    LoadModelByPath(path);
}

void Ayo::Model::LoadModelByPath(const std::string& path)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);

    // error if there's no scene, it is incomplete, or it doesn't have a root node.
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        AYO_CORE_ERROR("ERROR::ASSIMP::{0}", importer.GetErrorString());
    }

    m_Directory = path.substr(0, path.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene);
}

void Ayo::Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    // process the node's meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        unsigned int meshIndex = node->mMeshes[i];
        aiMesh* mesh = scene->mMeshes[meshIndex];
        m_Meshes.push_back(ProcessMesh(mesh, scene));
    }

    // recursively process all of its child nodes.
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}

std::shared_ptr<Ayo::Mesh> Ayo::Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    vertices.reserve(mesh->mNumVertices);

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vector3 position = Vector3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        Vector3 normal = Vector3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

        if (mesh->mTextureCoords[0]) {
            glm::vec2 texCoord(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            Vertex vertex(position, normal, texCoord);
            vertices.push_back(vertex);
        }
        else {
            glm::vec2 texCoord(0.0f);
            Vertex vertex(position, normal, texCoord);
            vertices.push_back(vertex);
        }
    }

    std::vector<unsigned int> indices;
    if (mesh->mNumFaces > 0) {
        indices.reserve(mesh->mNumFaces * mesh->mFaces[0].mNumIndices);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        const aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    //unsigned int materialIndex = 0;
    std::vector<std::shared_ptr<Texture>> textures;
    

    std::shared_ptr<Texture> diffuse, specular;

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        //materialIndex = mesh->mMaterialIndex;
        std::vector<std::shared_ptr<Texture>> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
        if (diffuseMaps.size() > 0) {
            diffuse = diffuseMaps[0];
        }
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<std::shared_ptr<Texture>> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR);
        if (specularMaps.size() > 0) {
            specular = specularMaps[0];
        }
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        std::vector<std::shared_ptr<Texture>> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

        std::vector<std::shared_ptr<Texture>> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    }

    std::shared_ptr<Ayo::StandardMaterial> mat = Ayo::StandardMaterial::Create(Vector3(1.0f), diffuse, specular, 0.032f);

    std::shared_ptr<Ayo::Mesh> ayoMesh = std::make_shared<Ayo::Mesh>(vertices, indices, mat);

    return ayoMesh;
}

std::vector<std::shared_ptr<Ayo::Texture>> Ayo::Model::LoadMaterialTextures(aiMaterial* material, aiTextureType type)
{
    unsigned int numTextures = material->GetTextureCount(type);

    std::vector<std::shared_ptr<Ayo::Texture>> result;
    result.reserve(numTextures);

    for (unsigned int i = 0; i < numTextures; i++) {
        aiString str;
        material->GetTexture(type, i, &str);
        auto resultTex = m_TextureIndexToLoadedTextureMap.find(str.C_Str());

        if (resultTex != m_TextureIndexToLoadedTextureMap.end()) {
            // texture already loaded
            result.push_back(resultTex->second);
        }
        else {
            // load texture
            const std::string texturePath = m_Directory + '/' + str.C_Str();
            std::shared_ptr<Texture> tex = Texture::Create(texturePath);
            tex->type = Texture::GetTextureType(type);
            m_TextureIndexToLoadedTextureMap.insert_or_assign(str.C_Str(), tex);
            result.push_back(tex);
        }

    }

    return result;
}
