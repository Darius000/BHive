#include "BHivePCH.h"
#include "Rotator.h"


namespace BHive
{

	Rotator::Rotator(float _roll, float _yaw, float _pitch)
		:Rotator()
	{
		roll = _roll;
		pitch = _pitch;
		yaw = _yaw;

		Clamp();
	}

	Rotator::Rotator()
		:roll(), pitch(), yaw()
	{

	}

	Rotator::Rotator(const Vector3& vector)
		:Rotator(vector.x, vector.y, vector.z)
	{

	}

	Rotator Rotator::FromVector(const Vector3& v)
	{
		return Rotator(v.x, v.y, v.z);
	}

	Rotator Rotator::Add(const Rotator& a, const Rotator& b)
	{
		float x = a.roll + b.roll;
		float y = a.yaw + b.yaw;
		float z = a.pitch + b.pitch;

		return Rotator(x, y, z);
	}

	Rotator Rotator::Substract(const Rotator& a, const Rotator& b)
	{
		float x = a.roll - b.roll;
		float y = a.yaw - b.yaw;
		float z = a.pitch - b.pitch;

		return Rotator(x, y, z);
	}

	Rotator Rotator::Multiply(const Rotator& a, float s)
	{
		float x = a.roll * s;
		float y = a.yaw * s;
		float z = a.pitch * s;

		return Rotator(x, y, z);
	}

	Rotator Rotator::Divide(const Rotator& a, float s)
	{
		float x = a.roll / s;
		float y = a.yaw / s;
		float z = a.pitch / s;

		return Rotator(x, y, z);
	}

	Rotator Rotator::Clamp()
	{
		roll	= MathLibrary::ModuloAngle(roll, 360.0f);
		yaw		= MathLibrary::ModuloAngle(yaw, 360.0f);
		pitch	= MathLibrary::ModuloAngle(pitch, 360.0f);
		return *this;
	}

	bool Rotator::IsNAN() const
	{
		return IsInfinte(roll) || IsInfinte(yaw) || IsInfinte(pitch) ||
			IsUndefinded(roll) || IsUndefinded(yaw) || IsUndefinded(pitch);
	}

	float Rotator::GetAxis(EAxis axis) const
	{
		if (axis == X) return roll;
		else if (axis == Y) return yaw;
		else return pitch;
	}

	Vector3 Rotator::ToVector() const
	{
		return Vector3(roll, yaw, pitch);
	}

	std::string Rotator::ToString() const
	{
		return "{ roll:" + NumToString(roll) + ", yaw:" + NumToString(yaw) + ", pitch:" + NumToString(pitch) + "}";
	}

	Rotator Rotator::operator+(const Rotator& r)
	{
		return Add(*this, r);
	}

	Rotator Rotator::operator-(const Rotator& r)
	{
		return Substract(*this, r);
	}

	Rotator Rotator::operator-=(const Rotator& r)
	{
		return *this = Substract(*this, r);
	}

	Rotator Rotator::operator/(float s)
	{
		return Divide(*this, s);
	}

	Rotator Rotator::operator/=(float s)
	{
		return *this = Divide(*this, s);
	}

	Rotator Rotator::operator*(float s)
	{
		return Multiply(*this, s);
	}

	Rotator Rotator::operator*=(float s)
	{
		return *this = Multiply(*this, s);
	}

	float Rotator::operator[](unsigned int index)
	{
		if (index <= 0) return roll;
		else if (index == 1) return yaw;
		else return pitch;
	}

	const Rotator Rotator::Zero()
	{
		return Rotator();
	}

	bool Rotator::operator!=(const Rotator& r)
	{
		return (yaw != r.yaw) && (roll != r.roll) && (pitch != r.pitch);
	}

	bool Rotator::operator==(const Rotator& r)
	{
		return (yaw == r.yaw) && (roll == r.roll) && (pitch == r.pitch);
	}

	Rotator Rotator::operator+=(const Rotator& r)
	{
		return *this = Add(*this, r);
	}

}