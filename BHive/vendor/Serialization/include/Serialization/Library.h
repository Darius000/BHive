#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "TypeTraits.h"

namespace Serialization
{

	//-------------------------
	//Binary
	//-------------------------


	

	///----------------
	///Read
	///----------------

	template<typename T>
	inline void ReadBinary(std::fstream& fs, T& o)
	{
		fs.read(reinterpret_cast<char*>(&o), GetSize(o));
	};

	template<>
	inline void ReadBinary(std::fstream& fs, std::string& o)
	{
		size_t size = 0;
		fs.read(reinterpret_cast<char*>(&size), sizeof(size_t));
		o.resize(size);
		fs.read(reinterpret_cast<char*>(&o[0]), size);
	};

	template<typename U>
	inline void ReadBinaryVector(std::fstream& fs, std::vector<U>& o)
	{		
		size_t numElements = 0;	
		fs.read(reinterpret_cast<char*>(&numElements), sizeof(size_t));
		o.resize(numElements);

		for (size_t i = 0; i < numElements; i++)
		{		
			U element;
			ReadBinary(fs, element);
			o[i] = std::move(element);
		}
	};

	///----------------
	///Write
	///----------------


	template<typename T>
	inline void WriteBinary(std::fstream& fs, const T& o)
	{
		fs.write(reinterpret_cast<const char*>(&o), GetSize(o));
	};

	template<>
	inline void WriteBinary(std::fstream& fs, const std::string& o)
	{
		size_t size = GetSize(o);
		fs.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
		fs.write(reinterpret_cast<const char*>(&o[0]), size);
	};

	template<typename U>
	inline void WriteBinaryVector(std::fstream& fs, const std::vector<U>& o)
	{		
		size_t numElements = o.size();
		
		fs.write(reinterpret_cast<const char*>(&numElements), sizeof(size_t));

		for (size_t i = 0; i < numElements; i++)
		{
			U element = o[i];
			WriteBinary(fs, element);
		}
	};

	//----------------------------
	//ASCI
	//----------------------------
	template<typename T> inline void Read(T& o){};
	template<typename T> inline void Write(const T& o){};

	template<typename T>
	inline void Read(std::fstream& fs, T& o)
	{
		fs >> o;
	};

	template<>
	inline void Read(std::fstream& fs, std::string& o)
	{
		std::getline(fs, o);
	};

	template<typename U>
	inline void ReadVector(std::fstream& fs, std::vector<U>& o)
	{
		class my_c_type : public std::ctype<char>
		{
			mask my_table[table_size];
		public:
			my_c_type(size_t refs = 0)
				:std::ctype<char>(&my_table[0], false, refs)
			{
				std::copy_n(classic_table(), table_size, my_table);
				my_table[','] = (mask)space;
				my_table['\n'] = (mask)space;
			}
		};

		std::string line;
		getline(fs, line);

		U value;
		size_t size = 0;

		fs >> size;
		o.resize(size);

		std::locale x(std::locale::classic(), new my_c_type);
		fs.imbue(x);

		size_t i = 0;
		while (fs >> value)
		{
			o[i] = value;
			i++;
			if (i == size) break;
		}
	};

	template<typename T>
	inline void Write(std::fstream& fs, const T& o)
	{
		fs << o << "\n";
	};

	template<>
	inline void Write(std::fstream& fs, const std::string& o)
	{
		fs << o << "\n";
	};

	template<typename T>
	inline void WriteVector(std::fstream& fs, const std::vector<T>& v)
	{
		fs << v.size() << " ";

		for (size_t i = 0; i < v.size(); i++)
		{

			fs << v[i];
			if (i != v.size() - 1)
				fs << " , ";
		}

		fs << "\n";
	};
}