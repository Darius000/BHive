#pragma once

#include "Mesh.h"
#include "Assets/Asset.h"

namespace BHive
{
	using Meshes = std::unordered_map<uint32, Ref<FMesh>>;

	class Model : public IAssetType
	{

	public:
		DEFINE_ASSET_BODY(Model, "meshicon")

		Model() = default;
		Model(const Ref<FMesh>& mesh);
		virtual ~Model() = default;

		void Render();
		static Ref<Model> Create(const WinPath& path);

	public:
		static Ref<Model> Import(const WinPath& path, bool ImportTextures, bool ImportTangetsAndBitTangets);
		static bool IsExtensionSupported(const std::string& ext);

	private:
		static void ProcessNode(uint32& id, aiNode* node, const aiScene* scene, Ref<Model> model, bool ImportTextures, bool ImportTangetsAndBitTangets);
		static Ref<FMesh> ProcessMesh(aiMesh* mesh, const aiScene* scene, bool ImportTextures, bool ImportTangetsAndBitTangets);
		static void ProcessTexture(aiMaterial* material, aiTextureType textureType);

	public:
		Ref<FMesh> GetMesh(uint32 id)
		{
			BH_CORE_ASSERT(m_Meshes.find(id) != m_Meshes.end(), "Mesh doesn't exist!");
			return m_Meshes[id];
		}

		Meshes& GetMeshes() { return m_Meshes; }
		WinPath& GetDirectory() { return m_OriginalDirectory; }
	public:
		void AddMesh(uint32 id, const Ref<FMesh>& Mesh) ;

	private:
		Meshes m_Meshes;
		WinPath m_OriginalDirectory;

		static WinPath s_LastLoadedDirectory;
	};
}