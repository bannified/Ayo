#pragma once

namespace Ayo {

	enum class MouseButton : unsigned char
	{
		LEFT = 0,
		RIGHT = 1,
		MIDDLE = 2,
		BACK = 3,
		FORWARD = 4
	};

	class AYO_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressed_Implementation(keycode); }

		inline static bool IsMouseButtonPressed(MouseButton button) { return s_Instance->IsMouseButtonPressed_Implementation(button); }
		inline static float GetMouseX() { return s_Instance->GetMouseX_Implementation(); }
		inline static float GetMouseY() { return s_Instance->GetMouseY_Implementation(); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePosition_Implementation(); }

	protected:
		virtual bool IsMouseButtonPressed_Implementation(MouseButton button) = 0;
		virtual bool IsKeyPressed_Implementation(int keycode) = 0;
		virtual float GetMouseX_Implementation() = 0;
		virtual float GetMouseY_Implementation() = 0;
		virtual std::pair<float, float> GetMousePosition_Implementation() = 0;

		Input() { };
	private:
		static std::shared_ptr<Input> s_Instance;
		
	};

}