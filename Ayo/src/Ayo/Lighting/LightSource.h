#pragma once

#include "glm/fwd.hpp"
#include "Ayo/Components/SceneComponent.h"

namespace Ayo
{
    class Shader;

    class LightSource : public SceneComponent
    {
    public:
        LightSource();
        ~LightSource();

        LightSource(glm::vec3 color, float intensity);

        virtual void SetupShader(const std::shared_ptr<Shader>& shader) = 0;

        virtual void Draw() = 0;

    protected:
        glm::vec3 p_Color;
        float p_Intensity;
    };
}
