#include "ayopch.h"
#include "StandardMaterial.h"

#include "Ayo/Renderer/RendererAPI.h"

Ayo::StandardMaterial::StandardMaterial(const Vector3& baseColor, 
                                        const std::shared_ptr<Texture>& diffuseMap, 
                                        const std::shared_ptr<Texture>& specularMap, 
                                        const float shininess)
    : p_BaseColor(baseColor), p_DiffuseMap(diffuseMap), p_SpecularMap(specularMap), p_Shininess(shininess) { }

Ayo::StandardMaterial::~StandardMaterial()
{

}

std::shared_ptr<Ayo::StandardMaterial> Ayo::StandardMaterial::Create(const Vector3& baseColor, 
                                                                     const std::shared_ptr<Texture>& diffuseMap,
                                                                     const std::shared_ptr<Texture>& specularMap,
                                                                     const float shininess)
{
    return std::make_shared<Ayo::StandardMaterial>(baseColor, diffuseMap, specularMap, shininess);
}

void Ayo::StandardMaterial::SetBaseColor(Vector3 color)
{
    p_BaseColor = color;
}

void Ayo::StandardMaterial::SetShaderProperties(const std::shared_ptr<Shader>& shader)
{
    shader->UpdateFloat3Constant("u_StandardMaterial.baseColor", p_BaseColor.Get());

    shader->AddTexture("u_StandardMaterial.diffuse", p_DiffuseMap);
    shader->AddTexture("u_StandardMaterial.specular", p_SpecularMap);

    shader->UpdateFloatConstant("u_StandardMaterial.shininess", p_Shininess);
}

