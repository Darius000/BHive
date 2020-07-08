#pragma once

namespace BHive
{
	class FMesh
	{
	public:
		FMesh();
		FMesh(const FMesh& Other);
		virtual ~FMesh(){};

		void Render();

		//Array of materials
		//Array of textures in materials
		//Shader in material
		virtual void SetVerticesAndIndices(const std::vector<float>& Vertices, const std::vector<uint32>& Indices);

	private:
		void CreateBuffers();

	protected:
		std::vector<float> m_Vertices;
		std::vector<uint32> m_Indices;

	private:
		Ref<VertexArray> m_VertexArray;

	};
}