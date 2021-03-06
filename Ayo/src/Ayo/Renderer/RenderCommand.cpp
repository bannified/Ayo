#include "ayopch.h"
#include "RenderCommand.h"

namespace Ayo {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

	void RenderCommand::SetClearColor(const glm::vec4 color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	void RenderCommand::Clear()
	{
		s_RendererAPI->Clear();
	}

	void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		s_RendererAPI->DrawIndexed(vertexArray);
	}

    void RenderCommand::SetWireframeMode(bool isWireframeMode)
    {
        s_RendererAPI->SetWireframeMode(isWireframeMode);
    }

    void RenderCommand::BeginScene()
    {
        s_RendererAPI->BeginScene();
    }

    void RenderCommand::EndScene()
    {
        s_RendererAPI->EndScene();
    }

}
