#include "BHivePCH.h"
#include "Quaternion.h"

namespace BHive
{

	Quaternion::Quaternion(const Vector3<float>& axis, float angle)
	{

#if DEGREE_ANGLES
		float rangle = ToRadians(angle);
#else
		float rangle = angle;
#endif
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

	glm::mat4 Quaternion::ToMatrix()
	{
		float xx = x * x;
		float yy = y * y;
		float zz = z * z;
		float xy = x * y;
		float zw = z * w;
		float xz = x * z;
		float yw = y * w;
		float yz = y * z;
		float xw = x * w;

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

		return glm::toMat4(m_Quaternion);
	}

	Rotator Quaternion::ToRotator()
	{
		//x is pitch, y is yaw, z is roll
		glm::vec3 euler = glm::eulerAngles(m_Quaternion);

		float pitch, yaw, roll = 0.0f;

#if DEGREE_ANGLES
		pitch = MathLibrary::ToDegrees(euler.x);
		yaw  = MathLibrary::ToDegrees(euler.y);
		roll = MathLibrary::ToDegrees(euler.z);
#else

		pitch = euler.x;
		yaw = euler.y;
		roll = euler.z;
#endif
		return Rotator(roll, yaw, pitch);
	}

	Quaternion Quaternion::FromEuler(float pitch, float yaw, float roll)
	{

		float ryaw, rpitch, rroll;

#if DEGREE_ANGLES
		ryaw = ToRadians(yaw);
		rpitch = ToRadians(pitch);
		rroll = ToRadians(roll);
#else
		ryaw = yaw;
		rpitch = pitch;
		rroll = roll;
#endif
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