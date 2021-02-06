#pragma once

#include "Property.h"

namespace Reflection
{ 
	DEFINE_PROPERTY(Char, char)
	DEFINE_PROPERTY(UInt8, uint8_t)
	DEFINE_PROPERTY(Int8, int8_t)
	DEFINE_PROPERTY(Bool, bool)
	DEFINE_PROPERTY(UInt, unsigned int)
	DEFINE_PROPERTY(Int, int)
	DEFINE_PROPERTY(UInt32, uint32_t)
	DEFINE_PROPERTY(Int32, int32_t)
	DEFINE_PROPERTY(UInt64, uint64_t)
	DEFINE_PROPERTY(Int64, int64_t)
	DEFINE_PROPERTY(Float, float)
	DEFINE_PROPERTY(Double, double)
	DEFINE_PROPERTY(String, std::string)
}