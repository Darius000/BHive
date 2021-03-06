#pragma once

namespace BHive
{
	class Quaternion
	{
	public:
		Quaternion();
		Quaternion(const Quaternion& other);
		Quaternion(const glm::mat4& matrix);
		Quaternion(const Vector3<float>& axis, float angle);

		float x, y, z, w;

		static Quaternion FromEuler(const Rotator& angles);
		static Quaternion FromEuler(float pitch, float yaw, float roll);	
		glm::mat4 ToMatrix();
		Rotator ToRotator();

		glm::quat m_Quaternion;

	private:
		static float ToRadians(const float& degrees);
	};
}