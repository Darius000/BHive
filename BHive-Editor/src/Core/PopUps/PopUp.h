#pragma once

#include "imgui.h"

namespace BHive
{
	class PopUp 
	{
	public:
		PopUp() = default;
		PopUp(const std::string& label, const uint64& id);

		virtual void OnRender();
		
		bool IsOpen() const { return m_IsOpen; }
		uint64 GetID() const { return m_ID; }

	protected:
		std::string m_Label;
		bool m_IsOpen = true;
		bool m_IsRendering = false;
		uint64 m_ID;
	};
}