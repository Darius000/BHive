#include "BHivePCH.h"
#include "Triangle.h"

namespace BHive
{

	Triangle::Triangle()
		:Triangle(1.0f, 1.0f)
	{

	}

	Triangle::Triangle(float width, float height)
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

		auto mesh = Make_Ref<FMesh>();
		mesh->SetVerticesAndIndices(m_Vertices, m_Indices, m_Faces);
		mesh->SetMaterial(AssetManager::Get<Material>("WorldDefault"));
		AddMesh(0, mesh);
	}

}