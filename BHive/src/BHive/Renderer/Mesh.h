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

	
}