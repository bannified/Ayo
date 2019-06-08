#include "ayopch.h"
#include "LayerStack.h"

namespace Ayo {

	LayerStack::LayerStack()
	{
		m_TopLayerPos = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		// free layers in memory.
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_TopLayerPos = m_Layers.emplace(m_TopLayerPos, layer);
		layer->OnAttach();
	}

	void LayerStack::RemoveLayer(Layer* layer)
	{
		layers::iterator toRemove = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (toRemove != m_Layers.end()) { // valid layer is found within vector
			m_Layers.erase(toRemove);
			--m_TopLayerPos;
		}

		layer->OnDetach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::RemoveOverlay(Layer* overlay)
	{
		layers::iterator toRemove = std::find(m_Layers.begin(), m_Layers.end(), overlay);

		if (toRemove != m_Layers.end()) { // valid overlay is found within vector
			m_Layers.erase(toRemove);
		}

		overlay->OnDetach();
	}
}
