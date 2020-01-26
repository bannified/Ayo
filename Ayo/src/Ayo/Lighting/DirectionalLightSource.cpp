#include "ayopch.h"
#include "DirectionalLightSource.h"

#include "Ayo/Renderer/VertexArray.h"
#include "Ayo/Renderer/Buffer.h"
#include "Ayo/Renderer/Shader.h"
#include "Ayo/Renderer/Renderer.h"

Ayo::DirectionalLightSource::~DirectionalLightSource()
{

}

Ayo::DirectionalLightSource::DirectionalLightSource(const Vector3 ambient, const Vector3 diffuse, const Vector3 specular, const float intensity)
    : LightSource(ambient, diffuse, specular, intensity) { }

void Ayo::DirectionalLightSource::SetupShader(const std::shared_ptr<Shader>& shader)
{
    shader->UpdateFloat3Constant("u_GlobalDirLight.ambient", p_Color.Get());
    shader->UpdateFloat3Constant("u_GlobalDirLight.diffuse", p_Diffuse.Get());
    shader->UpdateFloat3Constant("u_GlobalDirLight.specular", p_Specular.Get());

    shader->UpdateFloatConstant("u_GlobalDirLight.intensity", p_Intensity);
}

void Ayo::DirectionalLightSource::Draw()
{
    // no draw. since position does not matter.
}
