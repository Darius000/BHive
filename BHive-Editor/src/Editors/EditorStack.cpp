#include "EditorStack.h"
#include "Layers/ImGuiLayer.h"
#include "TextureEditor.h"
namespace BHive
{

	EditorStack::EditorStack()
	{
		
	}

	EditorStack::~EditorStack()
	{
		
	}

	void EditorStack::OpenEditor(Ref<ImGuiPanel> editor)
	{
		m_Editors.emplace_back(editor);
	}

	void EditorStack::OnImGuiRender()
	{
		for (auto it = m_Editors.begin(); it != m_Editors.end();)
		{
			if ((*it)->m_isOpen)
			{
				(*it)->OnImGuiRender();
				++it;
			}
			else
			{
				it = m_Editors.erase(it);
			}
		}
	}

	void EditorStack::OpenEditorForAsset(Asset* asset)
	{
		switch (asset->GetAssetType())
		{
		default:
			break;
		case AssetType::None:
			break;
		case AssetType::Texture:
			m_Editors.emplace_back(new TextureEditor((Texture2D*)asset));
		case AssetType::Shader:
			break;
		case AssetType::Mesh:
			break;
		}
	}

	Editors EditorStack::m_Editors;
}