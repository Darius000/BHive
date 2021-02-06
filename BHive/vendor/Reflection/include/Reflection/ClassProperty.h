#pragma once

#include "Property.h"

namespace Reflection
{
	#define String(x) #x

	template<typename T>
	class ClassProperty : public Property<T>
	{
	public:
		using Properties = std::unordered_map<std::string, IProperty*>;
		using PropertyIterator = Properties::iterator;

		ClassProperty(){};
		ClassProperty(const std::string& name, T* val, const std::vector<IProperty*>& _properties)
			:Property<T>(name, val)
		{
			AddProperties(_properties);
		}


		~ClassProperty() = default;


		void AddProperty(IProperty* property)
		{
			if (properties.find(property->GetName()) == end())
			{
				properties.insert({ property->GetName(), property });
			}
		}

		void AddProperties(const std::vector<IProperty*>& _properties)
		{
			for (auto property : _properties)
			{
				AddProperty(property);
			}
		}

		void RemoveProperty(const std::string& name)
		{
			if (properties.find(name) != end())
			{
				properties.erase(name);
			}
		}

		template<typename U>
		Property<U>& GetProperty(const std::string& name)
		{
			return *(Property<U>*)properties[name];
		}

		PropertyIterator begin() { return properties.begin(); }
		PropertyIterator end() { return properties.end(); }

		Properties GetProperties() { return properties; }
		Properties properties;
	};
}

#define DEFINE_CLASS(type)\
	using type##Class = ClassProperty<type>;

#define Begin_Class(type)\
	Reflection::type##Class Class = { this,

#define Add_Property(type, prop)\
	new Reflection::Property<type>{#prop, &(T::prop)},

#define End_Class()\
	};\
	Reflection::type##Class& GetClass() { return Class; }