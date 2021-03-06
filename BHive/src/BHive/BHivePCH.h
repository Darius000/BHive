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
#include <cctype>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <array>
#include <future> //async for multi threading
#include <chrono>
#include <thread>

//----------SPDLOG---------
#include <spdlog/fmt/ostr.h>
#include <spdlog/fmt/bundled/ostream.h>

//---------------GLM--------------
#define  GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


//----------------------ImGui--------
#include "BHive/ImGui/ImGuiWrappers.h"

//-------------Core----------------
#include "BHive/Core/Core.h"
#include "BHive/Core/Log.h"
#include "BHive/Core/PlatformDataTypes.h"
#include "BHive/Core/DataTypes.h"
#include "BHive/Debug/Instrumentor.h"
#include "BHive/Core/CoreLibrary.h"
#include "BHive/Core/Math/MathLibrary.h"
#include "BHive/Core/Math/MatrixLibrary.h"
#include "BHive/Core/KeyCodes.h"
#include "BHive/Core/MouseCodes.h"
#include "BHive/Core/Event.h"
#include "BHive/Core/MouseEvent.h"
#include "BHive/Core/KeyEvent.h"
#include "BHive/Core/ApplicationEvent.h"
#include "BHive/Core/Input.h"
#include "BHive/Core/Time/Time.h"
#include "BHive/Core/Layer.h"
#include "BHive/Core/Application.h"
#include "BHive/Object/Entity.h"
#include "BHive/Object/Script.h"
#include "BHive/Core/Types/Array.h"

//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

#ifdef BH_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // !BH_PLATFORM_WINDOWS

#define DEGREE_ANGLES 1
