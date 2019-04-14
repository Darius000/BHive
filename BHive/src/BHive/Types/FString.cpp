#include "BHivePCH.h"
#include "FString.h"

namespace BHive
{
	String::String()
		:m_Size(0)
	{
		m_Buffer = new char[m_Size + 1];
		m_Buffer[m_Size] = 0;
	}

	String::String(const char* string)
	{
		m_Size = strlen(string);
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, string, m_Size + 1);
		m_Buffer[m_Size] = 0;
	}

	String::String(const String& other)
		:m_Size(other.m_Size)
	{
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
	}

	String::~String()
	{
		delete[] m_Buffer;
	}

	unsigned int String::GetSize() const
	{
		return (unsigned int)m_Size;
	}

	char& String::operator[](unsigned int index)
	{
		if (index < 0 || index > m_Size - 1)
		{
			return m_Buffer[0];
		}


		return m_Buffer[index];
	}

	String& String::operator=(String string) noexcept
	{
		string.Swap(*this);
		return *this;
	}

	/*BHive::String& String::operator+(String string)
	{
		strcpy(m_Buffer, string.m_Buffer);
		m_Size = strlen(m_Buffer);
		m_Buffer = new char[m_Size + 1];
		m_Buffer[m_Size] = 0;
		return *this;
	}*/

	/*BHive::String& String::operator+(const char* string)
	{
		return string;
	}*/

	/*BHive::String& String::FromInt(const int number)
	{
		String newString("");
		memcpy(newString.m_Buffer,(void*)number, sizeof(number));
		return newString;
	}*/

	void String::Swap(String& string) noexcept
	{
		std::swap(m_Buffer, string.m_Buffer);
		std::swap(m_Size, string.m_Size);
	}

	std::ostream& operator<<(std::ostream& stream, const String& string)
	{
		stream << string.m_Buffer;
		return stream;
	}

	void Print(const String& string)
	{
		std::cout << string << "\n";
	}

}