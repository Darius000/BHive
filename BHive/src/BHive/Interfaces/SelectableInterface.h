#pragma once

#include "Interface.h"

namespace BHive
{
	class ISelectable : public IInterface
	{
	public:
		virtual bool IsSelected() = 0;
		virtual void Select(bool selected) = 0;
		virtual void ToggleSelection() = 0;
		virtual bool IsActive() = 0;
		virtual void SetActive(bool active = true) = 0;
	};
}