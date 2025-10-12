workspace "HappySisyphus"
    architecture "x64"
    startproject "Sandbox"
    

    configurations { "Debug", "Release", "Dist" }

-- Output directory format
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Dependencies.lua"

include "Sisyphus/vendor/glfw-forked"
include "Sisyphus/vendor/Glad"
include "Sisyphus/vendor/imgui-forked"


-- 
-- Sisyphus Library Project (Shared Library)
-- 
project "Sisyphus"
    location "Sisyphus"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir    ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "hspch.h"
    pchsource "Sisyphus/src/hspch.cpp"

    files { "%{prj.name}/src/**.h",
     "%{prj.name}/src/**.hpp",
     "%{prj.name}/src/**.cpp",
     "%{prj.name}/vendor/stb_image/**.h", 
     "%{prj.name}/vendor/stb_image/**.cpp", 
     "%{prj.name}/vendor/glm/glm/**.hpp", 
     "%{prj.name}/vendor/glm/glm/**.inl" 
    }

    includedirs { "%{prj.name}/src",
    "%{prj.name}/vendor/spdlog/include",
    "%{IncludeDir.GLFW}",
    "%{IncludeDir.Glad}",
    "%{IncludeDir.ImGui}",
    "%{IncludeDir.glm}",
    "%{IncludeDir.VulkanSDK}",
    "%{IncludeDir.stb_image}",
    "%{IncludeDir.assimp}",
    "%{IncludeDir.assimp_build}",
    }

     libdirs {
    "%{LibraryDir.assimp_build}"
    }

    links {"GLFW", "Glad", "ImGui", "opengl32.lib"}

    filter "system:windows"
        systemversion "latest"
        
        defines {
            "SP_PLATFORM_WINDOWS",
            -- "SP_BUILD_DLL",
            -- "_WINDLL",
            "GLFW_INCLUDE_NONE"
        }

        -- postbuildcommands {
        --    ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox") 
        --}

        buildoptions { "/utf-8" }

    filter "configurations:Debug"
        defines { "DEBUG", "SP_DEBUG" }
        runtime "Debug"
        symbols "on"
        
        links
		{
			"%{Library.ShaderC_Debug}",
			"%{Library.SPIRV_Cross_Debug}",
			"%{Library.SPIRV_Cross_GLSL_Debug}",
            "%{Library.assimp_build_Debug}"

		}

    filter "configurations:Release"
        defines { "NDEBUG", "SP_RELEASE" }
        runtime "Release"
        optimize "on"
        
		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}",
            "%{Library.assimp_build_Release}"
		}

    filter "configurations:Dist"
        defines { "NDEBUG", "SP_DIST" }
        runtime "Release"
        optimize "on"
        
		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}",
            "%{Library.assimp_build_Release}"
		}


-- 
-- Sandbox Application Project
-- 
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir    ("bin-int/" .. outputdir .. "/%{prj.name}")

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.hpp", "%{prj.name}/src/**.cpp" }


    includedirs {
        "Sisyphus/vendor/spdlog/include",
        "Sisyphus/src",
        "Sisyphus/vendor",
        "%{IncludeDir.glm}",
        "%{IncludeDir.assimp}",
        "%{IncludeDir.assimp_build}",
    }

    links {
        "Sisyphus"  
    }

    filter "system:windows"
        systemversion "latest"
        defines {
            "SP_PLATFORM_WINDOWS"
            -- "_WINDLL"
        }
        buildoptions { "/utf-8" }

    filter "configurations:Debug"
        defines { "DEBUG", "SP_DEBUG" }
        symbols "on"
        runtime "Debug"

    filter "configurations:Release"
        defines { "NDEBUG", "SP_RELEASE" }
        optimize "on"
        runtime "Release"

    filter "configurations:Dist"
        defines { "NDEBUG", "SP_DIST" }
        optimize "on"
        runtime "Release"

    
    