#include "BHivePCH.h"
#include <glad/glad.h>
#include "BHive/Renderer/Renderer.h"
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
		if (m_Material)
		{
			m_Material->Render();
		}

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

		//BH_CORE_INFO("{0}", m_Name);
	}

	void FMesh::SetMaterial(Ref<Material> material)
	{
		m_Material = material;
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

	void Model::Render()
	{
		for (auto& mesh : m_Meshes)
		{
			mesh.second->Render();
		}
	}

	Ref<Model> Model::Create(const WinPath& path)
	{
		return Import(path, false);
	}

	Ref<Model> Model::Import(const WinPath& path, bool ImportTextures)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path.GetFullPath(), aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			BH_CORE_ERROR("ERROR::ASSIMP:: {0}", importer.GetErrorString());
			return nullptr;
		}

		Ref<Model> model = Make_Ref<Model>();
		model->m_OriginalDirectory = path;
		model->m_Name = path.GetName();
		s_LastLoadedDirectory = path;
		uint32 id = 0;
		ProcessNode(id, scene->mRootNode, scene, model, ImportTextures);
		return model;
	}

	bool Model::IsExtensionSupported(const std::string& ext)
	{
		Assimp::Importer importer;
		return importer.IsExtensionSupported(ext);
	}

	void Model::ProcessNode(uint32& id, aiNode* node, const aiScene* scene, Ref<Model> model, bool ImportTextures)
	{
		for (uint32 i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			model->AddMesh(id, ProcessMesh(mesh, scene, ImportTextures));
			id++;
		}

		for (uint32 i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(id, node->mChildren[i], scene, model, ImportTextures);
		}
	}

	Ref<FMesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, bool ImportTextures)
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
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			if(ImportTextures)
			{ 
				for (uint32 i = 0; i < AI_TEXTURE_TYPE_MAX; i++)
				{
					ProcessTexture(material, (aiTextureType)i);
				}
			}
		}

		for (uint32 i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (uint32 j = 0; j < face.mNumIndices; j++)
			{
				Indices.push_back(face.mIndices[j]);
			}
		}

		Ref<PhongMaterial> Material(new PhongMaterial());
		Mesh->SetMaterial(Material);
		Mesh->SetVerticesAndIndices(Vertices, Indices);
		return Mesh;
	}

	void Model::ProcessTexture(aiMaterial* material, aiTextureType textureType)
	{
		aiString path;
		uint32 numtextures = material->GetTextureCount(textureType);

		if(numtextures == 0) return;

		for (uint32 i = 0; i < numtextures; i++)
		{
			aiReturn returnVal = material->GetTexture(textureType, i, &path);
			if (returnVal == aiReturn_SUCCESS)
			{
				if (!AssetManager::Exists(path.C_Str()))
				{
					WinPath WindowsPath(s_LastLoadedDirectory.GetPath() + WinPath(path.C_Str()));
					Texture2D::Create(WindowsPath);
				}
			}
		}
	}

	void Model::AddMesh(uint32 id, Ref<FMesh>& Mesh)
	{
		m_Meshes.emplace(std::pair{ id , Mesh });
	}

	WinPath Model::s_LastLoadedDirectory = "";
}