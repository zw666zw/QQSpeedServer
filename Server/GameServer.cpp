#include "GameServer.h"

extern std::recursive_mutex Mutex;
extern void NotifyRaceOver(ClientNode* Client, RoomNode* Room);
std::map<long, ClientNode*> Clients;
extern sqlite3* PlayerDB;
extern std::string IP;
extern USHORT TcpPort;
extern USHORT UdpPort;
//extern std::map<long, RoomNode*> Rooms;
BYTE taskaward[128] = { 0 };
BYTE BorderOver[187];
BYTE RankedOver[402];
BYTE jump24238[91];
BYTE jump24255[91];
BYTE StartTimerChallenge[1024] = { 0 };
BYTE StartTimerChallenge2[1024] = { 0 };
void ResponseGetSuperN2O(ClientNode* Client);
void ResponseGetSuperN2O2(ClientNode* Client);
extern std::string UITitleDispInfo_ADText;


extern UINT GameOverTime;
int Prob = 290;
extern void NotifyChangeReadyState(ClientNode* Client, UINT Uin, bool State);
extern void NotifyWaitUnReadyPlayers(ClientNode* Client);
void NotifyGenGameEndBoxAward(ClientNode* Client);
void NotifyRankedMatchSeasonInfo(ClientNode* Client, UINT SrcUin);
UINT RankGradeLevel[8] = { 0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b };
extern void RequestEnter3DRoom(ClientNode* Client);
extern void NotifyChangeRoomOwner(ClientNode* Client, RoomNode* Room);

void WriteKartPhysParam(BYTE*& p, UINT Uin, UINT KartID, ClientNode* Client)
{
	//写赛车物理性能 客户端根据这个决定赛车的性能
	WORD len;
	BYTE* pKartPhysParam = p;
	Write16(pKartPhysParam, 0); //len


	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;

	UINT curskill1, curskill2, curskill3;
	UINT curskillv1, curskillv2, curskillv3;
	UINT skilln2o, skillhide, skillview, convertspeed;
	UINT PetID = 0;
	UINT status = 0;
	UINT level = 0;
	UINT strenglevel = 0;
	skilln2o = skillhide = skillview = convertspeed = 0;
	char* petname;
	UINT SuperN2ORate = 0, SuperN2OTime = 0;
	Client->SuperN2O = 0;
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
	if (Uin > 10000) //Not NPC
	{
		sql = "SELECT RefitCout,MaxFlags,WWeight,SpeedWeight,JetWeight,SJetWeight,AccuWeight,ShapeRefitCount,KartHeadRefitItemID,KartTailRefitItemID,KartFlankRefitItemID,KartTireRefitItemID  FROM KartRefit WHERE Uin=? AND KartID=?;";
		result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (result == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, Uin);
			sqlite3_bind_int(stmt, 2, KartID);
			if (sqlite3_step(stmt) == SQLITE_ROW)
			{
				//可设置全局改装
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
		else
		{
			printf("%s\n", sqlite3_errmsg(PlayerDB));
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
	}
	//查询是否装备有改装加成卡120258
	if (Client->GlobalAddcard == 1)
	{
		//如果有改装加成卡 全车29
		SpeedWeight = JetWeight = SJetWeight = AccuWeight = 29;
	}


	//查询PetItem所有宠物id 并查看Item是否有装备的宠物
	char peton = 0;
	if (Client->PetID != 0)
	{

		peton = 1;
		sql = "SELECT * FROM PetItem Where PetId=?;";
		result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
		if (result == SQLITE_OK) {
			sqlite3_bind_int(stmt, 1, Client->PetID);
			if (sqlite3_step(stmt) == SQLITE_ROW) {

				curskill1 = sqlite3_column_int(stmt, 5);
				curskillv1 = sqlite3_column_int(stmt, 6);
				curskill2 = sqlite3_column_int(stmt, 7);
				curskillv2 = sqlite3_column_int(stmt, 8);
				curskill3 = sqlite3_column_int(stmt, 9);
				curskillv3 = sqlite3_column_int(stmt, 10);
				//printf("curpetid:%d\n", curpetid);
				//printf("curskill1id:%d\n", curskill1);
				//printf("curskillv1:%d\n", curskillv1);
			}
		}
		sqlite3_finalize(stmt);
		stmt = NULL;
	}



	//查询赛车技能
	sql = "SELECT * FROM KartSkill Where KartId=?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, KartID);
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			Client->SuperN2O = sqlite3_column_int(stmt, 1);
			skilln2o = sqlite3_column_int(stmt, 2);
			skillhide = sqlite3_column_int(stmt, 3);
			skillview = sqlite3_column_int(stmt, 4);
			convertspeed = sqlite3_column_int(stmt, 5);
			SuperN2ORate = sqlite3_column_int(stmt, 6);
			SuperN2OTime = sqlite3_column_int(stmt, 7);
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;
	if (skilln2o != 0)
		skilln2o = 1;
	if (skillhide != 0)
		skillhide = 4;
	if (skillview != 0)
		skillview = 2;

	char FilePath[MAX_PATH];
	UINT PhysInfosize;
	if (Client->KartSkinID != 0)
	{
		sprintf_s(FilePath, ".\\Kart\\%d.yml", Client->KartSkinID);
	}
	else
	{
		sprintf_s(FilePath, ".\\Kart\\%d.yml", KartID);
	}
	//sprintf_s(FilePath, ".\\Kart\\%d.yml", KartID);
	YAML::Node config = YAML::LoadFile(FilePath);

	Write32(pKartPhysParam, KartID);

	YAML::Node PhysInfo = config["PhysInfo"];
	PhysInfosize = PhysInfo.size() + 1;
	if (Client->KartSkinID == 127616)
		PhysInfosize += 1;
	Write8(pKartPhysParam, (BYTE)PhysInfosize); //PhysInfoCount
	YAML::Node PhysInfoParam;
	for (size_t i = 0; i < PhysInfo.size(); i++)
	{
		PhysInfoParam = PhysInfo[i];
		{ //PhysInfo
			BYTE* pPhysInfo = pKartPhysParam;
			Write16(pPhysInfo, 0); //len

			int PID = PhysInfoParam["PID"].as<int>();
			int AffectID = PhysInfoParam["AffectID"].as<int>();
			int Param = PhysInfoParam["Param"].as<int>();
			int LifeTime = PhysInfoParam["LifeTime"].as<int>();


			//TODO: 应该限制最大值, 但懒得做限制, 因为不同赛车等级是不同的, 留给后人去折腾吧!
			switch (PID)//增强kart车辆部分性能
			{
			case 1: //燃料
				Param += 10 * JetWeight;
				LifeTime += 8 * JetWeight;
				break;
			case 2001: //点火
				Param += 10 * SJetWeight;
				LifeTime += 4 * SJetWeight;//点火时长
				break;
			case 99999: //进气
				Param += 300 * AccuWeight;
				break;
			default:
				break;
			}

			Write32(pPhysInfo, PID);
			Write32(pPhysInfo, AffectID);
			Write32(pPhysInfo, Param);
			Write32(pPhysInfo, LifeTime);

			len = pPhysInfo - pKartPhysParam;
			Set16(pKartPhysParam, (WORD)len);
			pKartPhysParam += len;
		}
		PhysInfoParam.reset();
	}
	PhysInfo.reset();
	if (Client->KartSkinID == 127616)
	{ //紫色超级氮气
		BYTE* pPhysInfo = pKartPhysParam;
		Write16(pPhysInfo, 0); //len
		Write32(pPhysInfo, 777);//玉麒麟专属超级喷 必须写入这个数据才能显示专属氮气条
		Write32(pPhysInfo, 100);
		Write32(pPhysInfo, SuperN2ORate);
		Write32(pPhysInfo, SuperN2OTime);
		len = pPhysInfo - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
	}
	{ //紫色超级氮气
		BYTE* pPhysInfo = pKartPhysParam;
		Write16(pPhysInfo, 0); //len
		Write32(pPhysInfo, 34);
		Write32(pPhysInfo, 100);
		Write32(pPhysInfo, SuperN2ORate);
		Write32(pPhysInfo, SuperN2OTime);
		len = pPhysInfo - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
	}
	Client->SuperJet = 0;
	Client->SuperJetKartFuelInc = 0;
	Client->CurrentAccelerateFuel = 0;
	Client->PropID = 0;
	float CompensateParamPet = 1.0;
	if (peton == 1)
	{
		if (curskill1 == 1)
		{
			CompensateParamPet = curskillv1 / 100; //落后补偿技能生效
		}
		else if (curskill2 == 1)
		{
			CompensateParamPet = curskillv2 / 100;
		}
		else if (curskill3 == 1)
		{
			CompensateParamPet = curskillv3 / 100;
		}
		else
		{
			CompensateParamPet = 1.0;//如果宠物技能没有落后补偿
		}
	}
	//printf("落后补偿:%f", CompensateParamPet);
	YAML::Node CompensateParam = config["CompensateParam"];//落后补偿 //技能id：1
	Write8(pKartPhysParam, (BYTE)CompensateParam.size()); //CompensateParamCount
	YAML::Node CompensateParamParam;
	for (size_t i = 0; i < CompensateParam.size(); i++)
	{
		CompensateParamParam = CompensateParam[i];
		{ //CompensateParam
			BYTE* pCompensateParam = pKartPhysParam;
			Write16(pCompensateParam, 0); //len

			Write32(pCompensateParam, CompensateParamParam["Percent"].as<int>());
			Write32(pCompensateParam, CompensateParamParam["Value"].as<int>() * CompensateParamPet);

			len = pCompensateParam - pKartPhysParam;
			Set16(pKartPhysParam, (WORD)len);
			pKartPhysParam += len;
		}
		CompensateParamParam.reset();
	}
	CompensateParam.reset();
	{ //CollisionBoxParam
		YAML::Node CollisionBoxParam = config["CollisionBoxParam"];
		BYTE* pCollisionBoxParam = pKartPhysParam;
		Write16(pCollisionBoxParam, 0); //len

		Write32(pCollisionBoxParam, CollisionBoxParam["BoxLength"].as<int>());
		Write32(pCollisionBoxParam, CollisionBoxParam["BoxWidth"].as<int>());
		Write32(pCollisionBoxParam, CollisionBoxParam["BoxHeight"].as<int>());
		Write32(pCollisionBoxParam, CollisionBoxParam["AdjustOffset"].as<int>());
		Write32(pCollisionBoxParam, CollisionBoxParam["AdjustPickGap"].as<int>());
		Write32(pCollisionBoxParam, CollisionBoxParam["AdjustRemoteOffset"].as<int>());
		Write32(pCollisionBoxParam, CollisionBoxParam["AdjustBevelOffset"].as<int>());
		Write32(pCollisionBoxParam, CollisionBoxParam["ControllerOffset"].as<int>());

		len = pCollisionBoxParam - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
		CollisionBoxParam.reset();
	}

	{ //CarToCarCollisionParam
		YAML::Node CarToCarCollisionParam = config["CarToCarCollisionParam"];
		BYTE* pCarToCarCollisionParam = pKartPhysParam;
		Write16(pCarToCarCollisionParam, 0); //len

		Write32(pCarToCarCollisionParam, CarToCarCollisionParam["CollisionRadius"].as<int>());
		Write32(pCarToCarCollisionParam, CarToCarCollisionParam["CollisionLength"].as<int>());
		Write32(pCarToCarCollisionParam, CarToCarCollisionParam["CollisionWidth"].as<int>());
		Write32(pCarToCarCollisionParam, CarToCarCollisionParam["CollisionHeight"].as<int>());
		Write32(pCarToCarCollisionParam, CarToCarCollisionParam["CollisionLostCtrlTime"].as<int>());

		len = pCarToCarCollisionParam - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
		CarToCarCollisionParam.reset();
	}

	Write32(pKartPhysParam, config["BaseTurnRate"].as<int>());
	Write32(pKartPhysParam, config["VolatileTurnRate"].as<int>());
	Write32(pKartPhysParam, config["MaxTurnSpeed"].as<int>());
	Write32(pKartPhysParam, config["MinTurnSpeed"].as<int>());
	Write32(pKartPhysParam, config["MaxAccuTime"].as<int>());
	Write32(pKartPhysParam, config["BaseAccuRate"].as<int>());
	Write32(pKartPhysParam, config["MaxAffectSpeed"].as<int>());
	Write32(pKartPhysParam, config["Gravity"].as<int>() + (10 * WWeight)); //TODO: 悬挂; 未限制最大值!
	Write32(pKartPhysParam, config["AdditionalLocalZSpeed"].as<int>());
	Write32(pKartPhysParam, config["StartVec"].as<int>());
	Write32(pKartPhysParam, config["EndVecFist"].as<int>());
	Write32(pKartPhysParam, config["EndVecSecon"].as<int>());
	Write32(pKartPhysParam, config["DirKeyForce"].as<int>());
	Write32(pKartPhysParam, config["DirKeyTwist"].as<int>());
	Write32(pKartPhysParam, config["BannerTwist"].as<int>());
	Write32(pKartPhysParam, config["BannerKeyTwist"].as<int>());
	Write32(pKartPhysParam, config["BannerVecForce"].as<int>());
	Write32(pKartPhysParam, config["BannerHeadForce"].as<int>());
	Write32(pKartPhysParam, config["SlidFricForce"].as<int>());
	Write32(pKartPhysParam, config["RollFricForce"].as<int>());
	Write32(pKartPhysParam, config["StartWec"].as<int>());
	Write32(pKartPhysParam, config["MaxWec"].as<int>());
	Write32(pKartPhysParam, config["SuaiJianTwist"].as<int>());
	Write32(pKartPhysParam, config["DirUpKeyForce"].as<int>());

	YAML::Node AccelStatus = config["AccelStatus"];
	Write8(pKartPhysParam, (BYTE)AccelStatus.size()); //AccelStatusCount
	YAML::Node AccelStatusParam;
	for (size_t i = 0; i < AccelStatus.size(); i++)
	{
		AccelStatusParam = AccelStatus[i];
		{ //m_astKartPhysParam[].m_aiAccelStatus[]
			Write32(pKartPhysParam, AccelStatusParam.as<int>());
		}
		AccelStatusParam.reset();
	}
	AccelStatus.reset();

	YAML::Node ForwardAccel = config["ForwardAccel"];
	Write8(pKartPhysParam, (BYTE)ForwardAccel.size()); //ForwardAccelNum
	YAML::Node ForwardAccelParam;
	for (size_t i = 0; i < ForwardAccel.size(); i++)
	{
		ForwardAccelParam = ForwardAccel[i];
		{ //ForwardAccel
			BYTE* pForwardAccel = pKartPhysParam;
			Write16(pForwardAccel, 0); //len

			int Key = ForwardAccelParam["Key"].as<int>();
			int Value = ForwardAccelParam["Value"].as<int>();
			if (i >= 7 && i <= 9)
			{
				//TODO: 引擎; 未限制最大值!
				Value += 35 * SpeedWeight;
			}
			Write32(pForwardAccel, Key);
			Write32(pForwardAccel, Value);

			len = pForwardAccel - pKartPhysParam;
			Set16(pKartPhysParam, (WORD)len);
			pKartPhysParam += len;
		}
		ForwardAccelParam.reset();
	}
	ForwardAccel.reset();


	YAML::Node ForwardDecel = config["ForwardDecel"];
	Write8(pKartPhysParam, (BYTE)ForwardDecel.size()); //ForwardDecelNum
	YAML::Node ForwardDecelParam;
	for (size_t i = 0; i < ForwardDecel.size(); i++)
	{
		ForwardDecelParam = ForwardDecel[i];
		{ //ForwardDecel
			BYTE* pForwardDecel = pKartPhysParam;
			Write16(pForwardDecel, 0); //len

			Write32(pForwardDecel, ForwardDecelParam["Key"].as<int>());
			Write32(pForwardDecel, ForwardDecelParam["Value"].as<int>());

			len = pForwardDecel - pKartPhysParam;
			Set16(pKartPhysParam, (WORD)len);
			pKartPhysParam += len;
		}
		ForwardDecelParam.reset();
	}
	ForwardDecel.reset();

	YAML::Node BackwardAccel = config["BackwardAccel"];
	Write8(pKartPhysParam, (BYTE)BackwardAccel.size()); //BackwardAccelNum
	YAML::Node BackwardAccelParam;
	for (size_t i = 0; i < BackwardAccel.size(); i++)
	{
		BackwardAccelParam = BackwardAccel[i];
		{ //BackwardAccel
			BYTE* pBackwardAccel = pKartPhysParam;
			Write16(pBackwardAccel, 0); //len

			Write32(pBackwardAccel, BackwardAccelParam["Key"].as<int>());
			Write32(pBackwardAccel, BackwardAccelParam["Value"].as<int>());

			len = pBackwardAccel - pKartPhysParam;
			Set16(pKartPhysParam, (WORD)len);
			pKartPhysParam += len;
		}
		BackwardAccelParam.reset();
	}
	BackwardAccel.reset();

	YAML::Node BackwardDecel = config["BackwardDecel"];
	Write8(pKartPhysParam, (BYTE)BackwardDecel.size()); //BackwardDecelNum
	YAML::Node BackwardDecelParam;
	for (size_t i = 0; i < BackwardDecel.size(); i++)
	{
		BackwardDecelParam = BackwardDecel[i];
		{ //BackwardDecel
			BYTE* pBackwardDecel = pKartPhysParam;
			Write16(pBackwardDecel, 0); //len

			Write32(pBackwardDecel, BackwardDecelParam["Key"].as<int>());
			Write32(pBackwardDecel, BackwardDecelParam["Value"].as<int>());

			len = pBackwardDecel - pKartPhysParam;
			Set16(pKartPhysParam, (WORD)len);
			pKartPhysParam += len;
		}
		BackwardDecelParam.reset();
	}
	BackwardDecel.reset();
	if (peton == 1)
	{
		if (curskill1 == 2)
		{
			Write32(pKartPhysParam, curskillv1); //CrashCompensatePower碰撞氮气保留 保留100=100*10 加个条件有宠物才加
		}
		else if (curskill2 == 2)
		{
			Write32(pKartPhysParam, curskillv2);
		}
		else if (curskill3 == 2)
		{
			Write32(pKartPhysParam, curskillv3);
		}
		else
		{
			Write32(pKartPhysParam, 0);//如果宠物技能没有碰撞保护
		}
	}
	else//如果没装备宠物
	{
		Write32(pKartPhysParam, 0);
	}
	Write32(pKartPhysParam, 0); //DefenseRate
	Write32(pKartPhysParam, Uin); //Uin
	Write32(pKartPhysParam, 0xFFFFFFFF); //SpeedupCardGenRate组队模式下加速卡生产速率?
	Write8(pKartPhysParam, 0xFF);
	Write8(pKartPhysParam, 0xFF);
	Write8(pKartPhysParam, 0xFF);
	//Write8(pKartPhysParam, 0b00000111);//ExtraFuncFlag额外技能标志
	Write8(pKartPhysParam, 0xF8 | skillhide | skilln2o | skillview);// skillhide | skilln2o | skillview
	//最后一个二进制位生效蓝色氮气 倒数第3位是隐身 倒数第2位其他人氮气等道具数量可视

	Write8(pKartPhysParam, 0); //HasSkatePara
	/*
m_astKartPhysParam[].m_hasSkatePara[].m_iTrackSpeed
m_astKartPhysParam[].m_hasSkatePara[].m_iSkateSpeedCoef_AirBigJet
m_astKartPhysParam[].m_hasSkatePara[].m_iSkateSpeedCoef_Jump
m_astKartPhysParam[].m_hasSkatePara[].m_iSkateSpeedCoef_AirJetPoint
m_astKartPhysParam[].m_hasSkatePara[].m_iSkateSpeedCoef_MaxForce
m_astKartPhysParam[].m_hasSkatePara[].m_iOntrackAccRef
m_astKartPhysParam[].m_hasSkatePara[].m_iTrackAccRef
m_astKartPhysParam[].m_hasSkatePara[].m_iDashSkill
		*/

		//m_b->bool 单字节?
		//m_sh 有符号short 2字节
		//m_i 有符号 int 4字节
		//m_uch 无符号char
	Write8(pKartPhysParam, 0); //HasBattleModeSkillInfoList
	for (size_t i = 0; i < 0; i++)
	{ //BattleModeSkillInfoList
		BYTE* pBattleModeSkillInfoList = pKartPhysParam;
		Write16(pBattleModeSkillInfoList, 0); //len

		Write8(pBattleModeSkillInfoList, 0); //SkillNum
		for (size_t i = 0; i < 0; i++)
		{ //SkillInfo
			BYTE* pSkillInfo = pBattleModeSkillInfoList;
			Write16(pSkillInfo, 0); //len

			Write16(pSkillInfo, 0); //SkillId
			Write8(pSkillInfo, 0); //SkillLevel

			len = pSkillInfo - pBattleModeSkillInfoList;
			Set16(pBattleModeSkillInfoList, (WORD)len);
			pBattleModeSkillInfoList += len;
		}

		len = pBattleModeSkillInfoList - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
	}

#ifndef ZingSpeed
	//Write32(pKartPhysParam, 0x000000FF); //EnergyConvert 能量转换?
	// 漂移时为隐身技能提供能量
	//0x0000FFFF漂移直接集满?
	Write8(pKartPhysParam, 0x00);
	Write8(pKartPhysParam, 0x00);
	Write8(pKartPhysParam, 0x00);
	//Write8(pKartPhysParam, 0b11111111);
	Write8(pKartPhysParam, convertspeed);//convertspeed
	Write16(pKartPhysParam, 0xFFFF); //SuperN2ORate 超级氮气生效标志? 
	Write16(pKartPhysParam, 0); //CollisionLoseRate 碰撞损失速率
	Write8(pKartPhysParam, 0); //NotInterruptDrift 不断漂移

	Write8(pKartPhysParam, 0); //AddWeightNum

	Write8(pKartPhysParam, 0); //WeightNum

	Write8(pKartPhysParam, 0); //HasAntiCollisionCfg 碰撞保护配置
	/*
m_astKartPhysParam[].m_astAntiCollistionCfg[].m_uchNum
m_astKartPhysParam[].m_astAntiCollistionCfg[].m_aiPosition[]
		*/
		//YAML::Node BoatParam = config["BoatParam"];
	Write8(pKartPhysParam, 1); //HasBoatParam 开船图必须写开船物理性能 否则卡死
	for (size_t i = 0; i < 1; i++)
	{ //BoatParam
		BYTE* pBoatParam = pKartPhysParam;
		Write16(pBoatParam, 0); //len

		Write32(pBoatParam, 0); //DirKeyForceParamC
		Write32(pBoatParam, 0); //DirKeyForceParamD
		Write32(pBoatParam, 0); //DTFLimitAngle
		Write32(pBoatParam, 0); //DTFRatio
		Write32(pBoatParam, 10000); //UpKeyVecForce
		Write32(pBoatParam, 2000); //UpKeyVecForceParamA
		Write32(pBoatParam, -800); //UpKeyVecForceParamB
		Write32(pBoatParam, 0); //LRKeyVecForce
		Write32(pBoatParam, 2000); //LRKeyVecForceParamA
		Write32(pBoatParam, 70); //LRKeyVecForceParamB
		Write32(pBoatParam, 1000); //VecForce
		Write32(pBoatParam, 0); //VecForceParamA
		Write32(pBoatParam, 300); //VecForceParamB
		Write32(pBoatParam, 250); //BoatShape[]
		Write32(pBoatParam, 250); //BoatShape[]
		Write32(pBoatParam, 1000); //BoatShape[]
		Write32(pBoatParam, 3100); //WecEffect
		Write32(pBoatParam, 4500); //BannerKeyTwist
		Write32(pBoatParam, 0); //BannerKeyTwistParamA
		Write32(pBoatParam, 1000); //BannerKeyTwistParamB
		Write32(pBoatParam, 5000); //SuaiJianTwist
		Write32(pBoatParam, 600); //BoatHeighRatio
		Write32(pBoatParam, 5200); //BannerTwist
		Write32(pBoatParam, 1300); //BannerTwistParamA
		Write32(pBoatParam, 4000); //DirUpKeyForce
		Write32(pBoatParam, 3500); //DirUpKeyForceParamA
		Write32(pBoatParam, 0); //DirUpKeyForceParamB
		Write32(pBoatParam, 0); //DirKeyForce
		Write32(pBoatParam, 0); //DirKeyForceParamA
		Write32(pBoatParam, 1000000); //DirKeyForceParamB
		Write32(pBoatParam, 350000); //AddNO2PerSec
		Write32(pBoatParam, 375); //BoatAirValue
		Write32(pBoatParam, 3000); //ifSlidFricForce

		len = pBoatParam - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
	}
	//YAML::Node BoatForwardAccel = config["BoatForwardAccel"];
	Write8(pKartPhysParam, 13); //BoatForwardAccelNum
	//for (size_t i = 0; i < 13; i++)
	{ //BoatForwardAccel
		BYTE* pBoatForwardAccel = pKartPhysParam;
		Write16(pBoatForwardAccel, 0); //len
		Write32(pBoatForwardAccel, 0);
		Write32(pBoatForwardAccel, 5100);

		len = pBoatForwardAccel - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
	}
	{ //BoatForwardAccel
		BYTE* pBoatForwardAccel = pKartPhysParam;
		Write16(pBoatForwardAccel, 0); //len
		Write32(pBoatForwardAccel, 5000);
		Write32(pBoatForwardAccel, 5100);

		len = pBoatForwardAccel - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
	}
	{ //BoatForwardAccel
		BYTE* pBoatForwardAccel = pKartPhysParam;
		Write16(pBoatForwardAccel, 0); //len
		Write32(pBoatForwardAccel, 5700);
		Write32(pBoatForwardAccel, 5600);

		len = pBoatForwardAccel - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
	}
	{ //BoatForwardAccel
		BYTE* pBoatForwardAccel = pKartPhysParam;
		Write16(pBoatForwardAccel, 0); //len
		Write32(pBoatForwardAccel, 9000);
		Write32(pBoatForwardAccel, 6100);

		len = pBoatForwardAccel - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
	}
	{ //BoatForwardAccel
		BYTE* pBoatForwardAccel = pKartPhysParam;
		Write16(pBoatForwardAccel, 0); //len
		Write32(pBoatForwardAccel, 9300);
		Write32(pBoatForwardAccel, 6600);

		len = pBoatForwardAccel - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
	}
	{ //BoatForwardAccel
		BYTE* pBoatForwardAccel = pKartPhysParam;
		Write16(pBoatForwardAccel, 0); //len
		Write32(pBoatForwardAccel, 11000);
		Write32(pBoatForwardAccel, 7000);

		len = pBoatForwardAccel - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
	}
	{ //BoatForwardAccel
		BYTE* pBoatForwardAccel = pKartPhysParam;
		Write16(pBoatForwardAccel, 0); //len
		Write32(pBoatForwardAccel, 11800);
		Write32(pBoatForwardAccel, 7100);

		len = pBoatForwardAccel - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
	}
	{ //BoatForwardAccel
		BYTE* pBoatForwardAccel = pKartPhysParam;
		Write16(pBoatForwardAccel, 0); //len
		Write32(pBoatForwardAccel, 15000);
		Write32(pBoatForwardAccel, 9300);

		len = pBoatForwardAccel - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
	}
	{ //BoatForwardAccel
		BYTE* pBoatForwardAccel = pKartPhysParam;
		Write16(pBoatForwardAccel, 0); //len
		Write32(pBoatForwardAccel, 16000);
		Write32(pBoatForwardAccel, 9300);

		len = pBoatForwardAccel - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
	}
	{ //BoatForwardAccel
		BYTE* pBoatForwardAccel = pKartPhysParam;
		Write16(pBoatForwardAccel, 0); //len
		Write32(pBoatForwardAccel, 20000);
		Write32(pBoatForwardAccel, 9350);

		len = pBoatForwardAccel - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
	}
	{ //BoatForwardAccel
		BYTE* pBoatForwardAccel = pKartPhysParam;
		Write16(pBoatForwardAccel, 0); //len
		Write32(pBoatForwardAccel, 25000);
		Write32(pBoatForwardAccel, 9300);

		len = pBoatForwardAccel - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
	}
	{ //BoatForwardAccel
		BYTE* pBoatForwardAccel = pKartPhysParam;
		Write16(pBoatForwardAccel, 0); //len
		Write32(pBoatForwardAccel, 30000);
		Write32(pBoatForwardAccel, 9300);

		len = pBoatForwardAccel - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
	}
	{ //BoatForwardAccel
		BYTE* pBoatForwardAccel = pKartPhysParam;
		Write16(pBoatForwardAccel, 0); //len
		Write32(pBoatForwardAccel, 35000);
		Write32(pBoatForwardAccel, 9300);

		len = pBoatForwardAccel - pKartPhysParam;
		Set16(pKartPhysParam, (WORD)len);
		pKartPhysParam += len;
	}
	Write32(pKartPhysParam, 0); //DirUpKeyForceParamA
	Write32(pKartPhysParam, 0); //DirUpKeyForceParamB
#endif

	len = pKartPhysParam - p;
	Set16(p, len);
	p += len;
}


void WINAPI OnBegin(RoomNode* Room)
{
	Room->CountDownFlag = 0;
	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			NotifyRaceBegin(RoomClient);
		}
	}
}

void WINAPI OnCountDown3(RoomNode* Room)
{
	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			
			RoomClient->ReadyState = 0;//准备状态设置 防止卡准备
			
			RoomClient->IsFinish = FALSE;
			
			NotifyGameOver(RoomClient, 0, 0, NULL);
			
			
			if (Room->ChatRoomType == 6)
			{
				//进入3d房间
				ResponseCreateRoom(RoomClient, Room, 6);
				RequestEnter3DRoom(RoomClient);
				NotifyChangeRoomOwner(RoomClient, Room);
				for (char j = 0; j < 6; j++)
				{
					ClientNode* RoomClient2 = Room->Player[j];
					if (RoomClient2 && RoomClient2 != RoomClient)
					{
						NotifyEnterRoom(RoomClient, Room, RoomClient2, RoomClient2->SeatID);
					}
				}
			}
		}
	}

}
void WINAPI OnCountDown2(RoomNode* Room)
{
	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			
			NotifyRaceOver(RoomClient,Room);
			NotifyGenGameEndBoxAward(RoomClient);
		}
	}
	CreateRoomTimer(Room, GameOverTime, OnCountDown3);//退出结算界面
}
void WINAPI OnCountDown(RoomNode* Room)
{
	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			NotifyRaceShow(RoomClient);
		}
	}
	CreateRoomTimer(Room, 3000, OnCountDown2);//进入结算界面
	
	//CreateRoomTimer(Room, 1000, OnCountDown3);//直接退出 不结算
}

void WINAPI OnBorderCountDown2(RoomNode* Room)
{
	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			RoomClient->TaskID = 0;
			RoomClient->IsFinish = 0;
			SendToClient(RoomClient, 514, (const BYTE*)"\x00\x00\x00\x00", 4, RoomClient->GameID, FE_GAMELOGIC, RoomClient->ConnID, Notify);
			LeaveBorderRoom(RoomClient, 0);
		}
	}
}
void WINAPI OnBorderCountDown(RoomNode* Room)
{

	for (char i = 0; i < 6; i++)
	{
		ClientNode* RoomClient = Room->Player[i];
		if (RoomClient)
		{
			if (RoomClient->TaskID == 0xFFFD)
			{
				//边境结算
				BYTE* p = BorderOver;
				p += 2;
				Write32(p, RoomClient->Uin);
				Write32(p, RoomClient->FinishTime); //FinTime
				p += 4;
				Write32(p, 0); //ExpInc
				Write32(p, 0xFFFFFFFF); //TotalExp
				Write32(p, 0); //SuperMoneyInc
				Write32(p, 999999); //TotalSuperMoney
				Write32(p, 0); //PersonalHonor
				Write32(p, 0x00FFFFFF); //TotalPersonalHonor
				Write32(p, 0); //NationalHonor
				Write32(p, 0x00FFFFFF); //TotalNationalHonor
				SendToClient(RoomClient, 542, BorderOver, 187, RoomClient->ConnID, FE_PLAYER, RoomClient->ConnID, Notify);
			}
			else if (RoomClient->TaskID == 0xFFFC)
			{
				// 排位结算
				
				
				UINT GradeScoreTemp = RoomClient->GradeScore + 10;
				UINT GradeLevelTemp = RoomClient->GradeLevel;
				if (GradeScoreTemp > 125&& GradeLevelTemp<=6)//0-6级上限125分
				{
					GradeScoreTemp -= 125;//如果大于125 相减后得到最新分数 并升级Level
					RoomClient->GradeLevel++;
				}
				//7级不限分
				
				const char* sql = NULL;
				sqlite3_stmt* stmt = NULL;
				int result;
				sql = "UPDATE RankInfo SET GradeScore=?,GradeLevel=? WHERE Uin=?;";
				result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
				if (result == SQLITE_OK) {
					sqlite3_bind_int(stmt, 1, GradeScoreTemp);
					sqlite3_bind_int(stmt, 2, RoomClient->GradeLevel);
					sqlite3_bind_int(stmt, 3, RoomClient->Uin);
					result = sqlite3_step(stmt);
				}
				sqlite3_finalize(stmt);
				stmt = NULL;

				BYTE* p = RankedOver;
				p += 3;
				Write32(p, RoomClient->Uin);
				Write32(p, RoomClient->FinishTime); //FinTime
				Write32(p, 0); //TP
				Write32(p, 0); //MoneyInc
				Write32(p, 30); //TotalMoney
				Write32(p, 0xFFFFFFFF); //ExpInc
				Write32(p, 0xFFFFFFFF); //TotalExp


				p += 113;//RankedMatchLastGradeInfo
				Write32(p, RankGradeLevel[GradeLevelTemp]); //GradeLevel
				Write32(p, 1); //ChildLevel
				Write32(p, RoomClient->GradeScore); //GradeScore
				if (GradeLevelTemp <= 6)
				{
					Write32(p, 125); //MaxGradeScore
				}
				else
				{
					Write32(p, 0xFFFFFFFF); //MaxGradeScore
				}
				Write32(p, 0); //TotalScore
				p += 2; //RankedMatchGradeInfo
				Write32(p, RankGradeLevel[RoomClient->GradeLevel]); //GradeLevel
				Write32(p, 1); //ChildLevel
				Write32(p, GradeScoreTemp); //GradeScore
				if (GradeLevelTemp <= 6)
				{
					Write32(p, 125); //MaxGradeScore
				}
				else
				{
					Write32(p, 0xFFFFFFFF); //MaxGradeScore
				}
				Write32(p, 0); //TotalScore
				SendToClient(RoomClient, 513, RankedOver, 402, RoomClient->ConnID, FE_PLAYER, RoomClient->ConnID, Notify);
				NotifyRankedMatchSeasonInfo(RoomClient, RoomClient->Uin);//通知排位等级
				RoomClient->GradeScore= GradeScoreTemp;
			}
			else if (RoomClient->TaskID == 0xFFFB)
			{
				NotifyRaceOver(RoomClient, Room);
			}
			break;
		}
	}
	CreateRoomTimer(Room, 16000, OnBorderCountDown2);
}




void NotifyGameBegin(ClientNode* Client, ClientNode* Player[])
{
	char FilePath[MAX_PATH];
	
	
	ClientNode* Players[6];
	char CurrentPlayers = 0;
	if (Player)
	{
		for (char i = 0; i < 6; i++)
		{
			if (Player[i])
			{
				Players[CurrentPlayers] = Player[i];
				CurrentPlayers++;
			}
		}
	}
	else
	{
		Players[0] = Client;
		CurrentPlayers = 1;
	}
	//printf("NotifyGameBegin CurrentPlayers:%d\n", CurrentPlayers);
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	//Write32(p, 8000); //NormalLoadTime
	Write32(p, 8000); //NormalLoadTime 设置大一点防止有些模型加载不出来
	Write32(p, Client->MapID); //MapID
	//MapHash[]
	memset(p, 0, 32);
	p += 32;

	Write32(p, Client->GameID); //GameID
	Write32(p, (DWORD)time(nullptr)); //Seed

	Write8(p, CurrentPlayers);
	//m_aunRaceTrackOrders[MAX_MUCH_SEATNUMINROOM]
	int* aRaceTrackOrders = (int*)p;
	for (char i = 0; i < MAX_MUCH_SEATNUMINROOM; i++)
	{
		Write32(p, 0);
	}
	//起跑线并排的玩家
	int index[] = { 2,3,1,4,0,5 };
	for (char i = 0; i < CurrentPlayers; i++)
	{
		Set32((BYTE*)&aRaceTrackOrders[index[i]], Players[i]->Uin);
	}


	Write16(p, Client->TotalRound); //TotalMapRound
	Write32(p, 0); //PropUpdateInterval
	Write32(p, PlayerDB_GetMapRecord(Client->Uin, Client->MapID)); //Record


	Write8(p, 0); //NianShouTypeNum
	/*
m_astNianShouAwardInfo[].m_cAwardInGameType
m_astNianShouAwardInfo[].m_iActIDForClient
m_astNianShouAwardInfo[].m_cPointArrayIdx
m_astNianShouAwardInfo[].m_cCurrAwardNum
m_astNianShouAwardInfo[].m_acAwardPos[]
	*/

	Write8(p, CurrentPlayers); //SyncCarNum
	for (char i = 0; i < CurrentPlayers; i++)
	{ //SyncCar
		BYTE* pSyncCar = p;
		Write16(pSyncCar, 0); //len

		Write32(pSyncCar, Players[i]->Uin); //PlayerUin
		if (Players[i] == Client)
		{
			Write32(pSyncCar, Players[i]->KartID);
		}
		else
		{
			if (Players[i]->KartSkinID != 0)//CurCarID 这里也要查询是否有皮肤 不然对方看不见
			{
				Write32(pSyncCar, Players[i]->KartSkinID);
			}
			else
			{
				Write32(pSyncCar, Players[i]->KartID);
			}
		}
		
#ifndef ZingSpeed
		Write8(pSyncCar, 0); //HasStoneInfo
		/*
m_astSyncCar[].m_stSTKartStoneGrooveInfo[].m_iKartID
m_astSyncCar[].m_stSTKartStoneGrooveInfo[].m_iStoneGrooveNum
m_astSyncCar[].m_stSTKartStoneGrooveInfo[].m_astStoneGrooveInfo[].m_iStoneUseOccaType
m_astSyncCar[].m_stSTKartStoneGrooveInfo[].m_astStoneGrooveInfo[].m_iSkillStoneID
		*/
#endif

		len = pSyncCar - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write8(p, 10); //ReportDataFlag

	Write8(p, 0); //CheckDataNum
	/*
m_astMapCheckDiv[].m_shBeginIdx
m_astMapCheckDiv[].m_shEndIdx
	*/


	Write8(p, 0); //P2PMode
	Write8(p, 0); //TcpFrequence

	Write8(p, 50); //MultiInfoLen
	memset(p, 0, 50);
	p += 50;

	Write8(p, 0); //FeedBackEnabled

	Write8(p, 0); //SpeedSectionNum
	/*
m_au16SpeedSectionLowerBound[]
	*/

	Write8(p, 0); //NormalSpeedSectionNum
	/*
m_au16NormalSpeedSectionLowerBound[]
	*/

	Write8(p, 0); //MemCheckInfoNum
	/*
m_astMemCheckInfo[].m_u8MemIdxNum
m_astMemCheckInfo[].m_au32MemOffset[]
m_astMemCheckInfo[].m_u8DataType
m_astMemCheckInfo[].m_uPara
	*/

	Write8(p, 4); //ExtraInfoInterval
	Write16(p, -1); //OffsetThreshold
	Write32(p, 200); //SpeedRatioThreshold1
	Write32(p, 200); //SpeedRatioThreshold2
	Write32(p, 0); //HideTaskId
	Write8(p, 0); //HideTaskType
	Write32(p, 0); //HideTaskParam1

	Write8(p, 0); //ForceReportCPNum
	//m_au16ForceReportCP[]

	Write8(p, 0); //CliReserveFlag

	char EnableAntiDriftCheat = true; //反卡漂
	Write8(p, EnableAntiDriftCheat); //EnableAntiDriftCheat
	if (EnableAntiDriftCheat)
	{ //AntiDriftCheatPara
		BYTE* pAntiDriftCheatPara = p;
		Write16(pAntiDriftCheatPara, 0); //len

		Write32(pAntiDriftCheatPara, 0); //MaxDriftHistoryTime
		Write32(pAntiDriftCheatPara, 0); //MinTimeInterval
		Write32(pAntiDriftCheatPara, 0); //MaxTimeInterval
		Write32(pAntiDriftCheatPara, 220); //NormalThreshold
		Write32(pAntiDriftCheatPara, 15); //JetThreshold
		Write32(pAntiDriftCheatPara, 0); //JetInterval
		Write32(pAntiDriftCheatPara, 0); //OneSideSlidingInterval

		len = pAntiDriftCheatPara - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write8(p, 0); //HasCrashModePara
	/*
m_astCrashModePara[].m_u8SponsorSkillNum
m_astCrashModePara[].m_astSponsorSkill[].m_u8SkillID
m_astCrashModePara[].m_astSponsorSkill[].m_iPara1
m_astCrashModePara[].m_u8InitEggNum
m_astCrashModePara[].m_u8EggRefreshInterval
m_astCrashModePara[].m_u8EggRefreshNum
m_astCrashModePara[].m_u8InitN2ONum
m_astCrashModePara[].m_u8EggSourceIncNum
m_astCrashModePara[].m_u32RandSeed
m_astCrashModePara[].m_u8PropPointRatio
m_astCrashModePara[].m_u8EggPropRatio
m_astCrashModePara[].m_u8AddN2ONumOnEggLost
	*/

	Write32(p, 0); //FizzStarTaskId
	Write8(p, 0); //FizzStarTaskType
	Write32(p, 0); //FizzStarTaskParam1
	Write32(p, 0); //LDMRecordID
	Write32(p, 0); //GameSeq

#ifndef ZingSpeed
	Write8(p, 1); //PlayerNums
	{ //GameBeginPlayerInfo
		BYTE* pGameBeginPlayerInfo = p;
		Write16(pGameBeginPlayerInfo, 0); //len

		Write32(pGameBeginPlayerInfo, Client->Uin); //Uin
		Write32(pGameBeginPlayerInfo, 0); //ChumCircleID

		Write8(pGameBeginPlayerInfo, 0); //SkillNums
		/*
m_astGameBeginPlayerInfo[].m_astChumCircleSkillInfo[].m_uiSkillID
m_astGameBeginPlayerInfo[].m_astChumCircleSkillInfo[].m_uiSkillLv
		*/

		Write32(pGameBeginPlayerInfo, 0); //WorldEscapeTaskID

		{ //ProfessionLicenseInfo
			BYTE* pProfessionLicenseInfo = pGameBeginPlayerInfo;
			Write16(pProfessionLicenseInfo, 0); //len


			Write8(pProfessionLicenseInfo, 0); //BigLevel
			Write8(pProfessionLicenseInfo, 0); //SmallLevel


			len = pProfessionLicenseInfo - pGameBeginPlayerInfo;
			Set16(pGameBeginPlayerInfo, (WORD)len);
			pGameBeginPlayerInfo += len;
		}

		Write8(pGameBeginPlayerInfo, 0); //ParaNum
		/*
m_astGameBeginPlayerInfo[].m_stEffectGameBuffInfo[].m_ushBuffID
m_astGameBeginPlayerInfo[].m_stEffectGameBuffInfo[].m_uchFeatureID
m_astGameBeginPlayerInfo[].m_stEffectGameBuffInfo[].m_uchBuffLevel
m_astGameBeginPlayerInfo[].m_stEffectGameBuffInfo[].m_uchIsIcon
		*/

		Write32(pGameBeginPlayerInfo, 0); //StarsFightingStar
		Write8(pGameBeginPlayerInfo, 0); //ParaNum
		/*
m_astGameBeginPlayerInfo[].m_iParaList[]
		*/

		len = pGameBeginPlayerInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
#endif
	
	Write8(p, 0); //PlayeCheerNums
	Write8(p, 0); //MapNum
	Write32(p, 0); //SpecialMapId
	if (Client->TaskID == 0)
	{
		Write8(p, 0);//NPCNum
	}
	else
	{
		Write8(p, 5); //NPCNum
		try
		{
			YAML::Node Config = YAML::LoadFile(".\\Bot\\NPCListInfo.yml");
			size_t Num = Config.size();
			YAML::Node NPCCfg;
			for (size_t i = 0; i < Num; i++)
			{
				NPCCfg = Config[i];
				 //NPCInfo
				BYTE* pNPCInfo = p;
				Write16(pNPCInfo, 0); //len

				Write32(pNPCInfo, NPCCfg["NpcID"].as<int>()); //NpcID
				std::string RoomName = NPCCfg["RoomName"].as<std::string>();
				memset(pNPCInfo, 0, 17);
				memcpy(pNPCInfo, RoomName.c_str(),RoomName.length());
				pNPCInfo += 17;
				memset(pNPCInfo, 0, 17);//GuildName[]
				pNPCInfo += 17;
				{ //NpcItemInfo
					BYTE* pNpcItemInfo = pNPCInfo;
					Write16(pNpcItemInfo, 0); //len

					Write32(pNpcItemInfo, NPCCfg["RoleID"].as<int>()); //RoleID
					Write32(pNpcItemInfo, NPCCfg["HairID"].as<int>()); //HairID
					Write32(pNpcItemInfo, NPCCfg["FaceID"].as<int>()); //FaceID
					Write32(pNpcItemInfo, NPCCfg["GlassID"].as<int>()); //GlassID
					Write32(pNpcItemInfo, NPCCfg["CoatID"].as<int>()); //CoatID
					Write32(pNpcItemInfo, NPCCfg["GloveID"].as<int>()); //GloveID
					Write32(pNpcItemInfo, NPCCfg["TrousersID"].as<int>()); //TrousersID
					Write32(pNpcItemInfo, NPCCfg["PersonarID"].as<int>()); //PersonarID
					Write32(pNpcItemInfo, NPCCfg["TattooID"].as<int>()); //TattooID
					Write32(pNpcItemInfo, NPCCfg["WingID"].as<int>()); //WingID
					Write32(pNpcItemInfo, NPCCfg["DecoratorID"].as<int>()); //DecoratorID
					Write32(pNpcItemInfo, NPCCfg["KartID"].as<int>()); //KartID
					Write32(pNpcItemInfo, NPCCfg["ColorID"].as<int>()); //ColorID
					Write32(pNpcItemInfo, NPCCfg["TrackID"].as<int>()); //TrackID
					Write32(pNpcItemInfo, NPCCfg["EffectID"].as<int>()); //EffectID
					Write32(pNpcItemInfo, NPCCfg["BrandID"].as<int>()); //BrandID
					Write32(pNpcItemInfo, NPCCfg["TailID"].as<int>()); //TailID

					len = pNpcItemInfo - pNPCInfo;
					Set16(pNPCInfo, (WORD)len);
					pNPCInfo += len;
				}

				memcpy(pNPCInfo, "\x00\x00\x00\x00\x00\x00\x27\x10\x00\x22\x00\x00\x04\xe2\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x04\x00\x22\x00\x00\x00\x37\x00\x00\x00\x0a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00\x00\x01\x00\x01\x86\x9f\x00\x00\x00\xc8\x00\x22\x00\x00\x00\x3c\x00\x00\x00\x14\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00\x00\x01\x00\x00\x00\xc8\x00\x00\x00\x00\x00\x22\x00\x00\x00\x46\x00\x00\x00\x14\x00\x00\x00\x05\x00\x00\x00\x05\x00\x00\x00\x05\x00\x00\x00\x01\x00\x00\x00\x00\xff\xff\xff\x9c\x00\x22\x00\x00\x00\x50\x00\x00\x00\x19\x00\x00\x00\x0a\x00\x00\x00\x0a\x00\x00\x00\x05\x00\x00\x00\x01\xff\xff\xff\x9c\xff\xfe\x79\x61\x04\x00\x12\x00\x00\x00\x08\x00\x00\x00\x00\x00\x0f\x42\x36\x00\x00\x27\x0f\x00\x12\x00\x00\x00\x0a\x00\x00\x1f\x40\x00\x00\x03\xe7\x00\x00\x00\x14\x00\x12\x00\x00\x00\x01\x00\x00\x13\x88\x00\x00\x00\x14\xff\xff\xff\xec\x00\x12\x00\x00\x00\x02\x00\x00\x13\x88\xff\xff\xff\xec\xff\xff\xff\x9c", 252);
				pNPCInfo += 252;
				Write16(pNPCInfo, NPCCfg["MaxLevel"].as<int>()); //NPCAILevel
				Write16(pNPCInfo, 0); //TeamID

				len = pNPCInfo - p;
				Set16(p, (WORD)len);
				p += len;
				NPCCfg.reset();
			}
				
		}
		catch (const std::exception&)
		{
			return;
		}
		//int NPCKartID[5] = {127616,127365,123501 ,118729,110710 };
		//const char* NpcName[5] = {"陈伯\x0\x0","关佳鑫","胡旭\x0\x0","江章闯","张云彬"};
	//NPC配置 //NotifyGameNPCInfo(ClientNode* Client)
	//memcpy(p, "\x01\x6e\x00\x00\x00\x01\xc9\xe7\xbb\xe1\xc3\xc0\xd1\xf2\xd1\xf2\x00\x00\x00\x00\x00\x00\x0a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x46\x00\x00\x27\x22\x00\x00\x00\x00\x00\x00\x59\x02\x00\x00\x00\x00\x00\x01\x88\x84\x00\x00\x27\x30\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\xe7\x07\x00\x00\x27\x2d\x00\x00\x27\x75\x00\x00\x27\x73\x00\x00\x28\x08\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x27\x10\x00\x22\x00\x00\x04\xe2\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x04\x00\x22\x00\x00\x00\x37\x00\x00\x00\x0a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00\x00\x01\x00\x01\x86\x9f\x00\x00\x00\xc8\x00\x22\x00\x00\x00\x3c\x00\x00\x00\x14\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00\x00\x01\x00\x00\x00\xc8\x00\x00\x00\x00\x00\x22\x00\x00\x00\x46\x00\x00\x00\x14\x00\x00\x00\x05\x00\x00\x00\x05\x00\x00\x00\x05\x00\x00\x00\x01\x00\x00\x00\x00\xff\xff\xff\x9c\x00\x22\x00\x00\x00\x50\x00\x00\x00\x19\x00\x00\x00\x0a\x00\x00\x00\x0a\x00\x00\x00\x05\x00\x00\x00\x01\xff\xff\xff\x9c\xff\xfe\x79\x61\x04\x00\x12\x00\x00\x00\x08\x00\x00\x00\x00\x00\x0f\x42\x36\x00\x00\x27\x0f\x00\x12\x00\x00\x00\x0a\x00\x00\x1f\x40\x00\x00\x03\xe7\x00\x00\x00\x14\x00\x12\x00\x00\x00\x01\x00\x00\x13\x88\x00\x00\x00\x14\xff\xff\xff\xec\x00\x12\x00\x00\x00\x02\x00\x00\x13\x88\xff\xff\xff\xec\xff\xff\xff\x9c\x00\x09\x00\x00", 366);
	//p += 366;
		
	}
	//npc数据
	//"\x05\x01\x6e\x00\x00\x00\x01\xcd\xe1\xb1\xf3\xc7\xfa\xcc\xab\xe0\xcb\x00\x00\x00\x00\x00\x00\x0a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x46\x00\x00\x27\x26\x00\x00\x2c\x63\x00\x01\xfe\x89\x00\x00\x00\x00\x00\x01\xf0\xbf\x00\x00\x27\x30\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\xf2\x80\x00\x00\x27\x2d\x00\x00\x27\x75\x00\x00\x27\x73\x00\x00\x28\x08\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x27\x10\x00\x22\x00\x00\x04\xe2\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x04\x00\x22\x00\x00\x00\x37\x00\x00\x00\x0a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00\x00\x01\x00\x01\x86\x9f\x00\x00\x00\xc8\x00\x22\x00\x00\x00\x3c\x00\x00\x00\x14\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00\x00\x01\x00\x00\x00\xc8\x00\x00\x00\x00\x00\x22\x00\x00\x00\x46\x00\x00\x00\x14\x00\x00\x00\x05\x00\x00\x00\x05\x00\x00\x00\x05\x00\x00\x00\x01\x00\x00\x00\x00\xff\xff\xff\x9c\x00\x22\x00\x00\x00\x50\x00\x00\x00\x19\x00\x00\x00\x0a\x00\x00\x00\x0a\x00\x00\x00\x05\x00\x00\x00\x01\xff\xff\xff\x9c\xff\xfe\x79\x61\x04\x00\x12\x00\x00\x00\x08\x00\x00\x00\x00\x00\x0f\x42\x36\x00\x00\x27\x0f\x00\x12\x00\x00\x00\x0a\x00\x00\x1f\x40\x00\x00\x03\xe7\x00\x00\x00\x14\x00\x12\x00\x00\x00\x01\x00\x00\x13\x88\x00\x00\x00\x14\xff\xff\xff\xec\x00\x12\x00\x00\x00\x02\x00\x00\x13\x88\xff\xff\xff\xec\xff\xff\xff\x9c\x00\x0a\x00\x00\x01\x6e\x00\x00\x00\x02\xd0\xa1\xe9\xd9\xd7\xd3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x06\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x46\x00\x00\x27\x22\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\xe6\x6b\x00\x00\x27\x30\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x88\x23\x00\x00\x27\x2d\x00\x00\x27\x75\x00\x00\x27\x73\x00\x00\x28\x08\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x27\x10\x00\x22\x00\x00\x04\xe2\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x04\x00\x22\x00\x00\x00\x37\x00\x00\x00\x0a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00\x00\x01\x00\x01\x86\x9f\x00\x00\x00\xc8\x00\x22\x00\x00\x00\x3c\x00\x00\x00\x14\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00\x00\x01\x00\x00\x00\xc8\x00\x00\x00\x00\x00\x22\x00\x00\x00\x46\x00\x00\x00\x14\x00\x00\x00\x05\x00\x00\x00\x05\x00\x00\x00\x05\x00\x00\x00\x01\x00\x00\x00\x00\xff\xff\xff\x9c\x00\x22\x00\x00\x00\x50\x00\x00\x00\x19\x00\x00\x00\x0a\x00\x00\x00\x0a\x00\x00\x00\x05\x00\x00\x00\x01\xff\xff\xff\x9c\xff\xfe\x79\x61\x04\x00\x12\x00\x00\x00\x08\x00\x00\x00\x00\x00\x0f\x42\x36\x00\x00\x27\x0f\x00\x12\x00\x00\x00\x0a\x00\x00\x1f\x40\x00\x00\x03\xe7\x00\x00\x00\x14\x00\x12\x00\x00\x00\x01\x00\x00\x13\x88\x00\x00\x00\x14\xff\xff\xff\xec\x00\x12\x00\x00\x00\x02\x00\x00\x13\x88\xff\xff\xff\xec\xff\xff\xff\x9c\x00\x0a\x00\x00\x01\x6e\x00\x00\x00\x03\xcd\xe1\xb1\xf3\xc7\xfa\xcc\xab\xe0\xcb\x00\x00\x00\x00\x00\x00\x0a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x46\x00\x00\x27\x26\x00\x00\x2c\x63\x00\x01\xfe\x89\x00\x00\x00\x00\x00\x01\xf0\xbf\x00\x00\x27\x30\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\xf2\x80\x00\x00\x27\x2d\x00\x00\x27\x75\x00\x00\x27\x73\x00\x00\x28\x08\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x27\x10\x00\x22\x00\x00\x04\xe2\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x04\x00\x22\x00\x00\x00\x37\x00\x00\x00\x0a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00\x00\x01\x00\x01\x86\x9f\x00\x00\x00\xc8\x00\x22\x00\x00\x00\x3c\x00\x00\x00\x14\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00\x00\x01\x00\x00\x00\xc8\x00\x00\x00\x00\x00\x22\x00\x00\x00\x46\x00\x00\x00\x14\x00\x00\x00\x05\x00\x00\x00\x05\x00\x00\x00\x05\x00\x00\x00\x01\x00\x00\x00\x00\xff\xff\xff\x9c\x00\x22\x00\x00\x00\x50\x00\x00\x00\x19\x00\x00\x00\x0a\x00\x00\x00\x0a\x00\x00\x00\x05\x00\x00\x00\x01\xff\xff\xff\x9c\xff\xfe\x79\x61\x04\x00\x12\x00\x00\x00\x08\x00\x00\x00\x00\x00\x0f\x42\x36\x00\x00\x27\x0f\x00\x12\x00\x00\x00\x0a\x00\x00\x1f\x40\x00\x00\x03\xe7\x00\x00\x00\x14\x00\x12\x00\x00\x00\x01\x00\x00\x13\x88\x00\x00\x00\x14\xff\xff\xff\xec\x00\x12\x00\x00\x00\x02\x00\x00\x13\x88\xff\xff\xff\xec\xff\xff\xff\x9c\x00\x08\x00\x00\x01\x6e\x00\x00\x00\x04\xc2\xed\xc5\xa3\xb1\xc6\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x06\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x46\x00\x00\x27\x26\x00\x00\x00\x00\x00\x00\x5a\x00\x00\x00\x00\x00\x00\x01\xd2\x03\x00\x00\x27\x30\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\xf1\xcd\x00\x00\x27\x2d\x00\x00\x27\x75\x00\x00\x27\x73\x00\x00\x28\x08\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x27\x10\x00\x22\x00\x00\x04\xe2\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x04\x00\x22\x00\x00\x00\x37\x00\x00\x00\x0a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00\x00\x01\x00\x01\x86\x9f\x00\x00\x00\xc8\x00\x22\x00\x00\x00\x3c\x00\x00\x00\x14\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00\x00\x01\x00\x00\x00\xc8\x00\x00\x00\x00\x00\x22\x00\x00\x00\x46\x00\x00\x00\x14\x00\x00\x00\x05\x00\x00\x00\x05\x00\x00\x00\x05\x00\x00\x00\x01\x00\x00\x00\x00\xff\xff\xff\x9c\x00\x22\x00\x00\x00\x50\x00\x00\x00\x19\x00\x00\x00\x0a\x00\x00\x00\x0a\x00\x00\x00\x05\x00\x00\x00\x01\xff\xff\xff\x9c\xff\xfe\x79\x61\x04\x00\x12\x00\x00\x00\x08\x00\x00\x00\x00\x00\x0f\x42\x36\x00\x00\x27\x0f\x00\x12\x00\x00\x00\x0a\x00\x00\x1f\x40\x00\x00\x03\xe7\x00\x00\x00\x14\x00\x12\x00\x00\x00\x01\x00\x00\x13\x88\x00\x00\x00\x14\xff\xff\xff\xec\x00\x12\x00\x00\x00\x02\x00\x00\x13\x88\xff\xff\xff\xec\xff\xff\xff\x9c\x00\x0a\x00\x00\x01\x6e\x00\x00\x00\x05\x57\x6f\x6c\x76\x65\x73\x2e\x4e\x69\x6e\x67\x51\x69\x6e\x67\x00\x0f\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x46\x00\x00\x27\x26\x00\x00\x00\x00\x00\x01\xfe\x89\x00\x00\x00\x00\x00\x01\xcb\xdf\x00\x00\x27\x30\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xf7\xc5\x00\x00\x27\x2d\x00\x00\x27\x75\x00\x00\x27\x73\x00\x00\x28\x08\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x27\x10\x00\x22\x00\x00\x04\xe2\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x00\x00\x03\xe8\x00\x00\x02\x58\x04\x00\x22\x00\x00\x00\x37\x00\x00\x00\x0a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00\x00\x01\x00\x01\x86\x9f\x00\x00\x00\xc8\x00\x22\x00\x00\x00\x3c\x00\x00\x00\x14\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00\x00\x01\x00\x00\x00\xc8\x00\x00\x00\x00\x00\x22\x00\x00\x00\x46\x00\x00\x00\x14\x00\x00\x00\x05\x00\x00\x00\x05\x00\x00\x00\x05\x00\x00\x00\x01\x00\x00\x00\x00\xff\xff\xff\x9c\x00\x22\x00\x00\x00\x50\x00\x00\x00\x19\x00\x00\x00\x0a\x00\x00\x00\x0a\x00\x00\x00\x05\x00\x00\x00\x01\xff\xff\xff\x9c\xff\xfe\x79\x61\x04\x00\x12\x00\x00\x00\x08\x00\x00\x00\x00\x00\x0f\x42\x36\x00\x00\x27\x0f\x00\x12\x00\x00\x00\x0a\x00\x00\x1f\x40\x00\x00\x03\xe7\x00\x00\x00\x14\x00\x12\x00\x00\x00\x01\x00\x00\x13\x88\x00\x00\x00\x14\xff\xff\xff\xec\x00\x12\x00\x00\x00\x02\x00\x00\x13\x88\xff\xff\xff\xec\xff\xff\xff\x9c\x00\x09\x00\x00";
	Write8(p, 0); //MapNum
	int* aNPCRaceTrackOrders = (int*)p;
	for (size_t i = 0; i < MAXNPCNUMINROOM; i++)
	{
		//m_aunNPCTrackOrders[]
		Write32(p, 0);
	}
	//起跑线并排的机器人
	//int npcindex[] = { 2,3,1,4,0 };
	if (Client->TaskID != 0)
	{
		for (char i = 0; i < 5; i++)
		{
			Set32((BYTE*)&aNPCRaceTrackOrders[i], i + 1);
		}
	}
	
	//修复复位无敌2秒+机甲等动作
	const char* buf1 = "\x00\x00\x00\x00\x01\x24\xb1\x7e\xaf\x2a\x78\xa6\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0a\x00\x0b\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0f\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x37\x00\x00\x02\x00\x19\x00\x00\x05\x00\x00\x02\x58\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\x0b\xb8\x00\x19\x00\x00\x05\x00\x00\x01\x2c\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x03\xe8\x00\x00\x03\xe8\x00\x3b\x00\x01\x02\x00\x19\x00\x01\x05\x00\x00\x00\x00\x00\x00\x00\x32\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x1d\x00\x01\x06\x00\x00\x00\x00\x00\x00\x9c\x40\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\x27\x10\x00\x00\x00\x00\x00\x0a\x00\x00\x01\x00\x05\x00\x02\x00\x00\x00\x07\xb3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
	//const char* buf1 = "\x00\x00\x00\x00\x01\x24\xb1\x7e\xaf\x2a\x78\xa6\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0a\x00\x0b\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0f\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x37\x00\x00\x02\x00\x19\x00\x00\x05\x00\x00\x02\x58\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\x0b\xb8\x00\x19\x00\x00\x05\x00\x00\x01\x2c\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x03\xe8\x00\x00\x03\xe8\x00\x3b\x00\x01\x02\x00\x19\x00\x01\x05\x00\x00\x00\x00\x00\x00\x00\x32\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x1d\x00\x01\x06\x00\x00\x00\x00\x00\x00\x9c\x40\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\x27\x10\x00\x00\x00\x00\x00\x0a\x00\x00\x01\x00\x05\x00\x02\x00\x00\x00\x07\xb3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
	memcpy(p, buf1, 236);
	p += 236;

	len = p - buf;
	SendToClient(Client, 509, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
}

void NotifyKartPhysParam(ClientNode* Client, ClientNode* Player[])
{
	ClientNode* Players[6];
	char CurrentPlayers = 0;
	if (Player)
	{
		for (char i = 0; i < 6; i++)
		{
			if (Player[i])
			{
				Players[CurrentPlayers] = Player[i];
				CurrentPlayers++;
			}
		}
	}
	else
	{
		Players[0] = Client;
		CurrentPlayers = 1;
	}
	

	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write16(p, CurrentPlayers); //KartNum
	for (char i = 0; i < CurrentPlayers; i++)
	{ //KartPhysParam
		try
		{
			WriteKartPhysParam(p, Players[i]->Uin, Players[i]->KartID, Players[i]);
		}
		catch (const std::exception&)
		{
			return;
		}
		
	}

	Write16(p, 0xFFFF); //SuperN2ORate
	
	len = p - buf;
	SendToClient(Client, 551, buf, len, Client->GameID, FE_PLAYER, Client->ConnID, Notify);
}

void RequestPrepareReady(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);
#ifndef ZingSpeed
	//int MapID = Read32(Body);
	//char MapHash[32] = ReadString(Body);
	//UCHAR SingleGameRestartFlag = Read8(Body);
#endif
	
	Client->IsReady = TRUE;
	Client->IsFinish = FALSE;
	
	//等待所有人准备 并比较最大超时时间
	//RoomNode* Room = GetRoom(Client->RoomID);
	//if (!Room)
	//{
	//	return;
	//}
}

void NotifyRaceBegin(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, 9000); //CountDownTime
	Write16(p, 0); //DelayTime
#ifndef ZingSpeed
	Write8(p, 0); //StageIndex
	Write32(p, 0); //RaceCountDownTime
	Write32(p, 0); //RaceCountDownDis
	Write8(p, 0); //UseNewCountDownTime
	Write32(p, 0); //NewCountDownTime
	Write32(p, 0); //ServerSecond
	Write32(p, 0); //ServerMicroSecond
#endif

	len = p - buf;
	SendToClient(Client, 511, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
}

void NotifyPlayerFinishRace(ClientNode* Client, UINT Uin,bool NewRecord, int FinTime)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Uin); //Uin
	Write8(p, NewRecord); //NewRecord
	Write32(p, FinTime); //FinTime

	len = p - buf;
	SendToClient(Client, 522, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
}



/*DWORD WINAPI OnSingleOver(PVOID Client)
{
	ClientNode* PClient = ((ClientNode*)Client);
	if (PClient->TaskID == 0xFFFE)
	{
		SendToClient(PClient, 24238, (const BYTE*)"\x00\x00\x27\x11\x00\x00\x00\x05\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x1e\x00\x00\x00\x00\x00\x00\x00\x0b\x00\x00\x00\x00\x00\x00\x00\x21\x00\x00\x00\x00\x00\x00\x00\x21\x00\x00\x00\x00\x00\x00", 72, PClient->ConnID, FE_PLAYER, PClient->ConnID, Notify);
		//Sleep(2000);//休眠2s注意后面验证空指针
		SendToClient(PClient, 514, (const BYTE*)"\x00\x00\x00\x00", 4, PClient->GameID, FE_GAMELOGIC, PClient->ConnID, Notify);
	}
	else if (PClient->TaskID == 0xFFFF )
	{
		const char* buf6 = "\x00\x00\x00\x05\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x52\x00\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x1a\x60\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x2c\x00\x00\x27\x11\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x1a\x60\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\x00\x00\x00\x00\x00\x00\x50\x75";
		SendToClient(PClient, 24255, (const BYTE*)buf6, 161, PClient->ConnID, FE_PLAYER, PClient->ConnID, Notify);
		//Sleep(2000);
		SendToClient(PClient, 514, (const BYTE*)"\x00\x00\x00\x00\x00\x00\x00\x00", 8, PClient->GameID, FE_GAMELOGIC, PClient->ConnID, Notify);
		const char* buf7 = "\x00\x00\x00\x01\x00\x2e\x00\x01\x06\x00\xb4\xf3\xbc\xd2\xd2\xbb\xc6\xf0\xcc\xf4\xd5\xbd\xbc\xab\xcf\xde\xa3\xa1\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x70\x64\x1c\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0a\x00\x08\x47\x7e\x1d\x00\x00\x00\x00\x01\x00\x11\x00\x00\x00\x00\x00\x04\x01\x01\x00\x08\x11\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x0f\x24\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x0f\x24\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x17\x31\x2d\x31\x38\x37\x32\x34\x37\x33\x37\x36\x37\x2d\x31\x36\x38\x35\x30\x38\x37\x32\x36\x30\x00\x00\x00\x00\x00\x00\x00\x00\x00\x72\x69";
		SendToClient(PClient, 103, (BYTE*)buf7, 207, PClient->ServerID, FE_GAMESVRD, PClient->ConnID, Response);
	}
	PClient->TaskID = 0;
	PClient->IsFinish = FALSE;
	LeaveRoom(PClient, 0);
	return 0;
}*/

/*DWORD WINAPI OnSingleJump(PVOID Client)
{
	ClientNode* PClient = ((ClientNode*)Client);
	while (1)
	{
		Sleep(30000);//模拟30秒跳一次
		if (PClient->TaskID == 0xFFFE && PClient->IsLogin)
		{
			BYTE* p = jump24238;
			Write32(p, PClient->Uin);
			SendToClient(PClient, 24238, jump24238, 91, PClient->ConnID, FE_PLAYER, PClient->ConnID, Notify);

		}
		if (PClient->TaskID == 0xFFFF && PClient->IsLogin)
		{
			//跳关
			SendToClient(PClient, 24255, jump24255, 91, PClient->ConnID, FE_PLAYER, PClient->ConnID, Notify);
		}
		if (PClient->TaskID == 0 || PClient->IsLogin == FALSE)
		{
			return 0;
		}
		
	}
}*/

void RequestReportCurrentInfo(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	//UINT Uin = Read32(Body);
	//UINT Time = Read32(Body);
	//printf("Uin:%d\n", Uin);
	//UINT CurrentState = Read32(Body);
	
	//m_aiCurrentPosition[3]
	//DWORD a=Read32(Body);
	//DWORD b = Read32(Body);
	//DWORD c = Read32(Body);
	Body+=24;
	
	//fflush(stdout);
	BOOL IsFinish = FALSE;
	BYTE PassedCheckPointNum = Read8(Body);
	//printf("PassedCheckPointNum:%d\n", PassedCheckPointNum);
	for (size_t i = 0; i < PassedCheckPointNum; i++)
	{
		WORD PassedCheckPointID = Read16(Body);
		//printf("当前圈数:%d 通过地图检查点:%d\n", Client->Round,PassedCheckPointID);
		//fflush(stdout);
		/*if (Client->Loop)
		{
			if (Client->EndCheckPoint != 0 && PassedCheckPointID > Client->EndCheckPoint) //大于终点的则可能在走近道
			{
				//printf("continue\t");
				continue;
			}
			if (PassedCheckPointID == 0 && Client->PassedCheckPoint > 4)
			{
				Client->Round++;
				
				if (Client->Round >= Client->TotalRound)
				{
					IsFinish = TRUE;
				}
			}
			else if (Client->PassedCheckPoint == 0 && PassedCheckPointID > 4)
			{
				Client->Round--;
			}
		}
		else
		{
			if (PassedCheckPointID == Client->EndCheckPoint)
			{
				Client->Round++;
				if (Client->Round >= Client->TotalRound)
				{
					IsFinish = TRUE;
				}
			}
		}
		Client->PassedCheckPoint = PassedCheckPointID;
		*/
	}
	
	UINT LapTime = Read32(Body);

	BYTE AccVerifyDataNum = Read8(Body);
	for (size_t i = 0; i < AccVerifyDataNum; i++)
	{
		/*
m_astAccelVerifyData[].m_unType
m_astAccelVerifyData[].m_ushTotalCount
m_astAccelVerifyData[].m_unMaxDurTime
m_astAccelVerifyData[].m_ushOverlayCount
		*/
		Body += Get16(Body);
	}

	BYTE MsgSequence = Read8(Body);


	BYTE ExtraDataNum = Read8(Body);
	for (size_t i = 0; i < ExtraDataNum; i++)
	{
		/*
m_astExtraData[].stSkillStoneTriggerData.m_uTriggerTotalCount
m_astExtraData[].stSkillStoneTriggerData.m_uCheckData1
m_astExtraData[].stSkillStoneTriggerData.m_uCheckData2
m_astExtraData[].m_stClientReportSelfErr.m_iRemoveFailedCount
m_astExtraData[].m_stClientReportSelfErr.m_iNo2CheckErrCount
m_astExtraData[].m_stClientReportSelfErr.m_iFrictionCheckErrCount
m_astExtraData[].m_stClientReportSelfErr.m_iGPTargetCheckErrCount
m_astExtraData[].m_stClientReportSelfErr.m_iPowerCheckErrCount
m_astExtraData[].m_stClientReportSelfErr.m_iStoneCheckErrCount
m_astExtraData[].m_stClientReportSelfErr.m_iHashCheckErrCount
m_astExtraData[].m_stClientReportSelfErr.m_iTencentCarCheckErrCount
m_astExtraData[].m_stClientReportSelfErr.m_iUseIlleagleNo2Count
m_astExtraData[].m_stClientReportSelfErr.m_iListAffectGPsCheckErrCount
m_astExtraData[].m_stClientReportSelfErr.m_iGPTargetInvalidErrCount
m_astExtraData[].m_stClientReportSelfErr.m_aiErrData[ENMCRET_MAX]
m_astExtraData[].m_stClientReportSeflTag.m_iPowerCheckTag
m_astExtraData[].m_stClientReportSeflTag.m_iNo2CheckTag
m_astExtraData[].m_stClientReportSeflTag.m_iTencentCarCheckTag
m_astExtraData[].m_stClientReportSeflTag.m_iGPTargetInvalidCheckTag
m_astExtraData[].m_u32JetCombinationFlag
m_astExtraData[].m_unMaxSpeed
m_astExtraData[].m_u32CollisionNumOnLastCheckPoint
m_astExtraData[].m_uiTotalDrift
m_astExtraData[].m_bySpeedSectionNum
m_astExtraData[].m_auSpeedSectionAccTime[]
m_astExtraData[].m_byNormalSpeedSectionNum
m_astExtraData[].m_auNormalSpeedSectionAccTime[]
m_astExtraData[].m_u8MemCheckResultNum
m_astExtraData[].m_au32MemData[]
m_astExtraData[].m_auClientCheckErr[ECCET_MAX]
m_astExtraData[].m_auClientCheckErrTag[ECCETT_MAX]
m_astExtraData[].m_u8UpdateCount
m_astExtraData[].m_u8OffsetOverThresholdCount
m_astExtraData[].m_u32OffsetOverThresholdSum
m_astExtraData[].m_u16MaxOffsetSpeed
m_astExtraData[].m_u16AvgOffsetSpeed
m_astExtraData[].m_u16MaxRealSpeed
m_astExtraData[].m_u16AvgRealSpeed
m_astExtraData[].m_u32MaxSpeedRatio
m_astExtraData[].m_u16SpeedRatioOverThresholdCount
m_astExtraData[].m_u32MaxSpeedRatio2
m_astExtraData[].m_u16SpeedRatioOverThresholdCount2
m_astExtraData[].m_u32FBSkillRebornTime
m_astExtraData[].m_u32FBSkillChargeTime
m_astExtraData[].m_uiTotalPerpetualNight
m_astExtraData[].m_iRPCSFlag
m_astExtraData[].m_u32CollisionPlayerNum
m_astExtraData[].m_u32CollisionNumOnPlayer
m_astExtraData[].m_iCodeItegrity
m_astExtraData[].m_iSendLaPkg
m_astExtraData[].m_iSendDataToSvr
m_astExtraData[].m_aiAbnormalData[4]
m_astExtraData[].m_stLevelInfo.m_cLowFPSRatio
m_astExtraData[].m_stLevelInfo.m_cAveFPS
m_astExtraData[].m_stLevelInfo.m_iMemUsed
m_astExtraData[].m_stLevelInfo.m_iVMemUsed
m_astExtraData[].m_stLevelInfo.m_iGameSetting
m_astExtraData[].m_uiPositionErrorCount
m_astExtraData[].m_uiDropToDeathSurfaceNums
m_astExtraData[].m_uiCollideNumsInN2OStat
m_astExtraData[].m_uiBeyondPlayerNums
		*/
		Body += Get16(Body);
	}

	BYTE N2OChangeEventNum = Read8(Body);
	for (size_t i = 0; i < N2OChangeEventNum; i++)
	{
		/*
m_astN2OChangeEvent[].m_u16EventID
m_astN2OChangeEvent[].m_u32BeginLapTime
m_astN2OChangeEvent[].m_u16LastingTime
m_astN2OChangeEvent[].m_u8EventType
m_astN2OChangeEvent[].m_i16N2OChange
		*/
		Body += Get16(Body);
	}

	UINT Flag = Read32(Body);
	
#ifndef ZingSpeed
	BYTE HasCrashModeData = Read8(Body);
	if (HasCrashModeData)
	{
		//m_astCrashModeData[].m_u8CurEggNum
		Body += Get16(Body);
	}

	BYTE HasPointChallengeData = Read8(Body);
	if (HasPointChallengeData)
	{
		/*
m_astPointChallengeData[].m_uiEatCoin
m_astPointChallengeData[].m_uiBeforeTime
m_astPointChallengeData[].m_uiBeforeLong
m_astPointChallengeData[].m_uiCollectN2
m_astPointChallengeData[].m_uiShuangpen
m_astPointChallengeData[].m_uiKongpen
m_astPointChallengeData[].m_uiLuodipen
m_astPointChallengeData[].m_uiNPCRunAfterTime
m_astPointChallengeData[].m_uiLeiYinCrazyJet
		*/
		Body += Get16(Body);
	}

	UINT SkateCoinNum = Read32(Body);
	for (size_t i = 0; i < SkateCoinNum; i++)
	{
		/*
m_astSkateCoinData[].m_uiCoinID
m_astSkateCoinData[].m_uiPlayerPosX
m_astSkateCoinData[].m_uiPlayerPosY
m_astSkateCoinData[].m_uiPlayerPosZ
m_u32SkateComboAwardCoinNum
m_astSkateComboAwardCoinData[].m_ushComboNum
m_astSkateComboAwardCoinData[].m_ushCoinNum
		*/
		Body += Get16(Body);
	}


	UINT SkateComboAwardCoinNum = Read32(Body);
	for (size_t i = 0; i < SkateComboAwardCoinNum; i++)
	{
		/*
m_astSkateComboAwardCoinData[].m_ushComboNum
m_astSkateComboAwardCoinData[].m_ushCoinNum
		*/
		Body += Get16(Body);
	}

	UINT SkateDoubleJumpCount = Read32(Body);
	UINT CurrMapID = Read32(Body);


	BYTE HasGameDetailRecord = Read8(Body);
	if (HasGameDetailRecord)
	{
		/*
m_astGameDetailRecord[].m_uiUin
m_astGameDetailRecord[].m_szNickName[17]
m_astGameDetailRecord[].m_iKartId
m_astGameDetailRecord[].m_unFinTime
m_astGameDetailRecord[].m_uiHighestSpeed
m_astGameDetailRecord[].m_uiAverageSpeed
m_astGameDetailRecord[].m_uiCollisionCount
m_astGameDetailRecord[].m_uiN2OGatherCount
m_astGameDetailRecord[].m_uiJetTime
m_astGameDetailRecord[].m_uiChaoJiQiBu
m_astGameDetailRecord[].m_uiZhuangQiangDianPen
m_astGameDetailRecord[].m_uiDriftCount
m_astGameDetailRecord[].m_uiSmallJetCount
m_astGameDetailRecord[].m_uiDoubleJetCount
m_astGameDetailRecord[].m_uiFlyJetCount
m_astGameDetailRecord[].m_uiFallJetCount
m_astGameDetailRecord[].m_uiDuanWeiQiBu
m_astGameDetailRecord[].m_uiDuanWeiDoubleJetCount
m_astGameDetailRecord[].m_uiLinkJetCount
m_astGameDetailRecord[].m_uiWCJetCount
m_astGameDetailRecord[].m_uiCeShenDriftCount
m_astGameDetailRecord[].m_uiShuaiWeiDriftCount
m_astGameDetailRecord[].m_uiCWWJetCount
m_astGameDetailRecord[].m_uiXiaoGuaCount
m_astGameDetailRecord[].m_teamID
m_astGameDetailRecord[].m_uiFastCornersNum
m_astGameDetailRecord[].m_ushDiffCornerNum
m_astGameDetailRecord[].m_uiFastCornerDetailInfo[]
m_astGameDetailRecord[].m_usWSingleJetCount
m_astGameDetailRecord[].m_usWCWJetCount
m_astGameDetailRecord[].m_usCWWJetCount
m_astGameDetailRecord[].m_ushCeShenJetCount
m_astGameDetailRecord[].m_ushShuaiWeiJetCount
m_astGameDetailRecord[].m_shRankedMatchGrade
m_astGameDetailRecord[].m_ushDuanWeiPiaoYi
m_astGameDetailRecord[].m_ushDuanWeiJet
m_astGameDetailRecord[].m_ushOutOfTurnQuickly
m_astGameDetailRecord[].m_ushLaunch
m_astGameDetailRecord[].m_ushHitWaterDrift
m_astGameDetailRecord[].m_ushOutWaterJet
m_astGameDetailRecord[].m_ushN2DriftContinue
m_astGameDetailRecord[].m_ushWaveFlyJet
m_astGameDetailRecord[].m_ushWorldID
m_astGameDetailRecord[].m_uchNpc
m_astGameDetailRecord[].m_uiGameSeq
m_astGameDetailRecord[].m_uiTime
		*/
		Body += Get16(Body);
	}


	BYTE CurrentInfoFlag = Read8(Body);
	UINT TotalAccelerateFuel = Read32(Body);
	UINT DstNPCID = Read32(Body);
	UINT DistanceToEnd = Read32(Body);
	if (DstNPCID != 0)
	{
		return;//防止人机提前完成
	}
	if (DistanceToEnd != 0)
	{
		//全部通过距离计算 防止终点不红
		//printf("DistanceToEnd:%d\n", DistanceToEnd);
		IsFinish = FALSE;
	}
	else
	{
		IsFinish = TRUE;
	}
	//UINT GansterProcess = Read32(Body);
	//UINT TotalGangsterPKCount = Read32(Body);
	//printf("距离终点还剩:%d\n", DistanceToEnd);

	//BYTE HasTowerChallengeData = Read8(Body);
	//if (HasTowerChallengeData)
	//{
		/*
m_astTowerChallengeData[].m_uiEatCoin
m_astTowerChallengeData[].m_uiCollisionCount
m_astTowerChallengeData[].m_uiDriftCount
m_astTowerChallengeData[].m_cKartStatus
m_astTowerChallengeData[].m_cTrackElementNum
m_astTowerChallengeData[].m_astTriggerInfo[].m_cType
m_astTowerChallengeData[].m_astTriggerInfo[].m_cInitCheckPoint
m_astTowerChallengeData[].m_astTriggerInfo[].m_cPlayerTriggerCheckPoint
		*/
	//	Body += Get16(Body);
	//}

	//BYTE CurrentSelfRank = Read8(Body);
	//BYTE CurrentTeammateRank = Read8(Body);


	//BYTE HasP2PStatusData = Read8(Body);
	//if (HasP2PStatusData)
	//{
		/*
m_astP2PStatusData[].m_uiUin
m_astP2PStatusData[].m_ucServerUDPLoginStaus
m_astP2PStatusData[].m_ucPlayerNum
m_astP2PStatusData[].m_astP2PStatus2Player[].m_uiUin
m_astP2PStatusData[].m_astP2PStatus2Player[].m_ucP2PConnectState
m_astP2PStatusData[].m_astP2PStatus2Player[].m_ucP2PCanPass
m_astP2PStatusData[].m_astP2PStatus2Player[].m_uiP2PNetSpeed
m_astP2PStatusData[].m_astP2PStatus2Player[].m_uiNetSpeed
m_astP2PStatusData[].m_astP2PStatus2Player[].m_uiNotPassStateCount
m_astP2PStatusData[].m_astP2PStatus2Player[].m_uiSendDataCount[ENMSDM_MAX]
m_astP2PStatusData[].m_astP2PStatus2Player[].m_uiRecvDataCount[ENMSDM_MAX]
m_astP2PStatusData[].m_astP2PStatus2Player[].m_uiServerRecvDataCount[ENMSDM_MAX]
m_astP2PStatusData[].m_astP2PStatus2Player[].m_ushRecvPkgCount
m_astP2PStatusData[].m_astP2PStatus2Player[].m_astRecvPkgInfo[].m_uiPkgID
m_astP2PStatusData[].m_astP2PStatus2Player[].m_astRecvPkgInfo[].m_uiRecvTime
m_astP2PStatusData[].m_astP2PStatus2Player[].m_astRecvPkgInfo[].m_uiDistanceDiff
m_astP2PStatusData[].m_astP2PStatus2Player[].m_uchDetailCount
m_astP2PStatusData[].m_astP2PStatus2Player[].m_astDetailInfo[].m_ucType
m_astP2PStatusData[].m_astP2PStatus2Player[].m_astDetailInfo[].m_uiMsgID
m_astP2PStatusData[].m_astP2PStatus2Player[].m_astDetailInfo[].m_uiCount
m_astP2PStatusData[].m_ushSendPkgCount
m_astP2PStatusData[].m_astSendPkgInfo[].m_uiPkgID
m_astP2PStatusData[].m_astSendPkgInfo[].m_uiSendTime
m_astP2PStatusData[].m_astSendPkgInfo[].m_uchUDPStatus
m_astP2PStatusData[].m_astSendPkgInfo[].m_uchSendDataMethod
m_astP2PStatusData[].m_uiRaceBeginTime
m_astP2PStatusData[].m_uiLagCnt
m_astP2PStatusData[].m_uiLagCntGlobal
m_astP2PStatusData[].m_uiTickInLevel
		*/
	//	Body += Get16(Body);
	//}

	//UINT DistanceToFirstRacer = Read32(Body);
	//UINT TimerChallengeRecoverNum = Read32(Body);
	//UINT CoinNum = Read32(Body);

	//BYTE ClientPlayerNum = Read8(Body);
	//for (size_t i = 0; i < ClientPlayerNum; i++)
	//{
		/*
m_astClientGameInfo[].m_uiUin
m_astClientGameInfo[].m_uchDistanceNum
m_astClientGameInfo[].m_astDistanceToEndInfo[].m_uiTimeFromRaceBegin
m_astClientGameInfo[].m_astDistanceToEndInfo[].m_uiDistanceToEnd
m_astClientGameInfo[].m_uchCollisionNum
m_astClientGameInfo[].m_astClientCollisionInfo[].m_uiTimeFromRaceBegin
		*/
	//	Body += Get16(Body);
	//}

	//BYTE RankedMatchSpeedKingBuffer = Read8(Body);
	//UINT DistanceTotal = Read32(Body);
	//BYTE IsHitRecordContion = Read8(Body);
	//USHORT HangSpan = Read16(Body);
	//BYTE CurRound = Read8(Body);
	//BYTE IncRound = Read8(Body);


	/*if (Client->MapCompatibilityMode)
	{
		IsFinish = FALSE;
		if (DistanceToEnd == 0)
		{
			IsFinish = TRUE;
		}
	}*/
#endif
#ifdef DEBUG
	printf("Round:%d\n", Client->Round);
#endif
	if (IsFinish)
	{
		//printf("IsFinish:%d\n", IsFinish);
		
		Client->IsFinish = TRUE;
		if (Client->RoomID != 0 && Client->FinishTime == 0&&Client->TaskID == 0)
		{
			Client->FinishTime = LapTime * 10;
			bool NewRecord = PlayerDB_SetMapRecord(Client->Uin, Client->MapID, Client->FinishTime);
			
			
			RoomNode* Room = GetRoom(Client->RoomID);
			if (!Room)
			{
				return;
			}
			int PlayerNum = 0;
			if (Room->CountDownFlag == 0)
			{
				Room->CountDownFlag = 1;
				Client->ranknumber = Room->ranknumber;
				Room->ranknumber++;
				for (char i = 0; i < 6; i++)
				{
					ClientNode* RoomClient = Room->Player[i];
					if (RoomClient)
					{
						PlayerNum++;
						NotifyCountDown(RoomClient, Client->Uin, NewRecord, Client->FinishTime);
					}
				}
			}
			else
			{
				Client->ranknumber = Room->ranknumber;
				Room->ranknumber++;
				for (char i = 0; i < 6; i++)
				{
					ClientNode* RoomClient = Room->Player[i];
					if (RoomClient)
					{
						NotifyPlayerFinishRace(RoomClient, Client->Uin, NewRecord, Client->FinishTime);
					}
				}
			}
				
			
			
			
			if (!Room->Timer)
			{
				CreateRoomTimer(Room, 10000, OnCountDown);
				//if (PlayerNum > 1)
				//{
				//	CreateRoomTimer(Room, 10000, OnCountDown);//如果玩家大于1等待10秒后进入结算界面
				//}
				//else
				//{
					//if (NewRecord)
					//{
						//CreateRoomTimer(Room, 3000, OnCountDown);
					//}
				//}

			}
		}
		/*else if (Client->TaskID == 0xFFFF || Client->TaskID == 0xFFFE)
		{
			//闯关
			HANDLE over = CreateThread(NULL, 0, OnSingleOver, Client, 0, NULL);
			if (over)
			{
				CloseHandle(over);
			}
		}*/
		else if(Client->BorderRoomID != 0 && Client->FinishTime == 0 && Client->TaskID == 0xFFFD||Client->TaskID==0xFFFC||Client->TaskID==0xFFFB)
		{
			Client->FinishTime = LapTime * 10;
			bool NewRecord = PlayerDB_SetMapRecord(Client->Uin, Client->MapID, Client->FinishTime);
			
			RoomNode* BorderRoom = GetRoom(Client->BorderRoomID);
			if (!BorderRoom)
			{
				return;
			}
			int PlayerNum = 0;
			if (BorderRoom->CountDownFlag == 0)
			{
				BorderRoom->CountDownFlag = 1;
				for (char i = 0; i < 6; i++)
				{
					ClientNode* RoomClient = BorderRoom->Player[i];
					if (RoomClient)
					{
						PlayerNum++;
						
						NotifyCountDown(RoomClient, Client->Uin, NewRecord, Client->FinishTime);
					}
				}
			}
			else
			{
				for (char i = 0; i < 6; i++)
				{
					ClientNode* RoomClient = BorderRoom->Player[i];
					if (RoomClient)
					{
						NotifyPlayerFinishRace(RoomClient, Client->Uin, NewRecord, Client->FinishTime);
					}
				}
			}

			if (!BorderRoom->Timer)
			{
				CreateRoomTimer(BorderRoom, 10000, OnBorderCountDown);
				/*if (PlayerNum > 1)
				{
					CreateRoomTimer(BorderRoom, 10000, OnBorderCountDown);//如果玩家大于1等待10秒后进入结算界面
				}
				else
				{
					CreateRoomTimer(BorderRoom, 3000, OnBorderCountDown);
				}*/

			}
		}
		else if (Client->TaskID == 0x06a5)
		{
			
			Client->OptNum = 0;
			Client->TaskID = 0;
			Client->IsFinish = FALSE;
		}
		else if(Client->TaskID!=0)//其他单人任务完成
		{
			
			SendToClient(Client, 532, (BYTE*)"\x00\x00", 2, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
			
			BYTE* pp = taskaward;
			Write32(pp, Client->Uin);
			pp += 2;
			Write32(pp, Client->TaskID);
			Write8(pp, 0);
			SendToClient(Client, 533, taskaward, 127, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
			
			SendToClient(Client, 534, (BYTE*)"\x00\x00", 2, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
			Client->TaskID = 0;
			Client->OptNum = 0;
			Client->IsFinish = FALSE;
		}
		
	}
}

void NotifyCountDown(ClientNode* Client, UINT WinnerUin, bool WinnerNewRecord, UINT FinTime)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write32(p, 10000); //CountDownTime
	Write32(p, WinnerUin); //WinnerUin
	Write8(p, WinnerNewRecord); //WinnerNewRecord
	Write32(p, FinTime); //FinTime

	len = p - buf;
	SendToClient(Client, 512, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
}

void NotifyRaceShow(ClientNode* Client)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write32(p, 0); //RaceShowTime
	Write8(p, 0); //HasFBInfo
	/*
m_stFBInfo[].m_bFBResult
m_stFBInfo[].m_uiKiller
	*/

#ifndef ZingSpeed
	Write8(p, 0); //WinTeamID
	Write32(p, 0); //EventID

	Write32(p, 0); //ParaNum
	//m_auiPara[]

#endif

	len = p - buf;
	SendToClient(Client, 515, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
}

void NotifyRaceOver(ClientNode* Client, RoomNode* Room)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;
	//RoomNode* Room = GetRoom(Client->RoomID);
	//if (!Room)
	//{
	//	return;
	//}
	char playernum = 0;
	BYTE* PlayerNum = p;
	Write8(p, 0); //CurrentPlayerNum
	for (char i = 0; i < Room->CurrentPlayerNum; i++)
	{
		for (char i2 = 0; i2 < 6; i2++)
		{
			ClientNode* RoomClient = Room->Player[i2];
			if (RoomClient)
			{
				if (RoomClient->ranknumber == i && RoomClient->IsFinish == TRUE)
				{ //RaceScore
					playernum++;
					BYTE* pRaceScore = p;
					Write16(pRaceScore, 0); //len

					Write32(pRaceScore, RoomClient->Uin); //Uin
					Write32(pRaceScore, RoomClient->FinishTime); //FinTime
					Write32(pRaceScore, 0); //TP
					Write32(pRaceScore, 0); //MoneyInc
					Write32(pRaceScore, 99999999); //TotalMoney
					Write32(pRaceScore, 0); //ExpInc
					Write32(pRaceScore, 99999999); //TotalExp

					//Write8(pRaceScore, 0xa); //AwardNum
					//m_iSpecialAward[]
					memcpy(pRaceScore, "\x0a\x00\x00\x00\x03\x00\x00\x00\x06\x00\x00\x00\x07\x00\x00\x00\x08\x00\x00\x00\x10\x00\x00\x00\x1a\x00\x00\x00\x1e\x00\x00\x00\x1f\x00\x00\x00\x22\x00\x00\x00\x23", 41);
					pRaceScore += 41;
					Write32(pRaceScore, 0); //TeamWorkExpInc
					Write32(pRaceScore, 0); //PropPoint
					Write32(pRaceScore, 0); //PropPointAddExp
					Write32(pRaceScore, 0); //LuckyMatchPointInc
					Write32(pRaceScore, 0); //LuckyMatchPointTotal
					Write32(pRaceScore, 0); //LuckyMatchScoreInc
					Write32(pRaceScore, 0); //LuckyMatchScoreTotal
					Write32(pRaceScore, 0); //LuckMoneyInc
					Write32(pRaceScore, 99999999); //LuckMoneyTotal
					Write32(pRaceScore, 0); //GuildScoreInc

					Write8(pRaceScore, 0); //CrazyPropAchieveNum
					//m_aiCrazyPropAchieve[]

					Write32(pRaceScore, 0); //IncWlMatchScore
					Write32(pRaceScore, 0); //IncWlDegree
					Write8(pRaceScore, 0); //IncItemNumByWl
					/*
			m_astRaceScore[].m_astIncItemInfoByWl[].m_shGenderItemNum
			m_astRaceScore[].m_astIncItemInfoByWl[].m_aiItemID[EGT_MAX]
			m_astRaceScore[].m_astIncItemInfoByWl[].m_shItemNum
			m_astRaceScore[].m_astIncItemInfoByWl[].m_iAvailPeriod
			m_astRaceScore[].m_astIncItemInfoByWl[].m_usBroadcastType
			m_astRaceScore[].m_astIncItemInfoByWl[].m_usBroadcastFlag
			m_astRaceScore[].m_astIncItemInfoByWl[].m_ucShowPriority
			m_astRaceScore[].m_astIncItemInfoByWl[].m_uchItemType
			m_astRaceScore[].m_astIncItemInfoByWl[].m_uchIgnoreItem
			m_astRaceScore[].m_astIncItemInfoByWl[].m_uiLimitPara
			m_astRaceScore[].m_astIncItemInfoByWl[].m_ucSpecialAwardCtrlType
			m_astRaceScore[].m_astIncItemInfoByWl[].m_ucAwardCtrlType
					*/

					Write32(pRaceScore, 0); //WlMutiplyCard
					Write32(pRaceScore, 0); //SkateCoinInc
					Write32(pRaceScore, 0); //SkateCoinTotal
					Write32(pRaceScore, 0); //SkateCoinHistoryTotal
					Write32(pRaceScore, 99999999); //TotalCoupons


					Write8(pRaceScore, 0); //ChallengeCheer
					/*
			m_astRaceScore[].m_stChallengeCheer[].m_ushGuildCheerValueInc
			m_astRaceScore[].m_stChallengeCheer[].m_ushCheerValueInc
			m_astRaceScore[].m_stChallengeCheer[].m_uiTotalCheerValue
			m_astRaceScore[].m_stChallengeCheer[].m_ushCouponsInc
			m_astRaceScore[].m_stChallengeCheer[].m_iGuildScoreInc
			m_astRaceScore[].m_stChallengeCheer[].m_iSuperMoneyInc
					*/

					Write32(pRaceScore, 0); //LoveValue
					Write32(pRaceScore, 0); //SkateCoinEmperorBonus
					Write32(pRaceScore, 0); //DetailRecordID

					Write8(pRaceScore, 0); //HasGangsterResult
					/*
			m_astRaceScore[].m_astGangsterResult[].m_cAbnormalFalg
			m_astRaceScore[].m_astGangsterResult[].m_uiGangsterBlood
			m_astRaceScore[].m_astGangsterResult[].m_uiGangsterTotalScore
			m_astRaceScore[].m_astGangsterResult[].m_uiGangsterIndentity
			m_astRaceScore[].m_astGangsterResult[].m_uiFragmentInc
			m_astRaceScore[].m_astGangsterResult[].m_uiKillTimes
			m_astRaceScore[].m_astGangsterResult[].m_uiDeadTimes
			m_astRaceScore[].m_astGangsterResult[].m_ucIsMultiple
			m_astRaceScore[].m_astGangsterResult[].m_ucIsLimited
			m_astRaceScore[].m_astGangsterResult[].m_iScoreInc
			m_astRaceScore[].m_astGangsterResult[].m_iTotalScore
			m_astRaceScore[].m_astGangsterResult[].m_iLoseStreakCount
					*/

					{ //EquippedActiveKartInfo
						BYTE* pEquippedActiveKartInfo = pRaceScore;
						Write16(pEquippedActiveKartInfo, 0); //len

						Write8(pEquippedActiveKartInfo, 0); //HaveActiveInfo
						Write32(pEquippedActiveKartInfo, 0); //KartID
						Write32(pEquippedActiveKartInfo, 0); //ActiveLevel

						len = pEquippedActiveKartInfo - pRaceScore;
						Set16(pRaceScore, (WORD)len);
						pRaceScore += len;
					}


					Write8(pRaceScore, 0); //HasWeRelayRaceOverInfo
					/*
				m_astRaceScore[].m_stWeRelayRaceOverInfo[].m_stSumStageInfo.m_u32Score
				m_astRaceScore[].m_stWeRelayRaceOverInfo[].m_stSumStageInfo.m_u32ScoreInc
				m_astRaceScore[].m_stWeRelayRaceOverInfo[].m_stSumStageInfo.m_u32Supermoney
				m_astRaceScore[].m_stWeRelayRaceOverInfo[].m_stSumStageInfo.m_u32Coupons
				m_astRaceScore[].m_stWeRelayRaceOverInfo[].m_stSumStageInfo.m_u32SuperN2O
				m_astRaceScore[].m_stWeRelayRaceOverInfo[].m_uiWeRelayScoreInc
				m_astRaceScore[].m_stWeRelayRaceOverInfo[].m_uiWeRelayScoreNow
				m_astRaceScore[].m_stWeRelayRaceOverInfo[].m_uiWeRelayScoreLevelNow
				m_astRaceScore[].m_stWeRelayRaceOverInfo[].m_uiWeRelayScoreLevelLimit
				m_astRaceScore[].m_stWeRelayRaceOverInfo[].m_uiSupermoneyLimit
				m_astRaceScore[].m_stWeRelayRaceOverInfo[].m_uiSupermoneyNow
				m_astRaceScore[].m_stWeRelayRaceOverInfo[].m_uiCouponsLimit
				m_astRaceScore[].m_stWeRelayRaceOverInfo[].m_uiCouponsNow
				m_astRaceScore[].m_stWeRelayRaceOverInfo[].m_uiLuckAwardMul
					*/

					Write8(pRaceScore, 0); //HaveSkatePropRaceInfo
					/*
				m_astRaceScore[].m_stSkatePropRaceInfo[].m_uiScoreAdd
				m_astRaceScore[].m_stSkatePropRaceInfo[].m_uiScoreTotal
					*/

					Write8(pRaceScore, 0); //IsNewBox


					Write8(pRaceScore, 0); //HaveArrestScoreInfo
					/*
				m_astRaceScore[].m_stArrestScoreInfo[].m_uiScoreInGame
				m_astRaceScore[].m_stArrestScoreInfo[].m_uiScoreByGold
				m_astRaceScore[].m_stArrestScoreInfo[].m_uiGoldMoney
				m_astRaceScore[].m_stArrestScoreInfo[].m_uiArrestNum
				m_astRaceScore[].m_stArrestScoreInfo[].m_uchResultType
				m_astRaceScore[].m_stArrestScoreInfo[].m_bTeamID
					*/

					Write8(pRaceScore, 0); //HasRankedMatchInfo
					/*
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchLastGradeInfo.m_uiGradeLevel
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchLastGradeInfo.m_uiChildLevel
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchLastGradeInfo.m_uiGradeScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchLastGradeInfo.m_uiMaxGradeScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchLastGradeInfo.m_uiTotalScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchGradeInfo.m_uiGradeLevel
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchGradeInfo.m_uiChildLevel
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchGradeInfo.m_uiGradeScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchGradeInfo.m_uiMaxGradeScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchGradeInfo.m_uiTotalScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchPromoInfo.m_ucPromotionMatch
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchPromoInfo.m_uiPromotionRoundNums
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchPromoInfo.m_uiPromotionSuccessRoundNums
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchPromoInfo.m_uiPromotionAlreadySuccessRoundNums
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchPromoInfo.m_uiPromotionRecordTag
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchPromoInfo.m_uiCurrentPromotionRoundNums
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchPromoInfo.m_uiPromoFailedMinusScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchPromoInfo.m_uiPromoSuccAddScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchPromoInfo.m_ucPromoDirectly
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchPromoInfo.m_ucGradeNoNeedPromo
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchPromoInfo.m_bRankedMemoryNoNeedPromo
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchPromoInfo.m_uchPromotionExtraScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchPromoInfo.m_ucPromtRaceFailedDefendFlag
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_iRankAddScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_iFinishAddScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_iKillAllAddScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_iGradeProtectAddScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_iGradeAddScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_uiProtectAddScoreGradeLimit
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_iDailyExtraAddScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_iAwardRankCoinNums
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_iWeeklyAwardRankCoinNums
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_iWeeklyAwardRankCoinLimit
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_iAwardRankCoinNumsByRank
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_iAwardRankCoinNumsByFinish
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_iBanMapExtraAddScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_iTeamRankAddScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_iAwardRankCoinNumsByTeamRank
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_iAwardRankCoinNumsByTask
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_ucUseDoubleScoreItem
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_ucUserNotDecreaseItem
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_ucFinishSeasonChallengeTaskOrNot
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_uiFinishedSeasonChallengeTaskIndex
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_uiSeasonChallengeTaskProtectAddScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_uchNotDecreaseReason
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_ucHaveSpeedKingInfo
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchSpeedKingInfos[].m_ucWinOrNot
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchSpeedKingInfos[].m_UiAwardSpeedKingEnergyItemNums
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchSpeedKingInfos[].m_uiWeeklyAwardSpeedKingEnergyItemNums
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchSpeedKingInfos[].m_uiWeeklyAwardSpeedKingEnergyItemLimitNums
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_ucHaveExtraComputeInfo
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_uiExtraComputeType
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_uiAwardItemNums
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_uiWeekylyAwardItemNums
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_uiWeeklyAwardItemLimitNums
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_ucHaveGameLogicTask
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_astRakedMatchGamelogicTaskInfo[].m_uiGameLogicTaskType
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_astRakedMatchGamelogicTaskInfo[].m_uiTaskFinishCondValue
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_astRakedMatchGamelogicTaskInfo[].m_ucJudgeRule
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_astRakedMatchGamelogicTaskInfo[].m_uiTaskAddGradeScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_astRakedMatchGamelogicTaskInfo[].m_uchGradeScoreRangeNum
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_astRakedMatchGamelogicTaskInfo[].m_auiGradeScoreRange[]
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_astRakedMatchGamelogicTaskInfo[].m_uchTaskFinishCondValueNum
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_astRakedMatchGamelogicTaskInfo[].m_auiTaskFinishCondValueRange[]
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_astRakedMatchGamelogicTaskInfo[].m_uchTaskAddGradeScoreNum
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_astRakedMatchGamelogicTaskInfo[].m_auiTaskAddGradeScoreRange[]
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_astRakedMatchGamelogicTaskInfo[].m_uchFailedAddGradeScoreNum
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_astRakedMatchGamelogicTaskInfo[].m_auiFailedAddGradeScoreRange[]
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_astRakedMatchGamelogicTaskInfo[].m_ucFinishTask
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_astRakedMatchGamelogicTaskInfo[].m_uiExtraFinishTaskAddScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_ucWin
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_ucNormalPlayerOrNot
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_astRankedMatchExtracComputeInfos[].m_ucLeadRolePlayerNums
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_uiSeasonNewMapAddScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.uchSeasonChallengeBaseScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.uchSeasonChallengeContiWinExtrScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.uchSeasonChallengeRegretDefeatScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.uchSeasonChallengeRespectableOpponentScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_uchSpeedGodChallengeAddScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_uchSpeedGodChallengeAddCoin
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_uchSpeedFlashAddFactoryCoin
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_uchPinnacleBattleAddScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_uchPromotionExtraScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_uiSavedExtraScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_uiDailyExtraTaskID
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_uchSuitActiveAddScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_uchSpeedGodChallengeType
				m_astRaceScore[].m_stRankedMatchScore[].m_stRankedMatchComputeInfo.m_uchSuitActiveEffectID
				m_astRaceScore[].m_stRankedMatchScore[].m_uchHavePromotionExtraScoreInfo
				m_astRaceScore[].m_stRankedMatchScore[].m_stPromotionExtraScoreInfo[].m_ucPromotionMatch
				m_astRaceScore[].m_stRankedMatchScore[].m_stPromotionExtraScoreInfo[].m_uiPromotionRoundNums
				m_astRaceScore[].m_stRankedMatchScore[].m_stPromotionExtraScoreInfo[].m_uiPromotionSuccessRoundNums
				m_astRaceScore[].m_stRankedMatchScore[].m_stPromotionExtraScoreInfo[].m_uiPromotionAlreadySuccessRoundNums
				m_astRaceScore[].m_stRankedMatchScore[].m_stPromotionExtraScoreInfo[].m_uiPromotionRecordTag
				m_astRaceScore[].m_stRankedMatchScore[].m_stPromotionExtraScoreInfo[].m_uiCurrentPromotionRoundNums
				m_astRaceScore[].m_stRankedMatchScore[].m_stPromotionExtraScoreInfo[].m_uiPromoFailedMinusScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stPromotionExtraScoreInfo[].m_uiPromoSuccAddScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stPromotionExtraScoreInfo[].m_ucPromoDirectly
				m_astRaceScore[].m_stRankedMatchScore[].m_stPromotionExtraScoreInfo[].m_ucGradeNoNeedPromo
				m_astRaceScore[].m_stRankedMatchScore[].m_stPromotionExtraScoreInfo[].m_bRankedMemoryNoNeedPromo
				m_astRaceScore[].m_stRankedMatchScore[].m_stPromotionExtraScoreInfo[].m_uchPromotionExtraScore
				m_astRaceScore[].m_stRankedMatchScore[].m_stPromotionExtraScoreInfo[].m_ucPromtRaceFailedDefendFlag
					*/

					Write8(pRaceScore, 0); //HaveCrazyChaseScoreInfo
					/*
				m_astRaceScore[].m_astCrazyChaseScoreInfo[].m_uiUin
				m_astRaceScore[].m_astCrazyChaseScoreInfo[].m_shRole
				m_astRaceScore[].m_astCrazyChaseScoreInfo[].m_uiScore
				m_astRaceScore[].m_astCrazyChaseScoreInfo[].m_uchScoreNum
				m_astRaceScore[].m_astCrazyChaseScoreInfo[].m_astScoreInfo[].m_uchScoreType
				m_astRaceScore[].m_astCrazyChaseScoreInfo[].m_astScoreInfo[].m_iValue
				m_astRaceScore[].m_astCrazyChaseScoreInfo[].m_astScoreInfo[].m_iScore
					*/
					Write8(pRaceScore, 0); //TeamID

					Write8(pRaceScore, 0); //HasRankedMatchArenaInfo
					/*
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_ucWin
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_ucRank
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_ucTaskScore
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_iAwardRankCoinNums
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchLastGradeInfo.m_uiGradeLevel
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchLastGradeInfo.m_uiChildLevel
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchLastGradeInfo.m_uiGradeScore
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchLastGradeInfo.m_uiMaxGradeScore
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchLastGradeInfo.m_uiTotalScore
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchGradeInfo.m_uiGradeLevel
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchGradeInfo.m_uiChildLevel
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchGradeInfo.m_uiGradeScore
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchGradeInfo.m_uiMaxGradeScore
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchGradeInfo.m_uiTotalScore
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchPromoInfo.m_ucPromotionMatch
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchPromoInfo.m_uiPromotionRoundNums
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchPromoInfo.m_uiPromotionSuccessRoundNums
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchPromoInfo.m_uiPromotionAlreadySuccessRoundNums
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchPromoInfo.m_uiPromotionRecordTag
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchPromoInfo.m_uiCurrentPromotionRoundNums
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchPromoInfo.m_uiPromoFailedMinusScore
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchPromoInfo.m_uiPromoSuccAddScore
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchPromoInfo.m_ucPromoDirectly
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchPromoInfo.m_ucGradeNoNeedPromo
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchPromoInfo.m_bRankedMemoryNoNeedPromo
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchPromoInfo.m_uchPromotionExtraScore
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_stRankedMatchPromoInfo.m_ucPromtRaceFailedDefendFlag
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_ucWinNum
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_sCurrentScore
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_ucFinishScore
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_usAwardRankScore
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_ucAwardRankCoinNumsByRank
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_ucAwardRankCoinNumsByFinish
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_iWeeklyAwardRankCoinNums
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_iWeeklyAwardRankCoinLimit
				m_astRaceScore[].m_stRankedMatchArenaScore[].m_iAwardRankCoinNumsByTask
					*/


					Write32(pRaceScore, 0); //DistanceToEnd
					Write8(pRaceScore, 0); //ShortDistancWinPoint
					Write8(pRaceScore, 0); //Status


					Write8(pRaceScore, 0); //HaveRankedMatchSpeedKingInfo
					/*
				m_astRaceScore[].m_stRankedMatchSpeedKingScoreInfo[].m_uiAwardSpeedKingEnergyNums
				m_astRaceScore[].m_stRankedMatchSpeedKingScoreInfo[].m_ucWin
					*/


					Write8(pRaceScore, 0); //ProfessionLicenseAwardNum 职业生涯增长
				

					{ //RaceResult
						BYTE* pRaceResult = pRaceScore;
						Write16(pRaceResult, 0); //len

						Write8(pRaceResult, 0); //PLExpPowerValid
						Write8(pRaceResult, 0); //PLHonorPowerValid
						Write8(pRaceResult, 0); //ExpMultiNum
						Write8(pRaceResult, 0); //HonorMultiNum

						len = pRaceResult - pRaceScore;
						Set16(pRaceScore, (WORD)len);
						pRaceScore += len;
					}

					Write8(pRaceScore, 0); //HaveRankedMatchExtraInfo
					/*
					m_astRaceScore[].m_stRankedMatchExtraScoreInfo[].m_uiAwardItemNums
					m_astRaceScore[].m_stRankedMatchExtraScoreInfo[].m_ucWin
					*/

					Write8(pRaceScore, 0); //HasYuLeJiaNianHuaComputeData
					/*
					m_astRaceScore[].m_stYuLeJiaNianHuaComputeData[].m_iAwardScore
					m_astRaceScore[].m_stYuLeJiaNianHuaComputeData[].m_uchRecommend
					m_astRaceScore[].m_stYuLeJiaNianHuaComputeData[].m_uchScoreDouble
					m_astRaceScore[].m_stYuLeJiaNianHuaComputeData[].m_uchGuaJi
					*/

					len = pRaceScore - p;
					Set16(p, (WORD)len);
					p += len;
					break;
				}
			}
		}
	}
	Set8(PlayerNum, playernum);
	Write8(p, 0); //WinTeamID
	Write32(p, 0); //WinType
	Write32(p, 0); //AwardTime
	Write8(p, 0); //LuckyMatchResult
	Write8(p, 0); //LuckyMatchType


	Write8(p, 1); //PlayerNumber
	{ //HideTaskResult
		BYTE* pHideTaskResult = p;
		Write16(pHideTaskResult, 0); //len

		Write32(pHideTaskResult, Client->Uin); //Uin
		Write32(pHideTaskResult, 0); //TaskId
		Write8(pHideTaskResult, 0); //HideTaskFinishResult

		len = pHideTaskResult - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write8(p, 0); //HasLadderMatchResult
	/*
m_stLDMRaceResult[].m_u8PlayerNum
m_stLDMRaceResult[].m_stResult[].m_u32Uin
m_stLDMRaceResult[].m_stResult[].m_u32Score
m_stLDMRaceResult[].m_stResult[].m_i32ScoreInc
m_stLDMRaceResult[].m_stResult[].m_u32NextGradeScore
m_stLDMRaceResult[].m_stResult[].m_u8Grade
m_stLDMRaceResult[].m_stResult[].m_u8BeforeGrade
m_stLDMRaceResult[].m_stResult[].m_stRank.m_u8RankType
m_stLDMRaceResult[].m_stResult[].m_stRank.m_u8RankValue
m_stLDMRaceResult[].m_stResult[].m_stEstimateRank.m_u8RankType
m_stLDMRaceResult[].m_stResult[].m_stEstimateRank.m_u8RankValue
	*/

	Write8(p, 0); //NeedFreshTutor
	Write8(p, 0); //hasMedalGameInfo
	//m_medalGameInfo[].m_curMedal

#ifndef ZingSpeed
	Write8(p, 0); //KickOffPlayerNumber
	/*
m_stKickOffPlayer[].m_u32Uin
m_stKickOffPlayer[].m_szNickName[17]
m_stKickOffPlayer[].m_bGender
m_stKickOffPlayer[].m_bTeamID
m_stKickOffPlayer[].m_bCountry
	*/

	Write8(p, 0); //EliminatedRacerNum
	/*
m_astEliminatedRacer[].m_unUin
m_astEliminatedRacer[].m_szRacerName[17]
	*/

	Write8(p, 0); //TeamNum
	/*
m_astTeamScore[].m_ucTeamID
m_astTeamScore[].m_iTeamScore
m_astTeamScore[].m_ucTeamMinRank
m_astTeamScore[].m_ucCooperNum
m_astTeamScore[].m_ucIncCooper
m_astTeamScore[].m_ucCurCooper
	*/

	Write8(p, 0); //NPCRacerNum
	/*
m_astArrestNPCResultInfo[].m_iNpcID
m_astArrestNPCResultInfo[].m_szNPCName[17]
m_astArrestNPCResultInfo[].m_uchResultType
	*/

	Write8(p, 0); //hasGameFrameInfo
	/*
m_astGameFrameInfo[].m_uiUin
m_astGameFrameInfo[].m_iMapID
m_astGameFrameInfo[].m_ushFrameNum
m_astGameFrameInfo[].m_astFrameInfo[].m_ushCheckPointID
m_astGameFrameInfo[].m_astFrameInfo[].m_uiNum
m_astGameFrameInfo[].m_astFrameInfo[].m_astFrameList[].m_unTimeElaps
m_astGameFrameInfo[].m_astFrameInfo[].m_astFrameList[].m_fInPosX[]
m_astGameFrameInfo[].m_astFrameInfo[].m_astFrameList[].m_fInPosY[]
m_astGameFrameInfo[].m_astFrameInfo[].m_astFrameList[].m_fInPosZ[]
m_astGameFrameInfo[].m_astFrameInfo[].m_astFrameList[].m_fStepX[]
m_astGameFrameInfo[].m_astFrameInfo[].m_astFrameList[].m_fStepY[]
m_astGameFrameInfo[].m_astFrameInfo[].m_astFrameList[].m_fStepZ[]
m_astGameFrameInfo[].m_astFrameInfo[].m_astFrameList[].m_fCarMat[]
m_astGameFrameInfo[].m_astFrameInfo[].m_astFrameList[].m_fOutPosX[]
m_astGameFrameInfo[].m_astFrameInfo[].m_astFrameList[].m_fOutPosY[]
m_astGameFrameInfo[].m_astFrameInfo[].m_astFrameList[].m_fOutPosZ[]
m_astGameFrameInfo[].m_astFrameInfo[].m_astFrameList[].m_fAccTime[]
m_astGameFrameInfo[].m_astFrameInfo[].m_astFrameList[].m_fFrameTime[]
m_astGameFrameInfo[].m_astFrameInfo[].m_astFrameList[].m_ucSetPos
m_astGameFrameInfo[].m_astFrameInfo[].m_astFrameList[].m_ucCollision
	*/

	Write8(p, 0); //hasDesperateEscapeTrophyInfo
	/*
m_astDesperateEscapeTrophyInfo[].m_uchNum
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_uiUin
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_uiSrcUin
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_uchTrophyType
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_uiID
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_uiRefitCount
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_uchStatus
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_uchHasRefit
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_uiUin
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_iKartId
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_iRefitCout
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_shMaxFlags
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_shWWeight
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_shSpeedWeight
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_shJetWeight
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_shSJetWeight
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_shAccuWeight
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_iShapeRefitCount
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_iKartHeadRefitItemID
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_iKartTailRefitItemID
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_iKartFlankRefitItemID
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_iKartTireRefitItemID
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_iSecondRefitCount
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_shSpeed2Weight
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_shDriftVecWeight
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_shAdditionalZSpeedWeight
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_shAntiCollisionWeight
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_shLuckyValue
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_shRefitLuckyValueMaxWeight
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_iShapeSuitID
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_ucLegendSuitLevel
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_iLegendSuitLevelChoice
m_astDesperateEscapeTrophyInfo[].m_astInfo[].m_astKartRefitInfo[].m_iShapeLegendSuitID
	*/

	Write8(p, 0); //HasGameStageInfo
	/*
m_stGameStageInfo[].m_u8StageIndex
m_stGameStageInfo[].m_u8TotalStageNum
	*/
#endif

	len = p - buf;
	SendToClient(Client, 513, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
}


void NotifyGameOver(ClientNode* Client, USHORT LeaveGameType, BYTE ParaNum, int* ParaList)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;
	USHORT OverCount = 0;
	if (Client->RoomID)
	{
		Client->IsReady = FALSE;
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
				if (RoomClient->IsReady == FALSE)
				{
					OverCount++;//计算结束的人数
				}
			}
		}
		if (OverCount == Room->CurrentPlayerNum)
		{
			Room->Callback = NULL;
		}
	}


	Write16(p, 0); //ResultID

#ifndef ZingSpeed
	Write8(p, 0); //StageIndex
	Write8(p, 0); //ReturnHall
	Write8(p, 0); //WaitEnterRoom
	Write16(p, LeaveGameType); //LeaveGameType
	Write8(p, ParaNum); //ParaNum
	for (size_t i = 0; i < ParaNum; i++)
	{
		//m_aiParaList[]
		Write32(p, ParaList[i]);
	}
#endif

	len = p - buf;
	SendToClient(Client, 514, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
}


void RequestTransferByTCP(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	//DWORD dwStart = GetTickCount64();
	//对局方式为PVP时 Client指针指向为空 会导致Room为空
	//如果启动UDP服务器需要禁止该消息就不会走这个消息
	UINT Uin = Read32(Body);
	RoomNode* Room = NULL;
	if (Client->RoomID != 0)
	{
		Room = GetRoom(Client->RoomID);
	}
	else if (Client->BorderRoomID != 0)
	{
		Room = GetRoom(Client->BorderRoomID);
	}
	if (!Room)
	{
		return;
	}
	UINT Time = Read32(Body);

	char Ver = Read8(Body);
	int Seq = Read32(Body);
	char DstNum = Read8(Body);
	//printf("ClientUin:%d Transfer\n", Client->Uin);
	//printf("Client->RoomID:%d\n", Client->RoomID);
	//printf("Client->BorderRoomID:%d\n", Client->BorderRoomID);
	//printf("ClientTaskID:%d\n", Client->TaskID);
	
	/*DstInfo aDstInfo[6] = {0};
	for (char i = 0; i < DstNum; i++)
	{
		BYTE* pDstInfo = Body;
		USHORT len = Read16(pDstInfo);

		aDstInfo[i].PlayerID = Read16(pDstInfo);
		aDstInfo[i].Uin = Read32(pDstInfo);
		//printf("TransferByTCP ClientUin:%d to DstUin:%d\n",Uin, aDstInfo[i].Uin);
		//fflush(stdout);
		Body += len;
	}*/
	Body += 8*DstNum;
	
	
	USHORT BuffLen = Read16(Body);
	
	for (char i2 = 0; i2 < 6; i2++)
	{
		ClientNode* RoomClient =Room->Player[i2];
		if (RoomClient&&RoomClient!=Client)
		{
			for (int i = 0; i < 6; i++)
			{
				NotifyTranferByTCP(RoomClient, Client->Uin, Client->ConnID, Seq, Body, BuffLen);
			}
		}
	}	
	//DWORD dwUsed = GetTickCount64() - dwStart; //计算该函数所消耗的时间
		//printf("lost:%d ms\n", dwUsed);
}
void NotifyTranferByTCP(ClientNode* Client, UINT SrcUin, USHORT SrcPlayerID, int Seq, BYTE* Buff, int Bufflen)
{
	
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write32(p, SrcUin);
	Write16(p, SrcPlayerID);
	Write8(p, 0); //Ver
	Write32(p, Seq);
	Write16(p, Bufflen);
	memcpy(p, Buff, Bufflen);
	p += Bufflen;


	len = p - buf;
	SendToClient(Client, 560, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}


void NotifyAddPropBySkillStone(ClientNode* Client, int StoneSkillType, short PropID, int PropIndex)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write32(p, StoneSkillType);
	Write16(p, PropID);
	Write32(p, PropIndex);

	len = p - buf;
	SendToClient(Client, 908, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Notify);
}

/*

｜No.1 荣耀战狮｜

赛车技能

在使用氮气或道具时有一定概率触发，接下来一段时间内 小喷动力提升以及 时间延长。

参考NotifyAddPropBySkillStone添加氮气道具

｜No.2 流影霸主｜

赛车等级： A丨喷口数量： 5个丨宝石槽数： 4个

赛车技能

通过在竞速模式中 积攒氮气获得 隐身技能，按空格键即可触发， 开局自带一个隐身技能。

｜No.3 蓝魔尊｜

赛车等级： A丨喷口数量： 5个丨宝石槽数： 4个

赛车技能

当玩家装备进行个人竞速模式游戏时，如道具格内 已有一个氮气，所获得的 下一个氮气将转化为 组队氮气，且 完成6人竞速赛获得经验+50％。

蓝魔鬼进阶版，蓝色和白色的车身尽显大气，可以装有3个竞速宝石槽和1个道具宝石槽，让你在赛场上驰聘纵横。

｜No.4 雷霆先锋｜

赛车等级： A丨喷口数量： 5个丨宝石槽数： 4个

赛车技能

装备后【个人竞速】模式中，如果 集满两个氮气，必定有且只有一个成为 蓝色氮气。

｜No.5 雷克｜

赛车等级： A丨喷口数量： 5个丨宝石槽数： 4个

赛车技能

集完 两个氮气后 再集一管，其中一个氮气的颜色会变成 紫色氮气，最多可以两个氮气都变成紫色。

参考NotifyAddPropBySkillStone添加氮气道具

｜No.6 时之沧影｜

赛车等级： A丨喷口数量： 5个丨宝石槽数： 4个


赛车技能

装备此赛车在进行比赛时，车尾带 个人记录 倒计时秒表特效。

参考RequestReportCurrentInfo消息处理获取比赛倒计时

｜No.7 亡灵剃刀｜

赛车等级： A丨喷口数量： 5个丨宝石槽数： 4个

赛车技能

当玩家装备亡灵剃刀在竞速模式或道具模式下游戏时，可以 查看到单局内 所有玩家的道具信息。

*/
//显示情侣超级氮气空格大招
void NotifyLM2CCooperInc(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write8(p, 0); //Reason
	Write16(p, 0); //CooperInc
	Write16(p, 0); //CurAccuCooper
	Write32(p, 0); //TotalCooper
	Write8(p, 0); //BeTriggerSuperJet
	Write8(p, 0); //SuperJetTime
	Write8(p, 0); //TriggerLoveTimeLimit
	Write32(p, 0); //NoCooperDistance
	Write32(p, Client->Uin); //Uin

	len = p - buf;
	SendToClient(Client, 11338, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void ResponseC2LMTriggerSuperJet(ClientNode* Client)
{//情侣超级氮气特效
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	Write8(p, 0); //SkillID
	Write8(p, 0); //SkillType
	len = p - buf;
	SendToClient(Client, 11339, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void NotifyLM2CSuperJet(ClientNode* Client)
{//喷气显示情侣爱心
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p,Client->Uin); //SuperJetTeamMateUin
	Write8(p, 0); //SkillID
	Write8(p, 0); //SkillType
	Write8(p, 0); //IsAck
	len = p - buf;
	SendToClient(Client, 11340, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}
void RequestReportDrift(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body; WORD len;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	int DriftFlag = Read32(p);
	int AccelerateFuelInc = Read32(p);
	bool OnlyAccelSelfFue = Read8(p);
	UINT StartLapTime = Read32(p);
	UINT CurLapTime = Read32(p);

}

//添加超级氮气
void ResponseGetSuperN2O(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	int temp = 0;
	Write16(p, 0); //ResultID

	if (Client->SuperJetKartFuelInc >= 6000)
	{
		Write16(p, 777); //PropID玉麒麟超级氮气必须writekartphy写入777信息才生效
		Client->SuperJetKartFuelInc = 0;
		temp = 100;
	}
	else
	{
		Write16(p, 0);
		Client->CurrentAccelerateFuel = 0;
		temp = 180;
		
	}
	Write32(p, 1); //PropIndex
	Write32(p, 0); //CurrentAccelerateFuel
	Write8(p, 0); //ReasonLen
	//printf("temp:%d\n", temp);

	Write32(p, temp); //SuperJetKartFuelInc 玉麒麟superjet进度条增长量

	len = p - buf;
	SendToClient(Client, 119, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
	
	}
void NotifyUseProp(ClientNode* RoomClient,UINT DstUin, UINT Uin, UINT PropID)
{
	//通知别人使用道具效果 如氮气特效 导弹命中

	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Uin); //Uin
	Write16(p, PropID); //PropID
	Write32(p, DstUin); //DstUin
	Write32(p, 0); //PropPosition
	Write32(p, 0); //PropPosition
	Write32(p, 0); //PropPosition
	Write32(p, 0); //PropIndex
	Write16(p, 0); //NewID
	Write32(p, 0); //ItemID
	Write32(p, 0); //StoneSkillType
	Write32(p, 0); //LapTime
	Write8(p, 0); //DstUinNum
	//Write32(p, 0); //DstUin[]
	Write8(p, 0); //PropUseMode
	Write8(p, 0); //QueryUinNum
	//Write32(p, 0); //QueryUin[]
	Write8(p, 0); //DstType
	Write8(p, 0); //Position
	Write8(p, 0); //ParaNum
	//Write32(p, 0); //ParaList[]
	Write8(p, 0); //Status
	Write8(p, 0); //PropPosIdx
	Write8(p, 0); //PropSecType
	Write8(p, 0); //PassedCheckPointNum
	//Write16(p, 0); //PassedCheckPointIDs[]
	Write16(p, 0); //SubPropID
	Write8(p, 0); //OtherPropPosNum
	len = p - buf;
	SendToClient(RoomClient, 517, buf, len, RoomClient->ConnID, FE_PLAYER, RoomClient->ConnID, Notify);
}
void RequestUseProp2(ClientNode* Client, BYTE* Body, size_t BodyLen)
{//使用道具时就会触发这个请求消息 如氮气 其他道具等

	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	short PropID = Read16(Body);
	Client->PropID = PropID;
	if (34 == PropID)
	{
		Client->SuperJet = 0;
	}
	UINT DstUin = Read32(Body);

	//m_aiCurrentPosition[3]
	Body += 3 * 4;

	int PropIndex = Read32(Body);
	short NewID = Read16(Body);
	char IsClearProp = Read8(Body);
	BYTE DstType = Read8(Body);
	int MyUseItemID = Read32(Body);
	int DstUseItemID = Read32(Body);
	BYTE IsConvertMode = Read8(Body);
	int StoneSkillType = Read32(Body);
	UINT LapTime = Read32(Body);
	BYTE DstUinNum = Read8(Body);
	//m_au32DstUin[]
	
	BYTE PropUseMode = Read8(Body);
	BYTE QueryUinNum = Read8(Body);
	//m_au32QueryUin[]
	
#ifndef ZingSpeed
	UCHAR CurrentSelfRank = Read8(Body);
	UCHAR CurrentTeammateRank = Read8(Body);
	UCHAR Position = Read8(Body);
	char PropSecType = Read8(Body);
	UCHAR PropPosIdx = Read8(Body);
	UINT NPCUin = Read32(Body);
	UCHAR UsePropProtoMode = Read8(Body);
	short SubPropID = Read16(Body);
	UCHAR OtherPropPosNum = Read8(Body);
#endif

#ifdef DEBUG
	printf("PropID:%d, DstUin:%d, PropIndex:%d, StoneSkillType:%d\n", PropID, DstUin, PropIndex, StoneSkillType);
#endif
	//printf("PropID:%d, DstUin:%d, PropIndex:%d, StoneSkillType:%d\n", PropID, DstUin, PropIndex, StoneSkillType);
	//int Prob = 380;//六级重生发动率
	//int Prob = 290;
	if ((rand() % 1000) + Prob > 1000)
	{
		//重生发动 添加氮气道具 
		NotifyAddPropBySkillStone(Client, PropID, 1, PropIndex);
	}
	//ResponseGetSuperN2O(Client);
	RoomNode* Room = GetRoom(Client->RoomID);//通知其他人看到道具效果
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
				NotifyUseProp(RoomClient, DstUin, Uin, PropID);
			}
		}
	}
	

}

void NotifyAddPropByxiaolv(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	Write16(p, 34); //PropID
	Write32(p, 1); //PropIdx
	//Write32(p, 0); //ItemID
	//Write32(p, 0); //StoneSkillType

	len = p - buf;
	SendToClient(Client, 526, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}
//添加超级氮气
void ResponseGetSuperN2O2(ClientNode* Client)
{
	if (Client->SuperJet == 0)
	{
		Client->SuperJet = 1;//超级喷未使用标志 使用后才继续生产
		BYTE buf[8192]; BYTE* p = buf; size_t len;
		Write16(p, 0); //ResultID
		Write32(p, Client->Uin); //Uin
		Write16(p, 34); //PropID
		//34 433紫色氮气 2002蓝色氮气 71火球 176 190其他氮气 555火焰氮气 
		//777玉麒麟专属超级氮气
		Write32(p, 1); //PropIndex
		Write8(p, 0); //GetPropType
		Write32(p, 0); //AwardItemID
		Write8(p, 0); //ReasonLen
		Write16(p, 1); //PropPositionNO
		Write32(p, 0); //ActIDForClient
#ifndef ZingSpeed
		Write8(p, 0); //GetPropSecType
		Write8(p, 1); //PropPosIdx
		Write32(p, 0); //NPCUin
		Write8(p, 0); //ParaNum
		//Write32(p, 0); //ParaList[]
#endif
		len = p - buf;
		SendToClient(Client, 124, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
	}
}

void NotifySkillStoneKartInfo(ClientNode* Client, UINT ItemNum, KartStoneItemInfo* Items, bool HasMoreInfo)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	Write32(p, Client->Uin); //Uin

	Write32(p, ItemNum); //StoneKartNum
	for (int i = 0; i < ItemNum; i++)
	{
		BYTE* pKartStoneGrooveInfo = p;
		Write16(pKartStoneGrooveInfo, 0); //len
		Write32(pKartStoneGrooveInfo, Items[i].KartId);
		BYTE* pStoneGrooveNum = pKartStoneGrooveInfo;
		Write32(pKartStoneGrooveInfo, 0); //StoneGrooveNum
		{
			int StoneGrooveNum = 0;
			const char* sql = NULL;
			sqlite3_stmt* stmt = NULL;
			int result;
			sql = "SELECT StoneUseOccaType,SkillStoneID  FROM KartStone WHERE ID = ?;";
			result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
			if (result == SQLITE_OK) {
				sqlite3_bind_int(stmt, 1, Items[i].StoneID);
				while (sqlite3_step(stmt) == SQLITE_ROW)
				{ //StoneGrooveInfo
					StoneGrooveNum++;

					BYTE* pStoneGrooveInfo = pKartStoneGrooveInfo;
					Write16(pStoneGrooveInfo, 0); //len

					Write32(pStoneGrooveInfo, sqlite3_column_int(stmt, 0)); //StoneUseOccaType
					Write32(pStoneGrooveInfo, sqlite3_column_int(stmt, 1)); //SkillStoneID

					len = pStoneGrooveInfo - pKartStoneGrooveInfo;
					Set16(pKartStoneGrooveInfo, (WORD)len);
					pKartStoneGrooveInfo += len;
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
		len = pKartStoneGrooveInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write8(p, HasMoreInfo); //HasMoreInfo
	len = p - buf;
	SendToClient(Client, 228, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}
void NotifySkillStoneKartMoreInfo(ClientNode* Client, UINT ItemNum, KartStoneItemInfo* Items, bool HasMoreInfo)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //uin
	Write32(p, ItemNum); //StoneKartNum
	for (int i = 0; i < ItemNum; i++)
	{
		BYTE* pKartStoneGrooveInfo = p;
		Write16(pKartStoneGrooveInfo, 0); //len
		Write32(pKartStoneGrooveInfo, Items[i].KartId);
		BYTE* pStoneGrooveNum = pKartStoneGrooveInfo;
		Write32(pKartStoneGrooveInfo, 0); //StoneGrooveNum
		{
			int StoneGrooveNum = 0;
			const char* sql = NULL;
			sqlite3_stmt* stmt = NULL;
			int result;
			sql = "SELECT StoneUseOccaType,SkillStoneID  FROM KartStone WHERE ID = ?;";
			result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
			if (result == SQLITE_OK) {
				sqlite3_bind_int(stmt, 1, Items[i].StoneID);
				while (sqlite3_step(stmt) == SQLITE_ROW)
				{ //StoneGrooveInfo
					StoneGrooveNum++;

					BYTE* pStoneGrooveInfo = pKartStoneGrooveInfo;
					Write16(pStoneGrooveInfo, 0); //len

					Write32(pStoneGrooveInfo, sqlite3_column_int(stmt, 0)); //StoneUseOccaType
					Write32(pStoneGrooveInfo, sqlite3_column_int(stmt, 1)); //SkillStoneID

					len = pStoneGrooveInfo - pKartStoneGrooveInfo;
					Set16(pKartStoneGrooveInfo, (WORD)len);
					pKartStoneGrooveInfo += len;
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
		len = pKartStoneGrooveInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	
	Write8(p, HasMoreInfo); //HasNext

	len = p - buf;
	SendToClient(Client, 28416, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}
void NotifyOtherKartStoneInfo(ClientNode* Client)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;

	int ID = -1;
	sql = "SELECT ID  FROM KartStoneGroove  WHERE Uin=? AND KartID=?;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, Client->Uin);
		sqlite3_bind_int(stmt, 2, Client->KartID);
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

	Write32(p, 1); //OtherStoneKartNum
	{ //KartStoneGrooveInfo
		BYTE* paKartStoneGrooveInfo = p;
		Write16(paKartStoneGrooveInfo, 0); //len
		Write32(paKartStoneGrooveInfo, Client->Uin); //Uin
		{ //KartStoneGrooveInfo
			BYTE* pKartStoneGrooveInfo = paKartStoneGrooveInfo;
			Write16(pKartStoneGrooveInfo, 0); //len
			
			Write32(pKartStoneGrooveInfo, Client->KartID); //KartID
			
			BYTE* pStoneGrooveNum = pKartStoneGrooveInfo;
			Write32(pKartStoneGrooveInfo, 0); //StoneGrooveNum
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

						BYTE* pStoneGrooveInfo = pKartStoneGrooveInfo;
						Write16(pStoneGrooveInfo, 0); //len

						Write32(pStoneGrooveInfo, sqlite3_column_int(stmt, 0)); //StoneUseOccaType
						Write32(pStoneGrooveInfo, sqlite3_column_int(stmt, 1)); //SkillStoneID

						len = pStoneGrooveInfo - pKartStoneGrooveInfo;
						Set16(pKartStoneGrooveInfo, (WORD)len);
						pKartStoneGrooveInfo += len;
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

			len = pKartStoneGrooveInfo - paKartStoneGrooveInfo;
			Set16(paKartStoneGrooveInfo, (WORD)len);
			paKartStoneGrooveInfo += len;
		}

		len = paKartStoneGrooveInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	len = p - buf;
	SendToClient(Client, 907, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void RequestGetProp(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	if (Client->TaskID == 0xFFFF || Client->TaskID == 0xFFFE)
	{
		return;
	}
	BYTE* p = Body;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	short PropPositionNO = Read16(p);
	bool CurrentRank = Read8(p);
	//int CurrentPosition[3] = Read32(p);
	//int PreviousInterval = Read32(p);
	//char GetPropType = Read8(p);
	//bool TeammateRank = Read8(p);
	//char PointArrayIdx = Read8(p);
	//UINT LapTime = Read32(p);
#ifndef ZingSpeed
	//char GetPropSecType = Read8(p);
	//UCHAR PropPosIdx = Read8(p);
	//UINT NPCUin = Read32(p);
	//UCHAR ParaNum = Read8(p);
	//UINT ParaList[] = Read32(p);
#endif

	ResponseGetProp(Client);
}
void ResponseGetProp(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	static WORD PropIDs[] = { 1,2,3,4,5,6,7,8,9,10,15,16,18,21,25,27,41,43,44,45,46,47,49,50,51,53 };
	static int Index = 0;
	Index++;
	if (Index >= sizeof(PropIDs) / sizeof(WORD))
	{
		Index = 0;
	}
	//printf("%d\n", Index);

	Write16(p, 0); //ResultID
	Write32(p, Client->Uin); //Uin
	Write16(p, PropIDs[Index]); //PropID
	Write32(p, 0); //PropIndex
	Write8(p, 0); //GetPropType
	Write32(p, 0); //AwardItemID
	Write8(p, 0); //ReasonLen
	Write16(p, 0); //PropPositionNO
	Write32(p, 0); //ActIDForClient
#ifndef ZingSpeed
	Write8(p, 0); //GetPropSecType
	Write8(p, 0); //PropPosIdx
	Write32(p, 0); //NPCUin
	Write8(p, 0); //ParaNum
	Write32(p, 0); //ParaList[]
#endif


	len = p - buf;
	SendToClient(Client, 124, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}


void NotifyMsgBox(ClientNode* Client)
{
	BYTE buf[8192]; 
	BYTE* p = buf; 
	size_t len;

	Write8(p, 0); //MsgType
	{ //MsgBox
		BYTE* pMsgBox = p;
		Write16(pMsgBox, 0); //len

		{ //OnlineTaskMsg
			BYTE* pOnlineTaskMsg = pMsgBox;
			Write16(pOnlineTaskMsg, 0); //len

			Write8(pOnlineTaskMsg, 0); //MsgType
			Write32(pOnlineTaskMsg, 0); //OpenDate
			Write32(pOnlineTaskMsg, 0); //OpenTime
			Write32(pOnlineTaskMsg, 0); //CloseDate
			Write32(pOnlineTaskMsg, 0); //CloseTime
			Write8(pOnlineTaskMsg, 0); //IsToday
			Write8(pOnlineTaskMsg, 0); //URLLen
			Write8(pOnlineTaskMsg, 0); //WeekLimit

			len = pOnlineTaskMsg - pMsgBox;
			Set16(pMsgBox, (WORD)len);
			pMsgBox += len;
		}
		{ //VipPages
			BYTE* pVipPages = pMsgBox;
			Write16(pVipPages, 0); //len

			Write8(pVipPages, 0); //URLLen1
			Write8(pVipPages, 0); //URLLen2
			Write8(pVipPages, 0); //URLLen3

			len = pVipPages - pMsgBox;
			Set16(pMsgBox, (WORD)len);
			pMsgBox += len;
		}
		{ //ActivitiesAd
			BYTE* pActivitiesAd = pMsgBox;
			Write16(pActivitiesAd, 0); //len

			Write8(pActivitiesAd, 0); //URLLen

			len = pActivitiesAd - pMsgBox;
			Set16(pMsgBox, (WORD)len);
			pMsgBox += len;
		}
		{ //MatchSchedule
			BYTE* pMatchSchedule = pMsgBox;
			Write16(pMatchSchedule, 0); //len

			Write8(pMatchSchedule, 0); //URLLen

			len = pMatchSchedule - pMsgBox;
			Set16(pMsgBox, (WORD)len);
			pMsgBox += len;
		}
		{ //LoadingAd
			BYTE* pLoadingAd = pMsgBox;
			Write16(pLoadingAd, 0); //len

			Write8(pLoadingAd, 0); //Ver
			Write8(pLoadingAd, 0); //URLLen

			len = pLoadingAd - pMsgBox;
			Set16(pMsgBox, (WORD)len);
			pMsgBox += len;
		}
		{ //TaskAdvAd
			BYTE* pTaskAdvAd = pMsgBox;
			Write16(pTaskAdvAd, 0); //len

			Write8(pTaskAdvAd, 0); //URLLen

			len = pTaskAdvAd - pMsgBox;
			Set16(pMsgBox, (WORD)len);
			pMsgBox += len;
		}
		{ //LoginAd
			BYTE* pLoginAd = pMsgBox;
			Write16(pLoginAd, 0); //len

			Write8(pLoginAd, 0); //URLLen

			len = pLoginAd - pMsgBox;
			Set16(pMsgBox, (WORD)len);
			pMsgBox += len;
		}
		{ //T3Ad
			BYTE* pT3Ad = pMsgBox;
			Write16(pT3Ad, 0); //len

			Write8(pT3Ad, 0); //URLLen1
			Write8(pT3Ad, 0); //URLLen2
			Write8(pT3Ad, 0); //URLLen3
			Write8(pT3Ad, 0); //URLLen4

			len = pT3Ad - pMsgBox;
			Set16(pMsgBox, (WORD)len);
			pMsgBox += len;
		}

		len = pMsgBox - p;
		Set16(p, (WORD)len);
		p += len;
	}

	len = p - buf;
	SendToClient(Client, 596, buf, len, Client->ServerID, FE_GAMESVRD, Client->ConnID, Notify);
}

void NotifySvrConfig(ClientNode* Client) //服务端配置
{

	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;
	
	Write32(p, 5000); //GuildScoreThreshold

	{ //LuckyMatchCfg 
		BYTE* pLuckyMatchCfg = p;
		Write16(pLuckyMatchCfg, 0); //len

		const char Time[50] = "";
		memcpy(pLuckyMatchCfg, Time, 50);
		pLuckyMatchCfg += 50;

		const char Award[50] = "";
		memcpy(pLuckyMatchCfg, Award, 50);
		pLuckyMatchCfg += 50;

		const char StartCondition[50] = "";
		memcpy(pLuckyMatchCfg, StartCondition, 50);
		pLuckyMatchCfg += 50;

		Write32(pLuckyMatchCfg, 0); //LuckyMoney

		const char MatchTitle[50] = "";
		memcpy(pLuckyMatchCfg, MatchTitle, 50);
		pLuckyMatchCfg += 50;


		len = pLuckyMatchCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}

	{ //MsgStoneSysCfg
		BYTE* pMsgStoneSysCfg = p;
		Write16(pMsgStoneSysCfg, 0); //len

		Write8(pMsgStoneSysCfg, 1); //StoneSkillTakeEffect

		{ //SkillStoneCfg
			BYTE* pSkillStoneCfg = pMsgStoneSysCfg;
			Write16(pSkillStoneCfg, 0); //len


			BYTE* pSkillStoneNum = pSkillStoneCfg;
			Write32(pSkillStoneCfg, 0); //SkillStoneNum
			try
			{
				YAML::Node Config = YAML::LoadFile("SingleSkillStoneCfg.yml");
				YAML::Node SingleSkillStoneCfg;
				size_t Num = Config.size();
				for (size_t i = 0; i < Num; i++)
				{
					SingleSkillStoneCfg = Config[i];
					{ //SingleSkillStoneCfg
						BYTE* pSingleSkillStoneCfg = pSkillStoneCfg;
						Write16(pSingleSkillStoneCfg, 0); //len

						Write32(pSingleSkillStoneCfg, SingleSkillStoneCfg["StoneID"].as<int>());
						Write32(pSingleSkillStoneCfg, SingleSkillStoneCfg["ActiveCondVal1"].as<int>());
						Write32(pSingleSkillStoneCfg, SingleSkillStoneCfg["UseCountUpperlimit"].as<int>());
						Write32(pSingleSkillStoneCfg, SingleSkillStoneCfg["ActiveSuccessProb"].as<int>());
						Write32(pSingleSkillStoneCfg, SingleSkillStoneCfg["CoolTime"].as<int>());
						Write32(pSingleSkillStoneCfg, SingleSkillStoneCfg["GenResultVal1"].as<int>());

						len = pSingleSkillStoneCfg - pSkillStoneCfg;
						Set16(pSkillStoneCfg, (WORD)len);
						pSkillStoneCfg += len;
					}
					SingleSkillStoneCfg.reset();
				}
				Set32(pSkillStoneNum, Num);
			}
			catch (const std::exception&)
			{
				return;
			}


			len = pSkillStoneCfg - pMsgStoneSysCfg;
			Set16(pMsgStoneSysCfg, (WORD)len);
			pMsgStoneSysCfg += len;
		}

		Write32(pMsgStoneSysCfg, 0); //Kart2StoneGrooveNum
		/*
m_stMsgStoneSysCfg.m_astKart2StoneGrooveCfg[].m_iKartID
m_stMsgStoneSysCfg.m_astKart2StoneGrooveCfg[].m_iInitStoneGrooveNum
m_stMsgStoneSysCfg.m_astKart2StoneGrooveCfg[].m_aiStoneUseOccasionType[MAX_KART_STONE_GROOVE_NUM]
		*/


		len = pMsgStoneSysCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}


	{ //UITitleDispInfo 标题显示设置
		BYTE* pUITitleDispInfo = p;
		Write16(pUITitleDispInfo, 0); //len

		struct
		{
			bool GameName : 1;
			bool Version : 1;
			bool WorldName : 1;
			bool Ad : 1;
			bool NickName : 1;
			bool Unknown1 : 1;
			bool Unknown2 : 1;
			bool Unknown3 : 1;
		} DisplayBitMap{ 0,0,1,1,1,0,0,0 };
		memcpy(pUITitleDispInfo, &DisplayBitMap, sizeof(DisplayBitMap));
		pUITitleDispInfo += sizeof(DisplayBitMap);

		{ //ADText
			BYTE* pADText = pUITitleDispInfo;
			Write16(pADText, 0); //len

			len = strlen(UITitleDispInfo_ADText.c_str());
			Write8(pADText, (BYTE)len); //TextLen
			memcpy(pADText, UITitleDispInfo_ADText.c_str(), len);
			pADText += len;

			len = pADText - pUITitleDispInfo;
			Set16(pUITitleDispInfo, (WORD)len);
			pUITitleDispInfo += len;
		}

		len = pUITitleDispInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	{ //LoaderTipInfo 
		BYTE* pLoaderTipInfo = p;
		Write16(pLoaderTipInfo, 0); //len

		Write32(pLoaderTipInfo, 0); //Version
		Write8(pLoaderTipInfo, 0); //TipsNum
		//m_stLoaderTipInfo.m_astLoaderTipText[].m_u8TextLen


		len = pLoaderTipInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	{ //MailSysAD
		BYTE* pMailSysAD = p;
		Write16(pMailSysAD, 0); //len

		const char* ADText = "MailSysAD";
		len = strlen(ADText);
		Write16(pMailSysAD, (WORD)len); //TextLen
		memcpy(pMailSysAD, ADText, len);
		pMailSysAD += len;


		len = pMailSysAD - p;
		Set16(p, (WORD)len);
		p += len;
	}

	{ //CheatReportCfg 作弊报告配置
		BYTE* pCheatReportCfg = p;
		Write16(pCheatReportCfg, 0); //len

		Write8(pCheatReportCfg, 0); //ReplayDayNum
		Write8(pCheatReportCfg, 0); //IsReportCheatEnable

		len = pCheatReportCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write8(p, 0); //MaintainableKartNum
	//m_aiMaintainableKartID[]


	Write32(p, 0); //CommonBitSwitch
	Write8(p, 0); //QQKart2ButtonLen

	{ //GuildEnlistCfg 登记配置
		BYTE* pGuildEnlistCfg = p;
		Write16(pGuildEnlistCfg, 0); //len

		Write8(pGuildEnlistCfg, 0); //MinUnloginDay
		Write8(pGuildEnlistCfg, 0); //CdDay
		Write8(pGuildEnlistCfg, 0); //MaxAwardTimeOneDay 

		len = pGuildEnlistCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write8(p, true); //CloseQT
	Write32(p, 0); //QTCommonRoomID
	Write8(p, 0); //WlFetionDayLimit
	Write8(p, 0); //ShowShopIcon
	Write32(p, 0); //TiroRecommendMapNum
	//m_aiTiroRecommendMapIdList[]
	Write16(p, 0); //BoxMutiOpenLimit
	Write8(p, 0); //HallButtonShow
	Write8(p, 0); //HallButtonShowUrlLen
	Write32(p, 0); //EndlessModeBaseScorePerLevel
#ifndef ZingSpeed
	Write32(p, 0); //GetShopNonSaleInfoInterval
	{ //ShuttleRandMap
		BYTE* pShuttleRandMap = p;
		Write16(pShuttleRandMap, 0); //len

		Write16(pShuttleRandMap, 0); //BeginNum
		/*
		for (size_t i = 0; i < n; i++)
		{ //BeginMapList
			BYTE* pBeginMapList = pShuttleRandMap;
			Write16(pBeginMapList, 0); //len

			Write32(pBeginMapList, 0); //MapID
			Write16(pBeginMapList, 0); //BeginIdx
			Write16(pBeginMapList, 0); //EndIdx
			Write8(pBeginMapList, 0); //Reverse
			Write16(pBeginMapList, 0); //BeginCheckPointIdx

			len = pBeginMapList - pShuttleRandMap;
			Set16(pShuttleRandMap, (WORD)len);
			pShuttleRandMap += len;
		}
		*/
		Write16(pShuttleRandMap, 0); //MidNum
		/*
		for (size_t i = 0; i < n; i++)
		{ //MidMapList
			BYTE* pMidMapList = pShuttleRandMap;
			Write16(pMidMapList, 0); //len

			Write32(pMidMapList, 0); //MapID
			Write16(pMidMapList, 0); //BeginIdx
			Write16(pMidMapList, 0); //EndIdx
			Write8(pMidMapList, 0); //Reverse
			Write16(pMidMapList, 0); //BeginCheckPointIdx

			len = pMidMapList - pShuttleRandMap;
			Set16(pShuttleRandMap, (WORD)len);
			pShuttleRandMap += len;
		}
		*/
		Write16(pShuttleRandMap, 0); //EndNum
		/*
		for (size_t i = 0; i < n; i++)
		{ //EndMapList
			BYTE* pEndMapList = pShuttleRandMap;
			Write16(pEndMapList, 0); //len

			Write32(pEndMapList, 0); //MapID
			Write16(pEndMapList, 0); //BeginIdx
			Write16(pEndMapList, 0); //EndIdx
			Write8(pEndMapList, 0); //Reverse
			Write16(pEndMapList, 0); //BeginCheckPointIdx

			len = pEndMapList - pShuttleRandMap;
			Set16(pShuttleRandMap, (WORD)len);
			pShuttleRandMap += len;
		}
		*/
		len = pShuttleRandMap - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write8(p, 0); //HasWeeklyRecommendModeClientInfo
	/*
	for (size_t i = 0; i < n; i++)
	{ //WeeklyRecommendModeClientInfo
		BYTE* pWeeklyRecommendModeClientInfo = p;
		Write16(pWeeklyRecommendModeClientInfo, 0); //len

		Write32(pWeeklyRecommendModeClientInfo, 0); //OpenDate
		Write32(pWeeklyRecommendModeClientInfo, 0); //CloseDate
		Write32(pWeeklyRecommendModeClientInfo, 0); //OpenTime
		Write32(pWeeklyRecommendModeClientInfo, 0); //CloseTime
		Write8(pWeeklyRecommendModeClientInfo, 0); //WeekLimitNum
		Write8(pWeeklyRecommendModeClientInfo, 0); //WeekLimits[]
		Write32(pWeeklyRecommendModeClientInfo, 0); //DesktopSpecialShowFlag
		Write16(pWeeklyRecommendModeClientInfo, 0); //BaseMode
		Write16(pWeeklyRecommendModeClientInfo, 0); //SubMode
		Write32(pWeeklyRecommendModeClientInfo, 0); //SpecialFlag
		Write(pWeeklyRecommendModeClientInfo, 0); //AwardTriggerDesc[]
		Write8(pWeeklyRecommendModeClientInfo, 0); //AwardNum
		Write32(pWeeklyRecommendModeClientInfo, 0); //AwardItemID[]

		len = pWeeklyRecommendModeClientInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	Write32(p, 0); //ReportWeeklyRecommendModeTriggerInfoInterval
	Write32(p, 0); //MaxEnergy
	Write32(p, 0); //N2ORatio
	Write32(p, 0); //PlayerNumRatio[]
	Write32(p, 0); //IsOpenBuf
	Write8(p, 1); //CouponTreasureGameButtonShow
	Write8(p, 1); //NewYearFinancingShow 
	Write32(p, 0); //GuildTeamSignatureReportNumsLimit
	Write32(p, 0); //GetRelationItemMaxTimeout
	Write32(p, 1000); //ClientWaitGameBeginTimeout

#endif

	len = p - buf;
	SendToClient(Client, 800, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}
void NotifySvrConfig2(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write8(p, 0); //HaveTopMapRecord
	/*
	{ //TopMapRecordConfig
		BYTE* pTopMapRecordConfig = p;
		Write16(pTopMapRecordConfig, 0); //len

		Write32(pTopMapRecordConfig, 0); //Version
		Write32(pTopMapRecordConfig, 0); //RecordDisplayLimit
		Write8(pTopMapRecordConfig, 0); //RecordNumber
		for (size_t i = 0; i < n; i++)
		{ //Record
			BYTE* pRecord = pTopMapRecordConfig;
			Write16(pRecord, 0); //len

			Write32(pRecord, 0); //MapId
			Write32(pRecord, 0); //Record
			Write32(pRecord, 0); //Uin
			Write8(pRecord, 0); //WorldId
			Write8(pRecord, 0); //NameLength
			Write8(pRecord, 0); //UrlLength

			len = pRecord - pTopMapRecordConfig;
			Set16(pTopMapRecordConfig, (WORD)len);
			pTopMapRecordConfig += len;
		}

		len = pTopMapRecordConfig - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	Write8(p, 0); //HaveKartRoomPushInfo
	/*
	{ //KartRoomPushInfo
		BYTE* pKartRoomPushInfo = p;
		Write16(pKartRoomPushInfo, 0); //len

		Write32(pKartRoomPushInfo, 0); //Version
		Write16(pKartRoomPushInfo, 0); //PushItemNumber
		for (size_t i = 0; i < n; i++)
		{ //PushItem
			BYTE* pPushItem = pKartRoomPushInfo;
			Write16(pPushItem, 0); //len

			Write32(pPushItem, 0); //KartId
			Write8(pPushItem, 0); //TextLength

			len = pPushItem - pKartRoomPushInfo;
			Set16(pKartRoomPushInfo, (WORD)len);
			pKartRoomPushInfo += len;
		}

		len = pKartRoomPushInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/

	{ //ClickStreamCfg
		BYTE* pClickStreamCfg = p;
		Write16(pClickStreamCfg, 0); //len

		Write8(pClickStreamCfg, 2); //ReportMode

		Write8(pClickStreamCfg, 3); //ContextNum
		Write8(pClickStreamCfg, 1);
		Write8(pClickStreamCfg, 2);
		Write8(pClickStreamCfg, 3);

		Write32(pClickStreamCfg, 100); //MaxNum

		len = pClickStreamCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write8(p, 1); //IsGuildPKOpen
	Write8(p, 1); //IsEightYearsOpen
	Write8(p, 0); //HaveSkatePropGameLogicCfg滑冰道具游戏逻辑配置
	/*
	{ //SkatePropGameLogicCfg
		BYTE* pSkatePropGameLogicCfg = p;
		Write16(pSkatePropGameLogicCfg, 0); //len

		Write32(pSkatePropGameLogicCfg, 0); //PropAddN2ONum
		Write32(pSkatePropGameLogicCfg, 0); //N2OSpeed
		Write32(pSkatePropGameLogicCfg, 0); //ZanAddScoreNum
		Write32(pSkatePropGameLogicCfg, 0); //GetSpecialPropAddCoinNum
		Write32(pSkatePropGameLogicCfg, 0); //SkatePropHitCD
		Write32(pSkatePropGameLogicCfg, 0); //SkatePropHit_CoinSubNum
		Write32(pSkatePropGameLogicCfg, 0); //MaxOneGameLogicGetScoreNum

		len = pSkatePropGameLogicCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/

	Write16(p, 0); //SkatePropShoeNum
	//Write32(p, 0); //SkatePropShoeList[]

	Write16(p, 0); //SkatePropShoeNumForMultiGame
	//Write32(p, 0); //SkatePropShoeListForMultiGame[]

	Write32(p, 1); //AddAngleTime

	const int EMBM_MAX = 47;
	for (size_t i = 0; i < EMBM_MAX; i++)
	{ //ClassicMapInfo
		BYTE* pClassicMapInfo = p;
		Write16(pClassicMapInfo, 0); //len

		Write32(pClassicMapInfo, 0); //MapNums
		//Write32(pClassicMapInfo, 0); //MapIDS[]

		len = pClassicMapInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	
	Write8(p, 0); //OpenPopAds
	Write8(p, 0); //IsCloseSaveKeyTransInfo
	Write8(p, 0); //IsCloseSuperMoneySecondPsw
	Write32(p, 0); //NewMapNum
	/*
	for (size_t i = 0; i < n; i++)
	{ //NewMapTipsCfg
		BYTE* pNewMapTipsCfg = p;
		Write16(pNewMapTipsCfg, 0); //len

		Write32(pNewMapTipsCfg, 0); //Mapid
		Write16(pNewMapTipsCfg, 0); //WordLen

		len = pNewMapTipsCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/

	for(size_t i = 0; i < 16; i++)
	{
		Write8(p, 0); //ClientSwitch[]
	}

	Write8(p, 0); //OpenPwdRedEnvelop 口令红包打开标志
	Write8(p, 0); //IsUseTCLS
	Write8(p, 0); //IsPropTeamMatchShow

	Write32(p, 0); //CfgNums
	/*
	for (size_t i = 0; i < 1; i++)
	{ //CommonItemTopListInfos
		BYTE* pCommonItemTopListInfos = p;
		Write16(pCommonItemTopListInfos, 0); //len

		Write32(pCommonItemTopListInfos, 75827); //ItemID

		Write16(pCommonItemTopListInfos, 1); //ExtendInfoNums
		Write32(pCommonItemTopListInfos, 0); //ExtendInfoForItemGene[]

		Write16(pCommonItemTopListInfos, 1); //UpdateTopListNums
		Write32(pCommonItemTopListInfos, 0); //TopListID[]

		Write32(pCommonItemTopListInfos, 0); //ActiveDate
		Write32(pCommonItemTopListInfos, 0); //InActiveDate
		Write32(pCommonItemTopListInfos, 0); //ActiveTime
		Write32(pCommonItemTopListInfos, 0); //InActiveTime
		Write8(pCommonItemTopListInfos, 1); //UpdateTopList
		Write32(pCommonItemTopListInfos, 0); //ExtendInfoForLastUpdateTime
		Write32(pCommonItemTopListInfos, 0); //DailyTopListExtendInfoID
		Write32(pCommonItemTopListInfos, 0); //UpdateDate

		len = pCommonItemTopListInfos - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	Write8(p, 0); //IsShowBoardAllareaBubble
	Write8(p, 0); //RemindClearSuperMoneyLeftDays
	Write8(p, 0); //RemindClearSuperMoneyLeftHours
	Write32(p, 0); //RemindClearSuperMoneyThreshold
	Write16(p, 0); //RemindClearSuperMoneyInterval
	Write32(p, 0); //HPJMaxAccFuel
	Write32(p, 0); //HPJWildStatusAccelParam
	Write8(p, 0); //SwitchNum
	Write8(p, 1); //UseSign3使用标志3
	Write8(p, 0); //OpenRankedMatchSpeedKing
	Write8(p, 0); //OpenLimitMapCollect
	Write8(p, 0); //HasMoreInfo

	len = p - buf;
	SendToClient(Client, 822, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}
void NotifySvrConfig3(ClientNode* Client)
{
	BYTE *buf=new BYTE[16384]; 
	BYTE* p = buf; size_t len;

	try
	{
		WriteKartPhysParam(p, 0, 0,Client); //NPCKartPhysPara
	}
	catch (const std::exception&)
	{
		return;
	}
	try
	{
		YAML::Node NPCKartAICfg = YAML::LoadFile(".\\Bot\\NPCKartAIPhysParaCfg.yml");
		YAML::Node NPCKartAIPhysCfg = NPCKartAICfg["NPCKartAIPhysParaInfo"];
		size_t Num = NPCKartAIPhysCfg.size();
		//printf("Num:%d", Num);
		const int MAX_NPC_AI_LEVEL_NUM = 12;

		for (size_t i = 0; i < MAX_NPC_AI_LEVEL_NUM; i++)
		{ //NPCKartAIPhysPara
			YAML::Node NPCKartAIPhysParaCfg = NPCKartAIPhysCfg[i]["NPCKartAIPhysPara"];
			BYTE* pNPCKartAIPhysPara = p;
			Write16(pNPCKartAIPhysPara, 0); //len

			Write32(pNPCKartAIPhysPara, NPCKartAIPhysParaCfg["NpcN2OIntervalTime"].as<int>()); //NpcN2OIntervalTime
			Write32(pNPCKartAIPhysPara, NPCKartAIPhysParaCfg["NpcTriggerN2ORate"].as<int>()); //NpcTriggerN2ORate
			Write32(pNPCKartAIPhysPara, NPCKartAIPhysParaCfg["NpcRestCheckTime"].as<int>()); //NpcRestCheckTime
			Write32(pNPCKartAIPhysPara, NPCKartAIPhysParaCfg["NpcFixVelocity"].as<int>()); //NpcFixVelocity
			Write32(pNPCKartAIPhysPara, NPCKartAIPhysParaCfg["NpcFixVelocityRate"].as<int>()); //NpcFixVelocityRate
			Write32(pNPCKartAIPhysPara, NPCKartAIPhysParaCfg["NpcRunDisHulanThreshold"].as<int>()); //NpcRunDisHulanThreshold
			Write32(pNPCKartAIPhysPara, NPCKartAIPhysParaCfg["NpcSJetRate"].as<int>()); //NpcSJetRate
			Write32(pNPCKartAIPhysPara, NPCKartAIPhysParaCfg["NpcTurnAjustDisHulanRate"].as<int>()); //NpcTurnAjustDisHulanRate

			YAML::Node ForwardAccelCfg = NPCKartAIPhysParaCfg["ForwardAccel"];
			size_t ForwardAccelNum = ForwardAccelCfg.size();
			Write8(pNPCKartAIPhysPara, ForwardAccelNum); //ForwardAccelNum
			//printf("Num:%d", ForwardAccelNum);
			for (size_t j = 0; j < ForwardAccelNum; j++)
			{ //ForwardAccel
				BYTE* pForwardAccel = pNPCKartAIPhysPara;
				Write16(pForwardAccel, 0); //len

				Write32(pForwardAccel, ForwardAccelCfg[j]["Key"].as<int>()); //Key
				Write32(pForwardAccel, ForwardAccelCfg[j]["Value"].as<int>()); //Value

				len = pForwardAccel - pNPCKartAIPhysPara;
				Set16(pNPCKartAIPhysPara, (WORD)len);
				pNPCKartAIPhysPara += len;
			}

			YAML::Node BackwardAccelCfg = NPCKartAIPhysParaCfg["BackwardAccel"];
			size_t BackwardAccelNum = BackwardAccelCfg.size();
			Write8(pNPCKartAIPhysPara, BackwardAccelNum); //BackwardAccelNum
			for (size_t j = 0; j < BackwardAccelNum; j++)
			{ //BackwardAccel
				BYTE* pBackwardAccel = pNPCKartAIPhysPara;
				Write16(pBackwardAccel, 0); //len

				Write32(pBackwardAccel, BackwardAccelCfg[j]["Key"].as<int>()); //Key
				Write32(pBackwardAccel, BackwardAccelCfg[j]["Value"].as<int>()); //Value

				len = pBackwardAccel - pNPCKartAIPhysPara;
				Set16(pNPCKartAIPhysPara, (WORD)len);
				pNPCKartAIPhysPara += len;
			}


			Write32(pNPCKartAIPhysPara, NPCKartAIPhysParaCfg["StraightLenThreshold"].as<int>()); //StraightLenThreshold
			Write32(pNPCKartAIPhysPara, NPCKartAIPhysParaCfg["NpcDriftRate"].as<int>()); //NpcDriftRate

			YAML::Node CompensateParamCfg = NPCKartAIPhysParaCfg["CompensateParam"];
			size_t CompensateParamNum = CompensateParamCfg.size();
			Write8(pNPCKartAIPhysPara, CompensateParamNum); //CompensateParamCount

			for (size_t j = 0; j < CompensateParamNum; j++)
			{ //CompensateParam
				BYTE* pCompensateParam = pNPCKartAIPhysPara;
				Write16(pCompensateParam, 0); //len

				Write32(pCompensateParam, CompensateParamCfg[j]["Percent"].as<int>()); //Percent
				Write32(pCompensateParam, CompensateParamCfg[j]["Value"].as<int>()); //Value

				len = pCompensateParam - pNPCKartAIPhysPara;
				Set16(pNPCKartAIPhysPara, (WORD)len);
				pNPCKartAIPhysPara += len;
			}
		
			len = pNPCKartAIPhysPara - p;
			Set16(p, (WORD)len);
			p += len;
			NPCKartAIPhysParaCfg.reset();
		}
	}
	catch (const std::exception&)
	{
		printf(" NPCKartAIPhysParaCfg exception!\n");
		return;
	}

	try
	{
		WriteKartPhysParam(p, 0, 0,Client); //NPCKartPhysPara_NpcPlayer
	}
	catch (const std::exception&)
	{
		return;
	}
	Write8(p, 12); //LevelNum
	try
	{
		YAML::Node NPCPlayerKartAICfg = YAML::LoadFile(".\\Bot\\NPCPlayerKartAIPhysParaCfg.yml");
		YAML::Node NPCPlayerKartAIPhysCfg = NPCPlayerKartAICfg["NPCKartAIPhysParaInfo"];
		size_t Num = NPCPlayerKartAIPhysCfg.size();
		const int MAX_NPC_AI_LEVEL_NUM = 12;
		for (size_t i = 0; i < MAX_NPC_AI_LEVEL_NUM; i++)
		{ //NPCKartAIPhysPara
			BYTE* pNPCKartAIPhysPara_NpcPlayer = p;
			Write16(pNPCKartAIPhysPara_NpcPlayer, 0); //len
			YAML::Node NPCPlayerKartAIPhysParaCfg = NPCPlayerKartAIPhysCfg[i]["NPCKartAIPhysPara"];
			{ //Param

				BYTE* pParam = pNPCKartAIPhysPara_NpcPlayer;
				Write16(pParam, 0); //len

				Write32(pParam, NPCPlayerKartAIPhysParaCfg["NpcN2OIntervalTime"].as<int>()); //NpcN2OIntervalTime
				Write32(pParam, NPCPlayerKartAIPhysParaCfg["NpcTriggerN2ORate"].as<int>()); //NpcTriggerN2ORate
				Write32(pParam, NPCPlayerKartAIPhysParaCfg["NpcRestCheckTime"].as<int>()); //NpcRestCheckTime
				Write32(pParam, NPCPlayerKartAIPhysParaCfg["NpcFixVelocity"].as<int>()); //NpcFixVelocity
				Write32(pParam, NPCPlayerKartAIPhysParaCfg["NpcFixVelocityRate"].as<int>()); //NpcFixVelocityRate
				Write32(pParam, NPCPlayerKartAIPhysParaCfg["NpcRunDisHulanThreshold"].as<int>()); //NpcRunDisHulanThreshold
				Write32(pParam, NPCPlayerKartAIPhysParaCfg["NpcSJetRate"].as<int>()); //NpcSJetRate
				Write32(pParam, NPCPlayerKartAIPhysParaCfg["NpcTurnAjustDisHulanRate"].as<int>()); //NpcTurnAjustDisHulanRate

				YAML::Node ForwardAccelCfg = NPCPlayerKartAIPhysParaCfg["ForwardAccel"];
				size_t ForwardAccelNum = ForwardAccelCfg.size();
				Write8(pParam, ForwardAccelNum); //ForwardAccelNum

				for (size_t j = 0; j < ForwardAccelNum; j++)
				{ //ForwardAccel
					BYTE* pForwardAccel = pParam;
					Write16(pForwardAccel, 0); //len

					Write32(pForwardAccel, ForwardAccelCfg[j]["Key"].as<int>()); //Key
					Write32(pForwardAccel, ForwardAccelCfg[j]["Value"].as<int>()); //Value

					len = pForwardAccel - pParam;
					Set16(pParam, (WORD)len);
					pParam += len;
				}

				YAML::Node BackwardAccelCfg = NPCPlayerKartAIPhysParaCfg["BackwardAccel"];
				size_t BackwardAccelNum = BackwardAccelCfg.size();
				Write8(pParam, BackwardAccelNum); //BackwardAccelNum
				for (size_t j = 0; j < BackwardAccelNum; j++)
				{ //BackwardAccel
					BYTE* pBackwardAccel = pParam;
					Write16(pBackwardAccel, 0); //len

					Write32(pBackwardAccel, BackwardAccelCfg[j]["Key"].as<int>()); //Key
					Write32(pBackwardAccel, BackwardAccelCfg[j]["Value"].as<int>()); //Value

					len = pBackwardAccel - pParam;
					Set16(pParam, (WORD)len);
					pParam += len;
				}


				Write32(pParam, NPCPlayerKartAIPhysParaCfg["StraightLenThreshold"].as<int>()); //StraightLenThreshold
				Write32(pParam, NPCPlayerKartAIPhysParaCfg["NpcDriftRate"].as<int>()); //NpcDriftRate

				YAML::Node CompensateParamCfg = NPCPlayerKartAIPhysParaCfg["CompensateParam"];
				size_t CompensateParamNum = CompensateParamCfg.size();
				Write8(pParam, CompensateParamNum); //CompensateParamCount

				for (size_t j = 0; j < CompensateParamNum; j++)
				{ //CompensateParam
					BYTE* pCompensateParam = pParam;
					Write16(pCompensateParam, 0); //len

					Write32(pCompensateParam, CompensateParamCfg[j]["Percent"].as<int>()); //Percent
					Write32(pCompensateParam, CompensateParamCfg[j]["Value"].as<int>()); //Value

					len = pCompensateParam - pParam;
					Set16(pParam, (WORD)len);
					pParam += len;
				}
				len = pParam - pNPCKartAIPhysPara_NpcPlayer;
				Set16(pNPCKartAIPhysPara_NpcPlayer, (WORD)len);
				pNPCKartAIPhysPara_NpcPlayer += len;
			}
			Write32(pNPCKartAIPhysPara_NpcPlayer, NPCPlayerKartAIPhysParaCfg["N2OStartTime"].as<int>()); //N2OStartTime
			Write32(pNPCKartAIPhysPara_NpcPlayer, NPCPlayerKartAIPhysParaCfg["NpcN2OMaxCount"].as<int>()); //NpcN2OMaxCount
			Write32(pNPCKartAIPhysPara_NpcPlayer, NPCPlayerKartAIPhysParaCfg["Dis2FirstPlay"].as<int>()); //Dis2FirstPlay
			Write32(pNPCKartAIPhysPara_NpcPlayer, NPCPlayerKartAIPhysParaCfg["LostControlTime"].as<int>()); //LostControlTime
			Write32(pNPCKartAIPhysPara_NpcPlayer, NPCPlayerKartAIPhysParaCfg["LostInterval"].as<int>()); //LostInterval
			Write32(pNPCKartAIPhysPara_NpcPlayer, NPCPlayerKartAIPhysParaCfg["LostControlCount"].as<int>()); //LostControlCount

			len = pNPCKartAIPhysPara_NpcPlayer - p;
			Set16(p, (WORD)len);
			p += len;
			NPCPlayerKartAIPhysParaCfg.reset();
		}
	}
	catch (const std::exception&)
	{
		printf(" NPCPlayerKartAIPhysParaCfg exception!\n");
		return;
	}
	

	try
	{
		WriteKartPhysParam(p, 0, 0,Client); //NPCKartPhysPara_RankedMatch
	}
	catch (const std::exception&)
	{

		return;
	}
	Write8(p, 12); //NPCLevelNum_RankedMatch
	try
	{
		YAML::Node NPCRankedMatchKartAICfg = YAML::LoadFile(".\\Bot\\NPCRankedMatchKartAIPhysParaCfg.yml");
		YAML::Node NPCRankedMatchKartAIPhysCfg = NPCRankedMatchKartAICfg["NPCKartAIPhysParaInfo"];
		size_t Num = NPCRankedMatchKartAIPhysCfg.size();
		const int MAX_NPC_AI_LEVEL_NUM = 12;
		for (size_t i = 0; i < MAX_NPC_AI_LEVEL_NUM; i++)
		{//NPCKartAIPhysPara
			BYTE* pNPCKartAIPhysPara_RankedMatch = p;
			Write16(pNPCKartAIPhysPara_RankedMatch, 0); //len
			YAML::Node NPCRankedMatchKartAIPhysParaCfg = NPCRankedMatchKartAIPhysCfg[i]["NPCKartAIPhysPara"];
			{ //Param
				BYTE* pParam = pNPCKartAIPhysPara_RankedMatch;
				Write16(pParam, 0); //len
				Write32(pParam, NPCRankedMatchKartAIPhysParaCfg["NpcN2OIntervalTime"].as<int>()); //NpcN2OIntervalTime
				Write32(pParam, NPCRankedMatchKartAIPhysParaCfg["NpcTriggerN2ORate"].as<int>()); //NpcTriggerN2ORate
				Write32(pParam, NPCRankedMatchKartAIPhysParaCfg["NpcRestCheckTime"].as<int>()); //NpcRestCheckTime
				Write32(pParam, NPCRankedMatchKartAIPhysParaCfg["NpcFixVelocity"].as<int>()); //NpcFixVelocity
				Write32(pParam, NPCRankedMatchKartAIPhysParaCfg["NpcFixVelocityRate"].as<int>()); //NpcFixVelocityRate
				Write32(pParam, NPCRankedMatchKartAIPhysParaCfg["NpcRunDisHulanThreshold"].as<int>()); //NpcRunDisHulanThreshold
				Write32(pParam, NPCRankedMatchKartAIPhysParaCfg["NpcSJetRate"].as<int>()); //NpcSJetRate
				Write32(pParam, NPCRankedMatchKartAIPhysParaCfg["NpcTurnAjustDisHulanRate"].as<int>()); //NpcTurnAjustDisHulanRate

				YAML::Node ForwardAccelCfg = NPCRankedMatchKartAIPhysParaCfg["ForwardAccel"];
				size_t ForwardAccelNum = ForwardAccelCfg.size();
				Write8(pParam, ForwardAccelNum); //ForwardAccelNum

				for (size_t j = 0; j < ForwardAccelNum; j++)
				{ //ForwardAccel
					BYTE* pForwardAccel = pParam;
					Write16(pForwardAccel, 0); //len

					Write32(pForwardAccel, ForwardAccelCfg[j]["Key"].as<int>()); //Key
					Write32(pForwardAccel, ForwardAccelCfg[j]["Value"].as<int>()); //Value

					len = pForwardAccel - pParam;
					Set16(pParam, (WORD)len);
					pParam += len;
				}

				YAML::Node BackwardAccelCfg = NPCRankedMatchKartAIPhysParaCfg["BackwardAccel"];
				size_t BackwardAccelNum = BackwardAccelCfg.size();
				Write8(pParam, BackwardAccelNum); //BackwardAccelNum
				for (size_t j = 0; j < BackwardAccelNum; j++)
				{ //BackwardAccel
					BYTE* pBackwardAccel = pParam;
					Write16(pBackwardAccel, 0); //len

					Write32(pBackwardAccel, BackwardAccelCfg[j]["Key"].as<int>()); //Key
					Write32(pBackwardAccel, BackwardAccelCfg[j]["Value"].as<int>()); //Value

					len = pBackwardAccel - pParam;
					Set16(pParam, (WORD)len);
					pParam += len;
				}


				Write32(pParam, NPCRankedMatchKartAIPhysParaCfg["StraightLenThreshold"].as<int>()); //StraightLenThreshold
				Write32(pParam, NPCRankedMatchKartAIPhysParaCfg["NpcDriftRate"].as<int>()); //NpcDriftRate

				YAML::Node CompensateParamCfg = NPCRankedMatchKartAIPhysParaCfg["CompensateParam"];
				size_t CompensateParamNum = CompensateParamCfg.size();
				Write8(pParam, CompensateParamNum); //CompensateParamCount

				for (size_t j = 0; j < CompensateParamNum; j++)
				{ //CompensateParam
					BYTE* pCompensateParam = pParam;
					Write16(pCompensateParam, 0); //len

					Write32(pCompensateParam, CompensateParamCfg[j]["Percent"].as<int>()); //Percent
					Write32(pCompensateParam, CompensateParamCfg[j]["Value"].as<int>()); //Value

					len = pCompensateParam - pParam;
					Set16(pParam, (WORD)len);
					pParam += len;
				}
				len = pParam - pNPCKartAIPhysPara_RankedMatch;
				Set16(pNPCKartAIPhysPara_RankedMatch, (WORD)len);
				pNPCKartAIPhysPara_RankedMatch += len;
			}
			Write32(pNPCKartAIPhysPara_RankedMatch, NPCRankedMatchKartAIPhysParaCfg["N2OStartTime"].as<int>()); //N2OStartTime
			Write32(pNPCKartAIPhysPara_RankedMatch, NPCRankedMatchKartAIPhysParaCfg["NpcN2OMaxCount"].as<int>()); //NpcN2OMaxCount
			Write32(pNPCKartAIPhysPara_RankedMatch, NPCRankedMatchKartAIPhysParaCfg["Dis2FirstPlay"].as<int>()); //Dis2FirstPlay
			Write32(pNPCKartAIPhysPara_RankedMatch, NPCRankedMatchKartAIPhysParaCfg["LostControlTime"].as<int>()); //LostControlTime
			Write32(pNPCKartAIPhysPara_RankedMatch, NPCRankedMatchKartAIPhysParaCfg["LostInterval"].as<int>()); //LostInterval
			Write32(pNPCKartAIPhysPara_RankedMatch, NPCRankedMatchKartAIPhysParaCfg["LostControlCount"].as<int>()); //LostControlCount

			len = pNPCKartAIPhysPara_RankedMatch - p;
			Set16(p, (WORD)len);
			p += len;
			NPCRankedMatchKartAIPhysParaCfg.reset();
		}
	}
	catch (const std::exception&)
	{
		printf(" NPCRankedMatchKartAIPhysParaCfg exception!\n");
		return;
	}





	Write32(p, 0x0003BC27); //SwitchFlag1
	Write16(p, 60); //MaxQuickLerpThrehold
	Write16(p, 10); //QuickLerpStepCnts
	Write16(p, 12); //LerpSynccpFrequence

	Write16(p, 0); //ClientItemOpenTypeNum
	/*
	for (size_t i = 0; i < n; i++)
	{ //ClientItemOpenCfg
		BYTE* pClientItemOpenCfg = p;
		Write16(pClientItemOpenCfg, 0); //len

		Write16(pClientItemOpenCfg, 0); //OpenType
		Write8(pClientItemOpenCfg, 0); //ItemNum
		Write32(pClientItemOpenCfg, 0); //ItemList[]

		len = pClientItemOpenCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/

	Write8(p, 1); //OtherNum
	for (size_t i = 0; i < 1; i++)
	{ //CollisionPowerOtherInfo
		BYTE* pCollisionPowerOtherInfo = p;
		Write16(pCollisionPowerOtherInfo, 0); //len

		Write32(pCollisionPowerOtherInfo, 0); //Power
		Write32(pCollisionPowerOtherInfo, 100); //Ratio
		Write32(pCollisionPowerOtherInfo, 0); //Add

		len = pCollisionPowerOtherInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write32(p, 400); //CollisionMinPower
	Write32(p, 2900); //ItemExtendLimit
	Write32(p, 50); //ChattingTalkLevelLimit
	Write32(p, 0); //ChattingSpecialOp

	Write8(p, 0); //ForbidMapNum
	//Write32(p, 0); //ForbidMap[]

	Write32(p, 20000); //MaxBuySpeedNum

	Write8(p, 0); //ClientItemIconNum
	/*
	for (size_t i = 0; i < n; i++)
	{ //ClientIconCfg
		BYTE* pClientIconCfg = p;
		Write16(pClientIconCfg, 0); //len

		Write32(pClientIconCfg, 0); //ItemID
		Write8(pClientIconCfg, 0); //IconPathLen

		len = pClientIconCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/

	Write8(p, 0); //TDCBlackCarNum
	//Write32(p, 0); //TDCBlackCar[]

	Write8(p, 0); //TDCBlackCarTypeNum
	//Write32(p, 0); //TDCBlackCarType[]

	Write8(p, 0); //TDCBlackCarType2ndNum
	//Write32(p, 0); //TDCBlackCarType2nd[]

	{ //ClientFrameRateCfg客户端帧率配置
		BYTE* pClientFrameRateCfg = p;
		Write16(pClientFrameRateCfg, 0); //len

		Write32(pClientFrameRateCfg, 0); //MinFrameRate 改0生效45帧
		Write32(pClientFrameRateCfg, 60000); //MaxFrameRate
		Write32(pClientFrameRateCfg, 10); //FrameStep
		Write32(pClientFrameRateCfg, 0); //CurrentFrameRate

		len = pClientFrameRateCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write8(p, 16); //ReportFrameRateValue
	Write16(p, 10); //FrameOpSpan
	Write8(p, 0); //VideoSwitch

	Write8(p, 0); //KartRefitCardTypeNum
	/*
	for (size_t i = 0; i < 1; i++)
	{ //KartRefitCardCfg
		BYTE* pKartRefitCardCfg = p;
		Write16(pKartRefitCardCfg, 0); //len

		Write32(pKartRefitCardCfg, 0); //RefitCardID
		Write8(pKartRefitCardCfg, 1); //EffectNum
		for (size_t i = 0; i < 1; i++)
		{ //RefitCardEffect
			BYTE* pRefitCardEffect = pKartRefitCardCfg;
			Write16(pRefitCardEffect, 0); //len

			Write8(pRefitCardEffect, 0); //RefitID
			Write8(pRefitCardEffect, 0); //ModifyValue

			len = pRefitCardEffect - pKartRefitCardCfg;
			Set16(pKartRefitCardCfg, (WORD)len);
			pKartRefitCardCfg += len;
		}
		Write8(pKartRefitCardCfg, 0); //KartNum
		//Write32(pKartRefitCardCfg, 0); //KartList[]

		len = pKartRefitCardCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/

	len = p - buf;
	SendToClient(Client, 25066, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
	delete[] buf;
}


void NotifySpeed2Cfg(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //MapEffectMaskNum
	/*
	for (size_t i = 0; i < 0; i++)
	{ //MapEffectMask
		BYTE* pMapEffectMask = p;
		Write16(pMapEffectMask, 0); //len

		Write16(pMapEffectMask, 0); //MapID
		Write32(pMapEffectMask, 0); //EffectMask

		len = pMapEffectMask - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	Write8(p, 0); //Speed2ShopLimit
	Write32(p, 127); //OpenFlag

	len = p - buf;
	SendToClient(Client, 11358, buf, len, Client->ServerID, FE_GAMESVRD, Client->ConnID, Notify);
}

void NotifyTopUIItemInfo(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin

	Write16(p, 2); //Num
	for (size_t i = 0; i < 2; i++)
	{ //TopUIItemInfo
		BYTE* pTopUIItemInfo = p;
		Write16(pTopUIItemInfo, 0); //len

		Write8(pTopUIItemInfo, 0); //Type
		Write16(pTopUIItemInfo, 43); //ID
		Write16(pTopUIItemInfo, 0); //Tag
		Write16(pTopUIItemInfo, 0); //NameLen
		Write16(pTopUIItemInfo, 0); //PrompLen

		len = pTopUIItemInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	{ //RecommendModeInfo
		BYTE* pRecommendModeInfo = p;
		Write16(pRecommendModeInfo, 0); //len

		Write16(pRecommendModeInfo, 0); //ModeNum
		/*
		for (size_t i = 0; i < n; i++)
		{ //ModeInfo
			BYTE* pModeInfo = pRecommendModeInfo;
			Write16(pModeInfo, 0); //len

			Write16(pModeInfo, 0); //ModeID
			Write16(pModeInfo, 0); //Status
			Write32(pModeInfo, 0); //Privige
			Write16(pModeInfo, 0); //PrompLen

			len = pModeInfo - pRecommendModeInfo;
			Set16(pRecommendModeInfo, (WORD)len);
			pRecommendModeInfo += len;
		}
		*/
		len = pRecommendModeInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write8(p, 0); //Count
	/*
	for (size_t i = 0; i < n; i++)
	{ //EntryList
		BYTE* pEntryList = p;
		Write16(pEntryList, 0); //len

		Write8(pEntryList, 0); //Type
		Write8(pEntryList, 0); //Status
		Write16(pEntryList, 0); //PromptLen
		Write8(pEntryList, 0); //Tag
		Write8(pEntryList, 0); //Icon
		Write8(pEntryList, 0); //Kind
		Write8(pEntryList, 0); //Privilige
		Write8(pEntryList, 0); //IsTodayOpen
		Write8(pEntryList, 0); //SetType
		Write8(pEntryList, 0); //EmbedType
		Write8(pEntryList, 0); //LoginWindow

		len = pEntryList - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	Write8(p, 0); //SetNum
	/*
	for (size_t i = 0; i < n; i++)
	{ //EntrySet
		BYTE* pEntrySet = p;
		Write16(pEntrySet, 0); //len

		Write8(pEntrySet, 0); //Count
		for (size_t i = 0; i < n; i++)
		{ //EntryList
			BYTE* pEntryList = pEntrySet;
			Write16(pEntryList, 0); //len

			Write8(pEntryList, 0); //Type
			Write8(pEntryList, 0); //Status
			Write16(pEntryList, 0); //PromptLen
			Write8(pEntryList, 0); //Tag
			Write8(pEntryList, 0); //Icon
			Write8(pEntryList, 0); //Kind
			Write8(pEntryList, 0); //Privilige
			Write8(pEntryList, 0); //IsTodayOpen
			Write8(pEntryList, 0); //SetType
			Write8(pEntryList, 0); //EmbedType
			Write8(pEntryList, 0); //LoginWindow

			len = pEntryList - pEntrySet;
			Set16(pEntrySet, (WORD)len);
			pEntrySet += len;
		}

		len = pEntrySet - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	Write8(p, 0); //MouseOverNum
	/*
	for (size_t i = 0; i < n; i++)
	{ //MouseOverTipsCfg
		BYTE* pMouseOverTipsCfg = p;
		Write16(pMouseOverTipsCfg, 0); //len

		Write16(pMouseOverTipsCfg, 0); //ID
		Write16(pMouseOverTipsCfg, 0); //PrompLen

		len = pMouseOverTipsCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/

	len = p - buf;
	SendToClient(Client, 25116, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void NotifyRedPointInfo(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	Write8(p, 0); //RedPointNum
	/*
	for (size_t i = 0; i < n; i++)
	{ //RedPointInfo
		BYTE* pRedPointInfo = p;
		Write16(pRedPointInfo, 0); //len

		Write8(pRedPointInfo, 0); //Type
		Write8(pRedPointInfo, 0); //Status

		len = pRedPointInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	Write8(p, 1); //All
	Write8(p, 0); //IsNeedPlayVideoGuid

	len = p - buf;
	SendToClient(Client, 25114, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void RequestGetActivityCenterInfo(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	ResponseGetActivityCenterInfo(Client);
}
void ResponseGetActivityCenterInfo(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	Write32(p, 0); //TotalActivity
	Write32(p, 0); //CurrentWeekActivity
	Write32(p, 0); //LastWeekActivity
	Write32(p, 0); //CurrentDayActivity
	Write32(p, 0); //ActivityAppellcation
	Write32(p, 0); //ActivityLevel
	Write32(p, 0); //NextLevelActivity
	{ //DailyActivityBox
		BYTE* pDailyActivityBox = p;
		Write16(pDailyActivityBox, 0); //len

		Write32(pDailyActivityBox, 0); //Day
		Write32(pDailyActivityBox, 0); //BoxNum
		/*
		for (size_t i = 0; i < n; i++)
		{ //ActivityBox
			BYTE* pActivityBox = pDailyActivityBox;
			Write16(pActivityBox, 0); //len

			Write32(pActivityBox, 0); //BoxLevel
			Write32(pActivityBox, 0); //BoxType
			Write32(pActivityBox, 0); //ActivityType
			Write32(pActivityBox, 0); //NeedActivityNum
			Write32(pActivityBox, 0); //BoxStatus
			Write32(pActivityBox, 0); //BoxID
			for (size_t i = 0; i < n; i++)
			{ //Award
				BYTE* pAward = pActivityBox;
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

				len = pAward - pActivityBox;
				Set16(pActivityBox, (WORD)len);
				pActivityBox += len;
			}
			{ //PreviewAward
				BYTE* pPreviewAward = pActivityBox;
				Write16(pPreviewAward, 0); //len

				Write32(pPreviewAward, 0); //SuperMoney
				Write32(pPreviewAward, 0); //Coupons
				Write16(pPreviewAward, 0); //ItemNum
				Write32(pPreviewAward, 0); //ItemID[]

				len = pPreviewAward - pActivityBox;
				Set16(pActivityBox, (WORD)len);
				pActivityBox += len;
			}
			Write32(pActivityBox, 0); //PresetBoxID
			Write8(pActivityBox, 0); //HasActiveAward

			len = pActivityBox - pDailyActivityBox;
			Set16(pDailyActivityBox, (WORD)len);
			pDailyActivityBox += len;
		}
		*/
		len = pDailyActivityBox - p;
		Set16(p, (WORD)len);
		p += len;
	}
	{ //ActivityTaskCfg
		BYTE* pActivityTaskCfg = p;
		Write16(pActivityTaskCfg, 0); //len

		Write32(pActivityTaskCfg, 0); //TabNum
		/*
		for (size_t i = 0; i < n; i++)
		{ //ActivityTaskTab
			BYTE* pActivityTaskTab = pActivityTaskCfg;
			Write16(pActivityTaskTab, 0); //len

			Write32(pActivityTaskTab, 0); //TabOrder
			Write32(pActivityTaskTab, 0); //TabType
			Write32(pActivityTaskTab, 0); //Show
			Write32(pActivityTaskTab, 0); //TaskNum
			for (size_t i = 0; i < n; i++)
			{ //ActivityTask
				BYTE* pActivityTask = pActivityTaskTab;
				Write16(pActivityTask, 0); //len

				Write32(pActivityTask, 0); //TaskID
				Write32(pActivityTask, 0); //ActivityAward
				Write16(pActivityTask, 0); //ChildTaskNum
				Write32(pActivityTask, 0); //ChildTaskID[]

				len = pActivityTask - pActivityTaskTab;
				Set16(pActivityTaskTab, (WORD)len);
				pActivityTaskTab += len;
			}

			len = pActivityTaskTab - pActivityTaskCfg;
			Set16(pActivityTaskCfg, (WORD)len);
			pActivityTaskCfg += len;
		}
		*/
		len = pActivityTaskCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write8(p, 0); //BCNum
	/*
	for (size_t i = 0; i < n; i++)
	{ //BC
		BYTE* pBC = p;
		Write16(pBC, 0); //len

		Write16(pBC, 0); //ContentLen

		len = pBC - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	Write32(p, 0); //CurrentWeekActivityUsed
	{ //MultipleTimeCfg
		BYTE* pMultipleTimeCfg = p;
		Write16(pMultipleTimeCfg, 0); //len

		Write32(pMultipleTimeCfg, 0); //BeginTime
		Write32(pMultipleTimeCfg, 0); //EndTime
		Write16(pMultipleTimeCfg, 0); //MultiValue

		len = pMultipleTimeCfg - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write32(p, 0); //CurrentWeekActivityForLotto
	Write8(p, 0); //LottoItemNum
	//Write32(p, 0); //LottoItemID[]

	len = p - buf;
	SendToClient(Client, 24029, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestC2GSign3Operate(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);
	UCHAR OperateType = Read8(Body);
	
	ResponseC2GSign3Operate(Client, OperateType);
	
	
}
void ResponseC2GSign3Operate(ClientNode* Client, UCHAR OperateType)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	Write16(p, 0); //ResultID
	Write8(p, 0); //ReasonLen
	Write8(p, OperateType); //OperateType
	Write8(p, 0); //HasSign3Info
	/*
	for (size_t i = 0; i < n; i++)
	{ //Sign3Info
		BYTE* pSign3Info = p;
		Write16(pSign3Info, 0); //len

		Write32(pSign3Info, 0); //BeginDate
		Write32(pSign3Info, 0); //EndDate
		Write8(pSign3Info, 0); //SignNum
		Write8(pSign3Info, 0); //CanSign
		Write8(pSign3Info, 0); //AwardNum
		for (size_t i = 0; i < n; i++)
		{ //Sign2Award
			BYTE* pSign2Award = pSign3Info;
			Write16(pSign2Award, 0); //len

			{ //Award
				BYTE* pAward = pSign2Award;
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

				len = pAward - pSign2Award;
				Set16(pSign2Award, (WORD)len);
				pSign2Award += len;
			}
			Write16(pSign2Award, 0); //AwardTimes
			Write8(pSign2Award, 0); //HighGrade
			Write8(pSign2Award, 0); //FuncDes

			len = pSign2Award - pSign3Info;
			Set16(pSign3Info, (WORD)len);
			pSign3Info += len;
		}
		Write32(pSign3Info, 0); //SpecailAwardBeginDate
		Write32(pSign3Info, 0); //SpecailAwardEndDate
		{ //SpecialAward
			BYTE* pSpecialAward = pSign3Info;
			Write16(pSpecialAward, 0); //len

			Write32(pSpecialAward, 0); //Exp
			Write32(pSpecialAward, 0); //Money
			Write32(pSpecialAward, 0); //SuperMoney
			Write16(pSpecialAward, 0); //ItemNum
			for (size_t i = 0; i < n; i++)
			{ //ItemInfo
				BYTE* pItemInfo = pSpecialAward;
				Write16(pItemInfo, 0); //len

				Write32(pItemInfo, 0); //ItemID
				Write32(pItemInfo, 0); //ItemNum
				Write32(pItemInfo, 0); //AvailPeriod
				Write8(pItemInfo, 0); //Status
				WriteUn(pItemInfo, 0); //ObtainTime
				Write32(pItemInfo, 0); //OtherAttribute
				Write16(pItemInfo, 0); //ItemType

				len = pItemInfo - pSpecialAward;
				Set16(pSpecialAward, (WORD)len);
				pSpecialAward += len;
			}
			Write32(pSpecialAward, 0); //Coupons
			Write32(pSpecialAward, 0); //GuildPoint
			Write32(pSpecialAward, 0); //LuckMoney
			Write8(pSpecialAward, 0); //ExtendInfoNum
			for (size_t i = 0; i < n; i++)
			{ //ExtendInfoAward
				BYTE* pExtendInfoAward = pSpecialAward;
				Write16(pExtendInfoAward, 0); //len

				Write16(pExtendInfoAward, 0); //Key
				Write32(pExtendInfoAward, 0); //AddValue
				Write32(pExtendInfoAward, 0); //TotalValue
				Write8(pExtendInfoAward, 0); //ShowPriority
				Write16(pExtendInfoAward, 0); //BuyNeedScore
				Write8(pExtendInfoAward, 0); //OneMatchMaxNum

				len = pExtendInfoAward - pSpecialAward;
				Set16(pSpecialAward, (WORD)len);
				pSpecialAward += len;
			}
			Write32(pSpecialAward, 0); //SpeedCoin

			len = pSpecialAward - pSign3Info;
			Set16(pSign3Info, (WORD)len);
			pSign3Info += len;
		}
		Write8(pSign3Info, 0); //SpecialAwardState
		Write8(pSign3Info, 0); //IsSpecailAwardRemind
		Write8(pSign3Info, 0); //TipsLen
		Write32(pSign3Info, 0); //SpecialAwardID
		Write8(pSign3Info, 0); //LabelNum
		Write8(pSign3Info, 0); //GotLabelNum
		Write8(pSign3Info, 0); //FinalAwardState
		{ //FinalAward
			BYTE* pFinalAward = pSign3Info;
			Write16(pFinalAward, 0); //len

			Write32(pFinalAward, 0); //Exp
			Write32(pFinalAward, 0); //Money
			Write32(pFinalAward, 0); //SuperMoney
			Write16(pFinalAward, 0); //ItemNum
			for (size_t i = 0; i < n; i++)
			{ //ItemInfo
				BYTE* pItemInfo = pFinalAward;
				Write16(pItemInfo, 0); //len

				Write32(pItemInfo, 0); //ItemID
				Write32(pItemInfo, 0); //ItemNum
				Write32(pItemInfo, 0); //AvailPeriod
				Write8(pItemInfo, 0); //Status
				WriteUn(pItemInfo, 0); //ObtainTime
				Write32(pItemInfo, 0); //OtherAttribute
				Write16(pItemInfo, 0); //ItemType

				len = pItemInfo - pFinalAward;
				Set16(pFinalAward, (WORD)len);
				pFinalAward += len;
			}
			Write32(pFinalAward, 0); //Coupons
			Write32(pFinalAward, 0); //GuildPoint
			Write32(pFinalAward, 0); //LuckMoney
			Write8(pFinalAward, 0); //ExtendInfoNum
			for (size_t i = 0; i < n; i++)
			{ //ExtendInfoAward
				BYTE* pExtendInfoAward = pFinalAward;
				Write16(pExtendInfoAward, 0); //len

				Write16(pExtendInfoAward, 0); //Key
				Write32(pExtendInfoAward, 0); //AddValue
				Write32(pExtendInfoAward, 0); //TotalValue
				Write8(pExtendInfoAward, 0); //ShowPriority
				Write16(pExtendInfoAward, 0); //BuyNeedScore
				Write8(pExtendInfoAward, 0); //OneMatchMaxNum

				len = pExtendInfoAward - pFinalAward;
				Set16(pFinalAward, (WORD)len);
				pFinalAward += len;
			}
			Write32(pFinalAward, 0); //SpeedCoin

			len = pFinalAward - pSign3Info;
			Set16(pSign3Info, (WORD)len);
			pSign3Info += len;
		}
		Write32(pSign3Info, 0); //SeasonBeginDate
		Write32(pSign3Info, 0); //SeasonEndDate

		len = pSign3Info - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	Write8(p, 0); //SignNum
	Write8(p, 0); //HasAward
	/*
	for (size_t i = 0; i < n; i++)
	{ //Award
		BYTE* pAward = p;
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

		len = pAward - p;
		Set16(p, (WORD)len);
		p += len;
	}
	*/
	Write8(p, 0); //LabelNum

	len = p - buf;
	SendToClient(Client, 1401, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}


void RequestHyperSpaceJumboGetCfg(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);
	UCHAR CfgType = Read8(Body);

	ResponseHyperSpaceJumboGetCfg(Client, CfgType);
}

void ResponseHyperSpaceJumboGetCfg(ClientNode* Client, UCHAR CfgType)
{
	const char* buf = "\x00\x00\x27\x11\x00\x00\x00\x00\x00\x00\x00\x03\xa9\x80\x00\x00\x00\x00\x6a\x63\x00\x00\x5e\x8e\x00\x00\x7b\x56\x00\x00\x7e\x97\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x11\x00\x00\x00\x00\x00\x11\x00\x00\x00\x10\x00\x00\x00\x06\x00\x00\x00\x10\x00\x00\x00\x06\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x10\x00\x00\x22\x94\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x10\x00\x00\x22\x94\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x69\x6e";
	SendToClient(Client, 24202, (BYTE*)buf, 230, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestTimerChallenge2ndMoreHallInfo(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	ResponseTimerChallenge2ndMoreHallInfo(Client);
}

void ResponseTimerChallenge2ndMoreHallInfo(ClientNode* Client)
{
	const char* buf = "\x00\x00\x27\x11\x00\x00\x00\x0b\x00\x00\x00\x78\x00\x00\x00\x55\x00\x00\x00\x78\x00\x00\x27\x66\x00\x00\x00\x01\x00\x00\x00\x0f\x00\x00\x00\x05\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x78\x00\x14\x00\x00\x00\x05\x00\x00\x00\x01\x00\x00\x00\x05\x01\x00\x00\x00\x24\x00\x00\x14\x00\x00\x00\x0a\x00\x00\x00\x02\x00\x00\x00\x0a\x01\x00\x00\x00\x47\x00\x00\x14\x00\x00\x00\x0f\x00\x00\x00\x03\x00\x00\x00\x0f\x01\x00\x00\x00\x71\x00\x00\x14\x00\x00\x00\x14\x00\x00\x00\x02\x00\x00\x00\x14\x01\x00\x00\x00\x9a\x00\x00\x14\x00\x00\x00\x19\x00\x00\x00\x07\x00\x00\x00\x19\x01\x00\x00\x00\xc6\x00\x00\x14\x00\x00\x00\x1e\x00\x00\x00\x08\x00\x00\x00\x1e\x01\x00\x00\x00\xf7\x00\x00\x14\x00\x00\x00\x23\x00\x00\x00\x05\x00\x00\x00\x23\x01\x00\x00\x01\x29\x00\x00\x14\x00\x00\x00\x28\x00\x00\x00\x05\x00\x00\x00\x28\x01\x00\x00\x01\x50\x00\x00\x14\x00\x00\x00\x2d\x00\x00\x00\x05\x00\x00\x00\x2d\x01\x00\x00\x01\x85\x00\x00\x14\x00\x00\x00\x32\x00\x00\x00\x05\x00\x00\x00\x32\x01\x00\x00\x01\xb4\x00\x00\x14\x00\x00\x00\x37\x00\x00\x00\x05\x00\x00\x00\x37\x01\x00\x00\x01\xd7\x00\x00\x14\x00\x00\x00\x3c\x00\x00\x00\x05\x00\x00\x00\x3c\x01\x00\x00\x02\x0d\x00\x00\x14\x00\x00\x00\x41\x00\x00\x00\x05\x00\x00\x00\x41\x01\x00\x00\x02\x37\x00\x00\x14\x00\x00\x00\x46\x00\x00\x00\x05\x00\x00\x00\x46\x01\x00\x00\x02\x53\x00\x00\x14\x00\x00\x00\x4b\x00\x00\x00\x05\x00\x00\x00\x4b\x01\x00\x00\x02\x8a\x00\x00\x14\x00\x00\x00\x50\x00\x00\x00\x03\x00\x00\x00\x50\x01\x00\x00\x02\xae\x00\x00\x14\x00\x00\x00\x55\x00\x00\x00\x03\x00\x00\x00\x55\x01\x00\x00\x02\xcb\x00\x00\x14\x00\x00\x00\x5a\x00\x00\x00\x04\x00\x00\x00\x5a\x01\x00\x00\x02\xf3\x00\x00\x14\x00\x00\x00\x5f\x00\x00\x00\x04\x00\x00\x00\x5f\x01\x00\x00\x03\x19\x00\x00\x14\x00\x00\x00\x64\x00\x00\x00\x03\x00\x00\x00\x64\x01\x00\x00\x03\x38\x00\x00\x14\x00\x00\x00\x69\x00\x00\x00\x00\x00\x00\x00\x69\x01\x00\x00\x03\x62\x00\x00\x14\x00\x00\x00\x6e\x00\x00\x00\x00\x00\x00\x00\x6e\x01\x00\x00\x03\x88\x00\x00\x14\x00\x00\x00\x73\x00\x00\x00\x00\x00\x00\x00\x73\x01\x00\x00\x03\xa8\x00\x00\x14\x00\x00\x00\x78\x00\x00\x00\x00\x00\x00\x00\x78\x01\x00\x00\x03\xda\x00\x00\x14\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x05\x00\x00\x14\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x10\x00\x00\x14\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x18\x00\x00\x14\x00\x00\x00\x04\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x1e\x00\x00\x14\x00\x00\x00\x06\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x2b\x00\x00\x14\x00\x00\x00\x07\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x31\x00\x00\x14\x00\x00\x00\x08\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x3a\x00\x00\x14\x00\x00\x00\x09\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x41\x00\x00\x18\x00\x00\x00\x0b\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x4f\x00\x00\x03\xe2\x00\x00\x18\x00\x00\x00\x0c\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x57\x00\x00\x03\xea\x00\x00\x18\x00\x00\x00\x0d\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x60\x00\x00\x03\xf3\x00\x00\x18\x00\x00\x00\x0e\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x68\x00\x00\x03\xfb\x00\x00\x14\x00\x00\x00\x10\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x7a\x00\x00\x14\x00\x00\x00\x11\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x82\x00\x00\x14\x00\x00\x00\x12\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x8b\x00\x00\x14\x00\x00\x00\x13\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x91\x00\x00\x14\x00\x00\x00\x15\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\xa3\x00\x00\x14\x00\x00\x00\x16\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\xaa\x00\x00\x14\x00\x00\x00\x17\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\xb3\x00\x00\x14\x00\x00\x00\x18\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\xbf\x00\x00\x18\x00\x00\x00\x1a\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\xd2\x00\x00\x04\x0a\x00\x00\x18\x00\x00\x00\x1b\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\xde\x00\x00\x04\x15\x00\x00\x18\x00\x00\x00\x1c\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\xe8\x00\x00\x04\x20\x00\x00\x18\x00\x00\x00\x1d\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\xf3\x00\x00\x04\x2b\x00\x00\x14\x00\x00\x00\x1f\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x01\x02\x00\x00\x14\x00\x00\x00\x20\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x01\x0c\x00\x00\x14\x00\x00\x00\x21\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x01\x13\x00\x00\x14\x00\x00\x00\x22\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x01\x20\x00\x00\x14\x00\x00\x00\x24\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x01\x30\x00\x00\x14\x00\x00\x00\x25\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x01\x37\x00\x00\x14\x00\x00\x00\x26\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x01\x3f\x00\x00\x14\x00\x00\x00\x27\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x01\x48\x00\x00\x18\x00\x00\x00\x29\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x01\x59\x00\x00\x04\x36\x00\x00\x18\x00\x00\x00\x2a\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x01\x6c\x00\x00\x04\x49\x00\x00\x18\x00\x00\x00\x2b\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x01\x72\x00\x00\x04\x50\x00\x00\x18\x00\x00\x00\x2c\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x01\x7d\x00\x00\x04\x5b\x00\x00\x14\x00\x00\x00\x2e\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x01\x8c\x00\x00\x14\x00\x00\x00\x2f\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x01\x96\x00\x00\x14\x00\x00\x00\x30\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x01\x9d\x00\x00\x14\x00\x00\x00\x31\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x01\xa7\x00\x00\x14\x00\x00\x00\x33\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x01\xbd\x00\x00\x14\x00\x00\x00\x34\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x01\xc8\x00\x00\x14\x00\x00\x00\x35\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x01\xcd\x00\x00\x14\x00\x00\x00\x36\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x01\xd3\x00\x00\x18\x00\x00\x00\x38\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x01\xe1\x00\x00\x04\x69\x00\x00\x18\x00\x00\x00\x39\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x01\xed\x00\x00\x04\x74\x00\x00\x18\x00\x00\x00\x3a\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x01\xfa\x00\x00\x04\x81\x00\x00\x18\x00\x00\x00\x3b\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x02\x01\x00\x00\x04\x88\x00\x00\x14\x00\x00\x00\x3d\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x02\x13\x00\x00\x14\x00\x00\x00\x3e\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x02\x1b\x00\x00\x14\x00\x00\x00\x3f\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x02\x25\x00\x00\x14\x00\x00\x00\x40\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x02\x2f\x00\x00\x14\x00\x00\x00\x42\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x02\x3c\x00\x00\x14\x00\x00\x00\x43\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x02\x40\x00\x00\x14\x00\x00\x00\x44\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x02\x46\x00\x00\x14\x00\x00\x00\x45\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x02\x4f\x00\x00\x18\x00\x00\x00\x47\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x02\x61\x00\x00\x04\xa0\x00\x00\x18\x00\x00\x00\x48\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x02\x68\x00\x00\x04\xa5\x00\x00\x18\x00\x00\x00\x49\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x02\x77\x00\x00\x04\xb4\x00\x00\x18\x00\x00\x00\x4a\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x02\x80\x00\x00\x04\xbd\x00\x00\x14\x00\x00\x00\x4c\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x02\x92\x00\x00\x14\x00\x00\x00\x4d\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x02\x9b\x00\x00\x14\x00\x00\x00\x4e\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x02\xa2\x00\x00\x14\x00\x00\x00\x4f\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x02\xa9\x00\x00\x14\x00\x00\x00\x51\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x02\xb6\x00\x00\x14\x00\x00\x00\x52\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x02\xba\x00\x00\x14\x00\x00\x00\x53\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x02\xbf\x00\x00\x14\x00\x00\x00\x54\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x02\xc7\x00\x00\x18\x00\x00\x00\x56\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x02\xd6\x00\x00\x04\xca\x00\x00\x18\x00\x00\x00\x57\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x02\xdb\x00\x00\x04\xd0\x00\x00\x18\x00\x00\x00\x58\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x02\xe4\x00\x00\x04\xd9\x00\x00\x18\x00\x00\x00\x59\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x02\xe9\x00\x00\x04\xde\x00\x00\x14\x00\x00\x00\x5b\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x02\xfa\x00\x00\x14\x00\x00\x00\x5c\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x03\x04\x00\x00\x14\x00\x00\x00\x5d\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x03\x09\x00\x00\x14\x00\x00\x00\x5e\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x03\x13\x00\x00\x14\x00\x00\x00\x60\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x03\x1d\x00\x00\x14\x00\x00\x00\x61\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x03\x21\x00\x00\x14\x00\x00\x00\x62\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x03\x2a\x00\x00\x14\x00\x00\x00\x63\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x03\x33\x00\x00\x18\x00\x00\x00\x65\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x03\x43\x00\x00\x04\xef\x00\x00\x18\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x03\x4b\x00\x00\x04\xf7\x00\x00\x18\x00\x00\x00\x67\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x03\x53\x00\x00\x04\xff\x00\x00\x18\x00\x00\x00\x68\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x03\x5a\x00\x00\x05\x08\x00\x00\x14\x00\x00\x00\x6a\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x03\x69\x00\x00\x14\x00\x00\x00\x6b\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x03\x70\x00\x00\x14\x00\x00\x00\x6c\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x03\x7b\x00\x00\x14\x00\x00\x00\x6d\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x03\x7f\x00\x00\x14\x00\x00\x00\x6f\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x03\x8c\x00\x00\x14\x00\x00\x00\x70\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x03\x93\x00\x00\x14\x00\x00\x00\x71\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x03\x97\x00\x00\x14\x00\x00\x00\x72\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x03\xa0\x00\x00\x18\x00\x00\x00\x74\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x03\xb5\x00\x00\x05\x15\x00\x00\x18\x00\x00\x00\x75\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x03\xc4\x00\x00\x05\x26\x00\x00\x18\x00\x00\x00\x76\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x03\xcb\x00\x00\x05\x2d\x00\x00\x18\x00\x00\x00\x77\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x03\xd1\x00\x00\x05\x34\x00\x01\x00\x06\x00\x00\x00\x00\x00\x00\x00\x00\x04\x00\xc2\x20\x45\x39\x35\x30\x33\x42\x46\x39\x44\x31\x37\x30\x43\x31\x32\x42\x33\x45\x42\x44\x44\x33\x38\x37\x34\x30\x42\x41\x41\x45\x33\x45\x00\x42\x68\x74\x74\x70\x3a\x2f\x2f\x64\x6f\x77\x6e\x2e\x71\x71\x2e\x63\x6f\x6d\x2f\x71\x71\x6b\x61\x72\x74\x2f\x66\x75\x6c\x6c\x2f\x54\x69\x6d\x65\x72\x43\x68\x61\x6c\x6c\x65\x6e\x67\x65\x52\x65\x63\x6f\x72\x64\x5f\x70\x75\x74\x6f\x6e\x67\x5f\x6c\x6f\x77\x2e\x73\x70\x64\x01\x00\x46\x00\x00\x00\x00\x00\x00\x27\x3a\x00\x00\x27\x77\x00\x00\x00\x00\x00\x00\x27\x42\x00\x00\x27\x30\x00\x00\x27\x43\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x10\xc6\xd5\xcd\xa8\xa1\xa4\xbc\xab\xcf\xde\xcc\xf4\xd5\xbd\xd5\xdf\x00\x00\x00\xc3\x20\x36\x43\x37\x32\x33\x39\x31\x43\x35\x39\x30\x34\x30\x46\x45\x31\x46\x41\x41\x32\x45\x37\x42\x31\x30\x36\x31\x41\x31\x32\x39\x32\x00\x43\x68\x74\x74\x70\x3a\x2f\x2f\x64\x6f\x77\x6e\x2e\x71\x71\x2e\x63\x6f\x6d\x2f\x71\x71\x6b\x61\x72\x74\x2f\x66\x75\x6c\x6c\x2f\x54\x69\x6d\x65\x72\x43\x68\x61\x6c\x6c\x65\x6e\x67\x65\x52\x65\x63\x6f\x72\x64\x5f\x70\x75\x74\x6f\x6e\x67\x5f\x68\x69\x67\x68\x2e\x73\x70\x64\x01\x00\x46\x00\x00\x00\x00\x00\x00\x27\x3a\x00\x00\x27\x77\x00\x00\x00\x00\x00\x00\x27\x42\x00\x00\x27\x30\x00\x00\x27\x43\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x10\xc6\xd5\xcd\xa8\xa1\xa4\xbc\xab\xcf\xde\xcc\xf4\xd5\xbd\xd5\xdf\x00\x00\x00\xc3\x20\x37\x37\x34\x31\x39\x46\x38\x41\x44\x38\x42\x46\x44\x41\x44\x34\x42\x44\x37\x35\x30\x31\x42\x34\x34\x41\x46\x44\x37\x45\x31\x39\x00\x43\x68\x74\x74\x70\x3a\x2f\x2f\x64\x6f\x77\x6e\x2e\x71\x71\x2e\x63\x6f\x6d\x2f\x71\x71\x6b\x61\x72\x74\x2f\x66\x75\x6c\x6c\x2f\x54\x69\x6d\x65\x72\x43\x68\x61\x6c\x6c\x65\x6e\x67\x65\x52\x65\x63\x6f\x72\x64\x5f\x63\x68\x65\x73\x68\x65\x6e\x5f\x6c\x6f\x77\x2e\x73\x70\x64\x01\x00\x46\x00\x00\x00\x00\x00\x00\x27\x3a\x00\x00\x27\x77\x00\x00\x00\x00\x00\x00\x27\x42\x00\x00\x27\x30\x00\x00\x27\x43\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x10\xb3\xb5\xc9\xf1\xa1\xa4\xbc\xab\xcf\xde\xcc\xf4\xd5\xbd\xd5\xdf\x00\x00\x00\xc4\x20\x35\x46\x42\x39\x45\x30\x33\x46\x32\x33\x34\x37\x46\x34\x33\x30\x34\x32\x37\x44\x36\x46\x41\x30\x33\x36\x45\x45\x38\x31\x38\x35\x00\x44\x68\x74\x74\x70\x3a\x2f\x2f\x64\x6f\x77\x6e\x2e\x71\x71\x2e\x63\x6f\x6d\x2f\x71\x71\x6b\x61\x72\x74\x2f\x66\x75\x6c\x6c\x2f\x54\x69\x6d\x65\x72\x43\x68\x61\x6c\x6c\x65\x6e\x67\x65\x52\x65\x63\x6f\x72\x64\x5f\x63\x68\x65\x73\x68\x65\x6e\x5f\x68\x69\x67\x68\x2e\x73\x70\x64\x01\x00\x46\x00\x00\x27\x26\x00\x00\x27\x29\x00\x00\x27\x7a\x00\x00\x00\x00\x00\x00\x27\x3b\x00\x00\x27\x3d\x00\x00\x27\x3c\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x10\xb3\xb5\xc9\xf1\xa1\xa4\xbc\xab\xcf\xde\xcc\xf4\xd5\xbd\xd5\xdf\x00\x00\x00\x00\x00\x00\x00\x00\x50\x0f\x01\x00\x06\x00\x00\x00\x00\x03\x03\x59\x04\x00\x84\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\xc1\xd2\xd1\xe6\xb7\xc9\xd0\xd0\x00\x42\xc1\xf7\xbb\xf0\xc1\xfa\xbe\xa7\xb8\xb3\xd3\xe8\xc8\xfc\xb3\xb5\xb7\xc9\xd0\xd0\xb5\xc4\xc4\xdc\xc1\xa6\xa3\xac\xb3\xd6\xd0\xf8\xca\xb1\xbc\xe4\x35\xc3\xeb\xa3\xac\xc0\xe4\xc8\xb4\xca\xb1\xbc\xe4\x31\x35\xc3\xeb\xa3\xac\xca\xb9\xd3\xc3\xb4\xce\xca\xfd\x31\xb4\xce\x01\x00\x00\x00\x00\x00\x00\x00\x09\x01\x00\x00\x00\x00\x00\x00\x00\x13\x88\x00\x00\x3a\x98\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5b\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0b\xc1\xd2\xd1\xe6\xb7\xc9\xd0\xd0\x4c\x76\x32\x00\x16\xc1\xd2\xd1\xe6\xb7\xc9\xd0\xd0\xb5\xc4\xc0\xe4\xc8\xb4\xca\xb1\xbc\xe4\x2d\x35\xc3\xeb\x01\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x13\x88\x00\x00\x27\x10\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5b\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0b\xc1\xd2\xd1\xe6\xb7\xc9\xd0\xd0\x4c\x76\x33\x00\x16\xc1\xd2\xd1\xe6\xb7\xc9\xd0\xd0\xb5\xc4\xb3\xd6\xd0\xf8\xca\xb1\xbc\xe4\x2b\x32\xc3\xeb\x01\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x1b\x58\x00\x00\x27\x10\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5b\x00\x00\x00\x04\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0b\xc1\xd2\xd1\xe6\xb7\xc9\xd0\xd0\x4c\x76\x34\x00\x16\xc1\xd2\xd1\xe6\xb7\xc9\xd0\xd0\xb5\xc4\xca\xb9\xd3\xc3\xb4\xce\xca\xfd\x2b\x31\xb4\xce\x01\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x1b\x58\x00\x00\x27\x10\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x04\x00\x69\x00\x00\x00\xc0\x00\x00\x00\x00\x00\x00\x00\x00\x00\x69\x32\x00\x00\x00\x0a\x00\x08\xb8\xd6\xcc\xfa\xc0\xd7\xc5\xb5\x00\x27\xbf\xc9\xd7\xb0\xb1\xb8\xa1\xbe\xc2\xfa\xb8\xc4\xa1\xbf\x41\xbc\xb6\xc8\xfc\xb3\xb5\xb8\xd6\xcc\xfa\xc0\xd7\xc5\xb5\xbd\xf8\xd0\xd0\xb4\xf3\xb4\xb3\xb9\xd8\x01\x00\x00\x00\x00\x00\x00\x00\x09\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x6c\x00\x00\x00\xc2\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\xc5\xf6\xd7\xb2\xbc\xaf\xc6\xf8\x00\x2a\xb7\xc7\xc6\xaf\xd2\xc6\xd7\xb4\xcc\xac\xcf\xc2\xa3\xac\xc3\xbf\xb4\xce\xd7\xb2\xc7\xbd\xa3\xac\x36\x30\x25\xb8\xc5\xc2\xca\xbb\xf1\xb5\xc3\x37\x30\x25\xbc\xaf\xc6\xf8\x01\x00\x00\x00\x00\x00\xc1\x00\x03\x00\x00\x00\x00\xc3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x84\x00\x00\x00\xc5\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0c\xc6\xf0\xb2\xbd\xb6\xee\xcd\xe2\xb5\xaa\xc6\xf8\x00\x3e\xc6\xf0\xb2\xbd\xc1\xa2\xbf\xcc\xbb\xf1\xb5\xc3\xd2\xbb\xb8\xf6\xb5\xaa\xc6\xf8\xa3\xac\xc7\xd2\x31\x30\xc3\xeb\xc4\xda\xb5\xaa\xc6\xf8\xd7\xee\xb8\xdf\xcb\xd9\xb6\xc8\x2b\x32\x2e\x35\x6b\x6d\x2f\x68\xa3\xac\xb5\xaa\xc6\xf8\xb6\xaf\xc1\xa6\x2b\x35\x01\x00\x00\x00\x00\x00\xc4\x00\x03\x00\x00\x00\x00\xc6\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x67\x00\x00\x00\xc8\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\xb6\xaf\xc1\xa6\xcc\xe1\xc9\xfd\x00\x25\xc3\xbf\xb4\xce\xbd\xf8\xc8\xeb\xc6\xaf\xd2\xc6\xa3\xac\x35\x30\x25\xb8\xc5\xc2\xca\x37\xc3\xeb\xc4\xda\xb5\xaa\xc6\xf8\xb6\xaf\xc1\xa6\x2b\x31\x30\x01\x00\x00\x00\x00\x00\xc7\x00\x03\x00\x00\x00\x00\xc9\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x58\x04\x00\xa3\x00\x00\x00\x05\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\xc4\xdc\xc1\xbf\xca\xb1\xd6\xd3\x00\x61\xc1\xf7\xbb\xf0\xc1\xfa\xbe\xa7\xca\xb9\xc8\xfc\xb5\xc0\xc9\xcf\xc3\xc5\xb1\xe4\xb3\xc9\xcc\xd8\xca\xe2\xca\xb1\xd6\xd3\xc3\xc5\xa3\xac\xcd\xa8\xb9\xfd\xba\xf3\xb4\xb3\xb9\xd8\xca\xb1\xbc\xe4\xb6\xee\xcd\xe2\x2b\x31\x2e\x35\x73\xa3\xac\xb3\xd6\xd0\xf8\xca\xb1\xbc\xe4\x36\xc3\xeb\xa3\xac\xc0\xe4\xc8\xb4\xca\xb1\xbc\xe4\x31\x35\xc3\xeb\xa3\xac\xca\xb9\xd3\xc3\xb4\xce\xca\xfd\x31\xb4\xce\x01\x00\x00\x00\x00\x00\x00\x00\x09\x00\x00\x00\x00\x00\x00\x00\x00\x17\x70\x00\x00\x3a\x98\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5b\x00\x00\x00\x06\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0b\xc4\xdc\xc1\xbf\xca\xb1\xd6\xd3\x4c\x76\x32\x00\x16\xc4\xdc\xc1\xbf\xca\xb1\xd6\xd3\xb5\xc4\xc0\xe4\xc8\xb4\xca\xb1\xbc\xe4\x2d\x35\xc3\xeb\x01\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x17\x70\x00\x00\x27\x10\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5b\x00\x00\x00\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0b\xc4\xdc\xc1\xbf\xca\xb1\xd6\xd3\x4c\x76\x33\x00\x16\xc4\xdc\xc1\xbf\xca\xb1\xd6\xd3\xb5\xc4\xb3\xd6\xd0\xf8\xca\xb1\xbc\xe4\x2b\x33\xc3\xeb\x01\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x23\x28\x00\x00\x27\x10\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5b\x00\x00\x00\x08\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0b\xc4\xdc\xc1\xbf\xca\xb1\xd6\xd3\x4c\x76\x34\x00\x16\xc4\xdc\xc1\xbf\xca\xb1\xd6\xd3\xb5\xc4\xca\xb9\xd3\xc3\xb4\xce\xca\xfd\x2b\x31\xb4\xce\x01\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x23\x28\x00\x00\x27\x10\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x04\x00\x69\x00\x00\x00\xca\x00\x00\x00\x00\x00\x00\x00\x00\x00\xec\x0d\xff\xff\xff\xff\x00\x08\xca\xc9\xbb\xea\xbd\xf0\xbc\xd7\x00\x27\xbf\xc9\xd7\xb0\xb1\xb8\xa1\xbe\xc2\xfa\xb8\xc4\xa1\xbf\x54\xbc\xb6\xc8\xfc\xb3\xb5\xca\xc9\xbb\xea\xbd\xf0\xbc\xd7\xbd\xf8\xd0\xd0\xb4\xf3\xb4\xb3\xb9\xd8\x01\x00\x00\x00\x00\x00\x00\x00\x09\x01\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5a\x00\x00\x00\xcc\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\xd6\xfa\xc1\xa6\xc6\xf0\xc5\xdc\x00\x18\xc3\xbf\xb0\xf4\xc6\xf0\xc5\xdc\xca\xb1\xa3\xac\xb4\xb3\xb9\xd8\xca\xb1\xbc\xe4\x2b\x31\xc3\xeb\x01\x00\x00\x00\x00\x00\xcb\x00\x03\x01\x00\x00\x00\xcd\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x79\x00\x00\x00\xcf\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\xc5\xe7\xc9\xe4\xbc\xd3\xb3\xc9\x00\x37\xca\xb9\xd3\xc3\xcb\xab\xc5\xe7\xa3\xa8\xba\xac\x63\x77\x77\xa1\xa2\x77\x63\x77\xa3\xa9\xba\xf3\xa3\xac\xb4\xb3\xb9\xd8\xca\xb1\xbc\xe4\x2b\x31\xc3\xeb\xa3\xac\xa3\xa8\xc3\xbf\xb0\xf4\xc9\xcf\xcf\xde\x32\xb4\xce\xa3\xa9\x01\x00\x00\x00\x00\x00\xce\x00\x03\x01\x00\x00\x00\xd0\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x00\x00\x00\xd2\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\xbc\xab\xcb\xd9\xcc\xe1\xc9\xfd\x00\x22\xc3\xbf\x33\xb4\xce\xca\xb9\xd3\xc3\xb5\xaa\xc6\xf8\xa3\xac\x38\xc3\xeb\xc4\xda\xc6\xbd\xc5\xdc\xbc\xab\xcb\xd9\xc4\xdc\xc1\xa6\x2b\x38\x01\x00\x00\x00\x00\x00\xd1\x00\x03\x01\x00\x00\x00\xd3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x33\x04\x00\x97\x00\x00\x00\x09\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\xc1\xfa\xbe\xa7\xb4\xc5\xce\xfc\x00\x55\xc0\xa9\xb4\xf3\xb5\xc0\xbe\xdf\xca\xb0\xc8\xa1\xb7\xb6\xce\xa7\xb2\xa2\xc7\xd2\xb3\xd6\xd0\xf8\xca\xb1\xbc\xe4\xc4\xda\xc3\xbf\xc3\xeb\xd4\xf6\xbc\xd3\x32\x30\x25\xb5\xaa\xc6\xf8\xa3\xac\xb3\xd6\xd0\xf8\xca\xb1\xbc\xe4\x36\xc3\xeb\xa3\xac\xc0\xe4\xc8\xb4\xca\xb1\xbc\xe4\x31\x35\xc3\xeb\xa3\xac\xca\xb9\xd3\xc3\xb4\xce\xca\xfd\x31\xb4\xce\x01\x00\x00\x00\x00\x00\x00\x00\x09\x00\x00\x00\x00\x00\x00\x00\x00\x17\x70\x00\x00\x3a\x98\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5b\x00\x00\x00\x0a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0b\xc1\xfa\xbe\xa7\xb4\xc5\xce\xfc\x4c\x76\x32\x00\x16\xc1\xfa\xbe\xa7\xb4\xc5\xce\xfc\xb5\xc4\xc0\xe4\xc8\xb4\xca\xb1\xbc\xe4\x2d\x35\xc3\xeb\x01\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x17\x70\x00\x00\x27\x10\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5b\x00\x00\x00\x0b\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0b\xc1\xfa\xbe\xa7\xb4\xc5\xce\xfc\x4c\x76\x33\x00\x16\xc1\xfa\xbe\xa7\xb4\xc5\xce\xfc\xb5\xc4\xb3\xd6\xd0\xf8\xca\xb1\xbc\xe4\x2b\x33\xc3\xeb\x01\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x23\x28\x00\x00\x27\x10\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5b\x00\x00\x00\x0c\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0b\xc1\xfa\xbe\xa7\xb4\xc5\xce\xfc\x4c\x76\x34\x00\x16\xc1\xfa\xbe\xa7\xb4\xc5\xce\xfc\xb5\xc4\xca\xb9\xd3\xc3\xb4\xce\xca\xfd\x2b\x31\xb4\xce\x01\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x23\x28\x00\x00\x27\x10\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x04\x00\x5d\x00\x00\x00\xd4\x00\x00\x00\x00\x00\x00\x00\x00\x00\x43\xca\x00\x00\x00\x0a\x00\x06\xcc\xec\xbb\xfa\xcf\xdf\x00\x1d\xbf\xc9\xd7\xb0\xb1\xb8\x53\xbc\xb6\xc8\xfc\xb3\xb5\xcc\xec\xbb\xfa\xcf\xdf\xbd\xf8\xd0\xd0\xb4\xf3\xb4\xb3\xb9\xd8\x01\x00\x00\x00\x00\x00\x00\x00\x09\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5e\x00\x00\x00\xd6\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\xbc\xaf\xc6\xf8\xd4\xf6\xc7\xbf\x00\x1c\xc3\xbf\xb4\xce\xbd\xf8\xc8\xeb\xc6\xaf\xd2\xc6\xa3\xac\xc1\xa2\xbf\xcc\xbb\xf1\xb5\xc3\x38\x25\xbc\xaf\xc6\xf8\x01\x00\x00\x00\x00\x00\xd5\x00\x03\x00\x00\x00\x00\xd7\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x58\x00\x00\x00\xd9\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x07\x77\x63\x77\xbc\xab\xcb\xd9\x00\x17\xca\xb9\xd3\xc3\xb5\xaa\xc6\xf8\xbc\xb4\xbf\xc9\xb4\xef\xb5\xbd\x77\x63\x77\xcb\xd9\xb6\xc8\x01\x00\x00\x00\x00\x00\xd8\x00\x03\x00\x00\x00\x00\xda\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x74\x00\x00\x00\xdc\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\xb5\xaa\xc6\xf8\xc7\xbf\xbb\xaf\x00\x32\xbb\xf1\xb5\xc3\xb5\xaa\xc6\xf8\xba\xf3\xa3\xac\x32\x35\x25\xb5\xc4\xb8\xc5\xc2\xca\xb5\xaa\xc6\xf8\xd7\xee\xb8\xdf\xcb\xd9\xb6\xc8\x2b\x32\x2e\x35\x6b\x6d\x2f\x68\xa3\xac\xb3\xd6\xd0\xf8\x36\xc3\xeb\x01\x00\x00\x00\x00\x00\xdb\x00\x03\x00\x00\x00\x00\xdd\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x02\x01\x00\x12\x00\x00\x00\x01\x00\x00\x00\x02\x00\x00\x00\x03\x00\x00\x00\x05\x00\x00\x00\x06\x00\x00\x00\x07\x00\x00\x00\x09\x00\x00\x00\x0a\x00\x00\x00\x0b\x00\x00\x00\x0d\x00\x00\x00\x0e\x00\x00\x00\x0f\x00\x00\x00\x12\x00\x00\x00\x13\x00\x00\x00\x11\x00\x00\x00\x16\x00\x00\x00\x17\x00\x00\x00\x18\x02\xa8\x00\x28\x00\x13\x00\x00\x00\x0a\x03\x00\x00\x00\x01\x00\x00\x00\x02\x00\x00\x00\x03\x00\x13\x00\x00\x00\x0b\x03\x00\x00\x00\x05\x00\x00\x00\x06\x00\x00\x00\x07\x00\x13\x00\x00\x00\x0c\x03\x00\x00\x00\x09\x00\x00\x00\x0a\x00\x00\x00\x0b\x00\x1f\x00\x00\x00\x0d\x06\x00\x00\x00\x0d\x00\x00\x00\x0e\x00\x00\x00\x0f\x00\x00\x00\x11\x00\x00\x00\x12\x00\x00\x00\x13\x00\x13\x00\x00\x00\x0e\x03\x00\x00\x00\x16\x00\x00\x00\x17\x00\x00\x00\x18\x00\x13\x00\x00\x00\x19\x03\x00\x00\x00\x19\x00\x00\x00\x1a\x00\x00\x00\x1b\x00\x1f\x00\x00\x00\x1a\x06\x00\x00\x00\x1d\x00\x00\x00\x1e\x00\x00\x00\x1f\x00\x00\x00\x21\x00\x00\x00\x22\x00\x00\x00\x23\x00\x13\x00\x00\x00\x1b\x03\x00\x00\x00\x25\x00\x00\x00\x26\x00\x00\x00\x27\x00\x13\x00\x00\x00\x1c\x03\x00\x00\x00\x2a\x00\x00\x00\x2b\x00\x00\x00\x2c\x00\x13\x00\x00\x00\x1d\x03\x00\x00\x00\x2e\x00\x00\x00\x2f\x00\x00\x00\x30\x00\x07\x00\x00\x00\x28\x00\x00\x1f\x00\x00\x00\x29\x06\x00\x00\x00\x32\x00\x00\x00\x33\x00\x00\x00\x34\x00\x00\x00\x37\x00\x00\x00\x38\x00\x00\x00\x39\x00\x13\x00\x00\x00\x2a\x03\x00\x00\x00\x3a\x00\x00\x00\x3b\x00\x00\x00\x3c\x00\x13\x00\x00\x00\x2b\x03\x00\x00\x00\x3e\x00\x00\x00\x3f\x00\x00\x00\x40\x00\x13\x00\x00\x00\x2c\x03\x00\x00\x00\x43\x00\x00\x00\x44\x00\x00\x00\x45\x00\x07\x00\x00\x00\x37\x00\x00\x13\x00\x00\x00\x38\x03\x00\x00\x00\x46\x00\x00\x00\x47\x00\x00\x00\x48\x00\x13\x00\x00\x00\x39\x03\x00\x00\x00\x49\x00\x00\x00\x4a\x00\x00\x00\x4b\x00\x13\x00\x00\x00\x3a\x03\x00\x00\x00\x4c\x00\x00\x00\x4d\x00\x00\x00\x4e\x00\x13\x00\x00\x00\x3b\x03\x00\x00\x00\x4f\x00\x00\x00\x50\x00\x00\x00\x51\x00\x07\x00\x00\x00\x46\x00\x00\x13\x00\x00\x00\x47\x03\x00\x00\x00\x5e\x00\x00\x00\x5f\x00\x00\x00\x60\x00\x13\x00\x00\x00\x48\x03\x00\x00\x00\x61\x00\x00\x00\x62\x00\x00\x00\x63\x00\x13\x00\x00\x00\x49\x03\x00\x00\x00\x64\x00\x00\x00\x65\x00\x00\x00\x66\x00\x13\x00\x00\x00\x4a\x03\x00\x00\x00\x67\x00\x00\x00\x68\x00\x00\x00\x69\x00\x13\x00\x00\x00\x55\x03\x00\x00\x00\x6a\x00\x00\x00\x6b\x00\x00\x00\x6c\x00\x07\x00\x00\x00\x56\x00\x00\x13\x00\x00\x00\x57\x03\x00\x00\x00\x6d\x00\x00\x00\x6e\x00\x00\x00\x6f\x00\x13\x00\x00\x00\x58\x03\x00\x00\x00\x70\x00\x00\x00\x71\x00\x00\x00\x72\x00\x13\x00\x00\x00\x59\x03\x00\x00\x00\x73\x00\x00\x00\x74\x00\x00\x00\x75\x00\x07\x00\x00\x00\x64\x00\x00\x13\x00\x00\x00\x65\x03\x00\x00\x00\x82\x00\x00\x00\x83\x00\x00\x00\x84\x00\x13\x00\x00\x00\x66\x03\x00\x00\x00\x85\x00\x00\x00\x86\x00\x00\x00\x87\x00\x07\x00\x00\x00\x67\x00\x00\x07\x00\x00\x00\x68\x00\x00\x0f\x00\x00\x00\x73\x02\x00\x00\x00\x88\x00\x00\x00\x91\x00\x0f\x00\x00\x00\x74\x02\x00\x00\x00\x92\x00\x00\x00\x93\x00\x07\x00\x00\x00\x75\x00\x00\x0f\x00\x00\x00\x76\x02\x00\x00\x00\x8f\x00\x00\x00\x90\x00\x07\x00\x00\x00\x77\x00\x09\x00\x00";
	SendToClient(Client, 24258, (BYTE*)buf, 6682, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestPreGetCommonBoxAward(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	USHORT Type = Read16(Body);
	int AwardID = Read32(Body);
	UCHAR IsShowAllAward = Read8(Body);
	int EchoClient = Read32(Body);

	ResponsePreGetCommonBoxAward(Client, Type);
}

void ResponsePreGetCommonBoxAward(ClientNode* Client, USHORT Type)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	Write16(p, 0); //ResultID
	Write16(p, Type); //Type
	{ //AwardCfgArray
		BYTE* pAwardCfgArray = p;
		Write16(pAwardCfgArray, 0); //len

		Write8(pAwardCfgArray, 1); //ScoreAwardNum
		for (size_t i = 0; i < 1; i++)
		{ //ScoreAwardCfg
			BYTE* pScoreAwardCfg = pAwardCfgArray;
			Write16(pScoreAwardCfg, 0); //len

			Write8(pScoreAwardCfg, 1); //Type
			Write32(pScoreAwardCfg, 0); //StartScore
			{ //AwardInfo
				BYTE* pAwardInfo = pScoreAwardCfg;
				Write16(pAwardInfo, 0); //len

				Write32(pAwardInfo, 0); //Exp
				Write32(pAwardInfo, 0); //Money
				Write32(pAwardInfo, 0); //SuperMoney
				Write16(pAwardInfo, 0); //ItemNum
				for (size_t i = 0; i < 0; i++)
				{ //ItemInfo
					BYTE* pItemInfo = pAwardInfo;
					Write16(pItemInfo, 0); //len

					Write32(pItemInfo, 0); //ItemID
					Write32(pItemInfo, 0); //ItemNum
					Write32(pItemInfo, 0); //AvailPeriod
					Write8(pItemInfo, 0); //Status
					Write32(pItemInfo, 0); //ObtainTime
					Write32(pItemInfo, 0); //OtherAttribute
					Write16(pItemInfo, 0); //ItemType

					len = pItemInfo - pAwardInfo;
					Set16(pAwardInfo, (WORD)len);
					pAwardInfo += len;
				}

				Write32(pAwardInfo, 0); //Coupons
				Write32(pAwardInfo, 0); //GuildPoint
				Write32(pAwardInfo, 0); //LuckMoney

				Write8(pAwardInfo, 0); //ExtendInfoNum
				for (size_t i = 0; i < 0; i++)
				{ //ExtendInfoAward
					BYTE* pExtendInfoAward = pAwardInfo;
					Write16(pExtendInfoAward, 0); //len

					Write16(pExtendInfoAward, 0); //Key
					Write32(pExtendInfoAward, 0); //AddValue
					Write32(pExtendInfoAward, 0); //TotalValue
					Write8(pExtendInfoAward, 0); //ShowPriority
					Write16(pExtendInfoAward, 0); //BuyNeedScore
					Write8(pExtendInfoAward, 0); //OneMatchMaxNum

					len = pExtendInfoAward - pAwardInfo;
					Set16(pAwardInfo, (WORD)len);
					pAwardInfo += len;
				}

				Write32(pAwardInfo, 0); //SpeedCoin

				len = pAwardInfo - pScoreAwardCfg;
				Set16(pScoreAwardCfg, (WORD)len);
				pScoreAwardCfg += len;
			}
			Write8(pScoreAwardCfg, 0); //Status
			Write16(pScoreAwardCfg, 0); //ResultID
			Write16(pScoreAwardCfg, 0); //HasMoreInfo
			/*
			for (size_t i = 0; i < n; i++)
			{ //MoreInfo
				BYTE* pMoreInfo = pScoreAwardCfg;
				Write16(pMoreInfo, 0); //len

				Write16(pMoreInfo, 0); //AlreayGetNum
				Write16(pMoreInfo, 0); //MaxGetNum
				Write32(pMoreInfo, 0); //ItemID
				Write32(pMoreInfo, 0); //TimeStart
				Write32(pMoreInfo, 0); //TimeEnd
				Write32(pMoreInfo, 0); //NextAddNumLeftTime
				Write8(pMoreInfo, 0); //Num
				for (size_t i = 0; i < n; i++)
				{ //ComsumeItemArray
					BYTE* pComsumeItemArray = pMoreInfo;
					Write16(pComsumeItemArray, 0); //len

					Write32(pComsumeItemArray, 0); //ItemID
					Write32(pComsumeItemArray, 0); //StartScore
					Write32(pComsumeItemArray, 0); //DiscountStartScore

					len = pComsumeItemArray - pMoreInfo;
					Set16(pMoreInfo, (WORD)len);
					pMoreInfo += len;
				}
				Write8(pMoreInfo, 0); //ClientParaNum
				Write32(pMoreInfo, 0); //ClientParas[]
				Write32(pMoreInfo, 0); //DiscountTimeStart
				Write32(pMoreInfo, 0); //DiscountTimeEnd
				Write8(pMoreInfo, 0); //DiscountStatus
				Write32(pMoreInfo, 0); //LimitPara
				Write8(pMoreInfo, 0); //ItemExchangeType
				Write8(pMoreInfo, 0); //ItemLabelType
				Write16(pMoreInfo, 0); //ShowPriority
				Write8(pMoreInfo, 0); //Para0
				Write32(pMoreInfo, 0); //LastUpdateTime

				len = pMoreInfo - pScoreAwardCfg;
				Set16(pScoreAwardCfg, (WORD)len);
				pScoreAwardCfg += len;
			}
			*/

			Write32(pScoreAwardCfg, 0); //PosKey
			Write8(pScoreAwardCfg, 0); //AwardIdx
			Write8(pScoreAwardCfg, 0); //LabelStatus

			Write8(pScoreAwardCfg, 0); //ExtraAwardNum
			for (size_t i = 0; i < 0; i++)
			{ //ExtraAwardInfo
				BYTE* pExtraAwardInfo = pScoreAwardCfg;
				Write16(pExtraAwardInfo, 0); //len

				Write32(pExtraAwardInfo, 0); //Exp
				Write32(pExtraAwardInfo, 0); //Money
				Write32(pExtraAwardInfo, 0); //SuperMoney
				Write16(pExtraAwardInfo, 0); //ItemNum
				for (size_t i = 0; i < 0; i++)
				{ //ItemInfo
					BYTE* pItemInfo = pExtraAwardInfo;
					Write16(pItemInfo, 0); //len

					Write32(pItemInfo, 0); //ItemID
					Write32(pItemInfo, 0); //ItemNum
					Write32(pItemInfo, 0); //AvailPeriod
					Write8(pItemInfo, 0); //Status
					Write32(pItemInfo, 0); //ObtainTime
					Write32(pItemInfo, 0); //OtherAttribute
					Write16(pItemInfo, 0); //ItemType

					len = pItemInfo - pExtraAwardInfo;
					Set16(pExtraAwardInfo, (WORD)len);
					pExtraAwardInfo += len;
				}
				Write32(pExtraAwardInfo, 0); //Coupons
				Write32(pExtraAwardInfo, 0); //GuildPoint
				Write32(pExtraAwardInfo, 0); //LuckMoney

				Write8(pExtraAwardInfo, 0); //ExtendInfoNum
				for (size_t i = 0; i < 0; i++)
				{ //ExtendInfoAward
					BYTE* pExtendInfoAward = pExtraAwardInfo;
					Write16(pExtendInfoAward, 0); //len

					Write16(pExtendInfoAward, 0); //Key
					Write32(pExtendInfoAward, 0); //AddValue
					Write32(pExtendInfoAward, 0); //TotalValue
					Write8(pExtendInfoAward, 0); //ShowPriority
					Write16(pExtendInfoAward, 0); //BuyNeedScore
					Write8(pExtendInfoAward, 0); //OneMatchMaxNum

					len = pExtendInfoAward - pExtraAwardInfo;
					Set16(pExtraAwardInfo, (WORD)len);
					pExtraAwardInfo += len;
				}

				Write32(pExtraAwardInfo, 0); //SpeedCoin

				len = pExtraAwardInfo - pScoreAwardCfg;
				Set16(pScoreAwardCfg, (WORD)len);
				pScoreAwardCfg += len;
			}

			len = pScoreAwardCfg - pAwardCfgArray;
			Set16(pAwardCfgArray, (WORD)len);
			pAwardCfgArray += len;
		}
		len = pAwardCfgArray - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write32(p, 0); //AwardID
	Write32(p, 0); //NextClearLeftTime
	Write8(p, 0); //HasMoreInfo
	Write32(p, 0); //Score
	Write16(p, 0); //LeftGetAwardNum
	Write8(p, 0); //Status
	Write8(p, 0); //EnableMergeSameItem
	Write32(p, 0); //TimeStart
	Write32(p, 0); //TimeEnd
	Write32(p, 0); //SCPara
	Write8(p, 0); //IsShowAllAward
	Write16(p, 0); //ValueNum
	//Write32(p, 0); //Values[]
	Write32(p, 0); //EchoClient

	len = p - buf;
	SendToClient(Client, 24465, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}


void RequestAddToMatchQueue(ClientNode* Client, BYTE* Body, size_t BodyLen)
{//请求加入匹配队列？
	BYTE* p = Body;;

	UINT uin = Read32(p);
	UINT time = Read32(p);

	USHORT matchQueueType = Read16(p);
	UINT para1 = Read32(p);
	UCHAR IsAllArea = Read8(p);
	UCHAR paraNum = Read8(p);
	for (size_t i = 0; i < paraNum; i++)
	{
		UINT para = Read32(p);
	}
	int MapID = Read32(p);

	//ResponseAddToMatchQueue(Client, matchQueueType);

	//Client->MapCompatibilityMode = true;
	//Client->EndCheckPoint = 0;
	//Client->TotalRound = 1;
	//Client->Loop = false;

	//Client->MapID = 426;
	//Client->FinishTime = 0;
	//Client->Round = 0;
	//Client->PassedCheckPoint = 0;

	//NotifyMatchResult(Client, matchQueueType);
	
	//NotifyGameBegin(Client, NULL);
	//NotifyKartPhysParam(Client, NULL);
	//NotifyOtherKartStoneInfo(Client);
}

void ResponseAddToMatchQueue(ClientNode* Client, USHORT matchQueueType)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //resultId
	Write8(p, 0); //reasonLen
	Write16(p, matchQueueType); //matchQueueType
	Write32(p, 0); //Para0
	Write8(p, 0); //IsAllArea
	Write32(p, 0); //MapID

	len = p - buf;
	SendToClient(Client, 20079, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void NotifyMatchResult(ClientNode* Client, USHORT matchQueueType)
{
	
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //resultId
	Write16(p, 0); //reasonLen
	Write8(p, matchQueueType); //matchQueueType 0xa是排位队列
	Write8(p, 0); //hasEnterInfo
	for (size_t i = 0; i < 0; i++)
	{ //enterInfo
		BYTE* penterInfo = p;
		Write16(penterInfo, 0); //len 0x42

		{ //addrInfo
			BYTE* paddrInfo = penterInfo;
			Write16(paddrInfo, 0); //len 0x3a

			Write16(paddrInfo, Client->ServerID); //svrId 
			Write32(paddrInfo, inet_addr(IP.c_str())); //svrIP 0xCE5C6C71(4字节整数形式转换ip 注意大小头)
			Write8(paddrInfo, 1); //tcpPortNum 0x3
			Write16(paddrInfo, TcpPort); //tcpPort[] 0x274a 0x274b 0x274c
			Write8(paddrInfo, 1); //udpPortNum 0x1
			Write16(paddrInfo, UdpPort); //udpPort[] 0x274a
			Write8(paddrInfo, 0); //HasMultiIPInfo 0x1
			for (size_t i = 0; i < 0; i++)
			{ //MultiIPInfo
				BYTE* pMultiIPInfo = paddrInfo;
				Write16(pMultiIPInfo, 0); //len 0x27

				Write8(pMultiIPInfo, 0); //IPCount 0x4
				Write32(pMultiIPInfo, 0); //ServerIP[]0xce 5c 6c 71 0xe4 36 f1 3d 0x9e 03 35 70 0x77 e8 f4 6d
				Write8(pMultiIPInfo, 0); //DomainLen 0x13
				//0x64 78 32 70 76 70 2e 73 70 65 65 64 2e 71 71 2e 63 6f 6d
				len = pMultiIPInfo - paddrInfo;
				Set16(paddrInfo, (WORD)len);
				paddrInfo += len;
			}

			len = paddrInfo - penterInfo;
			Set16(penterInfo, (WORD)len);
			penterInfo += len;
		}
		Write32(penterInfo, Client->BorderRoomID); //roomId 0x00 00 02 eb
		Write16(penterInfo, 0); //SceneID 0x0

		len = penterInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	//00 00 00 ff 00 01 00 00 01 2e 53 40 ce 01 10 9d 8a 04 64 b2 56 00 00 00 01 04 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 6b 61 
	Write32(p, 0); //mapID 0x00 00 00 ff
	Write16(p, 0x0); //MatchedRoomType 0x00 01
	Write16(p, 0); //TeamMatchType 0x00 00
	Write8(p, 0x1); //PVPType 0x01
	Write32(p, 0); //PVPKey 0x2e 53 40 ce
	Write32(p, 12345678); //GameSeqIDHigh 0x01 10 9d 8a
	Write32(p, 87654321); //GameSeqIDLow 0x04 64 b2 56
	Write16(p, 0); //ForceTransCount0x00 00
	//Write32(p, 0); //ForceTransMsgID[]
	Write16(p, 1); //PlayerMatchingType 0x00 01
	Write8(p, 4); //paraNum
	Write32(p, 0);
	Write32(p, 0);
	Write32(p, 0);
	Write32(p, 0);
	//Write32(p, 0); //paraList[]

	len = p - buf;
	SendToClient(Client, 20081, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void RequestEnterMatchRoom(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT uin = Read32(Body);
	UINT time = Read32(Body);

	//Un roomId = ReadUn(Body);
	ResponseEnterMatchRoom(Client);
}

void ResponseEnterMatchRoom(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //resultId
	Write8(p, 0); //reasonLen

	Write8(p, 0); //HasMemoryRaceInfo
	//
	len = p - buf;
	SendToClient(Client, 20082, buf, len, Client->ServerID, FE_PLAYER, Client->ServerID, Response);
	
}




void RequestLeaveGame(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	//请求退出游戏
	UINT uin = Read32(Body);
	UINT time = Read32(Body);
	
	UINT GameSeqIDHigh = Read32(Body);
	UINT GameSeqIDLow = Read32(Body);
	USHORT LeaveGameType = Read16(Body);
	//UCHAR ParaNum = Read8(Body);
	//int[] ParaList[] = Read32(Body);
	//int ParaList[1];
	//ParaList[0] = Client->MapID;
	NotifyGameOver(Client, 0, 0, 0);
	Client->TaskID = 0;
	Client->IsFinish = FALSE;
	Client->IsReady == FALSE;
	//ResponseLeaveGame(Client);
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

void ResponseLeaveGame(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	Write16(p, 0); //ResultID

	len = p - buf;
	SendToClient(Client, 424, buf, len, Client->GameID, FE_GAMELOGIC, Client->ConnID, Response);
}


void NotifyRandRoomNameList(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	const char* RandRoomNameList[] = { "RandRoomName A","RandRoomName B","RandRoomName C" };
	BYTE Count = sizeof(RandRoomNameList) / sizeof(RandRoomNameList[0]);
	Write8(p, Count);
	for (BYTE i = 0; i < Count; i++)
	{ //RoomNames
		BYTE* pRoomNames = p;
		Write16(pRoomNames, 0); //len

		len = strlen(RandRoomNameList[i]);
		Write8(pRoomNames, (BYTE)len); //NameLen
		memcpy(pRoomNames, RandRoomNameList[i], len);
		pRoomNames += len;

		for (size_t i = 0; i < 20; i++)
		{
			Write8(pRoomNames, 0); //BaseModes[]
		}

		len = pRoomNames - p;
		Set16(p, (WORD)len);
		p += len;
	}

	len = p - buf;
	SendToClient(Client, 760, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}


void NotifyTopListDesc(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	try
	{
		YAML::Node Config = YAML::LoadFile("TopListDesc-QQSpeed.yml");//转换TopListDesc-QQSpeed.yml为ansi编码 否则utf-8可能乱码报错
		USHORT Count = (USHORT)Config.size();
		YAML::Node Descs;
		Write16(p, Count);
		for (USHORT i = 0; i < Count; i++)
		{ //Descs
			BYTE* pDescs = p;
			Write16(pDescs, 0); //len


			Descs = Config[i];

			Write16(pDescs, Descs["ID"].as<int>());

			std::string Name = Descs["Name"].as<std::string>();
			std::string ValueDesc = Descs["ValueDesc"].as<std::string>();
			std::string TitleName = Descs["TitleName"].as<std::string>();

			memset(pDescs, 0, MaxNickName);
			memcpy(pDescs, Name.c_str(), Name.length());
			pDescs += MaxNickName;

			memset(pDescs, 0, MaxNickName);
			memcpy(pDescs, ValueDesc.c_str(), ValueDesc.length());
			pDescs += MaxNickName;

			memset(pDescs, 0, MaxNickName);
			memcpy(pDescs, TitleName.c_str(), TitleName.length());
			pDescs += MaxNickName;

			Write8(pDescs, 0); //HasOtherInfo
			/*
			{ //Other
				BYTE* pOther = pDescs;
				Write16(pOther, 0); //len

				//WriteString(pOther, 0); //IntParaDesc0[]
				//WriteString(pOther, 0); //IntParaDesc1[]
				//WriteString(pOther, 0); //StrParaDesc0[]
				//WriteString(pOther, 0); //StrParaDesc1[]

				len = pOther - pDescs;
				Set16(pDescs, (WORD)len);
				pDescs += len;
			}
			*/

			Write8(pDescs, Descs["IsEnableSelfRank"].as<bool>());
			Descs.reset();
			len = pDescs - p;
			Set16(p, (WORD)len);
			p += len;
		}
	}
	catch (const std::exception&)
	{
		printf("异常\n");
		return;
	}
	

	len = p - buf;
	SendToClient(Client, 701, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void ResponseRankTopList(ClientNode* Client, USHORT ID)
{
	BYTE *buf=new BYTE[16384];
	BYTE* p = buf; size_t len;
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	int playercount = 0;
	char* NickName = NULL;
	char* newname = NULL;

	UINT GradeScore = 0;
	UINT GradeLevel = 0;
	Write32(p, Client->Uin); //Uin
	Write16(p, ID); //ID

	BYTE* pPlayerCount = p;
	Write16(p, 0); //Count
	//多表联合查询
	sql = "SELECT R.*,B.NickName FROM RankInfo R join BaseInfo B on R.Uin=B.Uin order by R.GradeLevel DESC,R.GradeScore DESC;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			playercount++;
			NickName = (char*)sqlite3_column_text(stmt, 3);
			newname = myutf8trans(NickName);
			BYTE* pPlayer = p;
			Write16(pPlayer, 0); //len
			Write32(pPlayer, sqlite3_column_int(stmt, 0)); //Uin
			GradeScore = sqlite3_column_int(stmt, 1);
			GradeLevel = sqlite3_column_int(stmt, 2);
			memset(pPlayer, 0, MaxNickName);
			if (newname)
			{
				memcpy(pPlayer, newname, strlen(newname));
				delete[] newname;
				newname = NULL;
			}
			pPlayer += MaxNickName;
			Write32(pPlayer, GradeScore+125*GradeLevel); //Value

			Write8(pPlayer, 0); //HasOtherInfo
			Write8(pPlayer, 0); //AreaId
			Write8(pPlayer, 0); //ParaNum
			Write8(pPlayer, 0); //AnchorNum
			len = pPlayer - p;
			Set16(p, (WORD)len);
			p += len;
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;
	Set16(pPlayerCount, playercount);
	Write32(p, 0); //SelfRank
	Write32(p, 0); //BeginRank
	Write32(p, 0); //UperPercentage

	len = p - buf;
	SendToClient(Client, 461, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
	delete[] buf;
}

void RequestTopList(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	USHORT ID = Read16(p);
	UCHAR Type = Read8(p);
	if (ID == 0x82)
	{
		//排位车神榜
		ResponseRankTopList(Client, ID);
	}
	else
	{
		ResponseTopList(Client, ID, Type);
	}
	
}

void ResponseTopList(ClientNode* Client, USHORT ID, UCHAR Type)
{
	BYTE* buf = new BYTE[16384];
	BYTE* p = buf; size_t len;
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	int playercount = 0;
	char* NickName = NULL;
	char* newname = NULL;

	Write32(p, Client->Uin); //Uin
	Write16(p, ID); //ID

	BYTE* pPlayerCount = p;
	Write16(p, 0); //Count
	sql = "SELECT Uin,NickName,Charm FROM BaseInfo order by Charm DESC;";
	result = sqlite3_prepare_v2(PlayerDB, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			playercount++;
			NickName = (char*)sqlite3_column_text(stmt,1);
			newname = myutf8trans(NickName);
			BYTE* pPlayer = p;
			Write16(pPlayer, 0); //len
			Write32(pPlayer, sqlite3_column_int(stmt, 0)); //Uin
			memset(pPlayer, 0, MaxNickName);
			if (newname)
			{
				memcpy(pPlayer, newname, strlen(newname));
				delete[] newname;
				newname = NULL;
			}
			pPlayer += MaxNickName;
			Write32(pPlayer, sqlite3_column_int(stmt, 2)); //Value

			Write8(pPlayer, 0); //HasOtherInfo
			Write8(pPlayer, 0); //AreaId
			Write8(pPlayer, 0); //ParaNum
			Write8(pPlayer, 0); //AnchorNum
			len = pPlayer - p;
			Set16(p, (WORD)len);
			p += len;
		}
	}
	sqlite3_finalize(stmt);
	stmt = NULL;
	Set16(pPlayerCount, playercount);
	Write32(p, 0); //SelfRank
	Write32(p, 0); //BeginRank
	Write32(p, 0); //UperPercentage

	len = p - buf;
	SendToClient(Client, 461, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
	delete[] buf;
}
void ResponsePointChallengeOpenMainBoard(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	Write16(p, 0); //ResultID
	Write32(p, 0); //TodayHighestTongGuanNum
	Write32(p, 0); //TodayHighestScore
	Write32(p, 0); //TotayTotalScore
	Write32(p, 5); //TiaoZhanNum
	Write32(p, 5); //TiaoZhanMaxNum
	Write32(p, 0); //GetTiaoZhanLeftSeconds
	Write32(p, 0); //HistoryHighestTongGuanNum
	Write32(p, 0); //HistoryHighestScore
	{ //AwardArray
		BYTE* pAwardArray = p;
		Write16(pAwardArray, 0); //len
		//道具key：586复活卡 588增时卡 590最后一搏
		Write8(pAwardArray, 3); //ExtendInfoNum
		{ //ExtendInfoAward
			BYTE* pExtendInfoAward = pAwardArray;
			Write16(pExtendInfoAward, 0); //len

			Write16(pExtendInfoAward, 586); //Key
			Write32(pExtendInfoAward, 90); //AddValue
			Write32(pExtendInfoAward, 90); //TotalValue
			Write8(pExtendInfoAward, 1); //ShowPriority
			Write16(pExtendInfoAward, 0); //BuyNeedScore
			Write8(pExtendInfoAward, 90); //OneMatchMaxNum

			len = pExtendInfoAward - pAwardArray;
			Set16(pAwardArray, (WORD)len);
			pAwardArray += len;
		}
		{ //ExtendInfoAward
			BYTE* pExtendInfoAward = pAwardArray;
			Write16(pExtendInfoAward, 0); //len

			Write16(pExtendInfoAward, 588); //Key
			Write32(pExtendInfoAward, 0); //AddValue
			Write32(pExtendInfoAward, 0); //TotalValue
			Write8(pExtendInfoAward, 0); //ShowPriority
			Write16(pExtendInfoAward, 0); //BuyNeedScore
			Write8(pExtendInfoAward, 0); //OneMatchMaxNum

			len = pExtendInfoAward - pAwardArray;
			Set16(pAwardArray, (WORD)len);
			pAwardArray += len;
		}
		{ //ExtendInfoAward
			BYTE* pExtendInfoAward = pAwardArray;
			Write16(pExtendInfoAward, 0); //len

			Write16(pExtendInfoAward, 590); //Key
			Write32(pExtendInfoAward, 0); //AddValue
			Write32(pExtendInfoAward, 0); //TotalValue
			Write8(pExtendInfoAward, 0); //ShowPriority
			Write16(pExtendInfoAward, 0); //BuyNeedScore
			Write8(pExtendInfoAward, 0); //OneMatchMaxNum

			len = pExtendInfoAward - pAwardArray;
			Set16(pAwardArray, (WORD)len);
			pAwardArray += len;
		}
		len = pAwardArray - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write32(p, 0); //WeekTotalScore
	Write32(p, 0); //TiaoZhanNum_TodayRecover
	Write32(p, 0); //TiaoZhanNum_MaxTodayRecoverNum
	Write32(p, 0); //GetTiaoZhanTotalSeconds

	len = p - buf;
	SendToClient(Client, 24754, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

/*void ResponseStartTimerChallenge(ClientNode* Client)
{
	Client->TaskID = 0xFFFE;
	Client->GameID = 2;
	Client->TotalRound = 1;
	Client->Loop = false;
	Client->FinishTime = 0;
	Client->Round = 0;
	Client->PassedCheckPoint = 0;
	Client->EndCheckPoint = 225;
	BYTE* p = StartTimerChallenge;
	p += 57;
	Write32(p, Client->Uin);
	p += 82;
	Write32(p, Client->Uin);
	Write32(p, Client->KartID);
	p += 104;
	Write32(p, Client->Uin);

	SendToClient(Client, 509, StartTimerChallenge, 589, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
	NotifyKartPhysParam(Client, NULL);
	//NotifyOtherKartStoneInfo(Client);

	//NotifyTimerChallengeCommonInfo
	const char* buf1 = "\x01\xe5\x00\x00\x00\x03\x00\x0a\x00\x00\x02\x4a\x00\x00\x00\x63\x00\x0a\x00\x00\x02\x4c\x00\x00\x00\x00\x00\x0a\x00\x00\x02\x4e\x00\x00\x00\x00\x00\x00\x13\x88\x00\x00\x00\x03\x00\x26\x05\x00\x0c\x00\x0c\x00\x15\x00\x17\x00\x1b\x00\x31\x00\x32\x00\x33\x00\x3a\x00\x3b\x00\x4b\x00\x4c\x00\x4d\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x92\x0c\x00\x42\x00\x01\x00\x02\x00\x03\x00\x04\x00\x06\x00\x07\x00\x08\x00\x09\x00\x0e\x00\x0f\x00\x11\x00\x12\x00\x1d\x00\x1e\x00\x1f\x00\x20\x00\x25\x00\x26\x00\x27\x00\x29\x00\x2a\x00\x2b\x00\x2c\x00\x2d\x00\x2e\x00\x30\x00\x34\x00\x35\x00\x36\x00\x37\x00\x38\x00\x39\x00\x3c\x00\x3d\x00\x3e\x00\x40\x00\x41\x00\x42\x00\x43\x00\x45\x00\x47\x00\x48\x00\x49\x00\x4a\x00\x4e\x00\x4f\x00\x50\x00\x51\x00\x52\x00\x53\x00\x54\x00\x55\x00\x56\x00\x59\x00\x5a\x00\x5b\x00\x5c\x00\x5d\x00\x5e\x00\x5f\x00\x60\x00\x61\x00\x62\x00\x63\x00\x64\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x88\x0d\x00\x3d\x00\x05\x00\x06\x00\x07\x00\x08\x00\x0a\x00\x0b\x00\x0c\x00\x0d\x00\x0e\x00\x0f\x00\x10\x00\x11\x00\x13\x00\x14\x00\x15\x00\x18\x00\x1a\x00\x1b\x00\x1d\x00\x1f\x00\x20\x00\x21\x00\x22\x00\x23\x00\x24\x00\x25\x00\x26\x00\x27\x00\x28\x00\x2a\x00\x2b\x00\x2c\x00\x2e\x00\x30\x00\x31\x00\x34\x00\x35\x00\x38\x00\x39\x00\x3e\x00\x40\x00\x42\x00\x49\x00\x4a\x00\x53\x00\x56\x00\x59\x00\x5d\x00\x5f\x00\x67\x00\x68\x00\x6a\x00\x73\x00\x7a\x00\x7c\x00\x83\x00\x8c\x00\x92\x00\x93\x00\x9c\x00\xaf\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x6d\x01\x00\x6a\x01\x00\x00\x00\x00\x00\x51\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x10\x02\x4e\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x10\x02\x4c\x00\x00\x00\x01\x00\x00\x00\x00\x01\x00\x00\x00\x00\x10\x02\x4a\x00\x00\x00\x63\x00\x00\x00\x63\x01\x00\x00\x63\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x03\x00\x00\x00\x03\x00\x00\x00\x00\x6c\x6f";

	SendToClient(Client, 24239, (BYTE*)buf1, 487, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
	//NotifyTimerChallengeEvent 08

	const char* buf2 = "\x00\x00\x27\x11\x00\x00\x00\x08\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x27\x10\x00\x0F\xFF\xFF\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
	SendToClient(Client, 24238, (BYTE*)buf2, 42, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);

	NotifyRaceBegin(Client);

	const char* buf3 = "\x00\x00\x27\x11\x00\x00\x00\x07\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x0F\xFF\xFF\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
	//NotifyTimerChallengeEvent 07
	SendToClient(Client, 24238, (BYTE*)buf3, 42, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
	//通关全部
	if (Client->JumpThread == 0)
	{
		HANDLE jump = CreateThread(NULL, 0, OnSingleJump, Client, 0, NULL);
		if (jump)
		{
			Client->JumpThread = 1;
			CloseHandle(jump);
		}
	}
}*/
/*void ResponseStartTimerChallenge2(ClientNode* Client)
{
	Client->TaskID = 0xFFFF;
	Client->GameID = 2;
	Client->TotalRound = 1;
	Client->Loop = false;
	Client->FinishTime = 0;
	Client->Round = 0;
	Client->PassedCheckPoint = 0;
	Client->EndCheckPoint = 0xFFFF;//结束点暂未定义 可以根据24256消息
	BYTE* p = StartTimerChallenge2;
	p += 57;
	Write32(p, Client->Uin);
	p += 82;
	Write32(p, Client->Uin);
	Write32(p, Client->KartID);
	p += 104;
	Write32(p, Client->Uin);
	p += 196;
	Write32(p, Client->Uin);
	p += 20;
	Write32(p, Client->Uin);
	//ResponseAddToMatchQueue(Client, 0x8);
	//NotifyMatchResult(Client, 0x8);
	//NotifyTimerChallenge2ndCommonInfo
	const char* buf1 = "\x01\xc1\x00\x00\x00\x02\x00\xd4\x13\x00\x63\x00\x01\x00\x02\x00\x03\x00\x05\x00\x06\x00\x07\x00\x09\x00\x0a\x00\x0b\x00\x0d\x00\x0e\x00\x0f\x00\x11\x00\x12\x00\x13\x00\x16\x00\x17\x00\x18\x00\x19\x00\x1a\x00\x1b\x00\x1d\x00\x1e\x00\x1f\x00\x21\x00\x22\x00\x23\x00\x25\x00\x26\x00\x27\x00\x2a\x00\x2b\x00\x2c\x00\x2e\x00\x2f\x00\x30\x00\x32\x00\x33\x00\x34\x00\x37\x00\x38\x00\x39\x00\x3a\x00\x3b\x00\x3c\x00\x3e\x00\x3f\x00\x40\x00\x43\x00\x44\x00\x45\x00\x46\x00\x47\x00\x48\x00\x49\x00\x4a\x00\x4b\x00\x4c\x00\x4d\x00\x4e\x00\x4f\x00\x50\x00\x51\x00\x5e\x00\x5f\x00\x60\x00\x61\x00\x62\x00\x63\x00\x64\x00\x65\x00\x66\x00\x67\x00\x68\x00\x69\x00\x6a\x00\x6b\x00\x6c\x00\x6d\x00\x6e\x00\x6f\x00\x70\x00\x71\x00\x72\x00\x73\x00\x74\x00\x75\x00\x82\x00\x83\x00\x84\x00\x85\x00\x86\x00\x87\x00\x8e\x00\x8f\x00\x90\x00\x91\x00\x92\x00\x93\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x6e\x11\x00\x30\x00\x04\x00\x08\x00\x0c\x00\x10\x00\x14\x00\x15\x00\x1c\x00\x20\x00\x24\x00\x28\x00\x29\x00\x2d\x00\x31\x00\x35\x00\x36\x00\x3d\x00\x41\x00\x42\x00\x52\x00\x53\x00\x54\x00\x55\x00\x56\x00\x57\x00\x58\x00\x59\x00\x5a\x00\x5b\x00\x5c\x00\x5d\x00\x76\x00\x77\x00\x78\x00\x79\x00\x7a\x00\x7b\x00\x7c\x00\x7d\x00\x7e\x00\x7f\x00\x80\x00\x81\x00\x88\x00\x89\x00\x8a\x00\x8b\x00\x8c\x00\x8d\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x6d\x01\x00\x6a\x00\x00\x00\x00\x00\x00\x51\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x10\x02\x4d\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x10\x02\x4d\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x10\x02\x4e\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x1b\x58\x00\x00\x00\x01\x50\x0f\x01\x00\x00\x4e\x20\x00\x00\x00\x01\x00\x00\x00\x01\x00\x00\x23\x28\x01\x00\x53\x00\x00\x27\x11\x01\x00\x4c\x00\x12\x00\x00\x00\x01\x00\x00\x00\x02\x00\x00\x00\x03\x00\x00\x00\x05\x00\x00\x00\x06\x00\x00\x00\x07\x00\x00\x00\x09\x00\x00\x00\x0a\x00\x00\x00\x0b\x00\x00\x00\x0d\x00\x00\x00\x0e\x00\x00\x00\x0f\x00\x00\x00\x12\x00\x00\x00\x13\x00\x00\x00\x11\x00\x00\x00\x16\x00\x00\x00\x17\x00\x00\x00\x18\x01\x00\x01\x00\x00";

	//NotifyTimerChallenge2ndEvent
	const char* buf2 = "\x00\x00\x00\x07\x00\x00\x00\x06\x00\x00\x00\x00\x00\x01\x38\x80\x00\x01\x38\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\x00\x00\x00\x00\x00\x00\x00\x00";
	//开始计时
	const char* buf3 = "\x00\x00\x00\x06\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x38\x80\x00\x01\x38\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\x00\x00\x00\x00\x00\x00\x61\x6c";
	//技能显示在notifygamebegin
	SendToClient(Client, 509, StartTimerChallenge2, 816, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
	NotifyKartPhysParam(Client, NULL);
	SendToClient(Client, 24256, (BYTE*)buf1, 565, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
	SendToClient(Client, 24255, (BYTE*)buf2, 91, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
	//NotifyOtherKartStoneInfo(Client);

	NotifyRaceBegin(Client);

	SendToClient(Client, 24255, (BYTE*)buf3, 91, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
	if (Client->JumpThread == 0)
	{
		HANDLE jump = CreateThread(NULL, 0, OnSingleJump, Client, 0, NULL);
		if (jump)
		{
			Client->JumpThread = 1;
			CloseHandle(jump);
		}
	}
}*/



void RequestReportTimerChallengeEvent(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body; WORD len;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	UINT EventID = Read32(p);
	//printf("ChallengeEvent:%d \n", EventID);
}
/*void RequestReportTimerChallenge2ndEvent(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	UINT EventID = Read32(p);
	//printf("Challenge2ndEvent:%d \n", EventID);
	if (EventID == 19)//退出挑战
	{
		Client->IsFinish = TRUE;
		//结束
		HANDLE over = CreateThread(NULL, 0, OnSingleOver, Client, 0, NULL);
		if (over)
		{
			CloseHandle(over);
		}
	}
	if (EventID == 17)//使用飞行技能
	{
		const char* buf = "\x00\x00\x27\x11\x00\x00\x00\x11\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
		SendToClient(Client, 24254, (BYTE*)buf, 20, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
	}
}*/
void NotifyBorderGameCondition(ClientNode* Client)
{
	const char* buf1 = "\x00\x0d\x00\x00\x27\x11\x64\x75\xda\xcf\x00\x00\x00\x00\xcf\x00\xcb\x44\x69\x73\x70\x61\x74\x63\x68\x43\x6f\x52\x65\x73\x70\x6f\x6e\x73\x65\x00\x00\xf6\x00\x00\x00\x00\x00\x00\x2a\x40\xfd\x00\x00\x00\xa9\xfa\x0c\x70\x6f\x77\x65\x72\x5f\x62\x6c\x65\x76\x65\x6c\xf6\x00\x00\x00\x00\x00\x00\x14\x40\xfa\x04\x6e\x61\x6d\x65\xfa\x0c\xb1\xdf\xbe\xb3\xc8\xd9\xd3\xfe\xcc\xd8\xc8\xa8\xfa\x0b\x73\x69\x6d\x70\x6c\x65\x5f\x64\x65\x73\x63\xfa\x14\xb1\xdf\xbe\xb3\xb6\xd4\xbe\xd6\xbb\xf1\xb5\xc3\xb6\xee\xcd\xe2\xc8\xd9\xd3\xfe\xfa\x06\x73\x74\x61\x74\x75\x73\xf6\x00\x00\x00\x00\x00\x00\x00\x00\xfa\x04\x64\x65\x73\x63\xfa\x42\xc3\xbf\xbe\xd6\xb1\xdf\xbe\xb3\xb1\xc8\xc8\xfc\xbb\xf1\xb5\xc3\xb6\xee\xcd\xe2\xb5\xe3\xc8\xd9\xd3\xfe\xa3\xac\xcf\xed\xca\xdc\xb6\xe0\xb1\xb6\xbc\xd3\xb3\xc9\x28\xb3\xf5\xbc\xb6\x2b\x35\xa3\xac\xb8\xdf\xbc\xb6\x2b\x31\x30\xa3\xac\xd7\xa8\xd2\xb5\x2b\x31\x35\x29\x00\x00";
	const char* buf2 = "\x00\x18\x00\x00\x00\x00\x00\x0a\x00\x1e\x00\x0a\x00\x00\x00\x00\x00\x03\x99\xb7\x00\x00\x00\x00\x00\x18\x00\x00\x00\x01\x00\x64\x00\x41\x00\x0a\x00\x00\x00\x00\x00\x03\x99\xb7\x00\x00\x03\xe8\x00\x18\x00\x00\x00\x02\x00\x0a\x00\x1e\x00\x0a\x00\x00\x00\x00\x00\x03\x99\xb7\x00\x00\x00\x00\x00\x18\x00\x00\x00\x03\x00\x64\x00\x41\x00\x0a\x00\x00\x00\x00\x00\x03\x99\xb7\x00\x00\x03\xe8\x00\x18\x00\x00\x00\x04\x01\x2c\x00\x5a\x00\x0a\x00\x02\x22\xe0\x00\x03\x34\x50\x00\x00\x4e\x20\x00\x18\x00\x00\x00\x05\x01\x2c\x00\x5a\x00\x0a\x00\x02\x22\xe0\x00\x03\x34\x50\x00\x00\x4e\x20\x00\x00\x00\x00\x00\x00\x0e\x00\x00\x00\x00\x00\x0a\x00\x1e\x00\x00\x00\x00\x00\x0e\x00\x00\x00\x01\x00\x64\x00\x41\x00\x00\x03\xe8\x00\x0e\x00\x00\x00\x02\x00\x0a\x00\x1e\x00\x00\x00\x00\x00\x0e\x00\x00\x00\x03\x00\x64\x00\x41\x00\x00\x03\xe8\x00\x0e\x00\x00\x00\x04\x01\x2c\x00\x5a\x00\x00\x4e\x20\x00\x0e\x00\x00\x00\x05\x01\x2c\x00\x5a\x00\x00\x4e\x20\x00\x0a\x64\x5d\x11\x00\x64\xb6\xb6\xff\x00\x01\x00\x0a\x00\x01\xe0\x78\x00\x03\x67\x18\x00\x00\x00\x00\x3c\x00\x00\x00\x3c\x00\x00\x00\x3c\x00\x00\x00\x3c\x00\x00\x00\x3c\x00\x00\x00\x3c\x00\x00\x00\x3c\x00\x00\x00\x3c\x00\x00\x00\x3c\x00\x01\x00\x0a\x00\x01\xe0\x78\x00\x03\x67\x18\x00\xbb\x01\x00\x5c\x00\x0f\x00\x01\x00\x0a\x00\x00\x00\x00\x00\x03\x99\xb7\x01\x00\x0f\x00\x01\x00\x0a\x00\x00\x00\x00\x00\x03\x99\xb7\x01\x00\x0f\x00\x01\x00\x0a\x00\x00\x00\x00\x00\x03\x99\xb7\x01\x00\x0f\x00\x01\x00\x0a\x00\x00\x00\x00\x00\x03\x99\xb7\x01\x00\x0f\x00\x01\x00\x0a\x00\x02\x22\xe0\x00\x03\x34\x50\x00\x00\x0f\x00\x01\x00\x0a\x00\x02\x22\xe0\x00\x03\x34\x50\x00\x00\x5c\x00\x0f\x00\x01\x00\x0a\x00\x01\xe0\x78\x00\x03\x67\x18\x00\x00\x0f\x00\x01\x00\x0a\x00\x01\xe0\x78\x00\x03\x67\x18\x00\x00\x0f\x00\x01\x00\x0a\x00\x01\xe0\x78\x00\x03\x67\x18\x00\x00\x0f\x00\x01\x00\x0a\x00\x01\xe0\x78\x00\x03\x67\x18\x00\x00\x0f\x00\x01\x00\x0a\x00\x02\x22\xe0\x00\x03\x34\x50\x00\x00\x0f\x00\x01\x00\x0a\x00\x02\x22\xe0\x00\x03\x34\x50\x00\x00\x0e\x00\x01\x00\x0a\x00\x01\xe0\x78\x00\x03\x67\x18\x00\x0e\x00\x01\x00\x0a\x00\x01\xe0\x78\x00\x03\x67\x18\x00\x0e\x00\x01\x00\x0a\x00\x01\xe0\x78\x00\x03\x67\x18\x00\x0e\x00\x01\x00\x0a\x00\x01\xe0\x78\x00\x03\x67\x18\x00\x0e\x00\x01\x00\x0a\x00\x02\x22\xe0\x00\x03\x34\x50\x00\x0e\x00\x01\x00\x0a\x00\x02\x22\xe0\x00\x03\x34\x50\x00\x1e\x00\x1a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00\x2f\xe4\x00\x00\x2e\xb6\x00\x00\x33\xff\x00\x00\x3e\x74\x00\x00\x2f\x0a\x00\x00";
	SendToClient(Client, 24251, (BYTE*)buf1, 222, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
	SendToClient(Client, 544, (BYTE*)buf2, 628, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);

}
void ResponseGetRankedMatchShowInfo(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	Write16(p, 0); //ResultID
	Write32(p, 0); //SeasonID
	Write16(p, 0); //DailyOpenTimeInfoNums

	Write32(p, 0); //SeasonOpenDate
	Write32(p, 0); //SeasonCloseDate
	{ //RankedMatchGradeInfo
		BYTE* pRankedMatchGradeInfo = p;
		Write16(pRankedMatchGradeInfo, 0); //len
		
		Write32(pRankedMatchGradeInfo, RankGradeLevel[Client->GradeLevel]); //GradeLevel 0x14 青铜 0x15白银段位 0x16黄金段位 0x17铂金 0x18 钻石 0x19 星耀 0x1a车神 0x1b传奇车神
		Write32(pRankedMatchGradeInfo, 1); //ChildLevel
		Write32(pRankedMatchGradeInfo, Client->GradeScore); //GradeScore
		Write32(pRankedMatchGradeInfo, 0); //MaxGradeScore
		Write32(pRankedMatchGradeInfo, 0); //TotalScore

		len = pRankedMatchGradeInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	{ //NextLevelReceAwardInfo
		BYTE* pNextLevelReceAwardInfo = p;
		Write16(pNextLevelReceAwardInfo, 0); //len

		{ //AwardInfo
			BYTE* pAwardInfo = pNextLevelReceAwardInfo;
			Write16(pAwardInfo, 0); //len

			Write32(pAwardInfo, 0); //Exp
			Write32(pAwardInfo, 0); //Money
			Write32(pAwardInfo, 0); //SuperMoney
			Write16(pAwardInfo, 0); //ItemNum

			Write32(pAwardInfo, 0); //Coupons
			Write32(pAwardInfo, 0); //GuildPoint
			Write32(pAwardInfo, 0); //LuckMoney
			Write8(pAwardInfo, 0); //ExtendInfoNum

			Write32(pAwardInfo, 0); //SpeedCoin

			len = pAwardInfo - pNextLevelReceAwardInfo;
			Set16(pNextLevelReceAwardInfo, (WORD)len);
			pNextLevelReceAwardInfo += len;
		}
		Write32(pNextLevelReceAwardInfo, 0); //GradeLevel
		Write32(pNextLevelReceAwardInfo, 0); //ChildLevel
		Write32(pNextLevelReceAwardInfo, 0); //FinishMatchNums

		len = pNextLevelReceAwardInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	{ //SeasonAwardInfo
		BYTE* pSeasonAwardInfo = p;
		Write16(pSeasonAwardInfo, 0); //len

		Write32(pSeasonAwardInfo, 0); //Exp
		Write32(pSeasonAwardInfo, 0); //Money
		Write32(pSeasonAwardInfo, 0); //SuperMoney
		Write16(pSeasonAwardInfo, 0); //ItemNum

		Write32(pSeasonAwardInfo, 0); //Coupons
		Write32(pSeasonAwardInfo, 0); //GuildPoint
		Write32(pSeasonAwardInfo, 0); //LuckMoney
		Write8(pSeasonAwardInfo, 0); //ExtendInfoNum

		Write32(pSeasonAwardInfo, 0); //SpeedCoin

		len = pSeasonAwardInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	{ //AnotherSeasonAwardInfo
		BYTE* pAnotherSeasonAwardInfo = p;
		Write16(pAnotherSeasonAwardInfo, 0); //len

		Write32(pAnotherSeasonAwardInfo, 0); //Exp
		Write32(pAnotherSeasonAwardInfo, 0); //Money
		Write32(pAnotherSeasonAwardInfo, 0); //SuperMoney
		Write16(pAnotherSeasonAwardInfo, 0); //ItemNum

		Write32(pAnotherSeasonAwardInfo, 0); //Coupons
		Write32(pAnotherSeasonAwardInfo, 0); //GuildPoint
		Write32(pAnotherSeasonAwardInfo, 0); //LuckMoney
		Write8(pAnotherSeasonAwardInfo, 0); //ExtendInfoNum

		Write32(pAnotherSeasonAwardInfo, 0); //SpeedCoin

		len = pAnotherSeasonAwardInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write16(p, 0); //SeasonMapNums

	Write16(p, 0); //PlayerSeasonInfoNums

	{ //RankedMatchPromoInfo
		BYTE* pRankedMatchPromoInfo = p;
		Write16(pRankedMatchPromoInfo, 0); //len

		Write8(pRankedMatchPromoInfo, 0); //PromotionMatch
		Write32(pRankedMatchPromoInfo, 0); //PromotionRoundNums
		Write32(pRankedMatchPromoInfo, 0); //PromotionSuccessRoundNums
		Write32(pRankedMatchPromoInfo, 0); //PromotionAlreadySuccessRoundNums
		Write32(pRankedMatchPromoInfo, 0); //PromotionRecordTag
		Write32(pRankedMatchPromoInfo, 0); //CurrentPromotionRoundNums
		Write32(pRankedMatchPromoInfo, 0); //PromoFailedMinusScore
		Write32(pRankedMatchPromoInfo, 0); //PromoSuccAddScore
		Write8(pRankedMatchPromoInfo, 0); //PromoDirectly
		Write8(pRankedMatchPromoInfo, 0); //GradeNoNeedPromo
		Write8(pRankedMatchPromoInfo, 0); //RankedMemoryNoNeedPromo
		Write8(pRankedMatchPromoInfo, 0); //PromotionExtraScore
		Write8(pRankedMatchPromoInfo, 0); //PromtRaceFailedDefendFlag

		len = pRankedMatchPromoInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write8(p, 0); //InhertGradeTag
	{ //GradeInheritInfo
		BYTE* pGradeInheritInfo = p;
		Write16(pGradeInheritInfo, 0); //len

		Write16(pGradeInheritInfo, 0); //OriginalGradeLevel
		Write16(pGradeInheritInfo, 0); //OriginalChildLevel
		Write16(pGradeInheritInfo, 0); //InheritedGradeLevel
		Write16(pGradeInheritInfo, 0); //InheritedChildLevel
		Write16(pGradeInheritInfo, 0); //InheritedLowLimitGradeLevel
		Write16(pGradeInheritInfo, 0); //InheritedLowLimitChildLevel

		len = pGradeInheritInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write8(p, 0); //RewardSeasonAward
	{ //LastSeasonAwardInfo
		BYTE* pLastSeasonAwardInfo = p;
		Write16(pLastSeasonAwardInfo, 0); //len

		Write32(pLastSeasonAwardInfo, 0); //Exp
		Write32(pLastSeasonAwardInfo, 0); //Money
		Write32(pLastSeasonAwardInfo, 0); //SuperMoney
		Write16(pLastSeasonAwardInfo, 0); //ItemNum

		Write32(pLastSeasonAwardInfo, 0); //Coupons
		Write32(pLastSeasonAwardInfo, 0); //GuildPoint
		Write32(pLastSeasonAwardInfo, 0); //LuckMoney
		Write8(pLastSeasonAwardInfo, 0); //ExtendInfoNum

		Write32(pLastSeasonAwardInfo, 0); //SpeedCoin

		len = pLastSeasonAwardInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	{ //AnotherLastSeasonAwardInfo
		BYTE* pAnotherLastSeasonAwardInfo = p;
		Write16(pAnotherLastSeasonAwardInfo, 0); //len

		Write32(pAnotherLastSeasonAwardInfo, 0); //Exp
		Write32(pAnotherLastSeasonAwardInfo, 0); //Money
		Write32(pAnotherLastSeasonAwardInfo, 0); //SuperMoney
		Write16(pAnotherLastSeasonAwardInfo, 0); //ItemNum

		Write32(pAnotherLastSeasonAwardInfo, 0); //Coupons
		Write32(pAnotherLastSeasonAwardInfo, 0); //GuildPoint
		Write32(pAnotherLastSeasonAwardInfo, 0); //LuckMoney
		Write8(pAnotherLastSeasonAwardInfo, 0); //ExtendInfoNum

		Write32(pAnotherLastSeasonAwardInfo, 0); //SpeedCoin

		len = pAnotherLastSeasonAwardInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	{ //DailyAwardInfo
		BYTE* pDailyAwardInfo = p;
		Write16(pDailyAwardInfo, 0); //len

		Write16(pDailyAwardInfo, 0); //ScoreInc
		Write16(pDailyAwardInfo, 0); //DailyScoreInc
		Write8(pDailyAwardInfo, 0); //DailyAwardGot
		Write32(pDailyAwardInfo, 0); //SuperMoney
		Write32(pDailyAwardInfo, 0); //CouponMoney

		len = pDailyAwardInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write8(p, 0); //CreateRoom
	Write8(p, 0); //RemindLengnedSpeedGodTip
	Write8(p, 0); //DisableSwitchGameSvr
	Write8(p, 0); //InheritFromOldSysTag
	Write32(p, 0); //OldSysGrade
	Write32(p, 0); //WeeklyAwardRankCoinNums
	Write32(p, 0); //WeeklyAwardRankCoinLimit
	Write32(p, 0); //CurrentRankCoinNums
	Write32(p, 0); //RankTaskNum

	Write32(p, 0); //FeiShiDescLen
	Write32(p, 0); //FeiShiID
	Write32(p, 0); //ShopItemNums

	memset(p, 0, 17);
	p += 17;//SeasonName[]
	//WriteString(p, 0); 
	Write32(p, 0); //BackgroundSceneId
	{ //RankedMatchSeasonChallengeInfo
		BYTE* pRankedMatchSeasonChallengeInfo = p;
		Write16(pRankedMatchSeasonChallengeInfo, 0); //len

		Write32(pRankedMatchSeasonChallengeInfo, 0); //SeasonStarNums
		Write32(pRankedMatchSeasonChallengeInfo, 0); //SeasonTaskNums

		{ //RankedMatchSeasonChallengeHonorDefendInfo
			BYTE* pRankedMatchSeasonChallengeHonorDefendInfo = pRankedMatchSeasonChallengeInfo;
			Write16(pRankedMatchSeasonChallengeHonorDefendInfo, 0); //len

			Write32(pRankedMatchSeasonChallengeHonorDefendInfo, 0); //NeedStarNums
			Write32(pRankedMatchSeasonChallengeHonorDefendInfo, 0); //AwardHonorDefendNums
			Write32(pRankedMatchSeasonChallengeHonorDefendInfo, 0); //DefendAddSocre

			len = pRankedMatchSeasonChallengeHonorDefendInfo - pRankedMatchSeasonChallengeInfo;
			Set16(pRankedMatchSeasonChallengeInfo, (WORD)len);
			pRankedMatchSeasonChallengeInfo += len;
		}
		Write8(pRankedMatchSeasonChallengeInfo, 0); //FinishNewTask
		Write32(pRankedMatchSeasonChallengeInfo, 0); //CurrentDefendHonorNums
		Write32(pRankedMatchSeasonChallengeInfo, 0); //UiDefendHonorLimitNums

		len = pRankedMatchSeasonChallengeInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write8(p, 0); //RaceTipType
	Write8(p, 0); //NewSeasonBegain
	Write8(p, 0); //HaveSeasonMapChallengeInfo

	Write32(p, 0); //NewSeasonMapAddDate
	Write8(p, 0); //HaveTippedSuperRaceGuard
	Write16(p, 0); //PromoAwardNums

	Write16(p, 0); //SeasonAwardNums

	Write32(p, 0); //CurrentHighGradeLevel
	Write32(p, 0); //CurrentHighChildLevel
	Write16(p, 0); //SpecialTipInfoLen
	Write16(p, 0); //SeasonNewMapNums
	Write32(p, 0); //SeasonNewMapID[]
	Write8(p, 0); //IsTriggerInheritedLowLimit
	Write8(p, 0); //InheritedLowLimitContentLens
	Write8(p, 0); //IsInheritedLowLimitUpdate
	Write8(p, 0); //InheritedLowLimitUpdateContentLens
	Write8(p, 0); //RankedMatchMissionTaskNums

	Write16(p, 0); //RankedMatchSuperRacePartLevelLimit
	Write16(p, 0); //NextGradeAndChildLevelSeasonTask
	Write16(p, 0); //CurrentSeasonTotalPartiNum
	Write8(p, 0); //SeasonMileStoneCfgNum

	Write16(p, 0); //SeasonMileStoneAwardNum
	Write8(p, 0); //TestDriveKartCfgNum

	Write16(p, 0); //TestDriveKartIdx
	Write32(p, 0); //TipContiUseTestKart
	Write8(p, 0); //MileStoneAddTip
	Write8(p, 0); //Type
	Write8(p, 0); //HasRankedMemoryData

	Write8(p, 0); //HasRankedSpeedFlashData

	Write8(p, 0); //CanPlayPinnacleBattle
	Write32(p, 0); //SavedExtraScore
	Write32(p, 0); //AnonymousModeStartScore
	Write16(p, 0); //SeasonHonerAwardNums

	Write32(p, 0); //LastSeasonTopHonerInfoIdx
	Write8(p, 0); //HasFengJianSunRenAwardData

	Write8(p, 0); //RankedCoinGradeCfgNum

	Write32(p, 0); //WeeklyAwardFactoryCoinLimit

	len = p - buf;
	SendToClient(Client, 25000, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void NotifyRankedMatchSeasonInfo(ClientNode* Client,UINT SrcUin)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, SrcUin); //Uin
	Write16(p, 1); //PlayerSeasonInfoNums
	for (size_t i = 0; i < 1; i++)
	{ //PlayerSeasonInfos
		BYTE* pPlayerSeasonInfos = p;
		Write16(pPlayerSeasonInfos, 0); //len

		Write16(pPlayerSeasonInfos, 0); //SeasonID
		Write16(pPlayerSeasonInfos, RankGradeLevel[Client->GradeLevel]); //GradeLevel
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

		len = pPlayerSeasonInfos - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write32(p, 0); //RankedMatchSpeedGodNums
	Write8(p, 0); //LegendSpeedGod
	Write32(p, 0); //CurrentSeasonID

	len = p - buf;
	SendToClient(Client, 25005, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void ResponsePVPLogin(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID

	len = p - buf;
	SendToClient(Client, 697, buf, len, Client->ServerID, FE_PLAYER, Client->ServerID, Response);


}
void RequestPVPLogin(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body; WORD len;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	UINT RandKey = Read32(p);
	ResponsePVPLogin(Client);
}



void ResponseChangeIdentity(ClientNode* Client, char SetOrUnset, char IsExRightFlag, UINT IdentityFlag)
{
	BYTE buf[39] = { 0 };
	/*BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	Write8(p, SetOrUnset); //SetOrUnset 0x0重置
	Write8(p, IsExRightFlag); //IsExRightFlag
	Write32(p, IdentityFlag); //IdentityFlag 0x78关小喷灯 0x02关宝石
	Write32(p, 0); //Identity
	Write8(p, 0); //ExRightFlag[]

	len = p - buf;*/
	if (SetOrUnset == 0)
	{
		memcpy(buf, "\x00\x00\x00\x01\x00\x00\x00\x78\x00\x50\x00\x01\x02\x00\x00\xa0\x00\x20\x80\x03\xa4\x01\x00\x40\x10\x00\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 38);
	}
	else
	{
		if (IdentityFlag == 0x78)
		{
			memcpy(buf, "\x00\x00\x01\x01\x00\x00\x00\x78\x00\x50\x00\x01\x02\x00\x00\xa0\x00\x20\x80\x03\xa4\x01\x00\x40\x10\x00\x10\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 38);
		}
		else if (IdentityFlag == 0x2)
		{
			memcpy(buf, "\x00\x00\x01\x01\x00\x00\x00\x02\x00\x50\x00\x01\x06\x00\x00\xa0\x00\x20\x80\x03\xa4\x01\x00\x40\x10\x00\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 38);
		}
	}

	SendToClient(Client, 131, (BYTE*)buf, 38, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void RequestChangeIdentity(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body; WORD len;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	char SetOrUnset = Read8(p);
	char IsExRightFlag = Read8(p);
	UINT IdentityFlag = Read32(p);
	//UINT BeginBit = Read32(p);
	//UINT EndBit = Read32(p);
	//UCHAR ExRightFlag[] = Read8(p);
	ResponseChangeIdentity(Client, SetOrUnset, IsExRightFlag, IdentityFlag);
}
void RequestReportCurrentOpt(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	BYTE* p = Body; WORD len;

	UINT Uin = Read32(p);
	UINT Time = Read32(p);
	short OptType = Read16(p);//紫钻退出0x4 树苗运输碰撞0x2
	int OptID = Read32(p);
	int SpecialValue = Read32(p);
}
void ResponseReportCurrentOpt(ClientNode* Client)
{
	BYTE buf[255]; BYTE* p = buf; size_t len;

	Write16(p, 0); //ResultID
	Write32(p, Client->Uin); //Uin
	Write16(p, 0x2); //OptType
	Write32(p, Client->OptNum); //OptNum

	len = p - buf;
	SendToClient(Client, 139, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
}

void NotifyGameNPCInfo(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //HostUin
	Write8(p, 5); //NPCNum
	try
	{
		YAML::Node Config = YAML::LoadFile(".\\Bot\\NPCListInfo.yml");
		size_t Num = Config.size();
		for (size_t i = 0; i < Num; i++)
		{
			YAML::Node NPCCfg = Config[i];
			//NPCInfo
			BYTE* pNPCPos = p;
			Write16(pNPCPos, 0); //len
			Write32(pNPCPos, NPCCfg["NpcID"].as<int>()); //NpcID
			Write16(pNPCPos, 0); //StartPos
			Write16(pNPCPos, NPCCfg["MaxLevel"].as<int>()); //NPCAILevel
			len = pNPCPos - p;
			Set16(p, (WORD)len);
			p += len;
			NPCCfg.reset();
		}

	}
	catch (const std::exception&)
	{
		return;
	}
	Write8(p, 0); //StageIndex

	len = p - buf;
	SendToClient(Client, 784, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);
}

void ResponseGetNewHandCritBoxAwardCfg(UINT ItemId,ClientNode* Client)
{
	BYTE buf[4096]; BYTE* p = buf; size_t len;
	char FilePath[MAX_PATH];
	ItemInfo* Items = NULL;
	int allitem = 0;
	int alllist = 0;
	
	sprintf_s(FilePath, ".\\Treasure\\%d.yml", ItemId);
	
	try
	{
		YAML::Node config = YAML::LoadFile(FilePath);
		alllist = config.size();
		if (alllist == 0)
		{
		
			return;//无物品
		}
		//randindex = (UINT)(rand() % alllist);
		YAML::Node SeedCfg = config[0];//0开头
		YAML::Node TreasureCfg = SeedCfg["Items"];//0开头
		allitem = TreasureCfg.size();
		if (allitem == 0)
		{
			return;//无物品
		}
		Items = new ItemInfo[8];//最多显示8个
		memset(Items, 0, sizeof(ItemInfo) * 8);
		//printf("allitem:%d\n",allitem);		
		for (int j = 0; j < 8; j++)
		{
			if (j >= allitem)
			{
				break;
			}
			//randindex = (UINT)(rand() % allitem);
			YAML::Node ItemCfg = TreasureCfg[j];//0开头
			Items[j].ItemID = ItemCfg["ItemId"].as<int>();
			Items[j].ItemNum = ItemCfg["ItemNum"].as<int>();
			ItemCfg.reset();
			
		}
	}
	catch (const std::exception&)
	{
	
		if (Items)
		{
			delete[] Items;
		}
		return;
	}

	char ItemNum = 0;
	Write16(p, 0); //ResultId
	Write32(p, Client->Uin); //Uin
	BYTE* pItemNum = p;
	Write16(p, 0); //ItemNum
	for (size_t i = 0; i < 8; i++)
	{ //LottoryAwardItem
		BYTE* pLottoryAwardItem = p;
		if (Items[i].ItemID == 0)
		{
			break;
		}
		ItemNum++;
		Write16(pLottoryAwardItem, 0); //len
		Write32(pLottoryAwardItem, Items[i].ItemID); //ItemID
		Write32(pLottoryAwardItem, Items[i].ItemNum); //Num
		Write32(pLottoryAwardItem, 0xFFFFFFFF); //Period
		Write16(pLottoryAwardItem, 2); //ItemType

		len = pLottoryAwardItem - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Set16(pItemNum, ItemNum);
	{ //MultiExtraAwardItem
		BYTE* pMultiExtraAwardItem = p;
		Write16(pMultiExtraAwardItem, 0); //len

		Write32(pMultiExtraAwardItem, 0); //ItemID
		Write32(pMultiExtraAwardItem, 0); //Num
		Write32(pMultiExtraAwardItem, 0); //Period
		Write16(pMultiExtraAwardItem, 0); //ItemType

		len = pMultiExtraAwardItem - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Write32(p, 0xa); //LuckValue
	Write32(p, 0x64); //MaxLuckValue
	Write32(p, ItemId); //ItemID
	
	len = p - buf;
	SendToClient(Client, 313, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
	
	delete[] Items;
	
	
}

void NotifyGenGameEndBoxAward(ClientNode* Client)
{
	BYTE buf[8192]; BYTE* p = buf; size_t len;
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	ItemInfo Item = {0};
	int allitem = 0;
	int alllist = 0;
	int listindex = 0;
	int randindex = 0;
	try
	{
		YAML::Node Config = YAML::LoadFile("Treasure.yml");
		size_t alllist = Config.size();
		if (alllist == 0)
		{
			//printf("1\n");
			return;//无物品
		}
		YAML::Node SeedCfg = Config[listindex];//0开头
		UINT Seed = (UINT)(rand() % 100) + 1;//取(0,100]
		UINT SeedTemp = SeedCfg["Seed"].as<int>();
		while (SeedTemp < Seed)
		{
			listindex++;
			if (listindex == alllist)
			{
				listindex = 0;//如果都不在范围 再重新计算随机值 直到有
				Seed = (UINT)(rand() % 100) + 1;//取(0,100]
				//Sleep(10);
			}
			SeedCfg = Config[listindex];//0开头
			SeedTemp = SeedCfg["Seed"].as<int>();
		}

		YAML::Node TreasureCfg = SeedCfg["Items"];//0开头
		allitem = TreasureCfg.size();
		if (allitem == 0)
		{
			return;//无物品
		}
		randindex = (UINT)(rand() % allitem);
		YAML::Node ItemCfg = TreasureCfg[randindex];//索引0开头
		Item.ItemID = ItemCfg["ItemId"].as<int>();
		Item.ItemNum = ItemCfg["ItemNum"].as<int>();
		//printf("ItemID:%d\n", Item.ItemID);
	}
	catch (const std::exception&)
	{
		return;
	}
	if (Item.ItemID != 0 && Item.ItemNum != 0)
	{
		Write32(p, Client->Uin); //Uin
		Write16(p, 3); //ItemNum
		for (size_t i = 0; i < 3; i++)
		{ //ItemInfo
			BYTE* pItemInfo = p;
			Write16(pItemInfo, 0); //len

			Write32(pItemInfo, Item.ItemID); //ItemID
			Write32(pItemInfo, Item.ItemNum); //ItemNum
			Write32(pItemInfo, 0); //AvailPeriod
			Write8(pItemInfo, 0); //Status
			Write32(pItemInfo, 0); //ObtainTime
			Write32(pItemInfo, 0); //OtherAttribute
			Write16(pItemInfo, 0); //ItemType

			len = pItemInfo - p;
			Set16(p, (WORD)len);
			p += len;
		}
		Write8(p, 0x62); //DescLen
		memcpy(p, "\xb9\xa7\xcf\xb2\xc4\xe3\xbb\xf1\xb5\xc3\xd0\xd2\xd4\xcb\xbf\xa8\xc5\xc6\x2f\x43\x30\x33\x33\xd1\xa1\x31\x2f\x43\x30\x30\xb5\xc4\xbb\xfa\xbb\xe1\xa3\xac\xb5\xe3\xbb\xf7\xbf\xa8\xc5\xc6\xbc\xb4\xbf\xc9\xc1\xec\xbd\xb1\x21\x00\x53\x45\x4c\x45\x43\x54\x20\x49\x74\x65\x6d\x49\x44\x2c\x49\x74\x65\x6d\x4e\x75\x6d\x2c\x41\x76\x61\x69\x6c\x50\x65\x72\x69\x6f\x64\x2c\x53\x74\x61\x74\x75\x73\x2c\x4f", 98);
		p += 98;
		len = p - buf;
		SendToClient(Client, 24755, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Notify);

		Item.ItemNum = PlayerDB_AddItem(Client, Client->Uin, Item.ItemID, Item.ItemNum, 0, 0);
		NotifyClientAddItem(Client, 1, &Item);
	}
}




void ResponseC2SGetKartAltasConfig(ClientNode* Client, UINT CfgVersion)
{
	BYTE* buf = new BYTE[25600];
	BYTE* p = buf; size_t len;

	Write32(p, Client->Uin); //Uin
	Write32(p, CfgVersion); //CfgVersion
	Write8(p, 0); //Result

	BYTE* pKartAltasCfgNum = p;
	Write16(p, 0); //KartAltasCfgNum
	
	if (!MKartAltasList)
	{
		return;
	}
	KARTALTAS* KartAltas = MKartAltasList->KartAltas;
	size_t Num = MKartAltasList->Size;
	for (size_t i = 0; i < Num; i++)
	{
		BYTE* pKartAltasConfig = p;
		Write16(pKartAltasConfig, 0); //len

		Write32(pKartAltasConfig, KartAltas[i].ID); //ItemID
		Write32(pKartAltasConfig, 0); //KartAltasUrlLen
		Write32(pKartAltasConfig, KartAltas[i].KartJetNum); //KartJetNum

		len = pKartAltasConfig - p;
		Set16(p, (WORD)len);
		p += len;
	}
	Set16(pKartAltasCfgNum, Num);
		
	
	len = p - buf;
	SendToClient(Client, 13710, buf, len, Client->ConnID, FE_PLAYER, Client->ConnID, Response);
	delete[] buf;
}
void RequestC2SGetKartAltasConfig(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);
	UINT CfgVersion = Read32(Body);

	ResponseC2SGetKartAltasConfig(Client, CfgVersion);
}

