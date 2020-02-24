#include "ayopch.h"
#include "OpenGLTexture.h"
#include "stb_image.h"

#include "glad/glad.h"

Ayo::OpenGLTexture::OpenGLTexture(const std::string textureImagePath)
{
    path = textureImagePath;

    glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureId);

    // Set texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* textureData = stbi_load(textureImagePath.c_str(), &m_Width, &m_Height, &m_NumColorChannels, 0);

    if (textureData) {
        glTextureStorage2D(m_TextureId, 1, GL_RGB8, m_Width, m_Height);
        GLenum format;
        switch (m_NumColorChannels) {
            case 1:
            format = GL_RED;
            case 2:
                format = GL_RG;
                break;
            case 3:
                format = GL_RGB;
                break;
            case 4:
                format = GL_RGBA;
                break;
            default:
                format = GL_RGB;
                break;
        }

        glTextureSubImage2D(m_TextureId, 0, 0, 0, m_Width, m_Height, format, GL_UNSIGNED_BYTE, textureData); // for image formats without alpha channel (.jpg)

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        AYO_CORE_ERROR("Failed to load texture at path {0}", textureImagePath);
    }

    stbi_image_free(textureData);
}

Ayo::OpenGLTexture::~OpenGLTexture()
{
    glDeleteTextures(1, &m_TextureId);
}

void Ayo::OpenGLTexture::Bind(const int textureIndex) const
{
    glBindTextureUnit(textureIndex, m_TextureId);
}

void Ayo::OpenGLTexture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
