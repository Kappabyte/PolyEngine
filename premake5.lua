workspace "Poly Engine"
    language "C++"
    architecture "x86_64"

    startproject "Polygon"

    configurations { "Debug", "Release" }

    filter { "configurations:Debug" }
        symbols "On"
        
    filter { "configurations:Release" }
        optimize "On"
    
        
	
	filter "system:windows"
        defines { "POLY_PLATFORM_WINDOWS" }

    filter "system:linux"
        defines { "POLY_PLATFORM_LINUX" }

    filter {}

    targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
	objdir ("Build/Obj/%{prj.name}/%{cfg.longname}")


include "./Libraries/libraries.lua"
include "./Projects/projects.lua"
