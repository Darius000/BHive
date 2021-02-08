#pragma once

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Library.h"
#include "ArchiveModes.h"

namespace Serialization
{
	//Class that performs all save and load operations
	//Call this after creating an object for loading an objects parameters
	class Archive
	{
	public:
		Archive(const std::string& filename, EArchiveModes modes = EArchiveModes::Binary)
			:m_FileName(filename), m_Modes(modes)
		{
			m_FileName.append(s_Extension);

			fs = new std::fstream();
		}
		~Archive()
		{
			delete fs;
		}

		template<class Object>
		void Serialize(const Object& o)
		{
			fs->open(m_FileName, static_cast<int>((EArchiveModes::Out | EArchiveModes::Trunc | m_Modes)));

			if(IsBinaryModeActive())  WriteBinary(*fs, s_FileVersion); else *fs << s_FileVersion << "\n";

			OnSerialize(*this, o, s_FileVersion);

			fs->close();
		}

		template<class Object>
		void DeSerialize(Object& o)
		{
			fs->open(m_FileName, static_cast<int>((EArchiveModes::In | m_Modes)));

			if (fs->good() == false) return;

			unsigned int fileversion = -1;

			if(IsBinaryModeActive()) ReadBinary(*fs, fileversion); else *fs >> fileversion;

			OnDeSerialize(*this, o, fileversion);

			fs->close();

		}

		const bool IsBinaryModeActive() const 
		{
			return (m_Modes & EArchiveModes::Binary) == EArchiveModes::Binary;
		}

		template<class T>
		void operator<<(const T* o);

		template<class T>
		void operator>>(T* o);

		template<class T>
		Archive& operator&(const T& var);

		template<class T>
		Archive& operator&(T& var);

		template<>
		Archive& operator&(std::string& var);

		template<>
		Archive& operator&(const std::string& var);

		template<class T>
		Archive& operator&(std::vector<T>& v);

		template<class T>
		Archive& operator&(const std::vector<T>& v);

	private:
		std::fstream* fs = nullptr;
		
		std::string m_FileName;

		EArchiveModes m_Modes;

		static unsigned int s_FileVersion;

		static const char* s_Extension;
	};


	template<class T>
	void Archive::operator<<(const T* o)
	{
		Serialize(*o);
	}

	template<class T>
	void Archive::operator>>(T* o)
	{
		DeSerialize(*o);
	}

	template<class T>
	Archive& Archive::operator&(const T& var)
	{
		IsBinaryModeActive() ? WriteBinary(*fs, var) : Write(*fs, var);

		return *this;
	}

	template<class T>
	Archive& Archive::operator&(T& var)
	{	
		IsBinaryModeActive() ? ReadBinary(*fs, var) : Read(*fs, var);

		return *this;
	}

	template<>
	Archive& Archive::operator&(std::string& var)
	{
		IsBinaryModeActive() ? ReadBinary(*fs, var) : Read(*fs, var);

		return *this;
	}

	template<>
	Archive& Archive::operator&(const std::string& var)
	{
		IsBinaryModeActive()? WriteBinary(*fs, var) : Write(*fs, var);
		
		return *this;
	}

	template<class T>
	Archive& Archive::operator&(const std::vector<T>& v)
	{
		IsBinaryModeActive() ? WriteBinaryVector<T>(*fs, v) : WriteVector<T>(*fs, v);
		
		return *this;
	}

	template<class T>
	Archive& Archive::operator&(std::vector<T>& v)
	{	
		IsBinaryModeActive() ?  ReadBinaryVector<T>(*fs, v) : ReadVector<T>(*fs, v);

		return *this;
	}

	template<typename T>
	auto OnSerialize(Archive& ar, const T& obj, unsigned int version)
		-> decltype(obj.Serialize(ar, version))
	{
		obj.Serialize(ar, version);
	};

	template<typename T>
	auto OnSerialize(Archive& ar, const T& obj, unsigned int version)
		->decltype(Serialize(ar, obj, version))
	{
		Serialize(ar, obj, version);
	};

	template<typename T>
	auto OnDeSerialize(Archive& ar, T& obj, unsigned int version)
		-> decltype(obj.DeSerialize(ar, version))
	{
		obj.DeSerialize(ar, version);
	};

	template<typename T>
	auto OnDeSerialize(Archive& ar, T& obj, unsigned int version)
		->decltype(DeSerialize(ar, obj, version))
	{
		DeSerialize(ar, obj, version);
	};

	template<class BaseClass, class T>
	inline void BaseObjectSerialize(Archive& ar, const T& obj, unsigned int version)
	{
		OnSerialize(ar, (BaseClass)obj, version);
	};

	template<class BaseClass, class T>
	inline void BaseObjectDeSerialize(Archive& ar, T& obj, unsigned int version)
	{
		OnDeSerialize(ar, (BaseClass&)obj, version);
	};

	template<class T>
	inline void SerializeObject(Archive& ar, const T* obj, unsigned int version)
	{
		const bool isnotnull = (obj == nullptr) ? false : true;

		ar& isnotnull;

		if (isnotnull)
			OnSerialize(ar, *obj, version);
	};

	template<class T>
	inline void DeSerializeObject(Archive& ar, T* obj, unsigned int version)
	{
		bool isnotnull = false;

		ar& isnotnull;

		if (isnotnull)
		{
			if(obj == nullptr)
				obj = new T();

			OnDeSerialize(ar, *obj, version);
		}
	};

#define SERIALIZEMEMEBER(archive, member) archive & member;
#define SERIALIZEBASECLASS(BaseClass, archive, obj, version) Serialization::BaseObjectSerialize<BaseClass>(archive, obj, version);
#define DESERIALIZEBASECLASS(BaseClass, archive, obj, version) Serialization::BaseObjectDeSerialize<BaseClass>(archive, obj, version);
#define SERIALIZEOBJECT(archive, obj, version) SerializeObject(archive, obj, version);
#define DESERIALIZEOBJECT(archive, obj, version) DeSerializeObject(archive, obj, version);
}