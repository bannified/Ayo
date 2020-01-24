#pragma once

#include "Ayo/Renderer/Materials/StandardMaterial.h"

namespace Ayo
{
    class OpenGLStandardMaterial : public StandardMaterial
    {
    public:
        OpenGLStandardMaterial(const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, const float shininess);
        ~OpenGLStandardMaterial();
    protected:
        virtual void SetShaderProperties(Shader& shader) override;

    };
}
