#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include"Message.h"
void InitDB();
void CloseDB();
void InitTaskInfo();
BOOL UserDB_Register(const char* Username, const char* Password);
DWORD UserDB_GetUin(const char* Username);
BOOL UserDB_CmpPassword(DWORD Uin, const char* Password);

int PlayerDB_AddItem(ClientNode* Client,DWORD Uin, DWORD ItemID, DWORD ItemNum, int AvailPeriod, bool Status);
DWORD PlayerDB_GetMapRecord(DWORD Uin, int MapID);
bool PlayerDB_SetMapRecord(DWORD Uin, int MapID, DWORD Record);
