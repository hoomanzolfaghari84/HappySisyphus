workspace "HappySisyphus"
    architecture "x64"
    startproject "Sisyphus"

    configurations { "Debug", "Release", "Dist" }

-- Output directory format
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- CoreLib project (Shared Library)
project "Sisyphus"
    location "Sisyphus"
    kind "SharedLib"
    language "C++"
    


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir    ("bin-int/" .. outputdir .. "/%{prj.name}")

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.hpp", "%{prj.name}/src/**.cpp" }

    includedirs { "%{prj.name}/vendor/spdlog/include" }

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "on"
        defines { "SP_PLATFORM_WINDOWS", "SP_BUILD_DLL", "_WINDLL" }
        postbuildcommands { ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox") }

    filter "configurations:Debug"
        defines { "DEBUG", "SP_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG", "SP_RELEASE" }
        optimize "On"

    filter "configurations:Dist"
        defines { "NDEBUG", "SP_Dist" }
        optimize "On"

    -- filter { "system:windows", "configurations:Release" }
    --     buildoptions "/MT"

-- App project (Console Application)
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir    ("bin-int/" .. outputdir .. "/%{prj.name}")

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.hpp", "%{prj.name}/src/**.cpp" }


    includedirs {
        "%{prj.name}/vendor/spdlog/include",
        "Sisyphus/src"
    }

    links {
        "Sisyphus"  
    }

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++23"
        staticruntime "on"
        defines { "SP_PLATFORM_WINDOWS", "_WINDLL" }

    filter "configurations:Debug"
        defines { "DEBUG", "SP_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG", "SP_RELEASE" }
        optimize "On"

    filter "configurations:Dist"
        defines { "NDEBUG", "SP_Dist" }
        optimize "On"

    
    