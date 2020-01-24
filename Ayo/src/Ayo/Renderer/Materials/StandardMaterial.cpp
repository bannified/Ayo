#include "ayopch.h"
#include "StandardMaterial.h"

#include "Platform/OpenGL/Materials/OpenGLStandardMaterial.h"

#include "Ayo/Renderer/RendererAPI.h"

Ayo::StandardMaterial::StandardMaterial(const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, const float shininess)
    : p_Ambient(ambient), p_Diffuse(diffuse), p_Specular(specular), p_Shininess(shininess) { }

Ayo::StandardMaterial::~StandardMaterial()
{

}

std::shared_ptr<Ayo::StandardMaterial> Ayo::StandardMaterial::Create(const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, const float shininess)
{
    switch (RendererAPI::GetCurrentAPI()) {
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLStandardMaterial>(ambient, diffuse, specular, shininess);
        case RendererAPI::API::NONE:
            AYO_CORE_ASSERT(false, "No RendererAPI selected in Renderer.h!");
            return nullptr;
    }

    AYO_CORE_ASSERT(false, "No RendererAPI selected in Renderer.h!");
    return nullptr;
}

