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
IncludeDir["Refl"] = "BHive/vendor/reflection/include"
IncludeDir["ImGui"] = "BHive/vendor/imgui"
IncludeDir["GLM"] = "BHive/vendor/glm/include"
IncludeDir["STB_Image"] = "BHive/vendor/stb_image"
IncludeDir["entt"] = "BHive/vendor/entt/include"

group "Dependencies"
    include "BHive/vendor/glfw"
    include "BHive/vendor/glad"
    include "BHive/vendor/imgui"
group  ""

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
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.inl",
		"%{prj.name}/vendor/stb_image/**h",
		"%{prj.name}/vendor/stb_image/**cpp",
		"%{prj.name}/vendor/glm/**hpp",
		"%{prj.name}/vendor/glm/**inl",
        "%{prj.name}/vendor/reflection/**.h",
        "%{prj.name}/vendor/reflection/**.cpp",
        "%{prj.name}/vendor/reflection/**.hpp",
		"%{prj.name}/Assets/**",
		"premake5.lua"
    }
    
    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/src/BHive",
        "%{prj.name}/vendor/spdlog/include",
        --"%{prj.name}/vendor/glm/include",
        --"%{prj.name}/Shaders",
        --"%{prj.name}/vendor/assimp/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.Refl}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.STB_Image}",
        "%{IncludeDir.entt}"
    }
    
    --libdirs {"%{prj.name}/vendor/assimp/lib"}

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        --"assimp-vc140-mt.lib",
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
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/Assets/**"
    }

    includedirs
    {
        "BHive/vendor/spdlog/include",
		"BHive/vendor/imgui",
        "BHive/vendor/assimp/include",
        "BHive/vendor/glad/include",
        "BHive/vendor",
        "BHive/src",
		"BHive/src/BHive",
        "%{IncludeDir.entt}",
        "%{IncludeDir.GLM}"
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

project "BHive-Editor"
    location "BHive-Editor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/Assets/**"
    }

    includedirs
    {
        "BHive/vendor/spdlog/include",
		"BHive/vendor/imgui",
        "BHive/vendor/assimp/include",
        "BHive/vendor/glad/include",
        "BHive/vendor",
        "BHive/src",
		"BHive/src/BHive",
        "%{IncludeDir.entt}",
        "%{IncludeDir.GLM}"
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