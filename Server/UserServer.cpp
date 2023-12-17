#include "Message.h"
#include "Database.h"
#include <mutex>
#include <stdio.h>
std::mutex RegsiterMutex;
void MyResponseGetUin(ClientNode* Client, UINT Uin)
{
	BYTE buf[255];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0);
	Write32(p, Uin);

	len = p - buf;
	SendToClient(Client, 1, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Response);
}

void MyRequestGetUin(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	size_t len;

	len = Read8(Body);
	char* UserName = new char[len + 1];
	memcpy(UserName, Body, len);
	Body += len;
	UserName[len] = 0;

	//printf("UserName:%s\n", UserName);
	fflush(stdout);
	DWORD Uin = UserDB_GetUin(UserName);

	delete[] UserName;
	
	MyResponseGetUin(Client, Uin);
	
}

void MyResponseRegister(ClientNode* Client, USHORT Result)
{
	BYTE buf[2];
	BYTE* p = buf;
	size_t len;

	Write16(p, Result);

	len = p - buf;
	SendToClient(Client, 2, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Response);
}


void MyRequestRegister(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	size_t len;

	len = Read8(Body);
	char* UserName = new char[len + 1];
	memcpy(UserName, Body, len);
	Body += len;
	UserName[len] = 0;

	len = Read8(Body);
	char* Password = new char[len + 1];
	memcpy(Password, Body, len);
	Body += len;
	Password[len] = 0;

	printf("UserName:%s, Password:%s\n", UserName, Password);
	fflush(stdout);
	//×¢²á¼ÓËø
	std::lock_guard<std::mutex> lg(RegsiterMutex);
	USHORT Result = UserDB_Register(UserName, Password) ? 0 : 1;

	delete[] UserName;
	delete[] Password;
	MyResponseRegister(Client, Result);
}
