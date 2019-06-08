#pragma once

#include "Ayo/Layer.h"

namespace Ayo {
	class AYO_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

	private:
		void OnAttach();
		void OnDetach();

		void OnUpdate();
		void OnEvent(Event& e);

		//void OnEnable();
		//void OnDisable();
		float m_Time = 0;

	};
}

