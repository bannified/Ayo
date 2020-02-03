#include "ayopch.h"
#include "OpenGLStandardMaterial.h"

#include "Ayo/Renderer/Shader.h"

Ayo::OpenGLStandardMaterial::OpenGLStandardMaterial(const Vector3& baseColor, 
                                                    const std::shared_ptr<Texture>& diffuseMap, 
                                                    const std::shared_ptr<Texture>& specularMap, 
                                                    const float shininess)
    : Ayo::StandardMaterial(baseColor, diffuseMap, specularMap, shininess) { }

Ayo::OpenGLStandardMaterial::~OpenGLStandardMaterial()
{

}

void Ayo::OpenGLStandardMaterial::SetShaderProperties(const std::shared_ptr<Shader>& shader)
{
    shader->UpdateFloat3Constant("u_StandardMaterial.color", p_BaseColor.Get());

    shader->AddTexture("u_StandardMaterial.diffuse", p_DiffuseMap);
    shader->AddTexture("u_StandardMaterial.specular", p_SpecularMap);

    //shader.UpdateFloat3Constant("u_StandardMaterial.ambient", p_AmbientColor.Get());
    //shader.UpdateFloat3Constant("u_StandardMaterial.diffuse", p_Diffuse.Get());
    //shader.UpdateFloat3Constant("u_StandardMaterial.specular", p_Specular.Get());

    shader->UpdateFloatConstant("u_StandardMaterial.shininess", p_Shininess);
}
