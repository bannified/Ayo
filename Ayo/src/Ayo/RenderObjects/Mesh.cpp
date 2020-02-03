#include "ayopch.h"
#include "Mesh.h"

#include "Ayo/Renderer/RenderCommand.h"

#include "glad/glad.h"

Ayo::Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, std::vector<std::shared_ptr<Texture>> textures)
    : m_Vertices(vertices), m_Indices(indices), m_Textures(textures) 
{
    SetupMesh();
}

void Ayo::Mesh::Draw(const Shader& shader)
{
    m_VertexArray->Bind();

    /*for (unsigned int i = 0; i < m_Textures.size(); i++) {
        const Texture& tex = m_Textures[i];
    }*/

    RenderCommand::DrawIndexed(m_VertexArray);
}

void Ayo::Mesh::SetupMesh()
{
    std::shared_ptr<VertexBuffer> vertexBuffer = Ayo::VertexBuffer::Create(&m_Vertices[0], sizeof(m_Vertices));

    /* Layout */
    Ayo::BufferLayout layout = {
        { Ayo::ShaderDataType::Float3, "a_Position"},
        { Ayo::ShaderDataType::Float3, "a_Normal"},
        { Ayo::ShaderDataType::Float2, "a_TexCoord"}
    };

    vertexBuffer->SetLayout(layout);
}
