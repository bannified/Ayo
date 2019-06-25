#include "ayopch.h"
#include "Renderer.h"

namespace Ayo {

	void Renderer::BeginScene()
	{
		// TODO
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray> vertexArray)
	{
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::EndScene()
	{
		//TODO
	}

}
