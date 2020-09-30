#pragma once

#include  <assimp/Importer.hpp>
#include  <assimp/scene.h>
#include  <assimp/postprocess.h>

#include "VertexArray.h"
#include "Buffer.h"
#include "Material.h"
#include "BHive/Managers/AssetManagers.h"

namespace BHive
{

	class FMesh
	{
	public:
	
		FMesh();
		FMesh(const std::vector<FVertex>& Vertices, const std::vector<uint32>& Indices, const std::vector<FFace>& Faces);
		FMesh(const FMesh& Other);
		virtual ~FMesh(){};

		void Render();
		virtual void SetVerticesAndIndices(const std::vector<FVertex>& Vertices, const std::vector<uint32>& Indices, const std::vector<FFace>& Faces);
		void SetName(const BName& NewName );	
		void SetMaterial(Ref<Material> material);
		void CalculateTangetsandBitTangets();
		bool ImportedTangentAndBitTangents() const {  return m_ImportedTangentAndBitTangents; }
		
	public:
		BName GetName() { return m_Name; }
		Ref<Material> GetMaterial() { return m_Material; }
		
	private:
		void CreateBuffers();

	public:
		std::vector<FVertex> m_Vertices;
		std::vector<uint32> m_Indices;
		std::vector<FFace> m_Faces;
		bool m_ImportedTangentAndBitTangents = false;
		BName m_Name;

	private:
		Ref<VertexArray> m_VertexArray;
		Ref<Material> m_Material;
		
		friend class MeshEditorCustomizationDetails;
	};

	using Meshes = std::unordered_map<uint32, Ref<FMesh>>;
	
	class Model : public Asset
	{
		
	public:
		Model() = default;
		virtual ~Model() = default;

		void Render();
		static Ref<Model> Create(const WinPath& path);

		std::string GetAssetType() const override { return "Mesh"; } ;

	public:
		static Ref<Model> Import(const WinPath& path, bool ImportTextures, bool ImportTangetsAndBitTangets);
		static bool IsExtensionSupported(const std::string& ext);

	private:
		static void ProcessNode(uint32& id, aiNode* node, const aiScene *scene, Ref<Model> model, bool ImportTextures, bool ImportTangetsAndBitTangets);
		static Ref<FMesh> ProcessMesh(aiMesh* mesh, const aiScene* scene, bool ImportTextures, bool ImportTangetsAndBitTangets);
		static void ProcessTexture(aiMaterial* material, aiTextureType textureType);

	public:
		Ref<FMesh> GetMesh(uint32 id)
		{ 
			BH_CORE_ASSERT(m_Meshes.find(id) != m_Meshes.end(), "Mesh doesn't exist!");
			return m_Meshes[id]; 
		}

		Meshes& GetMeshes() { return m_Meshes; }
		std::string& GetName() { return m_Name; }
		WinPath& GetDirectory() { return m_OriginalDirectory; }

		const std::string GetThumbnailName() const override
		{
			return "meshicon";
		}

	public:
		void AddMesh(uint32 id, Ref<FMesh>& Mesh);

	private:
		 Meshes m_Meshes;	
		 WinPath m_OriginalDirectory;
	
		 static WinPath s_LastLoadedDirectory;
	};
}