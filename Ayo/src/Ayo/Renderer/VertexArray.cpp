#include "ayopch.h"
#include "Ayo/Renderer/Renderer.h"
#include "VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Ayo {

	VertexArray::~VertexArray()
	{

	}

	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetCurrentAPI()) {
			case RendererAPI::API::OpenGL:
			{
				return std::make_shared<OpenGLVertexArray>();
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