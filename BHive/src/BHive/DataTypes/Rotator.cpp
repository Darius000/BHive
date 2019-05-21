#include "BHivePCH.h"
#include "Rotator.h"


namespace BHive
{
	Rotator::Rotator()
	{

	}

	Rotator::Rotator(float _roll, float _yaw, float _pitch)
		:roll(_roll), yaw(_yaw), pitch(_pitch)
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

	void Rotator::Normalize()
	{
		roll	= MathLibrary::ModuloAngle(roll, 360.0f);
		yaw		= MathLibrary::ModuloAngle(yaw, 360.0f);
		pitch	= MathLibrary::ModuloAngle(pitch, 360.0f);
	}

	void Rotator::NormalizeAxis(EAxis axis)
	{
		if (axis == X) roll = MathLibrary::ModuloAngle(roll, 360.0f); return;
		if (axis == Y) yaw = MathLibrary::ModuloAngle(yaw, 360.0f); return;
		if (axis == Z) pitch = MathLibrary::ModuloAngle(pitch, 360.0f); return;
	}

	bool Rotator::IsNearlyZero(float tolerance)
	{
		return (roll <= tolerance) && 
			(yaw <= tolerance) && 
			(pitch <= tolerance);
	}

	bool Rotator::IsZero()
	{
		return (roll == 0.0f) && 
			(yaw == 0.0f) && 
			(pitch == 0.0f);
	}

	bool Rotator::IsNAN() const
	{
		return MathLibrary::IsInfinte(roll) || MathLibrary::IsInfinte(yaw) || MathLibrary::IsInfinte(pitch) ||
			MathLibrary::IsUndefinded(roll) || MathLibrary::IsUndefinded(yaw) || MathLibrary::IsUndefinded(pitch);
	}

	float Rotator::GetAxis(EAxis axis) const
	{
		if (axis == X) return roll;
		if (axis == Y) return yaw;
		return pitch;
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