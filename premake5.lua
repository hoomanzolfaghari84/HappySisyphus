workspace "HappySisyphus"
    architecture "x64"
    startproject "Sandbox"

    configurations { "Debug", "Release", "Dist" }

-- Output directory format
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Sisyphus/vendor/GLFW/include"
IncludeDir["Glad"] = "Sisyphus/vendor/Glad/include"
IncludeDir["ImGui"] = "Sisyphus/vendor/imgui"


include "Sisyphus/vendor/GLFW"
include "Sisyphus/vendor/Glad"
include "Sisyphus/vendor/imgui"

-- 
-- Sisyphus Library Project (Shared Library)
-- 
project "Sisyphus"
    location "Sisyphus"
    kind "SharedLib"
    language "C++"
    


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir    ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "hspch.h"
    pchsource "Sisyphus/src/hspch.cpp"

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.hpp", "%{prj.name}/src/**.cpp" }

    includedirs { "%{prj.name}/src", "%{prj.name}/vendor/spdlog/include", "%{IncludeDir.GLFW}", "%{IncludeDir.Glad}", "%{IncludeDir.ImGui}"  }

    links {"GLFW", "Glad", "ImGui", "opengl32.lib"}

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++20"
        staticruntime "on"
        defines { "SP_PLATFORM_WINDOWS", "SP_BUILD_DLL", "_WINDLL", "GLFW_INCLUDE_NONE" }
        postbuildcommands { ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox") }
        buildoptions { "/utf-8" }

    filter "configurations:Debug"
        defines { "DEBUG", "SP_DEBUG" }
        -- runtime "Debug"
        symbols "On"
        buildoptions {"/MDd"}

    filter "configurations:Release"
        defines { "NDEBUG", "SP_RELEASE" }
        --runtime "Release"
        optimize "On"
        buildoptions {"/MD"}

    filter "configurations:Dist"
        defines { "NDEBUG", "SP_DIST" }
        --runtime "Release"
        optimize "On"
        buildoptions {"/MD"}

    -- filter { "system:windows", "configurations:Release" }
    --     buildoptions "/MT"

-- 
-- Sandbox Application Project
-- 
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir    ("bin-int/" .. outputdir .. "/%{prj.name}")

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.hpp", "%{prj.name}/src/**.cpp" }


    includedirs {
        "Sisyphus/vendor/spdlog/include",
        "Sisyphus/src"
    }

    links {
        "Sisyphus"  
    }

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++20"
        staticruntime "on"
        defines { "SP_PLATFORM_WINDOWS", "_WINDLL" }
        buildoptions { "/utf-8" }

    filter "configurations:Debug"
        defines { "DEBUG", "SP_DEBUG" }
        symbols "On"
        buildoptions {"/MDd"}

    filter "configurations:Release"
        defines { "NDEBUG", "SP_RELEASE" }
        optimize "On"
        buildoptions {"/MD"}

    filter "configurations:Dist"
        defines { "NDEBUG", "SP_DIST" }
        optimize "On"
        buildoptions {"/MD"}

    
    