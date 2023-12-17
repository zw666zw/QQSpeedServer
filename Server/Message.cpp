#include "Message.h"
#include "Database.h"
#include<stdlib.h>
#include <stdio.h>
#include <string>
#include <malloc.h>
#include<memory>
#include "Item.h"
#include "oicq/tea.h"
#include "sqlite/sqlite3.h"
#include "yaml-cpp/yaml.h"
extern sqlite3* PlayerDB;
//extern DWORD WINAPI OnSingleOver(PVOID Client);
//extern DWORD WINAPI OnSingleJump(PVOID Client);
extern void ResponseGetSuperN2O(ClientNode* Client);
extern void ResponseGetSuperN2O2(ClientNode* Client);
extern void StartSingleGame(ClientNode* Client, BYTE* Body);

void RequestGetSuperN2O(BYTE* Body, ClientNode* Client);
void MyRequestGetUin(ClientNode* Client, BYTE* Body, size_t BodyLen);
void MyRequestRegister(ClientNode* Client, BYTE* Body, size_t BodyLen);
void PrintfBody(ClientNode* Client, USHORT MsgID, BYTE* Body, size_t BodyLen);
void virtualsend(ClientNode* Client,ItemInfo* Items,short count,UINT itemid);
void virtualsend2(ClientNode* Client, ItemInfo* Items, UINT itemid);
void changekartskin( BYTE* Body, USHORT MsgID, size_t BodyLen, ClientNode* Client);
//void changekartskin2(BYTE* Body, USHORT MsgID, size_t BodyLen, ClientNode* Client);
void RequestDoBagItemShowOperate(ClientNode* Client, BYTE* Body, size_t BodyLen);
ItemInfo* GetRandItem(ClientNode* Client, UINT Itemid, short count);
//ItemInfo* GetRandItem2(ClientNode* Client,short count);
UINT GetRandMap(short MapID);
void ResponseGetQuickRaceTimeRandMap(ClientNode* Client);
extern void ResponseStartBorderGame(ClientNode* Client,USHORT matchQueueType,UINT MapID);
char registerflag = 1;//支持注册
char propflag = 1;//支持抽奖开关
extern char TransferModel;//0 udp 1 tcp
extern void RequestChangeIdentity(ClientNode* Client, BYTE* Body, size_t BodyLen);
extern void ResponseReportCurrentOpt(ClientNode* Client);

extern ClientNode* GetClient(long Uin);
extern void NotifyBorderGameCondition(ClientNode* Client);
extern void ResponseGetRankedMatchShowInfo(ClientNode* Client);
extern void ResponseGetNewHandCritBoxAwardCfg(UINT ItemId,ClientNode* Client);
extern void NotifyUseItemResult2(ClientNode* Client, int ItemID, int UseItemNum);
void RequestReportSkillStoneTakeEffect(ClientNode* Client, BYTE* Body, size_t BodyLen);
void RequestAddFriend(ClientNode* Client, BYTE* Body, size_t BodyLen);
void AckBeAddedAsFriend(ClientNode* Client, BYTE* Body, size_t BodyLen);
void RequestEngage(ClientNode* Client, BYTE* Body, size_t BodyLen);
void AckBeEngaged(ClientNode* Client, BYTE* Body, size_t BodyLen);
extern void RequestGetGroupFriendBaseInfo(ClientNode* Client);
void RequestAddCharm(ClientNode* Client);
extern void ResponseGetGroupFriendBaseInfo(ClientNode* Client, UINT Uin, char* newname);
void RequestInvitePlayer(ClientNode* Client, BYTE* Body, size_t BodyLen);
void ResponseQuickRPC(ClientNode* Client, UINT Uin, UINT Time,UINT Temp);
void ResponseQuickRPC2(ClientNode* Client, UINT Uin, UINT Time,UINT Temp);
extern void RequestC2SSearchKartAltas(ClientNode* Client, BYTE* Body, size_t BodyLen);
void RequestQuickRPC(ClientNode* Client, BYTE* Body, size_t BodyLen);
void RequestChangeOBState(ClientNode* Client, BYTE* Body, size_t BodyLen);
extern void RequestC2SGetKartAltasConfig(ClientNode* Client, BYTE* Body, size_t BodyLen);
extern void NotifyTaskAward(ClientNode* Client, UINT TaskID);
extern void NotifyTaskProgressRate(ClientNode* Client, UINT TaskID);
char* myutf8trans(char* utf8str)
{
	wchar_t* wstr = NULL;
	char* str = NULL;
	try {
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8str, -1, NULL, NULL);
	wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8str, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, NULL, NULL, NULL);
	str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr)
	{
		delete[] wstr;
		wstr = NULL;
	}
	return str;
	}
	catch (...)
	{
		if (wstr)
		{
			delete[] wstr;
		}
		if (str)
		{
			delete[] str;
		}
		return NULL;
	}
}
//GB2312到UTF-8的转换
char* G2U(const char* gb2312)
{
	wchar_t* wstr = NULL;
	char* str = NULL;
	
	try {
		int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
		wstr = new wchar_t[len + 1];
		memset(wstr, 0, len + 1);
		MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
		len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
		str = new char[len + 1];
		memset(str, 0, len + 1);
		WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
		if (wstr)
		{
			delete[] wstr;
			wstr = NULL;
		}
		return str;
	}
	catch (...)
	{
		if (wstr)
		{
			delete[] wstr;
		}
		if (str)
		{
			delete[] str;
		}
		return NULL;
	}
}








void OnRecvFromClient(ClientNode* Client, USHORT MsgID, BYTE* Body, size_t BodyLen)
{
	
	UINT itemid=0;
	UINT temp=0;
	UINT temp2=0;
	UINT temp3=0;
	BYTE* BodyHead;
	ItemInfo* Items = NULL;
#ifdef DEBUG
	if (MsgID != 538/*AckAntiBot*/ && MsgID != 562/*AckDpData*/)
	{
		printf("[GameServer][ConnID:%d]RecvMsg:%d\n", Client->ConnID, MsgID);
	}
#endif
	if (!Client->IsLogin)
	{
		if (MsgID > 100)
		{
			return; //未登录则不能执行太多操作
		}
	}
	//printf("MSG:%u\n", MsgID);
	switch (MsgID)
	{
		//MyServer
	case 1:
		//printf("MSG:%u\n", MsgID);
		MyRequestGetUin(Client, Body, BodyLen);
		break;
	case 2:
	//	printf("MSG:%u\n", MsgID);
		if (registerflag == 1)
		{
			MyRequestRegister(Client, Body, BodyLen);
		}
		break;
		//DirServer
	case 90:
		//printf("MSG:%u\n", MsgID);
		RequestGetWorldInfo(Client, Body, BodyLen);
		break;
	case 91:
		//printf("MSG:%u\n", MsgID);
		RequestGetChatRoomList(Client, Body, BodyLen);
		break;
		//GameServer
	case 100:
		//printf("MSG:%u\n", MsgID);
		RequestLogin(Client, Body, BodyLen);
		break;
	case 101:
	//	printf("MSG:%u\n", MsgID);
		RequestLogout(Client, Body, BodyLen);
		break;
	case 102:
	//	printf("MSG:%u\n", MsgID);
		//PrintfBody(Client, 0, Body, BodyLen);
		RequestGetRoomList(Client, Body, BodyLen);
		break;
	case 103:
		//printf("MSG:%u\n", MsgID);
		//PrintfBody(Client, 0,Body, BodyLen);
		RequestCreateRoom(Client, Body, BodyLen);
		break;
	case 104:
		//printf("MSG:%u\n", MsgID);
		//请求进入房间
		//PrintfBody(Client, 0, Body, BodyLen);
		RequestEnterRoom(Client, Body, BodyLen);
		break;
	case 105:
		
		//系统某些情况会自动调用
		//printf("RequestLeaveRoom:%u\n", MsgID);
		//请求离开房间
		//PrintfBody(Client, 0, Body, BodyLen);
		
		RequestLeaveRoom(Client, Body, BodyLen);
		
		
		break;
	case 107:
		//PrintfBody(Client, 0, Body, BodyLen);
		RequestChangeSeatState(Client, Body, BodyLen);
		break;
	case 108:
	//	printf("MSG:%u\n", MsgID);
	//PrintfBody(Client, 0, Body, BodyLen);
		RequestKickFromRoom(Client, Body, BodyLen);
		break;
	case 109:
	//	printf("MSG:%u\n", MsgID);
		//PrintfBody(Client, 0, Body, BodyLen);
		RequestChangeReadyState(Client, Body, BodyLen);
		break;
	case 110:
	//	printf("MSG:%u\n", MsgID);
		RequestStartGame(Client, Body, BodyLen);
		break;
	case 111:
		//printf("MSG:%u\n", MsgID);
		RequestTalk(Client, Body, BodyLen);
		break;
	case 112:
		//printf("MSG:%u\n", MsgID);
		RequestHello(Client, Body, BodyLen);
		//NotifyTaskAward(Client, 148);//在线任务奖励 taskid:148-150
		break;
	case 120:
	//	printf("MSG:%u\n", MsgID);
		if(Client->TaskID==0)//紫钻练习场房间也会请求这个消息 需要过滤
			RequestPrepareReady(Client, Body, BodyLen);
		break;
	case 121:
	//	printf("MSG:%u\n", MsgID);
		RequestChangeMap(Client, Body, BodyLen);
		break;
	case 122:
	//	printf("MSG:%u\n", MsgID);
	// 存在空指针
	//PrintfBody(Client, 0, Body, BodyLen);
		RequestFindPlayerByQQ(Client, Body, BodyLen);
		break;
	case 123:
		//printf("MSG:%u\n", MsgID);
		//对局实时报告 频繁适度减少读取优化
		if (Client->IsFinish == TRUE)
			break;
		RequestReportCurrentInfo(Client, Body, BodyLen);
		break;
	case 124:
	//	printf("MSG:%u\n", MsgID);
		RequestGetProp(Client, Body, BodyLen);
		break;
	case 130:
	//	printf("MSG:%u\n", MsgID);
		//PrintfBody(Client, Body, BodyLen);
		RequestChangeItemStatus(Client, Body, BodyLen);
		break;
	case 135:
	//	printf("MSG:%u\n", MsgID);
		RequestGetTaskList(Client, Body, BodyLen);
		break;
	case 139:
		//printf("MSG:%u\n", MsgID);
		//直接结束单人任务
		//Read32(Body);
		//Read32(Body);
		Body += 8;
		temp = Read16(Body);
		//printf("temp:%d\n", temp);
		
		if (temp != 0x2)//练习场完成12 练习场手动退出4
		{
			//练习场完成会请求这个消息 然后请求RequestReportCurrentInfo
			SendToClient(Client, 532, (BYTE*)"\x00\x00", 2, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
			SendToClient(Client, 534, (BYTE*)"\x00\x00", 2, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
			if (temp == 4)
			{
				Client->TaskID = 0;
			}
			Client->OptNum = 0;
		}
		else
		{
			Client->OptNum += 1;//单人 碰撞 踩雷次数
			ResponseReportCurrentOpt(Client);
		}
	
		break;
	case 145:
	//	printf("MSG:%u\n", MsgID);
		//RequestGetLicenseInfo(Client, Body, BodyLen);
		break;
	case 151:
	//	printf("MSG:%u\n", MsgID);
		//RequestSwitchInterface(Client, Body, BodyLen);
		break;
	case 152:
	//	printf("MSG:%u\n", MsgID);
		RequestGetSystemTaskList(Client, Body, BodyLen);
		break;
	case 153:
		//printf("RequestTransferByTCP:%u\n", MsgID);
		//对局请求 udp取消该请求 
		//PrintfBody(Client, MsgID, Body, BodyLen);
		RequestTransferByTCP(Client, Body, BodyLen);
		break;
	case 162:
		//printf("MSG:%u\n", MsgID);
		RequestChangeGender(Client, Body, BodyLen);
		break;
	case 163:
	//	printf("MSG:%u\n", MsgID);
		RequestNewGetFriendList(Client, Body, BodyLen);
		break;
	case 148:
		//好友列表信息 启动客户端时获取
		//PrintfBody(Client, MsgID, Body, BodyLen);
		//printf("ResponseGetGroupFriendBaseInfo\n");
		RequestGetGroupFriendBaseInfo(Client);
		//一次只能发送一个人 多次发送即可
		break;
	case 159:
		RequestInvitePlayer(Client, Body, BodyLen);
		break;
	case 114:
		//添加好友
		RequestAddFriend(Client, Body, BodyLen);
		break;
	case 507:
		//添加好友结果
		//PrintfBody(Client, MsgID, Body, BodyLen);
		AckBeAddedAsFriend(Client, Body, BodyLen);
		break;
	case 166:
		//订婚
		//PrintfBody(Client, MsgID, Body, BodyLen);
		RequestEngage(Client, Body, BodyLen);
		break;
	case 572:
		//订婚结果

		AckBeEngaged(Client, Body, BodyLen);
		break;
	case 165:
	//	printf("MSG:%u\n", MsgID);
		////当游戏模式是影子挑战 紫钻练习不触发这个消息可以取消重生宝石功能 极限挑战需要
		if (Client->GameID == 2)
		{
			RequestUseProp2(Client, Body, BodyLen);
		}
		break;
	case 174:
		//printf("请求改装MSG:%u\n", MsgID);
		//PrintfBody(Client, MsgID, Body, BodyLen);
		RequestRefitKart(Client, Body, BodyLen);
		break;
	case 179:
	//	printf("MSG:%u\n", MsgID);
		//改变UDP状态
	//	RequestChangeUdpState(Client, Body, BodyLen);
		break;
	case 183:
	//	printf("MSG:%u\n", MsgID);
		RequestSkipFreshTask(Client, Body, BodyLen);
		break;
	case 187:
	//	printf("MSG:%u\n", MsgID);
		//RequestGetRandomTask(Client, Body, BodyLen);
		break;
	case 253:
	//	printf("MSG:%u\n", MsgID);
	//	RequestDanceChangeMusic(Client, Body, BodyLen);
		break;
	case 254:
	//	printf("MSG:%u\n", MsgID);
	//	RequestChangeScene(Client, Body, BodyLen);
		break;
	case 257:
	//	printf("MSG:%u\n", MsgID);
	//	RequestDanceChangeMode(Client, Body, BodyLen);
		break;
	case 258:
	//	printf("MSG:%u\n", MsgID);
	//	RequestDanceChangeRandKeyFlag(Client, Body, BodyLen);
		break;
	case 259:
	//	printf("MSG:%u\n", MsgID);
	//	RequestDancePrepareReady(Client, Body, BodyLen);
		break;
	case 260:
	//	printf("MSG:%u\n", MsgID);
	//	RequestDanceStepStatistics(Client, Body, BodyLen);
		break;
	case 261:
	//	printf("MSG:%u\n", MsgID);
		RequestDeleteOneItem(Client, Body, BodyLen);
		break;
	case 262:
	//	printf("MSG:%u\n", MsgID);
	//	RequestLoverDanceChangeOneMode(Client, Body, BodyLen);
		break;
	case 263:
	//	printf("MSG:%u\n", MsgID);
	//	RequestLoverDanceStepStatistics(Client, Body, BodyLen);
		break;
	case 271:
		//printf("请求赛车改装信息MSG:%u\n", MsgID);
		RequestKartRefitInfo(Client, Body, BodyLen);
		break;
	case 277:
	//	printf("MSG:%u\n", MsgID);
		RequestChangeModel(Client, Body, BodyLen);
		break;
	case 351:
	//	printf("MSG:%u\n", MsgID);
		//PrintfBody(Client, 0, Body, BodyLen);
		RequestHeroMove(Client, Body, BodyLen);
		break;
	case 352:
		//printf("MSG:%u\n", MsgID);
		//进入户外休闲房间？
		RequestEnterOutdoor(Client, Body, BodyLen);
	case 353:
		//离开户外休闲房间
		//PrintfBody(Client, 0, Body, BodyLen);
		RequestLeaveOutdoor(Client, Body, BodyLen);
		break;
	case 357:
	//	printf("MSG:%u\n", MsgID);
		//检查重复用户名
		RequestRegister2(Client, Body, BodyLen);
		break;
	case 360:
	//	printf("MSG:%u\n", MsgID);
		RequestChangeChairState(Client, Body, BodyLen);
		break;
	case 363:
	//	printf("MSG:%u\n", MsgID);
		//RequestGetMaster(Client, Body, BodyLen);
		break;
	case 373:
	//	printf("MSG:%u\n", MsgID);//成就列表
		//RequestGetAchieveList(Client, Body, BodyLen);
		break;
	case 376:
	//	printf("MSG:%u\n", MsgID);
		//RequestModifyPlayerSignature(Client, Body, BodyLen);
		break;
	case 452:
	//	printf("MSG:%u\n", MsgID);
		//RequestGetShoppingCarItemList(Client, Body, BodyLen);
		break;
	case 461:
		// 存在空指针
	//	printf("MSG:%u\n", MsgID);//红人
		//PrintfBody(Client, MsgID, Body, BodyLen);
		RequestTopList(Client, Body, BodyLen);
		break;
	case 499:
	//	printf("MSG:%u\n", MsgID);
		//RequestTransferUDPOK(Client, Body, BodyLen);
		break;
	case 901:
	//	printf("MSG:%u\n", MsgID);
		RequestInlaySkillStone(Client, Body, BodyLen);
		break;
	case 944:
	//	printf("MSG:%u\n", MsgID);
		//RequestFizzInfo(Client, Body, BodyLen);
		break;
	case 1500:
	//	printf("MSG:%u\n", MsgID);
		RequestStartShadowChallenge(Client, Body, BodyLen);
		break;
	case 1501:
		//printf("MSG:%u\n", MsgID);
		RequestEndShadowChallenge(Client, Body, BodyLen);
		break;
	case 10501:
	//	printf("MSG:%u\n", MsgID);
		//RequestFishLogin(Client, Body, BodyLen);
		break;
	case 11451:
	//	printf("MSG:%u\n", MsgID);
		//RequestGetPlayerEventCfg(Client, Body, BodyLen);
		break;
	case 11452:
	//	printf("MSG:%u\n", MsgID);
		//RequestGetPlayerEvent(Client, Body, BodyLen);
		break;
	case 13710:
		//printf("MSG:%u\n", MsgID);//请求车库配置
		RequestC2SGetKartAltasConfig(Client, Body, BodyLen);
		break;
	case 13705:
		RequestC2SSearchKartAltas(Client, Body, BodyLen);
		break;
#ifndef ZingSpeed
	case 317:
		//printf("请求赛车皮肤配置MSG:%u\n", MsgID);
		RequestGetShapeRefitCfg(Client, Body, BodyLen);
		break;
	case 424:
		//printf("MSG:%u\n", MsgID);
		//对局请求退出消息424
		//影子挑战请求退出是1501
		RequestLeaveGame(Client, Body, BodyLen);
		break;
	case 1401:
		//printf("MSG:%u\n", MsgID);
		//RequestC2GSign3Operate(Client, Body, BodyLen);
		//PrintfBody(Client, MsgID,Body, BodyLen);
		break;
	case 16055:
		//printf("MSG:%u\n", MsgID);
		//RequestGetPrivilegeIntroInfo(Client, Body, BodyLen);
		break;
	case 20079:
		//模拟启动
	//	ResponseStartGame(Client, "暂未开放!");
	//	break;
		//PrintfBody(Client, MsgID, Body, BodyLen);
		Body += 8;
		temp = Read16(Body);//0x1立即竞速
		Body += 6;
		temp2 = Read32(Body);
		if (temp2 != 0)
		{
			temp3 = Read32(Body);//指定赛道匹配
		}
		//printf("MSG:%u\n", MsgID);
		//PrintfBody(Client, MsgID, Body, BodyLen);
		//RequestAddToMatchQueue(Client, Body, BodyLen);
		
		if (temp == 0x8)
		{
			//ResponseStartTimerChallenge2(Client);
			break;
			//龙晶大闯关
		}
		else if (temp == 0xa|| temp == 0x0||temp==0x1)//排位边境立即竞速
		{
			
			ResponseStartBorderGame(Client, temp,temp3);
			break;
			//排位 //边境
		}
	//	else if (temp == 0x0)
		//{
		//	ResponseStartGame(Client, "边境暂未开放!");
		//}
		break;
	case 20210:
	//组队匹配
		break;
	case 703:
		//RequestPVPHello
		SendToClient(Client, 703, (BYTE*)"\x00\x00", 2, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
		break;
	case 20082:
		//printf("RequestEnterMatchRoom MSG:%u\n", MsgID);
		//printf("ServerID:%u\n", Client->ServerID);
		//printf("ConnID:%u\n", Client->ConnID);
		RequestEnterMatchRoom(Client, Body, BodyLen);
		break;
	case 697:
		//printf("RequestPVPLogin MSG:%u\n", MsgID);
		//RequestPVPLogin(Client, Body, BodyLen);
		SendToClient(Client, 697, (BYTE*)"\x00\x00", 2, Client->ServerID, FE_PLAYER, Client->ServerID, Response);
		break;
	case 21111:
		//printf("MSG:%u\n", MsgID);
		//RequestSecondGetKartRefitLimitCfg(Client, Body, BodyLen);
		break;
	case 24029:
		//printf("活跃中心MSG:%u\n", MsgID);
		//RequestGetActivityCenterInfo(Client, Body, BodyLen);
		break;
	case 24201:
		//printf("MSG:%u\n", MsgID);
		//RequestGetItemTimeLimtCfg(Client, Body, BodyLen);
		break;
	case 24202:
		//printf("MSG:%u\n", MsgID);
		//龙晶大闯关挑战配置
		//RequestHyperSpaceJumboGetCfg(Client, Body, BodyLen);
		break;
	case 24215:
		//printf("MSG:%u\n", MsgID);
		//RequestGetKeyTranslateInfoNew(Client, Body, BodyLen);
		break;
	case 24258:
		//printf("MSG:%u\n", MsgID);
		//RequestTimerChallenge2ndMoreHallInfo(Client, Body, BodyLen);
		break;
	case 24391:
		//printf("MSG:%u\n", MsgID);
		//RequestWeRelayCommonCfg(Client, Body, BodyLen);
		break;
	case 24465:
		///printf("MSG:%u\n", MsgID);
		//RequestPreGetCommonBoxAward(Client, Body, BodyLen);
		break;
	case 24721:
		//printf("MSG:%u\n", MsgID);
		//RequestSSCOpenStatus(Client, Body, BodyLen);
		break;
	case 28421:
		//printf("MSG:%u\n", MsgID);
		RequestReplayOperate(Client, Body, BodyLen);
		break;
#endif
		//ShopServer
	case 20000:
		//printf("MSG:%u\n", MsgID);
		RequestBuyCommodity(Client, Body, BodyLen);
	case 316:
		//PrintfBody(Client, MsgID, Body, BodyLen);
		changekartskin(Body, MsgID, BodyLen, Client);
		break;
	
	case 168:
		//PrintfBody(Client, MsgID, Body, BodyLen);
		Body += 8;
		itemid = Read32(Body);
		Body += 12;
		temp = Read8(Body);//多开次数
		if (temp == 0)
		{
			temp++;//星宝瓶等道具是0
		}
		if (propflag == 0)
		{
			ResponseStartGame(Client, "抽奖暂时关闭!");
			break;
		}
		if (itemid == 62787)//魅力蝴蝶结加魅力
		{
			RequestAddCharm(Client);
			NotifyUseItemResult2(Client, itemid, temp);
			break;
		}
		//Items=GetRandItem2(Client,temp);
		Items = GetRandItem(Client, itemid, temp);
		if (Items == NULL)
		{
			ResponseStartGame(Client, "宝箱里面没有物品请配置宝箱!");
		}
		else
		{
			NotifyUseItemResult2(Client,itemid,temp);
			virtualsend(Client, Items, temp, itemid);
		}
		break;
	case 138:
		//紫钻练习场
		//printf("MSG:%u\n", MsgID);
		//PrintfBody(Client, MsgID, Body, BodyLen);
		Read32(Body);
		Read32(Body);
		StartSingleGame(Client, Body);
		/*if (Read32(Body) == 0x000006a5)
		{
			StartZiZuanGame(Client);
		}
		else
		{
			Body -= 4;
			StartSingleGame(Client, Body);
		}*/
		break;
	case 119:
		//漂移会触发 
		//printf("MSG:%u\n", MsgID);
		//PrintfBody(Client, MsgID, Body, BodyLen);
		RequestGetSuperN2O(Body, Client);
		break;
	case 10929:
		//printf("RequestGetBattleModeCarSkillInfoListMSG:%u\n", MsgID);
		//PrintfBody(Client, MsgID, Body, BodyLen);
		//ResponseGetBattleModeCarSkillInfoList(Client);
		break;
	//case 319:
		//printf("请求传奇皮肤操作:%u\n", MsgID);
		//PrintfBody(Client, MsgID, Body, BodyLen);
		//RequestShapeLegendOperate(Client, Body, BodyLen);
		//break;
	//case 20097:
		//Uin+Time+2字节flag1+2字节flag2+0x44
		//flag1=0xa 平地小喷
		//0x27 使用氮气
		//PrintfBody(Client, MsgID, Body, BodyLen);
		//break;
	case 24754:
		break;
		//ResponsePointChallengeOpenMainBoard(Client);//极限挑战
		break;
	case 24236:
		
		//ResponseStartTimerChallenge(Client);
		break;
	case 24237:
		//RequestReportTimerChallengeEvent(Client,Body,BodyLen);
		break;
	case 24753:
		//极限挑战购买道具 key：586复活卡 588增时卡 590最后一搏
		//PrintfBody(Client, MsgID, Body, BodyLen);
		break;
	case 25000:
		ResponseGetRankedMatchShowInfo(Client);//排位
		
		break;
	case 131:
		RequestChangeIdentity(Client,Body,BodyLen);
		break;
	case 24254:
		//PrintfBody(Client, MsgID, Body, BodyLen);
		break;
		//RequestReportTimerChallenge2ndEvent(Client, Body, BodyLen);
		break;
	case 24251:
		//PrintfBody(Client, MsgID, Body, BodyLen);
		RequestQuickRPC(Client, Body, BodyLen);
		break;

	case 313:
		//PrintfBody(Client, MsgID, Body, BodyLen);
		Body += 8;
		itemid = Read32(Body);
		ResponseGetNewHandCritBoxAwardCfg(itemid,Client);
		break;
	case 20128://查询产出途径
		break;
	case 24756://幸运3选一 结果
		//PrintfBody(Client, MsgID, Body, BodyLen);
		break;
	case 28412://置顶
	//PrintfBody(Client, MsgID, Body, BodyLen);
		RequestDoBagItemShowOperate(Client, Body, BodyLen);
		break;
	case 28379:
		//PrintfBody(Client, MsgID, Body, BodyLen);//赛道匹配
		ResponseGetQuickRaceTimeRandMap(Client);
		break;
	case 909://宝石发动通知
		RequestReportSkillStoneTakeEffect(Client, Body, BodyLen);
		break;
	case 134:
		//观战模式
		//PrintfBody(Client, MsgID, Body, BodyLen);
		RequestChangeOBState(Client, Body, BodyLen);
		break;
	default:
		//printf("未知消息:%u\n",MsgID);
		//fflush(stdout);
		//PrintfBody(Client, MsgID, Body, BodyLen);
		break;
	}
}




void RequestGetSuperN2O(BYTE *Body, ClientNode* Client)
{
	UINT temp = 0;
	Read32(Body);//Uin
	Read32(Body);//Time
	Read32(Body);// DriftFlag
	temp = Read32(Body);//当前漂移集气总量0x03e8==1000时获得一个氮气
	Client->SuperJetKartFuelInc += temp;//总量
	Client->CurrentAccelerateFuel += temp;//临时量
	if (Client->CurrentAccelerateFuel >= 1000 && Client->KartSkinID == 127616)
	{
		ResponseGetSuperN2O(Client);
		return;
	}
	else if(temp != 1000)//完美集气获得一个超级氮气
	{
		return;
	}
	if (Client->SuperN2O != 0)
		ResponseGetSuperN2O2(Client);
	else
		return;
}
UINT GetRandMap(short MapID)//0 全随 5边境 8赛事 16排位
{
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	int allmap = 0;
	int randindex = 0;
	UINT mapid = 0;
	if (MapID == 5)
	{
		sql = "SELECT count(BorderMap) FROM MapRand;";
	}
	else if (MapID == 8)
	{
		sql = "SELECT count(EventMap) FROM MapRand;";
	}
	else if (MapID == 16)
	{
		sql = "SELECT count(RankMap) FROM MapRand;";
	}
	else
	{
		sql = "SELECT count(AllMap) FROM MapRand;";
	}
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
			allmap = sqlite3_column_int(stmt, 0);
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;
	if (allmap == 0)
		return 114;
	//取得 [ a , b ] 的随机整数：rand()%(b-a+1) +a 
	randindex = rand() % (allmap);
	if (MapID == 5)
	{
		sql = "SELECT BorderMap FROM MapRand limit ?,1;";
	}
	else if (MapID == 8)
	{
		sql = "SELECT EventMap FROM MapRand limit ?,1;";
	}
	else if (MapID == 16)
	{
		sql = "SELECT RankMap FROM MapRand limit ?,1;";
	}
	else
	{
		sql = "SELECT AllMap FROM MapRand limit ?,1;";
	}
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, randindex);
		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
			mapid = sqlite3_column_int(stmt, 0);
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;
	if (mapid == 0)
	{
		//printf("itemid:%d,itemname:%s", *randitem, *itemname);
		return 114;
	}
	return mapid;
}
ItemInfo* GetRandItem(ClientNode* Client, UINT Itemid,short count)
{
	char FilePath[MAX_PATH];
	int allitem = 0;
	int alllist = 0;
	int randindex=0;
	int listindex = 0;
	ItemInfo* Items = NULL;
	
	UINT Seed = 0;
	UINT SeedTemp = 0;
	sprintf_s(FilePath, ".\\Treasure\\%d.yml", Itemid);
	YAML::Node SeedCfg;
	YAML::Node TreasureCfg;
	YAML::Node ItemCfg;
	//YAML::Node CloneCfg;

	try
	{
		
		YAML::Node config = YAML::LoadFile(FilePath);
		alllist = config.size();
		if (alllist == 0)
		{
			//printf("1\n");
			return NULL;//无物品
		}
		Items = new ItemInfo[count];
		if (!Items)
		{
			return NULL;//创建失败
		}
		memset(Items, 0, sizeof(ItemInfo) * count);
		for (int j = 0; j < count; j++)
		{
			
			//CloneCfg= YAML::Clone(config);//克隆指针 解决yml重复引用指针混乱2
			//UINT randlist= (UINT)(rand() % alllist);
			SeedCfg = config[listindex];//0开头
			
			Seed = (UINT)(rand() % 100) + 1;//取(0,100]
			SeedTemp = SeedCfg["Seed"].as<int>();
			while (SeedTemp < Seed)
			{
				listindex++;
				if (listindex == alllist)
				{
					listindex = 0;//如果都不在范围 再重新计算随机值 直到有
					Seed = (UINT)(rand() % 100) + 1;//取(0,100]
					//Sleep(10);
				}
				SeedCfg = config[listindex];//0开头
				SeedTemp = SeedCfg["Seed"].as<int>();
			}
			listindex = 0;

			//printf("Seed:%d SeedTemp:%d\n", Seed, SeedTemp);
			//if (SeedTemp > Seed)
			//{
				TreasureCfg = SeedCfg["Items"];//0开头
				allitem = TreasureCfg.size();
				if (allitem == 0)
				{
					continue;//无物品
				}
				randindex = (UINT)(rand() % allitem);
				ItemCfg = TreasureCfg[randindex];//0开头
				Items[j].ItemID = ItemCfg["ItemId"].as<int>();
				Items[j].ItemNum = ItemCfg["ItemNum"].as<int>();
				//Items[j].AvailPeriod = -1;//显示永久
				
				Items[j].AvailPeriod = ItemCfg["AvailPeriod"].as<int>();
				Items[j].ObtainTime = ItemCfg["ObtainTime"].as<int>();
				Items[j].ItemNum=PlayerDB_AddItem(Client, Client->Uin, Items[j].ItemID, Items[j].ItemNum, Items[j].AvailPeriod, 0);
				NotifyClientAddItem(Client, 1, &Items[j]);//通知客户端添加道具
			//}
				//printf("ItemID:%d\n", Items[j].ItemID);
				ItemCfg.reset();//重置指针 防止混乱
				TreasureCfg.reset();
				SeedCfg.reset();
		}
	}
	catch (const std::exception&)
	{
		//printf("exception");
		if (Items)
		{
			delete[] Items;
		}
		return NULL;
	}
	return Items;
}
/*ItemInfo* GetRandItem2(ClientNode* Client, short count)
{
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	int allitem = 0;
	int randindex;
	sql = "SELECT count(*) FROM AllItem;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
			allitem = sqlite3_column_int(stmt, 0);
		}
	}
	//printf("itemnum:%d", allitem);
	sqlite3_finalize(stmt);
	stmt = NULL;
	if (allitem == 0)
	{
		return NULL;//无物品
	}
	ItemInfo* Items = new ItemInfo[count];
	if (!Items)
	{
		return NULL;//创建失败
	}
	for (int i = 0; i < count; i++)
	{
		randindex = Client->AllItemindex;
		Client->AllItemindex++;
		if (Client->AllItemindex == allitem)
		{
			Client->AllItemindex = 0;
		}
		sql = "SELECT * FROM AllItem limit ?,1;";
		result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (result == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, randindex);
			if (sqlite3_step(stmt) == SQLITE_ROW)
			{
				Items[i].ItemID = sqlite3_column_int(stmt, 0);
				Items[i].ItemNum = 1;
				Items[i].ObtainTime = 0xFFFF;
			}
			else
			{
				Items[i].ItemID = 0;
				return Items;
			}
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
		Items[i].ItemID=PlayerDB_AddItem(Client, Client->Uin, Items[i].ItemID, 1, -1, false);
		NotifyClientAddItem(Client, 1, &Items[i]);//通知客户端添加道具

	}
	return Items;
}*/



void changekartskin(BYTE* Body, USHORT MsgID, size_t BodyLen, ClientNode* Client)
{
	//正常装皮肤 统一使用原车性能
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);
	UINT srcid = Read32(Body);//原车代码
	Body++;
	UINT karthead = Read32(Body);
	UINT kartail = Read32(Body);
	UINT karflank = Read32(Body);
	UINT kartire = Read32(Body);
	//Body += 17;
	UINT dstid = Read32(Body);//新皮肤代码
	UINT updateflag = 1;
	UINT ItemNum = 1;
	UINT isjijia = 0;//是否是机甲
	ItemStatus* aItemStatus;
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;

	aItemStatus = new ItemStatus;
	if (!aItemStatus)
	{
		return;
	}
	aItemStatus[0].NewStatus = 1;
	aItemStatus[0].ItemID = dstid;
	if (karthead == 0 && kartail == 0 && karflank == 0 && kartire == 0)
	{
		updateflag = 0;//如果全为0
	}
	if (dstid == 95405 || dstid == 96462)//本机更换机甲
	{
		isjijia = dstid;
		ResponseChangeItemStatus(Client, 1, aItemStatus);//穿机甲不用改数据库
		dstid = 0;
	}
	if (0 != updateflag)
	{
		sql = "UPDATE KartRefit SET KartHeadRefitItemID=?, KartTailRefitItemID=?,KartFlankRefitItemID=?,KartTireRefitItemID=? WHERE Uin=? AND KartID=?;";
		result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (result == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, karthead);
			sqlite3_bind_int(stmt, 2, kartail);
			sqlite3_bind_int(stmt, 3, karflank);
			sqlite3_bind_int(stmt, 4, kartire);

			sqlite3_bind_int(stmt, 5, Client->Uin);
			sqlite3_bind_int(stmt, 6, srcid);
			result = sqlite3_step(stmt);
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
	}
	sql = "UPDATE KartRefit SET ShapeSuitID=? WHERE Uin=? AND KartID=?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, dstid);
		//sqlite3_bind_int(stmt, 2, 10);
		//sqlite3_bind_int(stmt, 3, 1111);
		//sqlite3_bind_int(stmt, 4, dstid);

		sqlite3_bind_int(stmt, 2, Client->Uin);
		sqlite3_bind_int(stmt, 3, srcid);
		result = sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	stmt = NULL;

	ResponseSkinChange(Client, srcid, dstid);//通知本地皮肤变化
	if (Client->KartID == srcid)//如果当前装备车辆和srcid相同 通知别人我已换皮肤
	{
		Client->KartSkinID = dstid;
		aItemStatus[0].NewStatus = 1;
		if (isjijia)
		{
			aItemStatus[0].ItemID = isjijia;//穿机甲同时系统会自动请求requestchangeitemstatus更换94505 改成原车id即可
		}
		else
		{
			if (dstid == 0)
				aItemStatus[0].ItemID = srcid;
			else
				aItemStatus[0].ItemID = dstid;
		}
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
				if (RoomClient != Client)
				{
					NotifyChangeItemStatus(RoomClient, Client, 1, aItemStatus);
				}
			}
		}
	}
	delete aItemStatus;
}
void virtualsend2(ClientNode* Client, ItemInfo* Items, UINT itemid)
{

	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0x0000);//resultid
	Write32(p, Client->Uin);//uin?
	//模仿请求封包结构并回复
	BYTE* p1 = p;
	Write16(p1, 0); //len 必须
	Write32(p1, itemid);//打开的道具
	Write32(p1, 0);//未知无影响需占位


	Write8(p1, 0);
	Write8(p1, 4);//2字节 len
	Write16(p1, 0x0000);

	{ //Award
		BYTE* pAward = p1;
		Write16(pAward, 0); //len

		Write32(pAward, 0); //Exp
		Write32(pAward, 0); //Money
		Write32(pAward, 0); //SuperMoney
		Write16(pAward, 1); //ItemNum
		for (size_t i = 0; i < 1; i++)
		{ //ItemInfo
			BYTE* pItemInfo = pAward;
			Write16(pItemInfo, 0); //len

			Write32(pItemInfo, Items[0].ItemID); //ItemID
			Write32(pItemInfo, Items[0].ObtainTime); //ItemNum
			Write32(pItemInfo, 0); //AvailPeriod
			Write8(pItemInfo, 0); //Status
			Write32(pItemInfo, Items[0].AvailPeriod); //ObtainTime
			Write32(pItemInfo, 0); //OtherAttribute
			Write16(pItemInfo, 0); //ItemType

			len = pItemInfo - pAward;
			Set16(pAward, (WORD)len);
			pAward += len;
		}

		Write32(pAward, 0); //Coupons
		Write32(pAward, 0); //GuildPoint
		Write32(pAward, 0); //LuckMoney
		Write8(pAward, 0); //ExtendInfoNum
		Write32(pAward, 0); //SpeedCoin

		len = pAward - p1;
		Set16(p1, (WORD)len);
		p1 += len;
	}
	len = p1 - p;
	Set16(p, (WORD)len);
	p += len;
	len = p - buf;

	SendToClient(Client, 168, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
	delete[] Items;


}
void virtualsend(ClientNode* Client,ItemInfo* Items,short count,UINT itemid)
{
	
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	short ItemNum = 0;
	Write16(p, 0); //ResultID
	Write32(p, Client->Uin); //Uin
	{ //TreasureBoxToClient
		BYTE* pTreasureBoxToClient = p;
		Write16(pTreasureBoxToClient, 0); //len

		Write32(pTreasureBoxToClient, itemid); //BoxID
		Write32(pTreasureBoxToClient, 0); //BoxType
		{ //Key
			BYTE* pKey = pTreasureBoxToClient;
			Write16(pKey, 0); //len

			Write32(pKey, 0); //KeyType
			for (size_t i = 0; i <count; i++)
			{ //KeyEntry
				BYTE* pKeyEntry = pKey;
				Write16(pKeyEntry, 0); //len

				Write32(pKeyEntry, 0); //KeyID
				Write32(pKeyEntry, 0); //Num

				len = pKeyEntry - pKey;
				Set16(pKey, (WORD)len);
				pKey += len;
			}
			Write8(pKey, 0); //IsNotConsume

			len = pKey - pTreasureBoxToClient;
			Set16(pTreasureBoxToClient, (WORD)len);
			pTreasureBoxToClient += len;
		}
		{ //AwardEntry
			BYTE* pAwardEntry = pTreasureBoxToClient;
			Write16(pAwardEntry, 0); //len

			Write32(pAwardEntry, 0); //Exp
			Write32(pAwardEntry, 0); //Money
			Write32(pAwardEntry, 0); //SuperMoney
			BYTE* pItemNum = pAwardEntry;
			Write16(pAwardEntry, 0); //ItemNum
			for (size_t i = 0; i < count; i++)
			{ //ItemInfo
				BYTE* pItemInfo = pAwardEntry;
				Write16(pItemInfo, 0); //len
				//if (Items[i].ItemID == 0)
				//{
				//	continue;
				//}
				ItemNum++;
				Write32(pItemInfo, Items[i].ItemID); //ItemID
				Write32(pItemInfo, 1); //ItemNum
				Write32(pItemInfo, -1); //AvailPeriod
				Write8(pItemInfo, 0); //Status
				Write32(pItemInfo, Items[i].ObtainTime); //ObtainTime
				Write32(pItemInfo, 0); //OtherAttribute
				Write16(pItemInfo, 0); //ItemType

				len = pItemInfo - pAwardEntry;
				Set16(pAwardEntry, (WORD)len);
				pAwardEntry += len;
			}
			Set16(pItemNum, ItemNum);
			Write32(pAwardEntry, 0); //Coupons
			Write32(pAwardEntry, 0); //GuildPoint
			Write32(pAwardEntry, 0); //LuckMoney
			Write8(pAwardEntry, 0); //ExtendInfoNum
			Write32(pAwardEntry, 0); //SpeedCoin

			len = pAwardEntry - pTreasureBoxToClient;
			Set16(pTreasureBoxToClient, (WORD)len);
			pTreasureBoxToClient += len;
		}

		len = pTreasureBoxToClient - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write8(p, 0); //ReasonLen
	Write32(p, ItemNum); //Reserve
	Write32(p, 0); //MaxLuckVaue
	Write32(p, 0); //LuckValue
	Write32(p, 0); //TotalLuckValue
	Write32(p, 0); //OpenDate
	Write32(p, 0); //CloseDate
	Write32(p, 0); //OpenTime
	Write32(p, 0); //CloseTime

	len = p - buf;
	SendToClient(Client, 168, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);

	delete[] Items;
	
	
}
void PrintfBody(ClientNode* Client, USHORT MsgID, BYTE* Body, size_t BodyLen)
{

	printf("MsgID:%d  Body 内容大小：%d\n", MsgID,BodyLen);
	fflush(stdout);
	for (int i = 0;i < BodyLen;i++)
	{
		printf("%x ",*(Body+i));
		fflush(stdout);
	}
	printf("\n");
	fflush(stdout);
	
}

BOOL SendToClient(ClientNode* Client, short MsgID, const BYTE* Data, DWORD Length, short SrcID, char SrcFE, short DstID, short MsgType, char Encrypt)
{
	
		CSHEAD* ProtocolHead;
		MSGHEAD* MsgHead;
		void* MsgBody;
		int TotalLength;

		int MsgLen = sizeof(MSGHEAD) + Length;
		MsgHead = (MSGHEAD*)malloc(MsgLen);
		if (!MsgHead)
		{
			return 0;
		}
		MsgHead->MsgID = htons(MsgID);
		MsgHead->MsgType = htons(MsgType);
		MsgHead->MsgSeq = htonl(-1);
		MsgHead->SrcFE = SrcFE;
		MsgHead->DstFE = FE_CLIENT;
		MsgHead->SrcID = htons(SrcID);
		MsgHead->DstID = htons(DstID);
		MsgHead->BodyLen = htons(sizeof(USHORT) + USHORT(Length));
		MsgBody = (void*)(MsgHead + 1);
		memcpy(MsgBody, Data, Length);
		if (Encrypt)
		{
			int EncryptLen = oi_symmetry_encrypt2_len(MsgLen);
			TotalLength = sizeof(CSHEAD) + EncryptLen;
			if (!(ProtocolHead = (CSHEAD*)malloc(TotalLength)))
			{
				return 0;
			}
			//加密数据包
			oi_symmetry_encrypt2((BYTE*)MsgHead, MsgLen, Client->Key, (BYTE*)(ProtocolHead + 1), &EncryptLen);
			TotalLength = sizeof(CSHEAD) + EncryptLen;
		}
		else
		{
			TotalLength = sizeof(CSHEAD) + MsgLen;
			if (!(ProtocolHead = (CSHEAD*)malloc(TotalLength)))
			{
				return 0;
			}
			memcpy((MSGHEAD*)(ProtocolHead + 1), MsgHead, MsgLen);
		}
		free(MsgHead);

		ProtocolHead->TotalLength = htonl(TotalLength);
		ProtocolHead->Ver = htons(116);
		ProtocolHead->DialogID = htons(SrcID);
		ProtocolHead->Seq = htonl(-1);
		ProtocolHead->Uin = htonl(Client->Uin);
		ProtocolHead->BodyFlag = Encrypt;
		ProtocolHead->OptLength = 0;

		BOOL isOK = Client->Server->Send(Client->ConnID, (BYTE*)ProtocolHead, TotalLength);

		//if (MsgID == 90)
		//{
		//	for (int i = 0; i < TotalLength; i++)
		//	{
		//		printf("%02x ", *((BYTE*)ProtocolHead + i));
		//	}
		//}
#ifdef DEBUG
		printf("[ConnID:%d]SendMsg:%d\n", Client->ConnID, MsgID);
#endif
		free(ProtocolHead);
		return isOK;
	
	
	return 0;
}

void OnFullReceive(ClientNode* Client, BYTE* Data, size_t Length)
{
	if(Length < sizeof(CSHEAD))
	{
		Client->Server->Disconnect(Client->ConnID);
		Client->IsLogin = FALSE;
		//delete Client;
		return;
	}
	CSHEAD* ProtocolHead = (CSHEAD*)Data;
	BYTE* Body;
	DWORD HeadLen = sizeof(CSHEAD) + ProtocolHead->OptLength;
	if(Length < HeadLen)
	{
		Client->Server->Disconnect(Client->ConnID);
		Client->IsLogin = FALSE;
		//delete Client;
		return;
	}

	if (ProtocolHead->OptLength)
	{
		Body = (BYTE*)(ProtocolHead + 1);
		//官方服务器应该根据这个进行查表获取key
		//而我们偷懒,把它作为登录密码,这样其实不安全,并且它是明文传输的

		char* Password = new char[ProtocolHead->OptLength + 1];
		memcpy(Password, Body, ProtocolHead->OptLength);
		Password[ProtocolHead->OptLength] = 0;
		//printf("CmpPassword:%s\n", Password);
#ifdef ZingSpeed
		if (strcmp("!", Password) == 0) //TODO: 这个密码是固定的,不安全.
		{
			Client->IsLogin = TRUE;
		}
#else
		if (UserDB_CmpPassword(ntohl(ProtocolHead->Uin), Password))
		{
			Client->IsLogin = TRUE;
		}
		//else
			//Client->IsLogin = FALSE;密码错误
#endif
		delete[] Password;
		//Password = NULL;
	}

	DWORD BodyLen = Length - HeadLen;
	if (BodyLen >= sizeof(MSGHEAD))
	{
		MSGHEAD* MsgHead = (MSGHEAD*)((DWORD)Data + HeadLen);
		if (ProtocolHead->BodyFlag)
		{
			Body = (BYTE*)malloc(BodyLen);
			if (!Body)
			{
				return;
			}
			if (oi_symmetry_decrypt2((BYTE*)MsgHead, BodyLen, Client->Key, Body, (int*)&BodyLen) == false)
			{
				//printf("[ConnID:%d]解密失败\n", Client->ConnID);
				free(Body);
				return;
			}
		}
		else
		{
			
			Body = (BYTE*)malloc(BodyLen);
			if (!Body)
			{
				return;
			}
			memcpy(Body, MsgHead, BodyLen);
		}
		MsgHead = (MSGHEAD*)Body;
		Body = (BYTE*)Body + sizeof(MSGHEAD);
		BodyLen = BodyLen - sizeof(MSGHEAD);

		if (ProtocolHead->OptLength)
		{
			Client->ServerID = ntohs(MsgHead->DstID);
		}
		OnRecvFromClient(Client, ntohs(MsgHead->MsgID), Body, ntohs(MsgHead->BodyLen));

		free(MsgHead);
	}
	else
	{
		
		//printf("[ConnID:%d]不支持请求检查更新\n", Client->ConnID);
		Client->Server->Disconnect(Client->ConnID);
		Client->IsLogin = FALSE;
	
	}

}




void RequestFishLogin(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	ResponseFishLogin(Client);
}
void ResponseFishLogin(ClientNode* Client)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //Result
	Write32(p, Client->Uin); //Uin

	{ //BaseFishInfo
		BYTE* pBaseFishInfo = p;
		Write16(pBaseFishInfo, 0); //len

		Write32(pBaseFishInfo, 0); //Experience
		Write32(pBaseFishInfo, 0); //Money
		Write8(pBaseFishInfo, 0); //FishStockNum
		Write8(pBaseFishInfo, 0); //RubbishCount

		len = pBaseFishInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	{ //TodayInfo
		BYTE* pTodayInfo = p;
		Write16(pTodayInfo, 0); //len

		Write8(pTodayInfo, 0); //RestStealCount
		Write8(pTodayInfo, 0); //RestVisitStrangerCount
		Write8(pTodayInfo, 0); //RestClearRubbishCount

		len = pTodayInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write8(p, 0); //FishStockNum
	/*
m_astFishStockInfo[].m_uchFishStockID
m_astFishStockInfo[].m_uchMaturityCount
m_astFishStockInfo[].m_uchTotalGrowStage
m_astFishStockInfo[].m_uchCurrentGrowStage
m_astFishStockInfo[].m_uchFishNum
m_astFishStockInfo[].m_uchStealedCount
m_astFishStockInfo[].m_uchFeedInfo
m_astFishStockInfo[].m_iFishItemID
m_astFishStockInfo[].m_uiFishStartTime
m_astFishStockInfo[].m_uiMaturityTime
m_astFishStockInfo[].m_uiCurGrowStageEndTime
	*/

	Write8(p, 0); //ReasonLen


	len = p - buf;
	SendToClient(Client, 10501, buf, len, 0, 32, Client->ConnID, Response);
}


void RequestGetPlayerEventCfg(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	ResponseGetPlayerEventCfg(Client);
}
void ResponseGetPlayerEventCfg(ClientNode* Client)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID
	Write32(p, 0); //GetFriendsEventInterval
	Write32(p, 0); //GetOtherEventInterval
	Write32(p, 0); //FilterTimeLimit

	len = p - buf;
	SendToClient(Client, 11451, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestGetPlayerEvent(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);
	BYTE TargetType = Read8(Body);
	BYTE TimeType = Read8(Body);

	//m_ushTarGetNum
	//m_astTarGetInfo[].m_uiUin
	//m_astTarGetInfo[].m_uiEventID

	ResponseGetPlayerEvent(Client, TargetType, TimeType);
}
void ResponseGetPlayerEvent(ClientNode* Client, BYTE TargetType, BYTE TimeType)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID
	Write8(p, TargetType); //
	Write8(p, TimeType); //
	Write16(p, 0); //Num
	/*
m_astEvent[].m_uiUin
m_astEvent[].m_ucType
m_astEvent[].m_uiEventID
m_astEvent[].m_ucIntNum
m_astEvent[].m_auiPara[]
m_astEvent[].m_ucShortNum
m_astEvent[].m_aushPara[]
m_astEvent[].m_uStrNum
m_astEvent[].m_astPara[].m_szStr[]
m_astEvent[].m_uiTime
	*/

	len = p - buf;
	SendToClient(Client, 11452, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}


void RequestChangeUdpState(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);
	BYTE State = Read8(Body);
	//printf("Uin:%d ChangeUdpState:%d\n", Uin,State);
	//TransferModel = State;

	//fflush(stdout);
	
}

void RequestTransferUDPOK(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);
	short DstDlg = Read16(Body);
	UINT DstUin = Read32(Body);
	short InfoLength = Read16(Body);
	ResponseTransferUDPOK(Client);
}
void ResponseTransferUDPOK(ClientNode* Client)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID

	len = p - buf;
	SendToClient(Client, 499, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}
/*
999
--------------------CNotifyUDPOKPara--------------------
m_unUin
m_unTime
m_nSrcDlg
m_unSrcUin
m_nInfoLength
--------------------------------------------------------
*/





void RequestFizzInfo(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	ResponseFizzInfo(Client);
}
void ResponseFizzInfo(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	{ //FizzBaseInfo
		BYTE* pFizzBaseInfo = p;
		Write16(pFizzBaseInfo, 0); //len

		Write16(pFizzBaseInfo, 0); //FizzPointDaily
		Write16(pFizzBaseInfo, 0); //FizzPointWeekly
		Write32(pFizzBaseInfo, 0); //FizzPointTotal
		Write8(pFizzBaseInfo, 0); //FizzEmblem

		len = pFizzBaseInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write8(p, 0); //FizzTaskNum
	/*
	for (size_t i = 0; i < 0; i++)
	{ //FizzTaskInfo
		BYTE* pFizzTaskInfo = p;
		Write16(pFizzTaskInfo, 0); //len

		Write8(pFizzTaskInfo, 0); //TaskID
		Write8(pFizzTaskInfo, 0); //Status
		Write32(pFizzTaskInfo, 0); //TotalProgress
		Write32(pFizzTaskInfo, 0); //CurrentProgress
		Write16(pFizzTaskInfo, 0); //FizzPoint
		Write8(pFizzTaskInfo, 0); //DisplayPri
		Write8(pFizzTaskInfo, 0); //SpecialFlag

		len = pFizzTaskInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	Write8(p, 0); //FizzLotteryNum
	/*
	for (size_t i = 0; i < 0; i++)
	{ //FizzLotteryInfo
		BYTE* pFizzLotteryInfo = p;
		Write16(pFizzLotteryInfo, 0); //len

		Write8(pFizzLotteryInfo, 0); //LotteryType
		Write8(pFizzLotteryInfo, 0); //Status
		Write16(pFizzLotteryInfo, 0); //FizzPoint
		Write8(pFizzLotteryInfo, 0); //ControlledItemNum
		Write32(pFizzLotteryInfo, 0); //ControlledItem[]

		len = pFizzLotteryInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/

	len = p - buf;
	SendToClient(Client, 944, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestGetShoppingCarItemList(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);
	//ResponseGetShoppingCarItemList(Client);
}
void ResponseGetShoppingCarItemList(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	{ //ShoppingCarItemList
		BYTE* pShoppingCarItemList = p;
		Write16(pShoppingCarItemList, 0); //len

		Write8(pShoppingCarItemList, 1); //ItemNum
		Write32(pShoppingCarItemList, 10020); //Item[]

		len = pShoppingCarItemList - p;
		Set16(p, (WORD)len);
		p += len;
	}

	len = p - buf;
	SendToClient(Client, 452, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestGetKeyTranslateInfoNew(ClientNode* Client, BYTE* Body, size_t BodyLen)//获取新键盘设置
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	ResponseGetKeyTranslateInfoNew(Client);
}
void ResponseGetKeyTranslateInfoNew(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, 0); //Uin
	Write16(p, 0); //ResultID
	Write8(p, 0); //ReasonLen
	{ //KeyTranslateInfo
		BYTE* pKeyTranslateInfo = p;
		Write16(pKeyTranslateInfo, 0); //len

		Write8(pKeyTranslateInfo, 0); //KeyTranslateDefaultKeyNum1
		Write8(pKeyTranslateInfo, 0); //KeyTranslateNewKeyNum1
		Write8(pKeyTranslateInfo, 0); //KeyTranslateDefaultKeyNum2
		Write8(pKeyTranslateInfo, 0); //KeyTranslateNewKeyNum2

		len = pKeyTranslateInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	len = p - buf;
	SendToClient(Client, 24215, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}



void RequestGetMaster(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	ResponseGetMaster(Client);
}
void ResponseGetMaster(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	Write32(p, Client->Uin); //Uin
	Write8(p, 0); //AccStatus
	Write32(p,0); //MasterUin
	Write32(p, 0); //AccTime
	Write32(p, 0); //GraduateTime
	Write16(p, 0); //RecentPMAwardNum
	/*
	for (size_t i = 0; i < n; i++)
	{ //RecentPMAwards
		BYTE* pRecentPMAwards = p;
		Write16(pRecentPMAwards, 0); //len 

		Write16(pRecentPMAwards, 0); //RecentPMAwardDesLen 描述长度

		len = pRecentPMAwards - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	Write8(p, 0); //ReasonLen

	len = p - buf;
	SendToClient(Client, 363, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestSSCOpenStatus(ClientNode* Client, BYTE* Body, size_t BodyLen)//SSC比赛打开状态
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	ResponseSSCOpenStatus(Client);
}
void ResponseSSCOpenStatus(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	Write8(p, 1); //Satus
	Write8(p, 0); //TipsLen

	len = p - buf;
	SendToClient(Client, 24721, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestSwitchInterface(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	bool InterfaceType = Read8(Body);

	ResponseSwitchInterface(Client);
}
void ResponseSwitchInterface(ClientNode* Client)
{
	BYTE buf[6]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	Write32(p, 0); //Uin

	len = p - buf;
	SendToClient(Client, 151, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestSecondGetKartRefitLimitCfg(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	//二次进阶改装
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	ResponseSecondGetKartRefitLimitCfg(Client);
}
void ResponseSecondGetKartRefitLimitCfg(ClientNode* Client)
{
	//回复进阶改装信息?
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	Write32(p, Client->Uin); //Uin
	{ //KartRefitLimitCfg
		BYTE* pKartRefitLimitCfg = p;
		Write16(pKartRefitLimitCfg, 0); //len

		Write16(pKartRefitLimitCfg, 0); //OpenKartTypeNum
		//Write32(pKartRefitLimitCfg, 0); //OpenKartTypeList[]
		Write32(pKartRefitLimitCfg, 0); //MinFormerRefitTime
		Write16(pKartRefitLimitCfg, 0); //ExcludeKartTypeNum
		//Write32(pKartRefitLimitCfg, 0); //ExcludeKartTypeList[]
		Write16(pKartRefitLimitCfg, 0); //ForbidListNum
		//Write32(pKartRefitLimitCfg, 0); //ForbidRefitKartID[]

		len = pKartRefitLimitCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}
	{ //RefitItemWeightTypeCfg
		BYTE* pRefitItemWeightTypeCfg = p;
		Write16(pRefitItemWeightTypeCfg, 0); //len

		Write8(pRefitItemWeightTypeCfg, 0); //TypeNum
		/*
		for (size_t i = 0; i < n; i++)
		{ //ItemWeightLevel
			BYTE* pItemWeightLevel = pRefitItemWeightTypeCfg;
			Write16(pItemWeightLevel, 0); //len

			Write8(pItemWeightLevel, 0); //ItemWeightLevel
			Write16(pItemWeightLevel, 0); //MinWeight
			Write16(pItemWeightLevel, 0); //MaxWeight
			Write16(pItemWeightLevel, 0); //ExpAward

			len = pItemWeightLevel - pRefitItemWeightTypeCfg;
			Set16(pRefitItemWeightTypeCfg, (WORD)len);
			pRefitItemWeightTypeCfg += len;
		}
		*/
		len = pRefitItemWeightTypeCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}
	{ //RefitItemCfg
		BYTE* pRefitItemCfg = p;
		Write16(pRefitItemCfg, 0); //len

		Write16(pRefitItemCfg, 0); //ItemNum
		/*
		for (size_t i = 0; i < n; i++)
		{ //RefitItem
			BYTE* pRefitItem = pRefitItemCfg;
			Write16(pRefitItem, 0); //len

			Write32(pRefitItem, 0); //ItemID
			Write8(pRefitItem, 0); //ItemType
			Write8(pRefitItem, 0); //ItemWeightLevel
			Write16(pRefitItem, 0); //Value
			Write32(pRefitItem, 0); //FragmentItemID
			Write32(pRefitItem, 0); //FragmentNumToOneItem
			Write16(pRefitItem, 0); //IsItemOpen

			len = pRefitItem - pRefitItemCfg;
			Set16(pRefitItemCfg, (WORD)len);
			pRefitItemCfg += len;
		}
		*/

		len = pRefitItemCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}

	len = p - buf;
	SendToClient(Client, 21111, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestGetPrivilegeIntroInfo(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);

	ResponseGetPrivilegeIntroInfo(Client);
}
void ResponseGetPrivilegeIntroInfo(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, 0); //Uin
	Write32(p, 0); //CharmValueOfMonth
	Write32(p, 0); //VipLevel
	Write16(p, 0); //PrivilegeInfoNums
	/*
	for (size_t i = 0; i < n; i++)
	{ //PrivilegeInfos
		BYTE* pPrivilegeInfos = p;
		Write16(pPrivilegeInfos, 0); //len

		WriteUn(pPrivilegeInfos, 0); //NextLevelCharmVlaue
		WriteUn(pPrivilegeInfos, 0); //SearchTreasureNums
		WriteUn(pPrivilegeInfos, 0); //GetTreasureNums
		WriteUn(pPrivilegeInfos, 0); //CritCardNums
		WriteUn(pPrivilegeInfos, 0); //MechLargerCardNums
		WriteUn(pPrivilegeInfos, 0); //MallBuyLevel
		WriteUn(pPrivilegeInfos, 0); //HasAlreadyReceived
		WriteUn(pPrivilegeInfos, 0); //AwardItemNums
		for (size_t i = 0; i < n; i++)
		{ //FirstReachLevelItemInfos
			BYTE* pFirstReachLevelItemInfos = pPrivilegeInfos;
			Write16(pFirstReachLevelItemInfos, 0); //len

			WriteUn(pFirstReachLevelItemInfos, 0); //itemID
			WriteUn(pFirstReachLevelItemInfos, 0); //itemNums
			Write32(pFirstReachLevelItemInfos, 0); //AvailPeriod
			WriteUn(pFirstReachLevelItemInfos, 0); //isBestQuality

			len = pFirstReachLevelItemInfos - pPrivilegeInfos;
			Set16(pPrivilegeInfos, (WORD)len);
			pPrivilegeInfos += len;
		}

		len = pPrivilegeInfos - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	//WriteUn(p, 0); //AnouncementInfo[]

	len = p - buf;
	SendToClient(Client, 16055, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestGetItemTimeLimtCfg(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);
	UINT UpdateTime = Read32(Body);

	ResponsetGetItemTimeLimtCfg(Client, UpdateTime);
}
void ResponsetGetItemTimeLimtCfg(ClientNode* Client, UINT UpdateTime)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	Write16(p, 0); //ResultID

	Write32(p, 0); //ItemNum
	/*
	for (size_t i = 0; i < n; i++)
	{ //ItemTimeLimit
		BYTE* pItemTimeLimit = p;
		Write16(pItemTimeLimit, 0); //len

		Write32(pItemTimeLimit, 0); //ItemID
		Write32(pItemTimeLimit, 0); //ExpireTime

		len = pItemTimeLimit - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	Write32(p, UpdateTime); //UpdateTime

	len = p - buf;
	SendToClient(Client, 24201, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}


void RequestGetShapeRefitCfg(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	ResponseGetShapeRefitCfg(Client);
}
void ResponseGetShapeRefitCfg(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	UINT total=0;
	Write16(p, 0); //ResultID
	
	UINT curcount=0;
	UINT curkart=0;
	UINT curskin[64] = { 0 };

	const char* sql = NULL;
	const char* nsql = NULL;
	sqlite3_stmt* stmt = NULL;
	sqlite3_stmt* nstmt = NULL;
	int result;
	int nresult;
	
	BYTE* pTotalSkin = p;
	Write16(p, 0); //KartShapeRefitSuitNum 皮肤配置总数量

	sql = "SELECT * FROM SkinTotal;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			//查询赛车皮肤总量并循环回复客户端
			curkart = sqlite3_column_int(stmt, 0);
			curcount = sqlite3_column_int(stmt, 1);
			total += curcount;//变量增加数量

			nsql = "SELECT * FROM SkinItem Where KartID=?;";
			nresult = sqlite3_prepare_v2(PlayerDB, nsql, -1, &nstmt, NULL);
			if (nresult == SQLITE_OK) {
				sqlite3_bind_int(nstmt, 1, curkart);
				for (int i = 0;sqlite3_step(nstmt) == SQLITE_ROW;i++)
				{
					//查询所有皮肤id存入缓冲区
					curskin[i]= sqlite3_column_int(nstmt, 1);
				}
			}
			sqlite3_finalize(nstmt);
			nstmt = NULL;
	for (size_t i = 0; i < curcount; i++)
	{ //ShapeRefitSuit
		BYTE* pShapeRefitSuit = p;
		Write16(pShapeRefitSuit, 0); //len

		Write32(pShapeRefitSuit, curkart); //KartID
		Write8(pShapeRefitSuit, 0); //KarNameLen
		Write8(pShapeRefitSuit, 0); //RefitItemNum
		//Write32(pShapeRefitSuit, 0); //RefitItem[]
		Write8(pShapeRefitSuit,0 ); //EffectNum
		for (size_t i = 0; i < 0; i++)
		{ //RefitEffects
			BYTE* pRefitEffects = pShapeRefitSuit;
			Write16(pRefitEffects, 0); //len

			Write16(pRefitEffects, 0); //EffectID 
			Write8(pRefitEffects, 0); //Level
			Write32(pRefitEffects, 0); //Value1
			Write32(pRefitEffects, 0); //Value2
			Write8(pRefitEffects, 0); //ResourceLen
			//WriteString(pRefitEffects, "\x4b\x61\x72\x74\x41\x76\x61\x74\x61\x72\x45\x66\x66\x65\x63\x74\x2f\x53\x75\x70\x65\x72\x4a\x65\x74\x2f\x4a\x65\x74\x45\x66\x66\x2e\x6e\x69\x66");
			Write8(pRefitEffects, 0); //EffectResLen
			Write8(pRefitEffects, 0); //Grade

			len = pRefitEffects - pShapeRefitSuit;
			Set16(pShapeRefitSuit, (WORD)len);
			pShapeRefitSuit += len;
		}
		Write16(pShapeRefitSuit, 0x0); //Grade
		Write16(pShapeRefitSuit, 0x0); //DressPoint
		Write16(pShapeRefitSuit, 0x0); //CarLibraryCollectValue
		Write8(pShapeRefitSuit, 0); //RefitModifyNum
		/*for (size_t i = 0; i < n; i++)
		{ //RefitModify
			BYTE* pRefitModify = pShapeRefitSuit;
			Write16(pRefitModify, 0); //len

			Write16(pRefitModify, 0); //RefitID 
			Write8(pRefitModify, 0); //RefitModify
			Write32(pRefitModify, 0); //RefitLimitInc//
			Write32(pRefitModify, 0); //RefitInc

			len = pRefitModify - pShapeRefitSuit;
			Set16(pShapeRefitSuit, (WORD)len);
			pShapeRefitSuit += len;
		}*/
		Write8(pShapeRefitSuit, 0); //HasTurnModify
		/*for (size_t i = 0; i < n; i++)
		{ //TurnModify
			BYTE* pTurnModify = pShapeRefitSuit;
			Write16(pTurnModify, 0); //len

			Write32(pTurnModify, 0); //BaseTurnRate
			Write32(pTurnModify, 0); //VolatileTurnRate
			Write32(pTurnModify, 0); //MaxTurnSpeed
			Write32(pTurnModify, 0); //MinTurnSpeed
			Write32(pTurnModify, 0); //MaxAccuTime
			Write32(pTurnModify, 0); //BaseAccuRate
			Write32(pTurnModify, 0); //MaxAffectSpeed

			len = pTurnModify - pShapeRefitSuit;
			Set16(pShapeRefitSuit, (WORD)len);
			pShapeRefitSuit += len;
		}*/
		Write32(pShapeRefitSuit, curskin[i]); //ShapeSuitID
		Write8(pShapeRefitSuit, 0); //RefitAddtionNum
		//Write32(pShapeRefitSuit, 0);
		//Write32(pShapeRefitSuit, 0);
		//Write32(pShapeRefitSuit, 0);
		//Write32(pShapeRefitSuit, 0);
		Write8(pShapeRefitSuit, 0xe); //GradeResourceLen
		WriteString(pShapeRefitSuit, "\x74\x75\x6e\x69\x61\x6e\x78\x69\x61\x6e\x64\x69\x6e\x67");
		len = pShapeRefitSuit - p;
		Set16(p, (WORD)len);
		p += len;
	}
		}
	}
	Set16(pTotalSkin, total);
	sqlite3_finalize(stmt);
	stmt = NULL;
	
	
		
		
		//数据库legendSuitLevelChoice字段为10时对应选择1级传奇皮肤与特效代码
	//legendSuitLevelChoice为1111可显示进场特效
	//该字段是一个32位值
	Write16(p, 4); //KartShapeRefitLegendNum 传奇皮肤配置
	{ //ShapeRefitLegend 
		BYTE* pShapeRefitLegend = p;
		Write16(pShapeRefitLegend, 0); //len

		Write32(pShapeRefitLegend, 12720); //KartID
		Write8(pShapeRefitLegend, 0); //KarNameLen
		Write16(pShapeRefitLegend, 0); //Grade
		Write8(pShapeRefitLegend, 0); //GradeResourceLen
		//Write8(pShapeRefitLegend, 0xe); //GradeResourceLen
		//WriteString(pShapeRefitLegend, "\x74\x75\x6e\x69\x61\x6e\x78\x69\x61\x6e\x64\x69\x6e\x67");
		Write8(pShapeRefitLegend, 1); //LevelNum
		{ //LevelCfg
			BYTE* pLevelCfg = pShapeRefitLegend;
			Write16(pLevelCfg, 0); //len

			Write8(pLevelCfg, 1); //Level
			Write8(pLevelCfg, 0); //RefitItemNum
			Write8(pLevelCfg, 3); //EffectNum
			{ //RefitEffects
				BYTE* pRefitEffects = pLevelCfg;
				Write16(pRefitEffects, 0); //len

				Write16(pRefitEffects, 0); //EffectID
				Write8(pRefitEffects, 3); //Level
				Write32(pRefitEffects, 0); //Value1
				Write32(pRefitEffects, 0); //Value2
				Write8(pRefitEffects, 0x27); //ResourceLen
				WriteString(pRefitEffects, "\x41\x76\x61\x74\x61\x72\x2f\x6b\x61\x72\x74\x5f\x6e\x65\x77\x2f\x31\x32\x36\x35\x33\x37\x2f\x4d\x4f\x44\x45\x4c\x2f\x7a\x69\x73\x68\x65\x6e\x2e\x6e\x69\x66");
				Write8(pRefitEffects, 0x27); //EffectResLen
				WriteString(pRefitEffects, "\x41\x76\x61\x74\x61\x72\x2f\x6b\x61\x72\x74\x5f\x6e\x65\x77\x2f\x31\x32\x36\x35\x33\x37\x2f\x4d\x4f\x44\x45\x4c\x2f\x7a\x69\x73\x68\x65\x6e\x2e\x6e\x69\x66");
				Write8(pRefitEffects, 1); //Grade

				len = pRefitEffects - pLevelCfg;
				Set16(pLevelCfg, (WORD)len);
				pLevelCfg += len;
			}
			{ //RefitEffects
				BYTE* pRefitEffects = pLevelCfg;
				Write16(pRefitEffects, 0); //len

				Write16(pRefitEffects, 1); //EffectID
				Write8(pRefitEffects, 3); //Level
				Write32(pRefitEffects, 0); //Value1
				Write32(pRefitEffects, 0); //Value2
				Write8(pRefitEffects, 0x2c); //ResourceLen
				WriteString(pRefitEffects, "\x41\x76\x61\x74\x61\x72\x2f\x6b\x61\x72\x74\x5f\x6e\x65\x77\x2f\x31\x32\x36\x35\x33\x37\x2f\x4d\x4f\x44\x45\x4c\x2f\x64\x61\x70\x65\x6e\x74\x65\x78\x69\x61\x6f\x2e\x6e\x69\x66");
				Write8(pRefitEffects, 0x2c); //EffectResLen
				WriteString(pRefitEffects, "\x41\x76\x61\x74\x61\x72\x2f\x6b\x61\x72\x74\x5f\x6e\x65\x77\x2f\x31\x32\x36\x35\x33\x37\x2f\x4d\x4f\x44\x45\x4c\x2f\x64\x61\x70\x65\x6e\x74\x65\x78\x69\x61\x6f\x2e\x6e\x69\x66");
				Write8(pRefitEffects, 1); //Grade

				len = pRefitEffects - pLevelCfg;
				Set16(pLevelCfg, (WORD)len);
				pLevelCfg += len;
			}
			{ //RefitEffects
				BYTE* pRefitEffects = pLevelCfg;
				Write16(pRefitEffects, 0); //len

				Write16(pRefitEffects,4); //EffectID 0影响外观身体 1影响喷气时 
				Write8(pRefitEffects, 4); //Level
				Write32(pRefitEffects, 0x0fa1); //Value1
				Write32(pRefitEffects, 0x06d6); //Value2
				Write8(pRefitEffects, 0x24); //ResourceLen
				WriteString(pRefitEffects, "\x4b\x61\x72\x74\x41\x76\x61\x74\x61\x72\x45\x66\x66\x65\x63\x74\x2f\x53\x75\x70\x65\x72\x4a\x65\x74\x2f\x4a\x65\x74\x45\x66\x66\x2e\x6e\x69\x66");
				Write8(pRefitEffects, 0x2a); //EffectResLen
				WriteString(pRefitEffects, "\x41\x76\x61\x74\x61\x72\x2f\x6b\x61\x72\x74\x5f\x6e\x65\x77\x2f\x31\x32\x36\x35\x33\x37\x2f\x4d\x4f\x44\x45\x4c\x2f\x73\x74\x61\x72\x74\x73\x68\x6f\x77\x2e\x6e\x69\x66");
				Write8(pRefitEffects, 1); //Grade

				len = pRefitEffects - pLevelCfg;
				Set16(pLevelCfg, (WORD)len);
				pLevelCfg += len;
			}

			Write16(pLevelCfg, 0); //DressPoint
			Write16(pLevelCfg, 0); //CarLibraryCollectValue
			Write8(pLevelCfg, 0); //RefitModifyNum
			Write8(pLevelCfg, 0); //HasTurnModify
			Write32(pLevelCfg, 126537); //ShapeSuitID
			Write8(pLevelCfg, 0); //ConsumeNum
			len = pLevelCfg - pShapeRefitLegend;
			Set16(pShapeRefitLegend, (WORD)len);
			pShapeRefitLegend += len;
		}
		

		Write32(pShapeRefitLegend, 126537); //ShapeSuitID
		{ //MaxConsumInfo
			BYTE* pMaxConsumInfo = pShapeRefitLegend;
			Write16(pMaxConsumInfo, 0); //len

			Write32(pMaxConsumInfo, 0); //ItemID
			Write32(pMaxConsumInfo, 0); //ItemNum
			Write32(pMaxConsumInfo, 0); //ItemPeriod

			len = pMaxConsumInfo - pShapeRefitLegend;
			Set16(pShapeRefitLegend, (WORD)len);
			pShapeRefitLegend += len;
		}
		Write8(pShapeRefitLegend, 0); //LegendSkinType 传奇皮肤类型

		len = pShapeRefitLegend - p;
		Set16(p, (WORD)len);
		p += len;
	}
	{ //ShapeRefitLegend 
	BYTE* pShapeRefitLegend = p;
	Write16(pShapeRefitLegend, 0); //len

	Write32(pShapeRefitLegend, 12720); //KartID
	Write8(pShapeRefitLegend, 0); //KarNameLen
	Write16(pShapeRefitLegend, 0); //Grade
	//Write8(pShapeRefitLegend, 0); //GradeResourceLen
	Write8(pShapeRefitLegend, 0xe); //GradeResourceLen
	WriteString(pShapeRefitLegend, "\x74\x75\x6e\x69\x61\x6e\x78\x69\x61\x6e\x64\x69\x6e\x67");
	Write8(pShapeRefitLegend, 1); //LevelNum
	{ //LevelCfg
		BYTE* pLevelCfg = pShapeRefitLegend;
		Write16(pLevelCfg, 0); //len

		Write8(pLevelCfg, 1); //Level
		Write8(pLevelCfg, 0); //RefitItemNum
		Write8(pLevelCfg, 1); //EffectNum
		
		{ //RefitEffects
			BYTE* pRefitEffects = pLevelCfg;
			Write16(pRefitEffects, 0); //len

			Write16(pRefitEffects, 1); //EffectID
			Write8(pRefitEffects, 3); //Level
			Write32(pRefitEffects, 0); //Value1
			Write32(pRefitEffects, 0); //Value2
			Write8(pRefitEffects, 0x2c); //ResourceLen
			WriteString(pRefitEffects, "Avatar/kart_new/123506/MODEL/dapentexiao.nif");
			Write8(pRefitEffects, 0x2c); //EffectResLen
			WriteString(pRefitEffects, "Avatar/kart_new/123506/MODEL/dapentexiao.nif");
			Write8(pRefitEffects, 1); //Grade

			len = pRefitEffects - pLevelCfg;
			Set16(pLevelCfg, (WORD)len);
			pLevelCfg += len;
		}

		Write16(pLevelCfg, 0); //DressPoint
		Write16(pLevelCfg, 0); //CarLibraryCollectValue
		Write8(pLevelCfg, 0); //RefitModifyNum
		Write8(pLevelCfg, 0); //HasTurnModify
		Write32(pLevelCfg, 123506); //ShapeSuitID
		Write8(pLevelCfg, 0); //ConsumeNum
		len = pLevelCfg - pShapeRefitLegend;
		Set16(pShapeRefitLegend, (WORD)len);
		pShapeRefitLegend += len;
	}


	Write32(pShapeRefitLegend, 123506); //ShapeSuitID
	{ //MaxConsumInfo
		BYTE* pMaxConsumInfo = pShapeRefitLegend;
		Write16(pMaxConsumInfo, 0); //len

		Write32(pMaxConsumInfo, 0); //ItemID
		Write32(pMaxConsumInfo, 0); //ItemNum
		Write32(pMaxConsumInfo, 0); //ItemPeriod

		len = pMaxConsumInfo - pShapeRefitLegend;
		Set16(pShapeRefitLegend, (WORD)len);
		pShapeRefitLegend += len;
	}
	Write8(pShapeRefitLegend, 0); //LegendSkinType 传奇皮肤类型

	len = pShapeRefitLegend - p;
	Set16(p, (WORD)len);
	p += len;
	}
	{ //ShapeRefitLegend 
	BYTE* pShapeRefitLegend = p;
	Write16(pShapeRefitLegend, 0); //len

	Write32(pShapeRefitLegend, 74362); //KartID
	Write8(pShapeRefitLegend, 0); //KarNameLen
	Write16(pShapeRefitLegend, 0); //Grade
	Write8(pShapeRefitLegend, 0); //GradeResourceLen
	Write8(pShapeRefitLegend, 1); //LevelNum
	{ //LevelCfg
		BYTE* pLevelCfg = pShapeRefitLegend;
		Write16(pLevelCfg, 0); //len

		Write8(pLevelCfg, 1); //Level
		Write8(pLevelCfg, 0); //RefitItemNum
		Write8(pLevelCfg, 3); //EffectNum
		{ //RefitEffects
			BYTE* pRefitEffects = pLevelCfg;
			Write16(pRefitEffects, 0); //len

			Write16(pRefitEffects, 0); //EffectID
			Write8(pRefitEffects, 3); //Level
			Write32(pRefitEffects, 0); //Value1
			Write32(pRefitEffects, 0); //Value2
			Write8(pRefitEffects, 0x27); //ResourceLen
			WriteString(pRefitEffects, "\x41\x76\x61\x74\x61\x72\x2f\x6b\x61\x72\x74\x5f\x6e\x65\x77\x2f\x31\x31\x38\x37\x32\x39\x2f\x4d\x4f\x44\x45\x4c\x2f\x7a\x69\x73\x68\x65\x6e\x2e\x6e\x69\x66");
			Write8(pRefitEffects, 0x27); //EffectResLen
			WriteString(pRefitEffects, "\x41\x76\x61\x74\x61\x72\x2f\x6b\x61\x72\x74\x5f\x6e\x65\x77\x2f\x31\x31\x38\x37\x32\x39\x2f\x4d\x4f\x44\x45\x4c\x2f\x7a\x69\x73\x68\x65\x6e\x2e\x6e\x69\x66");
			Write8(pRefitEffects, 1); //Grade

			len = pRefitEffects - pLevelCfg;
			Set16(pLevelCfg, (WORD)len);
			pLevelCfg += len;
		}
		{ //RefitEffects
			BYTE* pRefitEffects = pLevelCfg;
			Write16(pRefitEffects, 0); //len

			Write16(pRefitEffects, 1); //EffectID
			Write8(pRefitEffects, 3); //Level
			Write32(pRefitEffects, 0); //Value1
			Write32(pRefitEffects, 0); //Value2
			Write8(pRefitEffects, 0x38); //ResourceLen
			WriteString(pRefitEffects, "\x41\x76\x61\x74\x61\x72\x2f\x6b\x61\x72\x74\x5f\x6e\x65\x77\x2f\x31\x31\x38\x37\x32\x39\x2f\x4d\x4f\x44\x45\x4c\x2f\x63\x68\x65\x71\x69\x61\x6e\x67\x75\x61\x6e\x67\x7a\x68\x61\x6f\x48\x55\x41\x4e\x47\x73\x65\x2e\x6e\x69\x66");
			Write8(pRefitEffects, 0x38); //EffectResLen
			WriteString(pRefitEffects, "\x41\x76\x61\x74\x61\x72\x2f\x6b\x61\x72\x74\x5f\x6e\x65\x77\x2f\x31\x31\x38\x37\x32\x39\x2f\x4d\x4f\x44\x45\x4c\x2f\x63\x68\x65\x71\x69\x61\x6e\x67\x75\x61\x6e\x67\x7a\x68\x61\x6f\x48\x55\x41\x4e\x47\x73\x65\x2e\x6e\x69\x66");
			Write8(pRefitEffects, 1); //Grade

			len = pRefitEffects - pLevelCfg;
			Set16(pLevelCfg, (WORD)len);
			pLevelCfg += len;
		}
		{ //RefitEffects
			BYTE* pRefitEffects = pLevelCfg;
			Write16(pRefitEffects, 0); //len

			Write16(pRefitEffects, 4); //EffectID
			Write8(pRefitEffects, 4); //Level
			Write32(pRefitEffects, 0x0fa1); //Value1
			Write32(pRefitEffects, 0x06d6); //Value2
			Write8(pRefitEffects, 0x24); //ResourceLen
			WriteString(pRefitEffects, "\x4b\x61\x72\x74\x41\x76\x61\x74\x61\x72\x45\x66\x66\x65\x63\x74\x2f\x53\x75\x70\x65\x72\x4a\x65\x74\x2f\x4a\x65\x74\x45\x66\x66\x2e\x6e\x69\x66");
			Write8(pRefitEffects, 0x2a); //EffectResLen
			WriteString(pRefitEffects, "\x41\x76\x61\x74\x61\x72\x2f\x6b\x61\x72\x74\x5f\x6e\x65\x77\x2f\x31\x31\x38\x37\x32\x39\x2f\x4d\x4f\x44\x45\x4c\x2f\x73\x74\x61\x72\x74\x73\x68\x6f\x77\x2e\x6e\x69\x66");
			Write8(pRefitEffects, 1); //Grade

			len = pRefitEffects - pLevelCfg;
			Set16(pLevelCfg, (WORD)len);
			pLevelCfg += len;
		}

		Write16(pLevelCfg, 0); //DressPoint
		Write16(pLevelCfg, 0); //CarLibraryCollectValue
		Write8(pLevelCfg, 0); //RefitModifyNum
		Write8(pLevelCfg, 0); //HasTurnModify
		Write32(pLevelCfg, 118729); //ShapeSuitID
		Write8(pLevelCfg, 0); //ConsumeNum
		len = pLevelCfg - pShapeRefitLegend;
		Set16(pShapeRefitLegend, (WORD)len);
		pShapeRefitLegend += len;
	}


	Write32(pShapeRefitLegend, 118729); //ShapeSuitID
	{ //MaxConsumInfo
		BYTE* pMaxConsumInfo = pShapeRefitLegend;
		Write16(pMaxConsumInfo, 0); //len

		Write32(pMaxConsumInfo, 0); //ItemID
		Write32(pMaxConsumInfo, 0); //ItemNum
		Write32(pMaxConsumInfo, 0); //ItemPeriod

		len = pMaxConsumInfo - pShapeRefitLegend;
		Set16(pShapeRefitLegend, (WORD)len);
		pShapeRefitLegend += len;
	}
	Write8(pShapeRefitLegend, 0); //LegendSkinType 传奇皮肤类型

	len = pShapeRefitLegend - p;
	Set16(p, (WORD)len);
	p += len;
	}
	{ //ShapeRefitLegend 
	BYTE* pShapeRefitLegend = p;
	Write16(pShapeRefitLegend, 0); //len

	Write32(pShapeRefitLegend, 90945); //KartID
	Write8(pShapeRefitLegend, 0); //KarNameLen
	Write16(pShapeRefitLegend, 0); //Grade
	Write8(pShapeRefitLegend, 0); //GradeResourceLen
	Write8(pShapeRefitLegend, 1); //LevelNum
	{ //LevelCfg
		BYTE* pLevelCfg = pShapeRefitLegend;
		Write16(pLevelCfg, 0); //len

		Write8(pLevelCfg, 1); //Level
		Write8(pLevelCfg, 0); //RefitItemNum
		Write8(pLevelCfg, 3); //EffectNum
		{ //RefitEffects
			BYTE* pRefitEffects = pLevelCfg;
			Write16(pRefitEffects, 0); //len

			Write16(pRefitEffects, 0); //EffectID
			Write8(pRefitEffects, 3); //Level
			Write32(pRefitEffects, 0); //Value1
			Write32(pRefitEffects, 0); //Value2
			Write8(pRefitEffects, 0x27); //ResourceLen
			WriteString(pRefitEffects, "\x41\x76\x61\x74\x61\x72\x2f\x6b\x61\x72\x74\x5f\x6e\x65\x77\x2f\x31\x32\x37\x33\x36\x35\x2f\x4d\x4f\x44\x45\x4c\x2f\x7a\x69\x73\x68\x65\x6e\x2e\x6e\x69\x66");
			Write8(pRefitEffects, 0x27); //EffectResLen
			WriteString(pRefitEffects, "\x41\x76\x61\x74\x61\x72\x2f\x6b\x61\x72\x74\x5f\x6e\x65\x77\x2f\x31\x32\x37\x33\x36\x35\x2f\x4d\x4f\x44\x45\x4c\x2f\x7a\x69\x73\x68\x65\x6e\x2e\x6e\x69\x66");
			Write8(pRefitEffects, 1); //Grade

			len = pRefitEffects - pLevelCfg;
			Set16(pLevelCfg, (WORD)len);
			pLevelCfg += len;
		}
		{ //RefitEffects
			BYTE* pRefitEffects = pLevelCfg;
			Write16(pRefitEffects, 0); //len

			Write16(pRefitEffects, 1); //EffectID
			Write8(pRefitEffects, 3); //Level
			Write32(pRefitEffects, 0); //Value1
			Write32(pRefitEffects, 0); //Value2
			Write8(pRefitEffects, 0x2c); //ResourceLen
			WriteString(pRefitEffects, "\x41\x76\x61\x74\x61\x72\x2f\x6b\x61\x72\x74\x5f\x6e\x65\x77\x2f\x31\x32\x37\x33\x36\x35\x2f\x4d\x4f\x44\x45\x4c\x2f\x64\x61\x70\x65\x6e\x74\x65\x78\x69\x61\x6f\x2e\x6e\x69\x66");
			Write8(pRefitEffects, 0x2c); //EffectResLen
			WriteString(pRefitEffects, "\x41\x76\x61\x74\x61\x72\x2f\x6b\x61\x72\x74\x5f\x6e\x65\x77\x2f\x31\x32\x37\x33\x36\x35\x2f\x4d\x4f\x44\x45\x4c\x2f\x64\x61\x70\x65\x6e\x74\x65\x78\x69\x61\x6f\x2e\x6e\x69\x66");
			Write8(pRefitEffects, 1); //Grade

			len = pRefitEffects - pLevelCfg;
			Set16(pLevelCfg, (WORD)len);
			pLevelCfg += len;
		}
		{ //RefitEffects
			BYTE* pRefitEffects = pLevelCfg;
			Write16(pRefitEffects, 0); //len

			Write16(pRefitEffects, 4); //EffectID
			Write8(pRefitEffects, 4); //Level
			Write32(pRefitEffects, 0x0fa1); //Value1
			Write32(pRefitEffects, 0x06d6); //Value2
			Write8(pRefitEffects, 0x24); //ResourceLen
			WriteString(pRefitEffects, "\x4b\x61\x72\x74\x41\x76\x61\x74\x61\x72\x45\x66\x66\x65\x63\x74\x2f\x53\x75\x70\x65\x72\x4a\x65\x74\x2f\x4a\x65\x74\x45\x66\x66\x2e\x6e\x69\x66");
			Write8(pRefitEffects, 0x2a); //EffectResLen
			WriteString(pRefitEffects, "\x41\x76\x61\x74\x61\x72\x2f\x6b\x61\x72\x74\x5f\x6e\x65\x77\x2f\x31\x32\x37\x33\x36\x35\x2f\x4d\x4f\x44\x45\x4c\x2f\x73\x74\x61\x72\x74\x73\x68\x6f\x77\x2e\x6e\x69\x66");
			Write8(pRefitEffects, 1); //Grade

			len = pRefitEffects - pLevelCfg;
			Set16(pLevelCfg, (WORD)len);
			pLevelCfg += len;
		}

		Write16(pLevelCfg, 0); //DressPoint
		Write16(pLevelCfg, 0); //CarLibraryCollectValue
		Write8(pLevelCfg, 0); //RefitModifyNum
		Write8(pLevelCfg, 0); //HasTurnModify
		Write32(pLevelCfg, 127365); //ShapeSuitID
		Write8(pLevelCfg, 0); //ConsumeNum
		len = pLevelCfg - pShapeRefitLegend;
		Set16(pShapeRefitLegend, (WORD)len);
		pShapeRefitLegend += len;
	}


	Write32(pShapeRefitLegend, 127365); //ShapeSuitID
	{ //MaxConsumInfo
		BYTE* pMaxConsumInfo = pShapeRefitLegend;
		Write16(pMaxConsumInfo, 0); //len

		Write32(pMaxConsumInfo, 0); //ItemID
		Write32(pMaxConsumInfo, 0); //ItemNum
		Write32(pMaxConsumInfo, 0); //ItemPeriod

		len = pMaxConsumInfo - pShapeRefitLegend;
		Set16(pShapeRefitLegend, (WORD)len);
		pShapeRefitLegend += len;
	}
	Write8(pShapeRefitLegend, 0); //LegendSkinType 传奇皮肤类型

	len = pShapeRefitLegend - p;
	Set16(p, (WORD)len);
	p += len;
	}

	len = p - buf;
	SendToClient(Client, 317, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}


void RequestWeRelayCommonCfg(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	ResponseWeRelayCommonCfg(Client);
}
void ResponseWeRelayCommonCfg(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	Write32(p, 0); //Uin
	{ //SeasonCfg
		BYTE* pSeasonCfg = p;
		Write16(pSeasonCfg, 0); //len

		Write32(pSeasonCfg, 0); //SeasonId
		Write32(pSeasonCfg, 0); //OpenDate
		Write32(pSeasonCfg, 0); //CloseDate
		Write32(pSeasonCfg, 0); //OpenDayNum
		Write32(pSeasonCfg, 0); //BroadCastContentLen
		Write32(pSeasonCfg, 0); //OpenTimeTipsLen

		const int MAX_SPEEDRALLY_OPEN_DAY_NUM = 1;
		for (size_t i = 0; i < MAX_SPEEDRALLY_OPEN_DAY_NUM; i++)
		{ //tDayOpenCfg
			BYTE* ptDayOpenCfg = pSeasonCfg;
			Write16(ptDayOpenCfg, 0); //len

			Write32(ptDayOpenCfg, 0); //DayID
			Write32(ptDayOpenCfg, 0); //OpenTimeNum
			/*
			for (size_t i = 0; i < MAX_OPEN_TIME_NUM; i++)
			{ //tOpenTimeCfg
				BYTE* ptOpenTimeCfg = ptDayOpenCfg;
				Write16(ptOpenTimeCfg, 0); //len

				Write32(ptOpenTimeCfg, 0); //OpenTime
				Write32(ptOpenTimeCfg, 0); //CloseTime
				Write32(ptOpenTimeCfg, 0); //TiyanOpenTime
				Write32(ptOpenTimeCfg, 0); //TiyanCloseTime

				len = ptOpenTimeCfg - ptDayOpenCfg;
				Set16(ptDayOpenCfg, (WORD)len);
				ptDayOpenCfg += len;
			}
			*/
			len = ptDayOpenCfg - pSeasonCfg;
			Set16(pSeasonCfg, (WORD)len);
			pSeasonCfg += len;
		}
		Write32(pSeasonCfg, 0); //LuckyBoxIndex
		Write32(pSeasonCfg, 0); //LuckyBoxPriority
		Write32(pSeasonCfg, 0); //LuckyBoxDayLimit

		len = pSeasonCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write32(p, 0); //RankNum
	/*
	for (size_t i = 0; i < n; i++)
	{ //RankAwardInfo
		BYTE* pRankAwardInfo = p;
		Write16(pRankAwardInfo, 0); //len

		Write32(pRankAwardInfo, 0); //RankType
		Write32(pRankAwardInfo, 0); //AwardNum
		for (size_t i = 0; i < n; i++)
		{ //BaseRankAwardToClient
			BYTE* pBaseRankAwardToClient = pRankAwardInfo;
			Write16(pBaseRankAwardToClient, 0); //len

			Write32(pBaseRankAwardToClient, 0); //Index
			Write32(pBaseRankAwardToClient, 0); //RankBegin
			Write32(pBaseRankAwardToClient, 0); //RankEnd
			{ //Award
				BYTE* pAward = pBaseRankAwardToClient;
				Write16(pAward, 0); //len

				Write32(pAward, 0); //Exp
				Write32(pAward, 0); //Money
				Write32(pAward, 0); //SuperMoney
				Write16(pAward, 0); //ItemNum
				for (size_t i = 0; i < n; i++)
				{ //ItemInfo
					BYTE* pItemInfo = pAward;
					Write16(pItemInfo, 0); //len

					Write32(pItemInfo, 0); //ItemID
					Write32(pItemInfo, 0); //ItemNum
					Write32(pItemInfo, 0); //AvailPeriod
					Write8(pItemInfo, 0); //Status
					WriteUn(pItemInfo, 0); //ObtainTime
					Write32(pItemInfo, 0); //OtherAttribute
					Write16(pItemInfo, 0); //ItemType

					len = pItemInfo - pAward;
					Set16(pAward, (WORD)len);
					pAward += len;
				}
				Write32(pAward, 0); //Coupons
				Write32(pAward, 0); //GuildPoint
				Write32(pAward, 0); //LuckMoney
				Write8(pAward, 0); //ExtendInfoNum
				for (size_t i = 0; i < n; i++)
				{ //ExtendInfoAward
					BYTE* pExtendInfoAward = pAward;
					Write16(pExtendInfoAward, 0); //len

					Write16(pExtendInfoAward, 0); //Key
					Write32(pExtendInfoAward, 0); //AddValue
					Write32(pExtendInfoAward, 0); //TotalValue
					Write8(pExtendInfoAward, 0); //ShowPriority
					Write16(pExtendInfoAward, 0); //BuyNeedScore
					Write8(pExtendInfoAward, 0); //OneMatchMaxNum

					len = pExtendInfoAward - pAward;
					Set16(pAward, (WORD)len);
					pAward += len;
				}
				Write32(pAward, 0); //SpeedCoin

				len = pAward - pBaseRankAwardToClient;
				Set16(pBaseRankAwardToClient, (WORD)len);
				pBaseRankAwardToClient += len;
			}
			Write32(pBaseRankAwardToClient, 0); //Status

			len = pBaseRankAwardToClient - pRankAwardInfo;
			Set16(pRankAwardInfo, (WORD)len);
			pRankAwardInfo += len;
		}

		len = pRankAwardInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	Write32(p, 0); //ActiveAwardNum
	/*
	for (size_t i = 0; i < n; i++)
	{ //ActiveAwardToClient
		BYTE* pActiveAwardToClient = p;
		Write16(pActiveAwardToClient, 0); //len

		Write32(pActiveAwardToClient, 0); //Index
		Write32(pActiveAwardToClient, 0); //ActiveValueLimit
		Write32(pActiveAwardToClient, 0); //RankLevLimit
		{ //Award
			BYTE* pAward = pActiveAwardToClient;
			Write16(pAward, 0); //len

			Write32(pAward, 0); //Exp
			Write32(pAward, 0); //Money
			Write32(pAward, 0); //SuperMoney
			Write16(pAward, 0); //ItemNum
			for (size_t i = 0; i < n; i++)
			{ //ItemInfo
				BYTE* pItemInfo = pAward;
				Write16(pItemInfo, 0); //len

				Write32(pItemInfo, 0); //ItemID
				Write32(pItemInfo, 0); //ItemNum
				Write32(pItemInfo, 0); //AvailPeriod
				Write8(pItemInfo, 0); //Status
				WriteUn(pItemInfo, 0); //ObtainTime
				Write32(pItemInfo, 0); //OtherAttribute
				Write16(pItemInfo, 0); //ItemType

				len = pItemInfo - pAward;
				Set16(pAward, (WORD)len);
				pAward += len;
			}
			Write32(pAward, 0); //Coupons
			Write32(pAward, 0); //GuildPoint
			Write32(pAward, 0); //LuckMoney
			Write8(pAward, 0); //ExtendInfoNum
			for (size_t i = 0; i < n; i++)
			{ //ExtendInfoAward
				BYTE* pExtendInfoAward = pAward;
				Write16(pExtendInfoAward, 0); //len

				Write16(pExtendInfoAward, 0); //Key
				Write32(pExtendInfoAward, 0); //AddValue
				Write32(pExtendInfoAward, 0); //TotalValue
				Write8(pExtendInfoAward, 0); //ShowPriority
				Write16(pExtendInfoAward, 0); //BuyNeedScore
				Write8(pExtendInfoAward, 0); //OneMatchMaxNum

				len = pExtendInfoAward - pAward;
				Set16(pAward, (WORD)len);
				pAward += len;
			}
			Write32(pAward, 0); //SpeedCoin

			len = pAward - pActiveAwardToClient;
			Set16(pActiveAwardToClient, (WORD)len);
			pActiveAwardToClient += len;
		}

		len = pActiveAwardToClient - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	Write32(p, 0); //CarTypeNum
	/*
	for (size_t i = 0; i < n; i++)
	{ //CarGuide
		BYTE* pCarGuide = p;
		Write16(pCarGuide, 0); //len

		Write32(pCarGuide, 0); //CarType
		Write32(pCarGuide, 0); //CarNum
		for (size_t i = 0; i < n; i++)
		{ //GuideCarInfo
			BYTE* pGuideCarInfo = pCarGuide;
			Write16(pGuideCarInfo, 0); //len

			Write32(pGuideCarInfo, 0); //CarID

			len = pGuideCarInfo - pCarGuide;
			Set16(pCarGuide, (WORD)len);
			pCarGuide += len;
		}

		len = pCarGuide - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	Write32(p, 0); //TiyanCarTypeNum
	/*
	for (size_t i = 0; i < n; i++)
	{ //TiyanCarGuide
		BYTE* pTiyanCarGuide = p;
		Write16(pTiyanCarGuide, 0); //len

		Write32(pTiyanCarGuide, 0); //CarType
		Write32(pTiyanCarGuide, 0); //CarNum
		for (size_t i = 0; i < n; i++)
		{ //GuideCarInfo
			BYTE* pGuideCarInfo = pTiyanCarGuide;
			Write16(pGuideCarInfo, 0); //len

			Write32(pGuideCarInfo, 0); //CarID

			len = pGuideCarInfo - pTiyanCarGuide;
			Set16(pTiyanCarGuide, (WORD)len);
			pTiyanCarGuide += len;
		}

		len = pTiyanCarGuide - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	{ //LuckyAwardToClient
		BYTE* pLuckyAwardToClient = p;
		Write16(pLuckyAwardToClient, 0); //len

		Write32(pLuckyAwardToClient, 0); //LuckBoxGet
		{ //Award
			BYTE* pAward = pLuckyAwardToClient;
			Write16(pAward, 0); //len

			Write32(pAward, 0); //Exp
			Write32(pAward, 0); //Money
			Write32(pAward, 0); //SuperMoney
			Write16(pAward, 0); //ItemNum
			/*
			for (size_t i = 0; i < n; i++)
			{ //ItemInfo
				BYTE* pItemInfo = pAward;
				Write16(pItemInfo, 0); //len

				Write32(pItemInfo, 0); //ItemID
				Write32(pItemInfo, 0); //ItemNum
				Write32(pItemInfo, 0); //AvailPeriod
				Write8(pItemInfo, 0); //Status
				Write32(pItemInfo, 0); //ObtainTime
				Write32(pItemInfo, 0); //OtherAttribute
				Write16(pItemInfo, 0); //ItemType

				len = pItemInfo - pAward;
				Set16(pAward, (WORD)len);
				pAward += len;
			}
			*/
			Write32(pAward, 0); //Coupons
			Write32(pAward, 0); //GuildPoint
			Write32(pAward, 0); //LuckMoney
			Write8(pAward, 0); //ExtendInfoNum
			/*
			for (size_t i = 0; i < n; i++)
			{ //ExtendInfoAward
				BYTE* pExtendInfoAward = pAward;
				Write16(pExtendInfoAward, 0); //len

				Write16(pExtendInfoAward, 0); //Key
				Write32(pExtendInfoAward, 0); //AddValue
				Write32(pExtendInfoAward, 0); //TotalValue
				Write8(pExtendInfoAward, 0); //ShowPriority
				Write16(pExtendInfoAward, 0); //BuyNeedScore
				Write8(pExtendInfoAward, 0); //OneMatchMaxNum

				len = pExtendInfoAward - pAward;
				Set16(pAward, (WORD)len);
				pAward += len;
			}
			*/
			Write32(pAward, 0); //SpeedCoin

			len = pAward - pLuckyAwardToClient;
			Set16(pLuckyAwardToClient, (WORD)len);
			pLuckyAwardToClient += len;
		}

		len = pLuckyAwardToClient - p;
		Set16(p, (WORD)len);
		p += len;
	}

	len = p - buf;
	SendToClient(Client, 24391, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}


void ResponseDoBagItemShowOperate(ClientNode* Client, USHORT OptType, USHORT ShowType, USHORT TabType,UINT ItemID)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	UINT TabItemTopNum = 0;
	UINT* Items = new UINT[500];//最大500个置顶
	if (OptType == 0x7 && ItemID != 0)//置顶
	{
		sql = "UPDATE Item SET OtherAttribute=?  WHERE Uin=? AND ItemID=?;";
		result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (result == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, 1);
			sqlite3_bind_int(stmt, 2, Client->Uin);
			sqlite3_bind_int(stmt, 3, ItemID);
			result = sqlite3_step(stmt);
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
	}
	else if (OptType == 0x2 && ItemID != 0)//取消置顶
	{
		sql = "UPDATE Item SET OtherAttribute=?  WHERE Uin=? AND ItemID=?;";
		result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (result == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, 0);
			sqlite3_bind_int(stmt, 2, Client->Uin);
			sqlite3_bind_int(stmt, 3, ItemID);
			result = sqlite3_step(stmt);
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
	}
	sql = "SELECT ItemID FROM Item WHERE Uin = ? and OtherAttribute=1;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Uin);
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			Items[TabItemTopNum]= sqlite3_column_int(stmt, 0);
			TabItemTopNum++;
			
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;


	Write16(p, 0); //ResultID
	Write32(p, Client->Uin); //Uin
	Write16(p, OptType); //OptType
	Write16(p, ShowType); //ShowType
	Write16(p, TabType); //TabType
	Write32(p, 1); //HasBagItemShowInfo
	//BagItemShowInfo
	BYTE* pBagItemShowInfo = p;
	Write16(pBagItemShowInfo, 0); //len
	Write32(pBagItemShowInfo, 6); //TabNum 6个页 赛车-宝石
	for (int i = 0; i < 6; i++)
	{
		BYTE* pBagTabItemTopInfo = pBagItemShowInfo;
		Write16(pBagTabItemTopInfo, 0); //len
		
		Write32(pBagTabItemTopInfo, TabItemTopNum); //ItemNum
		
		for (int j = 0; j < TabItemTopNum; j++)
		{
			Write32(pBagTabItemTopInfo, Items[j]);
		}
	
		len = pBagTabItemTopInfo - pBagItemShowInfo;
		Set16(pBagItemShowInfo, (WORD)len);
		pBagItemShowInfo += len;
	}
	Write32(pBagItemShowInfo, 0); //StarItemNum 星标数量
	//Write32(pBagItemShowInfo, 0); //StarItemID[]
	Write32(pBagItemShowInfo, 500); //TabTopItemNumMax
	Write32(pBagItemShowInfo, 0); //StarItemNumMax

	len = pBagItemShowInfo - p;
	Set16(p, (WORD)len);
	p += len;
	
	Write32(p, 0); //Para0
	Write32(p, 0); //ItemNum
	//Write32(p, 0); //ItemID[]

	len = p - buf;
	SendToClient(Client, 28412, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
	delete[] Items;
}

void RequestDoBagItemShowOperate(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body; WORD len;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	USHORT OptType = Read16(p);//0x0 打开背包 0x7置顶 0x2取消置顶 0x1 星标
	USHORT ShowType = Read16(p);
	USHORT TabType = Read16(p);
	int ItemID = Read32(p);
	//int ItemNum = Read32(p);
	
	ResponseDoBagItemShowOperate(Client, OptType, ShowType, TabType,ItemID);

}

void ResponseGetQuickRaceTimeRandMap(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	UINT* Maps = new UINT[3];
	char MapNum = 0;
	USHORT MapCount = 0;
	sql = "SELECT count(AllMap) FROM MapRand;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
			MapCount = sqlite3_column_int(stmt, 0);
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;


	sql = "SELECT AllMap FROM MapRand limit ?,3;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, rand()% MapCount);
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			Maps[MapNum] = sqlite3_column_int(stmt, 0);
			MapNum++;
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;
	Write32(p, Client->Uin); //Uin
	Write32(p, 0); //Time
	Write8(p, MapNum); //QuickRaceRandMapNum

	for (char i = 0; i < MapNum; i++)
	{
		Write32(p, Maps[i]);
	}
	Write8(p, 10); //QuickRaceRandMapRefreshTime
	Write16(p, 0); //SeasonMapNums

	len = p - buf;
	SendToClient(Client, 28379, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
	delete[] Maps;
}
void NotifyBeAddedAsFriend(ClientNode* Client,ClientNode* SrcClient)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	
	Write32(p, SrcClient->Uin); //SrcUin
	Write32(p, Client->Uin); //DstUin
	{ //SrcPlayerInfo
		BYTE* pSrcPlayerInfo = p;
		Write16(pSrcPlayerInfo, 0); //len

		Write8(pSrcPlayerInfo, 0); //Gender
		Write8(pSrcPlayerInfo, 0); //Country
		memset(pSrcPlayerInfo, 0, 17);
		
		memcpy(pSrcPlayerInfo, SrcClient->NickName, 17);
		
		pSrcPlayerInfo += 17;
		len = pSrcPlayerInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write16(p, 0); //WordLength
	Write8(p, 0); //Type
	Write16(p, 0); //Src

	len = p - buf;
	SendToClient(Client, 507, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}
void RequestAddFriend(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body; WORD len;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	UINT DstUin = Read32(p);
	ClientNode *DstClient=GetClient(DstUin);
	if (DstClient)
	{
		NotifyBeAddedAsFriend(DstClient, Client);
	}
	//UINT WordLength = Read32(p);
	//UCHAR Type = Read8(p);
	//USHORT Src = Read16(p);

}

void NotifyAddFriendResult(ClientNode* Client,USHORT result, ClientNode* SrcClient)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result2;

	if (result == 0)
	{
		BOOL haveFriend = 0;
		// 先查询是否有
		sql = "SELECT * FROM FriendInfo Where Uin=? and FriendUin=?;";
		result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (result == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, Client->Uin);
			sqlite3_bind_int(stmt, 2, SrcClient->Uin);
			if (sqlite3_step(stmt) == SQLITE_ROW)
			{
				haveFriend = 1;
			}
		}
		sqlite3_finalize(stmt);
		stmt = NULL;

		if (!haveFriend)
		{
			sql = "INSERT INTO FriendInfo VALUES(?, ?);";
			result2 = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
			if (result2 == SQLITE_OK) {
				sqlite3_bind_int(stmt, 1, Client->Uin);
				sqlite3_bind_int(stmt, 2, SrcClient->Uin);
				sqlite3_step(stmt);
			}
			sqlite3_finalize(stmt);
			stmt = NULL;
		}
	}

	Write16(p, result); //ResultID
	Write32(p, Client->Uin); //SrcUin
	Write32(p, SrcClient->Uin); //DstUin
	Write16(p, 0); //WordLength
	if (result == 0)
	{
		Write8(p, 8); //ReasonLen
		WriteString(p, "添加成功");
	}
	else
	{
		Write8(p, 16); //ReasonLen
		WriteString(p, "对方拒绝好友申请");
	}
	Write8(p, 0); //Type
	Write16(p, 0); //Src
	len = p - buf;
	SendToClient(Client, 508, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
	
	if (result == 0)
	{
		ResponseGetGroupFriendBaseInfo(Client, SrcClient->Uin,SrcClient->NickName);
	}

	
}
void AckBeAddedAsFriend(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body; WORD len;
	
	short ResultID = Read16(p);//0 同意 1不同意
	UINT SrcUin = Read32(p);
	UINT DstUin = Read32(p);
	//short WordLength = Read16(p);
	//UCHAR Type = Read8(p);
	//USHORT Src = Read16(p);
	ClientNode* DstClient = GetClient(DstUin);
	if (DstClient)
	{
		NotifyAddFriendResult(DstClient, ResultID, Client);
		NotifyAddFriendResult(Client, ResultID, DstClient);
	}
	
	
}


void NotifyOtherSkillStoneTakeEffect(ClientNode* Client,UINT SrcUin,UINT StoneID)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, SrcUin); //Uin
	Write32(p, StoneID); //StoneID

	len = p - buf;
	SendToClient(Client, 910, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}
void RequestReportSkillStoneTakeEffect(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body; WORD len;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	int StoneID = Read32(p);
	RoomNode* Room = GetRoom(Client->RoomID);
	if (!Room)
	{
		return;
	}
	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient && RoomClient != Client)
		{
			NotifyOtherSkillStoneTakeEffect(RoomClient, Uin, StoneID);
		}
	}
}
void NotifyBeEngaged(ClientNode* Client, ClientNode* SrcClient,UINT RingId)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	
	Write32(p, SrcClient->Uin); //SrcUin
	Write32(p, Client->Uin); //DstUin
	Write32(p, 0); //EngageType
	{ //SrcPlayerInfo
		BYTE* pSrcPlayerInfo = p;
		Write16(pSrcPlayerInfo, 0); //len

		Write8(pSrcPlayerInfo, 0); //Gender
		Write8(pSrcPlayerInfo, 0); //Country
		memset(pSrcPlayerInfo, 0, 17);
		
		memcpy(pSrcPlayerInfo, SrcClient->NickName, 17);
			
		pSrcPlayerInfo += 17;
		len = pSrcPlayerInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write16(p, 0); //WordLength
	Write32(p, RingId); //RingId

	len = p - buf;
	SendToClient(Client, 572, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void RequestEngage(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body; WORD len;

	UINT SrcUin = Read32(p);
	UINT Time = Read32(p);
	int EngageType = Read32(p);
	int RingID = Read32(p);
	UINT DstUin = Read32(p);
	ClientNode* DstClient = GetClient(DstUin);
	if (DstClient)
	{
		NotifyBeEngaged(DstClient, Client,RingID);
	}
	
	//char[] NickName[] = ReadString(p);
	//short WordLength = Read16(p);

}

void NotifyEngageResult(ClientNode* Client,USHORT resultID, ClientNode* SrcClient)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;

	
	Write16(p, resultID); //ResultID
	Write32(p, Client->Uin); //Uin
	Write32(p, SrcClient->Uin); //DstUin
	
	short namelen = strlen(SrcClient->NickName);
	Write8(p, namelen);
	memcpy(p, SrcClient->NickName, namelen);
	p += namelen;
	Write32(p, 0); //EngageType
	Write16(p, 0); //WordLength
	Write8(p, 0); //ReasonLen
	Write32(p, 0); //RingId
	Write32(p, 0); //EngageTime
	Write8(p, 0); //EngageFlag

	len = p - buf;
	SendToClient(Client, 573, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);


	if (resultID == 0)
	{
		
		// 先查询是否有
		if (Client->EngageUin!=0&&Client->EngageUin!= SrcClient->Uin)
		{//存在情侣且不同时
			sql = "UPDATE EngageInfo SET EngageUin=? WHERE Uin=?;";
			result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
			if (result == SQLITE_OK) {
				sqlite3_bind_int(stmt, 1, SrcClient->Uin);
				sqlite3_bind_int(stmt, 2, Client->Uin);
				result = sqlite3_step(stmt);
			}
			sqlite3_finalize(stmt);
			stmt = NULL;
		}
		else if(Client->EngageUin == 0)//不存在情侣
		{
			sql = "INSERT INTO EngageInfo VALUES(?, ?);";
			result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
			if (result == SQLITE_OK) {
				sqlite3_bind_int(stmt, 1, Client->Uin);
				sqlite3_bind_int(stmt, 2, SrcClient->Uin);
				sqlite3_step(stmt);
			}
			sqlite3_finalize(stmt);
			stmt = NULL;
			Client->EngageUin = SrcClient->Uin;
		}
	}
}
void AckBeEngaged(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body; WORD len;

	short ResultID = Read16(p);
	UINT SrcUin = Read32(p);
	UINT DstUin = Read32(p);
	//int EngageType = Read32(p);
	//short WordLength = Read16(p);
	ClientNode* DstClient = GetClient(DstUin);
	if (DstClient)
	{
		NotifyEngageResult(DstClient, ResultID, Client);
		NotifyEngageResult(Client, ResultID, DstClient);
	}
}


void RequestAddCharm(ClientNode* Client)
{
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	
	USHORT RandValue = 0;
	char Content[64] = { 0 };
	RandValue = (UINT)(rand() % 100);
	

	Client->Charm += RandValue;

	sql = "UPDATE BaseInfo SET Charm=? WHERE Uin=?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Charm);
		sqlite3_bind_int(stmt, 2, Client->Uin);
		result = sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	stmt = NULL;

	sprintf_s(Content, "\r\n\n\n/C01魅力值随机增加 %d 点\r\n\n\n\n\n", RandValue);
	ResponseStartGame(Client, Content);

}


void NotifyBeInvited(ClientNode* Client, ClientNode* SrcClient)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	RoomNode* Room = GetRoom(SrcClient->RoomID);
	if (!Room)
	{
		return;
	}
	Write32(p, SrcClient->Uin); //SrcUin
	memcpy(p, SrcClient->NickName, 17);
	p += 17;
	Write32(p, Client->Uin); //DstUin
	{ //PositionInfo
		BYTE* pPositionInfo = p;
		Write16(pPositionInfo, 0); //len

		Write8(pPositionInfo, 0); //ServerType
		Write16(pPositionInfo, 0); //Status
		Write32(pPositionInfo,Client->ServerID); //ServerID
		{ //RoomInfo
			BYTE* pRoomInfo = pPositionInfo;
			Write16(pRoomInfo, 0); //len

			Write16(pRoomInfo, Room->ID); //RoomID
			Write16(pRoomInfo,Room->BaseGameMode); //BaseGameMode
			Write16(pRoomInfo, Room->SubGameMode); //SubGameMode
			Write8(pRoomInfo, Room->CurrentPlayerNum); //CurrentPlayerNum
			Write8(pRoomInfo, 6); //TotalSeatNum
			Write8(pRoomInfo, 0); //Status
			Write32(pRoomInfo, Room->MapID); //MapID
			Write16(pRoomInfo,0); //Flag
			memcpy(pRoomInfo, Room->Name, MaxRoomName);
			pRoomInfo += 22;
			Write8(pRoomInfo, 0); //HasFBInfo
			
			Write8(pRoomInfo, 0); //SpeFlag
			Write32(pRoomInfo, 0); //RoomNo
			Write16(pRoomInfo, 0); //SvrId
			Write16(pRoomInfo, 0); //SceneID
			Write8(pRoomInfo, 0); //CurrentOBNum
			Write8(pRoomInfo, 0); //TotalOBNum
			Write8(pRoomInfo, 0); //SpecialActivityStatus
			Write8(pRoomInfo, 0); //AllowAutoStart
			Write32(pRoomInfo, 0); //Gender
			Write32(pRoomInfo, 0); //LocaleCode
			Write8(pRoomInfo, 0); //TalkRoomBGID
			Write8(pRoomInfo, 0); //SpecialActivityIDNum
			Write8(pRoomInfo, 0); //SpecialActivityInfoNum
			
			Write8(pRoomInfo, 0); //ValueNum
		
			Write8(pRoomInfo, 0); //ParaNum
		
			Write32(pRoomInfo, 0); //GSvrRoomNo
		

			len = pRoomInfo - pPositionInfo;
			Set16(pPositionInfo, (WORD)len);
			pPositionInfo += len;
		}
		Write8(pPositionInfo, 0); //StatusLen
		Write8(pPositionInfo, 1); //CanJoin

		len = pPositionInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write8(p, 0); //Type
	Write32(p, 0); //Para0
	Write32(p, 0); //Para1
	Write8(p, 0); //GVoiceRoomNameLen
	Write8(p, 0); //EquipedItemNum
	
	Write8(p, 0); //ReserveFlag
	Write8(p, 0); //Gender

	len = p - buf;
	SendToClient(Client, 569, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void RequestInvitePlayer(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body; WORD len;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	UINT DstUin = Read32(p);
	//bool Type = Read8(p);
	ClientNode* DstClient = GetClient(DstUin);
	if (DstClient)
	{
		NotifyBeInvited(DstClient, Client);
	}

}


void ResponseC2SearchKartAltas(ClientNode* Client,UINT DstUin)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, 0); //Result
	Write32(p, DstUin); //DstUin
	Write16(p, 0); //ItemNum
	for (size_t i = 0; i < 0; i++)
	{ //ItemInfoArray
		BYTE* pItemInfoArray = p;
		Write16(pItemInfoArray, 0); //len

		Write32(pItemInfoArray, 0); //ItemID
		Write32(pItemInfoArray, 0); //RefitCout
		{ //AltasCurKartAttr
			BYTE* pAltasCurKartAttr = pItemInfoArray;
			Write16(pAltasCurKartAttr, 0); //len

			Write32(pAltasCurKartAttr, 0); //Uin
			Write32(pAltasCurKartAttr, 0); //KartId
			Write32(pAltasCurKartAttr, 0); //RefitCout
			Write16(pAltasCurKartAttr, 0); //MaxFlags
			Write16(pAltasCurKartAttr, 0); //WWeight
			Write16(pAltasCurKartAttr, 0); //SpeedWeight
			Write16(pAltasCurKartAttr, 0); //JetWeight
			Write16(pAltasCurKartAttr, 0); //SJetWeight
			Write16(pAltasCurKartAttr, 0); //AccuWeight
			Write32(pAltasCurKartAttr, 0); //ShapeRefitCount
			Write32(pAltasCurKartAttr, 0); //KartHeadRefitItemID
			Write32(pAltasCurKartAttr, 0); //KartTailRefitItemID
			Write32(pAltasCurKartAttr, 0); //KartFlankRefitItemID
			Write32(pAltasCurKartAttr, 0); //KartTireRefitItemID
			{ //KartRefitExInfo
				BYTE* pKartRefitExInfo = pAltasCurKartAttr;
				Write16(pKartRefitExInfo, 0); //len

				Write8(pKartRefitExInfo, 0); //SpeedRefitStar
				Write8(pKartRefitExInfo, 0); //JetRefitStar
				Write8(pKartRefitExInfo, 0); //SJetRefitStar
				Write8(pKartRefitExInfo, 0); //AccuRefitStar
				Write8(pKartRefitExInfo, 0); //SpeedAddRatio
				Write8(pKartRefitExInfo, 0); //JetAddRatio
				Write8(pKartRefitExInfo, 0); //SJetAddRatio
				Write8(pKartRefitExInfo, 0); //AccuAddRatio

				len = pKartRefitExInfo - pAltasCurKartAttr;
				Set16(pAltasCurKartAttr, (WORD)len);
				pAltasCurKartAttr += len;
			}
			Write32(pAltasCurKartAttr, 0); //SecondRefitCount
			Write16(pAltasCurKartAttr, 0); //Speed2Weight
			Write16(pAltasCurKartAttr, 0); //DriftVecWeight
			Write16(pAltasCurKartAttr, 0); //AdditionalZSpeedWeight
			Write16(pAltasCurKartAttr, 0); //AntiCollisionWeight
			Write16(pAltasCurKartAttr, 0); //LuckyValue
			Write16(pAltasCurKartAttr, 0); //RefitLuckyValueMaxWeight
			Write32(pAltasCurKartAttr, 0); //ShapeSuitID
			Write8(pAltasCurKartAttr, 0); //LegendSuitLevel
			Write32(pAltasCurKartAttr, 0); //LegendSuitLevelChoice
			Write32(pAltasCurKartAttr, 0); //ShapeLegendSuitID

			len = pAltasCurKartAttr - pItemInfoArray;
			Set16(pItemInfoArray, (WORD)len);
			pItemInfoArray += len;
		}
		{ //AltasKartStoneGrooveInfo
			BYTE* pAltasKartStoneGrooveInfo = pItemInfoArray;
			Write16(pAltasKartStoneGrooveInfo, 0); //len

			Write32(pAltasKartStoneGrooveInfo, 0); //KartID
			Write32(pAltasKartStoneGrooveInfo, 0); //StoneGrooveNum
			for (size_t i = 0; i < 0; i++)
			{ //StoneGrooveInfo
				BYTE* pStoneGrooveInfo = pAltasKartStoneGrooveInfo;
				Write16(pStoneGrooveInfo, 0); //len

				Write32(pStoneGrooveInfo, 0); //StoneUseOccaType
				Write32(pStoneGrooveInfo, 0); //SkillStoneID

				len = pStoneGrooveInfo - pAltasKartStoneGrooveInfo;
				Set16(pAltasKartStoneGrooveInfo, (WORD)len);
				pAltasKartStoneGrooveInfo += len;
			}

			len = pAltasKartStoneGrooveInfo - pItemInfoArray;
			Set16(pItemInfoArray, (WORD)len);
			pItemInfoArray += len;
		}
		{ //AltasKartActiveLevelInfo
			BYTE* pAltasKartActiveLevelInfo = pItemInfoArray;
			Write16(pAltasKartActiveLevelInfo, 0); //len

			Write32(pAltasKartActiveLevelInfo, 0); //KartType
			Write32(pAltasKartActiveLevelInfo, 0); //ItemID
			Write32(pAltasKartActiveLevelInfo, 0); //ActiveLevel

			len = pAltasKartActiveLevelInfo - pItemInfoArray;
			Set16(pItemInfoArray, (WORD)len);
			pItemInfoArray += len;
		}

		len = pItemInfoArray - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write8(p, 0); //HasMoreInfo

	len = p - buf;
	SendToClient(Client, 13705, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}
void RequestC2SSearchKartAltas(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body; WORD len;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	UINT DstUin = Read32(p);
	ResponseC2SearchKartAltas(Client,DstUin);
}

void ResponseQuickRPC4(ClientNode* Client, UINT Uin, UINT Time, UINT Temp)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	{ //Head
		BYTE* pHead = p;
		Write16(pHead, 0); //len

		Write32(pHead, Uin); //Uin
		Write32(pHead, Time); //Time
		Write8(pHead, 0); //Version
		Write8(pHead, 0); //Compress
		Write8(pHead, 0); //OptLength

		len = pHead - p;
		Set16(p, (WORD)len);
		p += len;
	}

	memcpy(p, "\x00\x2c\x00\x28\x44\x69\x73\x70\x61\x74\x63\x68\x43\x6f\x52\x65\x73\x70\x6f\x6e\x73\x65\x00\x00\xf6\x00\x00\x00\x00\x00\x00\x31\x40\xf6\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 46);
	p += 29;
	Write32(p, Temp);
	p += 13;

	len = p - buf;
	SendToClient(Client, 24251, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);


}
void ResponseQuickRPC3(ClientNode* Client, UINT Uin, UINT Time, UINT Temp)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	{ //Head
		BYTE* pHead = p;
		Write16(pHead, 0); //len

		Write32(pHead, Uin); //Uin
		Write32(pHead, Time); //Time
		Write8(pHead, 0); //Version
		Write8(pHead, 0); //Compress
		Write8(pHead, 0); //OptLength

		len = pHead - p;
		Set16(p, (WORD)len);
		p += len;
	}
	memcpy(p, "\x0b\x17\x0b\x13\x44\x69\x73\x70\x61\x74\x63\x68\x43\x6f\x52\x65\x73\x70\x6f\x6e\x73\x65\x00\x00\xf6\x00\x00\x00\x00\x00\x00\x24\x40\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfd\x00\x00\x0a\xe6\xfa\x0b\x77\x65\x65\x6b\x65\x78\x70\x5f\x6d\x61\x78\xf6\x00\x00\x00\x00\x00\x82\xb4\x40\xfa\x09\x72\x65\x71\x62\x6c\x65\x76\x65\x6c\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfa\x06\x73\x6c\x65\x76\x65\x6c\xf6\x00\x00\x00\x00\x00\x00\x14\x40\xfa\x0d\x73\x6c\x65\x76\x65\x6c\x5f\x65\x78\x70\x63\x75\x72\xf6\x00\x00\x00\x00\x00\x7c\xaa\x40\xfa\x07\x42\x61\x73\x65\x43\x66\x67\xfd\x00\x00\x00\x56\xfa\x13\x4d\x61\x78\x4c\x65\x76\x65\x6c\x5f\x53\x6d\x61\x6c\x6c\x4c\x65\x76\x65\x6c\xf6\x00\x00\x00\x00\x00\x00\x14\x40\xfa\x11\x57\x65\x65\x6b\x4d\x61\x78\x54\x6f\x74\x61\x6c\x53\x63\x6f\x72\x65\xf6\x00\x00\x00\x00\x00\x40\x9f\x40\xfa\x11\x4d\x61\x78\x4c\x65\x76\x65\x6c\x5f\x42\x69\x67\x4c\x65\x76\x65\x6c\xf6\x00\x00\x00\x00\x00\x00\x18\x40\xfa\x08\x50\x6f\x77\x65\x72\x43\x66\x67\xfd\x00\x00\x02\xf7\xf6\x00\x00\x00\x00\x00\x60\x92\x40\xfd\x00\x00\x00\x6b\xfa\x0b\x73\x69\x6d\x70\x6c\x65\x5f\x64\x65\x73\x63\xfa\x18\xb8\xc4\xd7\xb0\xd0\xd2\xd4\xcb\xd6\xb5\xc9\xfa\xd0\xa7\xb5\xc8\xbc\xb6\xc9\xcf\xcf\xde\x2b\x31\xfa\x04\x6e\x61\x6d\x65\xfa\x12\xb8\xc4\xd7\xb0\xd0\xd2\xd4\xcb\xd6\xb5\xc9\xcf\xcf\xde\xcc\xd8\xc8\xa8\xfa\x04\x64\x65\x73\x63\xfa\x22\xb8\xc4\xd7\xb0\xd0\xd2\xd4\xcb\xd6\xb5\xc9\xfa\xd0\xa7\xb5\xc8\xbc\xb6\xc9\xcf\xcf\xde\x2b\x31\xa3\xa8\xb1\xe4\xce\xaa\x31\x36\xa3\xa9\xf6\x00\x00\x00\x00\x00\x54\x92\x40\xfd\x00\x00\x00\x23\xfb\x09\xfa\x0f\xbb\xf1\xb5\xc3\xb9\xa4\xd7\xca\xcc\xe1\xc9\xfd\x31\x30\x25\xfb\x0b\xfa\x08\xb9\xa4\xd7\xca\xcc\xd8\xc8\xa8\xfb\x0d\xfb\x0f\xf6\x00\x00\x00\x00\x00\x64\x92\x40\xfd\x00\x00\x00\x43\xfb\x09\xfa\x14\xc2\xe4\xba\xf3\xbb\xf1\xb5\xc3\xbc\xaf\xc6\xf8\xd0\xa7\xc2\xca\xcc\xe1\xc9\xfd\xfb\x0b\xfa\x0c\xbc\xaf\xc6\xf8\xd0\xa7\xc2\xca\xcc\xd8\xc8\xa8\xfb\x0d\xfa\x17\xc2\xe4\xba\xf3\xbb\xf1\xb5\xc3\xbc\xaf\xc6\xf8\xd0\xa7\xc2\xca\xcc\xe1\xc9\xfd\x31\x35\x25\xf6\x00\x00\x00\x00\x00\x58\x92\x40\xfd\x00\x00\x00\x6e\xfb\x09\xfa\x14\xb1\xdf\xbe\xb3\xb6\xd4\xbe\xd6\xbb\xf1\xb5\xc3\xb6\xee\xcd\xe2\xc8\xd9\xd3\xfe\xfb\x0b\xfa\x0c\xb1\xdf\xbe\xb3\xc8\xd9\xd3\xfe\xcc\xd8\xc8\xa8\xfb\x0d\xfa\x42\xc3\xbf\xbe\xd6\xb1\xdf\xbe\xb3\xb1\xc8\xc8\xfc\xbb\xf1\xb5\xc3\xb6\xee\xcd\xe2\xb5\xe3\xc8\xd9\xd3\xfe\xa3\xac\xcf\xed\xca\xdc\xb6\xe0\xb1\xb6\xbc\xd3\xb3\xc9\x28\xb3\xf5\xbc\xb6\x2b\x35\xa3\xac\xb8\xdf\xbc\xb6\x2b\x31\x30\xa3\xac\xd7\xa8\xd2\xb5\x2b\x31\x35\x29\xf6\x00\x00\x00\x00\x00\x4c\x92\x40\xfd\x00\x00\x00\x8c\xfb\x09\xfa\x14\xc3\xbf\xc8\xd5\xcf\xde\xb6\xa8\xb4\xce\xca\xfd\xbe\xad\xd1\xe9\xbc\xd3\xb3\xc9\xfb\x0b\xfa\x08\xbe\xad\xd1\xe9\xcc\xd8\xc8\xa8\xfb\x0d\xfa\x64\xc3\xbf\xc8\xd5\xcf\xde\xb6\xa8\xc7\xb0\x31\x35\xbe\xd6\xc8\xce\xd2\xe2\xb1\xc8\xc8\xfc\xa3\xac\xc3\xbf\xbe\xd6\xb6\xee\xcd\xe2\xbb\xf1\xb5\xc3\x24\x7b\x61\x64\x64\x65\x78\x70\x5f\x66\x69\x78\x6e\x75\x6d\x7d\xbe\xad\xd1\xe9\x28\xce\xb4\xcd\xea\xb3\xc9\xbb\xf1\xb5\xc3\x24\x7b\x61\x64\x64\x65\x78\x70\x5f\x66\x69\x78\x6e\x75\x6d\x5f\x6e\x6f\x74\x66\x69\x6e\x69\x73\x68\x65\x64\x7d\xbe\xad\xd1\xe9\x29\xf6\x00\x00\x00\x00\x00\x5c\x92\x40\xfd\x00\x00\x00\x4e\xfb\x09\xfa\x16\xc3\xbf\xc8\xd5\xc5\xc5\xce\xbb\xca\xd7\xb4\xce\xca\xa7\xb0\xdc\xb2\xbb\xb5\xf4\xb7\xd6\xfb\x0b\xfa\x10\xc5\xc5\xce\xbb\xc8\xfc\xb2\xbb\xb5\xf4\xb7\xd6\xcc\xd8\xc8\xa8\xfb\x0d\xfa\x1c\xc3\xbf\xc8\xd5\xc5\xc5\xce\xbb\xc8\xfc\xb6\xd4\xbe\xd6\xca\xd7\xb4\xce\xca\xa7\xb0\xdc\xb2\xbb\xb5\xf4\xb7\xd6\xf6\x00\x00\x00\x00\x00\x50\x92\x40\xfd\x00\x00\x00\x7c\xfb\x09\xfa\x14\xc3\xbf\xd6\xdc\xcf\xde\xb6\xa8\xb4\xce\xca\xfd\xba\xcf\xb3\xc9\xb1\xa3\xbb\xa4\xfb\x0b\xfa\x0c\xb1\xa6\xca\xaf\xba\xcf\xb3\xc9\xcc\xd8\xc8\xa8\xfb\x0d\xfa\x50\xc3\xbf\xd6\xdc\xcf\xde\xb6\xa8\xc9\xfa\xd0\xa7\x33\xb4\xce\xa3\xac\xb1\xa6\xca\xaf\xba\xcf\xb3\xc9\xca\xa7\xb0\xdc\xca\xb1\xa3\xac\xbf\xc9\xb1\xa3\xc1\xf4\x31\xb8\xf6\xd3\xc3\xc0\xb4\xba\xcf\xb3\xc9\xb5\xc4\xb5\xcd\xb5\xc8\xbc\xb6\xb1\xa6\xca\xaf\xa3\xa8\xd3\xc5\xcf\xc8\xca\xb9\xd3\xc3\xd7\xa3\xb8\xa3\xca\xaf\xa3\xa9\xfa\x0e\x72\x65\x71\x62\x6c\x65\x76\x65\x6c\x5f\x69\x6e\x66\x6f\xfd\x00\x00\x05\x17\xfa\x07\x54\x61\x73\x6b\x43\x66\x67\xfd\x00\x00\x01\xe5\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfd\x00\x00\x00\x7e\xfa\x0a\x6d\x5f\x75\x63\x54\x61\x73\x6b\x49\x44\xf6\x00\x00\x00\x00\x00\xda\xae\x40\xfa\x12\x6d\x5f\x75\x69\x54\x61\x73\x6b\x46\x69\x6e\x69\x73\x68\x4e\x75\x6d\x73\xf6\x00\x00\x00\x00\x00\x00\x3e\x40\xfa\x06\x53\x74\x61\x74\x75\x73\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfa\x14\x6d\x5f\x75\x69\x41\x6c\x72\x65\x61\x64\x79\x41\x77\x61\x72\x64\x4e\x75\x6d\x73\xf6\x00\x00\x00\x00\x00\x00\x3e\x40\xfa\x11\x6d\x5f\x75\x69\x41\x77\x61\x72\x64\x4d\x6f\x76\x65\x4e\x75\x6d\x73\xf6\x00\x00\x00\x00\x00\xc0\x82\x40\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfd\x00\x00\x00\x37\xfb\x22\xf6\x00\x00\x00\x00\x00\x6f\xb0\x40\xfb\x23\xf6\x00\x00\x00\x00\x00\x00\x14\x40\xfb\x24\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfb\x25\xf6\x00\x00\x00\x00\x00\x00\x14\x40\xfb\x26\xf6\x00\x00\x00\x00\x00\xc0\x82\x40\xf6\x00\x00\x00\x00\x00\x00\x08\x40\xfd\x00\x00\x00\x37\xfb\x22\xf6\x00\x00\x00\x00\x00\xdc\xae\x40\xfb\x23\xf6\x00\x00\x00\x00\x00\x00\x39\x40\xfb\x24\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfb\x25\xf6\x00\x00\x00\x00\x00\x00\x39\x40\xfb\x26\xf6\x00\x00\x00\x00\x00\xc0\x82\x40\xf6\x00\x00\x00\x00\x00\x00\x10\x40\xfd\x00\x00\x00\x37\xfb\x22\xf6\x00\x00\x00\x00\x00\xde\xae\x40\xfb\x23\xf6\x00\x00\x00\x00\x00\x00\x2e\x40\xfb\x24\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfb\x25\xf6\x00\x00\x00\x00\x00\x00\x2e\x40\xfb\x26\xf6\x00\x00\x00\x00\x00\xc0\x82\x40\xf6\x00\x00\x00\x00\x00\x00\x14\x40\xfd\x00\x00\x00\x37\xfb\x22\xf6\x00\x00\x00\x00\x00\xe0\xae\x40\xfb\x23\xf6\x00\x00\x00\x00\x00\x00\x89\x40\xfb\x24\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfb\x25\xf6\x00\x00\x00\x00\x00\x00\x89\x40\xfb\x26\xf6\x00\x00\x00\x00\x00\xc0\x82\x40\xf6\x00\x00\x00\x00\x00\x00\x18\x40\xfd\x00\x00\x00\x37\xfb\x22\xf6\x00\x00\x00\x00\x00\xe2\xae\x40\xfb\x23\xf6\x00\x00\x00\x00\x00\x00\x2e\x40\xfb\x24\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfb\x25\xf6\x00\x00\x00\x00\x00\x00\x2e\x40\xfb\x26\xf6\x00\x00\x00\x00\x00\xc0\x82\x40\xfa\x04\x6c\x63\x66\x67\xfd\x00\x00\x03\x19\xfb\x21\xfd\x00\x00\x01\x9e\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfd\x00\x00\x00\x37\xfb\x22\xf6\x00\x00\x00\x00\x00\xda\xae\x40\xfb\x23\xf6\x00\x00\x00\x00\x00\x00\x3e\x40\xfb\x24\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfb\x25\xf6\x00\x00\x00\x00\x00\x00\x3e\x40\xfb\x26\xf6\x00\x00\x00\x00\x00\xc0\x82\x40\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfd\x00\x00\x00\x37\xfb\x22\xf6\x00\x00\x00\x00\x00\x6f\xb0\x40\xfb\x23\xf6\x00\x00\x00\x00\x00\x00\x14\x40\xfb\x24\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfb\x25\xf6\x00\x00\x00\x00\x00\x00\x14\x40\xfb\x26\xf6\x00\x00\x00\x00\x00\xc0\x82\x40\xf6\x00\x00\x00\x00\x00\x00\x08\x40\xfd\x00\x00\x00\x37\xfb\x22\xf6\x00\x00\x00\x00\x00\xdc\xae\x40\xfb\x23\xf6\x00\x00\x00\x00\x00\x00\x39\x40\xfb\x24\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfb\x25\xf6\x00\x00\x00\x00\x00\x00\x39\x40\xfb\x26\xf6\x00\x00\x00\x00\x00\xc0\x82\x40\xf6\x00\x00\x00\x00\x00\x00\x10\x40\xfd\x00\x00\x00\x37\xfb\x22\xf6\x00\x00\x00\x00\x00\xde\xae\x40\xfb\x23\xf6\x00\x00\x00\x00\x00\x00\x2e\x40\xfb\x24\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfb\x25\xf6\x00\x00\x00\x00\x00\x00\x2e\x40\xfb\x26\xf6\x00\x00\x00\x00\x00\xc0\x82\x40\xf6\x00\x00\x00\x00\x00\x00\x14\x40\xfd\x00\x00\x00\x37\xfb\x22\xf6\x00\x00\x00\x00\x00\xe0\xae\x40\xfb\x23\xf6\x00\x00\x00\x00\x00\x00\x89\x40\xfb\x24\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfb\x25\xf6\x00\x00\x00\x00\x00\x00\x89\x40\xfb\x26\xf6\x00\x00\x00\x00\x00\xc0\x82\x40\xf6\x00\x00\x00\x00\x00\x00\x18\x40\xfd\x00\x00\x00\x37\xfb\x22\xf6\x00\x00\x00\x00\x00\xe2\xae\x40\xfb\x23\xf6\x00\x00\x00\x00\x00\x00\x2e\x40\xfb\x24\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfb\x25\xf6\x00\x00\x00\x00\x00\x00\x2e\x40\xfb\x26\xf6\x00\x00\x00\x00\x00\xc0\x82\x40\xfa\x05\x70\x6f\x77\x65\x72\xfd\x00\x00\x00\x24\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xf6\x00\x00\x00\x00\x00\x60\x92\x40\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xf6\x00\x00\x00\x00\x00\x4c\x92\x40\xfa\x0d\x73\x74\x61\x72\x5f\x65\x78\x70\x74\x6f\x74\x61\x6c\xf6\x00\x00\x00\x00\x00\x94\xd1\x40\xfa\x0b\x73\x74\x61\x72\x5f\x65\x78\x70\x63\x66\x67\xfd\x00\x00\x00\x87\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfd\x00\x00\x00\x15\xfa\x0a\x75\x70\x5f\x6e\x65\x65\x64\x65\x78\x70\xf6\x00\x00\x00\x00\x00\x20\xac\x40\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfd\x00\x00\x00\x0b\xfb\x2b\xf6\x00\x00\x00\x00\x00\x20\xac\x40\xf6\x00\x00\x00\x00\x00\x00\x08\x40\xfd\x00\x00\x00\x0b\xfb\x2b\xf6\x00\x00\x00\x00\x00\x20\xac\x40\xf6\x00\x00\x00\x00\x00\x00\x10\x40\xfd\x00\x00\x00\x0b\xfb\x2b\xf6\x00\x00\x00\x00\x00\x20\xac\x40\xf6\x00\x00\x00\x00\x00\x00\x14\x40\xfd\x00\x00\x00\x0b\xfb\x2b\xf6\x00\x00\x00\x00\x00\x20\xac\x40\xfa\x0f\x70\x6f\x69\x6e\x74\x5f\x77\x65\x65\x6b\x6c\x69\x6d\x69\x74\xf6\x00\x00\x00\x00\x00\x82\xb4\x40\xfa\x12\x43\x6f\x6d\x6d\x6f\x6e\x41\x77\x61\x72\x64\x42\x6f\x78\x54\x79\x70\x65\xf6\x00\x00\x00\x00\x00\xc0\x5c\x40\xfa\x0d\x61\x64\x64\x65\x78\x70\x5f\x66\x69\x78\x6e\x75\x6d\xf6\x00\x00\x00\x00\x00\xe0\x85\x40\xfa\x19\x61\x64\x64\x65\x78\x70\x5f\x66\x69\x78\x6e\x75\x6d\x5f\x6e\x6f\x74\x66\x69\x6e\x69\x73\x68\x65\x64\xf6\x00\x00\x00\x00\x00\x80\x71\x40\xfa\x05\x6c\x69\x6d\x69\x74\xfd\x00\x00\x00\x14\xfa\x09\x75\x73\x65\x72\x6c\x65\x76\x65\x6c\xf6\x00\x00\x00\x00\x00\x00\x59\x40\xfa\x0b\x50\x6f\x77\x65\x72\x53\x74\x61\x74\x75\x73\xfd\x00\x00\x01\xaf\xf6\x00\x00\x00\x00\x00\x60\x92\x40\xfd\x00\x00\x00\x55\xfa\x04\x6e\x75\x6d\x73\xf6\x00\x00\x00\x00\x00\x00\x26\x40\xfa\x0c\x70\x6f\x77\x65\x72\x5f\x62\x6c\x65\x76\x65\x6c\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfb\x0b\xfb\x0c\xfb\x09\xfb\x0a\xfa\x06\x73\x74\x61\x74\x75\x73\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfa\x07\x6d\x61\x78\x6e\x75\x6d\x73\xf6\x00\x00\x00\x00\x00\x00\xf0\xbf\xfb\x0d\xfb\x0e\xf6\x00\x00\x00\x00\x00\x54\x92\x40\xfd\x00\x00\x00\x22\xfb\x34\xf6\x00\x00\x00\x00\x00\x00\x10\x40\xfb\x0b\xfb\x10\xfb\x09\xfb\x0f\xfb\x35\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0d\xfb\x0f\xf6\x00\x00\x00\x00\x00\x64\x92\x40\xfd\x00\x00\x00\x22\xfb\x34\xf6\x00\x00\x00\x00\x00\x00\x18\x40\xfb\x0b\xfb\x12\xfb\x09\xfb\x11\xfb\x35\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0d\xfb\x13\xf6\x00\x00\x00\x00\x00\x58\x92\x40\xfd\x00\x00\x00\x22\xfb\x34\xf6\x00\x00\x00\x00\x00\x00\x14\x40\xfb\x0b\xfb\x15\xfb\x09\xfb\x14\xfb\x35\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0d\xfb\x16\xf6\x00\x00\x00\x00\x00\x4c\x92\x40\xfd\x00\x00\x00\x38\xfb\x33\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfb\x34\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfb\x0b\xfb\x18\xfb\x09\xfb\x17\xfb\x35\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfb\x36\xf6\x00\x00\x00\x00\x00\x00\x2e\x40\xfb\x0d\xfb\x19\xf6\x00\x00\x00\x00\x00\x5c\x92\x40\xfd\x00\x00\x00\x22\xfb\x34\xf6\x00\x00\x00\x00\x00\x00\x08\x40\xfb\x0b\xfb\x1b\xfb\x09\xfb\x1a\xfb\x35\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0d\xfb\x1c\xf6\x00\x00\x00\x00\x00\x50\x92\x40\xfd\x00\x00\x00\x38\xfb\x33\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x34\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfb\x0b\xfb\x1e\xfb\x09\xfb\x1d\xfb\x35\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfb\x36\xf6\x00\x00\x00\x00\x00\x00\x08\x40\xfb\x0d\xfb\x1f\xfa\x07\x77\x65\x65\x6b\x65\x78\x70\xf6\x00\x00\x00\x00\x00\x00\x5a\x40\xfa\x06\x62\x6c\x65\x76\x65\x6c\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfa\x0e\x73\x6c\x65\x76\x65\x6c\x5f\x65\x78\x70\x6e\x65\x65\x64\xf6\x00\x00\x00\x00\x00\x20\xac\x40\x00\x00\x00\x00", 2841);
	p += 29;
	Write32(p, Temp);
	p += 2808;

	len = p - buf;
	SendToClient(Client, 24251, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);


}
void ResponseQuickRPC2(ClientNode* Client, UINT Uin, UINT Time, UINT Temp)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	{ //Head
		BYTE* pHead = p;
		Write16(pHead, 0); //len

		Write32(pHead, Uin); //Uin
		Write32(pHead, Time); //Time
		Write8(pHead, 0); //Version
		Write8(pHead, 0); //Compress
		Write8(pHead, 0); //OptLength

		len = pHead - p;
		Set16(p, (WORD)len);
		p += len;
	}
	memcpy(p, "\x00\x2f\x00\x2b\x44\x69\x73\x70\x61\x74\x63\x68\x43\x6f\x52\x65\x73\x70\x6f\x6e\x73\x65\x00\x00\xf6\x00\x00\x00\x00\x00\x00\x1c\x40\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfd\x00\x00\x00\x00\x00\x00", 49);
	p += 29;
	Write32(p, Temp);
	p += 16;
	len = p - buf;
	SendToClient(Client, 24251, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);


}
void ResponseQuickRPC(ClientNode* Client, UINT Uin, UINT Time, UINT Temp)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	{ //Head
		BYTE* pHead = p;
		Write16(pHead, 0); //len

		Write32(pHead, Uin); //Uin
		Write32(pHead, Time); //Time
		Write8(pHead, 0); //Version
		Write8(pHead, 0); //Compress
		Write8(pHead, 0); //OptLength

		len = pHead - p;
		Set16(p, (WORD)len);
		p += len;
	}
	memcpy(p, "\x03\x95\x03\x91\x44\x69\x73\x70\x61\x74\x63\x68\x43\x6f\x52\x65\x73\x70\x6f\x6e\x73\x65\x00\x00\xf6\x00\x00\x00\x00\x00\x00\x08\x40\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfd\x00\x00\x03\x64\xfa\x18\x43\x6f\x6c\x6c\x65\x63\x74\x56\x61\x6c\x75\x65\x49\x6e\x4c\x65\x76\x65\x6c\x54\x6f\x74\x61\x6c\xf6\x00\x00\x00\x00\x00\x88\xc3\x40\xfa\x0c\x43\x6f\x6c\x6c\x65\x63\x74\x56\x61\x6c\x75\x65\xf6\x00\x00\x00\x00\x00\x75\xbf\x40\xfa\x07\x50\x6f\x73\x49\x6e\x66\x6f\xfd\x00\x00\x00\xc6\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xf6\x00\x00\x00\x00\x40\xdb\xf2\x40\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xf6\x00\x00\x00\x00\xc0\x27\xf2\x40\xf6\x00\x00\x00\x00\x00\x00\x08\x40\xf6\x00\x00\x00\x00\x00\xc5\xd3\x40\xf6\x00\x00\x00\x00\x00\x00\x10\x40\xf6\x00\x00\x00\x00\x00\x41\xd1\x40\xf6\x00\x00\x00\x00\x00\x00\x14\x40\xf6\x00\x00\x00\x00\x10\xe0\xf8\x40\xf6\x00\x00\x00\x00\x00\x00\x18\x40\xf6\x00\x00\x00\x00\x30\x5c\xf7\x40\xf6\x00\x00\x00\x00\x00\x00\x1c\x40\xf6\x00\x00\x00\x00\xf0\x6c\xf8\x40\xf6\x00\x00\x00\x00\x00\x00\x20\x40\xf6\x00\x00\x00\x00\x90\xfb\xf4\x40\xf6\x00\x00\x00\x00\x00\x00\x22\x40\xf6\x00\x00\x00\x00\x20\xc2\xf0\x40\xf6\x00\x00\x00\x00\x00\x00\x24\x40\xf6\x00\x00\x00\x00\x60\x1d\xfc\x40\xf6\x00\x00\x00\x00\x00\x00\x26\x40\xf6\x00\x00\x00\x00\xa0\x27\xf2\x40\xfa\x1a\x48\x69\x73\x74\x6f\x72\x79\x48\x69\x67\x68\x65\x73\x74\x43\x6f\x6c\x6c\x65\x63\x74\x56\x61\x6c\x75\x65\xf6\x00\x00\x00\x00\x00\x75\xbf\x40\xfa\x05\x54\x31\x6e\x75\x6d\xf6\x00\x00\x00\x00\x00\x00\x10\x40\xfa\x05\x54\x32\x6e\x75\x6d\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfa\x05\x54\x33\x6e\x75\x6d\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfa\x09\x46\x6c\x61\x67\x56\x61\x6c\x75\x65\xfd\x00\x00\x00\x36\xf6\x00\x00\x00\x00\x00\x00\x3d\x40\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xf6\x00\x00\x00\x00\x00\x00\x3b\x40\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xf6\x00\x00\x00\x00\x00\x00\x3c\x40\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfa\x07\x53\x75\x69\x74\x6e\x75\x6d\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfa\x07\x42\x61\x73\x65\x43\x66\x67\xfd\x00\x00\x01\x0c\xfa\x0e\x41\x6c\x6c\x6f\x77\x50\x6c\x61\x63\x65\x54\x50\x6f\x73\xfd\x00\x00\x00\x5a\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xf6\x00\x00\x00\x00\x00\x00\x1c\x40\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xf6\x00\x00\x00\x00\x00\x00\x20\x40\xf6\x00\x00\x00\x00\x00\x00\x08\x40\xf6\x00\x00\x00\x00\x00\x00\x22\x40\xf6\x00\x00\x00\x00\x00\x00\x10\x40\xf6\x00\x00\x00\x00\x00\x00\x24\x40\xf6\x00\x00\x00\x00\x00\x00\x14\x40\xf6\x00\x00\x00\x00\x00\x00\x26\x40\xfa\x09\x53\x6e\x75\x6d\x54\x6f\x74\x61\x6c\xf6\x00\x00\x00\x00\x00\x80\x5d\x40\xfa\x14\x4d\x61\x78\x43\x6f\x6c\x6c\x65\x63\x74\x56\x61\x6c\x75\x65\x4c\x65\x76\x65\x6c\xf6\x00\x00\x00\x00\x00\x00\x24\x40\xfa\x0c\x53\x75\x69\x74\x6e\x75\x6d\x54\x6f\x74\x61\x6c\xf6\x00\x00\x00\x00\x00\x00\x43\x40\xfa\x0a\x54\x32\x6e\x75\x6d\x54\x6f\x74\x61\x6c\xf6\x00\x00\x00\x00\x00\x80\x51\x40\xfa\x0a\x54\x31\x6e\x75\x6d\x54\x6f\x74\x61\x6c\xf6\x00\x00\x00\x00\x00\x00\x49\x40\xfa\x09\x41\x6e\x75\x6d\x54\x6f\x74\x61\x6c\xf6\x00\x00\x00\x00\x00\xf8\x81\x40\xfa\x0a\x54\x33\x6e\x75\x6d\x54\x6f\x74\x61\x6c\xf6\x00\x00\x00\x00\x00\x00\x22\x40\xfa\x11\x43\x6f\x6c\x6c\x65\x63\x74\x56\x61\x6c\x75\x65\x4c\x65\x76\x65\x6c\xf6\x00\x00\x00\x00\x00\x00\x20\x40\xfa\x04\x41\x6e\x75\x6d\xf6\x00\x00\x00\x00\x00\x00\x30\x40\xfa\x0a\x46\x6f\x72\x62\x69\x64\x53\x68\x6f\x77\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfa\x05\x6f\x74\x68\x65\x72\xf6\x00\x00\x00\x00\x00\x00\x42\x40\xfa\x07\x53\x68\x6f\x77\x4e\x75\x6d\xf6\x00\x00\x00\x00\x00\x00\x26\x40\xfa\x13\x43\x6f\x6c\x6c\x65\x63\x74\x56\x61\x6c\x75\x65\x49\x6e\x4c\x65\x76\x65\x6c\xf6\x00\x00\x00\x00\x00\x75\xbf\x40\xfa\x04\x53\x6e\x75\x6d\xf6\x00\x00\x00\x00\x00\x00\x10\x40\x35\x00\x00\x00", 919);
	p += 29;
	Write32(p, Temp);
	p += 886;

	len = p - buf;
	SendToClient(Client, 24251, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);


}

void RequestQuickRPC(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body; WORD len;
	UINT temp1 = 0, temp2 = 0, temp3 = 0;
	//Head
	BYTE* pHead = p;
	len = Read16(pHead);

	UINT Uin = Read32(pHead);
	UINT Time = Read32(pHead);
	BYTE Version = Read8(pHead);
	BYTE Compress = Read8(pHead);
	BYTE OptLength = Read8(pHead);

	p += len;


	//Body
	//BYTE* pBody = p;
	len = Read16(p);

	if (len == 0x2a)//边境
	{
		NotifyBorderGameCondition(Client);
	}
	else if (len == 0x28)
	{
		//车库1
		USHORT MsgLen = Read16(p);

		p += 32;
		temp1 = Read32(p);//序列号?不一致会导致环境异常报错
		//序列号在0x00 0x00 0xf6后面 4字节0+后四字节未知序列号 
		ResponseQuickRPC(Client, Uin, Time, temp1);
	}
	else if (len == 0x31)
	{
		//车库2
		USHORT MsgLen = Read16(p);

		p += 32;
		temp1 = Read32(p);//序列号?不一致会导致环境异常报错
		ResponseQuickRPC2(Client, Uin, Time, temp1);
	}
	else if (len == 0x34)
	{
		//查看别人车库 
		USHORT MsgLen = Read16(p);

		p += 35;
		temp1 = Read32(p);//序列号?不一致会导致环境异常报错
		ResponseQuickRPC3(Client, Uin, Time, temp1);
	}
	else if (len == 0x2e)
	{
		//赛道挑战图标
		USHORT MsgLen = Read16(p);
		p += 38;
		temp1 = Read32(p);//序列号?不一致会导致环境异常报错
		ResponseQuickRPC4(Client, Uin, Time, temp1);
	}
	else if (len == 0x33)
	{
		//赛道挑战打开面板
		USHORT MsgLen = Read16(p);
		p += 34;
		temp1 = Read32(p);//序列号?不一致会导致环境异常报错
		//需要先回复ResponsePreGetCommonBoxAward 24465消息才可以收到该24251消息
		//"\x05\xe7\x05\xe3\x44\x69\x73\x70\x61\x74\x63\x68\x43\x6f\x52\x65\x73\x70\x6f\x6e\x73\x65\x00\x00\xf6\x00\x00\x00\x00\x00\x00\x37\x40\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfd\x00\x00\x05\xb6\xfa\x09\x43\x6c\x6f\x73\x65\x54\x69\x6d\x65\xf6\x00\x00\xc0\xbf\x67\x28\xd9\x41\xfa\x10\x48\x61\x73\x4d\x61\x70\x52\x65\x63\x6f\x72\x64\x44\x61\x74\x61\xf8\xfa\x07\x6d\x61\x70\x69\x6e\x66\x6f\xfd\x00\x00\x05\x1f\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfd\x00\x00\x01\x2e\xfa\x05\x4d\x61\x70\x49\x44\xf6\x00\x00\x00\x00\x00\xb0\x78\x40\xfa\x0d\x4d\x61\x70\x52\x65\x63\x6f\x72\x64\x54\x69\x6d\x65\xf6\x00\x00\x00\x00\xf0\x19\xf7\x40\xfa\x0a\x41\x73\x73\x65\x73\x73\x49\x6e\x66\x6f\xfd\x00\x00\x00\x72\xfa\x03\x4e\x75\x6d\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfa\x0a\x41\x73\x73\x65\x73\x73\x54\x79\x70\x65\xf6\x00\x00\x00\x00\x00\x00\x37\x40\xfa\x03\x4d\x73\x67\xfa\x19\xcd\xea\xb3\xc9\xb1\xc8\xc8\xfc\xb2\xa2\xca\xb9\xd3\xc3\x57\x43\x57\xc5\xe7\x7b\x74\x63\x7d\xb4\xce\xfa\x07\x4d\x73\x67\x47\x61\x6d\x65\xfa\x11\xca\xb9\xd3\xc3\x57\x43\x57\xc5\xe7\x7b\x74\x63\x7d\xb4\xce\xa3\xba\xfa\x08\x69\x73\x66\x69\x6e\x69\x73\x68\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfa\x08\x53\x74\x61\x72\x49\x6e\x66\x6f\xfd\x00\x00\x00\x74\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfd\x00\x00\x00\x1e\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfa\x08\x62\x61\x73\x65\x74\x69\x6d\x65\xf6\x00\x00\x00\x00\xf0\x01\xfb\x40\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfd\x00\x00\x00\x16\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0e\xf6\x00\x00\x00\x00\xf0\x07\xfa\x40\xf6\x00\x00\x00\x00\x00\x00\x08\x40\xfd\x00\x00\x00\x16\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0e\xf6\x00\x00\x00\x00\xf0\x0d\xf9\x40\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfd\x00\x00\x00\xb9\xfb\x03\xf6\x00\x00\x00\x00\x00\xe0\x6f\x40\xfb\x04\xf6\x00\x00\x00\x00\x70\xf3\xf6\x40\xfb\x05\xfd\x00\x00\x00\x29\xfb\x06\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfb\x07\xf6\x00\x00\x00\x00\x00\x00\x37\x40\xfb\x08\xfb\x09\xfb\x0a\xfb\x0b\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0d\xfd\x00\x00\x00\x6c\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfd\x00\x00\x00\x16\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0e\xf6\x00\x00\x00\x00\x70\xdb\xfa\x40\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfd\x00\x00\x00\x16\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0e\xf6\x00\x00\x00\x00\x70\xe1\xf9\x40\xf6\x00\x00\x00\x00\x00\x00\x08\x40\xfd\x00\x00\x00\x16\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0e\xf6\x00\x00\x00\x00\x70\xe7\xf8\x40\xf6\x00\x00\x00\x00\x00\x00\x08\x40\xfd\x00\x00\x00\xb9\xfb\x03\xf6\x00\x00\x00\x00\x00\x00\x65\x40\xfb\x04\xf6\x00\x00\x00\x00\x00\x00\xf0\xbf\xfb\x05\xfd\x00\x00\x00\x29\xfb\x06\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfb\x07\xf6\x00\x00\x00\x00\x00\x00\x37\x40\xfb\x08\xfb\x09\xfb\x0a\xfb\x0b\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0d\xfd\x00\x00\x00\x6c\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfd\x00\x00\x00\x16\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0e\xf6\x00\x00\x00\x00\xc0\x44\x09\x41\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfd\x00\x00\x00\x16\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0e\xf6\x00\x00\x00\x00\xc0\xc7\x08\x41\xf6\x00\x00\x00\x00\x00\x00\x08\x40\xfd\x00\x00\x00\x16\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0e\xf6\x00\x00\x00\x00\xc0\x4a\x08\x41\xf6\x00\x00\x00\x00\x00\x00\x10\x40\xfd\x00\x00\x00\xb9\xfb\x03\xf6\x00\x00\x00\x00\x00\x00\x70\x40\xfb\x04\xf6\x00\x00\x00\x00\x80\x2b\xf9\x40\xfb\x05\xfd\x00\x00\x00\x29\xfb\x06\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfb\x07\xf6\x00\x00\x00\x00\x00\x00\x37\x40\xfb\x08\xfb\x09\xfb\x0a\xfb\x0b\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0d\xfd\x00\x00\x00\x6c\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfd\x00\x00\x00\x16\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0e\xf6\x00\x00\x00\x00\x80\x13\xfd\x40\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfd\x00\x00\x00\x16\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0e\xf6\x00\x00\x00\x00\x80\x19\xfc\x40\xf6\x00\x00\x00\x00\x00\x00\x08\x40\xfd\x00\x00\x00\x16\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0e\xf6\x00\x00\x00\x00\x80\x1f\xfb\x40\xf6\x00\x00\x00\x00\x00\x00\x14\x40\xfd\x00\x00\x00\xb9\xfb\x03\xf6\x00\x00\x00\x00\x00\x60\x6d\x40\xfb\x04\xf6\x00\x00\x00\x00\x00\x00\xf0\xbf\xfb\x05\xfd\x00\x00\x00\x29\xfb\x06\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfb\x07\xf6\x00\x00\x00\x00\x00\x00\x37\x40\xfb\x08\xfb\x09\xfb\x0a\xfb\x0b\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0d\xfd\x00\x00\x00\x6c\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfd\x00\x00\x00\x16\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0e\xf6\x00\x00\x00\x00\x80\x4f\x02\x41\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfd\x00\x00\x00\x16\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0e\xf6\x00\x00\x00\x00\x80\xd2\x01\x41\xf6\x00\x00\x00\x00\x00\x00\x08\x40\xfd\x00\x00\x00\x16\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0e\xf6\x00\x00\x00\x00\x80\x55\x01\x41\xf6\x00\x00\x00\x00\x00\x00\x18\x40\xfd\x00\x00\x00\xb9\xfb\x03\xf6\x00\x00\x00\x00\x00\xc0\x74\x40\xfb\x04\xf6\x00\x00\x00\x00\xa0\xdc\xf3\x40\xfb\x05\xfd\x00\x00\x00\x29\xfb\x06\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfb\x07\xf6\x00\x00\x00\x00\x00\x00\x37\x40\xfb\x08\xfb\x09\xfb\x0a\xfb\x0b\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0d\xfd\x00\x00\x00\x6c\xf6\x00\x00\x00\x00\x00\x00\xf0\x3f\xfd\x00\x00\x00\x16\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0e\xf6\x00\x00\x00\x00\xa0\xc4\xf7\x40\xf6\x00\x00\x00\x00\x00\x00\x00\x40\xfd\x00\x00\x00\x16\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0e\xf6\x00\x00\x00\x00\xa0\xca\xf6\x40\xf6\x00\x00\x00\x00\x00\x00\x08\x40\xfd\x00\x00\x00\x16\xfb\x0c\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x0e\xf6\x00\x00\x00\x00\xa0\xd0\xf5\x40\xfa\x0f\x52\x65\x66\x72\x65\x73\x68\x4c\x65\x66\x74\x44\x61\x79\x73\xf6\x00\x00\x00\x00\x00\x00\x1c\x40\xfa\x07\x42\x61\x73\x65\x43\x66\x67\xfd\x00\x00\x00\x14\xfa\x09\x43\x68\x61\x6e\x6e\x65\x6c\x49\x44\xf6\x00\x00\x00\x00\x00\x00\x08\x40\xfa\x08\x4f\x70\x65\x6e\x54\x69\x6d\x65\xf6\x00\x00\x00\x20\x19\x26\xd9\x41\xfa\x08\x53\x74\x61\x72\x4e\x75\x6d\x73\xf6\x00\x00\x00\x00\x00\x00\x00\x00\x35\x31\x00\x00";

	}
}

void ResponseChangeOBState(ClientNode* Client,BOOL OBState)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	Write8(p, OBState); //OBState
	Write8(p, 0); //ReasonLen

	len = p - buf;
	SendToClient(Client, 134, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void NotifyChangeOBState(ClientNode* Client, BOOL OBState,UINT Uin)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Uin); //Uin
	Write8(p, OBState); //OBState

	len = p - buf;
	SendToClient(Client, 609, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}
void RequestChangeOBState(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body; WORD len;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	bool OBState = Read8(p);
	ResponseChangeOBState(Client, OBState);
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
			NotifyChangeOBState(RoomClient, OBState, Uin);
		}
	}
}