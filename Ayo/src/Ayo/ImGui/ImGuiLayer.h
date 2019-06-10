#pragma once

#include "Ayo/Layer.h"

namespace Ayo {
	class AYO_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
		virtual void OnImGuiDraw() override; 
	private:	
		float m_Time = 0;

	};
}

