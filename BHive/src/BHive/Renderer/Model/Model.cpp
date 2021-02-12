#include "BHivePCH.h"
#include "Model.h"
#include "ProgressIndicators/ModelImportProgressIndicator.h"

namespace BHive
{
	Model::Model(const Ref<FMesh>& mesh)
	{
		AddMesh(0 , mesh);
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
		return Import(path, false, false);
	}

	Ref<Model> Model::Import(const WinPath& path, bool ImportTextures, bool ImportTangetsAndBitTangets)
	{
		Assimp::Importer importer;
		importer.SetProgressHandler(new MeshImportProgressIndicator());
		const aiScene* scene = importer.ReadFile(path.GetFullPath(), aiProcess_Triangulate |
			aiProcess_CalcTangentSpace);

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
		ProcessNode(id, scene->mRootNode, scene, model, ImportTextures, ImportTangetsAndBitTangets);
		return model;
	}

	bool Model::IsExtensionSupported(const std::string& ext)
	{
		Assimp::Importer importer;
		return importer.IsExtensionSupported(ext);
	}

	void Model::ProcessNode(uint32& id, aiNode* node, const aiScene* scene, Ref<Model> model, bool ImportTextures, bool ImportTangetsAndBitTangets)
	{
		for (uint32 i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			model->AddMesh(id, ProcessMesh(mesh, scene, ImportTextures, ImportTangetsAndBitTangets));
			id++;
		}

		for (uint32 i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(id, node->mChildren[i], scene, model, ImportTextures, ImportTangetsAndBitTangets);
		}
	}

	Ref<FMesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, bool ImportTextures, bool ImportTangetsAndBitTangets)
	{
		Ref<FMesh> Mesh(new FMesh());
		Mesh->SetName(mesh->mName.C_Str());

		std::vector<uint32> Indices;
		std::vector<FVertex> Vertices;
		std::vector<FFace> Faces;

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
			if (mesh->HasNormals())
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
			LinearColor4 color(0.0f, 0.0f, 0.0f, 0.0f);
			if (mesh->HasVertexColors(0))
			{
				color.r = mesh->mColors[0][i].r;
				color.g = mesh->mColors[0][i].g;
				color.b = mesh->mColors[0][i].b;
				color.a = mesh->mColors[0][i].a;
			}
			vertex.m_Color = color;

			FVector3 tangent = FVector3();
			FVector3 bittangent = FVector3();
			if (mesh->HasTangentsAndBitangents() && ImportTangetsAndBitTangets)
			{
				tangent.x = mesh->mTangents[i].x;
				tangent.y = mesh->mTangents[i].y;
				tangent.z = mesh->mTangents[i].z;

				bittangent.x = mesh->mBitangents[i].x;
				bittangent.y = mesh->mBitangents[i].y;
				bittangent.z = mesh->mBitangents[i].z;

			}

			vertex.m_Tangent = tangent;
			vertex.m_BitTangent = bittangent;

			Vertices.push_back(vertex);
		}

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			if (ImportTextures)
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
			FFace meshFace;
			for (uint32 j = 0; j < face.mNumIndices; j++)
			{
				Indices.push_back(face.mIndices[j]);
				meshFace.indices.push_back(face.mIndices[j]);
			}
			Faces.push_back(meshFace);
		}

		Mesh->SetMaterial(AssetManager::Get<Material>("WorldDefault"));
		Mesh->m_ImportedTangentAndBitTangents = ImportTangetsAndBitTangets && mesh->HasTangentsAndBitangents();
		Mesh->SetVerticesAndIndices(Vertices, Indices, Faces);
		return Mesh;
	}

	void Model::ProcessTexture(aiMaterial* material, aiTextureType textureType)
	{
		aiString path;
		uint32 numtextures = material->GetTextureCount(textureType);

		if (numtextures == 0) return;

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

	void Model::AddMesh(uint32 id, const Ref<FMesh>& Mesh)
	{
		m_Meshes.emplace(std::pair{ id , Mesh });
	}

	WinPath Model::s_LastLoadedDirectory = "";
}