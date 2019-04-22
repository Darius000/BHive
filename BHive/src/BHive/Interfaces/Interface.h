#pragma once

namespace BHive
{
	class IInterface
	{
	public:
		template<typename T, typename Interface>
		static bool HasInterface();
	};

	template<typename T, typename Interface>
	bool BHive::IInterface::HasInterface()
	{
		return std::is_base_of<T, Interface>::value;
	}

}
