#include "stdafx.h"
#include "BypassKIT.h"

HHOOK hMouse;

BOOL Clicked = FALSE;

LRESULT CALLBACK MouseFunc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	if (pMouseStruct)
	{
		switch (wParam)
		{
		case WM_LBUTTONDOWN:
			Clicked = TRUE;
			break;
		case WM_RBUTTONDOWN:
			Clicked = TRUE;
			break;
		}
	}

	return CallNextHookEx(hMouse, nCode, wParam, lParam);
}

void __cdecl MouseThread(void* Args)
{ 
	hMouse = SetWindowsHookEx(WH_MOUSE_LL, MouseFunc, GetModuleHandle(NULL), NULL);
	MSG msg;
	while (GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (Clicked)break;
	}
	_endthread();
}

void BypassKIT::ActivateAntiEmulator()
{
	int counting_stars = 0;
	for (int i = 1; i < INT_MAX; i++)
	{
		for (int s = 1; s < INT_MAX; s++)
			if (i % 2 == 0)
				counting_stars++;
			else
				counting_stars--;
	}
	HANDLE hMouseThread = (HANDLE)_beginthread(MouseThread, NULL, NULL);
#ifdef DMODE
	printf("|-----Bypass AntiEmulator-----|\n");
	printf("Waiting for click...\n");
#endif
	while (Clicked != 1)
		Sleep(1000);
	PostThreadMessage(GetThreadId(hMouseThread), NULL, NULL, NULL);
#ifdef DMODE
	printf("Clicked!\nNow gonna wait 2 minutes!\n");
#endif
	Sleep(120000);
#ifdef DMODE
	printf("Starting default procedure...\n");
#endif
}