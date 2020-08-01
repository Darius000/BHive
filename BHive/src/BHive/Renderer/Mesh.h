#pragma once

#include  <assimp/Importer.hpp>
#include  <assimp/scene.h>
#include  <assimp/postprocess.h>

#include "Material.h"
#include "Components/TransformComponent.h"

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

	public:
		BName GetName() { return m_Name; }
		
	private:
		void CreateBuffers();

	protected:

		std::vector<FVertex> m_Vertices;
		std::vector<uint32> m_Indices;
		BName m_Name;

	private:
		Ref<VertexArray> m_VertexArray;
		
	};

	
	class Model
	{
	public:
		Model();
		Model(Ref<FMesh>& mesh);
		Model(std::initializer_list<Ref<FMesh>> meshes);
		Model(std::vector<Ref<FMesh>> meshes);
		~Model(){};

		void AddMesh(Ref<FMesh>& Mesh);
		void Render();
		void SetTransform(const Transform& transform);
		Ref<Shader> GetShader() const { return m_Material->m_Shader; }

		void SetMaterial(Ref<Material> material);
		Ref<Material> GetMaterial() { return m_Material; }

	public:
		static Ref<Model> Import(const WinPath& Path);
		static void ProcessNode(aiNode* node, const aiScene *scene, Ref<Model> model);
		static Ref<FMesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);

	private:
		std::vector<Ref<FMesh>> m_Meshes;
		Ref<Material> m_Material;
		Transform m_Transform;
	};
}