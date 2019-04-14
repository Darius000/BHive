#include "BHivePCH.h"
#include "Mesh.h"


namespace BHive
{
	Mesh::Mesh(std::vector<Vertex> InVertices, std::vector<unsigned int> InIndices, std::vector<Texture2D> InTextures)
	{
		vertices = InVertices;
		indices = InIndices;
		textures = InTextures;

		SetupMesh();
	}

	void Mesh::Draw(Shader* shader)
	{
		unsigned int diffuseNum = 1;
		unsigned int specularNum = 1;
		unsigned int emissionNum = 1;

		for (unsigned int i = 0; i < textures.size(); i++)
		{
			std::string number;
			std::string name;
			ETextureType MapType = textures[i].Type;

			if (MapType == ETextureType::DIFFUSE)
			{
				number = std::to_string(diffuseNum++);
				name = "texture_diffuse";
			}
			else if (MapType == ETextureType::SPECULAR)
			{
				number = std::to_string(specularNum++);
				name = "texture_specular";
			}
			else if (MapType == ETextureType::EMISSION)
			{
				number = std::to_string(emissionNum++);
				name = "texture_emission";
			}

			shader->SetInt((name + number), i);

			textures[i].Use(i);
		}

		//draw Mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
	}

	void Mesh::SetupMesh()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		//vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		//vertex colors
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

		//vertex normals
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

		//vertex tex coords
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));

		glBindVertexArray(0);
	}
}
