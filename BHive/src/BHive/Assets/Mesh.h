#pragma once

#include "Core.h"
#include "Texture2D.h"
#include "Shader.h"


namespace BHive
{
	struct BHive_API Vertex
	{
		glm::vec3 Position;
		glm::vec3 Color;
		glm::vec3 Normal;
		glm::vec2 TexCoord;
	};

	class BHive_API Mesh : public BResource
	{
	public:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture2D> textures;

		Mesh();
		Mesh(std::vector<Vertex> InVertices, std::vector<unsigned int> InIndices, std::vector<Texture2D> InTextures);
		void Draw(Shader* shader);

		unsigned int VAO;

	private:

		unsigned int VBO, EBO;

		void SetupMesh();
	protected:
		virtual void OnSave(std::ofstream& resourceFile, const String& resourceFilePath) override;
		virtual void OnLoad(std::ifstream& resourceFile) override;
		virtual void LoadResource() override;

	};
}
