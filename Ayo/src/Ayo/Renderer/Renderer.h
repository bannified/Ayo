#pragma once

namespace Ayo {

	enum class RendererAPI
	{
		NONE = 0, // headless, server. no rendering required.
		OpenGL = 1,
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetCurrentAPI() { return s_CurrentAPI; }

	private:
		static RendererAPI s_CurrentAPI;
	};

}

