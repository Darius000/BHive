#include "BHivePCH.h"
#include "BillboardComponent.h"

namespace BHive
{
	BillboardComponent::BillboardComponent()
		//:texture(0)
	{

	}


	BillboardComponent::~BillboardComponent()
	{

	}

	/*void BillboardComponent::ComponentStart()
	{
		vertexShader = "Shaders/Billboard.vs";
		fragmentShader = "Shaders/Billboard.fs";

		size = 1.0f;

		color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		blendMode = 0;

		RenderComponent::ComponentStart();
	}

	void BillboardComponent::ComponentUpdate(float DeltaTime)
	{
		RenderComponent::ComponentUpdate(DeltaTime);

	}

	void BillboardComponent::Render()
	{
		RenderComponent::Render();

		shader->SetVector4("aColor", color);
		shader->SetInt("aBlending", blendMode);

		if (texture)
		{
			shader->SetInt("validTexture", 1);
			texture->Use(0);
			shader->SetInt("aTexture", 0);

		}
		else
		{
			shader->SetInt("validTexture", 0);
		}

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES,(GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}

	void BillboardComponent::Construct()
	{
		positions =
		{
			//pos					//uv
			size, size, 0.0f,		1.0f, 1.0f,
			size, -size, 0.0f,		1.0f, 0.0f,
			-size, -size, 0.0f,		0.0f, 0.0f,
			-size, size, 0.0f,		0.0f, 1.0f
		};

		indices =
		{
			0, 1, 2,
			2, 3, 0
		};

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, (unsigned int)positions.size() * sizeof(float), &positions[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (unsigned int)indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		/*std::cout << "Positions Size:" << (unsigned int)positions.size() * sizeof(float)
			<< " Indices Size:" << (unsigned int)indices.size() * sizeof(unsigned int) << "\n";*/
	/*}

	void BillboardComponent::SetTexture(std::string fileName, std::string path)
	{
		/*texture = new Texture2D();
		texture->LoadTexture(fileName, path);
		texture->Type = ETextureType::DIFFUSE;*/
	/*}

	void BillboardComponent::SetTexture(Texture2D* InTexture)
	{
		texture = InTexture;
	}

	void BillboardComponent::SetBlendMode(int InMode)
	{
		blendMode = InMode;
	}

	void BillboardComponent::SetSize(float InSize)
	{
		size = InSize;
	}

	void BillboardComponent::SetColor(glm::vec4 InColor)
	{
		color = InColor;
	}

	float BillboardComponent::CameraDistance(Camera* camera)
	{
		Vector3 A = GetTransform().GetPosition();
		Vector3 B = camera->GetTransform().GetPosition();

		float x = B.x - A.x;
		float y = B.y - A.y;
		float z = B.z - A.z;

		return sqrt((x * x) + (y * y) + (z * z));
	}*/
}