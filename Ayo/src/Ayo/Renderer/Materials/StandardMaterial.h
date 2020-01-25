#pragma once

#include "Ayo/Renderer/Material.h"
#include "Ayo/Math/Vector3.h"
#include "Ayo/Renderer/Texture.h"

namespace Ayo
{

    class StandardMaterial : public Material
    {
    public:
        StandardMaterial(const Vector3& baseColor,
                         const std::shared_ptr<Texture>& ambientMap,
                         const std::shared_ptr<Texture>& diffuseMap,
                         const std::shared_ptr<Texture>& specularMap,
                         const float shininess);

        ~StandardMaterial();
        
        static std::shared_ptr<StandardMaterial> Create(const Vector3& baseColor, 
                                                        const std::shared_ptr<Texture>& ambientMap,
                                                        const std::shared_ptr<Texture>& diffuseMap, 
                                                        const std::shared_ptr<Texture>& specularMap,
                                                        const float shininess);

    protected:
        /* Base Color, ambient color */
        Vector3 p_BaseColor;

        /* Ambient Map */
        std::shared_ptr<Texture> p_AmbientMap;

        /* Diffuse Map */
        std::shared_ptr<Texture> p_DiffuseMap;

        /* Specular Map */
        std::shared_ptr<Texture> p_SpecularMap;

        /* Specular exponent */
        float p_Shininess;
    };
}
