workspace "BHive"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "BHive"
	location "BHive"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

	pchheader "BHivePCH.h"
	pchsource "BHive/src/BHive/BHivePCH.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter"system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.17134.0"

		defines
		{
			"BH_PLATFORM_WINDOWS",
			"BH_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		filter "configurations:Debug"
			defines "BH_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "BH_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "BH_DIST"
			optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"BHive/vendor/spdlog/include",
		"BHive/src"
	}

	links
	{
		"BHive"
	}

	filter"system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.17134.0"

		defines
		{
			"BH_PLATFORM_WINDOWS",
		}

		filter "configurations:Debug"
			defines "BH_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "BH_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "BH_DIST"
			optimize "On"

		