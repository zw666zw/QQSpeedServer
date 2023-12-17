#pragma once
#include "Message.h"

int DanceMusicDuration(int MusicID);


void NotifyDanceGameBegin(ClientNode* Client);
void RequestDancePrepareReady(ClientNode* Client, BYTE* Body, size_t BodyLen);
void NotifyDanceRaceBegin(ClientNode* Client);

void RequestDanceChangeMusic(ClientNode* Client, BYTE* Body, size_t BodyLen);
void ResponseDanceChangeMusic(ClientNode* Client, int MusicID);

void RequestDanceChangeMode(ClientNode* Client, BYTE* Body, size_t BodyLen);
void ResponseDanceChangeMode(ClientNode* Client, int Mode);

void RequestDanceChangeRandKeyFlag(ClientNode* Client, BYTE* Body, size_t BodyLen);
void ResponseDanceChangeRandKeyFlag(ClientNode* Client, BYTE RandKeyFlag);

void RequestDanceStepStatistics(ClientNode* Client, BYTE* Body, size_t BodyLen);
void ResponseDanceStepStatistics(ClientNode* Client, UINT Uin, UINT ScoresInc, UINT ScoresTotal);
void NotifyDanceStepStatistics(ClientNode* Client, UINT Uin, UINT ScoresInc, UINT ScoresTotal);

void RequestChangeScene(ClientNode* Client, BYTE* Body, size_t BodyLen);
void ResponseChangeScene(ClientNode* Client, int SceneID);

void RequestLoverDanceChangeOneMode(ClientNode* Client, BYTE* Body, size_t BodyLen);
void ResponseLoverDanceChangeOneMode(ClientNode* Client, int Mode);
void RequestLoverDanceStepStatistics(ClientNode* Client, BYTE* Body, size_t BodyLen);
void NotifyLoverDanceStepStatistics(ClientNode* Client, char TeamID, UINT ScoresInc, UINT ScoresTotal);


void NotifyDanceShow(ClientNode* Client);
void NotifyDanceRaceOver(ClientNode* Client);
void NotifyDanceGameOver(ClientNode* Client);

