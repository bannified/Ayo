#pragma once
#include "Ayo/Renderer/Texture.h"

namespace Ayo
{
    class OpenGLTexture : public Texture
    {
    public:
        OpenGLTexture(const std::string textureImagePath);
        virtual ~OpenGLTexture();

        virtual void Bind(const int textureIndex) const override;

        virtual void Unbind() const override;

    private:
        unsigned int m_TextureId;
        int m_Height;
        int m_Width;
        int m_NumColorChannels;
    };
}

