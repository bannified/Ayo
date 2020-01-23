#pragma once

#include "LightSource.h"

#include "glm/fwd.hpp"

namespace Ayo
{
    class BufferLayout;
    class VertexArray;

    class DirectionalLightSource : public LightSource
    {
    public:
        ~DirectionalLightSource();

        DirectionalLightSource(glm::vec3 color, float intensity);

        virtual void SetupShader(const std::shared_ptr<Shader>& shader) override;

        virtual void Draw() override;

    private:
        std::shared_ptr<BufferLayout> m_Layout;
        std::shared_ptr<VertexArray> m_VertexArray;
    };
}

