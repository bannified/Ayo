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

        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::shared_ptr<Material>& material);

        void Draw(const std::shared_ptr<Shader>& shader);

        inline void SetMaterial(const std::shared_ptr<Material>& material) { this->m_Material = material; }

    private:

        std::shared_ptr<VertexArray> m_VertexArray;
        std::vector<Vertex> m_Vertices;
        std::vector<unsigned int> m_Indices;

        std::shared_ptr<Material> m_Material;

        void SetupMesh();
    };
}

