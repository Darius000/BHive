project "Reflection"
    kind "StaticLib"
    language "C++"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "**.h",
        "**.cpp"
    }
    
    includedirs
    {
        "%{prj.name}/include"
    }
    
    filter "system:windows"
    systemversion "latest"
    staticruntime "on"
        
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
