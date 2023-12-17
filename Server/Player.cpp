#include "Message.h"
#include<unordered_map>
#include <stdio.h>
#include <time.h>
#include <map>
#include <string>
#include <mutex>
#include "Database.h"
#include "Item.h"
#include "sqlite/sqlite3.h"
#include "yaml-cpp/yaml.h"
extern std::map<long, ClientNode*> Clients;
std::map<long, RoomNode*> Rooms;
extern std::recursive_mutex Mutex;
extern std::recursive_mutex ClientMutex;
extern sqlite3* PlayerDB;
extern void NotifyBorderGameCondition(ClientNode* Client);
void ResponseKartRefitInfoMoreInfo(ClientNode* Client, UINT ItemNum, KartRefitItemInfo* Items, bool HasMoreInfo);
extern ClientNode* GetClient(long Uin);
BYTE msg900[52] = { 0 };
void NotifyUseItemResult2(ClientNode* Client, int ItemID, int UseItemNum);
extern void NotifyRankedMatchSeasonInfo(ClientNode* Client,UINT SrcUin);
extern UINT RankGradeLevel[8];
void NotifySpecialActivityInfo(ClientNode* Client);

BOOL WritePlayerDBBaseInfo(BYTE*& p, UINT Uin)
{ //PlayerDBBaseInfo
	
	WORD len;
	BYTE* pPlayerDBBaseInfo = p;
	Write16(pPlayerDBBaseInfo, 0); //len

	char* NickName = NULL;
	char* newname = NULL;
	char Gender = 0;
	char Country = 0;
	UINT License = 0;
	UINT Experience = 0;
	UINT SuperMoney = 0;
	UINT Money = 0;
	UINT WinNum = 0;
	UINT SecondNum = 0;
	UINT ThirdNum = 0;
	UINT TotalNum = 0;
	UINT CurHonor = 0;
	UINT TotalHonor = 0;
	UINT TodayHonor = 0;
	UINT RelaxTime = 0;
	UINT MonthDurationBefor = 0;
	UINT MonthDurationCur = 0;
	UINT Charm = 0;
	UINT DurationGame = 0;
	UINT DanceExp = 0;
	UINT Coupons = 0;
	UINT Admiration = 0;
	UINT LuckMoney = 0;
	UINT TeamWorkExp = 0;
	UINT AchievePoint = 0;
	UINT RegTime = 0;
	std::string Signature = "";

	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;

	sql = "SELECT NickName,Gender,Country,License,Experience,SuperMoney,Money,WinNum,SecondNum,ThirdNum,TotalNum,CurHonor,TotalHonor,TodayHonor,RelaxTime,MonthDurationBefor,MonthDurationCur,Charm,DurationGame,DanceExp,Coupons,Admiration,LuckMoney,TeamWorkExp,AchievePoint,RegTime,Signature  FROM BaseInfo  WHERE Uin=?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Uin);
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW)
		{
			NickName = (char*)sqlite3_column_text(stmt, 0);
			newname = myutf8trans(NickName);
			//printf("NickName:%s\n", newname);
			//delete[] newname;

			Gender = sqlite3_column_int(stmt, 1);
			Country = sqlite3_column_int(stmt, 2);
			License = sqlite3_column_int(stmt, 3);
			Experience = sqlite3_column_int(stmt, 4);
			SuperMoney = sqlite3_column_int(stmt, 5);
			Money = sqlite3_column_int(stmt, 6);
			WinNum = sqlite3_column_int(stmt, 7);
			SecondNum = sqlite3_column_int(stmt, 8);
			ThirdNum = sqlite3_column_int(stmt, 9);
			TotalNum = sqlite3_column_int(stmt, 10);
			CurHonor = sqlite3_column_int(stmt, 11);
			TotalHonor = sqlite3_column_int(stmt, 12);
			TodayHonor = sqlite3_column_int(stmt, 13);
			RelaxTime = sqlite3_column_int(stmt, 14);
			MonthDurationBefor = sqlite3_column_int(stmt, 15);
			MonthDurationCur = sqlite3_column_int(stmt, 16);
			Charm = sqlite3_column_int(stmt, 17);
			DurationGame = sqlite3_column_int(stmt, 18);
			DanceExp = sqlite3_column_int(stmt, 19);
			Coupons = sqlite3_column_int(stmt, 20);
			Admiration = sqlite3_column_int(stmt, 21);
			LuckMoney = sqlite3_column_int(stmt, 22);
			TeamWorkExp = sqlite3_column_int(stmt, 23);
			AchievePoint = sqlite3_column_int(stmt, 24);
			RegTime = sqlite3_column_int(stmt, 25);
			Signature = (char*)sqlite3_column_text(stmt, 26);
		}
		else
		{
			sqlite3_finalize(stmt);
			stmt = NULL;
			return FALSE;//查不到人返回
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;
	memset(pPlayerDBBaseInfo, 0, 17);
	//WriteString(pPlayerDBBaseInfo, "秋意寒\0");
	if (newname)
	{
		memcpy((char*)pPlayerDBBaseInfo, newname, strlen(newname));
		delete[] newname;
		newname = NULL;
	}
	pPlayerDBBaseInfo += MaxNickName;
	

	Write8(pPlayerDBBaseInfo, Gender|0x48);//性别
	Write8(pPlayerDBBaseInfo, Country);
	Write32(pPlayerDBBaseInfo, License);//许可证，驾照
	Write32(pPlayerDBBaseInfo, 99999999);//Experience固定201级
	Write32(pPlayerDBBaseInfo, SuperMoney); //点券
	Write32(pPlayerDBBaseInfo, Money); //酷币
	Write32(pPlayerDBBaseInfo, WinNum);
	Write32(pPlayerDBBaseInfo, SecondNum);
	Write32(pPlayerDBBaseInfo, ThirdNum);
	Write32(pPlayerDBBaseInfo, TotalNum);
	Write32(pPlayerDBBaseInfo, CurHonor);//荣誉
	Write32(pPlayerDBBaseInfo, TotalHonor);
	Write32(pPlayerDBBaseInfo, TodayHonor);
	Write32(pPlayerDBBaseInfo, RelaxTime);//休闲时间
	Write32(pPlayerDBBaseInfo, MonthDurationBefor);
	Write32(pPlayerDBBaseInfo, MonthDurationCur);
	Write32(pPlayerDBBaseInfo, Charm);//魅力值
	Write32(pPlayerDBBaseInfo, DurationGame);
	Write32(pPlayerDBBaseInfo, DanceExp);
	Write32(pPlayerDBBaseInfo, Coupons); //消费券
	Write32(pPlayerDBBaseInfo, Admiration);
	Write32(pPlayerDBBaseInfo, LuckMoney);
	Write32(pPlayerDBBaseInfo, TeamWorkExp);
	Write32(pPlayerDBBaseInfo, AchievePoint);//成就点
	Write32(pPlayerDBBaseInfo, RegTime);

	strcpy_s((char*)pPlayerDBBaseInfo, MaxSignature, Signature.c_str());
	pPlayerDBBaseInfo += MaxSignature;

	Write32(pPlayerDBBaseInfo, 0); //LuckyMatchPoint
	Write32(pPlayerDBBaseInfo, 0); //LuckyMatchNum
	Write16(pPlayerDBBaseInfo, 0); //LuckyMatchFirstNum
	Write8(pPlayerDBBaseInfo, 0); //LuckyMatchBestRand
	Write32(pPlayerDBBaseInfo, 0); //LuckyMatchWinNum
	Write32(pPlayerDBBaseInfo, 0); //FizzPointTotal
	Write16(pPlayerDBBaseInfo, 0); //FizzPointDaily
	Write16(pPlayerDBBaseInfo, 0); //FizzPointWeekly
	Write16(pPlayerDBBaseInfo, 0); //FizzPointLastWeek 上周流行音乐
	Write8(pPlayerDBBaseInfo, 0); //FizzLotteryStatus
	Write32(pPlayerDBBaseInfo, 0); //FizzLastUpdateTime
	Write32(pPlayerDBBaseInfo, 0); //SNSLocaleCode 
	Write32(pPlayerDBBaseInfo, 0); //AuctionRightUnlockTime 
	Write8(pPlayerDBBaseInfo, 0); //ReserveFlag 保留标志
	Write32(pPlayerDBBaseInfo, 0); //CurConsumeScore当前消费分数
	Write32(pPlayerDBBaseInfo, 0); //HistoryConsumeScore
	Write8(pPlayerDBBaseInfo, 0); //CrashModeSponsorID崩溃模式发起人id
	Write32(pPlayerDBBaseInfo, 0); //Popularity人气
	Write32(pPlayerDBBaseInfo, 0); //LadderMatchAchievePoint阶梯匹配实现点
	Write32(pPlayerDBBaseInfo, 0); //Cash现金
	Write32(pPlayerDBBaseInfo, 0); //PlayerGPMIdentity玩家GPM身份
	Write32(pPlayerDBBaseInfo, 0); //PointTotalScore积分总分
	Write32(pPlayerDBBaseInfo, 0); //totalMapMedalNum
	Write32(pPlayerDBBaseInfo, 0); //lastMapMedalNum
	Write32(pPlayerDBBaseInfo, 0); //curMapMedalNum
	Write32(pPlayerDBBaseInfo, 0); //curMapMedalSeasonId
	Write32(pPlayerDBBaseInfo, 0); //lastClearMapMedalTime
#ifndef ZingSpeed
	Write32(pPlayerDBBaseInfo, 0); //max2048Score
	Write32(pPlayerDBBaseInfo, 0); //curPlay2048LeftNum
	Write32(pPlayerDBBaseInfo, 0); //CheerValue欢呼值
	Write16(pPlayerDBBaseInfo, 0x2b); //SeasonID赛季id
	Write32(pPlayerDBBaseInfo, 0); //LastCheerValue
	Write32(pPlayerDBBaseInfo, 99999999); //SpeedBean飞车豆
	Write32(pPlayerDBBaseInfo, 99999999); //SpeedCoin飞车币
#endif

	len = pPlayerDBBaseInfo - p;
	Set16(p, len);
	p += len;
}

void WritePlayerGuildInfo(BYTE*& p, UINT Uin)
{ //PlayerGuildInfo
	WORD len;

	BYTE* pPlayerGuildInfo = p;
	Write16(pPlayerGuildInfo, 0); //len


	strcpy_s((char*)pPlayerGuildInfo, MaxNickName, ""); //GuildName
	pPlayerGuildInfo += MaxNickName;

	Write16(pPlayerGuildInfo, 0); //Duty
	Write32(pPlayerGuildInfo, 0); //GuildID
	Write32(pPlayerGuildInfo, 0); //Right
	Write32(pPlayerGuildInfo, 0); //Medal
	Write32(pPlayerGuildInfo, 0); //Contribute

	memset(pPlayerGuildInfo, 0, 9); //m_szDutyTitle[]:
	pPlayerGuildInfo += 9;

	len = pPlayerGuildInfo - p;
	Set16(p, len);
	p += len;
}

UINT WriteEquipedItem(BYTE*& p, ClientNode* Client)//写入当前装备的项目让对方看到的
{ //EquipedItem
	const char* psql = NULL;
	sqlite3_stmt* pstmt = NULL;
	WORD len;

	BYTE* pItemNum = p;
	Write16(p, 0); //EquipedItemNum

	
	
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result,presult;
	size_t i = 0;
	UINT KartItemId = 0;
	sql = "SELECT ItemID,ItemNum,AvailPeriod,Status,ObtainTime,OtherAttribute  FROM Item WHERE Uin = ?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Uin);
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			UINT ItemID = sqlite3_column_int(stmt, 0);
			BYTE Status = sqlite3_column_int(stmt, 3);

			if (Status)
			{ //PlayerItemInfo
				i++;
				if (GetItemType(ItemID) == EAIT_CAR)
				{
					Client->KartID=KartItemId = ItemID;
					
					//if (Client->KartSkinID != 0)
					//{
					//	ItemID = Client->KartSkinID;
						//KartItemId = ItemID;
					//}
				}
				BYTE* pItemInfo = p;
				Write16(pItemInfo, 0); //len

				Write32(pItemInfo, ItemID);
				Write32(pItemInfo, sqlite3_column_int(stmt, 1));
				Write32(pItemInfo, sqlite3_column_int(stmt, 2));
				Write8(pItemInfo, Status);
				Write32(pItemInfo, sqlite3_column_int(stmt, 4));
				Write32(pItemInfo, sqlite3_column_int(stmt, 5));
#ifndef ZingSpeed
				Write16(pItemInfo, 0); //ItemType
#endif
				len = pItemInfo - p;
				Set16(p, (WORD)len);
				p += len;
			}
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;
	Set16(pItemNum, (WORD)i);
	
	return KartItemId;
}

UINT WriteEquipedItem2(BYTE*& p, long Uin)//写入当前装备的项目让对方看到的
{ //EquipedItem
	WORD len;

	BYTE* pItemNum = p;
	Write16(p, 0); //EquipedItemNum

	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	size_t i = 0;
	UINT KartItemId = 0;
	sql = "SELECT ItemID,ItemNum,AvailPeriod,Status,ObtainTime,OtherAttribute  FROM Item WHERE Uin = ?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Uin);
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			UINT ItemID = sqlite3_column_int(stmt, 0);
			BYTE Status = sqlite3_column_int(stmt, 3);

			if (Status)
			{ //PlayerItemInfo
				i++;
				if (GetItemType(ItemID) == EAIT_CAR)
				{
					KartItemId = ItemID;
				}

				BYTE* pItemInfo = p;
				Write16(pItemInfo, 0); //len

				Write32(pItemInfo, ItemID);
				Write32(pItemInfo, sqlite3_column_int(stmt, 1));
				Write32(pItemInfo, sqlite3_column_int(stmt, 2));
				Write8(pItemInfo, Status);
				Write32(pItemInfo, sqlite3_column_int(stmt, 4));
				Write32(pItemInfo, sqlite3_column_int(stmt, 5));
#ifndef ZingSpeed
				Write16(pItemInfo, 0); //ItemType
#endif
				len = pItemInfo - p;
				Set16(p, (WORD)len);
				p += len;
			}
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;
	Set16(pItemNum, (WORD)i);

	return KartItemId;
}

void WriteVisbleInfo(ClientNode* Client,BYTE*& p, UINT Uin, char SeatID, short PlayerID)//写其他玩家可见信息
{ //PlayerRoomVisibleInfo
	//printf("PlayerID：%d\n", PlayerID);
	WORD len;
	int Identity = ID_IDENTIFY_QQLEVEL1 | ID_IDENTIFY_QQLEVEL2 | ID_IDENTIFY_QQLEVEL3 | ID_IDENTIFY_SPEEDMEMBER | ID_IDENTIFY_QQFLAG | ID_IDENTIFY_HAVEWORD | ID_IDENTIFY_FINISHQQFLAG;

	BYTE* pPlayerRoomVisibleInfo = p;
	Write16(pPlayerRoomVisibleInfo, 0); //len

	Write32(pPlayerRoomVisibleInfo, Uin); //Uin
	Write32(pPlayerRoomVisibleInfo, Identity); //Identity
	Write8(pPlayerRoomVisibleInfo, SeatID); //SeatID
	Write8(pPlayerRoomVisibleInfo, 0); //TeamID
	Write16(pPlayerRoomVisibleInfo, PlayerID); //PlayerID
	Write8(pPlayerRoomVisibleInfo, 0); //Status

	WritePlayerDBBaseInfo(pPlayerRoomVisibleInfo, Uin);
	WritePlayerGuildInfo(pPlayerRoomVisibleInfo, Uin);
	WriteEquipedItem(pPlayerRoomVisibleInfo, Client);



	
	
	Write16(pPlayerRoomVisibleInfo,1); //PetNum in WriteVisbleInfo
	/*
m_stPlayerRoomVisibleInfo[].m_astPetInfo[].m_uiUin
m_stPlayerRoomVisibleInfo[].m_astPetInfo[].m_iPetId
m_stPlayerRoomVisibleInfo[].m_astPetInfo[].m_szPetName[]:
m_stPlayerRoomVisibleInfo[].m_astPetInfo[].m_cIsProper
m_stPlayerRoomVisibleInfo[].m_astPetInfo[].m_usLevel
m_stPlayerRoomVisibleInfo[].m_astPetInfo[].m_ucStatus
m_stPlayerRoomVisibleInfo[].m_astPetInfo[].m_usPetSkillNum
m_stPlayerRoomVisibleInfo[].m_astPetInfo[].m_astPetSkillList[].m_usSkillID
m_stPlayerRoomVisibleInfo[].m_astPetInfo[].m_astPetSkillList[].m_ucStatus
m_stPlayerRoomVisibleInfo[].m_astPetInfo[].m_astPetSkillList[].m_cActive
m_stPlayerRoomVisibleInfo[].m_astPetInfo[].m_astPetSkillList[].m_iValue
m_stPlayerRoomVisibleInfo[].m_astPetInfo[].m_iStrengLevel
	*/
	
	 { //PetInfo
		//国服宠物数据结构
		BYTE* pPetInfo = pPlayerRoomVisibleInfo;
		Write16(pPetInfo, 0); //len
		Write32(pPetInfo, Uin); //Uin
		Write32(pPetInfo, Client->PetID); //PetId黄金神兽  
		memset(pPetInfo, 0, 17);
		memcpy(pPetInfo, "宠物", 5);
		pPetInfo += 17;
		Write32(pPetInfo, 0);
		Write32(pPetInfo, 0);
		Write8(pPetInfo, 0);

		Write8(pPetInfo, Client->PetStatus);//当前宠物形态 黄金神兽 最高4级 

		Write16(pPetInfo, 0x00);//SkillNum

		Write32(pPetInfo, 0x0a); //StrengLevel强化等级 个人信息宠物图标有+5
		Write8(pPetInfo, 0x4); //TopStatus 变形形态
				//变形功能大于1开启
		{ //CommonInfo
			BYTE* pCommonInfo = pPetInfo;
			Write16(pCommonInfo, 0); //len

			Write32(pCommonInfo, 0x5); //HuanHuaLevel幻化等级
			Write8(pCommonInfo, 0x1); //CanHuanHua

			len = pCommonInfo - pPetInfo;
			Set16(pPetInfo, (WORD)len);
			pPetInfo += len;
		}
		len = pPetInfo - pPlayerRoomVisibleInfo;
		Set16(pPlayerRoomVisibleInfo, (WORD)len);

		pPlayerRoomVisibleInfo += len;
	}
	


	{ //PlayerGuildMatchInfo
		BYTE* pPlayerGuildMatchInfo = pPlayerRoomVisibleInfo;
		Write16(pPlayerGuildMatchInfo, 0); //len

		Write32(pPlayerGuildMatchInfo, 0); //SelfPoint
		Write32(pPlayerGuildMatchInfo, 0); //WinNum
		Write32(pPlayerGuildMatchInfo, 0); //TotalNum

		len = pPlayerGuildMatchInfo - pPlayerRoomVisibleInfo;
		Set16(pPlayerRoomVisibleInfo, (WORD)len);
		pPlayerRoomVisibleInfo += len;
	}
	

	Write8(pPlayerRoomVisibleInfo, true); //IsInTopList
	Write8(pPlayerRoomVisibleInfo, 0); //LoverRaceOrPro
	Write8(pPlayerRoomVisibleInfo, 0); //TmpEffectNum
	//m_stPlayerRoomVisibleInfo[].m_aiTmpEffectItems[]


	Write8(pPlayerRoomVisibleInfo, 0); //OBState
	Write8(pPlayerRoomVisibleInfo, 0); //DebutOrX5
	Write8(pPlayerRoomVisibleInfo, 0); //RandKeyFlag


	Write16(pPlayerRoomVisibleInfo, 0x0106); //VipFlag

	Write8(pPlayerRoomVisibleInfo, 0); //HaveAppellation
	/*
m_stPlayerRoomVisibleInfo[].m_astCurAppellation[].m_u8Type
m_stPlayerRoomVisibleInfo[].m_astCurAppellation[].m_u8Level
m_stPlayerRoomVisibleInfo[].m_astCurAppellation[].m_u8Status
m_stPlayerRoomVisibleInfo[].m_astCurAppellation[].m_u8Difficulty
m_stPlayerRoomVisibleInfo[].m_astCurAppellation[].m_i32MapId
m_stPlayerRoomVisibleInfo[].m_astCurAppellation[].m_u32Value
	*/

	{ //NobleInfo
		BYTE* pNobleInfo = pPlayerRoomVisibleInfo;
		Write16(pNobleInfo, 0); //len

		Write32(pNobleInfo, Uin); //NobleID
		Write8(pNobleInfo, 6); //NobleLevel
		Write32(pNobleInfo, 1); //NoblePoint
		Write32(pNobleInfo, 30); //NobleLeftDays

		len = pNobleInfo - pPlayerRoomVisibleInfo;
		Set16(pPlayerRoomVisibleInfo, (WORD)len);
		pPlayerRoomVisibleInfo += len;
	}

	Write8(pPlayerRoomVisibleInfo, 0); //HasCarryWizard
	/*
m_stPlayerRoomVisibleInfo[].m_astCarryWizardInfo[].m_ushWizardID
m_stPlayerRoomVisibleInfo[].m_astCarryWizardInfo[].m_szNickname[]:
m_stPlayerRoomVisibleInfo[].m_astCarryWizardInfo[].m_ushWizardType
m_stPlayerRoomVisibleInfo[].m_astCarryWizardInfo[].m_bOrder
m_stPlayerRoomVisibleInfo[].m_astCarryWizardInfo[].m_bEvolutionBranch
m_stPlayerRoomVisibleInfo[].m_astCarryWizardInfo[].m_bIsHuanHua
	*/
#ifndef ZingSpeed
	{ //GuildVipBaseInfo
		BYTE* pGuildVipBaseInfo = pPlayerRoomVisibleInfo;
		Write16(pGuildVipBaseInfo, 0); //len

		Write8(pGuildVipBaseInfo, 6); //GuildVipLevel
		Write32(pGuildVipBaseInfo, 1); //GuildVipPoint

		len = pGuildVipBaseInfo - pPlayerRoomVisibleInfo;
		Set16(pPlayerRoomVisibleInfo, (WORD)len);
		pPlayerRoomVisibleInfo += len;
	}
#endif
	Write32(pPlayerRoomVisibleInfo, 0); //ExFlag

	Write8(pPlayerRoomVisibleInfo, 0); //HaveLDMBaseInfo
	/*
m_stPlayerRoomVisibleInfo[].m_stPlayerLDMBaseInfo[].m_u8Grade
m_stPlayerRoomVisibleInfo[].m_stPlayerLDMBaseInfo[].m_u32Score
m_stPlayerRoomVisibleInfo[].m_stPlayerLDMBaseInfo[].m_u32MaxScore
m_stPlayerRoomVisibleInfo[].m_stPlayerLDMBaseInfo[].m_u32MaxGrade
	*/

	Write8(pPlayerRoomVisibleInfo, 0); //HasWl
	/*
m_stPlayerRoomVisibleInfo[].m_astPlayerWlVisibleInfo[].m_uiWonderLandID
m_stPlayerRoomVisibleInfo[].m_astPlayerWlVisibleInfo[].m_szWonderLandName[]:
m_stPlayerRoomVisibleInfo[].m_astPlayerWlVisibleInfo[].m_ushWonderLandDuty
m_stPlayerRoomVisibleInfo[].m_astPlayerWlVisibleInfo[].m_ucSubType
m_stPlayerRoomVisibleInfo[].m_astPlayerWlVisibleInfo[].m_bGuildGrade
	*/
#ifndef ZingSpeed
	Write8(pPlayerRoomVisibleInfo, 1); //HasLoverVip
	for (size_t i = 0; i < 1; i++)
	{ //LoverVipInfo
		BYTE* pLoverVipInfo = pPlayerRoomVisibleInfo;
		Write16(pLoverVipInfo, 0); //len

		Write8(pLoverVipInfo, 6); //LoverVipLevel
		Write32(pLoverVipInfo, 1); //LoverVipPoint
		Write8(pLoverVipInfo, 0); //GrowRate

		len = pLoverVipInfo - pPlayerRoomVisibleInfo;
		Set16(pPlayerRoomVisibleInfo, (WORD)len);
		pPlayerRoomVisibleInfo += len;
	}
#endif ZingSpeed
	Write8(pPlayerRoomVisibleInfo, 0); //HasBattleModeSkillInfoList
	/*
m_stPlayerRoomVisibleInfo[].m_astBattleModeSkillInfoList[].m_bSkillNum
m_stPlayerRoomVisibleInfo[].m_astBattleModeSkillInfoList[].m_astSkillInfo[].m_shSkillId
m_stPlayerRoomVisibleInfo[].m_astBattleModeSkillInfoList[].m_astSkillInfo[].m_bSkillLevel
	*/
	Write8(pPlayerRoomVisibleInfo, 1); //HasGarden
	for (size_t i = 0; i < 1; i++)
	{ //PersonalGardenBaseInfo
		BYTE* pPersonalGardenBaseInfo = pPlayerRoomVisibleInfo;
		Write16(pPersonalGardenBaseInfo, 0); //len

		Write8(pPersonalGardenBaseInfo, 6); //GardenLevel
		Write32(pPersonalGardenBaseInfo, 1); //GardenPoint
		Write8(pPersonalGardenBaseInfo, 0); //GrowRate
		Write32(pPersonalGardenBaseInfo, 0); //GardenExpireTime
		{ //SimpleInfo
			BYTE* pSimpleInfo = pPersonalGardenBaseInfo;
			Write16(pSimpleInfo, 0); //len

			Write32(pSimpleInfo, 0); //WeekPopularity
			Write32(pSimpleInfo, 0); //TotalPopularity
			Write32(pSimpleInfo, 0); //LastUpdatePopularityTime
			Write8(pSimpleInfo, 0); //PrivateType

			len = pSimpleInfo - pPersonalGardenBaseInfo;
			Set16(pPersonalGardenBaseInfo, (WORD)len);
			pPersonalGardenBaseInfo += len;
		}

		len = pPersonalGardenBaseInfo - pPlayerRoomVisibleInfo;
		Set16(pPlayerRoomVisibleInfo, (WORD)len);
		pPlayerRoomVisibleInfo += len;
	}
	{ //ConsumeVipInfo
		BYTE* pConsumeVipInfo = pPlayerRoomVisibleInfo;
		Write16(pConsumeVipInfo, 0); //len

		Write32(pConsumeVipInfo, 6); //VipLevel
		Write32(pConsumeVipInfo, 0); //CharmValueOfMonth
		Write32(pConsumeVipInfo, 0); //SearchTreasureNums
		Write32(pConsumeVipInfo, 0); //GetTreasureNums

		len = pConsumeVipInfo - pPlayerRoomVisibleInfo;
		Set16(pPlayerRoomVisibleInfo, (WORD)len);
		pPlayerRoomVisibleInfo += len;
	}
	Write8(pPlayerRoomVisibleInfo, 0); //HaveBaby
	{ //LoverBabyInfo
		BYTE* pLoverBabyInfo = pPlayerRoomVisibleInfo;
		Write16(pLoverBabyInfo, 0); //len

		Write32(pLoverBabyInfo, 0); //LoverBabyID
		Write32(pLoverBabyInfo, 0); //ItemID
		Write32(pLoverBabyInfo, 0); //GrowValue
		Write32(pLoverBabyInfo, 0); //MentalValue
		Write32(pLoverBabyInfo, 0); //BabyProfileLevel
		Write32(pLoverBabyInfo, 0); //StrengthLevel
		Write32(pLoverBabyInfo, 0); //GrowLevel
		//WriteString(pLoverBabyInfo, 0); //LoveBabyNickName[]
		Write16(pLoverBabyInfo, 0); //LoverBabyStat
		Write16(pLoverBabyInfo, 0); //LoverBabyEquipStat
		Write16(pLoverBabyInfo, 0); //LoverBabyTransferdStatus

		len = pLoverBabyInfo - pPlayerRoomVisibleInfo;
		Set16(pPlayerRoomVisibleInfo, (WORD)len);
		pPlayerRoomVisibleInfo += len;
	}
	{ //EmperorInfo钻皇信息
		BYTE* pEmperorInfo = pPlayerRoomVisibleInfo;
		Write16(pEmperorInfo, 0); //len

		Write8(pEmperorInfo, 6); //EmperorLevel
		Write32(pEmperorInfo, 1); //EmperorPoint
		Write32(pEmperorInfo, 30); //EmperorLeftDays
		Write8(pEmperorInfo, 0); //EmperorGrowRate

		len = pEmperorInfo - pPlayerRoomVisibleInfo;
		Set16(pPlayerRoomVisibleInfo, (WORD)len);
		pPlayerRoomVisibleInfo += len;
	}
	Write16(pPlayerRoomVisibleInfo, 0); //RaceCardNums
	
	{ //GansterScoreInfo
		BYTE* pGansterScoreInfo = pPlayerRoomVisibleInfo;
		Write16(pGansterScoreInfo, 0); //len

		Write32(pGansterScoreInfo, 0); //GansterSeasonID
		Write32(pGansterScoreInfo, 0); //GansterScore
		Write32(pGansterScoreInfo, 0); //PoliceScore
		Write32(pGansterScoreInfo, 0); //TotalGansterScore

		len = pGansterScoreInfo - pPlayerRoomVisibleInfo;
		Set16(pPlayerRoomVisibleInfo, (WORD)len);
		pPlayerRoomVisibleInfo += len;
	}
	Write32(pPlayerRoomVisibleInfo, 0); //OlympicId
	Write32(pPlayerRoomVisibleInfo, 0); //NPCEliminateWinTimes
	Write8(pPlayerRoomVisibleInfo, 0); //OriginTeamID
	Write8(pPlayerRoomVisibleInfo, 0); //NxNpc
	Write16(pPlayerRoomVisibleInfo, 0); //NxNpcAILevel
	{ //EquippedActiveKartInfo
		BYTE* pEquippedActiveKartInfo = pPlayerRoomVisibleInfo;
		Write16(pEquippedActiveKartInfo, 0); //len

		Write8(pEquippedActiveKartInfo, 0); //HaveActiveInfo
		Write32(pEquippedActiveKartInfo, 0); //KartID
		Write32(pEquippedActiveKartInfo, 0); //ActiveLevel

		len = pEquippedActiveKartInfo - pPlayerRoomVisibleInfo;
		Set16(pPlayerRoomVisibleInfo, (WORD)len);
		pPlayerRoomVisibleInfo += len;
	}
	Write8(pPlayerRoomVisibleInfo, 0); //SpecialActivityStatus
	Write8(pPlayerRoomVisibleInfo, 0); //AreaID
	Write8(pPlayerRoomVisibleInfo, 0); //HaveRaiseSecondBaby
	{ //SecondLoverBabyInfo
		BYTE* pSecondLoverBabyInfo = pPlayerRoomVisibleInfo;
		Write16(pSecondLoverBabyInfo, 0); //len

		Write32(pSecondLoverBabyInfo, 0); //LoverBabyID
		Write32(pSecondLoverBabyInfo, 0); //ItemID
		Write32(pSecondLoverBabyInfo, 0); //GrowValue
		Write32(pSecondLoverBabyInfo, 0); //MentalValue
		Write32(pSecondLoverBabyInfo, 0); //BabyProfileLevel
		Write32(pSecondLoverBabyInfo, 0); //StrengthLevel
		Write32(pSecondLoverBabyInfo, 0); //GrowLevel
		//WriteString(pSecondLoverBabyInfo, 0); //LoveBabyNickName[]
		Write16(pSecondLoverBabyInfo, 0); //LoverBabyStat
		Write16(pSecondLoverBabyInfo, 0); //LoverBabyEquipStat
		Write16(pSecondLoverBabyInfo, 0); //LoverBabyTransferdStatus

		len = pSecondLoverBabyInfo - pPlayerRoomVisibleInfo;
		Set16(pPlayerRoomVisibleInfo, (WORD)len);
		pPlayerRoomVisibleInfo += len;
	}
	Write8(pPlayerRoomVisibleInfo, 1); //HasRankedMatchInfo
	for (size_t i = 0; i < 1; i++)
	{ //RankedMatchGradeInfo
		BYTE* pRankedMatchGradeInfo = pPlayerRoomVisibleInfo;
		Write16(pRankedMatchGradeInfo, 0); //len

		Write32(pRankedMatchGradeInfo, RankGradeLevel[Client->GradeLevel]); //GradeLevel
		Write32(pRankedMatchGradeInfo, 1); //ChildLevel
		Write32(pRankedMatchGradeInfo, 0); //GradeScore
		Write32(pRankedMatchGradeInfo, 0); //MaxGradeScore
		Write32(pRankedMatchGradeInfo, 0); //TotalScore

		len = pRankedMatchGradeInfo - pPlayerRoomVisibleInfo;
		Set16(pPlayerRoomVisibleInfo, (WORD)len);
		pPlayerRoomVisibleInfo += len;
	}
	Write8(pPlayerRoomVisibleInfo, 0); //HasHuanLingChangeInfo

	Write8(pPlayerRoomVisibleInfo, 0); //EquipSealType
	Write16(pPlayerRoomVisibleInfo, 0); //Role
	Write8(pPlayerRoomVisibleInfo, 0); //SpecialActivityIDNum
	Write8(pPlayerRoomVisibleInfo, 0); //CrewID
	Write8(pPlayerRoomVisibleInfo, 1); //SpecialActivityInfoNum 职业生涯图标段位
	for (size_t i = 0; i < 1; i++)
	{ //SpecialActivityInfo
		BYTE* pSpecialActivityInfo = pPlayerRoomVisibleInfo;
		Write16(pSpecialActivityInfo, 0); //len

		Write8(pSpecialActivityInfo, 1); //ProfessionLicenseInfoNum
		for (size_t i = 0; i < 1; i++)
		{ //ProfessionLicenseInfo
			BYTE* pProfessionLicenseInfo = pSpecialActivityInfo;
			Write16(pProfessionLicenseInfo, 0); //len

			Write8(pProfessionLicenseInfo, 6); //BigLevel
			Write8(pProfessionLicenseInfo, 5); //SmallLevel

			len = pProfessionLicenseInfo - pSpecialActivityInfo;
			Set16(pSpecialActivityInfo, (WORD)len);
			pSpecialActivityInfo += len;
		}

		len = pSpecialActivityInfo - pPlayerRoomVisibleInfo;
		Set16(pPlayerRoomVisibleInfo, (WORD)len);
		pPlayerRoomVisibleInfo += len;
	}
	Write8(pPlayerRoomVisibleInfo, 0); //ParaNum
	
	Write8(pPlayerRoomVisibleInfo, 0); //ItemNum
	
	Write8(pPlayerRoomVisibleInfo, 0); //TDCExcluItemNum
	
	Write8(pPlayerRoomVisibleInfo, 0); //EquipNiChangItemNum

	Write8(pPlayerRoomVisibleInfo, 0); //TestKartGameType
	Write32(pPlayerRoomVisibleInfo, 0); //GameTestKartID
	Write8(pPlayerRoomVisibleInfo, 0); //HasStarsFightingInfo
	
	Write8(pPlayerRoomVisibleInfo, 0); //RoomBGSetting
	

	len = pPlayerRoomVisibleInfo - p;
	Set16(p, len);
	p += len;
}



void RequestRegister2(ClientNode* Client, BYTE* Body, size_t BodyLen)
{

	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	char* newname;

	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);
	const char* Nickname = (char*)Body;
	newname =G2U(Nickname);
	
	Body += MaxNickName;

	BYTE Gender = Read8(Body);
	BYTE Country = Read8(Body);
	UINT isNameExist = 0;
	//select* from BaseInfo where NickName = '姐姐';
	sql = "SELECT Uin FROM BaseInfo Where NickName=?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		if (newname)
		{
			sqlite3_bind_text(stmt, 1, newname, strlen(newname), SQLITE_TRANSIENT);
		}
		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
			isNameExist = sqlite3_column_int(stmt, 0);
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;
	if (isNameExist != 0)
	{
		ResponseStartGame(Client, "用户名已存在!");
		delete[] newname;//释放内存 防止重复名过多内存泄露
		return;
	}


	sql = "BEGIN"; //开始事务
	result = sqlite3_exec(PlayerDB, sql, NULL, NULL, NULL);

	sql = "INSERT INTO Player (Uin,VipFlag,IsInTopList) VALUES (?,?,?);";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Uin);
		sqlite3_bind_int(stmt, 2, 0x0106);
		sqlite3_bind_int(stmt, 3, 1);
		result = sqlite3_step(stmt);
	}
	else
	{
		printf("%s\n", sqlite3_errmsg(PlayerDB));
	}
	sqlite3_finalize(stmt);
	stmt = NULL;


	sql = "INSERT INTO BaseInfo (Uin,NickName,Gender,Country,Experience,SuperMoney,Money,Coupons,LuckMoney) VALUES (?,?,?,?,?,?,?,?,?);";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Uin);
		if (newname)
		{
			sqlite3_bind_text(stmt, 2, newname, strlen(newname), SQLITE_TRANSIENT);
			delete[] newname;
			newname = NULL;
		}
		sqlite3_bind_int(stmt, 3, Gender);
		sqlite3_bind_int(stmt, 4, Country);
		sqlite3_bind_int(stmt, 5, 99999999);
		sqlite3_bind_int(stmt, 6, 99999999);
		sqlite3_bind_int(stmt, 7, 99999999);
		sqlite3_bind_int(stmt, 8, 99999999);
		sqlite3_bind_int(stmt, 9, 99999999);
		result = sqlite3_step(stmt);
	}
	else
	{
		printf("%s\n", sqlite3_errmsg(PlayerDB));
	}
	sqlite3_finalize(stmt);
	stmt = NULL;

	UINT RoleID = Read32(Body);
	UINT HairID = Read32(Body);
	UINT FaceID = Read32(Body);
	UINT CoatID = Read32(Body);
	UINT GloveID = Read32(Body);
	UINT TrousersID = Read32(Body);
	UINT KartID = Read32(Body);
	UINT ColorID = Read32(Body);

	PlayerDB_AddItem(Client,Client->Uin, RoleID, 1, -1, true);
	PlayerDB_AddItem(Client, Client->Uin, HairID, 1, -1, true);
	PlayerDB_AddItem(Client, Client->Uin, FaceID, 1, -1, true);
	PlayerDB_AddItem(Client, Client->Uin, CoatID, 1, -1, true);
	PlayerDB_AddItem(Client, Client->Uin, GloveID, 1, -1, true);
	PlayerDB_AddItem(Client, Client->Uin, TrousersID, 1, -1, true);
	PlayerDB_AddItem(Client, Client->Uin, KartID, 1, -1, true);
	PlayerDB_AddItem(Client, Client->Uin, ColorID, 1, -1, true);
	//3D 男装
	PlayerDB_AddItem(Client, Client->Uin, 27178, 1, -1, true);
	PlayerDB_AddItem(Client, Client->Uin, 27179, 1, -1, true);
	PlayerDB_AddItem(Client, Client->Uin, 27180, 1, -1, true);
	PlayerDB_AddItem(Client, Client->Uin, 27181, 1, -1, true);
	PlayerDB_AddItem(Client, Client->Uin, 27182, 1, -1, true);
	//3D 女装
	PlayerDB_AddItem(Client, Client->Uin, 27190, 1, -1, true);
	PlayerDB_AddItem(Client, Client->Uin, 27191, 1, -1, true);
	PlayerDB_AddItem(Client, Client->Uin, 27192, 1, -1, true);
	PlayerDB_AddItem(Client, Client->Uin, 27193, 1, -1, true);
	PlayerDB_AddItem(Client, Client->Uin, 27194, 1, -1, true);


	//PlayerDB_AddItem(Client, Client->Uin, 10993, 1, -1, false); //傀儡
	PlayerDB_AddItem(Client, Client->Uin, 12720, 1, -1, false); //雷诺
	PlayerDB_AddItem(Client, Client->Uin, 129099, 1, -1, false); 
	PlayerDB_AddItem(Client, Client->Uin, 127616, 1, -1, false);
	//PlayerDB_AddItem(Client->Uin, 15225, 1, -1, false); //飞碟
	//PlayerDB_AddItem(Client, Client->Uin, 10024, 1, -1, false);
	//PlayerDB_AddItem(Client, Client->Uin, 10699, 1, -1, false);
	//PlayerDB_AddItem(Client, Client->Uin, 11147, 1, -1, false);
	//PlayerDB_AddItem(Client, Client->Uin, 11376, 1, -1, false);
	//PlayerDB_AddItem(Client, Client->Uin, 24859, 1, -1, false);
	PlayerDB_AddItem(Client, Client->Uin, 127758, 1, -1, false); 
	PlayerDB_AddItem(Client, Client->Uin, 18643, 1, -1, false); 
	PlayerDB_AddItem(Client, Client->Uin, 127762, 1, -1, false); 

	PlayerDB_AddItem(Client, Client->Uin, 21980, 10, -1, false); //效率宝珠LV4
	PlayerDB_AddItem(Client, Client->Uin, 21986, 10, -1, false); //重生宝珠LV4
	//PlayerDB_AddItem(Client, Client->Uin, 21992, 10, -1, false); //坚韧宝珠LV4
	//PlayerDB_AddItem(Client, Client->Uin, 22000, 1, -1, false); //苍天宝珠LV6
	//PlayerDB_AddItem(Client, Client->Uin, 22006, 1, -1, false); //大地宝珠LV6
	//PlayerDB_AddItem(Client, Client->Uin, 22012, 1, -1, false); //无双宝珠LV6
	//PlayerDB_AddItem(Client, Client->Uin, 22016, 1, -1, false); //后发宝珠LV4
	//PlayerDB_AddItem(Client, Client->Uin, 22024, 1, -1, false); //愤怒宝珠LV6

	PlayerDB_AddItem(Client, Client->Uin, 12376, 99, 0, false); //点火装置+1
	PlayerDB_AddItem(Client, Client->Uin, 12377, 99, 0, false); //进气系统+1
	PlayerDB_AddItem(Client, Client->Uin, 12378, 99, 0, false); //燃料系统+1
	PlayerDB_AddItem(Client, Client->Uin, 12379, 99, 0, false); //悬挂系统+1
	PlayerDB_AddItem(Client, Client->Uin, 12380, 99, 0, false); //引擎装置+1

	PlayerDB_AddItem(Client, Client->Uin, 10207, 1, 0, false); //小喇叭
	PlayerDB_AddItem(Client, Client->Uin, 10791, 1, -1, false); //临时驾照
	//PlayerDB_AddItem(Client, Client->Uin, 25858, 99, 0, false); //幸运星梦宝瓶
	PlayerDB_AddItem(Client, Client->Uin, 127748, 200, 0, false); //小橘子盲盒
	PlayerDB_AddItem(Client, Client->Uin, 18554, 1, 0, false);
	PlayerDB_AddItem(Client, Client->Uin, 120258, 1, 0, false);
	sql = "COMMIT"; //提交事务
	result = sqlite3_exec(PlayerDB, sql, NULL, NULL, NULL);


	ItemInfo Items[200];
	size_t ItemNum = 0;
	bool HasMoreInfo = false;
	sql = "SELECT ItemID,ItemNum,AvailPeriod,Status,ObtainTime,OtherAttribute  FROM Item WHERE Uin = ?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Uin);
	}
	else
	{
		printf("%s\n", sqlite3_errmsg(PlayerDB));
		sqlite3_finalize(stmt);
		stmt = NULL;
	}
	if (stmt)
	{
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			Items[ItemNum].ItemID = sqlite3_column_int(stmt, 0);
			Items[ItemNum].ItemNum = sqlite3_column_int(stmt, 1);
			Items[ItemNum].AvailPeriod = sqlite3_column_int(stmt, 2);
			Items[ItemNum].Status = sqlite3_column_int(stmt, 3);
			Items[ItemNum].ObtainTime = sqlite3_column_int(stmt, 4);
			Items[ItemNum].OtherAttribute = sqlite3_column_int(stmt, 5);
			Items[ItemNum].ItemType = 0;
			if (Items[ItemNum].Status && GetItemType(Items[ItemNum].ItemID) == EAIT_CAR)
			{
				Client->KartID = Items[ItemNum].ItemID;
				//printf("KartID:%d\n", Client->KartID);
			}

			ItemNum++;
			if (ItemNum >= 200)
			{
				HasMoreInfo = true;
				break;
			}
		}
	}
	ResponseRegister(Client, Nickname, Gender, Country, ItemNum, Items);
	if (stmt)
	{
		while (HasMoreInfo)
		{
			ItemNum = 0;
			HasMoreInfo = false;
			while (sqlite3_step(stmt) == SQLITE_ROW)
			{
				Items[ItemNum].ItemID = sqlite3_column_int(stmt, 0);
				Items[ItemNum].ItemNum = sqlite3_column_int(stmt, 1);
				Items[ItemNum].AvailPeriod = sqlite3_column_int(stmt, 2);
				Items[ItemNum].Status = sqlite3_column_int(stmt, 3);
				Items[ItemNum].ObtainTime = sqlite3_column_int(stmt, 4);
				Items[ItemNum].OtherAttribute = sqlite3_column_int(stmt, 5);
				Items[ItemNum].ItemType = 0;
				if (Items[ItemNum].Status && GetItemType(Items[ItemNum].ItemID) == EAIT_CAR)
				{
					Client->KartID = Items[ItemNum].ItemID;
					//printf("KartID:%d\n", Client->KartID);
				}

				ItemNum++;
				if (ItemNum >= 200)
				{
					HasMoreInfo = true;
					break;
				}
			}
			NotifyClientAddItem(Client, ItemNum, Items);
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
	}

	ResponseSkipFreshTask(Client); //跳过新手任务
}
void ResponseRegister(ClientNode* Client, const char* Nickname, BYTE  Gender, BYTE Country, UINT ItemNum, ItemInfo* Items)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID
	Write32(p, Client->Uin);

	strcpy_s((char*)p, MaxNickName, Nickname);
	p += MaxNickName;

	Write8(p, Gender);
	Write8(p, Country);

	Write16(p, ItemNum); //AddItemNum
	{
		for (size_t i = 0; i < ItemNum; i++)
		{
			BYTE* pItemInfo = p;
			Write16(pItemInfo, 0); //len

			Write32(pItemInfo, Items[i].ItemID);
			Write32(pItemInfo, Items[i].ItemNum);
			Write32(pItemInfo, Items[i].AvailPeriod);
			Write8(pItemInfo, Items[i].Status);
			Write32(pItemInfo, Items[i].ObtainTime);
			Write32(pItemInfo, Items[i].OtherAttribute);
#ifndef ZingSpeed
			Write16(pItemInfo, Items[i].ItemType); //ItemType
#endif

			len = pItemInfo - p;
			Set16(p, (WORD)len);
			p += len;
		}
	}

	Write16(p, 0); //AddTaskNum

	Write8(p, 0); //ReasonLen


	len = p - buf;
	SendToClient(Client, 129, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}
void InsertItem(ClientNode* Client)//通知客户端加全部数据
{
	
	const char* sql,*sql2;
	sqlite3_stmt* stmt = NULL;
	//sqlite3_stmt* stmt2 = NULL;
	int result, result2;
	bool hasMore=true;
	ItemInfo Items[200];//一次发送200条数据 老方法会卡400上限 通过responselogin后调用
	size_t ItemNum = 0;
	sql = "SELECT ItemID,ItemNum,AvailPeriod,Status,ObtainTime,OtherAttribute  FROM Item WHERE Uin = ? ;";
	//sql2 = "SELECT ShapeSuitID  FROM KartRefit WHERE Uin = ? and KartID = ? ;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	//result2 = sqlite3_prepare_v2(PlayerDB, sql2, -1, &stmt2, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Uin);
	}
	else
	{
		printf("%s\n", sqlite3_errmsg(PlayerDB));
		sqlite3_finalize(stmt);
		stmt = NULL;
	}
	if (stmt)
	{
		while (hasMore)
		{
			ItemNum = 0;
			hasMore = false;
			while (sqlite3_step(stmt) == SQLITE_ROW)
			{
				Items[ItemNum].ItemID = sqlite3_column_int(stmt, 0);
				Items[ItemNum].ItemNum = sqlite3_column_int(stmt, 1);
				Items[ItemNum].AvailPeriod = sqlite3_column_int(stmt, 2);
				Items[ItemNum].Status = sqlite3_column_int(stmt, 3);
				Items[ItemNum].ObtainTime = sqlite3_column_int(stmt, 4);
				Items[ItemNum].OtherAttribute = sqlite3_column_int(stmt, 5);
				Items[ItemNum].ItemType = 0;

				if (Items[ItemNum].Status && GetItemType(Items[ItemNum].ItemID) == EAIT_CAR)
				{
					Client->KartID = Items[ItemNum].ItemID;
					//printf("KartID:%d\n", Client->KartID);
				}

				ItemNum++;
				if (ItemNum >=200)
				{
					hasMore = true;
					break;
				}
			}
			NotifyClientAddItem(Client, ItemNum, Items);
			ItemStatus NewStatus;
			for (size_t i = 0; i < ItemNum; i++)
			{
				if (Items[i].Status)
				{
					NewStatus.ItemID = Items[i].ItemID;
					NewStatus.NewStatus = true;
					ResponseChangeItemStatus(Client, 1,&NewStatus);
				}
			}

		}
		sqlite3_finalize(stmt);
		stmt = NULL;

	}
}
void initiOtherInfo(ClientNode* Client)
{
	char* NickName = NULL;
	char* newname = NULL;
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	const char * sql2;
	sqlite3_stmt* stmt2 = NULL;
	int result2;
	sql2 = "SELECT ShapeSuitID  FROM KartRefit WHERE Uin = ? and KartID = ? ;";
	result2 = sqlite3_prepare_v2(PlayerDB, sql2, -1, &stmt2, NULL);
	if (result2 == SQLITE_OK) {
		sqlite3_bind_int(stmt2, 1, Client->Uin);
		sqlite3_bind_int(stmt2, 2, Client->KartID);
		if (sqlite3_step(stmt2) == SQLITE_ROW)
		{
			Client->KartSkinID = sqlite3_column_int(stmt2, 0);
			//printf("Client->KartSkinID:%d\n", Client->KartSkinID);
		}
	}
	sqlite3_finalize(stmt2);
	stmt2 = NULL;

	//查询PetItem所有宠物id 并查看Item是否有装备的宠物
	//多表联合查询
	sql2 = "SELECT P.PetID,P.Status FROM PetItem P join Item I on P.PetID=I.ItemID where I.Status=1 and I.Uin=?;";
	result2 = sqlite3_prepare_v2(PlayerDB, sql2, -1, &stmt2, NULL);
	if (result2 == SQLITE_OK) {
		sqlite3_bind_int(stmt2, 1, Client->Uin);
		if (sqlite3_step(stmt2) == SQLITE_ROW)
		{
			Client->PetID = sqlite3_column_int(stmt2, 0);
			Client->PetStatus = sqlite3_column_int(stmt2, 1);
		}
	}
	sqlite3_finalize(stmt2);
	stmt2 = NULL;

	//查询改装加成
	sql2 = "SELECT Status FROM Item Where ItemId=?;";
	result2 = sqlite3_prepare_v2(PlayerDB, sql2, -1, &stmt2, NULL);
	if (result2 == SQLITE_OK) {
		sqlite3_bind_int(stmt2, 1, 120258);
		if (sqlite3_step(stmt2) == SQLITE_ROW) {
			Client->GlobalAddcard = sqlite3_column_int(stmt2, 0);
		}
	}
	sqlite3_finalize(stmt2);
	stmt2 = NULL;

	//查询宝石加成
	sql2 = "SELECT Status FROM Item Where ItemId=?;";
	result2 = sqlite3_prepare_v2(PlayerDB, sql2, -1, &stmt2, NULL);
	if (result2 == SQLITE_OK) {
		sqlite3_bind_int(stmt2, 1, 18554);
		if (sqlite3_step(stmt2) == SQLITE_ROW) {
			Client->GlobalStone = sqlite3_column_int(stmt2, 0);
		}
	}
	sqlite3_finalize(stmt2);
	stmt2 = NULL;

	//查询用户名称,魅力
	sql = "SELECT NickName,Charm FROM BaseInfo  WHERE Uin=?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Uin);
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW)
		{
			NickName = (char*)sqlite3_column_text(stmt, 0);
			newname = myutf8trans(NickName);
			Client->Charm= sqlite3_column_int(stmt, 1);
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;
	if (newname)
	{
		memset(Client->NickName, 0, 17);
		memcpy(Client->NickName, newname, strlen(newname));
		delete[] newname;
		newname = NULL;
	}
}
void NotifyS2CMyKartAltasMoreInfo(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
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
	Write8(p, 0); //HasNext

	len = p - buf;
	SendToClient(Client, 13704, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}
void NotifyS2CMyKartAltas(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	//UINT Karts[3] = { 129099,119059 ,109563 };
	Write32(p, Client->Uin); //Uin
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

			Write32(pAltasCurKartAttr, Client->Uin); //Uin
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

			Write32(pAltasKartStoneGrooveInfo,0); //KartID
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
	SendToClient(Client, 13706, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void NotifyTaskProgressRate(ClientNode* Client,UINT TaskID, UINT ProgressRate, UINT Status)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	{ //TaskStatusInfo
		BYTE* pTaskStatusInfo = p;
		Write16(pTaskStatusInfo, 0); //len

		Write32(pTaskStatusInfo, TaskID); //TaskID
		Write8(pTaskStatusInfo, Status); //Status
		Write32(pTaskStatusInfo, ProgressRate); //ProgressRate
		Write32(pTaskStatusInfo, 0); //Other
		Write32(pTaskStatusInfo, 0); //LastUpdateTime

		len = pTaskStatusInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write8(p, 0); //RandTaskUpdateFlag

	len = p - buf;
	SendToClient(Client, 536, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}




void NotifyTaskAward(ClientNode* Client, UINT TaskID)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;
	ItemInfo* Items=NULL;
	size_t allitem;
	try
	{
		YAML::Node Config = YAML::LoadFile("OnlineAward.yml");
		allitem = Config.size();
		Items = new ItemInfo[allitem];
		memset(Items, 0, sizeof(ItemInfo) * allitem);
		for (int j = 0; j < allitem; j++)
		{
			YAML::Node ItemCfg = Config[j];//0开头
			Items[j].ItemID = ItemCfg["ItemId"].as<int>();
			Items[j].ItemNum = ItemCfg["ItemNum"].as<int>();
			Items[j].ObtainTime = ItemCfg["ObtainTime"].as<int>();
			Items[j].AvailPeriod = ItemCfg["AvailPeriod"].as<int>();
			ItemCfg.reset();
		}
	}
	catch (const std::exception&)
	{
		if (Items)
		{
			delete[] Items;
		}
		printf("在线半小时奖励配置异常!\n");
		return;
	}
	Write32(p, Client->Uin); // Uin
	Write32(p, TaskID);		 // TaskID
	
	
	{						 // TaskAward
		BYTE* pTaskAward = p;
		Write16(pTaskAward, 0); // len

		Write32(pTaskAward, 999999999); // AwardMoney
		Write32(pTaskAward, 999999999); // TotalMoney
		Write32(pTaskAward, 999999999); // AwardSuperMoney
		Write32(pTaskAward, 999999999); // TotalSuperMoney
		Write32(pTaskAward, 999999999); // AwardExp
		Write32(pTaskAward, 999999999); // TotalExp
		Write32(pTaskAward, allitem);	   // AwardItemNum
		for (size_t i = 0; i < allitem; i++)
		{ // AwardItemInfo
			BYTE* pAwardItemInfo = pTaskAward;
			Write16(pAwardItemInfo, 0); // len

			Write32(pAwardItemInfo, Items[i].ItemID); // ItemID
			Write32(pAwardItemInfo, Items[i].ItemNum);		// ItemNum
			Write32(pAwardItemInfo, Items[i].AvailPeriod);	// AvailPeriod
			Write8(pAwardItemInfo, 0);		// Status
			Write32(pAwardItemInfo, Items[i].ObtainTime);		// ObtainTime
			Write32(pAwardItemInfo, 0);		// OtherAttribute
			Write16(pAwardItemInfo, 0);		// ItemType

			len = pAwardItemInfo - pTaskAward;
			Set16(pTaskAward, (WORD)len);
			pTaskAward += len;
			PlayerDB_AddItem(Client, Client->Uin, Items[i].ItemID, Items[i].ItemNum, Items[i].AvailPeriod, 0);
		}
		Write32(pTaskAward, 999999999); // AwardCoupons
		Write32(pTaskAward, 999999999); // TotalCoupons
		Write32(pTaskAward, 999999999); // AwardLuckMoney
		Write32(pTaskAward, 999999999); // TotalLuckMoney
		Write32(pTaskAward, 0); // AwardTeamWorkExp
		Write32(pTaskAward, 0); // TotalTeamWorkExp
		Write32(pTaskAward, 0); // AwardWlCash
		Write32(pTaskAward, 0); // AwardWlCrystal
		Write32(pTaskAward, 0); // AwardWlDegree
		Write32(pTaskAward, 0); // ChumCircleActivity
		Write32(pTaskAward, 0); // GuildScore
		Write16(pTaskAward, 0); // AppellcationID
		Write16(pTaskAward, 0); // ScoreJingJi
		Write8(pTaskAward, 0);	// ExtendInfoNum
		Write32(pTaskAward, 0); // LiveExp
		Write32(pTaskAward, 0); // AwardSpeedCoin
		Write32(pTaskAward, 999999999); // TotalSpeedCoin

		len = pTaskAward - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write32(p, 0);				// NextTaskID
	Write16(p, 0);				// Type
	Write32(p, 0); // TaskWindowType
	Write8(p, 0);				// TaskTipsLen
	Write8(p, 0);				// ParaNum
	len = p - buf;
	SendToClient(Client, 537, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
	delete[] Items;
}
void OnlineTest()
{
	std::lock_guard<std::recursive_mutex> lg(ClientMutex);
	std::map<long, ClientNode*>::iterator iter;
	for (iter = Clients.begin(); iter != Clients.end(); iter++)
	{
		ClientNode* Client = iter->second;
		Client->OnlineTime += 60;//每次加10秒
		Client->TotalOnlineTime += 60;//每次加10秒
		if (Client->OnlineTime >= 1800)//如果在线半个小时
		{
			//发送进度
			NotifyTaskProgressRate(Client, 148, Client->OnlineTime / 60, 1);
			NotifyTaskProgressRate(Client, 149, Client->TotalOnlineTime / 60, 0);
			NotifyTaskAward(Client, 148);//发送在线奖励
			Client->OnlineTime = 0;//重置在线时间并继续检测
		}
		else
		{
			NotifyTaskProgressRate(Client, 148, Client->OnlineTime / 60, 0);
			NotifyTaskProgressRate(Client, 149, Client->TotalOnlineTime / 60, 0);
		}
	}
}

void NotifyAddTaskInfo(ClientNode* Client)
{

	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	Write16(p,5); //TaskNum
	//for (size_t i = 0; i < 1; i++)
	{ //PlayerDBTaskInfo
		BYTE* pPlayerDBTaskInfo = p;
		Write16(pPlayerDBTaskInfo, 0); //len

		Write32(pPlayerDBTaskInfo, 0x06a5); //TaskID 紫钻练习场任务 
		Write16(pPlayerDBTaskInfo, 0); //OptionID
		Write8(pPlayerDBTaskInfo, 0); //Status
		Write8(pPlayerDBTaskInfo, 0); //PrevStatus
		Write32(pPlayerDBTaskInfo, 0); //ProgressRate
		Write32(pPlayerDBTaskInfo, 0); //Other
		Write32(pPlayerDBTaskInfo, 0); //TakeTime
		Write32(pPlayerDBTaskInfo, 0); //LastUpdateTime

		len = pPlayerDBTaskInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	{ //PlayerDBTaskInfo
		BYTE* pPlayerDBTaskInfo = p;
		Write16(pPlayerDBTaskInfo, 0); //len

		Write32(pPlayerDBTaskInfo, 0x49); 
		Write16(pPlayerDBTaskInfo, 0); //OptionID
		Write8(pPlayerDBTaskInfo, 0); //Status
		Write8(pPlayerDBTaskInfo, 0); //PrevStatus
		Write32(pPlayerDBTaskInfo, 0); //ProgressRate
		Write32(pPlayerDBTaskInfo, 0); //Other
		Write32(pPlayerDBTaskInfo, 0); //TakeTime
		Write32(pPlayerDBTaskInfo, 0); //LastUpdateTime

		len = pPlayerDBTaskInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	{ //PlayerDBTaskInfo
		BYTE* pPlayerDBTaskInfo = p;
		Write16(pPlayerDBTaskInfo, 0); //len

		Write32(pPlayerDBTaskInfo, 0x6e); 
		Write16(pPlayerDBTaskInfo, 0); //OptionID
		Write8(pPlayerDBTaskInfo, 0); //Status
		Write8(pPlayerDBTaskInfo, 0); //PrevStatus
		Write32(pPlayerDBTaskInfo, 0); //ProgressRate
		Write32(pPlayerDBTaskInfo, 0); //Other
		Write32(pPlayerDBTaskInfo, 0); //TakeTime
		Write32(pPlayerDBTaskInfo, 0); //LastUpdateTime

		len = pPlayerDBTaskInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	{ //PlayerDBTaskInfo
		BYTE* pPlayerDBTaskInfo = p;
		Write16(pPlayerDBTaskInfo, 0); //len

		Write32(pPlayerDBTaskInfo, 148);
		Write16(pPlayerDBTaskInfo, 0); //OptionID
		Write8(pPlayerDBTaskInfo, 0); //Status
		Write8(pPlayerDBTaskInfo, 0); //PrevStatus
		Write32(pPlayerDBTaskInfo, 0); //ProgressRate
		Write32(pPlayerDBTaskInfo, 0); //Other
		Write32(pPlayerDBTaskInfo, 0); //TakeTime
		Write32(pPlayerDBTaskInfo, 0); //LastUpdateTime

		len = pPlayerDBTaskInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	{ //PlayerDBTaskInfo
		BYTE* pPlayerDBTaskInfo = p;
		Write16(pPlayerDBTaskInfo, 0); //len

		Write32(pPlayerDBTaskInfo, 149);
		Write16(pPlayerDBTaskInfo, 0); //OptionID
		Write8(pPlayerDBTaskInfo, 0); //Status
		Write8(pPlayerDBTaskInfo, 0); //PrevStatus
		Write32(pPlayerDBTaskInfo, 0); //ProgressRate
		Write32(pPlayerDBTaskInfo, 0); //Other
		Write32(pPlayerDBTaskInfo, 0); //TakeTime
		Write32(pPlayerDBTaskInfo, 0); //LastUpdateTime

		len = pPlayerDBTaskInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	len = p - buf;
	SendToClient(Client, 557, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}
void RequestLogin(ClientNode* Client, BYTE* Body, size_t BodyLen)//请求登录
{
	
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	UINT ClientVersion = Read32(Body);

	//QQNickName[20]
	Body += MaxQQNickName;
	//Gender
	Body += 1;
	//IconID
	Body += 1;

	UINT AttachIdentify = Read32(Body);// 确认身份
	UINT LoginType = Read32(Body);
	UINT LoaderTipVersion = Read32(Body);
	UINT ClientStatusContex = Read32(Body);
	BYTE IsSimplifyVersion = Read8(Body);
	UINT CurTopMapRecordVersion = Read32(Body);
	UINT CurKartRoomPushInfoVersion = Read32(Body);
	/*
m_sPreSvrID
m_u8TGPSignatureLen
m_uiRandomKey
m_stClientFingerprint.m_uiPID
m_stClientFingerprint.m_uiMacAddrHigh 物理地址高位
m_stClientFingerprint.m_uiMacAddrLow
m_stClientFingerprint.m_uiCPUID cpuid
m_stClientFingerprint.m_uiBiosID biosid
m_uiConnID
m_bUseTGP
m_usBarPriviSignatureLen
m_iNetBarLev
m_bReconnect
m_shLoginBuffLen
m_usClientKeyLen
m_uiPlayerFlag
m_ucLoginSrcType
m_ucRequestLoginType
m_ushNetBarTokenLen
	*/
	
	//初始化一些数据
	Client->Uin = Uin;
	Client->TaskID = 0;
	//printf("ClientVersion:%d, LoginType:%d\n", ClientVersion, LoginType);

	
	
	
	ResponseLogin(Client, ClientVersion, LoginType, 0, NULL, 0);
	InsertItem(Client);//添加背包道具
	NotifyClientVipFlag(Client);//通知客户端vip标志

	NotifyMsgBox(Client);
	NotifyRandRoomNameList(Client);
	NotifyTopListDesc(Client);
	NotifySpeed2Cfg(Client);
	NotifySvrConfig(Client);//添加服务端配置
	NotifySvrConfig2(Client);
#ifndef ZingSpeed
	NotifySvrConfig3(Client);//NPC配置
	NotifyTopUIItemInfo(Client);
	NotifyRedPointInfo(Client);

	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	KartStoneItemInfo Items[50];
	size_t ItemNum = 0;
	bool HasMoreInfo = false;
	sql = "SELECT KartID,ID  FROM KartStoneGroove WHERE Uin = ?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Uin);
	}
	else
	{
		printf("%s\n", sqlite3_errmsg(PlayerDB));
		sqlite3_finalize(stmt);
		stmt = NULL;
	}
	if (stmt)
	{
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			Items[ItemNum].KartId = sqlite3_column_int(stmt, 0);
			Items[ItemNum].StoneID = sqlite3_column_int(stmt, 1);
			ItemNum++;
			if (ItemNum >= 50)
			{
				HasMoreInfo = true;
				break;
			}
		}
	}
	NotifySkillStoneKartInfo(Client,ItemNum,Items,HasMoreInfo);//添加赛车宝石配置
	if (stmt)
	{
		while (HasMoreInfo)
		{
			ItemNum = 0;
			HasMoreInfo = false;
			while (sqlite3_step(stmt) == SQLITE_ROW)
			{
				Items[ItemNum].KartId = sqlite3_column_int(stmt, 0);
				Items[ItemNum].StoneID = sqlite3_column_int(stmt, 1);
				ItemNum++;
				if (ItemNum >= 50)
				{
					HasMoreInfo = true;
					break;
				}
			}
			NotifySkillStoneKartMoreInfo(Client, ItemNum, Items, HasMoreInfo);//添加更多赛车宝石配置
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
	}

	initiOtherInfo(Client);
	NotifyAddTaskInfo(Client);//添加任务配置
	NotifyS2CMyKartAltas(Client);//车库图集 图册
	//登录时通知 点击别人的个人信息车库会触发13705 RequestC2SSearchKartAltas消息
	NotifyRankedMatchSeasonInfo(Client, Client->Uin);//通知排位等级
	NotifySpecialActivityInfo(Client);//通知职业生涯段位信息
#endif
}
void ResponseLogin(ClientNode* Client, UINT ClientVersion, UINT LoginType, UINT ItemNum, ItemInfo* Items, bool HasMoreInfo)
{
	
	BYTE *buf = new BYTE[30720];//大包堆分配
	BYTE* p = buf;
	size_t len;
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;

	USHORT ResultID = 0;
	const char* Reason = "";
	int Identity = ID_IDENTIFY_QQLEVEL1 | ID_IDENTIFY_QQLEVEL2 | ID_IDENTIFY_QQLEVEL3 | ID_IDENTIFY_QQFLAG | ID_IDENTIFY_HAVEWORD | ID_IDENTIFY_FINISHQQFLAG;
	int IsInTopList = 0;
	if (!Client->IsLogin)
	{
		ResultID = 1;
		Reason = "the password is incorrect";
	}
	else
	{
	
		sql = "SELECT VipFlag,IsInTopList  FROM Player  WHERE Uin=?;";
		result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (result == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, Client->Uin);
			result = sqlite3_step(stmt);
			if (result == SQLITE_ROW)
			{
				ResultID = 0;
				if (sqlite3_column_int(stmt, 0) != 0)
				{
					Identity |= ID_IDENTIFY_SPEEDMEMBER;
				}
				IsInTopList = sqlite3_column_int(stmt, 1);

			}
			else
			{
				ResultID = 1; //未注册
			}
		}
		else
		{
			ResultID = 1;
			Reason = sqlite3_errmsg(PlayerDB);
			printf("%s\n", Reason);
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
	}

	Write16(p, ResultID); //ResultID 0为成功标志

	Write8(p, sizeof(Client->Key)); //KeyGameDataLength 密钥长度
	memcpy(p, Client->Key, sizeof(Client->Key));//对称加密密钥
	p += sizeof(Client->Key);

	Write32(p, Client->Uin);//用户登录id
	Write32(p, Identity);
	Write16(p, Client->ConnID); //用户连接id
	Write32(p, LoginType); //LoginType
	Write32(p, 4); //GameSvrdIdentity游戏服务标识

	WritePlayerDBBaseInfo(p, Client->Uin);//发送基础信息
	
	Write16(p, 0); //ItemNum 发送道具信息


	Write16(p, 0); //TaskNum 任务信息
	/*
m_astPlayerDBTaskInfo[].m_iTaskID
m_astPlayerDBTaskInfo[].m_shOptionID
m_astPlayerDBTaskInfo[].m_cStatus
m_astPlayerDBTaskInfo[].m_bPrevStatus
m_astPlayerDBTaskInfo[].m_iProgressRate
m_astPlayerDBTaskInfo[].m_iOther
m_astPlayerDBTaskInfo[].m_uiTakeTime
m_astPlayerDBTaskInfo[].m_uiLastUpdateTime
	*/

	Write8(p, 0); //RecomCountry
	Write32(p, (UINT)time(nullptr)); //ServerTime 服务器时间

	len = strlen(Reason);//原因
	Write8(p, (BYTE)len); //ReasonLen
	memcpy(p, Reason, len);//原因数据
	p += len;

	{ //PlayerRelationInfo玩家关系信息
		char* NickName = NULL;
		char* newname = NULL;
		sql = "SELECT EngageUin FROM EngageInfo WHERE Uin = ?;";
		result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (result == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, Client->Uin);
			if (sqlite3_step(stmt) == SQLITE_ROW)
			{
				Client->EngageUin = sqlite3_column_int(stmt, 0);
				
			}
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
	
		if (Client->EngageUin != 0)
		{
			sql = "SELECT NickName FROM BaseInfo  WHERE Uin=?;";
			result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
			if (result == SQLITE_OK) {
				sqlite3_bind_int(stmt, 1, Client->EngageUin);
				result = sqlite3_step(stmt);
				if (result == SQLITE_ROW)
				{
					NickName = (char*)sqlite3_column_text(stmt, 0);
					newname = myutf8trans(NickName);
				}
			}
			sqlite3_finalize(stmt);
			stmt = NULL;
		}

		BYTE* pPlayerRelationInfo = p;
		Write16(pPlayerRelationInfo, 0); //len
		Write32(pPlayerRelationInfo, Client->Uin); //SrcUin
		if (Client->EngageUin != 0)
		{
			Write32(pPlayerRelationInfo, 0x3); //RelationFlag
		}
		else
		{
			Write32(pPlayerRelationInfo, 0); //RelationFlag
		}
	
		Write32(pPlayerRelationInfo, Client->EngageUin); //RelationUin

		Write8(pPlayerRelationInfo, 17);//NickNameLen
		memset(pPlayerRelationInfo, 0, MaxNickName);
		//RelationNickName[]
		if (newname)
		{
			memcpy(pPlayerRelationInfo, newname, strlen(newname));
			delete[] newname;
			newname = NULL;
		}

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

	
	Write16(p, 0); //MapNum 地图数据


	if (HasMoreInfo)
	{
		Write16(p, 0); //PetNum ResponseLogin
	}
	else
	{
		const char* sql = NULL;
		sqlite3_stmt* stmt = NULL;
		int result;
		int totalpet=0;
		UINT PetID = 0;
		UINT status = 0;
		UINT level = 0;
		UINT strenglevel = 0;
		char* newname, * petname;
		UINT curskill1, curskill2, curskill3;
		UINT curskillv1, curskillv2, curskillv3;
		
		BYTE* pTotalPet = p;
		Write16(p, 0); //PetNum ResponseLogin
	/*
	* 宠物信息
	*/
		sql = "select * from PetItem;";
		result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (result == SQLITE_OK) {
			while (sqlite3_step(stmt) == SQLITE_ROW)
			{
				totalpet++;
				PetID = sqlite3_column_int(stmt, 0);
				petname = (char*)sqlite3_column_text(stmt, 1);
				newname = myutf8trans(petname);
				level = sqlite3_column_int(stmt, 2);
				status = sqlite3_column_int(stmt, 3);
				strenglevel = sqlite3_column_int(stmt, 4);
				curskill1= sqlite3_column_int(stmt, 5);
				curskillv1 = sqlite3_column_int(stmt, 6);
				curskill2 = sqlite3_column_int(stmt, 7);
				curskillv2= sqlite3_column_int(stmt, 8);
				curskill3 = sqlite3_column_int(stmt, 9);
				curskillv3 = sqlite3_column_int(stmt, 10);
				{ //PetInfo
			//国服宠物数据结构
					BYTE* pPetInfo = p;
					Write16(pPetInfo, 0); //len
					Write32(pPetInfo, Client->Uin); //Uin
					Write32(pPetInfo, PetID); //PetId  画中仙
					memset(pPetInfo, 0, 17);
					if (newname)
					{
						memcpy(pPetInfo, newname, strlen(newname));
						delete[] newname;
						newname = NULL;
					}
					pPetInfo += 17;
					
					Write32(pPetInfo, 0x00000000);//PetName[] 
					Write32(pPetInfo, 0x00000000);//PetName[] 
					Write8(pPetInfo, 0x01);//IsProper
			//后16字节
					//2字节等级
					Write16(pPetInfo, level);
					//8字节前后经验值
					Write8(pPetInfo, 0x11);
					Write8(pPetInfo, 0x11);
					Write8(pPetInfo, 0x11);
					Write8(pPetInfo, 0x11);
					Write8(pPetInfo, 0x11);
					Write8(pPetInfo, 0x11);
					Write8(pPetInfo, 0x11);
					Write8(pPetInfo, 0x11);

					Write8(pPetInfo, status); 

					//4字节前后体力值
					Write8(pPetInfo, 0x11);
					Write8(pPetInfo, 0x11);
					Write8(pPetInfo, 0x11);
					Write8(pPetInfo, 0x11);

					//所有技能如果要生效 需要对指定性能进行处理
				
					
					Write16(pPetInfo, 0x03);//SkillNum 最多3个技能
					for (size_t i = 0; i < 1; i++)
					{ //PetSkillList
						BYTE* pPetSkillList = pPetInfo;
						Write16(pPetSkillList, 0); //len
						Write16(pPetSkillList, curskill1);//SkillID //0x2撞击保护
						Write8(pPetSkillList, 0x01);//SkillStatus技能栏offset=6+10*3+6=42
						Write8(pPetSkillList, 0x01);//SkillActive
						Write32(pPetSkillList, curskillv1);//SkillValue
						len = pPetSkillList - pPetInfo;;
						Set16(pPetInfo, (WORD)len);
						pPetInfo += len;
					}
					for (size_t i = 0; i < 1; i++)
					{ //PetSkillList
						BYTE* pPetSkillList = pPetInfo;
						Write16(pPetSkillList, 0); //len
						Write16(pPetSkillList, curskill2);//SkillID 
						Write8(pPetSkillList, 0x02);
						Write8(pPetSkillList, 0x01);//SkillActive
						Write32(pPetSkillList, curskillv2);//SkillValue
						len = pPetSkillList - pPetInfo;;
						Set16(pPetInfo, (WORD)len);
						pPetInfo += len;
					}
					for (size_t i = 0; i < 1; i++)
					{ //PetSkillList
						BYTE* pPetSkillList = pPetInfo;
						Write16(pPetSkillList, 0); //len
						Write16(pPetSkillList, curskill3);//SkillID 
						Write8(pPetSkillList, 0x03);
						Write8(pPetSkillList, 0x01);//SkillActive
						Write32(pPetSkillList, curskillv3);//SkillValue
						len = pPetSkillList - pPetInfo;;
						Set16(pPetInfo, (WORD)len);
						pPetInfo += len;
					}

					Write32(pPetInfo, strenglevel); //StrengLevel强化等级 个人信息宠物图标有+5
					Write8(pPetInfo, 0x4); //TopStatus 变形形态
					//变形功能大于1开启
					{ //CommonInfo
						BYTE* pCommonInfo = pPetInfo;
						Write16(pCommonInfo, 0); //len

						Write32(pCommonInfo, 0x5); //HuanHuaLevel幻化等级
						Write8(pCommonInfo, 0x1); //CanHuanHua

						len = pCommonInfo - pPetInfo;
						Set16(pPetInfo, (WORD)len);
						pPetInfo += len;
					}
					//Write16(pPetInfo, 1); //PKStar
					//Write32(pPetInfo, 1); //PetSkinID
					len = pPetInfo - p;
					Set16(p, (WORD)len);
					p += len;
				}
			}
			Set16(pTotalPet, totalpet);
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
	}
	Write8(p, (bool)IsInTopList); //IsInTopList
	Write32(p, 0); //LastLoginTime
	Write32(p, 0); //MasterPoint
	Write8(p, 0); //LoginRealNameFlag

	//ExRightFlag[]
#ifndef ZingSpeed
	if (ClientVersion > 18457)
	{
		memset(p, 0, 24);
		p += 24;
	}
	else
#endif
	{
		memset(p, 0, 16);
		p += 16;
	}


	Write8(p, 0); //OverdueItemNum过期道具



	
	Write32(p, 0); //StoneKartNum赛车宝石数据


	Write32(p, 0); //LockedMapID
	Write32(p, 0); //TotalGuildProsperity
	Write32(p, 0); //ClientStatusContex
	Write8(p, 0); //IsHoneyMoon 
	Write8(p, HasMoreInfo); //HasMoreInfo 更多信息
	Write16(p, 0); //CurSvrID

	{ //NobleInfo 贵族信息
		BYTE* pNobleInfo = p;
		Write16(pNobleInfo, 0); //len

		Write32(pNobleInfo, Client->Uin); //NobleID
		Write8(pNobleInfo, 6); //NobleLevel
		Write32(pNobleInfo, 1); //NoblePoint
		Write32(pNobleInfo, 30); //NobleLeftDays

		len = pNobleInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write16(p, 6000); //ExtendItemNum扩展道具数量
	Write8(p, 60); //UpdateOnlineInfoInterval更新在线信息间隔

#ifndef ZingSpeed
	{ //GuildVipBaseInfo GuildVip信息车队贵族
		BYTE* pGuildVipBaseInfo = p;
		Write16(pGuildVipBaseInfo, 0); //len

		Write8(pGuildVipBaseInfo, 6); //GuildVipLevel
		Write32(pGuildVipBaseInfo, 1); //GuildVipPoint

		len = pGuildVipBaseInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	{ //GuildVipOtherInfo
		BYTE* pGuildVipOtherInfo = p;
		Write16(pGuildVipOtherInfo, 0); //len

		Write32(pGuildVipOtherInfo,30); //GuildVipLeftDays
		Write8(pGuildVipOtherInfo, 0); //CanReceiveGift

		len = pGuildVipOtherInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
#endif
	Write8(p, 0); //HasLDMInfo
	/*
m_astPlayerLDMBaseInfo[%d].m_u8Grade
m_astPlayerLDMBaseInfo[%d].m_u32Score
m_astPlayerLDMBaseInfo[%d].m_u32MaxScore
m_astPlayerLDMBaseInfo[%d].m_u32MaxGrade
	*/

	Write32(p, 0); //ForbiddenModeFreeTime禁止模式空闲时间
	Write32(p, 0); //ForbiddenModeBitSet

#ifndef ZingSpeed
	{ //LoverVipBaseInfo 情侣贵族信息
		BYTE* pLoverVipBaseInfo = p;
		Write16(pLoverVipBaseInfo, 0); //len

		Write8(pLoverVipBaseInfo, 6); //LoverVipLevel
		Write32(pLoverVipBaseInfo,1); //LoverVipPoint
		Write8(pLoverVipBaseInfo, 0); //GrowRate

		len = pLoverVipBaseInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	{ //LoverVipOtherInfo
		BYTE* pLoverVipOtherInfo = p;
		Write16(pLoverVipOtherInfo, 0); //len

		Write32(pLoverVipOtherInfo, 30); //LoverVipLeftDays
		Write8(pLoverVipOtherInfo, 1); //CanReceiveGift
		Write8(pLoverVipOtherInfo, 0); //ShowExpireTips

		len = pLoverVipOtherInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
#endif
	Write8(p, 0); //SkateTaskLevel 轮滑任务级别
	Write32(p, 0); //SkateCoin
	Write8(p, 0); //SkateExpSkillLevel
	Write16(p, 0); //SkateCoinCountDaily
	Write32(p, 0); //SkateCoinHistoryTotal
	Write32(p, 0); //MaxDayPveScore
	Write32(p, 0); //MaxHistoryPveScore

#ifndef ZingSpeed
	Write32(p, 0); //LoveValue

	Write8(p, 0); //HasCheerAddition 欢呼值添加
	/*
m_astCheerAdditon[%d].m_ushExpAddition
m_astCheerAdditon[%d].m_ushWageAddition
	*/

	{ //PersonalGardenBaseInfo个人花园基本信息
		BYTE* pPersonalGardenBaseInfo = p;
		Write16(pPersonalGardenBaseInfo, 0); //len

		Write8(pPersonalGardenBaseInfo, 6); //GardenLevel
		Write32(pPersonalGardenBaseInfo, 1); //GardenPoint
		Write8(pPersonalGardenBaseInfo, 30); //GrowRate
		Write32(pPersonalGardenBaseInfo, 0); //GardenExpireTime
		{ //SimpleInfo
			BYTE* pSimpleInfo = pPersonalGardenBaseInfo;
			Write16(pSimpleInfo, 0); //len

			Write32(pSimpleInfo, 0); //WeekPopularity
			Write32(pSimpleInfo, 0); //TotalPopularity
			Write32(pSimpleInfo, 0); //LastUpdatePopularityTime
			Write8(pSimpleInfo, 0); //PrivateType

			len = pSimpleInfo - pPersonalGardenBaseInfo;
			Set16(pPersonalGardenBaseInfo, (WORD)len);
			pPersonalGardenBaseInfo += len;
		}

		len = pPersonalGardenBaseInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	{ //ConsumeVipInfo消费Vip
		BYTE* pConsumeVipInfo = p;
		Write16(pConsumeVipInfo, 0); //len

		Write32(pConsumeVipInfo, 6); //VipLevel
		Write32(pConsumeVipInfo, 0); //CharmValueOfMonth
		Write32(pConsumeVipInfo, 0); //SearchTreasureNums
		Write32(pConsumeVipInfo, 0); //GetTreasureNums

		len = pConsumeVipInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	{ //EmperorInfo钻皇信息
		BYTE* pEmperorInfo = p;
		Write16(pEmperorInfo, 0); //len

		Write8(pEmperorInfo, 6); //EmperorLevel
		Write32(pEmperorInfo, 1); //EmperorPoint
		Write32(pEmperorInfo, 30); //EmperorLeftDays
		Write8(pEmperorInfo, 0); //EmperorGrowRate

		len = pEmperorInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	{ //EmperorOtherInfo
		BYTE* pEmperorOtherInfo = p;
		Write16(pEmperorOtherInfo, 0); //len

		Write32(pEmperorOtherInfo, 0); //ExpiredTime
		Write8(pEmperorOtherInfo, 0); //ShowExpireTips

		len = pEmperorOtherInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write32(p, 0); //ShuttleScoreWeek


	{ //ActivityInfo活动信息
		BYTE* pActivityInfo = p;
		Write16(pActivityInfo, 0); //len

		Write32(pActivityInfo, 0); //TotalActivity
		Write32(pActivityInfo, 0); //ActivityLevel

		len = pActivityInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	{ //GansterScoreInfo
		BYTE* pGansterScoreInfo = p;
		Write16(pGansterScoreInfo, 0); //len

		Write32(pGansterScoreInfo, 0); //GansterSeasonID
		Write32(pGansterScoreInfo, 0); //GansterScore
		Write32(pGansterScoreInfo, 0); //PoliceScore
		Write32(pGansterScoreInfo, 0); //TotalGansterScore

		len = pGansterScoreInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write32(p, 0); //OlympicId
	Write32(p, 0); //NPCEliminateWinTimes

	{ //BorderInfo
		BYTE* pBorderInfo = p;
		Write16(pBorderInfo, 0); //len

		Write32(pBorderInfo, 0x2b); //SeasonID
		Write32(pBorderInfo, 0x3); //Zhanxun
		Write32(pBorderInfo, 0x3); //SeasonZhanxun

		len = pBorderInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write32(p, 0); //ReduceReturnRate
	Write32(p, 0); //ReduceReturnAvailPeriod
	Write8(p, 0); //SpecialActivityStatus
	Write32(p, 0); //ThemeHouseDressDegreeValue

	Write32(p, 1); //3DRoomEnabled
	Write8(p,1); //3DRoomEnabled_OB
	Write8(p, 0); //BuyZizuanPopupOpen

	Write32(p, 0); //BuyZizuanPopupLimit
	Write8(p, 1); //EnableReconnectOpt

		//查询排位信息
	const char* sql2 = NULL;
	sqlite3_stmt* stmt2 = NULL;
	int result2;
	sql = "SELECT GradeScore,GradeLevel FROM RankInfo Where Uin=?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Uin);
		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
			Client->GradeScore = sqlite3_column_int(stmt, 0);
			Client->GradeLevel = sqlite3_column_int(stmt, 1);
			if (Client->GradeLevel > 7)
			{
				Client->GradeLevel = 7;
			}
		}
		else
		{
			//查询不到执行插入操作
			sql2 = "INSERT INTO RankInfo VALUES (?,?,?);";
			result2 = sqlite3_prepare_v2(PlayerDB, sql2, -1, &stmt2, NULL);
			if (result2 == SQLITE_OK) {
				sqlite3_bind_int(stmt2, 1, Client->Uin);
				sqlite3_bind_int(stmt2, 2, 0);
				sqlite3_bind_int(stmt2, 3, 0);
				result2 = sqlite3_step(stmt2);
			}
			sqlite3_finalize(stmt2);
			stmt2 = NULL;
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;

	Write8(p, 1); //HasRankedMatchInfo
	{ //RankedMatchGradeInfo
		BYTE* pRankedMatchGradeInfo = p;
		Write16(pRankedMatchGradeInfo, 0); //len

		Write32(pRankedMatchGradeInfo, RankGradeLevel[Client->GradeLevel]); //GradeLevel 排位等级图标
		Write32(pRankedMatchGradeInfo, 1); //ChildLevel
		Write32(pRankedMatchGradeInfo, 0); //GradeScore
		Write32(pRankedMatchGradeInfo, 0); //MaxGradeScore
		Write32(pRankedMatchGradeInfo, 0); //TotalScore

		len = pRankedMatchGradeInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write8(p, 0); //HasHuanLingChangeInfo
	/*
m_astHuanLingSuitInfo[%d].m_iSuitID
m_astHuanLingSuitInfo[%d].m_ucChangeLevel
	*/

	Write8(p, 0); //EquipSealType
	Write8(p, 0); //hCreditStarFlag
	Write8(p, 0); //PersonalPanelSelectRankedMatchFrameTag
	Write8(p, 0); //VersionURLLen
	Write8(p, 0); //PrivacyURLLen
	Write8(p, 0); //PersonalRankedMatchLevelShowTag
	Write16(p, 0); //LeftDeletingRoleDays
	Write8(p, 0); //OnlyRspEquippedItem
	Write32(p, 0); //LoginSwitchFlag1
	Write16(p, 0); //LeftUploadPLogNum
#endif

	len = p - buf;
	int MsgID = GetServerType(Client->ServerID);
	if (MsgID == Relax)
	{
		MsgID = 98;
	}
	else if (MsgID == Dance)
	{
		MsgID = 95;
	}
	else
	{
		if (ResultID == 0)
		{//顶号
			ClientNode* OldClient = GetClient(Client->Uin);
			if (OldClient != NULL)
			{
			
				BYTE* buf2 = msg900;
				buf2 += 2;
				Write32(buf2, Client->Uin);
				SendToClient(OldClient, 900,msg900 , 52, OldClient->ConnID, FE_PLAYER, OldClient->ConnID, Notify);
			}
		}
		//DWORD dwStart = GetTickCount64(); //取windows启动到现在的流逝时间(毫秒)
		std::lock_guard<std::recursive_mutex> lg(ClientMutex);
		Clients[Client->Uin] = Client;
		Client->OnlineTime = 0;
		Client->TotalOnlineTime = 0;
		//DWORD dwUsed = GetTickCount64() - dwStart; //计算该函数所消耗的时间
		//printf("Clients Add lost:%d ms\n", dwUsed);
		MsgID = 100;//回复RequestLogin消息id
	}
	
	//printf("ServerID:%d\n", Client->ServerID);
	SendToClient(Client, MsgID, buf, len, Client->ConnID, FE_GAMESVRD, Client->ConnID, Response);

	delete[] buf;
}
void NotifyLoginMoreInfo(ClientNode* Client, UINT ItemNum, ItemInfo* Items, bool HasNext)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;


	Write16(p, ItemNum); //ItemNum
	{
		for (size_t i = 0; i < ItemNum; i++)
		{
			BYTE* pItemInfo = p;
			Write16(pItemInfo, 0); //len

			Write32(pItemInfo, Items[i].ItemID);
			Write32(pItemInfo, Items[i].ItemNum);
			Write32(pItemInfo, Items[i].AvailPeriod);
			Write8(pItemInfo, Items[i].Status);
			Write32(pItemInfo, Items[i].ObtainTime);
			Write32(pItemInfo, Items[i].OtherAttribute);
#ifndef ZingSpeed
			Write16(pItemInfo, Items[i].ItemType); //ItemType
#endif

			len = pItemInfo - p;
			Set16(p, (WORD)len);
			p += len;
		}
	}

	Write16(p, 0); //TaskNum
	/*
m_astPlayerDBTaskInfo[].m_iTaskID
m_astPlayerDBTaskInfo[].m_shOptionID
m_astPlayerDBTaskInfo[].m_cStatus
m_astPlayerDBTaskInfo[].m_bPrevStatus
m_astPlayerDBTaskInfo[].m_iProgressRate
m_astPlayerDBTaskInfo[].m_iOther
m_astPlayerDBTaskInfo[].m_uiTakeTime
m_astPlayerDBTaskInfo[].m_uiLastUpdateTime
	*/

	Write16(p, 0);//PetNum




	
	Write16(p, 0); //MapNum
	/*
m_astRecord[].m_iMapID
m_astRecord[].m_iRecord
m_astRecord[].m_iLastUpdateTime
	*/


	Write16(p, 0); //OverdueItemNum
	/*
m_astOverdueItem[].m_iItemID
m_astOverdueItem[].m_iOverdueTime
m_astOverdueItem[].m_iOtherAttr
	*/

	Write16(p, 0); //StoneKartNum 赛车宝石数量
	/*
m_astKartStoneGrooveInfo[].m_iKartID
m_astKartStoneGrooveInfo[].m_iStoneGrooveNum
m_astKartStoneGrooveInfo[].m_astStoneGrooveInfo[].m_iStoneUseOccaType
m_astKartStoneGrooveInfo[].m_astStoneGrooveInfo[].m_iSkillStoneID
	*/

	Write8(p, HasNext);


	len = p - buf;
	SendToClient(Client, 223, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}


void RequestLogout(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	UINT LogOutFlag = Read32(Body);
	int ServerKickReason = Read32(Body);

	ResponseLogout(Client);
	Client->Server->Disconnect(Client->ConnID);
}
void ResponseLogout(ClientNode* Client)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID
	Write8(p, 0); //ReasonLen

	len = p - buf;
	SendToClient(Client, 101, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestHello(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	ResponseHello(Client, Uin, Time);
}
void ResponseHello(ClientNode* Client, UINT Uin, UINT Time)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID
	Write8(p, 0); //ReasonLen
	Write32(p, Time); //Time
	Write32(p, Uin); //Uin
	Write32(p, (DWORD)time(nullptr)); //ServerTime
#ifndef ZingSpeed
	Write32(p, 0); //ServerMicroSecond
#endif

	len = p - buf;
	
	SendToClient(Client, 112, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}


void RequestChangeGender(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	BYTE NewGender = Read8(Body);


	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;

	sql = "UPDATE BaseInfo SET Gender=?  WHERE Uin=? ;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, NewGender);
		sqlite3_bind_int(stmt, 2, Client->Uin);
		result = sqlite3_step(stmt);
	}
	else
	{
		printf("%s\n", sqlite3_errmsg(PlayerDB));
	}
	sqlite3_finalize(stmt);
	stmt = NULL;

	ResponseChangeGender(Client, NewGender, 0);
}
void ResponseChangeGender(ClientNode* Client, BYTE NewGender, BYTE UseType)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID

	Write8(p, NewGender);
	Write8(p, 0); //ReasonLen
#ifndef ZingSpeed
	Write8(p, UseType);
#endif

	len = p - buf;
	SendToClient(Client, 162, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void NotifyChangeItemStatus(ClientNode* Client, ClientNode* MyClient, USHORT ItemNum, ItemStatus* ItemStatus)
{
	//通知所有人变化装备 有皮肤直接更新皮肤
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
	USHORT KartNum = 0;

	
	Write32(p, MyClient->Uin);
	if (GetItemType(ItemStatus[0].ItemID) == EAIT_CAR&& 96462 != ItemStatus[0].ItemID && 95405 != ItemStatus[0].ItemID&& ItemStatus[0].ItemID!=Client->KartSkinID)
	{
		KartNum = 1;
		sql = "SELECT KartHeadRefitItemID,KartTailRefitItemID,KartFlankRefitItemID,KartTireRefitItemID,ShapeSuitID FROM KartRefit WHERE Uin = ? and KartID = ?;";
		result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (result == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, MyClient->Uin);
			sqlite3_bind_int(stmt, 2, MyClient->KartID);
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
	}
	Write16(p, ItemNum);
	for (size_t i = 0; i < ItemNum; i++)
	{
		BYTE* pItemStatus = p;
		Write16(pItemStatus, 0); //len

		Write32(pItemStatus, ItemStatus[i].ItemID);
		Write32(pItemStatus, 1); //ItemNum
		Write32(pItemStatus, -1); //AvailPeriod
		Write8(pItemStatus, ItemStatus[i].NewStatus); //Status
		Write32(pItemStatus, 1); //ObtainTime
		Write32(pItemStatus, 0); //OtherAttribute
		Write16(pItemStatus, 0); //ItemType

		len = pItemStatus - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write8(p, 0); //SpecFlag

	Write16(p, KartNum); //KartNum
	for (size_t i = 0; i < KartNum; i++)
	{ //KartRefitInfo
		BYTE* pKartRefitInfo = p;
		Write16(pKartRefitInfo, 0); //len

		Write32(pKartRefitInfo, MyClient->Uin); //Uin
		Write32(pKartRefitInfo, ItemStatus[0].ItemID); //KartId
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
	Write8(p, 0); //ChangeType

#ifndef ZingSpeed
	Write8(p, 0); //EquipNiChangItemNum

#endif



	len = p - buf;
	SendToClient(Client, 527, buf, len, Client->RoomID, FE_ROOM, Client->ConnID, Notify);
}

void RequestChangeItemStatus(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	//修改当前装备状态 赛车数据库status 1 为装备上 0为卸下
	//0 0 27 11 0 2b 37 b3 0 2 0 7 0 1 8d fd 1 0 7 0 1 f2 80 0 0 0 0 0 0 0 0 0 d0 25
	// 回复
	// // 0000+item数量如0002+长度0007+变更装备id如0001d117+状态01+长度0007+当前装备id如0002724+状态00+000000
	

	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	USHORT ItemNum = Read16(Body);

	if (ItemNum == 0)
	{
		return;
	}
	ItemStatus* aItemStatus = new ItemStatus[ItemNum];
	if (!aItemStatus)
	{
		return;
	}
	for (size_t i = 0; i < ItemNum; i++)
	{
		BYTE* pItemStatus = Body;
		USHORT len = Read16(pItemStatus);

		aItemStatus[i].ItemID = Read32(pItemStatus);
		aItemStatus[i].NewStatus = Read8(pItemStatus);

		Body += len;
	}
	/*
m_ucSpecFlag
m_ucChangeType
m_usItemNum
m_stEquipedItem[]
m_iNewKartID
	*/

	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;

	
	
	if (95405 == aItemStatus[0].ItemID)//机甲特别处理
	{
		aItemStatus[0].ItemID = 12720;
	}
	if (96462 == aItemStatus[0].ItemID)
	{
		aItemStatus[0].ItemID = 34393;
	}
	//sql = "BEGIN"; //开始事务，事务更快
	sql = "UPDATE Item SET Status=? WHERE Uin=? AND ItemID=?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	sqlite3_exec(PlayerDB, "BEGIN", NULL, NULL, NULL);
	for (size_t i2 = 0; i2 < ItemNum; i2++)
	{
		//循环修改当前装备状态 第一次修改是新装备status为1 第二次是老装备 status为0
		//size_t i = 0;
		if (result == SQLITE_OK) {
			if (i2 == 0)//新装备设置为1
			{
				//如果1&&车辆类型为1 则设置新的车辆id
				if (GetItemType(aItemStatus[i2].ItemID) == EAIT_CAR)
				{
					//这是新车
					Client->KartID = aItemStatus[i2].ItemID;//返回给客户端设置的车辆id
					//printf("NewKartID:%d\n", Client->KartID);
				}
				sqlite3_bind_int(stmt, 1, 0x01);
				//printf("NewItemID:%d\n", aItemStatus[i2].ItemID);
			}
			else
			{
				sqlite3_bind_int(stmt, 1, 0x00);
			}
			if (ItemNum == 1)
			{
				if (aItemStatus[0].ItemID == 120258)//改装加成卡
				{
					if (aItemStatus[0].NewStatus == 1)
					{
						Client->GlobalAddcard = 1;
					}
					else
					{
						Client->GlobalAddcard = 0;
					}
				}
				else if (aItemStatus[0].ItemID == 18554)//奶糖宝石加成卡
				{
					if (aItemStatus[0].NewStatus == 1)
					{
						Client->GlobalStone = 1;
					}
					else
					{
						Client->GlobalStone = 0;
					}
				}
				sqlite3_bind_int(stmt, 1, aItemStatus[i2].NewStatus);
			}
			sqlite3_bind_int(stmt, 2, Client->Uin);
			sqlite3_bind_int(stmt, 3, aItemStatus[i2].ItemID);
			sqlite3_step(stmt);
			
		}
		sqlite3_reset(stmt);
	}
	sqlite3_exec(PlayerDB, "COMMIT", NULL, NULL, NULL);//提交事务
	sqlite3_finalize(stmt);
	stmt = NULL;
	
	//查询是否是装备的宠物
	if (aItemStatus[0].NewStatus == 1)
	{
		sql = "SELECT Status FROM PetItem where PetID=? ;";
		result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (result == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, aItemStatus[0].ItemID);
			if (sqlite3_step(stmt) == SQLITE_ROW)
			{
				//查到是装备的宠物
				Client->PetID = aItemStatus[0].ItemID;
				Client->PetStatus = sqlite3_column_int(stmt, 0);
			}
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
	}
	
	ResponseChangeItemStatus(Client, ItemNum, aItemStatus);
	do
	{
		RoomNode* Room = GetRoom(Client->RoomID);
		if (!Room)
		{
			break;
		}
		for (char i = 0; i < 6; i++)
		{
			ClientNode* RoomClient = Room->Player[i];
			if (RoomClient)
			{
				if (RoomClient != Client)
				{
					NotifyChangeItemStatus(RoomClient, Client, ItemNum, aItemStatus);
				}
			}
		}
	} while (false);
	delete[] aItemStatus;
}

void ResponseChangeItemStatus(ClientNode* Client, USHORT ItemNum, ItemStatus* ItemStatus)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;
	UINT NewShapeSuitID = 0;
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	char ItemType = 0;
	if (GetItemType(ItemStatus[0].ItemID) == EAIT_CAR)//如果是更换车辆
	{
		ItemType = EAIT_CAR;
		sql = "SELECT ShapeSuitID FROM KartRefit Where Uin=? and KartID=?;";
		result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (result == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, Client->Uin);
			sqlite3_bind_int(stmt, 2, ItemStatus[0].ItemID);
			if (sqlite3_step(stmt) == SQLITE_ROW)
			{
				NewShapeSuitID = sqlite3_column_int(stmt, 0);
			}
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
		if (0 != NewShapeSuitID)//如果存在皮肤
		{
			Client->KartSkinID = NewShapeSuitID;
		}
		else
		{
			Client->KartSkinID = 0;
		}
	}
	

	Write16(p, 0); //ResultID

	Write16(p, ItemNum);

	for (size_t i = 0; i < ItemNum; i++)
	{
		BYTE* pItemStatus = p;
		Write16(pItemStatus, 0); //len

		Write32(pItemStatus, ItemStatus[i].ItemID);
		Write8(pItemStatus, ItemStatus[i].NewStatus);

		len = pItemStatus - p;//长度 指针相减得到 2+4+1=7
		Set16(p, (WORD)len);
		p += len;
	}

	Write8(p, 0); //ReasonLen

	Write8(p, 0); //SpecFlag
	Write8(p, 0); //ChangeType


	len = p - buf;
	//数据包Body分析 
	// 0000+item数量如0002+长度0007+变更装备id如0001d117+状态01
	//+长度0007+当前装备id如0002724+状态00+000000
	//printf("变更装备发送内容： \n");
	// printf("内容大小：%d\n", len);
	//for (int i = 0;i < len;i++)
	//{
	//	printf("%x ", *(buf+i));
	//}
	//printf("\n");
	SendToClient(Client, 130, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}


void RequestChangeModel(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);
	BYTE NewModel = Read8(Body);
	//UCHAR UseType = Read8(Body);

	ResponseChangeModel(Client, NewModel);
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
				NotifyChangeModel(RoomClient, Client->Uin, NewModel);
			}
		}
	}
}
void ResponseChangeModel(ClientNode* Client, BYTE NewModel)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, 0); //ResultID
	Write8(p, 0); //ReasonLen
	Write8(p, NewModel);
#ifndef ZingSpeed
	Write8(p, 0); //UseType
	Write8(p, 0); //TDCExcluItemNum
	//Write32(p, 0); //TDCExclusiveItemID[]
#endif

	len = p - buf;
	SendToClient(Client, 277, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}
void NotifyChangeModel(ClientNode* Client, UINT Uin, BYTE NewModel)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write32(p, Uin);
	Write8(p, NewModel);
#ifndef ZingSpeed
	Write8(p, 0); //TDCExcluItemNum
	//Write32(p, 0); //TDCExclusiveItemID[]
#endif

	len = p - buf;
	SendToClient(Client, 278, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void NotifyClientVipFlag(ClientNode* Client)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write32(p, Client->Uin); //Uin
	Write16(p, 0x0106); //VipFlag
	Write16(p, 0); //MsgLen
	Write16(p, 0); //VipGrowRate

	len = p - buf;
	SendToClient(Client, 948, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}


void RequestInlaySkillStone(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);
	int KartID = Read32(Body);
	int StoneGrooveID = Read32(Body);
	int SkillStoneID = Read32(Body);

	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;


	int ID = -1;
	sql = "SELECT ID  FROM KartStoneGroove  WHERE Uin=? AND KartID=?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Uin);
		sqlite3_bind_int(stmt, 2, KartID);
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW)
		{
			ID = sqlite3_column_int(stmt, 0);
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;
	if (ID != -1)
	{
		sql = "UPDATE KartStone SET StoneUseOccaType=?,SkillStoneID=?  WHERE ID=? AND StoneGrooveID=?;";
		result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (result == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, 0);
			sqlite3_bind_int(stmt, 2, SkillStoneID);
			sqlite3_bind_int(stmt, 3, ID);
			sqlite3_bind_int(stmt, 4, StoneGrooveID);
			result = sqlite3_step(stmt);
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
	}
	NotifyUpdateKartSkillStoneInfo(Client, KartID);
	NotifyUseItemResult2(Client, SkillStoneID, 1);
	ResponseInlaySkillStone(Client, KartID, StoneGrooveID, SkillStoneID);
}
void ResponseInlaySkillStone(ClientNode* Client, int KartID, int StoneGrooveID, int SkillStoneID)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	Write16(p, 0); //ReasonLen
	Write32(p, KartID);
	Write32(p, StoneGrooveID);
	Write32(p, SkillStoneID);

	len = p - buf;
	SendToClient(Client, 901, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void NotifyUpdateKartSkillStoneInfo(ClientNode* Client, int KartID)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;

	int ID = -1;
	sql = "SELECT ID  FROM KartStoneGroove  WHERE Uin=? AND KartID=?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Uin);
		sqlite3_bind_int(stmt, 2, KartID);
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW)
		{
			ID = sqlite3_column_int(stmt, 0);
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;
	if (ID == -1)
	{
		return;
	}

	Write32(p, Client->Uin); //Uin
	{ //KartStoneInfo
		BYTE* pKartStoneInfo = p;
		Write16(pKartStoneInfo, 0); //len

		Write32(pKartStoneInfo, KartID); //KartID

		BYTE* pStoneGrooveNum = pKartStoneInfo;
		Write32(pKartStoneInfo, 0); //StoneGrooveNum
		{
			int StoneGrooveNum = 0;
			const char* sql = NULL;
			sqlite3_stmt* stmt = NULL;
			int result;
			sql = "SELECT StoneUseOccaType,SkillStoneID  FROM KartStone WHERE ID = ?;";
			result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
			if (result == SQLITE_OK) {
				sqlite3_bind_int(stmt, 1, ID);
				while (sqlite3_step(stmt) == SQLITE_ROW)
				{ //StoneGrooveInfo
					StoneGrooveNum++;

					BYTE* pStoneGrooveInfo = pKartStoneInfo;
					Write16(pStoneGrooveInfo, 0); //len

					Write32(pStoneGrooveInfo, sqlite3_column_int(stmt, 0)); //StoneUseOccaType
					Write32(pStoneGrooveInfo, sqlite3_column_int(stmt, 1)); //SkillStoneID

					len = pStoneGrooveInfo - pKartStoneInfo;
					Set16(pKartStoneInfo, (WORD)len);
					pKartStoneInfo += len;
				}
			}
			else
			{
				printf("%s\n", sqlite3_errmsg(PlayerDB));
			}
			sqlite3_finalize(stmt);
			stmt = NULL;
			Set32(pStoneGrooveNum, StoneGrooveNum);
		}


		len = pKartStoneInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	len = p - buf;
	SendToClient(Client, 906, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}


void NotifyKickFromServer(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ReasonID
	Write32(p, Client->Uin); //SrcUin
	Write8(p, 0); //ReasonLen
	Write8(p, 0); //AntiCheatMode
	Write8(p, 0); //KickType

	len = p - buf;
	SendToClient(Client, 900, buf, len, Client->ServerID, FE_GAMESVRD, Client->ConnID, Notify);
}

void RequestKartRefitInfo(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);


	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;

	KartRefitItemInfo Items[50];
	size_t ItemNum = 0;
	bool HasMoreInfo = false;

	sql = "SELECT KartID,RefitCout,MaxFlags,WWeight,SpeedWeight,JetWeight,SJetWeight,AccuWeight,ShapeRefitCount,KartHeadRefitItemID,KartTailRefitItemID,KartFlankRefitItemID,KartTireRefitItemID,ShapeSuitID FROM KartRefit WHERE Uin = ?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Uin);
	}
	else
	{
		printf("%s\n", sqlite3_errmsg(PlayerDB));
		sqlite3_finalize(stmt);
		stmt = NULL;
	}
	if (stmt)
	{
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			Items[ItemNum].KartId = sqlite3_column_int(stmt, 0);
			Items[ItemNum].RefitCout = sqlite3_column_int(stmt, 1);
			Items[ItemNum].MaxFlags = sqlite3_column_int(stmt, 2);
			Items[ItemNum].WWeight = sqlite3_column_int(stmt, 3);
			Items[ItemNum].SpeedWeight = sqlite3_column_int(stmt, 4);
			Items[ItemNum].JetWeight = sqlite3_column_int(stmt, 5);
			Items[ItemNum].SJetWeight = sqlite3_column_int(stmt, 6);
			Items[ItemNum].AccuWeight = sqlite3_column_int(stmt, 7);
			Items[ItemNum].ShapeRefitCount = sqlite3_column_int(stmt, 8);
			Items[ItemNum].KartHeadRefitItemID = sqlite3_column_int(stmt, 9);
			Items[ItemNum].KartTailRefitItemID = sqlite3_column_int(stmt, 10);
			Items[ItemNum].KartFlankRefitItemID = sqlite3_column_int(stmt, 11);
			Items[ItemNum].KartTireRefitItemID = sqlite3_column_int(stmt, 12);
			Items[ItemNum].ShapeSuitID = sqlite3_column_int(stmt, 13);

			ItemNum++;
			if (ItemNum >= 50)
			{
				HasMoreInfo = true;
				break;
			}
		}
	}


	ResponseKartRefitInfo(Client, ItemNum, Items, HasMoreInfo);
	if (stmt)
	{
		while (HasMoreInfo)
		{
			ItemNum = 0;
			HasMoreInfo = false;
			while (sqlite3_step(stmt) == SQLITE_ROW)
			{
				Items[ItemNum].KartId = sqlite3_column_int(stmt, 0);
				Items[ItemNum].RefitCout = sqlite3_column_int(stmt, 1);
				Items[ItemNum].MaxFlags = sqlite3_column_int(stmt, 2);
				Items[ItemNum].WWeight = sqlite3_column_int(stmt, 3);
				Items[ItemNum].SpeedWeight = sqlite3_column_int(stmt, 4);
				Items[ItemNum].JetWeight = sqlite3_column_int(stmt, 5);
				Items[ItemNum].SJetWeight = sqlite3_column_int(stmt, 6);
				Items[ItemNum].AccuWeight = sqlite3_column_int(stmt, 7);
				Items[ItemNum].ShapeRefitCount = sqlite3_column_int(stmt, 8);
				Items[ItemNum].KartHeadRefitItemID = sqlite3_column_int(stmt, 9);
				Items[ItemNum].KartTailRefitItemID = sqlite3_column_int(stmt, 10);
				Items[ItemNum].KartFlankRefitItemID = sqlite3_column_int(stmt, 11);
				Items[ItemNum].KartTireRefitItemID = sqlite3_column_int(stmt, 12);
				Items[ItemNum].ShapeSuitID = sqlite3_column_int(stmt, 13);
				ItemNum++;
				if (ItemNum >= 50)
				{
					HasMoreInfo = true;
					break;
				}
			}
			ResponseKartRefitInfoMoreInfo(Client, ItemNum, Items, HasMoreInfo);
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
	}

}

void ResponseKartRefitInfo(ClientNode* Client, UINT ItemNum, KartRefitItemInfo* Items, bool HasMoreInfo)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	Write32(p, Client->Uin); //Uin

	BYTE* pKartNum = p;
	Write16(p, ItemNum); //KartNum
	for (size_t i = 0; i < ItemNum; i++)
	{ //KartRefitInfo
		BYTE* pKartRefitInfo = p;
		Write16(pKartRefitInfo, 0); //len

		Write32(pKartRefitInfo, Client->Uin); //Uin
		Write32(pKartRefitInfo, Items[i].KartId); //KartId
		Write32(pKartRefitInfo, Items[i].RefitCout); //RefitCout
		Write16(pKartRefitInfo, Items[i].MaxFlags); //MaxFlags
		Write16(pKartRefitInfo, Items[i].WWeight); //WWeight
		Write16(pKartRefitInfo, Items[i].SpeedWeight); //SpeedWeight
		Write16(pKartRefitInfo, Items[i].JetWeight); //JetWeight
		Write16(pKartRefitInfo, Items[i].SJetWeight); //SJetWeight
		Write16(pKartRefitInfo, Items[i].AccuWeight); //AccuWeight
		Write32(pKartRefitInfo, Items[i].ShapeRefitCount); //ShapeRefitCount
		Write32(pKartRefitInfo, Items[i].KartHeadRefitItemID); //KartHeadRefitItemID
		Write32(pKartRefitInfo, Items[i].KartTailRefitItemID); //KartTailRefitItemID
		Write32(pKartRefitInfo, Items[i].KartFlankRefitItemID); //KartFlankRefitItemID
		Write32(pKartRefitInfo, Items[i].KartTireRefitItemID); //KartTireRefitItemID
		{ //KartRefitExInfo
			BYTE* pKartRefitExInfo = pKartRefitInfo;
			Write16(pKartRefitExInfo, 0); //len

			Write8(pKartRefitExInfo, 0); //SpeedRefitStar
			Write8(pKartRefitExInfo, 0); //JetRefitStar
			Write8(pKartRefitExInfo, 0); //SJetRefitStar
			Write8(pKartRefitExInfo, 0); //AccuRefitStar
			Write8(pKartRefitExInfo, 0); //SpeedAddRatio
			Write8(pKartRefitExInfo, 0); //JetAddRatio
			Write8(pKartRefitExInfo, 0); //SJetAddRatio
			Write8(pKartRefitExInfo, 0); //AccuAddRatio

			len = pKartRefitExInfo - pKartRefitInfo;
			Set16(pKartRefitInfo, (WORD)len);
			pKartRefitInfo += len;
		}
		Write32(pKartRefitInfo, 0); //SecondRefitCount
		Write16(pKartRefitInfo, 0); //Speed2Weight
		Write16(pKartRefitInfo, 0); //DriftVecWeight
		Write16(pKartRefitInfo, 0); //AdditionalZSpeedWeight
		Write16(pKartRefitInfo, 0); //AntiCollisionWeight
		Write16(pKartRefitInfo, 0); //LuckyValue
		Write16(pKartRefitInfo, 0); //RefitLuckyValueMaxWeight
		Write32(pKartRefitInfo, Items[i].ShapeSuitID); //ShapeSuitID
		Write8(pKartRefitInfo, 10); //LegendSuitLevel
		Write32(pKartRefitInfo, 1111); //LegendSuitLevelChoice
		Write32(pKartRefitInfo, Items[i].ShapeSuitID); //ShapeLegendSuitID

		len = pKartRefitInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

#ifndef ZingSpeed
	Write32(p, 0); //MaxLuckyWeight
	Write32(p, 0); //LuckyValue
	Write32(p, 0); //MaxLuckyValue
	Write8(p, 0); //LevelNum
	
	Write8(p, HasMoreInfo); //HasMoreInfo
#endif
	len = p - buf;
	SendToClient(Client, 271, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}
void ResponseKartRefitInfoMoreInfo(ClientNode* Client, UINT ItemNum, KartRefitItemInfo* Items, bool HasMoreInfo)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	Write16(p, ItemNum); //KartNum
	for (size_t i = 0; i < ItemNum; i++)
	{ //KartRefitInfo
		BYTE* pKartRefitInfo = p;
		Write16(pKartRefitInfo, 0); //len

		Write32(pKartRefitInfo, Client->Uin); //Uin
		Write32(pKartRefitInfo, Items[i].KartId); //KartId
		Write32(pKartRefitInfo, Items[i].RefitCout); //RefitCout
		Write16(pKartRefitInfo, Items[i].MaxFlags); //MaxFlags
		Write16(pKartRefitInfo, Items[i].WWeight); //WWeight
		Write16(pKartRefitInfo, Items[i].SpeedWeight); //SpeedWeight
		Write16(pKartRefitInfo, Items[i].JetWeight); //JetWeight
		Write16(pKartRefitInfo, Items[i].SJetWeight); //SJetWeight
		Write16(pKartRefitInfo, Items[i].AccuWeight); //AccuWeight
		Write32(pKartRefitInfo, Items[i].ShapeRefitCount); //ShapeRefitCount
		Write32(pKartRefitInfo, Items[i].KartHeadRefitItemID); //KartHeadRefitItemID
		Write32(pKartRefitInfo, Items[i].KartTailRefitItemID); //KartTailRefitItemID
		Write32(pKartRefitInfo, Items[i].KartFlankRefitItemID); //KartFlankRefitItemID
		Write32(pKartRefitInfo, Items[i].KartTireRefitItemID); //KartTireRefitItemID
		{ //KartRefitExInfo
			BYTE* pKartRefitExInfo = pKartRefitInfo;
			Write16(pKartRefitExInfo, 0); //len

			Write8(pKartRefitExInfo, 0); //SpeedRefitStar
			Write8(pKartRefitExInfo, 0); //JetRefitStar
			Write8(pKartRefitExInfo, 0); //SJetRefitStar
			Write8(pKartRefitExInfo, 0); //AccuRefitStar
			Write8(pKartRefitExInfo, 0); //SpeedAddRatio
			Write8(pKartRefitExInfo, 0); //JetAddRatio
			Write8(pKartRefitExInfo, 0); //SJetAddRatio
			Write8(pKartRefitExInfo, 0); //AccuAddRatio

			len = pKartRefitExInfo - pKartRefitInfo;
			Set16(pKartRefitInfo, (WORD)len);
			pKartRefitInfo += len;
		}
		Write32(pKartRefitInfo, 0); //SecondRefitCount
		Write16(pKartRefitInfo, 0); //Speed2Weight
		Write16(pKartRefitInfo, 0); //DriftVecWeight
		Write16(pKartRefitInfo, 0); //AdditionalZSpeedWeight
		Write16(pKartRefitInfo, 0); //AntiCollisionWeight
		Write16(pKartRefitInfo, 0); //LuckyValue
		Write16(pKartRefitInfo, 0); //RefitLuckyValueMaxWeight
		Write32(pKartRefitInfo, Items[i].ShapeSuitID); //ShapeSuitID
		Write8(pKartRefitInfo, 10); //LegendSuitLevel
		Write32(pKartRefitInfo, 1111); //LegendSuitLevelChoice
		Write32(pKartRefitInfo, Items[i].ShapeSuitID); //ShapeLegendSuitID

		len = pKartRefitInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write8(p, HasMoreInfo); //HasNext

	len = p - buf;
	SendToClient(Client, 318, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}
void RequestNewGetFriendList(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	ResponseNewGetFriendList(Client);
}
void ResponseNewGetFriendList(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	UINT FriendNum = 0;
	Write16(p, 0); //ResultID
	Write32(p, Client->Uin); //Uin
	Write16(p, 0xFF); //MaxFriendNum
	Write16(p,1); //TotalFriendNum
	Write16(p,1); //FriendGroupNum
	
	for (size_t i = 0; i < 1; i++)
	{ //FriendGroupInfo
		BYTE* pFriendGroupInfo = p;
		Write16(pFriendGroupInfo, 0); //len

		Write16(pFriendGroupInfo, 0); //GroupID
		//GroupName[]
		memset(pFriendGroupInfo, 0, 17);
		memcpy(pFriendGroupInfo, "我的好友", 9);
		pFriendGroupInfo += MaxNickName;
		BYTE* pFriendNum = pFriendGroupInfo;
		Write16(pFriendGroupInfo, 0); //FriendNum
		sql = "SELECT FriendUin FROM FriendInfo WHERE Uin = ?;";
		result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (result == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, Client->Uin);
			while (sqlite3_step(stmt) == SQLITE_ROW)
			{
				FriendNum++;
				{ //Friend
					BYTE* pFriend = pFriendGroupInfo;
					Write16(pFriend, 0); //len

					Write32(pFriend, sqlite3_column_int(stmt, 0)); //FriendUin
					Write32(pFriend, 0); //RelationFlag
					Write32(pFriend, 0); //Degree
					Write8(pFriend, 0); //Flag
					Write32(pFriend, 0); //ReadedEventID

					len = pFriend - pFriendGroupInfo;
					Set16(pFriendGroupInfo, (WORD)len);
					pFriendGroupInfo += len;
				}

			}
			Set16(pFriendNum, FriendNum);
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
		
		len = pFriendGroupInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	
	Write8(p, 0); //ReasonLen

	len = p - buf;
	SendToClient(Client, 163, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}


void NotifyClientAddItem(ClientNode* Client, UINT ItemNum, ItemInfo* Items)
{

	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	Write32(p, Client->Uin); //SrcUin
	Write16(p, ItemNum); //ItemNum
	{
		for (size_t i = 0; i < ItemNum; i++)
		{
			BYTE* pItemInfo = p;
			Write16(pItemInfo, 0); //len

			Write32(pItemInfo, Items[i].ItemID);
			Write32(pItemInfo, Items[i].ItemNum);
			Write32(pItemInfo, Items[i].AvailPeriod);//为0是物品栏显示个数 -1显示永久 抽奖列表会显示已拥有
			Write8(pItemInfo, Items[i].Status);
			Write32(pItemInfo, Items[i].ObtainTime);
			Write32(pItemInfo, Items[i].OtherAttribute);
#ifndef ZingSpeed
			Write16(pItemInfo, Items[i].ItemType); //ItemType
#endif

			len = pItemInfo - p;
			Set16(p, (WORD)len);
			p += len;
		}
	}

	Write16(p, 0); //AttachLen
	Write16(p, 0); //AddKartNum
	/*
	for (size_t i = 0; i < n; i++)
	{ //AddKartRefitInfo
		BYTE* pAddKartRefitInfo = p;
		Write16(pAddKartRefitInfo, 0); //len

		Write32(pAddKartRefitInfo, 0); //Uin
		Write32(pAddKartRefitInfo, 0); //KartId
		Write32(pAddKartRefitInfo, 0); //RefitCout
		Write16(pAddKartRefitInfo, 0); //MaxFlags
		Write16(pAddKartRefitInfo, 0); //WWeight
		Write16(pAddKartRefitInfo, 0); //SpeedWeight
		Write16(pAddKartRefitInfo, 0); //JetWeight
		Write16(pAddKartRefitInfo, 0); //SJetWeight
		Write16(pAddKartRefitInfo, 0); //AccuWeight
		Write32(pAddKartRefitInfo, 0); //ShapeRefitCount
		Write32(pAddKartRefitInfo, 0); //KartHeadRefitItemID
		Write32(pAddKartRefitInfo, 0); //KartTailRefitItemID
		Write32(pAddKartRefitInfo, 0); //KartFlankRefitItemID
		Write32(pAddKartRefitInfo, 0); //KartTireRefitItemID

		len = pAddKartRefitInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	Write8(p, 0); //IncRedPacketNum

	len = p - buf;
	SendToClient(Client, 529, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void RequestDeleteOneItem(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);
	int ItemID = Read32(Body);


	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	sql = "DELETE FROM Item  WHERE Uin=? AND  ItemID = ?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Uin);
		sqlite3_bind_int(stmt, 2, ItemID);
		result = sqlite3_step(stmt);
	}
	else
	{
		printf("%s\n", sqlite3_errmsg(PlayerDB));
	}
	sqlite3_finalize(stmt);
	stmt = NULL;

	ResponseDeleteOneItem(Client, ItemID);
}
void ResponseDeleteOneItem(ClientNode* Client, int ItemID)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	Write32(p, Client->Uin); //Uin
	Write32(p, ItemID); //ItemID
	Write8(p, 0); //ReasonLen

	len = p - buf;
	SendToClient(Client, 261, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void NotifyUseItemResult2(ClientNode* Client, int ItemID, int UseItemNum)
{
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;

	int CurrentItemNum = 0;
	//GetItemNum
	if (sqlite3_prepare_v2(PlayerDB, "SELECT ItemNum from Item WHERE Uin=? AND ItemID=?;", -1, &stmt, NULL) == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Uin);
		sqlite3_bind_int(stmt, 2, ItemID);

		if (sqlite3_step(stmt) == SQLITE_ROW) CurrentItemNum = sqlite3_column_int(stmt, 0);
	}
	sqlite3_finalize(stmt);
	stmt = NULL;

	int realnum = CurrentItemNum - UseItemNum;
	if (realnum < 0)
	{
		realnum = 0;
	}
	if (sqlite3_prepare_v2(PlayerDB, "UPDATE Item SET ItemNum=? WHERE Uin = ? AND ItemID = ?;", -1, &stmt, NULL) == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, realnum);
		sqlite3_bind_int(stmt, 2, Client->Uin);
		sqlite3_bind_int(stmt, 3, ItemID);
		sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	stmt = NULL;
	NotifyUseItemResult(Client, ItemID, UseItemNum, realnum);
}

void NotifyUseItemResult(ClientNode* Client, int ItemID, int UseItemNum, int CurrentItemNum)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	Write32(p, ItemID); //ItemID
	Write32(p, UseItemNum); //UseItemNum
	Write32(p, CurrentItemNum); //CurrentItemNum

	len = p - buf;
	SendToClient(Client, 556, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void RequestRefitKart(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	int KartItemId = Read32(Body);

	UCHAR KartNameLen = Read8(Body);
	Body += KartNameLen;

	int RefitItemId = Read32(Body);

	int Reserved = Read32(Body);
#ifndef ZingSpeed
	//Read16 2字节 是批量改装的数量
	short RefitCount= Read16(Body);
	short RefitTimes = Read16(Body);
#endif
	//printf("[RequestRefitKart] KartItemId: %d, KartNameLen: %d, RefitItemId: %d, Reserved: %d\n", KartItemId, KartNameLen, RefitItemId, Reserved);

	const char* Reason = "Sửa đổi thất bại!";

	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;

	int RefitItemNum = 0;
	//查询当前车辆改装信息
	//short MaxFlags = 0;
	short WWeight = 0;
	short SpeedWeight = 0;
	short JetWeight = 0;
	short SJetWeight = 0;
	short AccuWeight = 0;

	char RefitUseItem = 0;


	
	//GetItemNum
	if (sqlite3_prepare_v2(PlayerDB, "SELECT ItemNum from Item WHERE Uin=? AND ItemID=?;", -1, &stmt, NULL) == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Uin);
		sqlite3_bind_int(stmt, 2, RefitItemId);

		if (sqlite3_step(stmt) == SQLITE_ROW) RefitItemNum = sqlite3_column_int(stmt, 0);
	}
	sqlite3_finalize(stmt);
	stmt = NULL;

	//查询当前改装属性
	sql = "SELECT WWeight,SpeedWeight,JetWeight,SJetWeight,AccuWeight FROM KartRefit WHERE Uin=? AND KartID=?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Uin);
		sqlite3_bind_int(stmt, 2, KartItemId);
		if (sqlite3_step(stmt) == SQLITE_ROW)
		{

			WWeight = sqlite3_column_int(stmt, 0);
			SpeedWeight = sqlite3_column_int(stmt, 1);
			JetWeight = sqlite3_column_int(stmt, 2);
			SJetWeight = sqlite3_column_int(stmt, 3);
			AccuWeight = sqlite3_column_int(stmt, 4);
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;

	char RefitLimit = 0;
	while (RefitCount > 0)
	{
		RefitCount--;
		if (RefitItemNum > 0) {
			//改装上限29
			switch (RefitItemId)
			{
			case 12376: //Đánh lửa+1 //点火装置+1
				SJetWeight += 1;
				if (SJetWeight > 29)
				{
					SJetWeight = 29;
					RefitLimit = 1;
					ResponseStartGame(Client, "已达改装上限!");
					break;
				}
				break;
			case 12377: //Bơm khí+1 //进气系统+1
				AccuWeight += 1;
				if (AccuWeight > 29)
				{
					AccuWeight = 29;
					RefitLimit = 1;
					ResponseStartGame(Client, "已达改装上限!");
					break;
				}
				break;
			case 12378: //Nhiên liệu+1 //燃料系统+1
				JetWeight += 1;
				if (JetWeight > 29)
				{
					JetWeight = 29;
					RefitLimit = 1;
					ResponseStartGame(Client, "已达改装上限!");
					break;
				}
				break;
			case 12379: //Giảm Sóc+1 //悬挂系统+1
				WWeight += 1;
				if (WWeight > 29)
				{
					WWeight = 29;
					RefitLimit = 1;
					ResponseStartGame(Client, "已达改装上限!");
					break;
				}
				break;
			case 12380: //Động cơ+1 //引擎装置+1
				SpeedWeight += 1;
				if (SpeedWeight > 29)
				{
					SpeedWeight = 29;
					RefitLimit = 1;
					ResponseStartGame(Client, "已达改装上限!");
					break;
				}
				break;
			case 12386: //Đánh lửa+2
				SJetWeight += 2;
				if (SJetWeight > 29)
				{
					SJetWeight = 29;
					RefitLimit = 1;
					ResponseStartGame(Client, "已达改装上限!");
					break;
				}
				break;
			case 12387: //Bơm khí+2
				AccuWeight += 2;
				if (AccuWeight > 29)
				{
					AccuWeight = 29;
					RefitLimit = 1;
					ResponseStartGame(Client, "已达改装上限!");
					break;
				}
				break;
			case 12388: //Nhiên liệu+2
				JetWeight += 2;
				if (JetWeight > 29)
				{
					JetWeight = 29;
					RefitLimit = 1;
					ResponseStartGame(Client, "已达改装上限!");
					break;
				}
				break;
			case 12389: //Giảm Sóc+2
				WWeight += 2;
				if (WWeight > 29)
				{
					WWeight = 29;
					RefitLimit = 1;
					ResponseStartGame(Client, "已达改装上限!");
					break;
				}
				break;
			case 12390: //Động cơ+2
				SpeedWeight += 2;
				if (SpeedWeight > 29)
				{
					SpeedWeight = 29;
					RefitLimit = 1;
					ResponseStartGame(Client, "已达改装上限!");
					break;
				}
				break;
			default:
				//printf("改装部位:%u\n", RefitItemId);
				break;
			}
			if (RefitLimit == 1)
			{
				break;
			}
			RefitItemNum--;
			RefitUseItem++;
		}
	}
	sql = "UPDATE KartRefit SET RefitCout=RefitCout+1, SJetWeight=?,AccuWeight=?,JetWeight=?,WWeight=?,SpeedWeight=?  WHERE Uin=? AND KartID=?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, SJetWeight);
		sqlite3_bind_int(stmt, 2, AccuWeight);
		sqlite3_bind_int(stmt, 3, JetWeight);
		sqlite3_bind_int(stmt, 4, WWeight);
		sqlite3_bind_int(stmt, 5, SpeedWeight);

		sqlite3_bind_int(stmt, 6, Client->Uin);
		sqlite3_bind_int(stmt, 7, KartItemId);
		result = sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	stmt = NULL;
	ResponseRefitKart(Client, KartItemId, Reason, SJetWeight, AccuWeight, JetWeight, WWeight, SpeedWeight);
	if (RefitItemNum <= 0) {//Delete Item
		if (sqlite3_prepare_v2(PlayerDB, "DELETE FROM Item  WHERE Uin=? AND ItemID=?;", -1, &stmt, NULL) == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, Client->Uin);
			sqlite3_bind_int(stmt, 2, RefitItemId);
			sqlite3_step(stmt);
		}
	}
	else
	{
		if (sqlite3_prepare_v2(PlayerDB, "UPDATE Item SET ItemNum=? WHERE Uin = ? AND ItemID = ?;", -1, &stmt, NULL) == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, RefitItemNum);
			sqlite3_bind_int(stmt, 2, Client->Uin);
			sqlite3_bind_int(stmt, 3, RefitItemId);
			sqlite3_step(stmt);
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;

	NotifyUseItemResult(Client, RefitItemId, RefitUseItem, RefitItemNum);

	
}
void ResponseRefitKart(ClientNode* Client, int KartItemId, const char* Reason, short inc_SJetWeight, short inc_AccuWeight, short inc_JetWeight, short inc_WWeight, short inc_SpeedWeight)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, 0); //Result
	Write32(p, Client->Uin); //Uin
	Write32(p, KartItemId); //KartItemId

	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	int RefitCout = 0;
	short MaxFlags = 0;
	short WWeight = 0;
	short SpeedWeight = 0;
	short JetWeight = 0;
	short SJetWeight = 0;
	short AccuWeight = 0;
	int ShapeRefitCount = 0;
	int KartHeadRefitItemID = 0;
	int KartTailRefitItemID = 0;
	int KartFlankRefitItemID = 0;
	int KartTireRefitItemID = 0;

	sql = "SELECT RefitCout,MaxFlags,WWeight,SpeedWeight,JetWeight,SJetWeight,AccuWeight,ShapeRefitCount,KartHeadRefitItemID,KartTailRefitItemID,KartFlankRefitItemID,KartTireRefitItemID  FROM KartRefit WHERE Uin=? AND KartID=?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Uin);
		sqlite3_bind_int(stmt, 2, KartItemId);
		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
			RefitCout = sqlite3_column_int(stmt, 0);
			MaxFlags = sqlite3_column_int(stmt, 1);
			WWeight = sqlite3_column_int(stmt, 2);
			SpeedWeight = sqlite3_column_int(stmt, 3);
			JetWeight = sqlite3_column_int(stmt, 4);
			SJetWeight = sqlite3_column_int(stmt, 5);
			AccuWeight = sqlite3_column_int(stmt, 6);

			ShapeRefitCount = sqlite3_column_int(stmt, 7);
			KartHeadRefitItemID = sqlite3_column_int(stmt, 8);
			KartTailRefitItemID = sqlite3_column_int(stmt, 9);
			KartFlankRefitItemID = sqlite3_column_int(stmt, 10);
			KartTireRefitItemID = sqlite3_column_int(stmt, 11);
		}
	}

	sqlite3_finalize(stmt);
	stmt = NULL;

	{ //Increasement增长属性

		BYTE* pIncreasement = p;
		Write16(pIncreasement, 0); //len

		Write32(pIncreasement, Client->Uin); //Uin
		Write32(pIncreasement, KartItemId); //KartId
		Write32(pIncreasement, 1); //RefitCout
		Write16(pIncreasement, 0); //MaxFlags
		Write16(pIncreasement, inc_WWeight); //WWeight
		Write16(pIncreasement, inc_SpeedWeight); //SpeedWeight
		Write16(pIncreasement, inc_JetWeight); //JetWeight
		Write16(pIncreasement, inc_SJetWeight); //SJetWeight
		Write16(pIncreasement, inc_AccuWeight); //AccuWeight
		Write32(pIncreasement, 0); //ShapeRefitCount
		Write32(pIncreasement, 0); //KartHeadRefitItemID
		Write32(pIncreasement, 0); //KartTailRefitItemID
		Write32(pIncreasement, 0); //KartFlankRefitItemID
		Write32(pIncreasement, 0); //KartTireRefitItemID
#ifndef ZingSpeed
		Write32(pIncreasement, 0); //SecondRefitCount进阶修改
		Write16(pIncreasement, 0); //Speed2Weight
		Write16(pIncreasement, 0); //DriftVecWeight
		Write16(pIncreasement, 0); //AdditionalZSpeedWeight
		Write16(pIncreasement, 0); //AntiCollisionWeight
		Write16(pIncreasement, 0); //LuckyValue
		Write16(pIncreasement, 0); //RefitLuckyValueMaxWeight
		Write32(pIncreasement, 0); //ShapeSuitID 皮肤适配id
		Write8(pIncreasement, 0); //LegendSuitLevel
		Write32(pIncreasement, 0); //LegendSuitLevelChoice
		Write32(pIncreasement, 0); //ShapeLegendSuitID 传奇皮肤适配id
#endif

		len = pIncreasement - p;
		Set16(p, (WORD)len);
		p += len;
	}
	{ //CurAttr
		BYTE* pCurAttr = p;
		Write16(pCurAttr, 0); //len

		Write32(pCurAttr, Client->Uin); //Uin
		Write32(pCurAttr, KartItemId); //KartId
		Write32(pCurAttr, RefitCout); //RefitCout
		Write16(pCurAttr, MaxFlags); //MaxFlags
		Write16(pCurAttr, WWeight); //WWeight
		Write16(pCurAttr, SpeedWeight); //SpeedWeight
		Write16(pCurAttr, JetWeight); //JetWeight
		Write16(pCurAttr, SJetWeight); //SJetWeight
		Write16(pCurAttr, AccuWeight); //AccuWeight
		Write32(pCurAttr, ShapeRefitCount); //ShapeRefitCount
		Write32(pCurAttr, KartHeadRefitItemID); //KartHeadRefitItemID
		Write32(pCurAttr, KartTailRefitItemID); //KartTailRefitItemID
		Write32(pCurAttr, KartFlankRefitItemID); //KartFlankRefitItemID
		Write32(pCurAttr, KartTireRefitItemID); //KartTireRefitItemID
#ifndef ZingSpeed
		Write32(pCurAttr, 0); //SecondRefitCount
		Write16(pCurAttr, 0); //Speed2Weight
		Write16(pCurAttr, 0); //DriftVecWeight
		Write16(pCurAttr, 0); //AdditionalZSpeedWeight
		Write16(pCurAttr, 0); //AntiCollisionWeight
		Write16(pCurAttr, 0); //LuckyValue
		Write16(pCurAttr, 0); //RefitLuckyValueMaxWeight
		Write32(pCurAttr, 0); //ShapeSuitID
		Write8(pCurAttr, 0); //LegendSuitLevel
		Write32(pCurAttr, 0); //LegendSuitLevelChoice
		Write32(pCurAttr, 0); //ShapeLegendSuitID
#endif
		len = pCurAttr - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write32(p, 500); //ExpAward
	Write32(p, 250); //MoneyAward

	len = strlen(Reason);
	Write16(p, (WORD)len); //ReasonLen
	memcpy(p, Reason, len);
	p += len;

#ifndef ZingSpeed
	Write16(p, 0); //RefitTimes
	Write16(p, 1); //ResponseIdx
	Write8(p, 1); //LastIdx
	Write32(p, 0); //LuckyValue
#endif

	len = p - buf;
	//PrintfBody(0, 0, buf, len);
	SendToClient(Client, 174, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void ResponseSkinChange(ClientNode* Client, int KartItemId, int SkinItemId)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	UINT karthead = 0;
	UINT kartail =0;
	UINT karflank = 0;
	UINT kartire = 0;
	if (0 == SkinItemId)
	{
		sql = "SELECT KartHeadRefitItemID,KartTailRefitItemID,KartFlankRefitItemID,KartTireRefitItemID  FROM KartRefit WHERE Uin = ? and  KartID = ?;";
		result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (result == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, Client->Uin);
			sqlite3_bind_int(stmt, 2, KartItemId);
			if (sqlite3_step(stmt) == SQLITE_ROW)
			{
				karthead = sqlite3_column_int(stmt, 0);
				kartail = sqlite3_column_int(stmt, 1);
				karflank = sqlite3_column_int(stmt, 2);
				kartire = sqlite3_column_int(stmt, 3);
			}
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
	}
	
	Write16(p, 0); //ResultID
	Write8(p, 0); //ReasonLen
	Write32(p, KartItemId); //KartItemID
	{ //KartRefitExInfo
		BYTE* pKartRefitExInfo = p;
		Write16(pKartRefitExInfo, 0); //len

		Write8(pKartRefitExInfo, 0); //SpeedRefitStar
		Write8(pKartRefitExInfo, 0); //JetRefitStar
		Write8(pKartRefitExInfo, 0); //SJetRefitStar
		Write8(pKartRefitExInfo, 0); //AccuRefitStar
		Write8(pKartRefitExInfo, 0); //SpeedAddRatio
		Write8(pKartRefitExInfo, 0); //JetAddRatio
		Write8(pKartRefitExInfo, 0); //SJetAddRatio
		Write8(pKartRefitExInfo, 0); //AccuAddRatio

		len = pKartRefitExInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write8(p, 4); //RefitItemNum
	Write32(p, karthead); //RefitItemID[]
	Write32(p, kartail); //RefitItemID[]
	Write32(p, karflank); //RefitItemID[]
	Write32(p, kartire); //RefitItemID[]
	Write32(p, SkinItemId); //ShapeSuitID
	{ //RefitClientInfo
		BYTE* pRefitClientInfo = p;
		Write16(pRefitClientInfo, 0); //len

		Write32(pRefitClientInfo, 0); //Uin
		Write32(pRefitClientInfo, KartItemId); //KartId
		Write32(pRefitClientInfo, 0); //RefitCout
		Write16(pRefitClientInfo, 0); //MaxFlags
		Write16(pRefitClientInfo, 0); //WWeight
		Write16(pRefitClientInfo, 0); //SpeedWeight
		Write16(pRefitClientInfo, 0); //JetWeight
		Write16(pRefitClientInfo, 0); //SJetWeight
		Write16(pRefitClientInfo, 0); //AccuWeight
		Write32(pRefitClientInfo, 0); //ShapeRefitCount
		Write32(pRefitClientInfo, 0); //KartHeadRefitItemID
		Write32(pRefitClientInfo, 0); //KartTailRefitItemID
		Write32(pRefitClientInfo, 0); //KartFlankRefitItemID
		Write32(pRefitClientInfo, 0); //KartTireRefitItemID
		{ //KartRefitExInfo
			BYTE* pKartRefitExInfo = pRefitClientInfo;
			Write16(pKartRefitExInfo, 0); //len

			Write8(pKartRefitExInfo, 0); //SpeedRefitStar
			Write8(pKartRefitExInfo, 0); //JetRefitStar
			Write8(pKartRefitExInfo, 0); //SJetRefitStar
			Write8(pKartRefitExInfo, 0); //AccuRefitStar
			Write8(pKartRefitExInfo, 0); //SpeedAddRatio
			Write8(pKartRefitExInfo, 0); //JetAddRatio
			Write8(pKartRefitExInfo, 0); //SJetAddRatio
			Write8(pKartRefitExInfo, 0); //AccuAddRatio

			len = pKartRefitExInfo - pRefitClientInfo;
			Set16(pRefitClientInfo, (WORD)len);
			pRefitClientInfo += len;
		}
		Write32(pRefitClientInfo, 0); //SecondRefitCount
		Write16(pRefitClientInfo, 0); //Speed2Weight
		Write16(pRefitClientInfo, 0); //DriftVecWeight
		Write16(pRefitClientInfo, 0); //AdditionalZSpeedWeight
		Write16(pRefitClientInfo, 0); //AntiCollisionWeight
		Write16(pRefitClientInfo, 0); //LuckyValue
		Write16(pRefitClientInfo, 0); //RefitLuckyValueMaxWeight
		Write32(pRefitClientInfo, SkinItemId); //ShapeSuitID
		Write8(pRefitClientInfo, 10); //LegendSuitLevel
		Write32(pRefitClientInfo,1111); //LegendSuitLevelChoice
		Write32(pRefitClientInfo, SkinItemId); //ShapeLegendSuitID

		len = pRefitClientInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	len = p - buf;
	SendToClient(Client, 316, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}
void RequestModifyPlayerSignature(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);

	char Signature[MaxSignature] = {};
	memcpy(Signature, p, MaxSignature);
	p += MaxSignature;

	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;

	sql = "UPDATE BaseInfo SET Signature=? WHERE Uin=?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, Signature, strnlen_s(Signature, MaxSignature), SQLITE_TRANSIENT);
		sqlite3_bind_int(stmt, 2, Client->Uin);
		result = sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	stmt = NULL;


	ResponseModifyPlayerSignature(Client, Signature);
}

void ResponseModifyPlayerSignature(ClientNode* Client, char* Signature)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	Write8(p, 0); //ReasonLen

	//Signature[]
	memcpy(p, Signature, MaxSignature);
	p += MaxSignature;


	len = p - buf;
	SendToClient(Client, 376, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestFindPlayerByQQ(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body;;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);

	char NickName[MaxNickName] = {};
	memcpy(NickName, p, MaxNickName);
	p += MaxNickName;

	UINT DstUin = Read32(p);
	UINT DstNobleID = Read32(p);
	UCHAR Contex = Read8(p);
#ifndef ZingSpeed
	UCHAR AreaIdDst = Read8(p);
	UCHAR IgnoreByQQ2Msg = Read8(p);
	UCHAR SimpleInfo = Read8(p);
#endif

	ResponseFindPlayerByQQ(Client, DstUin);
	
}

void ResponseFindPlayerByQQ(ClientNode* Client, UINT DstUin)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	UINT KartItemId = 0;

	BOOL findresult;
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int sqlresult;
	Write16(p, 0); //ResultID
	{ //PlayerInfo
		BYTE* pPlayerInfo = p;
		Write16(pPlayerInfo, 0); //len
		
		Write32(pPlayerInfo, DstUin); //Uin
		Write32(pPlayerInfo, 0); //Identity
		Write16(pPlayerInfo, 0); //PlayerID

		findresult=WritePlayerDBBaseInfo(pPlayerInfo, DstUin);
		if (findresult==FALSE)
		{
			return;
		}
		WritePlayerGuildInfo(pPlayerInfo, DstUin);
		KartItemId = WriteEquipedItem2(pPlayerInfo, DstUin);
		
		Write32(pPlayerInfo, 0); //MasterPoint
		Write32(pPlayerInfo, 0); //TotalGuildProsperity

		Write16(pPlayerInfo, 0x0106); //VipFlag
		Write16(pPlayerInfo, 0); //VipGrowRate

		Write8(pPlayerInfo, 0); //AppellationNum
		
		{ //NobleInfo
			BYTE* pNobleInfo = pPlayerInfo;
			Write16(pNobleInfo, 0); //len

			Write32(pNobleInfo, DstUin); //NobleID
			Write8(pNobleInfo, 6); //NobleLevel
			Write32(pNobleInfo, 1); //NoblePoint
			Write32(pNobleInfo, 30); //NobleLeftDays

			len = pNobleInfo - pPlayerInfo;
			Set16(pPlayerInfo, (WORD)len);
			pPlayerInfo += len;
		}

		Write8(pPlayerInfo, 0); //HasCarryWizard
		

#ifndef ZingSpeed
		{ //GuildVipBaseInfo
			BYTE* pGuildVipBaseInfo = pPlayerInfo;
			Write16(pGuildVipBaseInfo, 0); //len

			Write8(pGuildVipBaseInfo, 6); //GuildVipLevel
			Write32(pGuildVipBaseInfo, 0); //GuildVipPoint

			len = pGuildVipBaseInfo - pPlayerInfo;
			Set16(pPlayerInfo, (WORD)len);
			pPlayerInfo += len;
		}
#endif

		Write8(pPlayerInfo, 0); //HasLDMInfo
		

#ifndef ZingSpeed
		Write8(pPlayerInfo,1); //HasLoverVip
		
		for (size_t i = 0; i < 1; i++)
		{ //LoverVipInfo
			BYTE* pLoverVipInfo = pPlayerInfo;
			Write16(pLoverVipInfo, 0); //len

			Write8(pLoverVipInfo, 6); //LoverVipLevel
			Write32(pLoverVipInfo, 1); //LoverVipPoint
			Write8(pLoverVipInfo, 0); //GrowRate

			len = pLoverVipInfo - pPlayerInfo;
			Set16(pPlayerInfo, (WORD)len);
			pPlayerInfo += len;
		}
		
#endif

		Write8(pPlayerInfo, 0); //IsShowMounts

#ifndef ZingSpeed
		Write8(pPlayerInfo, 1); //HasGarden
		
		{ //PersonalGardenBaseInfo
			BYTE* pPersonalGardenBaseInfo = pPlayerInfo;
			Write16(pPersonalGardenBaseInfo, 0); //len

			Write8(pPersonalGardenBaseInfo, 6); //GardenLevel
			Write32(pPersonalGardenBaseInfo, 1); //GardenPoint
			Write8(pPersonalGardenBaseInfo, 0); //GrowRate
			Write32(pPersonalGardenBaseInfo, 0); //GardenExpireTime
			{ //SimpleInfo
				BYTE* pSimpleInfo = pPersonalGardenBaseInfo;
				Write16(pSimpleInfo, 0); //len

				Write32(pSimpleInfo, 0); //WeekPopularity
				Write32(pSimpleInfo, 0); //TotalPopularity
				Write32(pSimpleInfo, 0); //LastUpdatePopularityTime
				Write8(pSimpleInfo, 0); //PrivateType

				len = pSimpleInfo - pPersonalGardenBaseInfo;
				Set16(pPersonalGardenBaseInfo, (WORD)len);
				pPersonalGardenBaseInfo += len;
			}

			len = pPersonalGardenBaseInfo - pPlayerInfo;
			Set16(pPlayerInfo, (WORD)len);
			pPlayerInfo += len;
		}
		

		Write8(pPlayerInfo, 1); //isConsumeVip
		Write32(pPlayerInfo, 6); //ConsumeVipLevel
		Write32(pPlayerInfo, 0); //SearchTreasureNums 
		Write32(pPlayerInfo, 0); //GetTreasureNums 
		Write32(pPlayerInfo, 0); //ConsumeVipCharmVlaueOfMonth 
		{ //EmperorInfo
			BYTE* pEmperorInfo = pPlayerInfo;
			Write16(pEmperorInfo, 0); //len

			Write8(pEmperorInfo, 6); //EmperorLevel
			Write32(pEmperorInfo, 0); //EmperorPoint
			Write32(pEmperorInfo, 0); //EmperorLeftDays
			Write8(pEmperorInfo, 0); //EmperorGrowRate

			len = pEmperorInfo - pPlayerInfo;
			Set16(pPlayerInfo, (WORD)len);
			pPlayerInfo += len;
		}
		{ //EmperorOtherInfo
			BYTE* pEmperorOtherInfo = pPlayerInfo;
			Write16(pEmperorOtherInfo, 0); //len

			Write32(pEmperorOtherInfo, 0); //ExpiredTime
			Write8(pEmperorOtherInfo, 0); //ShowExpireTips

			len = pEmperorOtherInfo - pPlayerInfo;
			Set16(pPlayerInfo, (WORD)len);
			pPlayerInfo += len;
		}
		{ //ActivityInfo
			BYTE* pActivityInfo = pPlayerInfo;
			Write16(pActivityInfo, 0); //len

			Write32(pActivityInfo, 0); //TotalActivity
			Write32(pActivityInfo, 0); //ActivityLevel

			len = pActivityInfo - pPlayerInfo;
			Set16(pPlayerInfo, (WORD)len);
			pPlayerInfo += len;
		}

		Write8(pPlayerInfo, 0); //HaveWakedKartAttributeAddInfo
		

		Write8(pPlayerInfo, 0); //HaveLoverBabyInfo
		

		{ //GansterScoreInfo
			BYTE* pGansterScoreInfo = pPlayerInfo;
			Write16(pGansterScoreInfo, 0); //len

			Write32(pGansterScoreInfo, 0); //GansterSeasonID
			Write32(pGansterScoreInfo, 0); //GansterScore
			Write32(pGansterScoreInfo, 0); //PoliceScore
			Write32(pGansterScoreInfo, 0); //TotalGansterScore

			len = pGansterScoreInfo - pPlayerInfo;
			Set16(pPlayerInfo, (WORD)len);
			pPlayerInfo += len;
		}

		Write32(pPlayerInfo, 0); //OlympicId
		Write32(pPlayerInfo, 0); //LastOlympicUpdateTime
		Write32(pPlayerInfo, 0); //NPCEliminateWinTimes
		{ //BorderInfo
			BYTE* pBorderInfo = pPlayerInfo;
			Write16(pBorderInfo, 0); //len

			Write32(pBorderInfo, 0); //SeasonID
			Write32(pBorderInfo, 0); //Zhanxun
			Write32(pBorderInfo, 0); //SeasonZhanxun

			len = pBorderInfo - pPlayerInfo;
			Set16(pPlayerInfo, (WORD)len);
			pPlayerInfo += len;
		}
		Write8(pPlayerInfo, 0); //SpecialActivityID
		Write32(pPlayerInfo, 0); //ThemeHouseCollectValue 0x64
		Write8(pPlayerInfo, 0); //HaveSecondLoverBabyInfo
		{ //SecondLoverBabyInfo
			BYTE* pSecondLoverBabyInfo = pPlayerInfo;
			Write16(pSecondLoverBabyInfo, 0); //len

			Write32(pSecondLoverBabyInfo, 0); //BabyStatus
			Write32(pSecondLoverBabyInfo, 0); //LoverBabyItemID
			Write32(pSecondLoverBabyInfo, 0); //LoverBabyID
			Write32(pSecondLoverBabyInfo, 0); //BabyGrowLevel
			Write32(pSecondLoverBabyInfo, 0); //BabyStrengthLevel
			Write16(pSecondLoverBabyInfo, 0); //LoverBabyStat
			Write16(pSecondLoverBabyInfo, 0); //LoverBabyEquipStat
			Write16(pSecondLoverBabyInfo, 0); //LoverBabyTransferdStatus

			len = pSecondLoverBabyInfo - pPlayerInfo;
			Set16(pPlayerInfo, (WORD)len);
			pPlayerInfo += len;
		}
		Write8(pPlayerInfo, 0); //EquipBaby
		Write8(pPlayerInfo, 0); //ActiveStatus
		Write32(pPlayerInfo, 0); //HelperLev



		//查询排位信息
		sql = "SELECT GradeLevel FROM RankInfo Where Uin=?;";
		sqlresult = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (sqlresult == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, DstUin);
			if (sqlite3_step(stmt) == SQLITE_ROW)
			{
				UINT leveltemp = sqlite3_column_int(stmt, 0);
				if (leveltemp > 7)
				{
					leveltemp = 7;
				}
				Write8(pPlayerInfo, 1); //HasRankedMatchInfo
				for (size_t i = 0; i < 1; i++)
				{ //RankedMatchGradeInfo
					BYTE* pRankedMatchGradeInfo = pPlayerInfo;
					Write16(pRankedMatchGradeInfo, 0); //len

					Write32(pRankedMatchGradeInfo, RankGradeLevel[leveltemp]); //GradeLevel
					Write32(pRankedMatchGradeInfo, 1); //ChildLevel
					Write32(pRankedMatchGradeInfo, 0); //GradeScore
					Write32(pRankedMatchGradeInfo, 0); //MaxGradeScore
					Write32(pRankedMatchGradeInfo, 0); //TotalScore

					len = pRankedMatchGradeInfo - pPlayerInfo;
					Set16(pPlayerInfo, (WORD)len);
					pPlayerInfo += len;
				}
				Write16(pPlayerInfo, 1); //PlayerSeasonInfoNums
				for (size_t i = 0; i < 1; i++)
				{ //PlayerSeasonInfos
					BYTE* pPlayerSeasonInfos = pPlayerInfo;
					Write16(pPlayerSeasonInfos, 0); //len

					Write16(pPlayerSeasonInfos, 0); //SeasonID
					Write16(pPlayerSeasonInfos, RankGradeLevel[leveltemp]); //GradeLevel
					Write8(pPlayerSeasonInfos, 1); //ChildLevel
					Write16(pPlayerSeasonInfos, 0); //HighGradeLevel
					Write8(pPlayerSeasonInfos, 0); //HighChildLevel
					Write8(pPlayerSeasonInfos, 0); //SeasonInfoProcesedTag
					Write8(pPlayerSeasonInfos, 0); //SeasonComputeInfoTipTag
					Write16(pPlayerSeasonInfos, 0); //SeasonInheritTag
					Write8(pPlayerSeasonInfos, 0); //SeasonInheritTipTag
					Write16(pPlayerSeasonInfos, 0); //SpeedGodNums
					Write32(pPlayerSeasonInfos, 0); //SpeedRoundNums
					Write32(pPlayerSeasonInfos, 0); //SpeedFinishRoundNums
					Write32(pPlayerSeasonInfos, 0); //TotalRankIndex
					Write32(pPlayerSeasonInfos, 0); //ContiFinishRoundNums
					Write32(pPlayerSeasonInfos, 0); //SpeedKillAllRoundNums
					Write32(pPlayerSeasonInfos, 0); //PropRoundNums
					Write32(pPlayerSeasonInfos, 0); //PropFinishRoundNums
					Write32(pPlayerSeasonInfos, 0); //ContiFinishPropRoundNums
					Write32(pPlayerSeasonInfos, 0); //PropKillAllRoundNums
					Write8(pPlayerSeasonInfos, 0); //LastRoundIndex
					Write32(pPlayerSeasonInfos, 0); //OpenDate
					Write32(pPlayerSeasonInfos, 0); //CloseDate
					Write32(pPlayerSeasonInfos, 0); //HistroyContFinishRoundNums

					len = pPlayerSeasonInfos - pPlayerInfo;
					Set16(pPlayerInfo, (WORD)len);
					pPlayerInfo += len;
				}
			}
			else
			{
				Write8(pPlayerInfo, 0); //HasRankedMatchInfo
				Write16(pPlayerInfo, 0); //PlayerSeasonInfoNums
			}
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
		
		Write8(pPlayerInfo, 0); //IsHelperAppOnline
		Write32(pPlayerInfo, 0); //RankedMatchSpeedGodNums
		Write8(pPlayerInfo, 0); //EquipSealType

		Write8(pPlayerInfo, 0); //HasHuanLingChangeInfo
		

		Write8(pPlayerInfo, 0); //SpecialActivityIDNum
		Write8(pPlayerInfo, 0); //PersonalPanelSelectRankedMatchFrameTag

		Write8(pPlayerInfo, 1); //SpecialActivityInfoNum
		for (size_t i = 0; i < 1; i++)
		{ //SpecialActivityInfo
			BYTE* pSpecialActivityInfo = pPlayerInfo;
			Write16(pSpecialActivityInfo, 0); //len

			Write8(pSpecialActivityInfo, 1); //ProfessionLicenseInfoNum
			for (size_t i = 0; i < 1; i++)
			{ //ProfessionLicenseInfo
				BYTE* pProfessionLicenseInfo = pSpecialActivityInfo;
				Write16(pProfessionLicenseInfo, 0); //len

				Write8(pProfessionLicenseInfo, 6); //BigLevel
				Write8(pProfessionLicenseInfo, 5); //SmallLevel

				len = pProfessionLicenseInfo - pSpecialActivityInfo;
				Set16(pSpecialActivityInfo, (WORD)len);
				pSpecialActivityInfo += len;
			}

			len = pSpecialActivityInfo - pPlayerInfo;
			Set16(pPlayerInfo, (WORD)len);
			pPlayerInfo += len;
		}


		Write8(pPlayerInfo, 0); //PersonalRankedMatchLevelShowTag

		Write8(pPlayerInfo, 0); //ItemNum
	

		Write8(pPlayerInfo, 0); //ExRightFlagLen

		Write8(pPlayerInfo, 0); //EquipNiChangItemNum
		
#endif
		len = pPlayerInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write8(p, 1); //IsOnLine
	{ //PositionInfo
		BYTE* pPositionInfo = p;
		Write16(pPositionInfo, 0); //len

		Write8(pPositionInfo, 0); //ServerType
		Write16(pPositionInfo, 0); //Status
		Write32(pPositionInfo, 0); //ServerID
		{ //RoomInfo
			BYTE* pRoomInfo = pPositionInfo;
			Write16(pRoomInfo, 0); //len

			Write16(pRoomInfo, 0); //RoomID
			Write16(pRoomInfo, 0); //BaseGameMode
			Write16(pRoomInfo, 0); //SubGameMode
			Write8(pRoomInfo, 0); //CurrentPlayerNum
			Write8(pRoomInfo,0); //TotalSeatNum
			Write8(pRoomInfo, 0); //Status
			Write32(pRoomInfo, 0); //MapID
			Write16(pRoomInfo, 0); //Flag

			//RoomName[]
			memset(pRoomInfo, 0, MaxRoomName);
			pRoomInfo += MaxRoomName;

			Write8(pRoomInfo, 0); //HasFBInfo
			/*
			{ //FBInfo
				BYTE* pFBInfo = pRoomInfo;
				Write16(pFBInfo, 0); //len

				Write8(pFBInfo, 0); //AvailableLev
				Write8(pFBInfo, 0); //Lev
				Write8(pFBInfo, 0); //SubLev
				Write32(pFBInfo, 0); //BossID
				Write8(pFBInfo, 0); //FBSeason

				len = pFBInfo - pRoomInfo;
				Set16(pRoomInfo, (WORD)len);
				pRoomInfo += len;
			}
			*/
#ifndef ZingSpeed
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
			//Write32(pRoomInfo, 0); //EnterRoomValue[]
			Write8(pRoomInfo, 0); //ParaNum
			//Write32(pRoomInfo, 0); //ParaList[]
			Write32(pRoomInfo, 0); //GSvrRoomNo

			//OwnerName[]
			memset(pRoomInfo, 0, MaxNickName);
			pRoomInfo += MaxNickName;
#endif
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
	Write8(p, 0); //ReasonLen
	{ //PlayerRelationInfo
		
		UINT EngageUin = 0;

		char* NickName = NULL;
		char* newname = NULL;
		sql = "SELECT EngageUin FROM EngageInfo WHERE Uin = ?;";
		sqlresult = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (sqlresult == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, DstUin);
			if (sqlite3_step(stmt) == SQLITE_ROW)
			{
				EngageUin =sqlite3_column_int(stmt, 0);
			}
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
		if (EngageUin != 0)
		{
			sql = "SELECT NickName FROM BaseInfo  WHERE Uin=?;";
			sqlresult = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
			if (sqlresult == SQLITE_OK) {
				sqlite3_bind_int(stmt, 1, EngageUin);
				sqlresult = sqlite3_step(stmt);
				if (sqlresult == SQLITE_ROW)
				{
					NickName = (char*)sqlite3_column_text(stmt, 0);
					newname = myutf8trans(NickName);
				}
			}
			sqlite3_finalize(stmt);
			stmt = NULL;
		}
		BYTE* pPlayerRelationInfo = p;
		Write16(pPlayerRelationInfo, 0); //len

		Write32(pPlayerRelationInfo, DstUin); //SrcUin
		if (EngageUin != 0)
		{
			Write32(pPlayerRelationInfo, 0x3); //RelationFlag
		}
		else
		{
			Write32(pPlayerRelationInfo, 0); //RelationFlag
		}
		Write32(pPlayerRelationInfo, 0); //RelationUin 0x0
		Write8(pPlayerRelationInfo, 17);//NickNameLen
		memset(pPlayerRelationInfo, 0, MaxNickName);
		//RelationNickName[]
		if (newname)
		{
			memcpy(pPlayerRelationInfo, newname, strlen(newname));
			delete[] newname;
			newname = NULL;
		}
		
		pPlayerRelationInfo += MaxNickName;

		Write32(pPlayerRelationInfo, 0); //EngageTime
		Write32(pPlayerRelationInfo, 0); //NextCanBookingTimeLimit
		Write32(pPlayerRelationInfo, 0); //BeginHoneyMoonTime
		Write32(pPlayerRelationInfo, 0); //EndHoneyMoonTime
		Write8(pPlayerRelationInfo, 0x4); //EngageFlag 0x4

		len = pPlayerRelationInfo - p;
		Set16(p, (WORD)len);
		p += len;
		
	}
	{ //CurKartAttr
		BYTE* pCurKartAttr = p;
		Write16(pCurKartAttr, 0); //len

		int RefitCout = 0;
		short MaxFlags = 0;
		short WWeight = 0;
		short SpeedWeight = 0;
		short JetWeight = 0;
		short SJetWeight = 0;
		short AccuWeight = 0;
		int ShapeRefitCount = 0;
		int KartHeadRefitItemID = 0;
		int KartTailRefitItemID = 0;
		int KartFlankRefitItemID = 0;
		int KartTireRefitItemID = 0;
		UINT ShapeSuitID = 0;
		UINT ShapeLegendSuitID = 0;
		sql = "SELECT RefitCout,MaxFlags,WWeight,SpeedWeight,JetWeight,SJetWeight,AccuWeight,ShapeRefitCount,KartHeadRefitItemID,KartTailRefitItemID,KartFlankRefitItemID,KartTireRefitItemID,ShapeSuitID  FROM KartRefit WHERE Uin=? AND KartID=?;";
		sqlresult = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (sqlresult == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, DstUin);
			sqlite3_bind_int(stmt, 2, KartItemId);
			if (sqlite3_step(stmt) == SQLITE_ROW)
			{
				RefitCout = sqlite3_column_int(stmt, 0);
				MaxFlags = sqlite3_column_int(stmt, 1);
				WWeight = sqlite3_column_int(stmt, 2);
				SpeedWeight = sqlite3_column_int(stmt, 3);
				JetWeight = sqlite3_column_int(stmt, 4);
				SJetWeight = sqlite3_column_int(stmt, 5);
				AccuWeight = sqlite3_column_int(stmt, 6);

				ShapeRefitCount = sqlite3_column_int(stmt, 7);
				KartHeadRefitItemID = sqlite3_column_int(stmt, 8);
				KartTailRefitItemID = sqlite3_column_int(stmt, 9);
				KartFlankRefitItemID = sqlite3_column_int(stmt, 10);
				KartTireRefitItemID = sqlite3_column_int(stmt, 11);
				ShapeSuitID = sqlite3_column_int(stmt, 12);
			}
		}
		else
		{
			printf("%s\n", sqlite3_errmsg(PlayerDB));
		}
		sqlite3_finalize(stmt);
		stmt = NULL;

		Write32(pCurKartAttr, DstUin); //Uin
		Write32(pCurKartAttr, KartItemId); //KartId
		Write32(pCurKartAttr, RefitCout); //RefitCout
		Write16(pCurKartAttr, MaxFlags); //MaxFlags
		Write16(pCurKartAttr, WWeight); //WWeight
		Write16(pCurKartAttr, SpeedWeight); //SpeedWeight
		Write16(pCurKartAttr, JetWeight); //JetWeight
		Write16(pCurKartAttr, SJetWeight); //SJetWeight
		Write16(pCurKartAttr, AccuWeight); //AccuWeight
		Write32(pCurKartAttr, ShapeRefitCount); //ShapeRefitCount
		Write32(pCurKartAttr, KartHeadRefitItemID); //KartHeadRefitItemID
		Write32(pCurKartAttr, KartTailRefitItemID); //KartTailRefitItemID
		Write32(pCurKartAttr, KartFlankRefitItemID); //KartFlankRefitItemID
		Write32(pCurKartAttr, KartTireRefitItemID); //KartTireRefitItemID
		{ //KartRefitExInfo
			BYTE* pKartRefitExInfo = pCurKartAttr;
			Write16(pKartRefitExInfo, 0); //len

			Write8(pKartRefitExInfo, 0); //SpeedRefitStar
			Write8(pKartRefitExInfo, 0); //JetRefitStar
			Write8(pKartRefitExInfo, 0); //SJetRefitStar
			Write8(pKartRefitExInfo, 0); //AccuRefitStar
			Write8(pKartRefitExInfo, 0); //SpeedAddRatio
			Write8(pKartRefitExInfo, 0); //JetAddRatio
			Write8(pKartRefitExInfo, 0); //SJetAddRatio
			Write8(pKartRefitExInfo, 0); //AccuAddRatio

			len = pKartRefitExInfo - pCurKartAttr;
			Set16(pCurKartAttr, (WORD)len);
			pCurKartAttr += len;
		}
#ifndef ZingSpeed
		Write32(pCurKartAttr, 0); //SecondRefitCount
		Write16(pCurKartAttr, 0); //Speed2Weight
		Write16(pCurKartAttr, 0); //DriftVecWeight
		Write16(pCurKartAttr, 0); //AdditionalZSpeedWeight
		Write16(pCurKartAttr, 0); //AntiCollisionWeight
		Write16(pCurKartAttr, 0); //LuckyValue
		Write16(pCurKartAttr, 0); //RefitLuckyValueMaxWeight
		Write32(pCurKartAttr, ShapeSuitID); //ShapeSuitID
		Write8(pCurKartAttr, 10); //LegendSuitLevel
		Write32(pCurKartAttr, 1111); //LegendSuitLevelChoice
		Write32(pCurKartAttr, ShapeSuitID); //ShapeLegendSuitID
#endif
		len = pCurKartAttr - p;
		Set16(p, (WORD)len);
		p += len;
	}
	
	ClientNode* DstClient = GetClient(DstUin);
	if (!DstClient)
	{
		Write16(p, 0);
	}
	else
	{
		Write16(p, 1); //PetNum responsefindplayerbyqq
		{ //PetInfo
			//国服宠物数据结构
			BYTE* pPetInfo = p;
			Write16(pPetInfo, 0); //len
			Write32(pPetInfo, DstUin); //Uin

			Write32(pPetInfo, DstClient->PetID); //PetId黄金神兽  
			memset(pPetInfo, 0, 17);
			memcpy(pPetInfo, "宠物", 5);
			pPetInfo += 17;
			Write32(pPetInfo, 0);
			Write32(pPetInfo, 0);
			Write8(pPetInfo, 0);

			Write8(pPetInfo, DstClient->PetStatus);//当前宠物形态 黄金神兽 最高4级 

			Write16(pPetInfo, 0x00);//SkillNum

			Write32(pPetInfo, 0x0a); //StrengLevel强化等级 个人信息宠物图标有+5
			Write8(pPetInfo, 0x4); //TopStatus 变形形态
					//变形功能大于1开启
			{ //CommonInfo
				BYTE* pCommonInfo = pPetInfo;
				Write16(pCommonInfo, 0); //len

				Write32(pCommonInfo, 0x5); //HuanHuaLevel幻化等级
				Write8(pCommonInfo, 0x1); //CanHuanHua

				len = pCommonInfo - pPetInfo;
				Set16(pPetInfo, (WORD)len);
				pPetInfo += len;
			}
			len = pPetInfo - p;
			Set16(p, (WORD)len);

			p += len;
		}
	}
	
	Write8(p, 1); //IsInTopList
	{ //KartStoneGrooveInfo
		BYTE* pKartStoneGrooveInfo = p;
		Write16(pKartStoneGrooveInfo, 0); //len

		Write32(pKartStoneGrooveInfo, 0); //KartID
		Write32(pKartStoneGrooveInfo, 0); //StoneGrooveNum
		for (size_t i = 0; i < 0; i++)
		{ //StoneGrooveInfo
			BYTE* pStoneGrooveInfo = pKartStoneGrooveInfo;
			Write16(pStoneGrooveInfo, 0); //len

			Write32(pStoneGrooveInfo, 0); //StoneUseOccaType
			Write32(pStoneGrooveInfo, 0); //SkillStoneID

			len = pStoneGrooveInfo - pKartStoneGrooveInfo;
			Set16(pKartStoneGrooveInfo, (WORD)len);
			pKartStoneGrooveInfo += len;
		}

		len = pKartStoneGrooveInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write8(p, 0); //Contex

	{ //PlayerWlVisibleInfo
		BYTE* pPlayerWlVisibleInfo = p;
		Write16(pPlayerWlVisibleInfo, 0); //len

		Write32(pPlayerWlVisibleInfo, 0); //WonderLandID

		//WonderLandName[]
		memset(pPlayerWlVisibleInfo, 0, MaxNickName);
		pPlayerWlVisibleInfo += MaxNickName;

		Write16(pPlayerWlVisibleInfo, 0); //WonderLandDuty
		Write8(pPlayerWlVisibleInfo, 0); //SubType
		Write8(pPlayerWlVisibleInfo, 0); //GuildGrade

		len = pPlayerWlVisibleInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write32(p, 0); //SkateCoin
	Write32(p, 0); //MaxDayPveScore
	Write32(p, 0); //MaxHistoryPveScore

	{ //EquipedCarBattleModeSkillInfoList
		BYTE* pEquipedCarBattleModeSkillInfoList = p;
		Write16(pEquipedCarBattleModeSkillInfoList, 0); //len

		Write8(pEquipedCarBattleModeSkillInfoList, 0); //SkillNum
		

		len = pEquipedCarBattleModeSkillInfoList - p;
		Set16(p, (WORD)len);
		p += len;
	}
#ifndef ZingSpeed
	Write8(p, 0); //HasCCVisibleInfo
	

	Write8(p, 0); //HasCheerAddition


	Write32(p, 0); //LoveValue
	Write16(p, 0); //CanEnterChannelFalg[]
	Write8(p, 0); //SpecialActivityID
	Write32(p, 0); //ThemeHouseDressDegreeValue
	Write8(p, 0); //AreaIdDst
	Write8(p, 0); //SpecialActivityIDNum
	Write8(p, 0); //SimpleInfo
#endif

	len = p - buf;
	SendToClient(Client, 122, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestGetAchieveList(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	UINT DstUin = Read32(p);

	ResponseGetAchieveList(Client, DstUin);
}

void ResponseGetAchieveList(ClientNode* Client, UINT DstUin)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	Write32(p, DstUin); //DstUin

	Write16(p, 0); //Result
	Write16(p, 1); //AchieveNum
	for (size_t i = 0; i < 1; i++)
	{ //Achieves
		BYTE* pAchieves = p;
		Write16(pAchieves, 0); //len

		Write16(pAchieves, 7937); //ID
		Write8(pAchieves, 0); //ShowType
		Write8(pAchieves, 0); //LogicType
		Write8(pAchieves, 0); //Status
		Write16(pAchieves, 0); //Progress
		Write16(pAchieves, 0); //TotalProgress
		Write32(pAchieves, 0); //FinTime
		Write16(pAchieves, 0); //AchieveValue
		Write32(pAchieves, 0); //AchieveFlagType

		len = pAchieves - p;
		Set16(p, (WORD)len);
		p += len;
	}

	len = p - buf;
	SendToClient(Client, 373, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void ResponseGetGroupFriendBaseInfo(ClientNode* Client,UINT Uin,char *newname)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	Write16(p, 0); //GroupID
	{ //GroupFriendBaseInfo
		BYTE* pGroupFriendBaseInfo = p;
		Write16(pGroupFriendBaseInfo, 0); //len

		Write32(pGroupFriendBaseInfo, Uin); //Uin
		memset(pGroupFriendBaseInfo, 0, 17);
		if (newname)
		{
			memcpy(pGroupFriendBaseInfo, newname, strlen(newname));
		}
		pGroupFriendBaseInfo += 17;
		len = pGroupFriendBaseInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write8(p, 0); //ReasonLen

	len = p - buf;
	SendToClient(Client, 148, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestGetGroupFriendBaseInfo(ClientNode* Client)
{
	//BYTE* p = Body; WORD len;

	//UINT Uin = Read32(p);
	//UINT Time = Read32(p);
	//short GroupID = Read16(p);

	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	char* NickName = NULL;
	char* newname = NULL;
	//联合查询
	sql = "SELECT F.Uin,B.NickName FROM FriendInfo F join BaseInfo b  on F.Uin=B.Uin WHERE F.FriendUin = ?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Uin);
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			NickName = (char*)sqlite3_column_text(stmt, 1);
			newname = myutf8trans(NickName);
			ResponseGetGroupFriendBaseInfo(Client, sqlite3_column_int(stmt, 0),newname);
			if (newname)
			{
				delete[] newname;
				newname = NULL;
			}
		}
	}
}
void NotifySpecialActivityInfo(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	Write16(p, 0); //ActivityID
	Write8(p, 0); //Flag
	Write32(p, 0); //OpenDate
	Write32(p, 0); //CloseDate
	Write32(p, 0); //OpenTime
	Write32(p, 0); //CloseTime
	Write8(p, 0); //SpecialActivityIDNum
	Write8(p, 1); //SpecialActivityInfoNum
	for (size_t i = 0; i < 1; i++)
	{ //SpecialActivityInfo
		BYTE* pSpecialActivityInfo = p;
		Write16(pSpecialActivityInfo, 0); //len

		Write8(pSpecialActivityInfo, 1); //ProfessionLicenseInfoNum
		for (size_t i = 0; i < 1; i++)
		{ //ProfessionLicenseInfo
			BYTE* pProfessionLicenseInfo = pSpecialActivityInfo;
			Write16(pProfessionLicenseInfo, 0); //len

			Write8(pProfessionLicenseInfo, 6); //BigLevel
			Write8(pProfessionLicenseInfo, 5); //SmallLevel

			len = pProfessionLicenseInfo - pSpecialActivityInfo;
			Set16(pSpecialActivityInfo, (WORD)len);
			pSpecialActivityInfo += len;
		}

		len = pSpecialActivityInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	len = p - buf;
	SendToClient(Client, 24767, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void ResponseShapeLegendOperate(ClientNode* Client, UCHAR OpType, int ShapeID, UCHAR ShapeLevel, int NewShowChoice)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	Write8(p, 0); //ReasonLen
	Write8(p, 0); //OpType
	Write16(p, 0); //ShapeNum
	for (size_t i = 0; i < 0; i++)
	{ //ShapeInfo
		BYTE* pShapeInfo = p;
		Write16(pShapeInfo, 0); //len

		Write32(pShapeInfo, 0); //ShapeID
		Write8(pShapeInfo, 0); //ShapeLevel
		Write32(pShapeInfo, 0); //ShowChoice

		len = pShapeInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write32(p, 0); //ShapeID
	Write8(p, 0); //ShapeLevel
	Write8(p, 0); //HasRefit
	for (size_t i = 0; i < 0; i++)
	{ //RefitClientInfo
		BYTE* pRefitClientInfo = p;
		Write16(pRefitClientInfo, 0); //len

		Write32(pRefitClientInfo, 0); //Uin
		Write32(pRefitClientInfo, 0); //KartId
		Write32(pRefitClientInfo, 0); //RefitCout
		Write16(pRefitClientInfo, 0); //MaxFlags
		Write16(pRefitClientInfo, 0); //WWeight
		Write16(pRefitClientInfo, 0); //SpeedWeight
		Write16(pRefitClientInfo, 0); //JetWeight
		Write16(pRefitClientInfo, 0); //SJetWeight
		Write16(pRefitClientInfo, 0); //AccuWeight
		Write32(pRefitClientInfo, 0); //ShapeRefitCount
		Write32(pRefitClientInfo, 0); //KartHeadRefitItemID
		Write32(pRefitClientInfo, 0); //KartTailRefitItemID
		Write32(pRefitClientInfo, 0); //KartFlankRefitItemID
		Write32(pRefitClientInfo, 0); //KartTireRefitItemID
		{ //KartRefitExInfo
			BYTE* pKartRefitExInfo = pRefitClientInfo;
			Write16(pKartRefitExInfo, 0); //len

			Write8(pKartRefitExInfo, 0); //SpeedRefitStar
			Write8(pKartRefitExInfo, 0); //JetRefitStar
			Write8(pKartRefitExInfo, 0); //SJetRefitStar
			Write8(pKartRefitExInfo, 0); //AccuRefitStar
			Write8(pKartRefitExInfo, 0); //SpeedAddRatio
			Write8(pKartRefitExInfo, 0); //JetAddRatio
			Write8(pKartRefitExInfo, 0); //SJetAddRatio
			Write8(pKartRefitExInfo, 0); //AccuAddRatio

			len = pKartRefitExInfo - pRefitClientInfo;
			Set16(pRefitClientInfo, (WORD)len);
			pRefitClientInfo += len;
		}
		Write32(pRefitClientInfo, 0); //SecondRefitCount
		Write16(pRefitClientInfo, 0); //Speed2Weight
		Write16(pRefitClientInfo, 0); //DriftVecWeight
		Write16(pRefitClientInfo, 0); //AdditionalZSpeedWeight
		Write16(pRefitClientInfo, 0); //AntiCollisionWeight
		Write16(pRefitClientInfo, 0); //LuckyValue
		Write16(pRefitClientInfo, 0); //RefitLuckyValueMaxWeight
		Write32(pRefitClientInfo, 0); //ShapeSuitID
		Write8(pRefitClientInfo, 0); //LegendSuitLevel
		Write32(pRefitClientInfo, 0); //LegendSuitLevelChoice
		Write32(pRefitClientInfo, 0); //ShapeLegendSuitID

		len = pRefitClientInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write32(p, 0); //NewShowChoice
	Write32(p, 0); //DirectMaxLevelShapeID
	Write32(p, 0); //DirectMaxShapePreLevel

	len = p - buf;
	SendToClient(Client, 319, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestShapeLegendOperate(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body; WORD len;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	UCHAR OpType = Read8(p);
	int ShapeID = Read32(p);
	UCHAR ShapeLevel = Read8(p);
	int NewShowChoice = Read32(p);
	//ResponseShapeLegendOperate(Client, OpType, ShapeID,ShapeLevel, NewShowChoice);

}