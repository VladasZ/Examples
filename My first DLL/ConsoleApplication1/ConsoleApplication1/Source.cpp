#include <windows.h>
#include <iostream>


using namespace std;



typedef void(*cfunc)();
typedef bool(*_cfunc)();
typedef int(*_fact)(int);


cfunc show;
cfunc Test2;
_cfunc returnTrue;
_fact fact;


int main()
{
	HINSTANCE hLib = LoadLibrary(L"MyFirstDll.dll");
	if (hLib == NULL)
	{
		printf("Unable to load library!");
		return -1;
	}
	show = (cfunc)GetProcAddress((HMODULE)hLib, "show");

	if (returnTrue = (_cfunc)GetProcAddress((HMODULE)hLib, "returnTrue")) {
		cout << "izi!" << endl;
	}
	if (!GetProcAddress((HMODULE)hLib, "returnTrue")) {
		cout << "mda....." << endl;
	}
	else cout << "toje izi!" << endl;

	fact = (_fact)GetProcAddress((HMODULE)hLib, "fact");

	show();
	cout << returnTrue() << endl;

	cout << fact(10) << endl;

	//Test2();
	FreeModule(hLib);
	return 0;
}