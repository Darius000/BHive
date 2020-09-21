#pragma once

namespace BHive
{ 
	struct FVertex
	{	
		FVertex(){}
		FVertex(Vector3<float> Position, LinearColor4 Color, Vector2<float> TexCoord, Vector3<float> Normal)
			:m_Position(Position), m_Color(Color), m_TexCoord(TexCoord), m_Normal(Normal)
		{
		
		}

		Vector3<float> m_Position;
		LinearColor4 m_Color;
		Vector2<float> m_TexCoord;
		Vector3<float> m_Normal;
	};
}
