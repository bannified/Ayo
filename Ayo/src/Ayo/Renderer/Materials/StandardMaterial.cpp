#include "ayopch.h"
#include "StandardMaterial.h"

#include "Platform/OpenGL/Materials/OpenGLStandardMaterial.h"

#include "Ayo/Renderer/RendererAPI.h"

Ayo::StandardMaterial::StandardMaterial(const Vector3& baseColor, 
                                        const std::shared_ptr<Texture>& ambientMap,
                                        const std::shared_ptr<Texture>& diffuseMap, 
                                        const std::shared_ptr<Texture>& specularMap, 
                                        const float shininess)
    : p_BaseColor(baseColor), p_AmbientMap(ambientMap), p_DiffuseMap(diffuseMap), p_SpecularMap(specularMap), p_Shininess(shininess) { }

Ayo::StandardMaterial::~StandardMaterial()
{

}

std::shared_ptr<Ayo::StandardMaterial> Ayo::StandardMaterial::Create(const Vector3& baseColor, 
                                                                     const std::shared_ptr<Texture>& ambientMap,
                                                                     const std::shared_ptr<Texture>& diffuseMap,
                                                                     const std::shared_ptr<Texture>& specularMap,
                                                                     const float shininess)
{
    switch (RendererAPI::GetCurrentAPI()) {
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLStandardMaterial>(baseColor, ambientMap, diffuseMap, specularMap, shininess);
        case RendererAPI::API::NONE:
            AYO_CORE_ASSERT(false, "No RendererAPI selected in Renderer.h!");
            return nullptr;
    }

    AYO_CORE_ASSERT(false, "No RendererAPI selected in Renderer.h!");
    return nullptr;
}

