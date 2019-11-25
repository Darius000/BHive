#pragma once
#include <iostream>

namespace BHive
{
	template<class T>
	class BArray
	{
	public:
		BArray()
		{
			m_items = new T[DEFAULT_SIZE];
			m_length = DEFAULT_SIZE;
		}

		BArray(size_t size)
		{
			m_items = new T[size];
			m_length = size;
		}

		BArray(const T* items)
		{
			m_items = new T[sizeof(items) / sizeof(T)];

			uint64_t j = (uint64_t)0;

			while (items != nullptr)
			{
				m_items[j] = items;
				items++;
			}
		}

		~BArray()
		{
			delete[] m_items;
		}

		T* operator[](uint64_t index) const
		{
			return m_items[index];
		}

	protected:
		void MoveElementsLeft(uint64_t index)
		{
			uint64_t i = index;
			while (i < m_length)
			{
				std::cout << "i + 1 replaces i" << std::endl;
				//m_items[i] = m_items[i + 1];
				i++;
			}
		}

		void MoveElementsRight(uint64_t index)
		{
			uint64_t i = index;
			while (i < m_length)
			{
				std::cout << "i  replaces i + 1" << std::endl;
				//m_items[i + 1] = m_items[i];
				i++;
			}

		}

	private:
		T* m_items;
		size_t m_length;
	};
}