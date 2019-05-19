#pragma once

namespace BHive
{
	inline bool operator==(const Object& a, const Object& b)
	{
		return (a.GetObjectID() == b.GetObjectID());
	}

	inline std::ostream& operator<<(std::ostream& os, const Object& object)
	{
		return os << object.ToString();
	}
}