#pragma once

#include "Core.h"
#include "BHive/Object/Object.h"
#include "BHive/Interfaces/Serializable.h"
#include "BHive/Editors/AssetEditor.h"


namespace BHive
{
	class BHive_API BResource : public Object , public ISerializable
	{
	public:
		BResource() = default;
		//BResource(const String& name);

		//virtual bool Load(const String& name, const String& path); 

		virtual void OnDestroyed() override;

		virtual void CreateEditorWindow();
		virtual void CreateContextMenuItems() override;
		virtual unsigned int GetIconData() const;

		//String GetPath() const { return m_Path; }
		//void SetPath(const String& path) { m_Path = path; }

	protected:
		//bool DoesAssetFileExist(String file);

		virtual void OnSave(std::ofstream& resourceFile, const FString& resourceFilePath) override;
		virtual void OnLoad(std::ifstream& resourceFile) override;
		virtual void LoadResource() = 0;

	protected:
		unsigned int m_IconData;
		//String m_Path;

		//Create shared pointer for resource editor
		//create editor class
	};
}