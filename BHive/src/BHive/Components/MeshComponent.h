#pragma once

#include "Assets/Shader.h"
#include "Assets/Mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Cameras/Camera.h"
#include "GameObject.h"

namespace BHive
{
	class MeshComponent;
	class BBox;

	class BHive_API BBox
	{
	public:

		BBox(std::vector<glm::vec3> InPositions, glm::vec3 InColor = glm::vec3(1.0f, .5f, 0.0f))
			:color(InColor)
		{
			CalculateBounds(InPositions);
		}

		BBox(glm::vec3 InMin, glm::vec3 InMax, glm::vec3 InColor = glm::vec3(1.0f, .5f, 0.0f))
			:color(InColor)
		{
			min = InMin;
			max = InMax;
		}

		~BBox()
		{
			delete shader;
		}

		glm::vec3 min;
		glm::vec3 max;
		glm::vec3 color;

		void CreateDrawBounds();

		void DrawBounds(MeshComponent* meshComponent);

	protected:
		void CalculateBounds(const std::vector<glm::vec3> positions);

	private:
		unsigned int VAO, EBO;
		unsigned int VBO;

		std::vector<unsigned int> indices;

		Shader* shader;
	};

	class BHive_API MeshComponent : public GameObject
	{
	public:
		MeshComponent();
		MeshComponent(std::string path);

		
		void Draw(Shader* shader);
		void DrawBounds();

		void LoadResource(std::string path);
		void SetUpBounds();

		BBox* BoundingBox;
		std::vector<BBox*> SubBoundingBoxes;

	private:

		std::vector<Texture2D> textures_loaded;

		std::vector<Mesh> meshes;
		std::string directory;

		bool gammaCorrection;
		bool m_BoundsUpdated;

		void LoadMeshComponent(std::string path);
		void ProcessNode(aiNode * node, const aiScene* World);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* World);
		std::vector<Texture2D> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, ETextureType typeName);
		BBox* GetSubBoundingBox(int index);
	};
}

