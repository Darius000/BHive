#ifndef IInterface_H
#define IInterface_H

namespace BHive
{
	class IInterface
	{
	public:
		template<typename T, typename Interface>
		static bool HasInterface();
	};

	template<typename T, typename Interface>
	bool IInterface::HasInterface()
	{
		return std::is_base_of<T, Interface>::value;
	}

}

#endif
