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
IncludeDir["GLM"] = "BHive/vendor/glm/include"
IncludeDir["STB_Image"] = "BHive/vendor/stb_image"
IncludeDir["entt"] = "BHive/vendor/entt/include"
IncludeDir["Assimp"] = "BHive/vendor/Assimp/include"
IncludeDir["RTTR"] = "BHive/vendor/rttr/include"
IncludeDir["FreeType"] = "BHive/vendor/FreeType/include"
IncludeDir["ImGuizmo"] = "BHive/vendor/ImGuizmo"
IncludeDir["Reflection"] = "BHive/vendor/Reflection/include"
IncludeDir["Serialization"] = "BHive/vendor/Serialization/include"

group "Dependencies"
    include "BHive/vendor/glfw"
    include "BHive/vendor/glad"
    include "BHive/vendor/imgui"
    include "BHive/vendor/Reflection"
    include "BHive/vendor/Serialization"
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
        "%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
        "%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp"
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
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.Refl}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.STB_Image}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.Assimp}",
        "%{IncludeDir.RTTR}",
        "%{IncludeDir.FreeType}",
        "%{IncludeDir.ImGuizmo}",
        "%{IncludeDir.Reflection}",
        "%{IncludeDir.Serialization}"
    }

    libdirs {"%{prj.name}/vendor/assimp/lib", 
        "%{prj.name}/vendor/rttr/lib",
        "%{prj.name}/vendor/FreeType/lib"}

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "Reflection",
        "Serialization",
        "rttr_core_lib_s_d.lib",
        "assimp.lib",
        "zlibstaticd.lib",
        "IrrXMLd.lib",
        "opengl32.lib",
        "freetype.lib"
    }
    
    filter "files:BHive/vendor/ImGuizmo/**.cpp"
        flags {"NoPCH"}
 
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
        "BHive/vendor/glad/include",
        "BHive/vendor",
        "BHive/src",
		"BHive/src/BHive",
        "%{IncludeDir.entt}",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.Assimp}",
        "%{IncludeDir.RTTR}"
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
        "BHive/vendor/glad/include",
        "BHive/vendor",
        "BHive/src",
        "%{prj.name}/src",
        "%{prj.name}/src/Core",
		"BHive/src/BHive",
        "%{IncludeDir.entt}",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.Assimp}",
        "%{IncludeDir.RTTR}",
        "%{IncludeDir.Reflection}"
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