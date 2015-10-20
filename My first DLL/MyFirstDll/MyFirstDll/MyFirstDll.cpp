// MyFirstDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


extern "C" __declspec(dllexport) void show() {
	cout << "bka bka mda nu da tiipoo......" << endl;
}
extern "C" __declspec(dllexport) int fact(int n) {
	if (n == 1) return 1;
	return n * fact(n - 1);
}
extern "C" __declspec(dllexport) bool returnTrue() {
	return true;
}