#include "ayopch.h"
#include "Material.h"

#include "Ayo/Renderer/RendererAPI.h"

void Ayo::Material::SetupShader(const std::shared_ptr<Shader>& shader)
{
    SetShaderProperties(shader);
}
