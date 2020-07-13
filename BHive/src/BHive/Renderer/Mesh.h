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
		virtual void SetVerticesAndIndices(const std::vector<FVertex>& Vertices, const std::vector<uint32>& Indices);
		void AddChild(Ref<FMesh> Child);

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
		std::vector<Ref<FMesh>> Children;
	};

	Ref<FMesh> LoadFromFile(const WinPath& Path);
	Ref<FMesh> ParseChildMesh(std::string& line, std::istream& MeshFile);
}