#pragma once
#include "BHive.h"

namespace BHive
{ 
	#define CLASSTOSTRING(x) #x

	template<class T>
	struct Factory
	{		
		static const std::string GetName() { return ""; }
	};

	//Register Factory
	template<>
	struct Factory<TagComponent>{
		static const std::string GetName() { return "Tag Component"; }
	};

	template<>
	struct Factory<TransformComponent>{
		static const std::string GetName() { return "Transform Component"; }
	};

	template<>
	struct Factory<DirectionalLightComponent>{
		static const std::string GetName() { return "Directional Light Component"; }
	};

	template<>
	struct Factory<PointLightComponent>{
		static const std::string GetName() { return "Point Light Component"; }
	};

	template<>
	struct Factory<CameraComponent>{
		static const std::string GetName() { return "Camera Component"; }
	};

	template<>
	struct Factory<RenderComponent>{
		static const std::string GetName() { return "Render Component"; }
	};

	template<>
	struct Factory<NativeScriptComponent>{
		static const std::string GetName() { return "Native Script Component"; }
	};
}
