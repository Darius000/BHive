#pragma once

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Archive.h"

namespace Serialization
{ 
	//Abstract class for serialization objects
	class ISerializable
	{
	public:
		ISerializable();

		virtual std::string& GetName() = 0;
		virtual void Serialize(Archive& ar, unsigned int version) const = 0;
		virtual void DeSerialize(Archive& ar, unsigned int version) = 0;
	};
}