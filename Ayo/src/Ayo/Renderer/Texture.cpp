#include "ayopch.h"
#include "Texture.h"

#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLTexture.h"

Ayo::Texture::Texture()
{

}

Ayo::Texture::~Texture()
{

}

std::shared_ptr<Ayo::Texture> Ayo::Texture::Create(const std::string textureImagePath)
{
    switch (RendererAPI::GetCurrentAPI()) {
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture>(textureImagePath);
        case RendererAPI::API::NONE:
            AYO_CORE_ASSERT(false, "No RendererAPI selected in Renderer.h!");
            return nullptr;
    }

    AYO_CORE_ASSERT(false, "No RendererAPI selected in Renderer.h!");
    return nullptr;
}
