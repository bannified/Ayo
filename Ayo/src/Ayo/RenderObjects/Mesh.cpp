#include "ayopch.h"
#include "Mesh.h"

#include "Ayo/Renderer/RenderCommand.h"
#include "Ayo/Renderer/Renderer.h"

#include "glad/glad.h"

Ayo::Mesh::~Mesh()
{

}

Ayo::Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, std::vector<std::shared_ptr<Texture>> textures)
    : m_Vertices(vertices), m_Indices(indices), m_Textures(textures) 
{
    m_VertexArray = Ayo::VertexArray::Create();
    SetupMesh();
}

void Ayo::Mesh::Draw(const std::shared_ptr<Shader>& shader)
{
    m_VertexArray->Bind();

    for (unsigned int i = 0; i < m_Textures.size(); i++) {
        const std::shared_ptr<Texture>& tex = m_Textures[i];
        if (tex->type == TextureType::DiffuseTexture) {
            std::string texName = tex->GetTextureName();
            shader->AddTexture("u_StandardMaterial." + tex->GetTextureName(), tex);
            break;
        }
    }

    Renderer::Submit(m_VertexArray);
    m_VertexArray->Unbind();
}

void Ayo::Mesh::SetupMesh()
{
    std::shared_ptr<VertexBuffer> vertexBuffer = Ayo::VertexBuffer::Create(&m_Vertices[0], m_Vertices.size() * sizeof(Vertex));

    /* Layout */
    Ayo::BufferLayout layout = {
        { Ayo::ShaderDataType::Float3, "a_Position"},
        { Ayo::ShaderDataType::Float3, "a_Normal"},
        { Ayo::ShaderDataType::Float2, "a_TexCoord"}
    };

    vertexBuffer->SetLayout(layout);

    std::shared_ptr<IndexBuffer> indexBuffer = Ayo::IndexBuffer::Create(&m_Indices[0], m_Indices.size());
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    m_VertexArray->SetIndexBuffer(indexBuffer);
}
