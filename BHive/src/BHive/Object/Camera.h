#pragma once


namespace BHive
{
	/*enum class Projection : uint32
	{
		Orthographic = 0,
		Perspective = 1
	};

	struct OrthographicSettings
	{
		float Right = 1.0f;
		float Left = -1.0f;
		float Bottom = -1.0f;
		float Top = 1.0f;
		float Near = -1.0f;
		float Far = 1.0f;
	};

	struct PerspectiveSettings
	{
		float FieldofView = 35.0f;
		FVector2 AspectRatio = FVector2(16.0f, 9.0f);
		float Near = .01f;
		float Far = 1000.0f;
	};*/

	class Camera
	{
	public:
		Camera();
		Camera(glm::mat4 projection);
		//Camera(Projection projection );
	//
	//public:
	//	void SetPerspective(PerspectiveSettings perspective);
	//	void SetOthographic(OrthographicSettings orthographic);

	public:
		glm::mat4 GetProjection() const { return m_Projection; }

	/*public:
		OrthographicSettings m_OrthoSettings;
		PerspectiveSettings m_PerspSettings;
		Projection m_ProjectionType;*/
	protected:
		glm::mat4 m_Projection = glm::mat4(1.0f);
	};
}