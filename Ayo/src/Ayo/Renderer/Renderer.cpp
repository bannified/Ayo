#include "ayopch.h"
#include "Renderer.h"

namespace Ayo {

	void Renderer::BeginScene()
	{
		// TODO
        RenderCommand::BeginScene();
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray> vertexArray)
	{
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::EndScene()
	{
		//TODO
        RenderCommand::EndScene();
	}

}
