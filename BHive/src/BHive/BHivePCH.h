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

//---------------GLM--------------
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//-------------Core----------------
#include "BHive/Core/Core.h"
#include "BHive/Core/DataTypes.h"
#include "BHive/Math/MathLibrary.h"
#include "BHive/Core/KeyCodes.h"
#include "BHive/Core/MouseCodes.h"
#include "BHive/Core/Event.h"
#include "BHive/Core/MouseEvent.h"
#include "BHive/Core/KeyEvent.h"
#include "BHive/Core/ApplicationEvent.h"
#include "BHive/Core/Input.h"
#include "BHive/Core/Log.h"
#include "BHive/Core/Time.h"
#include "BHive/Core/Layer.h"
#include "BHive/Core/Application.h"



//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

#ifdef BH_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // !BH_PLATFORM_WINDOWS



