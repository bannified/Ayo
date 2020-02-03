#pragma once

#include "assimp/material.h"

namespace Ayo
{
    enum class TextureType
    {
        DiffuseTexture, SpecularTexture, INVALID
    };


    class Texture
    {
    public:
        Texture();
        virtual ~Texture();

        TextureType type;

        virtual void Bind(const int textureIndex) const = 0;
        virtual void Unbind() const = 0;

        static std::shared_ptr<Texture> Create(const std::string textureImagePath);

        inline static TextureType GetTextureType(const aiTextureType& type)
        {
            switch (type) {
                case aiTextureType_DIFFUSE:
                    return TextureType::DiffuseTexture;
                case aiTextureType_SPECULAR:
                    return TextureType::SpecularTexture;
                default:
                    AYO_CORE_WARN("Trying to load an unsupported texture: {0}", type);
                    return TextureType::INVALID;
            }
        }
    };
}

