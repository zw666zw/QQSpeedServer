#pragma once

#include "Message.h"

void InitChatRoom();
class ChatRoomNode
{
public:
	UINT ID;
	const char* Name;
	short CurrPlayerNum;
	short MaxPlayerNum;
	int RoomType;
	short SceneID;
	int x;
	int y;
	int z;
	ClientNode* Player[99];
};
constexpr int ChatRoomNum = 6;
extern ChatRoomNode ChatRooms[ChatRoomNum];



void RequestEnterOutdoor(ClientNode* Client, BYTE* Body, size_t BodyLen);

void RequestChangeChairState(ClientNode* Client, BYTE* Body, size_t BodyLen);

void LeaveOutdoor(ClientNode* Client);
void RequestLeaveOutdoor(ClientNode* Client, BYTE* Body, size_t BodyLen);
void ResponseLeaveOutdoor(ClientNode* Client);
void NotifyLeaveOutdoor(ClientNode* Client, UINT Uin);

void RequestHeroMove(ClientNode* Client, BYTE* Body, size_t BodyLen);

