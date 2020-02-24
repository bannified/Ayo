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

        DirectionalLightSource(const Vector3 ambient, const Vector3 diffuse, const Vector3 specular, const float intensity);

        virtual void SetupShader(const std::shared_ptr<Shader>& shader) override;

        virtual void Draw(const std::shared_ptr<Shader>& shader) override;

    };
}

