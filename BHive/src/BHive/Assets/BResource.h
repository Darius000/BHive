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
		BResource() = default;
		BResource(const String& name);

		virtual bool Load(const String& name, const String& path); 

		virtual void OnDestroyed() override;

		virtual void CreateEditorWindow();
		virtual void CreateContextMenuItems() override;
		unsigned int GetData() const { return m_Data; }

		String GetPath() const { return m_Path; }
		void SetPath(const String& path) { m_Path = path; }

	protected:
		bool DoesAssetFileExist(String file);

	protected:
		unsigned int m_Data;
		String m_Path;
	};
}