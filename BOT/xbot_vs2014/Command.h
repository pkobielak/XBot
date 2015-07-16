#pragma once

// Lista mo¿liwych komend
#define UPDATE 1 // Aktualizuj
#define DOWNLOAD_AND_EXECUTE 2 // Pobierz i uruchom


class Command
{
private:
	unsigned char ToDo; //treœæ komendy (0 - 255)

public:
	Command(unsigned char); // Konstruktor, nie mo¿e istnieæ komenda bez treœci.
	
	void Make(); // Próba wykonania komendy
};