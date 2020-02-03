#pragma once

#include "Ayo/Math/Vector3.h"
#include "glm/glm.hpp"

namespace Ayo
{
    struct Vertex
    {
        Vector3 Position;
        Vector3 Normal;
        glm::vec2 TexCoords;

        Vertex(Vector3 position, Vector3 normal, glm::vec2 texCoords) :
            Position(position), Normal(normal), TexCoords(texCoords) { }
    };
}