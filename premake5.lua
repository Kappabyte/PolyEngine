workspace "Poly Engine"
    language "C++"
    architecture "x86_64"

    configurations { "Dubug", "Release" }

    filter { "configurations:Debug" }
        symbols "On"
        
    filter { "configurations:Release" }
        optimize "On"

    filter {}

    targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
	objdir ("Build/Obj/%{prj.name}/%{cfg.longname}")


include "./Libraries/libraries.lua"
include "./Projects/projects.lua"
