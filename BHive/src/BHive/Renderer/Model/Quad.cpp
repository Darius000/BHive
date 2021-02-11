#include "BHivePCH.h"
#include "Quad.h"

namespace BHive
{
	Quad::Quad()
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

		auto quad = Make_Ref<FMesh>();

		quad->SetVerticesAndIndices(m_Vertices, m_Indices, m_Faces);
		quad->SetMaterial(AssetManager::Get<Material>("WorldDefault"));
		AddMesh(0, quad);		
	}
}