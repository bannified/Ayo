#include "ayopch.h"
#include "Material.h"

#include "Ayo/Renderer/RendererAPI.h"

void Ayo::Material::SetupShader(Shader& shader)
{
    SetShaderProperties(shader);
}
