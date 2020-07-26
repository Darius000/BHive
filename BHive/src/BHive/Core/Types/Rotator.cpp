#include "BHivePCH.h"
#include "Rotator.h"


namespace BHive
{
	Rotator::Rotator()
		:roll(0.0f), yaw(0.0f), pitch(0.0f)
	{

	}

	Rotator::Rotator(float _roll, float _yaw, float _pitch)
		:roll(_roll), yaw(_yaw), pitch(_pitch)
	{
		
	}

	Rotator::Rotator(const FVector3& vector)
		:Rotator(vector.x, vector.y, vector.z)
	{

	}

	Rotator Rotator::FromVector(const FVector3& v)
	{
		return Rotator(v.x, v.y, v.z);
	}

	void Rotator::Normalize()
	{
		roll	= MathLibrary::ModuloAngle(roll, 360.0f);
		yaw		= MathLibrary::ModuloAngle(yaw, 360.0f);
		pitch	= MathLibrary::ModuloAngle(pitch, 360.0f);
	}

	void Rotator::NormalizeAxis(EAxis axis)
	{
		if (axis == EAxis::X) {roll = MathLibrary::ModuloAngle(roll, 360.0f); return;}
		if (axis == EAxis::Y) {yaw = MathLibrary::ModuloAngle(yaw, 360.0f); return;}
		if (axis == EAxis::Z) {pitch = MathLibrary::ModuloAngle(pitch, 360.0f); return;}
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
		if (axis == EAxis::X) return roll;
		if (axis == EAxis::Y) return yaw;
		return pitch;
	}

	FVector3 Rotator::ToVector() const
	{
		return FVector3(roll, yaw, pitch);
	}

	BString Rotator::ToString() const
	{
		return Format("{ %f, %f, %f }", roll, yaw, pitch);
	}

	Rotator Rotator::operator+(const Rotator& r)
	{
		return Rotator(roll + r.roll, yaw + r.yaw, pitch + r.pitch);
	}

	Rotator Rotator::operator-(const Rotator& r)
	{
		return Rotator(roll - r.roll, yaw - r.yaw, pitch - r.pitch);
	}

	Rotator Rotator::operator-=(const Rotator& r)
	{
		return *this = *this - r;
	}

	Rotator Rotator::operator/(float s)
	{
		return Rotator(roll / s, yaw / s, pitch / s);
	}

	Rotator Rotator::operator/=(float s)
	{
		return *this = *this / s;
	}

	Rotator Rotator::operator*(float s)
	{
		return Rotator(roll * s, yaw * s, pitch * s);
	}

	Rotator Rotator::operator*=(float s)
	{
		return *this = *this * s;
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
		return *this = *this + r;
	}
}