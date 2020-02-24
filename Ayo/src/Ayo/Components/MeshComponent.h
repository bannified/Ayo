#pragma once

#include "Ayo/Components/SceneComponent.h"

#include "Ayo/RenderObjects/Model.h"

namespace Ayo {

    class MeshComponent : public SceneComponent
    {

    public:
        MeshComponent(const std::string& meshPath);

        void SetMesh(const std::string& path);

        void Draw(const std::shared_ptr<Shader>& shader);

    private:
        std::shared_ptr<Model> m_Model;

        std::vector<std::shared_ptr<Material>> m_AllMaterials;

        void InitModel();
    };

}

