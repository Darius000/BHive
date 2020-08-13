#pragma once
#include "BHive/Core/PlatformDataTypes.h"
#include "BHive/Core/Log.h"

namespace BHive
{
	template<class T, size_t Size>
	class Array
	{
	public:
		Array();
		Array(const Array& other);
	
	public:
		size_t GetSize();

	public:
		T& operator[](uint64 index);
		const T& operator[](uint64 index) const;
		Array& operator=(const Array& other);

	private:
		T m_items[Size];
	};

	template<class T, size_t Size>
	Array<T, Size>& Array<T, Size>::operator=(const Array& other)
	{
		for (uint32 i = 0; i < Size; i++)
		{
			m_items[i] = other.m_items[i];
		}
	}

	template<class T, size_t Size>
	T& Array<T, Size>::operator[](uint64 index)
	{
		BH_CORE_ASSERT((index < Size || index >= 0), "Index is out of range!");

		return m_items[index];
	}

	template<class T, size_t Size>
	Array<T, Size>::Array(const Array& other)
	{
		if(&other == this)
			return this;

		for (uint32 i = 0; i < Size; i++)
		{
			m_items[i] = other.m_items[i];
		}
	}

	template<class T, size_t Size>
	Array<T, Size>::Array()
	{

	}

	template<class T, size_t Size>
	size_t Array<T, Size>::GetSize()
	{
		return Size;
	}

	template<class T, size_t Size>
	const T& Array<T, Size>::operator[](uint64 index) const
	{

		BH_CORE_ASSERT((index < Size || index >= 0 ), "Index is out of range!");

		return m_items[index];
	}

}