#pragma once

#include "Ayo/Components/SceneComponent.h"

#include "Ayo/RenderObjects/Mesh.h"

namespace Ayo {

    class MeshComponent : public SceneComponent
    {

    public:
        MeshComponent(const std::string& meshPath);

        void SetMesh(const std::string& path);
    private:
        std::shared_ptr<Mesh> m_Mesh;
    };

}

