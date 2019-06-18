#include "ayopch.h"
#include "Buffer.h"

#include "Ayo/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Ayo {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetCurrentAPI()) {
			case RendererAPI::OpenGL:
			{
				return new OpenGLVertexBuffer(vertices, size);
			}
			case RendererAPI::NONE:
			{
				AYO_CORE_ASSERT(false, "No RendererAPI selected in Renderer.h!");
				return nullptr;
			}
		}

		AYO_CORE_ASSERT(false, "Invalid RendererAPI selected in Renderer.h!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetCurrentAPI()) {
			case RendererAPI::OpenGL:
			{
				return new OpenGLIndexBuffer(indices, count);
			}
			case RendererAPI::NONE:
			{
				AYO_CORE_ASSERT(false, "No RendererAPI selected in Renderer.h!");
				return nullptr;
			}
		}

		AYO_CORE_ASSERT(false, "Invalid RendererAPI selected in Renderer.h!");
		return nullptr;
	}

}

