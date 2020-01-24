#pragma once

#include "Ayo/Renderer/Material.h"
#include "Ayo/Math/Vector3.h"

namespace Ayo
{

    class StandardMaterial : public Material
    {
    public:
        StandardMaterial(const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, const float shininess);
        ~StandardMaterial();
        
        static std::shared_ptr<StandardMaterial> Create(const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, const float shininess);

    protected:
        /* Ambient Color */
        Vector3 p_Ambient;

        /* Diffuse Color */
        Vector3 p_Diffuse;

        /* Specular Color */
        Vector3 p_Specular;

        /* Specular exponent */
        float p_Shininess;
    };
}
