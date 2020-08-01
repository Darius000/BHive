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

	FMesh::FMesh(const std::vector<FVertex>& Vertices, const std::vector<uint32>& Indices)
		:m_Vertices(Vertices), m_Indices(Indices), m_VertexArray(nullptr)
	{
		CreateBuffers();
	}

	void FMesh::Render()
	{
		if(m_VertexArray) 
		{
			Renderer::Draw(m_VertexArray);
		}
	}

	void FMesh::SetVerticesAndIndices(const std::vector<FVertex>& Vertices, const std::vector<uint32>& Indices)
	{
		m_Vertices = Vertices;
		m_Indices = Indices;

		CreateBuffers();
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

	Model::Model()
	{

	}

	Model::Model(std::initializer_list<Ref<FMesh>> meshes)
		:m_Meshes(meshes)
	{
		
	}

	Model::Model(Ref<FMesh>& mesh)
	{
		AddMesh(mesh);
	}

	Model::Model(std::vector<Ref<FMesh>> meshes)
		:m_Meshes(meshes)
	{

	}

	void Model::AddMesh(Ref<FMesh>& Mesh)
	{
		m_Meshes.emplace_back(Mesh);
	}

	void Model::Render()
	{
		for (const auto& mesh : m_Meshes)
		{
			if (m_Material) 
			{
				m_Material->m_Shader->SetMat4("u_Model", m_Transform.GetMatrix());
				m_Material->Render();
			}

			mesh->Render();
		}
	}

	void Model::SetMaterial(Ref<Material> material)
	{
		m_Material = material;
	}

	void Model::SetTransform(const Transform& transform)
	{
		m_Transform = transform;
	}

	Ref<Model> Model::Import(const WinPath& Path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(*Path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			BH_CORE_ERROR("ERROR::ASSIMP:: {0}", importer.GetErrorString());
			return nullptr;
		}

		Ref<Model> model(new Model());
		Ref<LambertMaterial> DMaterial(new LambertMaterial());
		model->SetMaterial(DMaterial);
		ProcessNode(scene->mRootNode, scene, model);
		return model;
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene, Ref<Model> model)
	{
		for (uint32 i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			model->AddMesh(ProcessMesh(mesh, scene));
		}

		for (uint32 i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene, model);
		}
	}

	Ref<FMesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		Ref<FMesh> Mesh(new FMesh());
		Mesh->SetName(mesh->mName.C_Str());

		std::vector<uint32> Indices;
		std::vector<FVertex> Vertices;

		for (uint32 i = 0; i < mesh->mNumVertices; i++)
		{
			FVertex vertex;

			//Get position
			FVector3 position;
			position.x = mesh->mVertices[i].x;
			position.y = mesh->mVertices[i].y;
			position.z = mesh->mVertices[i].z;
			vertex.m_Position = position;

			//Get normals
			FVector3 normal(0.0f, 0.0f, 0.0f);
			if(mesh->HasNormals())
			{ 
				normal.x = mesh->mNormals[i].x;
				normal.y = mesh->mNormals[i].y;
				normal.z = mesh->mNormals[i].z;
			}
			vertex.m_Normal = normal;

			//Get Texture coordinates
			FVector2 texcoordinate(0.0f, 0.0f);
			
			if (mesh->HasTextureCoords(0))
			{
				texcoordinate.x = mesh->mTextureCoords[0][i].x;
				texcoordinate.y = mesh->mTextureCoords[0][i].y;
			}
			vertex.m_TexCoord = texcoordinate;

			//Get VertexColors
			LinearColor color(0.0f, 0.0f, 0.0f, 0.0f);
			if (mesh->HasVertexColors(0))
			{
				color.r = mesh->mColors[0][i].r;
				color.g = mesh->mColors[0][i].g;
				color.b = mesh->mColors[0][i].b;
				color.a = mesh->mColors[0][i].a;
			}
			vertex.m_Color = color;

			Vertices.push_back(vertex);
		}

		if (mesh->mMaterialIndex >= 0)
		{
			/*aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			aiString path;
			aiReturn tex = material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
			Texture2D::Create(path.C_Str(), (WinPath("BHiveEditor\\Import\\Meshes\\Shotgun\\") + WinPath(path.C_Str()));*/
		}

		for (uint32 i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (uint32 j = 0; j < face.mNumIndices; j++)
			{
				Indices.push_back(face.mIndices[j]);
			}
		}

		
		Mesh->SetVerticesAndIndices(Vertices, Indices);
		return Mesh;
	}

}