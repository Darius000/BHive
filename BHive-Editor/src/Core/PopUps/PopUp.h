#pragma once

#include "imgui.h"

namespace BHive
{
	class PopUp
	{
	public:
		PopUp(const char* label);

		virtual void OnImGuiRender();
		void OpenPopup();

	protected:
		const char* m_Label;
		bool m_IsOpen = false;
	};
}