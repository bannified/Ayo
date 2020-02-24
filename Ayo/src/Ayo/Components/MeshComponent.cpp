#include "ayopch.h"
#include "MeshComponent.h"
#include "glm/glm.hpp"

Ayo::MeshComponent::MeshComponent(const std::string& meshPath)
{
    SetMesh(meshPath);
}

void Ayo::MeshComponent::SetMesh(const std::string& path)
{
    m_Model = std::make_shared<Model>(path);
    InitModel();
}

void Ayo::MeshComponent::Draw(const std::shared_ptr<Shader>& shader)
{
    shader->Bind();

    shader->UpdateMat4Constant("u_ModelMatrix", GetRelativeTransform());
    shader->UpdateMat4Constant("u_NormalMatrix", glm::transpose(glm::inverse(GetRelativeTransform())));

    m_Model->Draw(shader);
}

void Ayo::MeshComponent::InitModel()
{
    m_AllMaterials.clear();
    if (m_Model) {
        auto meshes = m_Model->GetMeshes();
        m_AllMaterials.reserve(meshes.size());

        for (auto mesh : meshes) {
            m_AllMaterials.push_back(mesh->GetMaterial());
        }
    }
}
