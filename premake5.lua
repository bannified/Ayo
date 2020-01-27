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
IncludeDir["glm"] = "Ayo/vendor/glm"
IncludeDir["stb"] = "Ayo/vendor/stb"
IncludeDir["assimp"] = "Ayo/vendor/assimp/include"
IncludeDir["boost"] = "Ayo/vendor/boost/boost"

include "Ayo/vendor/glfw" -- includes the premake5 file in glfw. kind of copy pasting it in here.
include "Ayo/vendor/glad"
include "Ayo/vendor/ImGui"

project "Ayo"
	location "Ayo" -- Relative path of project 
	kind "StaticLib" -- SharedLib for .dll file, StaticLib for .lib
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ayopch.h"
	pchsource "Ayo/src/ayopch.cpp"

	files
	{
		"%{prj.name}/src/**.h", -- every .h file
		"%{prj.name}/src/**.cpp", -- every .cpp file
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
        "%{IncludeDir.stb}",
        "%{IncludeDir.assimp}",
        "%{IncludeDir.boost}"
	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
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
			"GLFW_INCLUDE_NONE",
			
			-- For dynamic linking...
			--"AYO_BUILD_DLL",
			--"AYO_DYNAMIC_LINK"
		}

		--[[ for using Ayo as a .dll
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}
		--]]

	filter "configurations:Debug" -- just in Debug.
		defines 
		{
			"AYO_DEBUG",
			"AYO_ENABLE_ASSERTS"
		}
		symbols "on"
		runtime "Debug"

	filter "configurations:Release"
		defines "AYO_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "AYO_DIST"
		runtime "Release"
		optimize "on"

	-- filter { "system:windows", "configurations:Release"} -- for multiple filters.

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Ayo/src",
		"Ayo/vendor",
		"%{IncludeDir.glm}"
	}

	links 
	{
		"Ayo"	
	}

	filter "system:windows" -- everything under this filter only apply to windows
		systemversion "latest"

		defines 
		{
			"AYO_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug" -- just in Debug.
		defines "AYO_DEBUG"
		symbols "on"
		runtime "Debug"

	filter "configurations:Release"
		defines "AYO_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "AYO_DIST"
		runtime "Release"
		optimize "on"
