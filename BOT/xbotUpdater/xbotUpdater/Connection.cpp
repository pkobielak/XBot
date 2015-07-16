#include "Connection.h"


bool NewConnection::run_winsock() // Zwraca TRUE je�li si� powiod�o
{
	WSADATA wsdata;

	return (WSAStartup(MAKEWORD(2, 0), &wsdata) == NULL);
}

SOCKET NewConnection::create_socket()
{
	sockaddr_in sock;

	//hostent* HostInfo = gethostbyname("growproject.vxm.pl"); //Zbierz informacje o ho�cie
	//
	//if (HostInfo == NULL) { return 0; } //Zwr�� invalid_socket je�li nie uda�o si� zebra� info o ho�cie
	//
	//memcpy(&(sock.sin_addr), HostInfo->h_addr, HostInfo->h_length); //skopiuj IP ze struktury hostent do sock.sin_add
	//
	sock.sin_addr.s_addr = inet_addr("127.0.0.1");

	sock.sin_family = AF_INET; // Rodzina protoko��w "AF_INET = np TCP/IP"
	sock.sin_port = htons(80); // Port docelowy po��czenia

	memset(&(sock.sin_zero), '/0', 8); // wyzeruj reszt� struktury

	int sockfd = socket(PF_INET, SOCK_STREAM, 0); // Utworzenie deskryptora gniazda
	int res = connect(sockfd, (struct sockaddr*)&sock, sizeof(struct sockaddr_in)); // Inicjacja po��czenia
	if (res < 0)
		return 0;
	else
	{
		_socket = sockfd;
		return sockfd;
	}
}

bool NewConnection::send_data(std::string http_query)
{
	for (int i = 0; i < http_query.size(); i++)
		if (http_query[i] == ' ')http_query.replace(i, 1, "%20");

	std::string get = "GET ";
	std::string typeof_packet = " HTTP/1.1\r\nHost: growproject.vxm.pl\r\nContent-type: application/x-www-form-urlencoded\r\n\r\n";

	get += http_query;
	get += typeof_packet;

	const char* payload = get.c_str();

	//printf("\n\nSformulowane zapytanie:\n%s\n\n\n", payload);

	return (send(_socket, payload, strlen(payload), NULL) >= (int)strlen(payload));
}

void NewConnection::close_socket()
{
	closesocket(_socket);
}

NewConnection::~NewConnection()
{
	close_socket();
	WSACleanup();
}

using namespace std;

#define	BUFFERSIZE 4096

bool NewConnection::DownloadNewClient()// Zapisuje plik nowego klienta pod nazw� "new.exe"
{
	char buffer[BUFFERSIZE];

	NewConnection Connection;

	Connection.run_winsock();
	while (!Connection.create_socket())
		Sleep(30000);
	Connection.send_data("/file.exe");

	int nRecv, npos;
	nRecv = recv(Connection._socket, (char*)&buffer, BUFFERSIZE, 0);

	// getting end of header //
	string str_buff = buffer;
	npos = str_buff.find("\r\n\r\n");

	// open the file in the beginning //
	HANDLE hFile;
	hFile = CreateFileA("new.exe", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

	// Download file //
	DWORD ss;
	while ((nRecv > 0) && (nRecv != INVALID_SOCKET)){
		if (npos > 0){
			char bf[BUFFERSIZE];
			// copy from end position of header //
			memcpy(bf, buffer + (npos + 4), nRecv - (npos + 4));
			WriteFile(hFile, bf, nRecv - (npos + 4), &ss, NULL);
		}
		else{
			// write normally if end not found //
			WriteFile(hFile, buffer, nRecv, &ss, NULL);
		}

		// buffer cleanup  //
		ZeroMemory(&buffer, sizeof(buffer));
		nRecv = recv(Connection._socket, (char*)&buffer, BUFFERSIZE, 0);
		str_buff = buffer;
		npos = str_buff.find("\r\n\r\n");
	}

	// Close connection and handle //
	CloseHandle(hFile);
	Connection.close_socket();
	WSACleanup();

	return TRUE;
}