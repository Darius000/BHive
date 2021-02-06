#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <ostream>
#include <fstream>

#include "IProperty.h"

namespace Reflection
{ 
	template<typename T>
	class Property : public IProperty
	{
	public:
		Property(const std::string& propertyName, T* val, 
			PropertyTags tags = (PropertyTags)0, 
			PropertyMetaData metaData = (PropertyMetaData)0
		)
			:name(propertyName), value(val), tags(tags), metaData(metaData)
		{}

		Property(const Property<T>& other)
		{ 
			value = other.value;
			name = other.name;
			tags = other.tags;
			metaData = other.metaData;
		}

		virtual ~Property() = default;

		virtual bool operator==(const Property<T>& prop) const { return	*value ==	*prop.value; }
		virtual bool operator!=(const Property<T>& prop) const { return	*value !=	*prop.value; }
		virtual bool operator>=(const Property<T>& prop) const { return	*value >=	*prop.value; }
		virtual bool operator<=(const Property<T>& prop) const { return	*value <=	*prop.value; }
		virtual bool operator>(const Property<T>& prop) const { return	*value >	*prop.value; }
		virtual bool operator<(const Property<T>& prop) const { return	*value <	*prop.value; }
		virtual bool operator==(const T&  v) const	{ return *value ==	v; }
		virtual bool operator!=(const T&  v) const	{ return *value !=	v; }
		virtual bool operator>=(const T&  v) const	{ return *value >=	v; }
		virtual bool operator<=(const T&  v) const	{ return *value <=	v; }
		virtual bool operator>(const T& v) const		{ return *value >	v; }
		virtual bool operator<(const T& v) const		{ return *value <	v; }
		Property<T>& operator=(const Property<T>& prop)
		{
			value = prop.value;
			name = prop.name;
			tags = prop.tags;
			metaData = prop.metaData;
			return *this;
		}

		T& operator =(const T& v) {return *value = v;  }
		T* operator =(T* v) { return value = v; }

		virtual const T& operator()() const { return *value; }
		virtual explicit operator const T& () const { return *value; }
		virtual T* operator->() { return value; }

		friend std::ostream& operator<<(std::ostream& os, const Property<T>& prop)
		{	
			os << *prop.value;
			return os;
		}
		friend std::fstream& operator>>(std::fstream& is, Property<T>& prop)
		{
			is >> *prop.value;
			return is;
		}
		

		//IProperty Begin
		std::string GetName() override {  return name; }
		std::string GetTypeName() override { return "none"; };
		const PropertyTags& GetTags() const override { return tags; }
		const PropertyMetaData& GetMetaData() const override { return metaData; }
		void PrintValue() const override { std::cout << *this << "\n"; }
		//IProperty End

	protected:

		T* value;
		std::string name;
		PropertyTags tags;
		PropertyMetaData metaData;
	};

	#define DEFINE_OPERATOR_EQUALS(classname, type)\
		classname& operator=(const type & v) { *value = v; return *this; }
	


	#define DEFINE_PROPERTY_TYPE(classname, type)\
		class classname##Property : public Property<type>\
		{\
		public:\
			classname##Property(const std::string& propertyName, type* val,\
				PropertyTags tags = (PropertyTags)0, PropertyMetaData metaData = (PropertyMetaData)0)\
				:Property<type>(propertyName, val, tags, metaData){}\
			std::string GetTypeName(){ return #type; }\
			DEFINE_OPERATOR_EQUALS(classname##Property, type)\
		};

	#define DEFINE_PROPERTY(name, type)\
		DEFINE_PROPERTY_TYPE(name, type)
}

