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

// Asserts
#ifdef AYO_ENABLE_ASSERTS
	#define AYO_ASSERT(x, ...) { if ((!x)) { AYO_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } } //TODO: Change to a better assert.
	#define AYO_CORE_ASSERT(x, ...) { if ((!x)) { AYO_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else 
	#define AYO_ASSERT(x, ...)
	#define AYO_CORE_ASSERT(x, ...)
#endif

// General macros
#define SINGLE_BIT(x) 1 << x