#pragma once

//namespace BHive
//{ 
//	enum class EPropertyType
//	{
//		INT, FLOAT, DOUBLE, CHAR, VECTOR3, VECTOR2, COLOR, VECTOR4
//	};
//
//	class MetaData
//	{
//	public:
//		MetaData(const char* name, EPropertyType type, unsigned int size)
//			:m_Type(type), m_Name(name), m_Size(size){}
//		~MetaData(){}
//
//		const char* GetName() const { return m_Name; }
//		EPropertyType GetType() const { return m_Type; }
//		unsigned int GetSize() const { return m_Size;}
//
//	private:
//		EPropertyType m_Type;
//		const char* m_Name;
//		unsigned int m_Size;
//	};
//
//	template<typename T>
//	class Property
//	{
//	public:
//		explicit Property(const char* name,  EPropertyType type, T& data) :
//			PropertyBase(name, type), m_Value(data){}
//
//		Property& operator=(const T& data)
//		{
//			value = data; return *this;
//		}
//
//		Property& operator=(const Property& other)
//		{
//			this->m_Value = other.m_Value;
//			return *this;
//		}
//
//		operator T() const { return m_Value; }
//		operator T&() { return m_Value; }
//
//	private:
//		Property(const Property&) = default;
//
//		T m_Value;
//	};
//
//	template<typename T>
//	class ReadOnlyProperty 
//	{
//	public:
//		explicit ReadOnlyProperty(const char* name, EPropertyType type, T& data) :
//			PropertyBase(name, type), m_Value(data) {}
//
//
//		operator T() const { return m_Value; }
//		operator const T& () { return m_Value; }
//
//	private:
//		ReadOnlyProperty(const ReadOnlyProperty&) = default;
//
//		T m_Value;
//	};
//
//	template<typename EnumClass>
//	class Enum : public Property<EnumClass>
//	{
//	public:
//
//		/*EnumClass operator |(EnumClass a, EnumClass b) { return static_cast<EnumClass>(static_cast<T>(a) | static_cast<T>(b)); }; 
//		EnumClass operator &(const EnumClass& a, const EnumClass& b) { return static_cast<EnumClass>(static_cast<T>(a) & static_cast<T>(b)); }; 
//		EnumClass& operator |=(EnumClass& a, EnumClass b) { return a = a | b; };*/
//	};
//}

