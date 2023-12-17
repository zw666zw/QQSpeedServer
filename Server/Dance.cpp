#include "Dance.h"
#include <stdio.h>
#include <time.h>

#include "Room.h"

#include "yaml-cpp/yaml.h"


void WINAPI OnDanceTimer3(RoomNode* Room)
{
	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			NotifyDanceGameOver(RoomClient);
		}
	}
}
void WINAPI OnDanceTimer2(RoomNode* Room)
{
	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			NotifyDanceRaceOver(RoomClient);
		}
	}
	CreateRoomTimer(Room, 5000, OnDanceTimer3);
}
void WINAPI OnDanceTimer(RoomNode* Room)
{
	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			NotifyDanceShow(RoomClient);
		}
	}
	CreateRoomTimer(Room, 5000, OnDanceTimer2);
}


int DanceMusicDuration(int MusicID)
{
	int Duration = -1;
	try
	{
		YAML::Node Config = YAML::LoadFile("DanceMusic.yml");
		for (size_t i = 0; i < Config.size(); i++)
		{
			YAML::Node DanceMusic = Config[i];
			if (DanceMusic["ID"].as<int>() == MusicID)
			{
				Duration = DanceMusic["Duration"].as<int>();
				break;
			}
		}
	}
	catch (const std::exception&)
	{
	}
	return Duration;
}

void NotifyDanceGameBegin(ClientNode* Client)
{
	RoomNode* Room = GetRoom(Client->RoomID);
	if (!Room)
	{
		return;
	}

	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, 8000); //NormalLoadTime

	Write32(p, Client->GameID); //GameID
	Write32(p, (DWORD)time(nullptr)); //Seed

	Write8(p, Room->CurrentPlayerNum);

	int Mode = 3;
	if (Room->SubGameMode == 2)
	{
		Mode = 1;
	}
	else if (Room->SubGameMode == 1)
	{
		Mode = 3;
	}
	//printf("Mode %d\n", Mode);
	fflush(stdout);
	Write32(p, Mode); //Mode
	Write32(p, Room->SceneID); //SceneID
	Write32(p, Room->MusicID); //MusicID

	Write8(p, 0); //RandKeyFlag
	Write8(p, 0); //PlayerNum
	/*
m_astLoverDanceStartGameInfo[].m_uiUin
m_astLoverDanceStartGameInfo[].m_iMode
m_astLoverDanceStartGameInfo[].m_bRandKeyFlag
m_astLoverDanceStartGameInfo[].m_ucTeamID
	*/

	len = p - buf;
	SendToClient(Client, 726, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
}

void RequestDancePrepareReady(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	/*
m_iMode
m_iSceneID
m_szSceneHash[]:
m_iMusicID
m_szMusicHash[]:
m_bRandKeyFlag
m_uiClothesWeight
	*/

	if (Client->RoomID)
	{
		Client->IsReady = TRUE;
		RoomNode* Room = GetRoom(Client->RoomID);
		if (!Room)
		{
			return;
		}
		BOOL All = TRUE;
		for (char i = 0; i < 6; i++)
		{
			ClientNode* RoomClient = Room->Player[i];
			if (RoomClient)
			{
				if (RoomClient->IsReady == FALSE)
				{
					All = FALSE;
					break;
				}
			}
		}
		if (All)
		{
			for (char i = 0; i < 6; i++)
			{
				ClientNode* RoomClient = Room->Player[i];
				if (RoomClient)
				{
					NotifyDanceRaceBegin(RoomClient);
				}
			}
		}
	}
}

void NotifyDanceRaceBegin(ClientNode* Client)
{
	RoomNode* Room = GetRoom(Client->RoomID);
	if (!Room)
	{
		return;
	}
	ClientNode* Players[6];
	char CurrentPlayers = 0;
	for (char i = 0; i < 6; i++)
	{
		if (Room->Player[i])
		{
			Players[CurrentPlayers] = Room->Player[i];
			CurrentPlayers++;
		}
	}

	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write32(p, 9000); //CountDownTime

	Write8(p, CurrentPlayers); //PlayerNum
	for (char i = 0; i < CurrentPlayers; i++)
	{
		Write32(p, Players[i]->Uin); //Uin[]
	}

	len = p - buf;
	SendToClient(Client, 728, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
}


void RequestDanceChangeMusic(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	int MusicID = Read32(Body);

	RoomNode* Room = GetRoom(Client->RoomID);
	if (!Room)
	{
		return;
	}
	Room->MusicID = MusicID;
	//printf("MusicID:%d\n", MusicID);
	fflush(stdout);
	ResponseDanceChangeMusic(Client, MusicID);
}
void ResponseDanceChangeMusic(ClientNode* Client, int MusicID)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID
	Write32(p, MusicID); //NewMusicID
	
	Write8(p, 0); //ReasonLen

	Write32(p, 0); //PreKnownMusicID

	len = p - buf;
	SendToClient(Client, 253, buf, len, Client->RoomID, FE_ROOM, Client->ConnID, Response);
}

void RequestDanceChangeMode(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	int Mode = Read32(Body);
	//printf("Mode:%d\n", Mode);
	fflush(stdout);
	ResponseDanceChangeMode(Client, Mode);
}
void ResponseDanceChangeMode(ClientNode* Client, int Mode)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID
	Write32(p, Mode); //NewMode

	Write8(p, 0); //ReasonLen

	Write32(p, 0); //PreKnownMusicID

	len = p - buf;
	SendToClient(Client, 257, buf, len, Client->RoomID, FE_ROOM, Client->ConnID, Response);
}

void RequestDanceChangeRandKeyFlag(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	BYTE RandKeyFlag = Read8(Body);
	//printf("RandKeyFlag:%d\n", RandKeyFlag);
	fflush(stdout);
	ResponseDanceChangeRandKeyFlag(Client, RandKeyFlag);
}
void ResponseDanceChangeRandKeyFlag(ClientNode* Client, BYTE RandKeyFlag)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID

	Write8(p, RandKeyFlag); //NewRandKeyFlag

	Write8(p, 0); //ReasonLen

	len = p - buf;
	SendToClient(Client, 258, buf, len, Client->RoomID, FE_ROOM, Client->ConnID, Response);
}

void RequestChangeScene(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	int SceneID = Read32(Body);

	RoomNode* Room = GetRoom(Client->RoomID);
	if (!Room)
	{
		return;
	}
	Room->SceneID = SceneID;
	//printf("SceneID:%d\n", SceneID);
	fflush(stdout);
	ResponseChangeScene(Client, SceneID);
}
void ResponseChangeScene(ClientNode* Client, int SceneID)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID
	Write32(p, SceneID); //NewSceneID

	Write8(p, 0); //ReasonLen


	len = p - buf;
	SendToClient(Client, 254, buf, len, Client->RoomID, FE_ROOM, Client->ConnID, Response);
}

void RequestDanceStepStatistics(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	WORD len;
	UINT ScoresInc = 0;

	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	int SegID = Read32(Body);
	int StepID = Read32(Body);
	int Checksum = Read32(Body);
	short Hits = Read16(Body);

	struct
	{
		short First;
		short Last;
	} Combo = { 0,0 };
	{ //Combo
		BYTE* pCombo = Body;
		len = Read16(pCombo);

		Combo.First = Read16(pCombo);
		Combo.Last = Read16(pCombo);
		//printf("First:%d\tLast:%d\t", Combo.First, Combo.Last);

		Body += len;
	}

	short Decision = Read16(Body);

	//printf("Hits:%d\tDecision:%d\n", Hits, Decision);

	ScoresInc = Combo.Last * Decision;
	Client->Scores += ScoresInc;
	ResponseDanceStepStatistics(Client, Uin, ScoresInc, Client->Scores);

	RoomNode* Room = GetRoom(Client->RoomID);
	if (!Room)
	{
		return;
	}
	for (char i = 0; i < 6; i++)
	{
		if (Room->Player[i])
		{
			NotifyDanceStepStatistics(Room->Player[i], Uin, ScoresInc, Client->Scores);
		}
	}
}
void ResponseDanceStepStatistics(ClientNode* Client, UINT Uin, UINT ScoresInc, UINT ScoresTotal)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID
	Write32(p, Uin);
	Write32(p, ScoresInc);
	Write32(p, ScoresTotal);

	len = p - buf;
	SendToClient(Client, 260, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Response);
}
void NotifyDanceStepStatistics(ClientNode* Client, UINT Uin, UINT ScoresInc, UINT ScoresTotal)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write32(p, Uin);
	Write32(p, ScoresInc);
	Write32(p, ScoresTotal);

	len = p - buf;
	SendToClient(Client, 732, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
}

void NotifyDanceRank(ClientNode* Client, UINT Uin, UINT ScoresInc, UINT ScoresTotal)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	/*
m_bPlayerNum
m_auiUin[]
	*/

	len = p - buf;
	SendToClient(Client, 733, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
}

void RequestLoverDanceChangeOneMode(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	int Mode = Read32(Body);

	RoomNode* Room = GetRoom(Client->RoomID);
	if (!Room)
	{
		return;
	}
	//printf("Mode:%d\n", Mode);
	fflush(stdout);
	ResponseLoverDanceChangeOneMode(Client, Mode);
}
void ResponseLoverDanceChangeOneMode(ClientNode* Client, int Mode)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID
	Write32(p, Mode); //NewMode

	Write8(p, 0); //ReasonLen

	len = p - buf;
	SendToClient(Client, 262, buf, len, Client->RoomID, FE_ROOM, Client->ConnID, Response);
}

void RequestLoverDanceStepStatistics(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	WORD len;
	UINT ScoresInc = 0;

	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	int SegID = Read32(Body);
	int StepID = Read32(Body);
	int Checksum = Read32(Body);
	short Hits = Read16(Body);

	struct
	{
		short First;
		short Last;
	} Combo = { 0,0 };
	{ //Combo
		BYTE* pCombo = Body;
		len = Read16(pCombo);

		Combo.First = Read16(pCombo);
		Combo.Last = Read16(pCombo);
		//printf("First:%d\tLast:%d\t", Combo.First, Combo.Last);

		Body += len;
	}

	short Decision = Read16(Body);
	short NormalKeyTotalHits = Read16(Body);

	//printf("Hits:%d\tDecision:%d\tNormalKeyTotalHits:%d\n", Hits, Decision, NormalKeyTotalHits);

	ScoresInc = Combo.Last * Decision;
	Client->Scores += ScoresInc;

	RoomNode* Room = GetRoom(Client->RoomID);
	if (!Room)
	{
		return;
	}
	for (char i = 0; i < 6; i++)
	{
		if (Room->Player[i])
		{
			NotifyLoverDanceStepStatistics(Room->Player[i], 0, ScoresInc, Client->Scores);
		}
	}
}
void NotifyLoverDanceStepStatistics(ClientNode* Client, char TeamID, UINT ScoresInc, UINT ScoresTotal)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write8(p, TeamID);
	Write32(p, ScoresInc);
	Write32(p, ScoresTotal);
	Write8(p, 0); //Cooper
	Write8(p, 0); //CooperScoresInc
	Write32(p, 0); //TotalCooper

	len = p - buf;
	SendToClient(Client, 735, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
}



void NotifyDanceShow(ClientNode* Client)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write32(p, 3000); //ShowTime

	len = p - buf;
	SendToClient(Client, 729, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
}

void NotifyDanceRaceOver(ClientNode* Client)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write8(p, 0); //PlayerNum
	/*
m_astDanceScores[].m_unUin
m_astDanceScores[].m_iRank
m_astDanceScores[].m_iScore
m_astDanceScores[].m_iDanceExpInc
m_astDanceScores[].m_iTotalDanceExp
m_astDanceScores[].m_iMaxCombo
m_astDanceScores[].m_iMaxPerfect
m_astDanceScores[].m_iExpInc
m_astDanceScores[].m_iTotalExp
m_astDanceScores[].m_iMoneyInc
m_astDanceScores[].m_iTotalMoney
m_astDanceScores[].m_bAwardNum
m_astDanceScores[].m_aiSpecialAward[]
m_astDanceScores[].m_iDegree
m_astDanceScores[].m_iLoverVipDanceExpMulti
	*/

	Write8(p, 0); //WinTeamID
	Write32(p, 0); //AwardTime

	Write8(p, 0); //TeamNum
	/*
m_astTeamDanceScores[].m_ucTeamID
m_astTeamDanceScores[].m_ucTeamRank
m_astTeamDanceScores[].m_uiTotalCooper
m_astTeamDanceScores[].m_uiTotalScore
LOVERDANCE_TEM_NUM
m_astTeamDanceScores[].m_stMemDanceScore[].m_unUin
m_astTeamDanceScores[].m_stMemDanceScore[].m_iRank
m_astTeamDanceScores[].m_stMemDanceScore[].m_iScore
m_astTeamDanceScores[].m_stMemDanceScore[].m_iDanceExpInc
m_astTeamDanceScores[].m_stMemDanceScore[].m_iTotalDanceExp
m_astTeamDanceScores[].m_stMemDanceScore[].m_iMaxCombo
m_astTeamDanceScores[].m_stMemDanceScore[].m_iMaxPerfect
m_astTeamDanceScores[].m_stMemDanceScore[].m_iExpInc
m_astTeamDanceScores[].m_stMemDanceScore[].m_iTotalExp
m_astTeamDanceScores[].m_stMemDanceScore[].m_iMoneyInc
m_astTeamDanceScores[].m_stMemDanceScore[].m_iTotalMoney
m_astTeamDanceScores[].m_stMemDanceScore[].m_bAwardNum
m_astTeamDanceScores[].m_stMemDanceScore[].m_aiSpecialAward[]
m_astTeamDanceScores[].m_stMemDanceScore[].m_iDegree
m_astTeamDanceScores[].m_stMemDanceScore[].m_iLoverVipDanceExpMulti
	*/

	len = p - buf;
	SendToClient(Client, 730, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
}

void NotifyDanceGameOver(ClientNode* Client)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID

	len = p - buf;
	SendToClient(Client, 731, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
}