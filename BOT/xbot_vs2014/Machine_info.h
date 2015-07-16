// Przechowuje informacje o maszynie
#include "stdafx.h"
#include "Bot_version.h"
#include "SHA256.h"

class MachineInfo // Zawiera informacje o nosicielu
{
public:
	char PC_Name[MAX_COMPUTERNAME_LENGTH + 1]; // Nazwa komputera
	char Username[UNLEN + 1]; // Nazwa u¿ytkownika
	char CPU_clock[16]; // Procesor CPU
	char OS[16]; // Wersja systemu Windows
	char* Bot_version = VERSION; // Wersja bota

	std::string GetBotID(); // Zwraca ³añcuch zawieraj¹cy Bot_ID

	void make_info(); // Wype³nia strukturê MACHINE_INFO

	std::string create_long_payload(); // Zwraca ³añcuch sklejonych informacji o komputerze nosiciela

	std::string create_keepalive(); // Zwraca ³añcuch keep-alive

	MachineInfo();
	~MachineInfo();
};


// Processor info
#include <powrprof.h>
#pragma comment(lib, "Powrprof.lib")

typedef struct _PROCESSOR_POWER_INFORMATION {
	ULONG  Number;
	ULONG  MaxMhz;
	ULONG  CurrentMhz;
	ULONG  MhzLimit;
	ULONG  MaxIdleState;
	ULONG  CurrentIdleState;
} PROCESSOR_POWER_INFORMATION, *PPROCESSOR_POWER_INFORMATION;

// Windows version
#include <VersionHelpers.h>