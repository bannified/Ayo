#include "ayopch.h"
#include "OpenGLTexture.h"
#include "stb_image.h"

#include "glad/glad.h"

Ayo::OpenGLTexture::OpenGLTexture(const std::string textureImagePath)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureId);

    // Set texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* textureData = stbi_load(textureImagePath.c_str(), &m_Width, &m_Height, &m_NumColorChannels, 0);

    if (textureData) {
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        glTextureStorage2D(m_TextureId, 1, GL_RGB8, m_Width, m_Height);
        glTextureSubImage2D(m_TextureId, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, textureData); // for image formats without alpha channel (.jpg)
        //glTextureSubImage2D(m_TextureId, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, textureData); // for image formats with alpha channel (.png)
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
