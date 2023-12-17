#pragma once
#include "Message.h"


#ifdef ZingSpeed
constexpr int MaxRoomName = 66;
#else
constexpr int MaxRoomName = 22;
#endif


class RoomNode;
typedef void(WINAPI* RoomOnTimer)(RoomNode*);

class RoomNode
{
public:
	UINT ID;
	char Name[MaxRoomName];
	USHORT RoomOwnerID;
	USHORT ServerID;
	USHORT BaseGameMode;
	USHORT SubGameMode;
	BYTE SeatNum;
	BYTE CurrentPlayerNum;
	USHORT Flag;//标志位
	char Password[16] = { 0 };//房间密码
	ClientNode* Player[6] = { 0 };
	char SeatState[6] = { 1 };//座位状态
	HANDLE Timer;
	RoomOnTimer Callback;//RoomNode* 指针 
	BYTE ChatRoomType;
	//
	UINT MapID;
	class
	{
	public:
		char Season;
		char Timeslot;
		char Weather;
	} STDynamicInfo;

	//Dance
	int SceneID;
	int MusicID;

	//
	//char BorderFlag;
	USHORT matchQueueType;
	char CountDownFlag = 0;
	char ranknumber = 0;
};

RoomNode* GetRoom(long RoomID);
void LeaveRoom(ClientNode* Client, short LeaveType);
void LeaveBorderRoom(ClientNode* Client, short LeaveType);
void PrintRoom();
void CreateRoomTimer(RoomNode* Room, int Timeout, RoomOnTimer Callback);


void RequestGetRoomList(ClientNode* Client, BYTE* Body, size_t BodyLen);
void ResponseGetRoomList(ClientNode* Client, USHORT BaseGameMode, USHORT SubGameMode);
void StartSingleGame(ClientNode* Client, BYTE* Body);
void RequestCreateRoom(ClientNode* Client, BYTE* Body, size_t BodyLen);
void ResponseCreateRoom(ClientNode* Client, RoomNode* Room, BYTE ChatRoomType);

void RequestEnterRoom(ClientNode* Client, BYTE* Body, size_t BodyLen);
void ResponseEnterRoom(ClientNode* Client, RoomNode* Room, char SeatID,BOOL HasMoreInfo,char index);
void NotifyEnterRoom(ClientNode* Client, RoomNode* Room, ClientNode* RoomClient, char SeatID);

void RequestLeaveRoom(ClientNode* Client, BYTE* Body, size_t BodyLen);
void ResponseLeaveRoom(ClientNode* Client, short LeaveType);
void NotifyLeaveRoom(ClientNode* Client, UINT uin, char SeatID, bool IsChangeRoomOwner, short NewRoomOwnerID, short LeaveType);

void RequestStartGame(ClientNode* Client, BYTE* Body, size_t BodyLen);
void ResponseStartGame(ClientNode* Client, const char* Reason);

void RequestChangeMap(ClientNode* Client, BYTE* Body, size_t BodyLen);
void ResponseChangeMap(ClientNode* Client, RoomNode* Room);
void NotifyChangeMap(ClientNode* Client, UINT Uin, RoomNode* Room);

void RequestChangeSeatState(ClientNode* Client, BYTE* Body, size_t BodyLen);
void ResponseChangeSeatState(ClientNode* Client, BYTE SeatID, BYTE SeatState);

void RequestKickFromRoom(ClientNode* Client, BYTE* Body, size_t BodyLen);
void ResponseKickFromRoom(ClientNode* Client, UINT DstUin);

void RequestChangeReadyState(ClientNode* Client, BYTE* Body, size_t BodyLen);
void ResponseChangeReadyState(ClientNode* Client, bool ReadyState);

void RequestTalk(ClientNode* Client, BYTE* Body, size_t BodyLen);
void ResponseTalk(ClientNode* Client, BYTE Type, BYTE ClientUseFlag, UINT DestPlayerUin);
void NotifyTalk(ClientNode* Client, ClientNode* RoomClient, BYTE Type, BYTE ClientUseFlag, UINT DestPlayerUin, short ContentLength, const char* Content);
