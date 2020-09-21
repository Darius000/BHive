#pragma once


namespace BHive
{
	class Camera
	{
	public:
		Camera();
		Camera(glm::mat4 projection);

	public:
		glm::mat4 GetProjection() const { return m_Projection; }
	protected:
		glm::mat4 m_Projection = glm::mat4(1.0f);
	};
}