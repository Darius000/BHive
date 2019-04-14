workspace "BHive"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "BHive/vendor/glfw/include"
IncludeDir["Glad"] = "BHive/vendor/glad/include"
IncludeDir["ImGui"] = "BHive/vendor/imgui"
IncludeDir["ASSIMP"] = 

include "BHive/vendor/glfw"
include "BHive/vendor/glad"
include "BHive/vendor/imgui"

project "BHive"
    location "BHive"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

    pchheader "BHivePCH.h"
    pchsource "BHive/src/BHive/BHivePCH.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    
    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/src/BHIve",
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/vendor/glm/include",
        "%{prj.name}/Shaders",
        "%{prj.name}/vendor/assimp/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
    }
    
    libdirs {"%{prj.name}/vendor/assimp/lib"}

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "assimp-vc140-mt.lib",
        "opengl32.lib"
    }

    filter"system:windows"
        systemversion "latest"

        defines
        {
            "BH_PLATFORM_WINDOWS",
            "BH_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
            "_CRT_SECURE_NO_WARNING"
        }


        filter "configurations:Debug"
            defines "BH_DEBUG"
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            defines "BH_RELEASE"
            runtime "Release"
            optimize "on"

        filter "configurations:Dist"
            defines "BH_DIST"
            runtime "Release"
            optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

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
        "BHive/vendor/glm/include",
        "BHive/vendor/assimp/include",
        "BHive/vendor/glad/include",
        "BHive/vendor",
        "BHive/src"
    }
    
    links
    {
        "BHive"
    }

    filter"system:windows"
        systemversion "latest"

        defines
        {
            "BH_PLATFORM_WINDOWS",
        }
        
        prebuildcommands{ ("{COPY} %{prj.location}../BHive/vendor/assimp/dll/assimp-vc140-mt.dll %{cfg.targetdir}")}
        
        filter "configurations:Debug"
            defines "BH_DEBUG"
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            defines "BH_RELEASE"
            runtime "Release"
            optimize "on"

        filter "configurations:Dist"
            defines "BH_DIST"
            runtime "Release"
            optimize "on"