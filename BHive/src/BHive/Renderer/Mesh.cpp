#include "BHivePCH.h"
#include <glad/glad.h>
#include "BHive/Renderer/Renderer.h"
#include "BHive/Renderer/VertexArray.h"
#include "Buffer.h"
#include "Mesh.h"

namespace BHive
{
	FMesh::FMesh()
		:m_VertexArray(nullptr)
	{

	}

	FMesh::FMesh(const FMesh& Other)
	{
		m_VertexArray.reset(Other.m_VertexArray.get());
	}

	void FMesh::Render()
	{
		if(m_VertexArray) Renderer::Draw(m_VertexArray);

		for (const auto& Child : Children)
		{
			Child->Render();
		}
	}

	void FMesh::SetVerticesAndIndices(const std::vector<FVertex>& Vertices, const std::vector<uint32>& Indices)
	{
		m_Vertices = Vertices;
		m_Indices = Indices;

		CreateBuffers();
	}

	void FMesh::AddChild(Ref<FMesh> Child)
	{
		Children.push_back(Child);
	}

	void FMesh::SetName(const BName& NewName)
	{
		m_Name = NewName;

		BH_CORE_INFO("{0}", m_Name);
	}

	void FMesh::CreateBuffers()
	{
		m_VertexArray.reset(VertexArray::Create());

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color"},
			{ ShaderDataType::Float2, "a_TexCoord"},
			{ ShaderDataType::Float3, "a_Normal" }
		};

		Ref<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(VertexBuffer::Create(m_Vertices));
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		Ref<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(IndexBuffer::Create(m_Indices));

		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	}


	struct FFaceData
	{
		uint32 m_VertexIndices[3];
		uint32 m_ColorIndices[3];
		uint32 m_TextureIndices[3];
		uint32 m_NormalIndices[3];
		//FVertexData* m_VertexData[3];

		friend std::istream& operator>>(std::istream& is, FFaceData& Face)
		{
			return is >> Face.m_VertexIndices[0] >> Face.m_TextureIndices[0] >> Face.m_NormalIndices[0] >>
				Face.m_VertexIndices[1]  >> Face.m_TextureIndices[1]  >> Face.m_NormalIndices[1] 
				>> Face.m_VertexIndices[2]  >> Face.m_TextureIndices[2]  >> Face.m_NormalIndices[2];
		}
	};

	Ref<FMesh> LoadFromFile(const WinPath& Path)
	{
		Ref<FMesh> ParentMesh;
		std::vector<Ref<FMesh>> Meshes;

		try
		{
			std::ifstream MeshFile(*Path, std::ifstream::in);
			if (MeshFile.is_open())
			{
				std::string line;
				/*while (std::getline(MeshFile, line).good())
				{
					if (line.substr(0, 2) == "o ")
					{
						std::istringstream l(line.substr(2), std::ios::in);
						std::string objName;
						l >> objName;

						
					}
					
				}*/

				Ref<FMesh> ChildMesh = ParseChildMesh(line, MeshFile);
				//ChildMesh->SetName(objName);
				Meshes.push_back(ChildMesh);

				MeshFile.close();
			}
		}
		catch (std::ifstream::failure exception)
		{
			BH_CORE_ERROR("ERROR {1}{0}", *Path, exception.what());
		}

		if(!Meshes.empty())
		{ 
			ParentMesh = Meshes[0];

			for (const auto& Mesh : Meshes)
			{
				if (Mesh != ParentMesh)
				{
					ParentMesh->AddChild(Mesh);
				}
			}
		}

		return ParentMesh;
	};

	Ref<FMesh> ParseChildMesh(std::string& line, std::istream& MeshFile)
	{
		std::vector<uint32> Indices;
		std::vector<FFaceData> Faces;
		std::vector<LinearColor> temp_Color{ LinearColor(1.0f, 0.5f, 0.0f) };
		std::vector<Vector2<float>> temp_TexCoords;
		std::vector<Vector3<float>> temp_Normals;

		std::vector<FVertex> VerticesData;

		while (std::getline(MeshFile, line))
		{	
			/*if (line.substr(0, 2) == "o ")
			{
				break;
			}*/
			if (line.substr(0, 2) == "v ")
			{
				std::istringstream l(line.substr(2), std::ios::in);

				float x, y, z;
				l >> x >> y >> z;

				FVertex VertexData;
				VertexData.m_Position = {x,y,z};
				VerticesData.push_back(VertexData);
			}
			else if (line.substr(0, 3) == "vt ")
			{
				std::istringstream l(line.substr(2), std::ios::in);
				float x, y;

				l >> x >> y;
				Vector2 TexCoord = Vector2(x, y);
				temp_TexCoords.push_back(TexCoord);
			}
			else if (line.substr(0, 3) == "vn ")
			{
				std::istringstream l(line.substr(2), std::ios::in);
				float x, y, z;

				l >> x >> y >> z;
				Vector3 Normal = Vector3(x, y, z);
				temp_Normals.push_back(Normal);

			}
			else if (line.substr(0, 2) == "f ")
			{
				FFaceData FaceData;

				std::replace(line.begin(), line.end(), '/', ' ');
				std::istringstream l(line.substr(2), std::ios::in);

				l >> FaceData;
				Faces.push_back(FaceData);
			}
		}


		for (auto SubFace : Faces)
		{
			uint32 index0 = SubFace.m_VertexIndices[0] - 1;
			uint32 index1 = SubFace.m_VertexIndices[1] - 1;
			uint32 index2 = SubFace.m_VertexIndices[2] - 1;

			Indices.push_back(index0);
			Indices.push_back(index1);
			Indices.push_back(index2);

			VerticesData[index0].m_Color = temp_Color[0];
			VerticesData[index1].m_Color = temp_Color[0];
			VerticesData[index2].m_Color = temp_Color[0];

			VerticesData[index0].m_TexCoord = temp_TexCoords[SubFace.m_TextureIndices[0] - 1];
			VerticesData[index1].m_TexCoord = temp_TexCoords[SubFace.m_TextureIndices[1] - 1];
			VerticesData[index2].m_TexCoord = temp_TexCoords[SubFace.m_TextureIndices[2] - 1];

			VerticesData[index0].m_Normal = temp_Normals[SubFace.m_NormalIndices[0] - 1];
			VerticesData[index1].m_Normal = temp_Normals[SubFace.m_NormalIndices[1] - 1];
			VerticesData[index2].m_Normal = temp_Normals[SubFace.m_NormalIndices[2] - 1];
		}


		Ref<FMesh> Mesh(new FMesh());
		Mesh->SetVerticesAndIndices(VerticesData, Indices);
		return Mesh;
	};
}