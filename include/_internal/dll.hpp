#pragma once

#include <Geode/platform/cplatform.h>


#ifdef GEODE_IS_WINDOWS
	#ifdef AMBER_EXPORTING
		#define AMBER_DLL __declspec(dllexport)
	#else
		#define AMBER_DLL __declspec(dllimport)
	#endif
#else
	#ifdef AMBER_EXPORTING
		#define AMBER_DLL __attribute__((visibility("default")))
	#else
		#define AMBER_DLL
	#endif
#endif