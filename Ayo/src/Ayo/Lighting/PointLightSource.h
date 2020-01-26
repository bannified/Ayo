#pragma once

#include "LightSource.h"

#include "Ayo/Renderer/Buffer.h"
#include "Ayo/Renderer/VertexArray.h"

namespace Ayo
{
    class PointLightSource : public LightSource
    {
    public:
        PointLightSource(const Vector3 ambient, const Vector3 diffuse, const Vector3 specular, const float intensity);
        ~PointLightSource();

        virtual void SetupShader(const std::shared_ptr<Shader>& shader) override;

        virtual void Draw() override;

    private:
        std::shared_ptr<BufferLayout> m_Layout;
        std::shared_ptr<VertexArray> m_VertexArray;
    };
}

