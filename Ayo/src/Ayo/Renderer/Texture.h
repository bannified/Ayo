#pragma once

#include "assimp/material.h"

namespace Ayo
{
    enum class TextureType
    {
        DiffuseTexture, SpecularTexture, NormalTexture, HeightTexture, INVALID
    };


    class Texture
    {
    public:
        Texture();
        virtual ~Texture();

        TextureType type;
        std::string path;

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
                case aiTextureType_HEIGHT:
                    return TextureType::NormalTexture;
                case aiTextureType_AMBIENT:
                    return TextureType::HeightTexture;
                default:
                    AYO_CORE_WARN("Trying to load an unsupported texture: {0}", type);
                    return TextureType::INVALID;
            }
        }

        inline std::string GetTextureName() {
            switch (type) {
            case TextureType::DiffuseTexture:
                return "diffuse";
            case TextureType::SpecularTexture:
                return "specular";
            case TextureType::NormalTexture:
                return "normal";
            case TextureType::HeightTexture:
                return "height";
            default:
                AYO_CORE_WARN("Trying to USE an unsupported texture");
            }
            return "";
        }
    };
}

