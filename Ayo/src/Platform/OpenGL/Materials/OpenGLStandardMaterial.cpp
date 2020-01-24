#include "ayopch.h"
#include "OpenGLStandardMaterial.h"

#include "Ayo/Renderer/Shader.h"

Ayo::OpenGLStandardMaterial::OpenGLStandardMaterial(const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, const float shininess) 
    : Ayo::StandardMaterial(ambient, diffuse, specular, shininess) { }

Ayo::OpenGLStandardMaterial::~OpenGLStandardMaterial()
{

}

void Ayo::OpenGLStandardMaterial::SetShaderProperties(Shader& shader)
{
    shader.UpdateFloat3Constant("u_StandardMaterial.ambient", p_Ambient.Get());
    shader.UpdateFloat3Constant("u_StandardMaterial.diffuse", p_Diffuse.Get());
    shader.UpdateFloat3Constant("u_StandardMaterial.specular", p_Specular.Get());
    shader.UpdateFloatConstant("u_StandardMaterial.shininess", p_Shininess);
}
