#include "BHivePCH.h"
#include "MeshComponent.h"
#include "GameStatics.h"


namespace BHive
{
	void BBox::CalculateBounds(const std::vector<glm::vec3> positions)
	{
		min.x = min.y = min.z = 1e10f;
		max.x = max.y = max.z = -1e10f;

		for (unsigned int i = 0; i < positions.size(); ++i)
		{
			glm::vec3 temp = positions[i];

			min.x = std::min(min.x, temp.x);
			min.y = std::min(min.y, temp.y);
			min.z = std::min(min.z, temp.z);

			max.x = std::max(max.x, temp.x);
			max.y = std::max(max.y, temp.y);
			max.z = std::max(max.z, temp.z);
		}

		CreateDrawBounds();
	}

	void BBox::CreateDrawBounds()
	{
		shader = new Shader("Shaders/BoundingBox.vs", "Shaders/BoundingBox.fs");

		float vertices[] =
		{
			//front
			max.x, max.y, min.z,	//0
			max.x, min.y, min.z,	//1
			min.x, min.y, min.z,	//2	
			min.x,  max.y, min.z,	//3

			//back
			max.x, max.y, max.z,	//4
			max.x, min.y, max.z,	//5
			min.x, min.y, max.z,	//6
			min.x,  max.y, max.z,	//7

		};

		indices =
		{
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			6, 7, 4,

			4, 0, 3,
			3, 7, 4,

			5, 1, 2,
			2, 6, 5,

			4, 5, 1,
			1, 0, 4,

			3, 2, 6,
			6, 7, 3
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void BBox::DrawBounds(MeshComponent * meshComponent)
	{
		shader->Use();
		shader->SetVector3("boundsColor", color);
		shader->SetMatrix4("view", GameStatics::GetActiveCamera()->GetViewMatrix());
		shader->SetMatrix4("projection", GameStatics::GetActiveCamera()->GetProjectionMatrix());
		shader->SetMatrix4("model", meshComponent->GetRootComponent()->GetMatrix());

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	MeshComponent::MeshComponent()
		:BoundingBox(0), SubBoundingBoxes(0), m_BoundsUpdated(false)
	{
		SetDisplayName("MeshComponent");
	}

	MeshComponent::MeshComponent(std::string path)
		: MeshComponent()
	{
		LoadResource(path);
	}

	void MeshComponent::LoadResource(std::string path)
	{
		LoadMeshComponent(path);

		SetUpBounds();

	}

	void MeshComponent::SetUpBounds()
	{
		std::vector<glm::vec3> positions;

		for (unsigned int i = 0; i < SubBoundingBoxes.size(); i++)
		{
			positions.push_back(SubBoundingBoxes[i]->min);
			positions.push_back(SubBoundingBoxes[i]->max);
		}

		BoundingBox = new BBox(positions, glm::vec3(0.0f, 1.0f, 0.5f));

		m_BoundsUpdated = true;
	}

	void MeshComponent::Draw(Shader* shader)
	{
		shader->Use();

		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			meshes[i].Draw(shader);
		}

		DrawBounds();
	}

	void MeshComponent::DrawBounds()
	{
		if (m_BoundsUpdated)
		{
			for (unsigned int i = 0; i < SubBoundingBoxes.size(); i++)
			{
				SubBoundingBoxes[i]->DrawBounds(this);
			}

			BoundingBox->DrawBounds(this);
		}
	}

	void MeshComponent::LoadMeshComponent(std::string path)
	{
		Assimp::Importer importer;
		const aiScene *World = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!World || World->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !World->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}

		std::cout << "ASSIMP::FILE LOADED SUCCESSFULLY" << std::endl;

		directory = path.substr(0, path.find_last_of('/'));

		ProcessNode(World->mRootNode, World);
	}

	void MeshComponent::ProcessNode(aiNode * node, const aiScene* World)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = World->mMeshes[node->mMeshes[i]];
			meshes.push_back(ProcessMesh(mesh, World));
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], World);
		}
	}

	Mesh MeshComponent::ProcessMesh(aiMesh* mesh, const aiScene* World)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture2D> textures;
		std::vector<glm::vec3> positions;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;

			//process vertex positions, normals, texture coordinates
			glm::vec3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;
			positions.push_back(vector);

			if (mesh->HasVertexColors(i))
			{
				vector.x = mesh->mColors[i]->r;
				vector.y = mesh->mColors[i]->g;
				vector.z = mesh->mColors[i]->b;
				vertex.Color = vector;
			}

			if (mesh->HasNormals())
			{
				vector.x = mesh->mNormals[i].x;
				vector.x = mesh->mNormals[i].x;
				vector.x = mesh->mNormals[i].x;
				vertex.Normal = vector;
			}

			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoord = vec;
			}
			else
				vertex.TexCoord = glm::vec2(0.0f, 0.0f);


			vertices.push_back(vertex);
		}

		//process indices
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		//process material
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial * material = World->mMaterials[mesh->mMaterialIndex];
			std::vector<Texture2D> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, ETextureType::DIFFUSE);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			std::vector<Texture2D> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, ETextureType::SPECULAR);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

			std::vector<Texture2D> emissionMaps = LoadMaterialTextures(material, aiTextureType_EMISSIVE, ETextureType::EMISSION);
			textures.insert(textures.end(), emissionMaps.begin(), emissionMaps.end());
		}

		//process bounds
		SubBoundingBoxes.push_back(new BBox(positions));

		return Mesh(vertices, indices, textures);
	}

	std::vector<Texture2D> MeshComponent::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, ETextureType typeName)
	{
		std::vector<Texture2D> texures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;
			for (unsigned int j = 0; j < textures_loaded.size(); j++)
			{
				if (std::strcmp(textures_loaded[j].GetDisplayName().data(), str.C_Str()) == 0)
				{
					texures.push_back(textures_loaded[j]);
					skip = true;
					break;
				}
			}
			if (!skip)
			{
				Texture2D texture = Texture2D(str.C_Str(), directory, typeName);
				texures.push_back(texture);
				textures_loaded.push_back(texture);
			}
		}

		return texures;
	}

	BBox* MeshComponent::GetSubBoundingBox(int index)
	{
		return SubBoundingBoxes[index];
	}
}

