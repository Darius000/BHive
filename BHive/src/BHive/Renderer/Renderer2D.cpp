#include "BHivePCH.h"
#include "Renderer2D.h"
#include "BHive/Renderer/Shader.h"
#include "BHive/Renderer/Material.h"

namespace BHive
{

	void Renderer2D::Init()
	{
		RenderCommands::Init();
	}

	void Renderer2D::ShutDown()
	{

	}

	void Renderer2D::Begin()
	{
		RenderCommands::SetClearColor(LinearColor4(0.5f, 0.5f, 0.50f, 1.0f));
		RenderCommands::Clear();
	}

	void Renderer2D::End()
	{
		
	}


	Ref<Model> Renderer2D::Plane(float width, float height)
	{
		std::vector<FVertex> m_Vertices =
		{
			FVertex({-width / 2.0f, -height / 2.0f, 0.0f},	{0.0f, 1.0f, 0.0f},		{0.0f, 0.0f},	{0.0f, 0.0f, 1.0f}),
			FVertex({width / 2.0f, -height / 2.0f, 0.0f},	{0.0f, 1.0f, 0.0f},		{1.0f, 0.0f},	{0.0f, 0.0f, 1.0f}),
			FVertex({width / 2.0f, height / 2.0f, 0.0f},	{0.0f, 1.0f, 0.0f},		{1.0f, 1.0f},	{0.0f, 0.0f, 1.0f}),
			FVertex({-width / 2.0f, height / 2.0f, 0.0f},	{0.0f, 1.0f, 0.0f},		{0.0f, 1.0f},	{0.0f, 0.0f, 1.0f})
		};


		std::vector<uint32> m_Indices =
		{
			0, 1, 2, 2, 3, 0
		};

		std::vector<FFace> m_Faces = 
		{
			{{0, 1, 2}}, {{2, 3, 0}}
		};

		Ref<FMesh> plane(new FMesh());
		
		plane->SetVerticesAndIndices(m_Vertices, m_Indices, m_Faces);
		Ref<Model> m_Model = Make_Ref<Model>();
		m_Model->AddMesh(0, plane);
		plane->SetMaterial(AssetManager::Get<Material>(DefaultMaterialName));
		m_Model->m_Name = "plane";
		return m_Model;
	}


	Ref<Model> Renderer2D::Triangle(float width, float height)
	{
		std::vector<FVertex> m_Vertices =
		{
			FVertex({-width / 2.0f, 0.0f, 0.0f},	{1.0f, 0.0f, 0.0f},		{0.0f, 0.0f},	{0.0f, 0.0f, 1.0f}),
			FVertex({width / 2.0f, 0.0f, 0.0f},	{1.0f, 0.0f, 0.0f},		{1.0f, 0.0f},	{0.0f, 0.0f, 1.0f}),
			FVertex({0.0f, height, 0.0f},			{1.0f, 0.0f, 0.0f},		{0.5f, 1.0f},	{0.0f, 0.0f, 1.0f})
		};

		std::vector<uint32> m_Indices =
		{
			0 , 1, 2
		};

		std::vector<FFace> m_Faces = 
		{
			{{0 ,1 ,2}}
		};

		Ref<FMesh> triangle(new FMesh());
		triangle->SetVerticesAndIndices(m_Vertices, m_Indices, m_Faces);
		Ref<Model> m_Model = Make_Ref<Model>();
		m_Model->AddMesh(0, triangle);
		triangle->SetMaterial(AssetManager::Get<Material>(DefaultMaterialName));
		m_Model->m_Name = "triangle";
		return m_Model;
	}


	Ref<Model> Renderer2D::Quad()
	{
		std::vector<FVertex> m_Vertices =
		{
			FVertex({-1.0, -1.0f, 0.0f},	{0.0f, 1.0f, 0.0f},		{0.0f, 0.0f},	{0.0f, 0.0f, 1.0f}),
			FVertex({1.0f, -1.0f, 0.0f},	{0.0f, 1.0f, 0.0f},		{1.0f, 0.0f},	{0.0f, 0.0f, 1.0f}),
			FVertex({1.0f, 1.0f, 0.0f},	{0.0f, 1.0f, 0.0f},		{1.0f, 1.0f},	{0.0f, 0.0f, 1.0f}),
			FVertex({-1.0f, 1.0f, 0.0f},	{0.0f, 1.0f, 0.0f},		{0.0f, 1.0f},	{0.0f, 0.0f, 1.0f})
		};


		std::vector<uint32> m_Indices =
		{
			0, 1, 2, 2, 3, 0
		};

		std::vector<FFace> m_Faces =
		{
			{{0, 1, 2}}, {{2, 3, 0}}
		};

		Ref<FMesh> quad(new FMesh());

		quad->SetVerticesAndIndices(m_Vertices, m_Indices, m_Faces);
		Ref<Model> m_Model = Make_Ref<Model>();
		m_Model->AddMesh(0, quad);
		quad->SetMaterial(AssetManager::Get<Material>(DefaultMaterialName));
		m_Model->m_Name = "Quad";
		return m_Model;
	}

	void Renderer2D::Draw(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommands::DrawIndexed(vertexArray);
	}

	void Renderer2D::OnWindowResized(uint32 width, uint32 height)
	{
		RenderCommands::SetViewport(0, 0, width, height);
	}
}