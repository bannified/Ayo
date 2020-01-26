#include "ayopch.h"
#include "PointLightSource.h"

#include "Ayo/Renderer/Shader.h"
#include "Ayo/Renderer/Renderer.h"

Ayo::PointLightSource::PointLightSource(const Vector3 ambient, const Vector3 diffuse, const Vector3 specular, const float intensity, 
                                        const float constantAttenuation /*= 1.0f*/, const float linearAttentuation /*= 0.09f*/, const float quadraticAttenuation /*= 0.032f*/)
    : LightSource(ambient, diffuse, specular, intensity),
    p_ConstantAttenuation(constantAttenuation), p_LinearAttenuation(linearAttentuation), p_QuadraticAttenuation(quadraticAttenuation) 
{
    BufferLayout m_Layout = {
            {
                ShaderDataType::Float3, "a_Position"
            }
    };

    // Setup buffers
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<IndexBuffer> indexBuffer;

    m_VertexArray = VertexArray::Create();

    /* Vertices */
    float vertices[] = {
        // Vertices
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
    };

    vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

    vertexBuffer->SetLayout(m_Layout);

    /* Indices */
    unsigned int indices[] = { 0,  1,      2,      2,      3,      0,
                                4,  4 + 1,  4 + 2,  4 + 2,  4 + 3,  4,
                                8,  8 + 1,  8 + 2,  8 + 2,  8 + 3,  8,
                                12, 12 + 1, 12 + 2, 12 + 2, 12 + 3, 12,
                                16, 16 + 1, 16 + 2, 16 + 2, 16 + 3, 16,
                                20, 20 + 1, 20 + 2, 20 + 2, 20 + 3, 20,
    };
    indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

    /* Final Binding to VertexArray */
    m_VertexArray->AddVertexBuffer(vertexBuffer);
    m_VertexArray->SetIndexBuffer(indexBuffer);
}

Ayo::PointLightSource::~PointLightSource()
{

}

void Ayo::PointLightSource::SetupShader(const std::shared_ptr<Shader>& shader)
{
    shader->UpdateFloat3Constant("u_PointLight.position", GetLocalLocation().Get());

    shader->UpdateFloat3Constant("u_PointLight.ambient", p_Color.Get() * p_Intensity);
    shader->UpdateFloat3Constant("u_PointLight.diffuse", p_Diffuse.Get() * p_Intensity);
    shader->UpdateFloat3Constant("u_PointLight.specular", p_Specular.Get() * p_Intensity);

    shader->UpdateFloatConstant("u_PointLight.intensity", p_Intensity);

    shader->UpdateFloatConstant("u_PointLight.constant", p_ConstantAttenuation);
    shader->UpdateFloatConstant("u_PointLight.linear", p_LinearAttenuation);
    shader->UpdateFloatConstant("u_PointLight.quadratic", p_QuadraticAttenuation);
}

void Ayo::PointLightSource::Draw()
{
    m_VertexArray->Bind();
    Renderer::Submit(m_VertexArray);
}
