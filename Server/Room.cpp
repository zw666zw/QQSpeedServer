#include "Room.h"
#include "Map.h"
#include<unordered_map>
#include <stdio.h>
#include <time.h>
#include <map>
#include <mutex>
#include "sqlite/sqlite3.h"
BYTE BorderOnePlayerInfo[1305];
extern std::map<long, RoomNode*> Rooms;
UINT GlobalBorderRoomID = 0;
HANDLE TimerQueue = CreateTimerQueue();
BYTE chewangkaoyan[100] = { 0 };
BYTE shumiaoyunshu[100] = { 0 };
BYTE baofengtiaozhan[2048] = { 0 };
int baofengmap[5] = { 137,118,120,108,135 };
void WINAPI OnDanceTimer(RoomNode* Room);
extern UINT GetRandMap(short MapID);
std::recursive_mutex Mutex;
extern std::recursive_mutex ClientMutex;
long SeqRoomID = 0;
//extern DWORD WINAPI OnSingleOver(PVOID Client);
void NotifyChangeReadyState(ClientNode* Client, UINT Uin, bool State);
void NotifyChangeSeatState(ClientNode* Client, char SeatID, char SeatState);
extern void WINAPI OnBegin(RoomNode* Room);
void NotifyClientUpdatePlayerID(ClientNode* Client);
extern UINT SyncTime;
extern sqlite3* PlayerDB;
extern std::map<long, ClientNode*> Clients;
extern void NotifyGameNPCInfo(ClientNode* Client);
extern UINT DanceTime;

extern void RequestEnter3DRoom(ClientNode* Client);
void NotifyChangeRoomOwner(ClientNode* Client, RoomNode* Room);
void NotifyBugletTalk(ClientNode* Client,char* Content,short clength,char BugletType)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	

	Write8(p, 1); //BugletNum
	for (size_t i = 0; i < 1; i++)
	{ //BugletInfo
		BYTE* pBugletInfo = p;
		Write16(pBugletInfo, 0); //len

		Write32(pBugletInfo, Client->Uin); //SrcUin
		memset(pBugletInfo, 0, 17);
		
		memcpy(pBugletInfo, Client->NickName, 17);
		
		pBugletInfo += 17;
		//WriteString(pBugletInfo, 0); //SrcNickName[]
		
		memset(pBugletInfo, 0, 17);//SrcGuildName[]
		pBugletInfo += 17;
		Write8(pBugletInfo, 0); //Gender
		Write16(pBugletInfo, clength); //ContentLength
		memcpy(pBugletInfo, Content, clength);
		pBugletInfo += clength;
	
		//memcpy(pBugletInfo, (BYTE*)"\x0c\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0f\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0c\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x12\x00\x00\x00\x0a\x00\x00\x27\x24\x00\x00\x00\x01\xff\xff\xff\xff\x00\x00", 74);
		//pBugletInfo += 74;

		Write8(pBugletInfo, BugletType); //BugletType
		Write32(pBugletInfo, 0); //Identify
		Write16(pBugletInfo, 0x106); //VipFlag
		memset(pBugletInfo, 0, 18); //Contentid[]
		pBugletInfo += 18;
		{ //NobleInfo
			BYTE* pNobleInfo = pBugletInfo;
			Write16(pNobleInfo, 0); //len

			Write32(pNobleInfo, 0); //NobleID
			Write8(pNobleInfo, 6); //NobleLevel
			Write32(pNobleInfo, 0); //NoblePoint
			Write32(pNobleInfo, 0); //NobleLeftDays

			len = pNobleInfo - pBugletInfo;
			Set16(pBugletInfo, (WORD)len);
			pBugletInfo += len;
		}
		{ //GuildVipBaseInfo
			BYTE* pGuildVipBaseInfo = pBugletInfo;
			Write16(pGuildVipBaseInfo, 0); //len

			Write8(pGuildVipBaseInfo, 6); //GuildVipLevel
			Write32(pGuildVipBaseInfo, 0); //GuildVipPoint

			len = pGuildVipBaseInfo - pBugletInfo;
			Set16(pBugletInfo, (WORD)len);
			pBugletInfo += len;
		}
		Write8(pBugletInfo, 1); //HasLoverVip
		for (size_t i = 0; i < 1; i++)
		{ //LoverVipInfo
			BYTE* pLoverVipInfo = pBugletInfo;
			Write16(pLoverVipInfo, 0); //len

			Write8(pLoverVipInfo, 6); //LoverVipLevel
			Write32(pLoverVipInfo, 0); //LoverVipPoint
			Write8(pLoverVipInfo, 0); //GrowRate

			len = pLoverVipInfo - pBugletInfo;
			Set16(pBugletInfo, (WORD)len);
			pBugletInfo += len;
		}
		Write8(pBugletInfo, 6); //GardenLevel
		Write32(pBugletInfo, 6); //ConsumeVipLevel
		{ //EmperorInfo
			BYTE* pEmperorInfo = pBugletInfo;
			Write16(pEmperorInfo, 0); //len

			Write8(pEmperorInfo, 6); //EmperorLevel
			Write32(pEmperorInfo, 0); //EmperorPoint
			Write32(pEmperorInfo, 0); //EmperorLeftDays
			Write8(pEmperorInfo, 0); //EmperorGrowRate

			len = pEmperorInfo - pBugletInfo;
			Set16(pBugletInfo, (WORD)len);
			pBugletInfo += len;
		}
		Write8(pBugletInfo, 0); //HasCarLottoryRecord
		
		len = pBugletInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	len = p - buf;
	std::lock_guard<std::recursive_mutex> lg(ClientMutex);
	std::map<long, ClientNode*>::iterator iter = Clients.begin();
	while (iter != Clients.end())
	{
		ClientNode* DstClient = iter->second;
		if (DstClient)
		{
			SendToClient(DstClient, 555, buf, len, DstClient->ConnID, FE_PLAYER, DstClient->ConnID, Notify);
		}
		iter++;
	}
}
void NotifyClientUpdatePlayerID(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 1); //PlayerNum
	for (size_t i = 0; i < 1; i++)
	{ //PlayerIDInfo
		BYTE* pPlayerIDInfo = p;
		Write16(pPlayerIDInfo, 0); //len

		Write32(pPlayerIDInfo, Client->Uin); //Uin
		Write16(pPlayerIDInfo, Client->ConnID); //PlayerID

		len = pPlayerIDInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	len = p - buf;
	SendToClient(Client, 24390, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}
void NotifyWaitUnReadyPlayers(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, 0x4e20); //WaitLoadTime

	len = p - buf;
	SendToClient(Client, 510, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}


void NotifyUpdateKartSkillStoneInfo2(ClientNode* Client, int KartID)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	UINT skillstoneid[2] = { 21980,21986};
	//UINT skillstoneid[5] = { 21980,21986,22016,21992,22004 };
	Write32(p, Client->Uin); //Uin
	
	 //KartStoneInfo
	BYTE* pKartStoneInfo = p;
	Write16(pKartStoneInfo, 0); //len
	Write32(pKartStoneInfo, KartID); //KartID
	Write32(pKartStoneInfo, 2); //StoneGrooveNum
	for (int i = 0; i <2; i++)
	{
		BYTE* pStoneGrooveInfo = pKartStoneInfo;
		Write16(pStoneGrooveInfo, 0); //len

		Write32(pStoneGrooveInfo, 0); //StoneUseOccaType
		Write32(pStoneGrooveInfo, skillstoneid[i]); //SkillStoneID

		len = pStoneGrooveInfo - pKartStoneInfo;
		Set16(pKartStoneInfo, (WORD)len);
		pKartStoneInfo += len;
	}
	len = pKartStoneInfo - p;
	Set16(p, (WORD)len);
	p += len;
	len = p - buf;
	SendToClient(Client, 906, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void WINAPI OnPrepareTest(RoomNode* Room)
{
	UINT time = 0;
	char PlayerNum = Room->CurrentPlayerNum;
	ClientNode* RoomClient;
	BOOL AllReady = TRUE;
	while (time < SyncTime)
	{
		for (char i = 0; i < 6; i++)
		{
			RoomClient = Room->Player[i];
			if (RoomClient)
			{
				if (RoomClient->IsReady == FALSE)
				{
					AllReady = FALSE;
				}
			}
		}
		if (AllReady)
		{
			break;//所有人准备好就马上跳出循环否则继续等待
		}
		AllReady = TRUE;
		time += 1000;
		Sleep(1000);//每休眠一秒进行一次验证 超时自动跳出
	}
	for (char i = 0; i < 6; i++)
	{
		if (PlayerNum == 0)
		{
			return;//防止房间删除后没人了还继续执行后续代码
		}
		RoomClient = Room->Player[i];
		if (RoomClient)
		{
			if (RoomClient->IsReady == TRUE)
			{
				//等待所有人准备 同步跳舞动作 跳舞动作必须一样 否则卡起步 再发送性能数据
				NotifyKartPhysParam(RoomClient, Room->Player);
			}
			else
			{
				NotifyKartPhysParam(RoomClient, Room->Player);
				SendToClient(RoomClient, 514, (const BYTE*)"\x00\x00\x00\x00", 4, RoomClient->GameID, FE_GAMELOGIC, RoomClient->ConnID, Notify);
				if (Room->ChatRoomType == 6)
				{
					//异常退出3d房间
					ResponseCreateRoom(RoomClient, Room, 0);
				}
				//LeaveOutdoor(RoomClient);
				LeaveRoom(RoomClient, 0);//异常退出房间
				PlayerNum--;
			}
		}
	}
	CreateRoomTimer(Room, DanceTime, OnBegin);//游戏开始跳舞的时间 0直接跳过

}

RoomNode* NewRoom()
{
	RoomNode* Room = new RoomNode;
	
	Room->ID = InterlockedIncrement(&SeqRoomID);

	memset(Room->Name, 0, sizeof(Room->Name));
	Room->RoomOwnerID = 0;
	Room->ServerID = 0;
	Room->BaseGameMode = 0;
	Room->SubGameMode = 0;
	Room->SeatNum = 0;
	Room->CurrentPlayerNum = 0;
	Room->Flag = 0;
	memset(Room->Password, 0, sizeof(Room->Password));
	for (size_t i = 0; i < 6; i++)
	{
		Room->Player[i] = NULL;
	}
	Room->Timer = NULL;
	Room->Callback = NULL;

	Room->MapID = 0;
	Room->STDynamicInfo.Season = -1;
	Room->STDynamicInfo.Timeslot = -1;
	Room->STDynamicInfo.Weather = -1;

	Room->SceneID = 0;
	Room->MusicID = 0;
	
	std::lock_guard<std::recursive_mutex> lg(Mutex);
	Rooms[Room->ID] = Room;//多线程单读map可以不锁 同时读写map一定要锁 
	
	return Room;
}


RoomNode* GetRoom(long RoomID)
{
	RoomNode* Room = NULL;
	std::lock_guard<std::recursive_mutex> lg(Mutex);
	//DWORD dwStart = GetTickCount64(); //取windows启动到现在的流逝时间(毫秒)
	auto iter = Rooms.find(RoomID);
	if (iter != Rooms.end())
	{
		Room = iter->second;
	}
	else
	{
		//Room = iter->second;
		//printf("无效的房间ID:%d\n", RoomID);//产生房间错误如边境 3d休闲 竞速等会产生空指针
		//最好都提前执行LeaveRoom
	}
	//DWORD dwUsed = GetTickCount64() - dwStart; //计算该函数所消耗的时间
	//printf("Room Search lost:%d ms\n", dwUsed);
	return Room;
	
	
}
void PrintRoom()
{
	
	std::map<long, RoomNode*>::iterator iter = Rooms.begin();
	while (iter != Rooms.end())
	{
		RoomNode* Room = iter->second;
		if (Room)
		{
			printf("RoomID:%d, ", Room->ID);
			printf("BaseGameMode:%d, ", Room->BaseGameMode);
			printf("SubGameMode:%d, ", Room->SubGameMode);
			printf("ServerID:%d, ", Room->ServerID);
			printf("RoomOwnerID:%d, ", Room->RoomOwnerID);
			printf("Name:%s\n", Room->Name);
			printf("Flag:%d, ", Room->Flag);
			printf("Password:%s\n", Room->Password);
			for (char i = 0; i < 6; i++)
			{
				ClientNode* RoomClient = Room->Player[i];
				if (RoomClient)
				{
					printf("\tPlayerID:%d, SeatID:%d\n", RoomClient->ConnID, i);
				}
			}

			
		}
		iter++;
	}
}

VOID WINAPI OnTimer(PVOID p, BOOLEAN b)
{
	RoomNode* Room = (RoomNode*)p;
	if (DeleteTimerQueueTimer(TimerQueue, Room->Timer, NULL))
	{
		Room->Timer = NULL;
	}
	Room->Timer = NULL;
	Room->Callback(Room);
}

void CreateRoomTimer(RoomNode* Room, int Timeout, RoomOnTimer Callback)
{
	Room->Callback = Callback;
	CreateTimerQueueTimer(&Room->Timer, TimerQueue, OnTimer, Room, Timeout, 0, WT_EXECUTEINTIMERTHREAD);
}


void RequestGetRoomList(ClientNode* Client, BYTE* Body, size_t BodyLen)
{

	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	USHORT StartRoomIdx = Read16(Body);
	USHORT GetRoomNum = Read16(Body);
	USHORT BaseGameMode = Read16(Body);
	USHORT SubGameMode = Read16(Body);
	BYTE FBLev = Read8(Body);
	BYTE FBSeason = Read8(Body);
	BYTE RoomFlag = Read8(Body);

	ResponseGetRoomList(Client, BaseGameMode, SubGameMode);
}
void ResponseGetRoomList(ClientNode* Client, USHORT BaseGameMode, USHORT SubGameMode)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID
	Write16(p, (WORD)Rooms.size()); //CurTotalRoomNum
	Write16(p, 0); //StartIdx

	BYTE* pRoomNum = p;
	Write16(p, 0); //RoomNum
	{
		int RoomNum = 0;
		//DWORD dwStart = GetTickCount64(); //取windows启动到现在的流逝时间(毫秒)
		std::lock_guard<std::recursive_mutex> lg(Mutex);
		std::map<long, RoomNode*>::iterator iter;
		for (iter = Rooms.begin(); iter != Rooms.end(); iter++)
		{
			RoomNode* Room = iter->second;

			//if (Room->BaseGameMode != 0x2e)//
			//{ //Rooms
				RoomNum++;
				BYTE* pRooms = p;
				Write16(pRooms, 0); //len

				Write16(pRooms, Room->ID); //RoomID
				Write16(pRooms, Room->BaseGameMode); //BaseGameMode
				Write16(pRooms, Room->SubGameMode); //SubGameMode
				Write8(pRooms, Room->CurrentPlayerNum); //CurrentPlayerNum
				Write8(pRooms, Room->SeatNum); //TotalSeatNum
				if (Room->Callback == NULL && Room->SeatNum > 1)
				{
					Write8(pRooms, 1); //Status 房间状态 1为可进?0为不可进? 可以通过callback判断
				}
				else
					Write8(pRooms, 0);
				Write32(pRooms, Room->MapID); //MapID
#ifdef ZingSpeed
				Write8(pRooms, (BYTE)Room->Flag); //Flag
#else
				Write16(pRooms, Room->Flag); //Flag
#endif

				memcpy(pRooms, Room->Name, MaxRoomName); //RoomName
				pRooms += MaxRoomName;

				Write8(pRooms, 0); //HasFBInfo


#ifndef ZingSpeed
				Write8(pRooms, 0); //SpeFlag
				Write32(pRooms, 0); //RoomNo
				Write16(pRooms, 0); //SvrId
				//if(Room->ChatRoomType==0x6)
					//Write16(pRooms, 0x190); //SceneID

				Write16(pRooms, 0); //SceneID
				Write8(pRooms, 0); //CurrentOBNum
				Write8(pRooms, 0); //TotalOBNum
				Write8(pRooms, 0); //SpecialActivityStatus
				Write8(pRooms, 0); //AllowAutoStart
				Write32(pRooms, 0); //Gender
				Write32(pRooms, 0); //LocaleCode
				Write8(pRooms, 0); //TalkRoomBGID
				Write8(pRooms, 0); //SpecialActivityIDNum
				Write8(pRooms, 0); //SpecialActivityInfoNum

#endif

				len = pRooms - p;
				Set16(p, (WORD)len);
				p += len;
			//}
			//else
			//{
			//	continue;
			//}

		}
		//DWORD dwUsed = GetTickCount64() - dwStart; //计算该函数所消耗的时间
		//printf("Rooms Get List lost:%d ms\n", dwUsed);
		
		Set16(pRoomNum, RoomNum);
	}


	Write8(p, 0); //ReasonLen

	Write16(p, BaseGameMode); //BaseGameMode
	Write16(p, SubGameMode); //SubGameMode
	Write8(p, 0); //FBAvailableLev
	Write8(p, 0); //FBLev
	Write8(p, 0); //FBSeason

	Write16(p, 0); //ChannelStatus
	Write8(p, 0); //RoomFlag


	len = p - buf;
	SendToClient(Client, 102, buf, len, Client->ServerID, FE_GAMESVRD, Client->ConnID, Response);
}

void RequestCreateRoom(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	LeaveOutdoor(Client);
	LeaveRoom(Client, 0);
	LeaveBorderRoom(Client, 0);
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	USHORT BaseGameMode = Read16(Body);
	if (BaseGameMode == 1 || BaseGameMode == 2 || BaseGameMode == 19)
	{
	}
	else
	{
		ResponseStartGame(Client, "暂未开放");
		return;
	}
	USHORT SubGameMode = Read16(Body);
#ifdef ZingSpeed
	char* RoomName = (char*)Body;
	Body += MaxRoomName;

	BYTE SeatNum = Read8(Body);
	BYTE Flag = Read8(Body);
#else
	USHORT Flag = Read16(Body);

	char* RoomName = (char*)Body;
	/*for (int i = 0; i < 22; i++)
	{
		if (Body[i] != 0)
		{
			break;
		}
		else if (Body[21] == 0&&i==21)
		{
			//房间创建失败 不能空名字 
			return;
		}
	}*/
	Body += MaxRoomName;

	BYTE SeatNum = Read8(Body);
#endif

	char Password[16];
	memcpy(Password, Body, 16);
	Body += 16;
	

	BYTE IsNewerOpen = Read8(Body);
	BYTE FBSeason = Read8(Body);
	BYTE Contex = Read8(Body);
	BYTE FBLev = Read8(Body);

#ifndef ZingSpeed
	BYTE SpeFlag = Read8(Body);

	BYTE MoreInfoNum = Read8(Body);
	for (BYTE i = 0; i < MoreInfoNum; i++)
	{
		//m_astMoreInfos[].m_iTaskID
		Body += Get16(Body);
	}

	USHORT CreateRoomType = Read16(Body);
	USHORT ServerMatchType = Read16(Body);
	USHORT TeamMatchType = Read16(Body);
	BYTE ChatRoomType = Read8(Body);
	USHORT SceneID = Read16(Body);
	BYTE PresetOBNum = Read8(Body);
	BYTE AllowAutoStart = Read8(Body);
	BYTE TalkRoomBGID = Read8(Body);

	BYTE ValueNum = Read8(Body);
	for (BYTE i = 0; i < ValueNum; i++)
	{
		//m_aiEnterRoomValue[]
		Read32(Body);
	}
#endif

	RoomNode* Room = NewRoom();
	Room->BaseGameMode = BaseGameMode;
	Room->SubGameMode = SubGameMode;
	strcpy_s(Room->Name, RoomName);
	Room->ServerID = Client->ServerID;
	Room->RoomOwnerID = Client->ConnID;
	Client->RoomID = Room->ID;
	Room->SeatNum = SeatNum;
	Room->CurrentPlayerNum = 1;
	Room->Flag = Flag;
	memcpy(Room->Password, Password, 16);
	Room->ChatRoomType = ChatRoomType;
	for (char i = 0; i < 6; i++)
	{
		Room->Player[i] = nullptr;
		Room->SeatState[i] = 1;
	}
	Room->Player[0] = Client;
	Client->ReadyState = 0;//0 是准备 1是取消准备
	Client->ChatRoomID = -1;
	if (BaseGameMode == 0x2e)//龙晶大闯关
	{
		const char* buf1 = "\x00\x00\x00\x01\x00\x2e\x00\x01\x06\x00\xb4\xf3\xbc\xd2\xd2\xbb\xc6\xf0\xcc\xf4\xd5\xbd\xbc\xab\xcf\xde\xa3\xa1\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x70\x64\x1c\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0a\x00\x08\x47\x7e\x1d\x00\x00\x00\x00\x01\x00\x11\x00\x00\x00\x00\x00\x04\x01\x01\x00\x08\x11\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x0f\x24\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x0f\x24\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x17\x31\x2d\x31\x38\x37\x32\x34\x37\x33\x37\x36\x37\x2d\x31\x36\x38\x35\x30\x38\x37\x32\x36\x30\x00\x00\x00\x00\x00\x00\x00\x00\x00\x72\x69";
		SendToClient(Client, 103, (BYTE*)buf1, 207, Client->ServerID, FE_GAMESVRD, Client->ConnID, Response);
	}
	else
	{
		ResponseCreateRoom(Client, Room, ChatRoomType);
		//设置观战
		SendToClient(Client, 134, (BYTE*)"\x00\x00\x00\x00", 4, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
		if (ChatRoomType == 0x6)
		{
			RequestEnter3DRoom(Client);
		}
	}	
}
void ResponseCreateRoom(ClientNode* Client, RoomNode* Room,BYTE ChatRoomType)
{

	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID

	Write16(p, Room->ID); //RoomID
	Write16(p, Room->BaseGameMode); //BaseGameMode
	Write16(p, Room->SubGameMode); //SubGameMode
#ifdef ZingSpeed
	memcpy(p, Room->Name, MaxRoomName); //RoomName
	p += MaxRoomName;

	Write8(p, Room->SeatNum); //SeatNum
	Write8(p, (BYTE)Room->Flag); //Flag
#else
	Write16(p, 0x18c); //Flag 皇族 情侣贵族房间标志

	memcpy(p, Room->Name, MaxRoomName); //RoomName
	p += MaxRoomName;

	Write8(p, Room->SeatNum); //SeatNum
#endif // ZingSpeed


	Write8(p, 0); //SeatID
	Write8(p, 0); //TeamID

	Write8(p, 0); //ReasonLen


	Write8(p, 0); //LoverRaceOrPro

	Write32(p, Room->MapID); //MapID
	Write8(p, 0); //DebutOrX5
	Write32(p, (DWORD)time(nullptr)); //ServerTime
	Write32(p, 0); //PreKnowMapID
	Write32(p, 0); //PreKnownMusicID

	Write8(p, 0); //HasFBInfo
	/*
m_astFBInfo[%d].m_bAvailableLev
m_astFBInfo[%d].m_bLev
m_astFBInfo[%d].m_bSubLev
m_astFBInfo[%d].m_iBossID
m_astFBInfo[%d].m_bFBSeason
	*/

	Write32(p, 0); //HasFBInfoGuildScoreInNextGame
	Write8(p, 0); //HasFBInfoContex
	Write16(p, 0); //GuildScoreAlreadyAward
	Write16(p, 0); //GuildScoreTotalAward
#ifndef ZingSpeed
	Write8(p, 0xa); //HasFBInfoSpeFlag
	Write32(p, Room->ID); //RoomNo

	Write8(p, 0); //MoreInfoNum
	/*
m_astMoreInfos[%d].m_iTaskID
	*/


	Write16(p, 0); //RaceCardNums
	/*
m_astRaceCardAddValueInfo[%d].m_uiRaceCardID
m_astRaceCardAddValueInfo[%d].m_uiAddValue
	*/

	Write16(p, 0); //CreateRoomType
	Write16(p, 0); //ServerMatchType
	Write16(p, 0); //TeamMatchType
	Write8(p, ChatRoomType); //ChatRoomType 3d房间是6
	if (ChatRoomType == 6)
	{
		Write16(p, 0x190);
	}
	else
	{
		Write16(p, 0); //SceneID 0x190
	}
	
	Write8(p, 0); //PresetOBNum
	Write8(p, 0); //AllowAutoStart
	Write8(p, 0); //TalkRoomBGID
	Write16(p, 0); //Role

	Write8(p, 0); //ParaNum
	//ParaList[]

	Write8(p, 0); //ValueNum
	//EnterRoomValue[]

	Write32(p, 0); //PlayerEquipKartID
	Write32(p, 0); //RankedMatchTestDriveKartID
	Write8(p, 0); //GVoiceRoomNameLen
	Write8(p, 0); //GVoiceReasonLen
	Write8(p, 0); //TDCExcluItemNum
	//TDCExclusiveItemID[]

	Write8(p, 0); //TestKartGameType
	Write32(p, 0); //GameTestKartID

	Write8(p, 0); //HasStarsFightingInfo
	/*
m_stStarsFightingInfo[%d].m_iStar
m_stStarsFightingInfo[%d].m_iStarVal
m_stStarsFightingInfo[%d].m_iStarsFightingStarLevel
	*/

	Write8(p, 0); //HasYuLeJiaNianHuaInfo
	/*
m_stYuLeJiaNianHuaInfo[%d].m_uiMode
m_stYuLeJiaNianHuaInfo[%d].m_uiScore
m_stYuLeJiaNianHuaInfo[%d].m_uchRankRangNum
m_stYuLeJiaNianHuaInfo[%d].m_auiRankRange[%d]
m_stYuLeJiaNianHuaInfo[%d].m_uchRankScoreNum
m_stYuLeJiaNianHuaInfo[%d].m_auiRankScore[%d]
m_stYuLeJiaNianHuaInfo[%d].m_uchInRecommend
m_stYuLeJiaNianHuaInfo[%d].m_uchInDoubleScore
	*/
#endif

	len = p - buf;
	SendToClient(Client, 103, buf, len, Client->ServerID, FE_GAMESVRD, Client->ConnID, Response);
}




void RequestEnterRoom(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	LeaveOutdoor(Client);
	LeaveRoom(Client, 0);
	LeaveBorderRoom(Client, 0);
	//printf("RequestEnterRoom\n");
	//请求进入房间 
	//自行添加验证密码和游戏过程能否进入
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	USHORT RoomID = Read16(Body);

	char Password[16] = { 0 };
	memcpy(Password, Body, 16);
	Body += 16;
	

	BYTE InviteType = Read8(Body);
	UINT InviterUin = Read32(Body);
	BOOL HasMoreInfo = FALSE;

	RoomNode* Room = GetRoom(RoomID);
	if (!Room)
	{
		return;
	}
	if (Room->Callback != NULL || Room->CurrentPlayerNum == 6 || Room->SeatNum==Room->CurrentPlayerNum)
	{
		return;
	}
	
	for (int i = 0; i < 15; i++)
	{
		if (Password[i+1] != Room->Password[i+1])
		{    //默认传0x30
			//从第1位开始比较 0位不管
			ResponseStartGame(Client, "房间密码错误!");
			return;
		}
	}
	
	
	for (int i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient == 0&&Room->SeatState[i]==1)
		{
			Client->SeatID = i;
			Client->RoomID = RoomID;
			Client->ReadyState = 1;
			Room->Player[i] = Client;
			Room->CurrentPlayerNum++;
			Client->ChatRoomID = -1;
			if (Room->ChatRoomType == 6)
			{
				//进入3d房间
				ResponseCreateRoom(Client, Room, 6);
				RequestEnter3DRoom(Client);
				NotifyChangeRoomOwner(Client, Room);
			}
			else
			{
				ResponseEnterRoom(Client, Room, i, 0, 0);//回复进入房间让自己看到其他人的信息
			}
			//设置观战
			SendToClient(Client, 134, (BYTE*)"\x00\x00\x00\x00", 4, Client->ConnID, FE_PLAYER, Client->ConnID, Response);

			
			//通知其它玩家
			for (char i2 = 0; i2 < 6; i2++)
			{
				ClientNode* RoomClient = Room->Player[i2];
				if (RoomClient && RoomClient != Client)
				{
					
					NotifyEnterRoom(RoomClient, Room, Client, i);
					NotifyEnterRoom(Client, Room, RoomClient, i2);
				}
			}
			for (char i3 = 0; i3 < 6; i3++)
			{
				ClientNode* RoomClient = Room->Player[i3];
				if (RoomClient && RoomClient != Client)
				{
					NotifyChangeReadyState(RoomClient, Client->Uin, Client->ReadyState);
					NotifyChangeReadyState(Client, RoomClient->Uin, RoomClient->ReadyState);
				}
			}
			for (char i4 = 0; i4 < 6; i4++)
			{
				if (Room->SeatState[i4] == 0)
				{
					NotifyChangeSeatState(Client, i4, 0);//座位状态变化
				}
			}
			//通知其它玩家
			
			break;
		}
	}
	
}

void ResponseEnterRoom(ClientNode* Client, RoomNode* Room, char SeatID,BOOL HasMoreInfo,char index)
{
	//printf("ResponseEnterRoom\n");
	//回复进入房间
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID

	Write16(p, Room->ID); //RoomID
	Write16(p, Room->BaseGameMode); //BaseGameMode
	Write16(p, Room->SubGameMode); //SubGameMode


	memcpy(p, Room->Name, MaxRoomName); //RoomName
	p += MaxRoomName;

	Write8(p, 6); //SeatNum 固定写当前6个座位可用
#ifdef ZingSpeed
	Write8(p, (BYTE)Room->Flag); //Flag
#else
	Write16(p,0x18c); //Flag
#endif

	Write8(p, SeatID); //SeatID
	Write8(p, 0); //TeamID
	Write32(p, Room->MapID); //MapID
	Write16(p, Room->RoomOwnerID); //RoomOwnerID
	
	//SeatStatus[6]
	for (size_t i = 0; i < 6; i++)
	{
		Write8(p, 2);//写6个座位的座位状态 0显示x 
		//Write8(p, 1);
	}

	//BYTE* pPlayerCount = p;
	Write8(p,0); //PlayerCount //写其他玩家信息 多了看不到
	/*int PlayerCount = 0;
	for (int i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			if (RoomClient != Client)
			{
		       PlayerCount++;
			   WriteVisbleInfo(RoomClient, p, RoomClient->Uin, RoomClient->SeatID, RoomClient->ConnID); //NewPlayerInfo
			   break;
			}
		}
	}
	Set8(pPlayerCount, PlayerCount);*/

	Write8(p, 0); //ReasonLen
	Write8(p, 0); //PlayerCount2

	Write16(p, 0); //KartNum


	Write8(p, 0); //LoverRaceOrPro

	{ //STDynamicInfo
		BYTE* pSTDynamicInfo = p;
		Write16(pSTDynamicInfo, 0); //len

		Write8(pSTDynamicInfo, Room->STDynamicInfo.Season);
		Write8(pSTDynamicInfo, Room->STDynamicInfo.Timeslot);
		Write8(pSTDynamicInfo, Room->STDynamicInfo.Weather);

		len = pSTDynamicInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write32(p, 0); //PreKnowMapID
	Write8(p, 0); //HasMoreInfo
	Write32(p, 0); //MapSubID

	Write8(p, 0); //HasFBInfo

	Write32(p, 0); //GuildScoreInNextGame
	Write16(p, 0); //GuildScoreAlreadyAward
	Write16(p, 0); //GuildScoreTotalAward

	Write8(p, 0); //SpeFlag
	Write8(p, 0); //MapNum
	
	Write32(p, Room->ID); //RoomNo
	Write16(p, 0); //SvrId
	Write16(p, 0); //RaceCardNums
	
	Write16(p, 0); //CreateRoomType
	Write16(p, 0); //ServerMatchType
	Write16(p, 0); //TeamMatchType
	Write16(p, 0); //MatchedRoomType
	Write8(p, 0); //InviteType
	Write8(p, 0); //HasWeRelayRoomInfo

	Write8(p, 0); //RoomFlag
	Write8(p, 0); //MaxOBNum
	Write8(p, 0); //AllowAutoStart
	Write8(p, 0); //HasLMInfo

	Write8(p, 0); //TalkRoomBGID
	Write16(p, 0); //Role
	Write8(p, 0); //ParaNum
	//Write32(p, 0); //ParaList[]
	{ //RoomInfoChange
		BYTE* pRoomInfoChange = p;
		Write16(pRoomInfoChange, 0); //len

		Write32(pRoomInfoChange, 0); //TeamJumpLevel
		Write32(pRoomInfoChange, 0); //RoomBGID

		len = pRoomInfoChange - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write32(p, 0); //PlayerEquipKartID
	Write32(p, 0); //RankedMatchTestDriveKartID
	Write8(p, 0); //FirstlyTipMap
	Write8(p, 0); //GVoiceRoomNameLen
	Write8(p, 0); //GVoiceReasonLen
	Write8(p, 0); //TDCExcluItemNum
	//Write32(p, 0); //TDCExclusiveItemID[]
	Write8(p, 0); //TestKartGameType
	Write32(p, 0); //GameTestKartID
	Write8(p, 0); //HasStarsFightingInfo
	
	Write8(p, 0); //HasYuLeJiaNianHuaInfo
	
	len = p - buf;
	SendToClient(Client, 104, buf, len, Room->ID, FE_ROOM, Client->ConnID, Response);
}
void NotifyEnterRoom(ClientNode* Client, RoomNode* Room, ClientNode* RoomClient, char SeatID)
{
	//printf("NotifyEnterRoom\n");
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	UINT KartHeadRefitItemID = 0;
	UINT KartTailRefitItemID = 0;
	UINT KartFlankRefitItemID = 0;
	UINT KartTireRefitItemID = 0;

	UINT ShapeSuitID = 0;
	UCHAR LegendSuitLevel = 10;
	UINT LegendSuitLevelChoice = 1111;
	UINT ShapeLegendSuitID = 0;
	

	Write16(p, Room->ID); //RoomID

	WriteVisbleInfo(RoomClient,p, RoomClient->Uin, SeatID, RoomClient->ConnID); //NewPlayerInfo

	{ //PlayerRelationInfo
		BYTE* pPlayerRelationInfo = p;
		Write16(pPlayerRelationInfo, 0); //len


		Write32(pPlayerRelationInfo, RoomClient->Uin); //SrcUin
		
		Write32(pPlayerRelationInfo, 0); //RelationFlag
		
		Write32(pPlayerRelationInfo, 0); //RelationUin

		memset(pPlayerRelationInfo, 0, MaxNickName);
		pPlayerRelationInfo += MaxNickName;

		Write32(pPlayerRelationInfo, 0); //EngageTime
		Write32(pPlayerRelationInfo, 0); //NextCanBookingTimeLimit
		Write32(pPlayerRelationInfo, 0); //BeginHoneyMoonTime
		Write32(pPlayerRelationInfo, 0); //EndHoneyMoonTime
		Write8(pPlayerRelationInfo, 0x4); //EngageFlag


		len = pPlayerRelationInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	sql = "SELECT KartHeadRefitItemID,KartTailRefitItemID,KartFlankRefitItemID,KartTireRefitItemID,ShapeSuitID FROM KartRefit WHERE Uin = ? and KartID = ?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, RoomClient->Uin);
		sqlite3_bind_int(stmt, 2, RoomClient->KartID);
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW)
		{
			KartHeadRefitItemID = sqlite3_column_int(stmt, 0);
			KartTailRefitItemID = sqlite3_column_int(stmt, 1);
			KartFlankRefitItemID = sqlite3_column_int(stmt, 2);
			KartTireRefitItemID = sqlite3_column_int(stmt, 3);
			ShapeLegendSuitID = ShapeSuitID = sqlite3_column_int(stmt, 4);
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;
	Write16(p, 1); //KartNum
	{ //KartRefitInfo
		BYTE* pKartRefitInfo = p;
		Write16(pKartRefitInfo, 0); //len

		Write32(pKartRefitInfo, RoomClient->Uin); //Uin
		Write32(pKartRefitInfo, RoomClient->KartID); //KartId
		Write32(pKartRefitInfo, 0); //RefitCout
		Write16(pKartRefitInfo, 0); //MaxFlags
		Write16(pKartRefitInfo, 0); //WWeight
		Write16(pKartRefitInfo, 0); //SpeedWeight
		Write16(pKartRefitInfo, 0); //JetWeight
		Write16(pKartRefitInfo, 0); //SJetWeight
		Write16(pKartRefitInfo, 0); //AccuWeight
		Write32(pKartRefitInfo, 0); //ShapeRefitCount
		Write32(pKartRefitInfo, KartHeadRefitItemID); //KartHeadRefitItemID
		Write32(pKartRefitInfo, KartTailRefitItemID); //KartTailRefitItemID
		Write32(pKartRefitInfo, KartFlankRefitItemID); //KartFlankRefitItemID
		Write32(pKartRefitInfo, KartTireRefitItemID); //KartTireRefitItemID
		Write32(pKartRefitInfo, 0); //SecondRefitCount
		Write16(pKartRefitInfo, 0); //Speed2Weight
		Write16(pKartRefitInfo, 0); //DriftVecWeight
		Write16(pKartRefitInfo, 0); //AdditionalZSpeedWeight
		Write16(pKartRefitInfo, 0); //AntiCollisionWeight
		Write16(pKartRefitInfo, 0); //LuckyValue
		Write16(pKartRefitInfo, 0); //RefitLuckyValueMaxWeight
		Write32(pKartRefitInfo, ShapeSuitID); //ShapeSuitID
		Write8(pKartRefitInfo, LegendSuitLevel); //LegendSuitLevel
		Write32(pKartRefitInfo, LegendSuitLevelChoice); //LegendSuitLevelChoice
		Write32(pKartRefitInfo, ShapeLegendSuitID); //ShapeLegendSuitID

		len = pKartRefitInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	{ //RoomInfoChange
		BYTE* pRoomInfoChange = p;
		Write16(pRoomInfoChange, 0); //len

		Write32(pRoomInfoChange, 0); //TeamJumpLevel
		Write32(pRoomInfoChange, 0); //RoomBGID

		len = pRoomInfoChange - p;
		Set16(p, (WORD)len);
		p += len;
	}
	len = p - buf;
	SendToClient(Client, 500, buf, len, Room->ID, FE_ROOM, Client->ConnID, Notify);
}


void RequestLeaveRoom(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);
	short LeaveType = 0;
#ifndef ZingSpeed
	LeaveType = Read16(Body);//正常是0 客户端某些时候会自动请求该消息导致退房错误 
	//BYTE LeaveRoomReason = Read8(Body);
#endif
	/*普通房间强制观战后防止自动退出
	if (Client->OBState == 1 && Client->ChatRoomID == -1)
	{
		RoomNode* Room = GetRoom(Client->RoomID);
		//防止观战状态强制退出 会请求2次
		if (Room)
		{
			//if (Client->AutoLeave != 1)//保证每局只触发自动退出一次释放资源
			//{
			//	ResponseLeaveRoom(Client, 0);
			//	Client->AutoLeave = 1;
			//	return;
			//}
			ResponseEnterRoom(Client, Room, Client->SeatID, 0, 0);
			for (char j = 0; j < 6; j++)
			{
				ClientNode* RoomClient2 = Room->Player[j];
				if (RoomClient2 && RoomClient2 != Client)
				{
					NotifyEnterRoom(Client, Room, RoomClient2, RoomClient2->SeatID);
				}
			}
			SendToClient(Client, 134, (BYTE*)"\x00\x00\x01\x00", 4, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
			ResponseStartGame(Client,"请关闭观战模式再退出房间");
			return;
		}
	}*/
	if (LeaveType == 0)
	{
		LeaveOutdoor(Client);
		LeaveRoom(Client, LeaveType);
		LeaveBorderRoom(Client, LeaveType);
	}	
	
}
void LeaveRoom(ClientNode* Client, short LeaveType)
{
	RoomNode* Room = GetRoom(Client->RoomID);
	if (!Room)
	{
		return;
	}
	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			if (RoomClient == Client)
			{
				ResponseLeaveRoom(Client, LeaveType);
				RoomClient->ReadyState = 1;
				//RoomClient->OBState = 0;
				RoomClient->TaskID = 0;
				RoomClient->RoomID = 0;
				Room->Player[i] = NULL;
				Room->CurrentPlayerNum--;

				BOOL IsRoomOwner = FALSE;
				short NewRoomOwnerID = Room->RoomOwnerID;
				if (NewRoomOwnerID == Client->ConnID)
				{
					IsRoomOwner = TRUE;
					for (char i2 = 0; i2 < 6; i2++)
					{
						RoomClient = Room->Player[i2];
						if (RoomClient)
						{
							NewRoomOwnerID = RoomClient->ConnID; //转让房主
							RoomClient->ReadyState = 0;//设置准备状态
							break;
						}
					}
				}
				Room->RoomOwnerID = NewRoomOwnerID;

				//通知其它玩家
				int n = 0;
				for (char i2 = 0; i2 < 6; i2++)
				{
					RoomClient = Room->Player[i2];
					if (RoomClient)
					{
						NotifyLeaveRoom(RoomClient, Client->Uin, i, IsRoomOwner, NewRoomOwnerID, LeaveType);
						n++;
					}
				}

				if (n == 0)
				{
					if (Room->Timer)
					{
						if (DeleteTimerQueueTimer(TimerQueue, Room->Timer, INVALID_HANDLE_VALUE))
						{
							Room->Timer = NULL;
						}
					}
				
					std::lock_guard<std::recursive_mutex> lg(Mutex);
					Rooms.erase(Room->ID);
					delete Room;
					//Room = NULL;
				}
				break;

			}
		}
	}
}
void LeaveBorderRoom(ClientNode* Client, short LeaveType)
{
	RoomNode* Room = GetRoom(Client->BorderRoomID);
	if (!Room)
	{
		return;
	}
	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient == Client)
		{
			ResponseLeaveRoom(RoomClient, LeaveType);
			RoomClient->ReadyState = 1;
			RoomClient->TaskID = 0;
			RoomClient->BorderRoomID = 0;
			Room->Player[i] = NULL;
			Room->CurrentPlayerNum--;
			
			if (Room->Timer)
			{
				if (DeleteTimerQueueTimer(TimerQueue, Room->Timer, INVALID_HANDLE_VALUE))
				{
					Room->Timer = NULL;
				}
			}
			std::lock_guard<std::recursive_mutex> lg(Mutex);
			Rooms.erase(Room->ID);
			delete Room;//清理边境房间
			//通知其它玩家...
			break;
		}

	}
}
void ResponseLeaveRoom(ClientNode* Client, short LeaveType)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID

	Write8(p, 0); //ReasonLen

#ifndef ZingSpeed
	Write16(p, LeaveType); //LeaveType
	Write16(p, 0); //BaseGameMode
	Write16(p, 0); //SubGameMode
	Write8(p, 0); //IsLeaveGVoice
#endif

	len = p - buf;
	SendToClient(Client, 105, buf, len, Client->RoomID, FE_ROOM, Client->ConnID, Response);
}
void NotifyLeaveRoom(ClientNode* Client, UINT Uin, char SeatID, bool IsChangeRoomOwner, short NewRoomOwnerID, short LeaveType)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, Client->RoomID); //RoomID
	Write32(p, Uin); //Uin
	Write8(p, SeatID); //SeatID
	Write8(p, IsChangeRoomOwner); //IsChangeRoomOwner
	Write16(p, NewRoomOwnerID); //NewRoomOwnerID

#ifdef ZingSpeed
	Write8(p, 0); //Flag
#else
	Write16(p, 0); //Flag
#endif
	
	Write8(p, 0); //HasFBInfo
	/*
m_astFBInfo[].m_bAvailableLev
m_astFBInfo[].m_bLev
m_astFBInfo[].m_bSubLev
m_astFBInfo[].m_iBossID
m_astFBInfo[].m_bFBSeason
	*/

	len = p - buf;
	SendToClient(Client, 501, buf, len, Client->RoomID, FE_ROOM, Client->ConnID, Notify);
}


void NotifyBorderPlayerInfo(ClientNode* Client)
{
	RoomNode* BorderRoom=NULL;
	if (Client->RoomID != 0)
	{
		BorderRoom = GetRoom(Client->RoomID);
	}
	else if (Client->BorderRoomID != 0)
	{
		BorderRoom = GetRoom(Client->BorderRoomID);
	}
	if (!BorderRoom )
	{
		return;
	}
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	Write32(p, BorderRoom->BaseGameMode); //BaseMode
	Write32(p, BorderRoom->SubGameMode); //SubMode
	Write8(p, BorderRoom->CurrentPlayerNum); //PlayerCount
	for (size_t i = 0; i < 6; i++)
	{ //PlayerRoomVisibleInfo
		ClientNode* RoomClient = BorderRoom->Player[i];
		if (RoomClient)
		{
			BYTE* pPlayerRoomVisibleInfo = BorderOnePlayerInfo;
			pPlayerRoomVisibleInfo += 2;
			Write32(pPlayerRoomVisibleInfo, RoomClient->Uin); //Uin
			BYTE* pBack = pPlayerRoomVisibleInfo;
			pPlayerRoomVisibleInfo += 9;
			WritePlayerDBBaseInfo(pPlayerRoomVisibleInfo, RoomClient->Uin);
			pPlayerRoomVisibleInfo = pBack;
			pPlayerRoomVisibleInfo += 350;
			//装备车辆
			if (RoomClient->KartSkinID != 0)
				Write32(pPlayerRoomVisibleInfo, RoomClient->KartSkinID);
			else
				Write32(pPlayerRoomVisibleInfo, RoomClient->KartID);
			memcpy(p, BorderOnePlayerInfo, 805);
			p += 805;
		}
	}
	Write16(p, 0); 
	
	if (Client->TaskID == 0xFFFD||Client->TaskID==0)
	{
		memcpy(p, "\x00\x00\x00\x00\x00", 5);
		p += 5;
	}
	else if (Client->TaskID == 0xFFFC)
	{
		memcpy(p, "\x00\x00\x01\x00\x1e\x00\x01\x98\x99\x00\x01\x98\xa3\x00\x01\x98\x99\x00\x01\x98\xa3\x00\x00\x00\x00\x00\x00\x27\x3d\x00\x00\x27\x30\x00\x00", 35);
		p +=35;
	}
	
	len = p - buf;
	
	SendToClient(Client, 548, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);

}
void NotifyRankedMatchBanMapInfo(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	UINT randindex = (rand() % 20);
	{ //BanMapCfg
		BYTE* pBanMapCfg = p;
		Write16(pBanMapCfg, 0); //len

		Write32(pBanMapCfg, 0); //GradeLevelLimit
		Write32(pBanMapCfg, 4); //ChooseTime
		Write32(pBanMapCfg, 4); //ShowTime
		Write32(pBanMapCfg, 8); //TotalMapNum
		Write32(pBanMapCfg, 1); //ChooseMapNum
		Write32(pBanMapCfg, 0); //BonusScore
		Write32(pBanMapCfg, 0); //PinnacleBattleTotalMapNum
		Write32(pBanMapCfg, 0); //PinnacleBattleChooseMapNum

		len = pBanMapCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write32(p, 8); //MapNum
	sql = "SELECT RankMap FROM MapRand limit ?,8;";//随机取出8张图显示 
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, randindex);
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			{ //MapInfo
				BYTE* pMapInfo = p;
				Write16(pMapInfo, 0); //len

				Write32(pMapInfo, sqlite3_column_int(stmt, 0)); //MapID
				Write32(pMapInfo, 0); //Status
				Write8(pMapInfo, 0); //ThemeMapOrNot
				Write8(pMapInfo, 0); //SeasonNewMapOrNot
				Write8(pMapInfo, 0); //PinnacleBattleMapOrNot
				Write16(pMapInfo, 0); //TotalBeBannedNums
				Write16(pMapInfo, 0); //FinalRandBanMapType

				len = pMapInfo - p;
				Set16(p, (WORD)len);
				p += len;
			}
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;

	Write8(p, 0); //Type

	len = p - buf;
	SendToClient(Client, 25009, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void WINAPI OnBorderRace(RoomNode* Room)
{
	Room->CountDownFlag = 0;
	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			NotifyRaceBegin(RoomClient);
			//SendToClient(RoomClient, 28241, (BYTE*)"\x00\x00\x27\x11\x00\x00\x14\x00\x00\x00\x63\x00\x00\x00\x00\x00\x00\x00", 18, RoomClient->GameID, FE_GAMELOGIC, RoomClient->ConnID, Notify);
			
		}
	}
}
void WINAPI OnBorderGame(RoomNode* Room)
{
	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			if (RoomClient->GlobalStone == 1)
			{
				NotifyUpdateKartSkillStoneInfo2(RoomClient, RoomClient->KartID);//全局宝石
			}
			NotifyGameBegin(RoomClient, Room->Player);
			NotifyGameNPCInfo(RoomClient);
			NotifyKartPhysParam(RoomClient, NULL);
			//NotifyOtherKartStoneInfo(RoomClient);
		}
	}
	//跳舞并同步加载
	CreateRoomTimer(Room, 16000, OnBorderRace);
}
void WINAPI OnNotifyPlayerInfo(RoomNode* Room)
{
	int time = 0;
	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			NotifyBorderPlayerInfo(RoomClient);
			if (RoomClient->TaskID == 0xFFFC)
			{
				time = 3000;
				NotifyRankedMatchBanMapInfo(RoomClient);//排位禁图
				
			}	
			else
			{
				time = 0;
			}
		}
	}
	//开始游戏
	CreateRoomTimer(Room, time, OnBorderGame);
}
void WINAPI OnMatchResult(RoomNode* Room)
{
	//Room->Flag = 0x18c;//标志该房间不能进入
	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			NotifyMatchResult(RoomClient, Room->matchQueueType);
		}
	}
	//等待EnterMatchRoom 并发送NotifyBorderPlayerInfo
	CreateRoomTimer(Room, 1000, OnNotifyPlayerInfo);
}
RoomNode* NewBorderRoom(char matchQueueType)
{
	//printf("NewBorderRoom\n");
	RoomNode *BorderRoom = NewRoom();
	if (!BorderRoom)
	{
		return NULL;
	}
	//GlobalBorderRoomID = BorderRoom->ID;//新建一个边境房间 并记录新的可用房间号

	if (matchQueueType == 0|| matchQueueType == 1)
	{
		BorderRoom->BaseGameMode = BorderRoom->SubGameMode = 1;
	}
	else if (matchQueueType == 0xa)
	{
		BorderRoom->BaseGameMode = 0x28;
		BorderRoom->SubGameMode  = 1;
	}

	//随机地图
	BorderRoom->matchQueueType = matchQueueType;
	BorderRoom->MapID = GetRandMap(5);
	CreateRoomTimer(BorderRoom, 1000, OnMatchResult);
	return BorderRoom;
	//建立成功后 开始计时等待其他用户加入并 通知匹配结果
	
}
void ResponseStartBorderGame(ClientNode* Client,USHORT matchQueueType,UINT MapID)
{
	LeaveOutdoor(Client);
	LeaveRoom(Client, 0);
	LeaveBorderRoom(Client, 0);
	ResponseAddToMatchQueue(Client, matchQueueType);
	//RoomNode* BorderRoom = GetRoom(GlobalBorderRoomID);
	/*if (!BorderRoom)//如果房间不存在或者人数满了或者开始了游戏就新建否则直接加入房间
	{
		BorderRoom = NewBorderRoom(matchQueueType);
	}
	else if (BorderRoom->CurrentPlayerNum == 6 || BorderRoom->Flag != 0 || BorderRoom->matchQueueType != matchQueueType)
	{
		BorderRoom = NewBorderRoom(matchQueueType);
	}*/
	RoomNode* BorderRoom = NewBorderRoom(matchQueueType);

	if (!BorderRoom)
	{
		return;
	}
	//填充客户端地图信息
	if (MapID != 0)
	{
		BorderRoom->MapID = MapID;
	}
	Map* pMap = GetMap(BorderRoom->MapID);
	if(matchQueueType==0)
		Client->TaskID = 0xFFFD;
	else if(matchQueueType==0xa)
		Client->TaskID = 0xFFFC;
	else if (matchQueueType == 0x1)//普通立即竞速
		Client->TaskID = 0xFFFB;
	Client->GameID = 2;
	Client->IsReady = TRUE;
	if (pMap)
	{
		Client->MapCompatibilityMode = false;
		Client->EndCheckPoint = pMap->End;
		Client->TotalRound = pMap->Round;
		Client->Loop = pMap->Loop;
	}
	else
	{
		Client->MapCompatibilityMode = true;
		Client->EndCheckPoint = 0;
		Client->TotalRound = 1;
		Client->Loop = false;
	}
	Client->MapID = BorderRoom->MapID;
	Client->FinishTime = 0;
	Client->Round = 0;
	Client->PassedCheckPoint = 0;
	Client->BorderRoomID = BorderRoom->ID;
	Client->IsFinish = FALSE;
	//加入房间
	for (char i = 0; i < 6; i++)
	{
		if (!BorderRoom->Player[i])//空位
		{
			
			BorderRoom->Player[i] = Client;
			BorderRoom->CurrentPlayerNum++;
			break;
		}
	}
	
	
}

	

void StartSingleGame(ClientNode* Client, BYTE* Body)
{
	
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	//const char* buf2;
	RoomNode* Room = GetRoom(Client->RoomID);
	int TaskID = Read32(Body);
	UINT MapID = Read32(Body);
	Client->TaskID = TaskID;
	if (TaskID != 0x06a5)
	{
		LeaveOutdoor(Client);
		LeaveRoom(Client, 0);
		LeaveBorderRoom(Client, 0);
	}
	//printf("TaskID:%d\n", Client->TaskID);
	if (!Room)
	{
		MapID = GetRandMap(0);
	}
	else
	{
		if (Room->MapID < 100)
		{
			MapID = GetRandMap(0);
		}
		else
		{
			MapID = Room->MapID;
		}
	}

	if (TaskID == 0x49) //暴风随机
	{
		//int i = rand() % 5 ;
		MapID = baofengmap[Client->OptIndex];
		if (Client->OptIndex <= 0)
			Client->OptIndex = 4;
		else
			Client->OptIndex -= 1;
		
		
	}
	Map* pMap = GetMap(MapID);
	Client->GameID = 0;
	Client->IsReady = TRUE;
	if (pMap)
	{
		Client->MapCompatibilityMode = false;
		Client->EndCheckPoint = pMap->End;
		Client->TotalRound = pMap->Round;
		Client->Loop = pMap->Loop;
	}
	else
	{
		Client->MapCompatibilityMode = true;
		Client->EndCheckPoint = 0;
		Client->TotalRound = 1;
		Client->Loop = false;
	}
	Client->MapID = MapID;
	Client->FinishTime = 0;
	Client->Round = 0;
	Client->PassedCheckPoint = 0;
	if (TaskID == 0x06a5)
	{
		//int MapID = Read32(Body);
		//UCHAR Level = Read8(Body);
		//printf("TaskID：%d MapID：%d\n", TaskID, MapID);
		Write32(p, 0xea60); //NormalLoadTime
		Write32(p, TaskID); //TaskID
		Write32(p, MapID); //MapID
		//MapHash[]
		memset(p, 0, 32);
		p += 32;
		Write32(p, 0); //GameID
		Write32(p, (DWORD)time(nullptr)); //Seed
		Write16(p, Client->TotalRound); //TotalMapRound pMap可能空指针
		Write32(p, 0); //TimeLimit
		Write32(p, 0); //MaxNPCDistance
		Write16(p, 0); //InitPropNum
		Write16(p, 0); //NpcNum
	
		Write32(p, 0); //PlayerItemNum
	
		Write8(p, 0); //SyncCarNum
	
		Write8(p, 0); //PlayerNum
	
		Write8(p, 0); //FeedBackEnabled
		Write16(p, 0); //PropID
		Write32(p, 0); //PropIndex
		Write16(p, 0); //PropNum
		Write16(p, 0); //LogicType
		Write8(p, 0); //MapCheckpointFileIndex
		Write32(p, 0); //Duration
		Write32(p, 0); //BeginCDTime
		Write32(p, 0); //PropInteval
		len = p - buf;
		SendToClient(Client, 530, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
	}
	else if (TaskID == 0x49)
	{
	BYTE* pp = baofengtiaozhan;
	pp += 8;
	//rand()%(b-a+1) +a 
	Write32(pp, MapID);
	pp += 40;
	Write16(pp, Client->TotalRound);
	SendToClient(Client, 530, baofengtiaozhan, 1928, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
	}
	else if (TaskID == 0x6e)//树苗
	{
		BYTE* pp = shumiaoyunshu;
		pp += 8;
		Write32(pp, MapID);
		pp += 40;
		Write16(pp, Client->TotalRound);
		SendToClient(Client, 530, shumiaoyunshu, 98, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
	}
	else if (TaskID == 0x48)//车王考验
	{
	BYTE* pp = chewangkaoyan;
	pp += 8;
	Write32(pp, MapID);
	pp += 40;
	Write16(pp, Client->TotalRound);
	Write32(pp, 0x2FFFD);//timelimit
	SendToClient(Client, 530, chewangkaoyan, 98, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);

	}
	NotifyKartPhysParam(Client, NULL);
	//NotifyOtherKartStoneInfo(Client);
	SendToClient(Client, 531, (BYTE*)"\x00\x00", 2, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
	
}

void WINAPI OnStart(RoomNode* Room)
{
	
}
void RequestStartGame(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);
	
	RoomNode* Room = GetRoom(Client->RoomID);
	if (!Room)
	{
		return;
	}
	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			if (RoomClient->ReadyState == 1)
			{
				ResponseStartGame(Client, "玩家未准备!");
				return;
			}
		}
	}
	if (Room->Callback)
	{
		ResponseStartGame(Client, "游戏进行中,无法开始!");
		return;//防止重复点击开始bug
	}

	Room->Callback = OnStart;//设置回调
	Room->ranknumber = 0;//排名
	if (Room->BaseGameMode == 4) //舞蹈
	{
		if (Room->SceneID == 0)
		{
			Room->SceneID = 17;
		}

		if (Room->MusicID < 10)
		{
			Room->MusicID = 303;
		}

		for (char i = 0; i < 6; i++)
		{
			ClientNode* RoomClient = Room->Player[i];
			if (RoomClient)
			{
				RoomClient->GameID = 2;
				RoomClient->IsReady = TRUE;
				RoomClient->IsFinish = FALSE;

				RoomClient->Scores = 0;

				NotifyDanceGameBegin(RoomClient);
			}
		}
		//CreateRoomTimer(Room, DanceMusicDuration(Room->MusicID), OnDanceTimer);
		CreateRoomTimer(Room, DanceMusicDuration(Room->MusicID), OnDanceTimer);
	}
	else
	{
		UINT MapID = Room->MapID;
		if (MapID < 100) //随机
		{
			//MapID = (UINT)(rand() % (300 - 104 + 1) + 104);
			MapID = GetRandMap(MapID);
			//MapID = 114; //道具练习场
		}

		Map* pMap = GetMap(MapID);
		if (!pMap)
		{
#ifndef ZingSpeed
			//ResponseStartGame(Client, "未配置此地图!稍后尝试兼容模式...");
			printf("请配置 MapID:%d\n", MapID);
			//Sleep(1);
			fflush(stdout);
#else
			//ResponseStartGame(Client, "未配置此地图!");
			printf("请配置 MapID:%d\n", MapID);
			return;
#endif
		}

		for (char i = 0; i < 6; i++)
		{
			ClientNode* RoomClient = Room->Player[i];
			if (RoomClient)
			{
				//RoomClient->AutoLeave = 0;
				RoomClient->GameID = 2;
				RoomClient->IsReady = FALSE;
				RoomClient->IsFinish = FALSE;
				if (pMap)
				{
					RoomClient->MapCompatibilityMode = false;
					RoomClient->EndCheckPoint = pMap->End;
					RoomClient->TotalRound = pMap->Round;
					RoomClient->Loop = pMap->Loop;
				}
				else
				{
					RoomClient->MapCompatibilityMode = true;
					RoomClient->EndCheckPoint = 0;
					RoomClient->TotalRound = 1;
					RoomClient->Loop = false;
				}
				RoomClient->MapID = MapID;
				RoomClient->FinishTime = 0;
				RoomClient->Round = 0;
				RoomClient->PassedCheckPoint = 0;
				//NotifyClientUpdatePlayerID(RoomClient);
				if (RoomClient->GlobalStone == 1)
				{
					NotifyUpdateKartSkillStoneInfo2(RoomClient, RoomClient->KartID);
				}
				if (Room->ChatRoomType == 6)
				{
					LeaveOutdoor(RoomClient);//离开3d房休闲区防止卡起步
				}
				NotifyGameBegin(RoomClient, Room->Player);
				//发送kartphys之前等待所有人准备 同步跳舞动作 跳舞动作必须一样 否则卡起步
				
				//NotifyKartPhysParam(RoomClient, Room->Player);
				//NotifyOtherKartStoneInfo(RoomClient);
				
			}
		}
		CreateRoomTimer(Room, 3000, OnPrepareTest);//验证准备状态
	

	}
	

}
void ResponseStartGame(ClientNode* Client, const char* Reason)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, -1); //ResultID

	len = strlen(Reason);
	Write8(p, (BYTE)len); //ReasonLen
	memcpy(p, Reason, len);
	p += len;

	len = p - buf;
	SendToClient(Client, 110, buf, len, Client->RoomID, FE_ROOM, Client->ConnID, Response);
}


void RequestChangeMap(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	UINT NewMapID = Read32(Body);
	//printf("mapid:%d\n", NewMapID);
	
	/*
m_iMapSubID
	*/
	char Season = -1;
	char Timeslot = -1;
	char Weather = -1;
	{
		BYTE* pSTDynamicInfo = Body;
		USHORT len = Read16(pSTDynamicInfo);

		Season = Read8(pSTDynamicInfo);
		Timeslot = Read8(pSTDynamicInfo);
		Weather = Read8(pSTDynamicInfo);

		Body += len;
	}

	RoomNode* Room = GetRoom(Client->RoomID);
	if (!Room)
	{
		return;
	}
	Room->MapID = NewMapID;
	Room->STDynamicInfo.Season = Season;
	Room->STDynamicInfo.Timeslot = Timeslot;
	Room->STDynamicInfo.Weather = Weather;

	ResponseChangeMap(Client, Room);

	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			if (RoomClient != Client)
			{
				NotifyChangeMap(RoomClient, Client->Uin, Room);
			}
		}
	}


}
void ResponseChangeMap(ClientNode* Client, RoomNode* Room)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID
	Write32(p, Room->MapID); //NewMapID
	Write8(p, 0); //ReasonLen
	Write8(p, 0); //UnLockMapCondDescNum
	//m_astUnLockMapCondDesc[].m_bDescLen

	{ //STDynamicInfo
		BYTE* pSTDynamicInfo = p;
		Write16(pSTDynamicInfo, 0); //len

		Write8(pSTDynamicInfo, Room->STDynamicInfo.Season);
		Write8(pSTDynamicInfo, Room->STDynamicInfo.Timeslot);
		Write8(pSTDynamicInfo, Room->STDynamicInfo.Weather);

		len = pSTDynamicInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write32(p, 0); //PreKnowMapID
	Write32(p, 0); //MapSubID
#ifndef ZingSpeed
	Write8(p, 0); //FirstlyTipMap
#endif

	len = p - buf;
	SendToClient(Client, 121, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Response);
}
void NotifyChangeMap(ClientNode* Client, UINT Uin, RoomNode* Room)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write32(p, Uin); //Uin
	Write32(p, Room->MapID); //NewMapID

	{ //STDynamicInfo
		BYTE* pSTDynamicInfo = p;
		Write16(pSTDynamicInfo, 0); //len

		Write8(pSTDynamicInfo, Room->STDynamicInfo.Season);
		Write8(pSTDynamicInfo, Room->STDynamicInfo.Timeslot);
		Write8(pSTDynamicInfo, Room->STDynamicInfo.Weather);

		len = pSTDynamicInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write32(p, 0); //PreKnowMapID
	Write32(p, 0); //MapSubID
#ifndef ZingSpeed
	Write8(p, 0); //FirstlyTipMap
#endif

	len = p - buf;
	SendToClient(Client, 520, buf, len, Client->RoomID, FE_ROOM, Client->ConnID, Notify);
}

void NotifyChangeSeatState(ClientNode* Client,char SeatID,char SeatState)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write8(p, SeatID); //SeatID
	Write8(p, SeatState); //SeatState

	len = p - buf;
	SendToClient(Client, 502, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}
void RequestChangeSeatState(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	short RoomID = Read16(Body);
	BYTE SeatID = Read8(Body);
	BYTE SeatState = Read8(Body);//0关闭 1开放

	RoomNode* Room = GetRoom(RoomID);
	if (!Room)
	{
		return;
	}
	if (Client->ConnID != Room->RoomOwnerID)
	{
		return;
	}
	if (SeatState == 1)
	{
		Room->SeatState[SeatID] = 1;
		Room->SeatNum++;
	}
	else
	{
		Room->SeatState[SeatID] = 0;
		Room->SeatNum--;
	}
	ResponseChangeSeatState(Client, SeatID, SeatState);

	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			if (RoomClient!= Client)
			{
				NotifyChangeSeatState(RoomClient, SeatID, SeatState);
			}
		}
	}

}
void ResponseChangeSeatState(ClientNode* Client, BYTE SeatID, BYTE SeatState)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID

	Write8(p, SeatID);
	Write8(p, SeatState);

	Write8(p, 0); //ReasonLen

	len = p - buf;
	SendToClient(Client, 107, buf, len, Client->RoomID, FE_ROOM, Client->ConnID, Response);
}

void NotifyKickFromRoom(ClientNode* Client,UINT Uin,USHORT RoomID)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, RoomID); //RoomID
	Write32(p, Uin); //DstUin
	Write16(p, 0); //ReasonID
	Write8(p, 0); //ReasonLen
	Write16(p, 0); //BaseGameMode

	len = p - buf;
	SendToClient(Client, 503, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}
void RequestKickFromRoom(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	UINT DstUin = Read32(Body);
	BYTE KickReason = Read8(Body);
	
	RoomNode* Room = GetRoom(Client->RoomID);
	if (!Room)
	{
		return;
	}
	if (Client->ConnID != Room->RoomOwnerID)
	{
		return;
	}
	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			if (RoomClient->Uin == DstUin)
			{
				//if (RoomClient->OBState == 1)
				//{
				//	ResponseStartGame(Client, "无法踢出观战者!");
				//	return;
				//}
				ResponseKickFromRoom(Client, DstUin);//踢出房间
				NotifyKickFromRoom(RoomClient, DstUin,Room->ID);
				//LeaveRoom(RoomClient, 0);
				//LeaveOutdoor(RoomClient);
				if (Room->ChatRoomType == 0)
				{
					ResponseStartGame(RoomClient, "你已被踢出房间!");
				}
				
			}
		}
	}
}
void ResponseKickFromRoom(ClientNode* Client, UINT DstUin)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID

	Write32(p, DstUin);

	Write8(p, 0); //ReasonLen

	len = p - buf;
	SendToClient(Client, 108, buf, len, Client->RoomID, FE_ROOM, Client->ConnID, Response);
}


void NotifyChangeReadyState(ClientNode* Client, UINT Uin, bool State)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write32(p, Uin);
	Write8(p, State);

	len = p - buf;
	SendToClient(Client, 504, buf, len, Client->RoomID, FE_ROOM, Client->ConnID, Notify);
}
void RequestChangeReadyState(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	bool ReadyState = Read8(Body);//准备是0 取消准备是1
	
	ResponseChangeReadyState(Client, ReadyState);
	RoomNode* Room = GetRoom(Client->RoomID);
	if (!Room)
	{
		return;
	}
	if (ReadyState == 0)
	{
		Client->ReadyState = 0;
	}
	else if(ReadyState == 1)
	{
		Client->ReadyState = 1;
	}
	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			if (RoomClient != Client)
			{
				NotifyChangeReadyState(RoomClient, Client->Uin, ReadyState);
			}
		}
	}
}
void ResponseChangeReadyState(ClientNode* Client, bool ReadyState)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID

	Write8(p, ReadyState);

	Write8(p, 0); //ReasonLen


	len = p - buf;
	SendToClient(Client, 109, buf, len, Client->RoomID, FE_ROOM, Client->ConnID, Response);
}


void RequestTalk(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	//请求说话
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	BYTE Type = Read8(Body);
	BYTE ClientUseFlag = Read8(Body);
	UINT DestPlayerUin = Read32(Body);

	USHORT ContentLength = Read16(Body);
	char* Content = (char*)Body;
	Body += ContentLength;
	//printf("Content:%s\n", Content);
	BYTE BugletType = Read8(Body);
	BYTE ReserveFlag = Read8(Body);

	if (Type == 1 && ClientUseFlag == 0 && stricmp(Content, "g") == 0)
	{
		
		//手动发送GameOver消息
		/*if (Client->TaskID == 0xFFFE)
		{ //极限挑战强制退出
			Client->IsFinish = TRUE;
			HANDLE over = CreateThread(NULL, 0, OnSingleOver, Client, 0, NULL);
			if (over)
			{
				CloseHandle(over);
			}
		}*/
		if (Client->TaskID == 0 || Client->TaskID == 0xFFFD || Client->TaskID == 0xFFFC || Client->TaskID == 0xFFFB)
		{//排位 边境 竞速快速退出
			SendToClient(Client, 514, (const BYTE*)"\x00\x00\x00\x00", 4, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
			Client->TaskID = 0;
			Client->IsFinish = FALSE;
			Client->IsReady == FALSE;
			RoomNode* Room = GetRoom(Client->RoomID);
			if (Room)
			{
				if (Room->CurrentPlayerNum == 1 && Client->TaskID == 0)
				{//单人退出直接到房间
					if (Room->ChatRoomType == 6)
					{
						//进入3d房间
						ResponseCreateRoom(Client, Room, 6);
						RequestEnter3DRoom(Client);
						//NotifyChangeRoomOwner(Client, Room);
					}
					if (Room->Timer)
					{
						if (DeleteTimerQueueTimer(TimerQueue, Room->Timer, INVALID_HANDLE_VALUE))
						{
							Room->Timer = NULL;
						}
					}
					Room->Callback = NULL;
				}
				else
				{//多人退出到大厅
					if (Room->ChatRoomType == 6)
					{
						//退出3d房间
						ResponseCreateRoom(Client, Room, 0);
					}
					//LeaveOutdoor(Client);
					LeaveRoom(Client, 0);
				}
			}
			LeaveBorderRoom(Client, 0);
		}
		return;
	}
	//ResponseTalk(Client, Type, ClientUseFlag, DestPlayerUin);
	else if (Type == 3)
	{
		//喇叭功能
		NotifyBugletTalk(Client, Content, ContentLength,BugletType);
		return;
	}
	//printf("Type:%d, ClientUseFlag:%d. DestPlayerUin:%d BugletType:%d\n", Type, ClientUseFlag, DestPlayerUin, BugletType);
    //房间内说话Type:4, ClientUseFlag : 2
	//对局内说话Type:1, ClientUseFlag:0
	else if (Type == 1 || Type == 4)
	{
		RoomNode* Room = GetRoom(Client->RoomID);
		if (!Room)
		{
			return;
		}
		/*强制观战模式
		if (Type == 1 && strstr(Content, "ob 1") || strstr(Content, "ob 0"))
		{
			char* temp = Content;
			temp += 3;
			int obstate=atoi(temp);
			if (obstate == 1)
			{
				Client->OBState = 1;
				SendToClient(Client, 134, (BYTE*)"\x00\x00\x01\x00", 4, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
			}
			else
			{
				Client->OBState = 0;
				SendToClient(Client, 134, (BYTE*)"\x00\x00\x00\x00", 4, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
			}
			for (char i = 0; i < 6; i++)
			{
				ClientNode* RoomClient = Room->Player[i];
				if (RoomClient)
				{
					BYTE obbuf[5];
					BYTE* pobbuf = obbuf;
					Write32(pobbuf, Client->Uin);
					Write8(pobbuf, Client->OBState);
					SendToClient(RoomClient, 609, obbuf, 5, RoomClient->ConnID, FE_PLAYER, RoomClient->ConnID, Notify);
				}
			}
			if (Client->OBState == 1)
			{
				Content = const_cast <char*>("开启观战模式");
			}
			else
			{
				Content = const_cast <char*>("关闭观战模式");
			}
			ContentLength = 12;
		}*/
		if (Type == 1 && strstr(Content, "map"))
		{
			//自定义切换地图
			char* mapid = Content;
			mapid += 4;
			Room->MapID = atoi(mapid);
			for (char i = 0; i < 6; i++)
			{
				ClientNode* RoomClient = Room->Player[i];
				if (RoomClient)
				{
					NotifyChangeMap(RoomClient, RoomClient->Uin, Room);
				}
			}
			return;
		}
		for (char i = 0; i < 6; i++)
		{
			ClientNode* RoomClient = Room->Player[i];
			if (RoomClient)
			{
#ifdef ZingSpeed
				if (RoomClient == Client)
				{
					continue;
		}
#endif
				NotifyTalk(RoomClient, Client, Type, ClientUseFlag, DestPlayerUin, ContentLength, Content);
			}
		}
	}
}
void ResponseTalk(ClientNode* Client, BYTE Type, BYTE ClientUseFlag, UINT DestPlayerUin)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID

	Write8(p, Type);
	Write8(p, ClientUseFlag);
	Write32(p, DestPlayerUin);

	Write8(p, 0); //ReasonLen
	Write8(p, 0); //BugletType
	Write8(p, 0); //ReserveFlag
	Write8(p, 0); //ReserveData
#ifndef ZingSpeed
	Write8(p, 0); //TalkSpecialType
	Write32(p, 0); //Seq
#endif

	len = p - buf;
	SendToClient(Client, 111, buf, len, Client->RoomID, FE_ROOM, Client->ConnID, Response);
}
void NotifyTalk(ClientNode* Client, ClientNode* RoomClient, BYTE Type, BYTE ClientUseFlag, UINT DestPlayerUin, short ContentLength, const char* Content)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write32(p, RoomClient->Uin);

	memset(p, 0, 17);
	
	memcpy(p, RoomClient->NickName, 17);
	
	p += 17;

	Write8(p, 0); //Gender

	Write8(p, Type);
	Write8(p, ClientUseFlag);
	Write32(p, DestPlayerUin);

	Write16(p, ContentLength);
	memcpy(p, Content, ContentLength);
	p += ContentLength;


	Write8(p, 0); //BugletType
	Write16(p, 0); //Identify
	Write16(p, 0x106); //VipFlag
	Write8(p, 0); //CanReport


	{ //TalkerInfo
		BYTE* pTalkerInfo = p;
		Write16(pTalkerInfo, 0); //len

		Write32(pTalkerInfo, 0); //Exp

		{ //NobleInfo
			BYTE* pNobleInfo = pTalkerInfo;
			Write16(pNobleInfo, 0); //len

			Write32(pNobleInfo, Client->Uin); //NobleID
			Write8(pNobleInfo, 6); //NobleLevel
			Write32(pNobleInfo, 1); //NoblePoint
			Write32(pNobleInfo, 30); //NobleLeftDays

			len = pNobleInfo - pTalkerInfo;
			Set16(pTalkerInfo, (WORD)len);
			pTalkerInfo += len;
		}
#ifndef ZingSpeed
		{ //GuildVipBaseInfo
			BYTE* pGuildVipBaseInfo = pTalkerInfo;
			Write16(pGuildVipBaseInfo, 0); //len

			Write8(pGuildVipBaseInfo, 6); //GuildVipLevel
			Write32(pGuildVipBaseInfo, 1); //GuildVipPoint

			len = pGuildVipBaseInfo - pTalkerInfo;
			Set16(pTalkerInfo, (WORD)len);
			pTalkerInfo += len;
		}
		Write32(pTalkerInfo, 0); //GuildId

		Write8(pTalkerInfo, 1); //HasLoverVip
		
		for (size_t i = 0; i < 1; i++)
		{ //LoverVipInfo
			BYTE* pLoverVipInfo = pTalkerInfo;
			Write16(pLoverVipInfo, 0); //len

			Write8(pLoverVipInfo, 6); //LoverVipLevel
			Write32(pLoverVipInfo, 0); //LoverVipPoint
			Write8(pLoverVipInfo, 0); //GrowRate

			len = pLoverVipInfo - pTalkerInfo;
			Set16(pTalkerInfo, (WORD)len);
			pTalkerInfo += len;
		}
		
		Write8(pTalkerInfo, 6); //GardenLevel
		Write8(pTalkerInfo, 6); //ConsumeVipLevel
		{ //EmperorInfo
			BYTE* pEmperorInfo = pTalkerInfo;
			Write16(pEmperorInfo, 0); //len

			Write8(pEmperorInfo, 6); //EmperorLevel
			Write32(pEmperorInfo, 0); //EmperorPoint
			Write32(pEmperorInfo, 0); //EmperorLeftDays
			Write8(pEmperorInfo, 0); //EmperorGrowRate

			len = pEmperorInfo - pTalkerInfo;
			Set16(pTalkerInfo, (WORD)len);
			pTalkerInfo += len;
		}
		Write32(pTalkerInfo, 0); //HelperLev
#endif

		len = pTalkerInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	
	Write8(p, 0); //ReserveFlag
	Write32(p, 0); //ReserveData
#ifndef ZingSpeed
	memset(p, 0, 18); //Contentid[]
	p+=18;
#endif
	Write8(p, 0); //transBufType
	Write16(p, 0); //transBufLen
#ifndef ZingSpeed
	Write8(p, 0); //MsgSource
	Write16(p, 0); //DstNickNameLength
	Write32(p, 0); //Seq
#endif

	len = p - buf;
	SendToClient(Client, 505, buf, len, Client->RoomID, FE_ROOM, Client->ConnID, Notify);
}
void NotifyChangeRoomOwner(ClientNode* Client, RoomNode* Room)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, Room->ID); //RoomID
	Write16(p, Room->RoomOwnerID); //NewRoomOwnerID
	Write8(p, 0); //HasFBInfo
	for (size_t i = 0; i < 0; i++)
	{ //FBInfo
		BYTE* pFBInfo = p;
		Write16(pFBInfo, 0); //len

		Write8(pFBInfo, 0); //AvailableLev
		Write8(pFBInfo, 0); //Lev
		Write8(pFBInfo, 0); //SubLev
		Write32(pFBInfo, 0); //BossID
		Write8(pFBInfo, 0); //FBSeason

		len = pFBInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write16(p, 0); //OriRoomOwnerID
	Write8(p, 0); //ChangeType
	Write16(p, 0); //RoomType

	len = p - buf;
	SendToClient(Client, 524, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}
void ResponseChangeRoomOwner(ClientNode* Client, RoomNode* Room)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	Write32(p, Room->RoomOwnerID); //NewOwner
	Write16(p, 0); //ResultID
	Write8(p, 0); //ReasonLen

	len = p - buf;
	SendToClient(Client, 713, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}
void RequestChangeRoomOwner(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body; WORD len;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	UINT NewOwner = Read32(p);

}