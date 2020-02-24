#pragma once

#include "Ayo/RenderObjects/Mesh.h"
#include "Ayo/Renderer/Material.h"
#include "Ayo/Renderer/Shader.h"
#include "assimp/scene.h"

namespace Ayo
{

    class Model
    {
    public:
        ~Model();

        Model(const std::string& path);

        void Draw(const std::shared_ptr<Shader>& shader);

    private:

        /* Model Data */
        std::unordered_map<std::string, std::shared_ptr<Texture>> m_TextureIndexToLoadedTextureMap;

        std::vector<std::shared_ptr<Mesh>> m_Meshes;
        std::string m_Directory;

        void LoadModelByPath(const std::string& path);
        void ProcessNode(aiNode* node, const aiScene* scene);
        std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<std::shared_ptr<Texture>> LoadMaterialTextures(aiMaterial* material, aiTextureType type);
    };
}

