#pragma once
#include <iostream>

namespace BHive
{
	template<class T, size_t Size>
	class BArray
	{
	public:
		BArray()
		{
			
		}

		size_t GetSize() { return Size; }

		T* operator[](uint64_t index) const
		{
			return m_items[index];
		}

	protected:
		

	private:
		T m_items[Size];
	};
}