#pragma once

#include "Core.h"

namespace BHive
{
	class BHive_API String
	{
	private:
		char* m_Buffer;
		size_t m_Size;

	public:
		String();
		String(const char* string);
		String(const String& other);
		~String();
		unsigned int GetSize() const;
		char& operator[](unsigned int index);
		String& operator=(String string) noexcept;
		//String& operator+(String string);
		//String& operator+(const char* string);
		//static String& FromInt(const int number);
		void Swap(String& string) noexcept;
		friend std::ostream& operator<<(std::ostream& stream, const String& string);
	};

	inline std::ostream& operator<<(std::ostream& stream, const String& string);

	void Print(const String& string);
}
