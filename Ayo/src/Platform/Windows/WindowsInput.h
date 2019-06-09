#pragma once

#include "Ayo/Input.h"

namespace Ayo {

	class WindowsInput : public Input
	{
	public:
		WindowsInput();
		virtual ~WindowsInput();

	protected:
		virtual bool IsKeyPressed_Implementation(int keycode) override;

		virtual bool IsMouseButtonPressed_Implementation(int button) override;
		virtual float GetMouseX_Implementation() override;
		virtual float GetMouseY_Implementation() override;
		virtual std::pair<float, float> GetMousePosition_Implementation() override;
	};

}


