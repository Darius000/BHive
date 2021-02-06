#pragma once

#include <memory>

namespace Reflection
{
	class IRegisterable
	{
	public:
		static std::shared_ptr<IRegisterable> MakeRegisterable()
		{
			return std::make_shared<IRegisterable>();
		}
	};

	template<typename T>
	class IRegisterableType : public IRegisterable
	{

	};
}