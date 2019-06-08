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

		void ImGui_ImplGlfw_NewFrame();
		static void ImGui_ImplGlfw_UpdateMousePosAndButtons();
		static void ImGui_ImplGlfw_UpdateMouseCursor();

	};
}

