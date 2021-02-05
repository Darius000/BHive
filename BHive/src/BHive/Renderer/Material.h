#pragma  once

#include "Shader.h"
#include "Assets/Asset.h"

namespace BHive
{
	static const char* DefaultMaterialName = "DefaultMaterial";

	class Material : public IAssetType
	{
		DEFINE_ASSET_BODY(Material, "materialicon")
	public:

		Material();
		Material(Ref<Shader> shader);
		virtual ~Material(){};

		void Render();
		
		Ref<Shader> GetShader()
		{
			return m_Shader;
		}

	protected:
		Ref<Shader> m_Shader;

		friend class FMesh;
		friend class MaterialEditorCustomizationDetails;
	};
}