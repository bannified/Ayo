#pragma once

// only applies for Windows (declspec is a Windows only thing)
#ifdef AYO_PLATFORM_WINDOWS // means we're trying to build this dll (not defined for other projects)
	#ifdef AYO_BUILD_DLL
		#define AYO_API __declspec(dllexport)
	#else // if in anywhere else other than Ayo...
		#define AYO_API __declspec(dllimport)
	#endif
#else
#error Ayo only supports windows!
#endif

// General macros
#define SINGLE_BIT(x) 1 << x