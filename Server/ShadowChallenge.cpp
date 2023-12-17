#include "Message.h"

#include <stdio.h>


void RequestStartShadowChallenge(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);
	UINT MapID = Read32(Body);

	Client->RoomID = 0;
	Client->GameID = 0;

	ResponseStartShadowChallenge(Client);
	NotifyKartPhysParam(Client, NULL);
	//NotifyOtherKartStoneInfo(Client);
}
void ResponseStartShadowChallenge(ClientNode* Client)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write32(p, 0); //ResultID

	len = p - buf;
	SendToClient(Client, 1500, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestEndShadowChallenge(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	{
		UINT Uin = Read32(Body);
		UINT Time = Read32(Body);
	}

	int Time = Read32(Body);

	ResponseEndShadowChallenge(Client, Time != 0 ? 0 : 3);
}
void ResponseEndShadowChallenge(ClientNode* Client, int ResultID)
{
	
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write32(p, ResultID); //ResultID
	Write32(p, 0); //MoneyInc
	Write32(p, 0); //ExpInc
	Write32(p, 30); //MoneyTotal
	Write32(p, 1); //ExpTotal

	Write16(p, 0); //ItemNum

	//MAXAWORDSIZE:64
	for (size_t i = 0; i < 64; i++)
	{
		Write32(p, 0); //ItemID
	}


	len = p - buf;
	SendToClient(Client, 1501, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}


void RequestReplayOperate(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	//影子挑战必须回复这个
	BYTE* p = Body; WORD len;

	UINT Uin = Read32(p);
	UCHAR Cmd = Read8(p);
	int Para0 = Read32(p);

	{ //ReqReplayInfo
		BYTE* pReqReplayInfo = p;
		len = Read16(pReqReplayInfo);
		/*
		USHORT UuidLen = Read16(pReqReplayInfo);
		USHORT GIdxLen = Read16(pReqReplayInfo);
		UCHAR FileMd5Len = Read8(pReqReplayInfo);
		char NickName[] = ReadString(pReqReplayInfo);
		int BaseMode = Read32(pReqReplayInfo);
		int SubMode = Read32(pReqReplayInfo);
		int Channel = Read32(pReqReplayInfo);
		int MapID = Read32(pReqReplayInfo);
		UINT FinTime = Read32(pReqReplayInfo);
		UINT CTime = Read32(pReqReplayInfo);
		UCHAR Other = Read8(pReqReplayInfo);
		UCHAR KeyBufferLen = Read8(pReqReplayInfo);
		UCHAR KeyHashLen = Read8(pReqReplayInfo);
		USHORT ReplayVersion = Read16(pReqReplayInfo);
		*/
		p += len;
	}
	int Para1 = Read32(p);
	
	//printf("Cmd:%d, Para0:%d, Para1:%d\n", Cmd, Para0, Para1);

	ResponseReplayOperate(Client, Cmd);
}
void ResponseReplayOperate(ClientNode* Client, UCHAR Cmd)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	Write16(p, 0); //ResultID
	Write8(p, Cmd); //Cmd
	Write32(p, 99); //Para0
	Write32(p, 0); //ReplayNum
	/*
	for (size_t i = 0; i < n; i++)
	{ //ReplayInfo
		BYTE* pReplayInfo = p;
		Write16(pReplayInfo, 0); //len

		Write16(pReplayInfo, 0); //UuidLen
		Write16(pReplayInfo, 0); //GIdxLen
		Write8(pReplayInfo, 0); //FileMd5Len
		WriteString(pReplayInfo, 0); //NickName[]
		Write32(pReplayInfo, 0); //BaseMode
		Write32(pReplayInfo, 0); //SubMode
		Write32(pReplayInfo, 0); //Channel
		Write32(pReplayInfo, 0); //MapID
		Write32(pReplayInfo, 0); //FinTime
		Write32(pReplayInfo, 0); //CTime
		Write8(pReplayInfo, 0); //Other
		Write8(pReplayInfo, 0); //KeyBufferLen
		Write8(pReplayInfo, 0); //KeyHashLen
		Write16(pReplayInfo, 0); //ReplayVersion

		len = pReplayInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	Write8(p, 0); //UrlTmplLen

	len = p - buf;
	SendToClient(Client, 28421, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

