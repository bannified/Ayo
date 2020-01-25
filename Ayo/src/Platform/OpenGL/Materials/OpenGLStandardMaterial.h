#pragma once

#include "Ayo/Renderer/Materials/StandardMaterial.h"

namespace Ayo
{
    class OpenGLStandardMaterial : public StandardMaterial
    {
    public:
        OpenGLStandardMaterial(const Vector3& baseColor,
                               const std::shared_ptr<Texture>& ambientMap,
                               const std::shared_ptr<Texture>& diffuseMap,
                               const std::shared_ptr<Texture>& specularMap,
                               const float shininess);

        ~OpenGLStandardMaterial();
    protected:
        virtual void SetShaderProperties(Shader& shader) override;

    };
}
