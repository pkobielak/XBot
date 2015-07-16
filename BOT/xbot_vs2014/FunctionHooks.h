#include "stdafx.h"
#include "Strings.h"

// Hooks typedefs
typedef	VOID(WINAPI * protGetSystemInfo)(LPSYSTEM_INFO);
typedef INT(WINAPI * lolMessageBoxA)(HWND, LPCSTR, LPCSTR, UINT);
typedef INT(WINAPI * protCallNtPowerInformation)(POWER_INFORMATION_LEVEL, PVOID, ULONG, PVOID, ULONG);

class FunctionHooks
{	
public:
	FunctionHooks();
	~FunctionHooks();
	struct
	{
		HMODULE PowrProfdll = NULL;
		HMODULE Kernel32dll = NULL;
		HMODULE User32dll = NULL;
	}LibraryHandles;
	void LoadLibraries();// £aduje biblioteki
	void FreeLibraries();// Zwalnia zasoby bibliotek
	void LoadHooks();// Tworzy uchwyty
	
	// Hook list
	protGetSystemInfo GetSystemInfo;
	lolMessageBoxA MessageBoxA;
	protCallNtPowerInformation CallNtPowerInformation;
};


FunctionHooks::FunctionHooks()
{
	LoadLibraries();
	LoadHooks();
}

FunctionHooks::~FunctionHooks()
{
	FreeLibraries();
}

void FunctionHooks::LoadLibraries()
{
	// PowrProf.dll
	LibraryHandles.PowrProfdll = LoadLibraryA(STRINGS.PowrProfdll);
	// Kernel23.dll
	LibraryHandles.Kernel32dll = GetModuleHandleA(STRINGS.Kernel32dll);
	// User32.dll
	LibraryHandles.User32dll = GetModuleHandleA("User32.dll");
}

void FunctionHooks::FreeLibraries()
{
	// PowrProf.dll
	FreeLibrary(LibraryHandles.PowrProfdll);
}

void FunctionHooks::LoadHooks()
{
	GetSystemInfo = (protGetSystemInfo)GetProcAddress(LibraryHandles.Kernel32dll, STRINGS.GetSystemInfo);
	MessageBoxA = (lolMessageBoxA)GetProcAddress(LibraryHandles.User32dll, "MessageBoxA");
	CallNtPowerInformation = (protCallNtPowerInformation)GetProcAddress(LibraryHandles.PowrProfdll, STRINGS.CallNtPowerInformation);
}


