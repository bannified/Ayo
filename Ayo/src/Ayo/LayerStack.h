#pragma once
#include "ayopch.h"

#include "Ayo/Layer.h"

namespace Ayo {
	
	class AYO_API LayerStack
	{
		using layers = std::vector<Layer*>;

	public:
		LayerStack();
		virtual ~LayerStack();

		void PushLayer(Layer* layer);
		void RemoveLayer(Layer* layer);

		void PushOverlay(Layer* overlay);
		void RemoveOverlay(Layer* overlay);

		inline layers::iterator begin() { return m_Layers.begin(); }
		inline layers::iterator end() { return m_Layers.end(); }
		inline layers::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		inline layers::reverse_iterator rend() { return m_Layers.rend(); }

	private:
		layers m_Layers;
		unsigned int m_TopLayerIndex;

	};

}

