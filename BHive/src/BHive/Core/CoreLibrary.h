#ifndef CORELIBRARY_H
#define CORELIBRARY_H

namespace BHive
{
	struct CoreLibrary
	{
		template<typename T>
		static const char* GetVariableType(T t)
		{
			return typeid(t).name();
		}
	};
}

#endif