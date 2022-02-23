project "Glad"
    location "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "On"

    files
    {
        "Glad/include/glad/glad.h",
        "Glad/include/KHR/khrplatform.h",
        "Glad/src/glad.c"
    }

    includedirs
    {
        "Glad/include"
    }
    
    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"