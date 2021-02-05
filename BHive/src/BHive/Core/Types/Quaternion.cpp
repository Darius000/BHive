#include "BHivePCH.h"
#include "Quaternion.h"

namespace BHive
{

	Quaternion::Quaternion(const Vector3<float>& axis, float angle)
	{
		float rangle = ToRadians(angle);

		w = cos(rangle / 2);

		x = (axis.x) * sin(rangle / 2);
		y = (axis.y) * sin(rangle / 2);
		z = (axis.z) * sin(rangle / 2);
		m_Quaternion = glm::quat(w, x, y, z);
	}

	Quaternion::Quaternion()
		:w(), x(), y(), z(), m_Quaternion()
	{

	}

	Quaternion::Quaternion(const Quaternion& other)
	{
		x =	other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		m_Quaternion = other.m_Quaternion;
	}

	Quaternion::Quaternion(const glm::mat4& matrix)
		:Quaternion()
	{
		m_Quaternion = glm::quat(matrix);
	}


	float Quaternion::ToRadians(const float& degrees)
	{
		return degrees  * ((22.0f / 7.0f) / 360.0f);
	}

	glm::mat4 Quaternion::ToMatrix(const Quaternion& quat)
	{
		float xx = quat.x * quat.x;
		float yy = quat.y * quat.y;
		float zz = quat.z * quat.z;
		float xy = quat.x * quat.y;
		float zw = quat.z * quat.w;
		float xz = quat.x * quat.z;
		float yw = quat.y * quat.w;
		float yz = quat.y * quat.z;
		float xw = quat.x * quat.w;

		float r0c0 = 1 - 2 * yy - 2 * zz;
		float r0c1 = 2 * xy - 2 * zw;
		float r0c2 = 2 * xz + 2 * yw;
		float r1c0 = 2 * xy + 2 * zw;
		float r1c1 = 1 - 2 * xx - 2 * zz;
		float r1c2 = 2 * yz + 2 * xw;
		float r2c0 = 2 * xz - 2 * yw;
		float r2c1 = 2 * yz + 2 * xw;
		float r2c2 = 1 - 2 * xx - 2 * yy;

		auto m0 =  glm::mat3(
			{ r0c0, r0c1, r0c2},
			{ r1c0, r1c1, r1c2 },
			{ r2c0, r2c1, r2c2 }
		); 

		return glm::toMat4(quat.m_Quaternion);
	}

	Rotator Quaternion::ToRotator(const Quaternion& quat)
	{
		//x is pitch, y is yaw, z is roll
		glm::vec3 euler = glm::eulerAngles(quat.m_Quaternion);

		float pitch = MathLibrary::ToDegrees(euler.x);
		float yaw = MathLibrary::ToDegrees(euler.y);
		float roll = MathLibrary::ToDegrees(euler.z);

		return Rotator(roll, yaw, pitch);
	}

	Quaternion Quaternion::FromEuler(float pitch, float yaw, float roll)
	{
		float ryaw = ToRadians(yaw);
		float rpitch = ToRadians(pitch);
		float rroll = ToRadians(roll);

		//yaw
		float cy = cos(ryaw / 2);
		float sy = sin(ryaw / 2);

		//pitch
		float cp = cos(rpitch / 2);
		float sp = sin(rpitch / 2);

		//roll
		float cr = cos(rroll / 2);
		float sr = sin(rroll / 2);

		Quaternion quat;
		quat.m_Quaternion = glm::quat({rpitch, ryaw,  rroll});
		/*quat.w = cr * cp * cy - sr * sp * sy;
		quat.x = sr * cp * cy + cr * sp * sy;
		quat.y = cr * sp * cy + sr * cp * sy;
		quat.z = cr * cp * sy - sr * sp * cy;*/

		return quat;
	}

	Quaternion Quaternion::FromEuler(const Rotator& angles)
	{
		return FromEuler(angles.pitch, angles.yaw, angles.roll);
	}

}