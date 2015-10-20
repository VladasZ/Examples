// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

extern "C" __declspec(dllexport) void show();
extern "C" __declspec(dllexport) int fact(int n);
extern "C" __declspec(dllexport) bool returnTrue();


// TODO: reference additional headers your program requires here
#include <iostream>

using namespace std;