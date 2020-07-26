#pragma once

namespace BHive
{
	class BHive_API Input
	{
	public:
		static bool IsKeyPressed(int keycode) ;
		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}