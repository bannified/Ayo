#pragma once
#include "ayopch.h"
#include "Ayo/Events/Event.h"

namespace Ayo {
	class AYO_API Layer
	{
	public:
		Layer(const std::string& name = "AbstractLayer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetach()	{};
		
		virtual void OnUpdate()	{};
		virtual void OnEvent(Event& e) {};

		/* this dynamic method is meant to be defined by client */
		virtual void OnImGuiDraw() {};

		virtual void OnEnable() {};
		virtual void OnDisable() {};

		inline std::string GetName() { return m_DebugName; };

	private:
		bool m_Enabled = true;

		std::string m_DebugName;
	};
}

