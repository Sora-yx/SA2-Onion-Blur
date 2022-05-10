#include "pch.h"


extern "C" {

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		Sleep(10);
		init_OnionBlur();
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}