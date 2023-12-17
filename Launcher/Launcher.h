#pragma once
#include "framework.h"
#include "Resource.h"

#ifndef ZingSpeed
#ifndef _WIN64
#define QQSpeed_x64
#endif
#endif

#pragma pack(push,1)
struct SharedData
{
	HWND hWnd;
#ifdef QQSpeed_x64
	int hWnd_;
#endif
	DWORD Uin;
	char PwdMD5[16];
	char Unknown1[24];
	DWORD WorldID;
	char UserDir[MAX_PATH];
	DWORD CommodityListCRC;
	char CommodityListURL[128];
	char Key[16];
	int SignKeyLen;
	char SignKey[128];
	int ClientKeyLen;
	char ClientKey[128];
	char QQNickNameLength;
	char QQNickName[37];
	char Unknown2[1817];
};

struct NotifyLoginResult
{
	HWND	hWnd;
#ifdef QQSpeed_x64
	int hWnd_;
#endif
	DWORD	Entity;
	INT		LoginResult;
	CHAR	ErrorMessage[100];
};
#pragma pack(pop)


enum ServerEntity
{
	eQQServer = 0,
	eDirServer = 1,
	eGameServer = 2,
	eShopServer = 3,
};

enum LoginResult
{
	eLoginSuccessed = 0,
	eLoginFailed = 1,
	eLoginTimeout = 2,
	eLoginRequireReg = 3,
	eLoginCanceled = 4,
	eLoginIdentityLimit = 5,
	eLoginVersionLimit = 6,
	eLoginVersionRecommend = 7,
	eLoginFileCracked = 8,
};



BOOL LoginDialog(HWND hWnd);