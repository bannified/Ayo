#pragma once

#include "Ayo/RenderObjects/Vertex.h"
#include "Ayo/Renderer/Texture.h"
#include "Ayo/Renderer/Shader.h"
#include "Ayo/Renderer/Material.h"

#include "Ayo/Renderer/VertexArray.h"

namespace Ayo
{

    class Mesh
    {
    public:
        ~Mesh();

        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, std::vector<std::shared_ptr<Texture>> textures);

        void Draw(const std::shared_ptr<Shader>& shader);

        inline void SetMaterialIndex(unsigned int index) { m_MaterialIndex = index; }

    private:

        std::shared_ptr<VertexArray> m_VertexArray;

        std::vector<Vertex> m_Vertices;
        std::vector<unsigned int> m_Indices;
        std::vector<std::shared_ptr<Texture>> m_Textures;

        std::vector<Material> m_MaterialSlots;

        unsigned int m_MaterialIndex;

        void SetupMesh();
    };
}

