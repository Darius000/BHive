#include "BHivePCH.h"
#include "Cube.h"

namespace BHive
{

	Cube::Cube()
		:Cube(1.0f, 1.0f , 1.0f)
	{

	}

	Cube::Cube(float size)
		: Cube(size, size, size)
	{

	}


	Cube::Cube(float width, float height, float length)
	{
		width = width / 2.0f;
		height = height / 2.0f;
		length = length / 2.0f;

		FVector3 frontS[] = {
			{ -width, -height, length },
			{ width, -height, length },
			{ width, height, length },
			{ -width, height, length}
		};

		FVector3 backS[] = {
			{ width, -height, -length },
			{ -width, -height, -length },
			{ -width, height, -length},
			{ width, height, -length }
		};

		FVector3 topS[] = {
			{ -width, height, length },
			{ width, height, length },
			{ width, height, -length},
			{ -width, height, -length }
		};

		FVector3 bottomS[] = {
			{ width, -height, length },
			{ -width, -height, length },
			{ -width, -height, -length},
			{ width, -height, -length }
			
		};

		FVector3 leftS[] = {
			{ width, -height, length },
			{ width, -height, -length },
			{ width, height, -length},
			{ width, height, length }
			
		};

		FVector3 rightS[] = {
			{ -width, -height, -length },
			{ -width, -height, length },
			{ -width, height, length },
			{ -width, height, -length}
		};

		auto bottom = CreateSide(bottomS, { 0.0f, -1.0f, 0.0f }, 0);
		auto top = CreateSide(topS, { 0.0f, 1.0f, 0.0f }, 1);
		auto right = CreateSide(rightS, { -1.0f, 0.0f, 0.0f }, 2);
		auto left = CreateSide(leftS, { 1.0f, 0.0f, 0.0f }, 3);
		auto front = CreateSide(frontS, { 0.0f, 0.0f, 1.0f }, 4);
		auto back = CreateSide(backS, { 0.0f, 0.0f, -1.0f }, 5);

		FaceData cubeFaceData;
		
		//Append vertices together
		AppendFace(cubeFaceData, bottom);
		AppendFace(cubeFaceData, top);
		AppendFace(cubeFaceData, right);
		AppendFace(cubeFaceData, left);
		AppendFace(cubeFaceData, front);
		AppendFace(cubeFaceData, back);

		AddFaceMesh(cubeFaceData, 0);
	}


	FaceData Cube::CreateSide(FVector3 sizes[4], const FVector3& direction, uint32 offset)
	{
		std::vector<FVertex> vertices =
		{
			FVertex(sizes[0], {0.0f, 0.0f, 0.0f},	{0.0f, 0.0f}, direction),
			FVertex(sizes[1], {0.0f, 0.0f, 0.0f},	{1.0f, 0.0f}, direction),
			FVertex(sizes[2], {0.0f, 0.0f, 0.0f},	{1.0f, 1.0f}, direction),
			FVertex(sizes[3], {0.0f, 0.0f, 0.0f},	{0.0f, 1.0f}, direction)
		};

		//set indices to be offset by multiples of three
		std::vector<uint32> indices =
		{
			0 +  (3 * offset) + offset, 1 + (3 * offset) + offset, 2 + (3 * offset) + offset
			, 2 + (3 * offset) + offset, 3 + (3 * offset) + offset, 0 + (3 * offset) + offset
		};

		std::vector<FFace> faces =
		{
			{{0 + (3 * offset) + offset, 1 + (3 * offset) + offset, 2 + (3 * offset) + offset}},
			{{2 + (3 * offset) + offset, 3 + (3 * offset) + offset, 0 + (3 * offset) + offset}}
		};

		return FaceData(vertices, indices, faces);
	}

	void Cube::AppendFace(FaceData& face, const FaceData& data)
	{
		//Append data vertices
		auto& vertices = face.m_Vertices;
		size_t sizeV = vertices.size();
		vertices.insert(vertices.begin() + sizeV, data.m_Vertices.begin(), data.m_Vertices.end());

		//Append indices
		auto& indices = face.m_Indices;
		size_t sizeI = indices.size();
		indices.insert(indices.begin() + sizeI, data.m_Indices.begin(), data.m_Indices.end());

		//append faces
		auto& faces = face.m_Faces;
		size_t sizeF = faces.size();
		faces.insert(faces.begin() + sizeF, data.m_Faces.begin(), data.m_Faces.end());
	}

	void Cube::AddFaceMesh(const FaceData& data, uint32 id)
	{
		auto mesh = Make_Ref<FMesh>();
		mesh->SetVerticesAndIndices(data.m_Vertices,
			data.m_Indices, data.m_Faces);
		mesh->SetMaterial(AssetManager::Get<Material>("WorldDefault"));
		AddMesh(id, mesh);
	}

}