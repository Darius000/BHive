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

	class ISerializable : public IInterface
	{
	public:
		virtual void SaveData() = 0;
		virtual void LoadData() = 0;
		virtual void OnLoad(std::ifstream& resourceFile) = 0;
		virtual void OnSave(std::ofstream& resourceFile) = 0;
		virtual std::ofstream GetData() = 0;

		std::ofstream& operator<<(const ISerializable& object)
		{
			return GetData();
		}
	};
}