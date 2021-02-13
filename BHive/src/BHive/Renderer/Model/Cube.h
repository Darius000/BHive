#pragma once

#include "Model.h"

namespace BHive
{
	struct FaceData
	{
		FaceData() = default;

		FaceData(const std::vector<FVertex>& vertices,
			const std::vector<uint32>& indices,
			const std::vector<FFace>& faces)
		{
			m_Vertices = vertices;
			m_Indices = indices;
			m_Faces = faces;
		}

		std::vector<FVertex> m_Vertices;
		std::vector<uint32> m_Indices;
		std::vector<FFace> m_Faces;
	};

	//Creates a default cube model
	class Cube : public Model
	{
	public:
		Cube();
		Cube(float size);
		Cube(float width, float height, float length);

	private:
		/*create a specific side of a cube
		@Param size , size of face
		@Param direction, normal direction
		@Param offset, the offset of the vertices and indices
		*/
		 FaceData CreateSide(FVector3 sizes[4], const FVector3& direction, uint32 offset);

		 //Append face into single object
		 void AppendFace(FaceData& vector, const FaceData& data);

		 void AddFaceMesh(const FaceData& data, uint32 id);
	};

}