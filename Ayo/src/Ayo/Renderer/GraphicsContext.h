#pragma once

namespace Ayo {

	class AYO_API GraphicsContext
	{
	public:
		GraphicsContext();
		virtual ~GraphicsContext();

		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;
		virtual void Shutdown() = 0;
	};
}



