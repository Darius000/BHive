#pragma once

#include "Core.h"
#include "Object.h"
#include "Interfaces/Serializable.h"
#include "Editors/AssetEditor.h"


namespace BHive
{
	class BHive_API BResource : public Object
	{
	public:
		BResource();
		BResource(const String& name);

		virtual bool Load(const String& name, const String& path); //Load the asset

		virtual void OnDestroyed() override;

		virtual void CreateEditorWindow();
		virtual void CreateContextMenuItems() override;
		unsigned int GetData() const { return m_Data; }

		String GetPath() const { return m_Path; }
		void SetPath(const String& path) { m_Path = path; }

	protected:
		unsigned int m_Data;

	private:
		String m_Path;
	};
}