#include "ayopch.h"
#include "Buffer.h"

#include "Ayo/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Ayo {

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (RendererAPI::GetCurrentAPI()) {
			case RendererAPI::API::OpenGL:
			{
				return std::make_shared<OpenGLVertexBuffer>(vertices, size);
			}
			case RendererAPI::API::NONE:
			{
				AYO_CORE_ASSERT(false, "No RendererAPI selected in Renderer.h!");
				return nullptr;
			}
		}

		AYO_CORE_ASSERT(false, "Invalid RendererAPI selected in Renderer.h!");
		return nullptr;
	}

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (RendererAPI::GetCurrentAPI()) {
			case RendererAPI::API::OpenGL:
			{
				return std::make_shared<OpenGLIndexBuffer>(indices, count);
			}
			case RendererAPI::API::NONE:
			{
				AYO_CORE_ASSERT(false, "No RendererAPI selected in Renderer.h!");
				return nullptr;
			}
		}

		AYO_CORE_ASSERT(false, "Invalid RendererAPI selected in Renderer.h!");
		return nullptr;
	}

}

