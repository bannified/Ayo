#pragma once

#include "LightSource.h"

#include "Ayo/Renderer/Buffer.h"
#include "Ayo/Renderer/Shader.h"
#include "Ayo/Renderer/VertexArray.h"

namespace Ayo
{
    class PointLightSource : public LightSource
    {
    public:
        PointLightSource(const Vector3 ambient, const Vector3 diffuse, const Vector3 specular, const float intensity,
                         const float constantAttenuation = 1.0f, const float linearAttentuation = 0.09f, const float quadraticAttenuation = 1.0f);

        ~PointLightSource();

        virtual void SetupShader(const std::shared_ptr<Shader>& shader) override;

        virtual void Draw(const std::shared_ptr<Shader>& shader) override;

    protected:
        float p_ConstantAttenuation;
        float p_LinearAttenuation;
        float p_QuadraticAttenuation;

    private:
        std::shared_ptr<BufferLayout> m_Layout;
        std::shared_ptr<VertexArray> m_VertexArray;
    };
}

