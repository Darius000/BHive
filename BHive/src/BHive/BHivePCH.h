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

using String = std::string;
