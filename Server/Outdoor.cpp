#include "Outdoor.h"

#include <stdio.h>
#include <string>
#include <time.h>



constexpr int MAX_CHAIR_NUM = 200;
constexpr int MAX_NUM_IN_EACHCHAIR = 2;

struct MoveInfo
{
	UINT Uin;
	char WalkStatue;
	int Posion[3];
	int Ori[9];
	UINT AttachUin;
	int WalkExtState;
};


ChatRoomNode ChatRooms[ChatRoomNum];
void InitChatRoom()
{
	ChatRooms[0].ID = 0;
	ChatRooms[0].Name = "琳琅湾";
	ChatRooms[0].CurrPlayerNum = 0;
	ChatRooms[0].MaxPlayerNum = 99;
	ChatRooms[0].RoomType = 1;//RoomType必须一致才能进入房间
	ChatRooms[0].SceneID = 109;
	ChatRooms[0].x = 0;
	ChatRooms[0].y = -50000;
	ChatRooms[0].z = 0;
	for (size_t i = 0; i < 99; i++)
	{
		ChatRooms[0].Player[i] = NULL;
	}

	ChatRooms[1].ID = 1;
	ChatRooms[1].Name = "琳琅镇";
	ChatRooms[1].CurrPlayerNum = 0;
	ChatRooms[1].MaxPlayerNum = 99;
	ChatRooms[1].RoomType = 2;
	ChatRooms[1].SceneID = 25;
	ChatRooms[1].x = 0;
	ChatRooms[1].y = 0;
	ChatRooms[1].z = 0;
	for (size_t i = 0; i < 99; i++)
	{
		ChatRooms[1].Player[i] = NULL;
	}

	ChatRooms[2].ID = 2;
	ChatRooms[2].Name = "单身派对";
	ChatRooms[2].CurrPlayerNum = 0;
	ChatRooms[2].MaxPlayerNum = 99;
	ChatRooms[2].RoomType = 3;
	ChatRooms[2].SceneID = 109;
	ChatRooms[2].x = 0;
	ChatRooms[2].y = -40000;
	ChatRooms[2].z = 0;
	for (size_t i = 0; i < 99; i++)
	{
		ChatRooms[2].Player[i] = NULL;
	}

	ChatRooms[3].ID = 3;
	ChatRooms[3].Name = "皇族休闲区";
	ChatRooms[3].CurrPlayerNum = 0;
	ChatRooms[3].MaxPlayerNum = 99;
	ChatRooms[3].RoomType = 4;
	ChatRooms[3].SceneID = 136;
	ChatRooms[3].x = 10000;
	ChatRooms[3].y = 0;
	ChatRooms[3].z = 0;
	for (size_t i = 0; i < 99; i++)
	{
		ChatRooms[3].Player[i] = NULL;
	}

	ChatRooms[4].ID = 4;
	ChatRooms[4].Name = "中国城";
	ChatRooms[4].CurrPlayerNum = 0;
	ChatRooms[4].MaxPlayerNum = 99;
	ChatRooms[4].RoomType = 3;
	ChatRooms[4].SceneID = 4;
	ChatRooms[4].x = 33071;
	ChatRooms[4].y = -45773;
	ChatRooms[4].z = 4368;
	for (size_t i = 0; i < 99; i++)
	{
		ChatRooms[4].Player[i] = NULL;
	}

	ChatRooms[5].ID = 0x87;
	ChatRooms[5].Name = "3DRoom";
	ChatRooms[5].CurrPlayerNum = 0;
	ChatRooms[5].MaxPlayerNum = 99;
	ChatRooms[5].RoomType = 0;
	ChatRooms[5].SceneID = 0x190;
	ChatRooms[5].x = 0xfffff172;
	ChatRooms[5].y = 0xffffffaf;
	ChatRooms[5].z = 0x9;
	for (size_t i = 0; i < 99; i++)
	{
		ChatRooms[5].Player[i] = NULL;
	}

}



void NotifyNPCInfo(ClientNode* Client);
void NotifyChairInfo(ClientNode* Client);
void ResponseEnterOutdoor(ClientNode* Client, short SceneID, int x, int y, int z);
void NotifyGuildRoomMoreInfo(ClientNode* Client);
void ResponseChangeChairState(ClientNode* Client, BYTE ChangeState, int ChairIndx, BYTE SeatIndx);
void NotifyEnterOutdoor(ClientNode* Client, ChatRoomNode* ChatRoom, ClientNode* RoomClient, char SeatID);

ChatRoomNode* GetChatRoom(short ChatRoomID)
{
	ChatRoomNode* ChatRoom = NULL;
	for (size_t i = 0; i < ChatRoomNum; i++)
	{
		if (ChatRooms[i].ID == ChatRoomID)
		{
			ChatRoom = &ChatRooms[i];
			break;
		}
	}
	return ChatRoom;
}


void RequestEnter3DRoom(ClientNode* Client)
{

	//3D房间只能通过ResponseCreateRoom方法进再通过NotifyChangeRoomOwner转房主 RequestEnterRoom进不显示备战
	//ResponseCreateRoom(RoomClient, Room, 6);
	//RequestEnter3DRoom(RoomClient);
	// NotifyChangeRoomOwner
	ChatRoomNode* ChatRoom = GetChatRoom(0x87);
	if (!ChatRoom)
	{
		return;
	}


	for (char i = 0; i < 99; i++)
	{
		if (!ChatRoom->Player[i])
		{
			Client->ChatRoomID = 0x87;
			ChatRoom->Player[i] = Client;
			ChatRoom->CurrPlayerNum++;

			
			int x = ChatRoom->x;
			int y = ChatRoom->y;
			int z = ChatRoom->z;
			//printf("SceneID:%d\n", SceneID);
			//fflush(stdout);
			NotifyNPCInfo(Client);
			ResponseEnterOutdoor(Client, ChatRoom->SceneID, x, y, z);
			NotifyGuildRoomMoreInfo(Client);
			NotifyChairInfo(Client);

			//通知其它玩家
			for (char i2 = 0; i2 < 99; i2++)
			{
				ClientNode* RoomClient = ChatRoom->Player[i2];
				if (RoomClient)
				{
					if (RoomClient != Client)
					{
						NotifyEnterOutdoor(RoomClient, ChatRoom, Client, i);//通知其他人看到自己
						NotifyEnterOutdoor(Client, ChatRoom, RoomClient, i2);//通知自己看到其他人
					}
				}
			}

			break;
		}
	}
}
void RequestEnterOutdoor(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	short SceneID = Read16(Body);
	short ChatRoomID = Read16(Body);
	short NPCCfgVer = Read16(Body);

	LeaveOutdoor(Client);//出房间
	LeaveRoom(Client, 0);
	LeaveBorderRoom(Client, 0);
	//printf("SceneID:%d, ChatRoomID:%d\n",SceneID, ChatRoomID);

	//fflush(stdout);
	ChatRoomNode* ChatRoom = GetChatRoom(ChatRoomID);
	if (!ChatRoom)
	{
		return;
	}
	

	for (char i = 0; i < 99; i++)
	{
		if (!ChatRoom->Player[i])
		{
			Client->ChatRoomID = ChatRoomID;
			ChatRoom->Player[i] = Client;
			ChatRoom->CurrPlayerNum++;
			
			SceneID = ChatRoom->SceneID;
			int x = ChatRoom->x;
			int y = ChatRoom->y;
			int z = ChatRoom->z;
			//printf("SceneID:%d\n", SceneID);
			//fflush(stdout);
			NotifyNPCInfo(Client);
			ResponseEnterOutdoor(Client, SceneID, x, y, z);
			NotifyGuildRoomMoreInfo(Client);
			NotifyChairInfo(Client);

			//通知其它玩家
			for (char i2 = 0; i2 < 99; i2++)
			{
				ClientNode* RoomClient = ChatRoom->Player[i2];
				if (RoomClient)
				{
					if (RoomClient != Client)
					{
						NotifyEnterOutdoor(RoomClient, ChatRoom, Client, i);//通知其他人看到自己
						NotifyEnterOutdoor(Client, ChatRoom, RoomClient, i2);//通知自己看到其他人
					}
				}
			}

			break;
		}
	}
}
void ResponseEnterOutdoor(ClientNode* Client, short SceneID, int x, int y, int z)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;


	Write16(p, Client->ChatRoomID); //ChatRoomID
	Write16(p, SceneID); //SceneID

	{ //HeroMoveInfo
		BYTE* pHeroMoveInfo = p;
		Write16(pHeroMoveInfo, 0); //len

		Write32(pHeroMoveInfo, 0); //Uin
		Write8(pHeroMoveInfo, 0); //WalkStatue

		Write32(pHeroMoveInfo, x); //Posion[3]
		Write32(pHeroMoveInfo, y);
		Write32(pHeroMoveInfo, z);

		Write32(pHeroMoveInfo, 1000); //Ori[9]
		Write32(pHeroMoveInfo, 0);
		Write32(pHeroMoveInfo, 0);
		Write32(pHeroMoveInfo, 0);
		Write32(pHeroMoveInfo, 1000);
		Write32(pHeroMoveInfo, 0);
		Write32(pHeroMoveInfo, 0);
		Write32(pHeroMoveInfo, 0);
		Write32(pHeroMoveInfo, 1000);

		Write32(pHeroMoveInfo, 0); //AttachUin
		Write32(pHeroMoveInfo, 0); //WalkExtState

		len = pHeroMoveInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write16(p, 0); //ResultID

	const char RoomName[] = "Name";
	len = strlen(RoomName);
	Write8(p, (BYTE)len); //ReasonLen
	memcpy(p, RoomName, len);
	p += len;


	Write16(p, 0); //HeroCount

	
	Write16(p, 0); //RelationHeroCount
	

	Write16(p, 0); //KartNum
	

	Write16(p, 0); //HammerCount
	/*
m_astEquipedHammer[].m_iEquipedHammerID
	*/

	Write16(p, 0); //StealPigCount
	/*
m_astStealPig[].m_cStatus
m_astStealPig[].m_cPigPos
m_astStealPig[].m_iItemID
	*/
	Write16(p, 0); //MaxHeroNumInRoom


	len = p - buf;
	SendToClient(Client, 352, buf, len, Client->ChatRoomID, FE_OUTDOORSVRD, Client->ConnID, Response);
}

void NotifyEnterOutdoor(ClientNode* Client, ChatRoomNode* ChatRoom, ClientNode* RoomClient, char SeatID)
{
	
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, ChatRoom->ID); //ChatRoomID
	Write16(p, ChatRoom->SceneID); //SceneID
	Write32(p, (DWORD)time(nullptr)); //Time


	{ //HeroInfo
		
		BYTE* pHeroInfo = p;
		Write16(pHeroInfo, 0); //len

		{ //HeroMoveInfo
			BYTE* pHeroMoveInfo = pHeroInfo;
			Write16(pHeroMoveInfo, 0); //len

			Write32(pHeroMoveInfo, RoomClient->Uin); //Uin
			Write8(pHeroMoveInfo, 0); //WalkStatue

			Write32(pHeroMoveInfo, ChatRoom->x); //Posion[3]
			Write32(pHeroMoveInfo, ChatRoom->y);
			Write32(pHeroMoveInfo, ChatRoom->z);

			Write32(pHeroMoveInfo, 1000); //Ori[9]
			Write32(pHeroMoveInfo, 0);
			Write32(pHeroMoveInfo, 0);
			Write32(pHeroMoveInfo, 0);
			Write32(pHeroMoveInfo, 1000);
			Write32(pHeroMoveInfo, 0);
			Write32(pHeroMoveInfo, 0);
			Write32(pHeroMoveInfo, 0);
			Write32(pHeroMoveInfo, 1000);

			Write32(pHeroMoveInfo, 0); //AttachUin
			Write32(pHeroMoveInfo, 0); //WalkExtState

			len = pHeroMoveInfo - pHeroInfo;
			Set16(pHeroInfo, (WORD)len);
			pHeroInfo += len;
		}

		Write32(pHeroInfo, 0); //NextPoint
		Write16(pHeroInfo, 0); //PathLen
		//m_astHeroInfo[].m_aiPath[]

		WriteVisbleInfo(RoomClient,pHeroInfo, RoomClient->Uin, SeatID, RoomClient->ConnID); //HeroVisbleInfo


		Write16(pHeroInfo, 0); //HeroEnterDelayTime


		len = pHeroInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	


	{ //PlayerRelationInfo
		BYTE* pPlayerRelationInfo = p;
		Write16(pPlayerRelationInfo, 0); //len

		Write32(pPlayerRelationInfo, RoomClient->Uin); //SrcUin
		Write32(pPlayerRelationInfo, 0); //RelationFlag
		Write32(pPlayerRelationInfo, 0); //RelationUin

		memset(pPlayerRelationInfo, 0, MaxNickName); //RelationNickname[]
		strcpy_s((char*)pPlayerRelationInfo, MaxNickName, "test");
		pPlayerRelationInfo += MaxNickName;

		Write32(pPlayerRelationInfo, 0); //EngageTime
		Write32(pPlayerRelationInfo, 0); //NextCanBookingTimeLimit
		Write32(pPlayerRelationInfo, 0); //BeginHoneyMoonTime
		Write32(pPlayerRelationInfo, 0); //EndHoneyMoonTime
		
		Write8(pPlayerRelationInfo, 0); //EngageFlag


		len = pPlayerRelationInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write16(p, 0); //KartNum
	/*
m_astKartRefitInfo[].m_uiUin
m_astKartRefitInfo[].m_iKartId
m_astKartRefitInfo[].m_iRefitCout
m_astKartRefitInfo[].m_shMaxFlags
m_astKartRefitInfo[].m_shWWeight
m_astKartRefitInfo[].m_shSpeedWeight
m_astKartRefitInfo[].m_shJetWeight
m_astKartRefitInfo[].m_shSJetWeight
m_astKartRefitInfo[].m_shAccuWeight
m_astKartRefitInfo[].m_iShapeRefitCount
m_astKartRefitInfo[].m_iKartHeadRefitItemID
m_astKartRefitInfo[].m_iKartTailRefitItemID
m_astKartRefitInfo[].m_iKartFlankRefitItemID
m_astKartRefitInfo[].m_iKartTireRefitItemID
	*/

	{ //StealPig
		BYTE* pStealPig = p;
		Write16(pStealPig, 0); //len


		Write8(pStealPig, 0); //Status
		Write8(pStealPig, 0); //PigPos
		Write32(pStealPig, 0); //ItemID


		len = pStealPig - p;
		Set16(p, (WORD)len);
		p += len;
	}


	len = p - buf;
	SendToClient(Client, 852, buf, len, ChatRoom->ID, FE_OUTDOORSVRD, Client->ConnID, Notify);
}

void NotifyNPCInfo(ClientNode* Client)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 4); //NPCCfgVer
	Write8(p, 0); //NPCNum


	len = p - buf;
	SendToClient(Client, 863, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void NotifyGuildRoomMoreInfo(ClientNode* Client)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write32(p, 0); //GuildID
	Write8(p, 0); //GuildRoomID

	BYTE* pHeroCount = p;
	Write16(p, 0); //HeroCount
	/*ChatRoomNode* ChatRoom = GetChatRoom(Client->ChatRoomID);
	if (!ChatRoom)
	{
		return;
	}
	short HeroCount = 0;
	for (char i = 0; i < 99; i++)
	{
		if (ChatRoom->Player[i] && ChatRoom->Player[i] != Client)
		{ //HeroInfo
			HeroCount++;

			BYTE* pHeroInfo = p;
			Write16(pHeroInfo, 0); //len

			{ //HeroMoveInfo
				BYTE* pHeroMoveInfo = pHeroInfo;
				Write16(pHeroMoveInfo, 0); //len

				Write32(pHeroMoveInfo, ChatRoom->Player[i]->Uin); //Uin
				Write8(pHeroMoveInfo, 0); //WalkStatue

				Write32(pHeroMoveInfo, ChatRoom->x); //Posion[3]
				Write32(pHeroMoveInfo, ChatRoom->y);
				Write32(pHeroMoveInfo, ChatRoom->z);

				Write32(pHeroMoveInfo, 1000); //Ori[9]
				Write32(pHeroMoveInfo, 0);
				Write32(pHeroMoveInfo, 0);
				Write32(pHeroMoveInfo, 0);
				Write32(pHeroMoveInfo, 1000);
				Write32(pHeroMoveInfo, 0);
				Write32(pHeroMoveInfo, 0);
				Write32(pHeroMoveInfo, 0);
				Write32(pHeroMoveInfo, 1000);

				Write32(pHeroMoveInfo, 0); //AttachUin
				Write32(pHeroMoveInfo, 0); //WalkExtState

				len = pHeroMoveInfo - pHeroInfo;
				Set16(pHeroInfo, (WORD)len);
				pHeroInfo += len;
			}

			Write32(pHeroInfo, 0); //NextPoint
			Write16(pHeroInfo, 0); //PathLen
			//m_astHeroInfo[].m_aiPath[]

			WriteVisbleInfo(ChatRoom->Player[i],pHeroInfo, ChatRoom->Player[i]->Uin, i, ChatRoom->Player[i]->ConnID); //HeroVisbleInfo
			
			Write16(pHeroInfo, 0); //HeroEnterDelayTime


			len = pHeroInfo - p;
			Set16(p, (WORD)len);
			p += len;
		}
	}
	Set16(pHeroCount, HeroCount);
	*/

	Write16(p, 0); //RelationHeroCount
	/*
m_astPlayerRelationInfo[].m_uiSrcUin
m_astPlayerRelationInfo[].m_iRelationFlag
m_astPlayerRelationInfo[].m_uiRelationUin
m_astPlayerRelationInfo[].m_szRelationNickname[]:
m_astPlayerRelationInfo[].m_u32EngageTime
m_astPlayerRelationInfo[].m_uiNextCanBookingTimeLimit
m_astPlayerRelationInfo[].m_uiBeginHoneyMoonTime
m_astPlayerRelationInfo[].m_uiEndHoneyMoonTime
m_astPlayerRelationInfo[].m_bEngageFlag
	*/

	Write16(p, 0); //KartNum
	/*
m_astKartRefitInfo[].m_uiUin
m_astKartRefitInfo[].m_iKartId
m_astKartRefitInfo[].m_iRefitCout
m_astKartRefitInfo[].m_shMaxFlags
m_astKartRefitInfo[].m_shWWeight
m_astKartRefitInfo[].m_shSpeedWeight
m_astKartRefitInfo[].m_shJetWeight
m_astKartRefitInfo[].m_shSJetWeight
m_astKartRefitInfo[].m_shAccuWeight
m_astKartRefitInfo[].m_iShapeRefitCount
m_astKartRefitInfo[].m_iKartHeadRefitItemID
m_astKartRefitInfo[].m_iKartTailRefitItemID
m_astKartRefitInfo[].m_iKartFlankRefitItemID
m_astKartRefitInfo[].m_iKartTireRefitItemID
	*/

	Write16(p, 0); //HammerCount
	/*
m_astEquipedHammer[].m_iEquipedHammerID
	*/

	Write16(p, 0); //StealPigCount
	/*
m_astStealPig[].m_cStatus
m_astStealPig[].m_cPigPos
m_astStealPig[].m_iItemID
	*/

	Write8(p, 0); //HaveNext

	Write8(p, 0); //HaveAppellation
	/*
m_astCurAppellation[].m_u8Type
m_astCurAppellation[].m_u8Level
m_astCurAppellation[].m_u8Status
m_astCurAppellation[].m_u8Difficulty
m_astCurAppellation[].m_i32MapId
m_astCurAppellation[].m_u32Value
	*/


	len = p - buf;
	SendToClient(Client, 11019, buf, len, Client->ChatRoomID, FE_OUTDOORSVRD, Client->ConnID, Notify);
}

void NotifyChairInfo(ClientNode* Client)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	for (size_t i = 0; i < MAX_CHAIR_NUM; i++)
	{ //ChairInfo
		BYTE* pChairInfo = p;
		Write16(pChairInfo, 0); //len

		for (size_t i = 0; i < MAX_NUM_IN_EACHCHAIR; i++)
		{ //UinInChair
			Write32(pChairInfo, 0);
		}

		len = pChairInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	len = p - buf;
	SendToClient(Client, 864, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void NotifyChangeChairState(ClientNode* Client,UINT Uin,BYTE ChangeState, int ChairIndx, BYTE SeatIndx)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, ChairIndx); //ChairIndx
	Write8(p, SeatIndx); //SeatIndx
	Write32(p, Uin); //Uin
	Write8(p, ChangeState); //State

	len = p - buf;
	SendToClient(Client, 865, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}
void RequestChangeChairState(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);


	BYTE ChangeState = Read8(Body);
	int ChairIndx = Read32(Body);
	BYTE SeatIndx = Read8(Body);

	ResponseChangeChairState(Client, ChangeState, ChairIndx, SeatIndx);
	ChatRoomNode* ChatRoom = GetChatRoom(Client->ChatRoomID);
	if (!ChatRoom)
	{
		return;
	}
	for (char i2 = 0; i2 < 99; i2++)
	{
		ClientNode* RoomClient = ChatRoom->Player[i2];
		if (RoomClient)
		{
			if (RoomClient != Client)
			{
				NotifyChangeChairState(RoomClient, Client->Uin, ChangeState, ChairIndx, SeatIndx);
			}
		}
	}
}
void ResponseChangeChairState(ClientNode* Client, BYTE ChangeState, int ChairIndx, BYTE SeatIndx)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;


	Write32(p, Client->Uin); //Uin
	Write16(p, 0); //Result

	Write8(p, ChangeState);
	Write32(p, ChairIndx);
	Write8(p, SeatIndx);


	len = p - buf;
	SendToClient(Client, 360, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void LeaveOutdoor(ClientNode* Client)
{
	ChatRoomNode* ChatRoom = GetChatRoom(Client->ChatRoomID);
	if (!ChatRoom)
	{
		return;
	}
	for (char i = 0; i < 99; i++)
	{
		if (ChatRoom->Player[i] == Client)
		{
			ResponseLeaveOutdoor(Client);
			ChatRoom->Player[i] = NULL;
			Client->ChatRoomID = -1;
			ChatRoom->CurrPlayerNum--;

			//通知其它玩家
			for (char i2 = 0; i2 < 99; i2++)
			{
				ClientNode* RoomClient = ChatRoom->Player[i2];
				if (RoomClient)
				{
					if (RoomClient != Client)
					{
						NotifyLeaveOutdoor(RoomClient, Client->Uin);
					}
				}
			}
			break;
		}
	}
}
void NotifyChangeHammerStatus(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, 0); //SrcUin
	Write32(p, 0); //Time
	{ //EquipedHammer
		BYTE* pEquipedHammer = p;
		Write16(pEquipedHammer, 0); //len

		Write32(pEquipedHammer, 0); //EquipedHammerID

		len = pEquipedHammer - p;
		Set16(p, (WORD)len);
		p += len;
	}

	len = p - buf;
	SendToClient(Client, 861, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}
void ResponseChangeHammerStatus(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	{ //EquipedHammer
		BYTE* pEquipedHammer = p;
		Write16(pEquipedHammer, 0); //len

		Write32(pEquipedHammer, 0); //EquipedHammerID

		len = pEquipedHammer - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write8(p, 0); //ReasonLen

	len = p - buf;
	SendToClient(Client, 359, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestChangeHammerStatus(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	//Msg 359 休闲区切换锤子pk
	BYTE* p = Body; WORD len;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	{ //EquipedHammer
		BYTE* pEquipedHammer = p;
		len = Read16(pEquipedHammer);

		int EquipedHammerID = Read32(pEquipedHammer);

		p += len;
	}

}
void RequestLeaveOutdoor(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);
	USHORT Temp1 = Read16(Body);//LeaveType
	USHORT Time2 = Read16(Body);//Room ID
	if (Temp1 == 0)//进入休闲区会自动请求这个消息 需要判断防止异常退出
	{
		LeaveOutdoor(Client);
		LeaveRoom(Client, 0);
		LeaveBorderRoom(Client, 0);
	}
		
}
void ResponseLeaveOutdoor(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	Write8(p, 0); //ReasonLen

	len = p - buf;
	SendToClient(Client, 353, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}
void NotifyLeaveOutdoor(ClientNode* Client, UINT Uin)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Uin); //Uin
	Write32(p, 0); //Time

	len = p - buf;
	SendToClient(Client, 853, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void NotifyHeroMove(ClientNode* Client, BYTE* buf,int len1,int len2);

void RequestHeroMove(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body; WORD len1;
	WORD len2;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	len1=Read16(p);
	len2 = BodyLen - 10;
	/*MoveInfo HeroMoveInfo;
	 { //HeroMoveInfo
		BYTE* pHeroMoveInfo = p;
		len = Read16(pHeroMoveInfo);

		HeroMoveInfo.Uin = Read32(pHeroMoveInfo);
		HeroMoveInfo.WalkStatue = Read8(pHeroMoveInfo);
		for (size_t i = 0; i < 3; i++)
		{
			HeroMoveInfo.Posion[i] = Read32(pHeroMoveInfo);
		}
		for (size_t i = 0; i < 9; i++)
		{
			HeroMoveInfo.Ori[i] = Read32(pHeroMoveInfo);
		}
		HeroMoveInfo.AttachUin = Read32(pHeroMoveInfo);
		HeroMoveInfo.WalkExtState = Read32(pHeroMoveInfo);

		p += len;
	}
	int NextPoint = Read32(p);
	short PathLen = Read16(p);
	//int[] Path[] = Read32(p);
	int CurCellID = Read32(p);
	*/
	

	ChatRoomNode* ChatRoom = GetChatRoom(Client->ChatRoomID);
	if (!ChatRoom)
	{
		return;
	}
	for (char i = 0; i < 99; i++)
	{
		if (ChatRoom->Player[i] && ChatRoom->Player[i] != Client)
		{
			NotifyHeroMove(ChatRoom->Player[i], p,len1,len2);
		}
	}
}
void NotifyHeroMove(ClientNode* Client, BYTE* buf, int len1,int len2)
{
	BYTE buf1[8192]; BYTE* p = buf1; size_t len;
	Write16(p, len1); //len
	memcpy(p, buf, len2);
	len = len2 + 2;
	/* { //HeroMoveInfo
		BYTE* pHeroMoveInfo = p;
		Write16(pHeroMoveInfo, 0); //len

		Write32(pHeroMoveInfo, HeroMoveInfo->Uin);
		Write8(pHeroMoveInfo, HeroMoveInfo->WalkStatue);
		for (size_t i = 0; i < 3; i++)
		{
			Write32(pHeroMoveInfo, HeroMoveInfo->Posion[i]);
		}
		for (size_t i = 0; i < 9; i++)
		{
			Write32(pHeroMoveInfo, HeroMoveInfo->Ori[i]);
		}
		Write32(pHeroMoveInfo, HeroMoveInfo->AttachUin);
		Write32(pHeroMoveInfo, HeroMoveInfo->WalkExtState);

		len = pHeroMoveInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write32(p, 0); //NextPoint
	Write16(p, 0); //PathLen
	//Write32(p, 0); //Path[]
	Write32(p, 0); //Time

	len = p - buf;
	*/
	SendToClient(Client, 851, buf1, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

