#pragma once

namespace Ayo
{

    class Texture
    {
    public:
        Texture();
        virtual ~Texture();

        virtual void Bind(const int textureIndex) const = 0;
        virtual void Unbind() const = 0;

        static std::shared_ptr<Texture> Create(const std::string textureImagePath);
    };
}

