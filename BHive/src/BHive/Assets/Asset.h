#pragma once

#include "Core.h"
#include "Object.h"
#include "Interfaces/Serializable.h"
#include "Editors/AssetEditor.h"


namespace BHive
{
	class BHive_API Asset : public Object, public ISerializable
	{
	public:
		Asset();
		Asset(String name);

		virtual bool Load(std::string name, std::string path); //Load the asset

		virtual void OnDestroyed() override;

		virtual void CreateEditorWindow();
		virtual void CreateContextMenuItems() override;
		unsigned int GetData() const { return m_Data; }

		String GetPath() const { return m_Path; }
		void SetPath(String path) { m_Path = path; }

		virtual void OnSave(std::fstream& file) override;


		virtual void OnLoad(std::fstream& file) override;

	protected:
		unsigned int m_Data;

		String m_Path;
	};
}