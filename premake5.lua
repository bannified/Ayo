workspace "Ayo"
	architecture "x64"

	startproject "Sandbox"

	configurations 
	{
		"Debug", 
		"Release", -- stripped debug code, optimizations on, but with logging.
		"Dist" -- actual distribution build.
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" -- Debug-Windows-x64

-- Include directories relative to root folder (where solution is)
IncludeDir = {}
IncludeDir["glfw"] = "Ayo/vendor/glfw/include"
IncludeDir["glad"] = "Ayo/vendor/glad/include"
IncludeDir["imgui"] = "Ayo/vendor/ImGui"

include "Ayo/vendor/glfw" -- includes the premake5 file in glfw. kind of copy pasting it in here.
include "Ayo/vendor/glad"
include "Ayo/vendor/ImGui"

project "Ayo"
	location "Ayo" -- Relative path of project 
	kind "SharedLib" -- .dll file
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ayopch.h"
	pchsource "Ayo/src/ayopch.cpp"

	files
	{
		"%{prj.name}/src/**.h", -- every .h file
		"%{prj.name}/src/**.cpp" -- every .cpp file
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}"
	}

	links {
		"GLFW",
		"Glad",
		"opengl32.lib",
		"ImGui"
	}

	filter "system:windows" -- everything under this filter only apply to windows
		cppdialect "C++17"
		systemversion "latest"

		defines 
		{
			"AYO_PLATFORM_WINDOWS",
			"AYO_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug" -- just in Debug.
		defines 
		{
			"AYO_DEBUG",
			"AYO_ENABLE_ASSERTS"
		}
		symbols "On"
		runtime "Debug"
		staticruntime "off"

	filter "configurations:Release"
		defines "AYO_RELEASE"
		symbols "On"
		runtime "Release"
		staticruntime "off"

	filter "configurations:Dist"
		defines "AYO_DIST"
		symbols "On"
		runtime "Release"
		staticruntime "off"

	-- filter { "system:windows", "configurations:Release"} -- for multiple filters.

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h", -- every .h file
		"%{prj.name}/src/**.cpp" -- every .cpp file
	}

	includedirs
	{
		"Ayo/vendor/spdlog/include",
		"Ayo/src"
	}

	links 
	{
		"Ayo"	
	}

	filter "system:windows" -- everything under this filter only apply to windows
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		defines 
		{
			"AYO_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug" -- just in Debug.
		defines "AYO_DEBUG"
		symbols "On"
		runtime "Debug"
		staticruntime "off"

	filter "configurations:Release"
		defines "AYO_RELEASE"
		symbols "On"
		runtime "Release"
		staticruntime "off"

	filter "configurations:Dist"
		defines "AYO_DIST"
		symbols "On"
		runtime "Release"
		staticruntime "off"

