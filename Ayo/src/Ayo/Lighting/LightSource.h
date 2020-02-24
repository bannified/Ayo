#pragma once

#include "Ayo/Components/SceneComponent.h"

namespace Ayo
{
    class Shader;

    class LightSource : public SceneComponent
    {
    public:
        LightSource();
        ~LightSource();

        LightSource(const Vector3 color, const Vector3 diffuse, const Vector3 specular, const float intensity);

        virtual void SetupShader(const std::shared_ptr<Shader>& shader) = 0;

        virtual void Draw(const std::shared_ptr<Shader>& shader) = 0;

        inline Vector3 GetBaseColor() { return p_Color; }

    protected:
        Vector3 p_Color;
        Vector3 p_Diffuse;
        Vector3 p_Specular;

        float p_Intensity;
    };
}
