#pragma once

#include  <assimp/Importer.hpp>
#include  <assimp/scene.h>
#include  <assimp/postprocess.h>

#include "VertexArray.h"
#include "Buffer.h"
#include "Material.h"

namespace BHive
{
	class FMesh
	{
	public:
	
		FMesh();
		FMesh(const std::vector<FVertex>& Vertices, const std::vector<uint32>& Indices);
		FMesh(const FMesh& Other);
		virtual ~FMesh(){};

		void Render();
		virtual void SetVerticesAndIndices(const std::vector<FVertex>& Vertices, const std::vector<uint32>& Indices);
		void SetName(const BName& NewName );	
		void SetMaterial(Ref<Material> material);
		
	public:
		BName GetName() { return m_Name; }
		Ref<Shader> GetShader() const { return m_Material->m_Shader; }
		Ref<Material> GetMaterial() { return m_Material; }
		
	private:
		void CreateBuffers();

	protected:

		std::vector<FVertex> m_Vertices;
		std::vector<uint32> m_Indices;
		BName m_Name;

	private:
		Ref<VertexArray> m_VertexArray;
		Ref<Material> m_Material;
		
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
		static Ref<Model> Import(const WinPath& path, bool ImportTextures);
		static bool IsExtensionSupported(const std::string& ext);

	private:
		static void ProcessNode(uint32& id, aiNode* node, const aiScene *scene, Ref<Model> model, bool ImportTextures);
		static Ref<FMesh> ProcessMesh(aiMesh* mesh, const aiScene* scene, bool ImportTextures);
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

	public:
		void AddMesh(uint32 id, Ref<FMesh>& Mesh);

	private:
		 Meshes m_Meshes;	
		 WinPath m_OriginalDirectory;
	
		 static WinPath s_LastLoadedDirectory;
	};
}