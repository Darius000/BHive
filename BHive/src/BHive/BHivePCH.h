#pragma once


#include <iostream>
#include <utility>
#include <algorithm>
#include <memory>
#include <functional>

#include <string>
#include <sstream>
#include <fstream>
#include <ostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <array>

#include "BHive/Log.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#ifdef BH_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // !BH_PLATFORM_WINDOWS

#include "BHive/Events/EventMacros.h"

#include"BHive/Math/MathLibrary.h"
#include "PlatformTypes.h"
#include "DataTypes.h"

//#include "BHive/DataTypes/Color.h" 0 - 255 unsigned char- max is 255
//#include "BHive/DataTypes/LinearColor.h" 0 - 1



typedef std::string String;
typedef std::ofstream ofStream;
typedef std::ifstream ifStream;
typedef std::istream iStream;

//Convert a number to string
template<typename T>
std::string NumToString(T x)
{
	return std::to_string(x);
}

