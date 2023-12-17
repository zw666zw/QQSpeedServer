#pragma once
#include "Message.h"
#include<unordered_map>
#include <stdio.h>
#include <time.h>
#include <map>
#include "yaml-cpp/yaml.h"
#include <mutex>
#include "Database.h"
#include "Item.h"
#include "sqlite/sqlite3.h"
#include <io.h>
#include <string>

typedef struct MKartAltas {
	UINT ID;
	UINT KartJetNum;
}KARTALTAS;

typedef struct MKartAltasList {
	KARTALTAS* KartAltas;
	UINT Size;
}KARTALTASLIST;
KARTALTASLIST* MKartAltasList=NULL;
void LoadKartAltasList()
{
	try
	{
		YAML::Node Config = YAML::LoadFile("KartAltasList.yml");
		MKartAltasList = new KARTALTASLIST;//新建赛车车库列表
		YAML::Node KartAltasCfg;
		size_t Num;
		MKartAltasList->Size= Num = Config.size();
		KARTALTAS* MKartAltas = new KARTALTAS[Num];
		MKartAltasList->KartAltas = MKartAltas;
		for (size_t i = 0; i < Num; i++)
		{
			KartAltasCfg = Config[i];
			MKartAltas[i].ID= KartAltasCfg["ID"].as<int>(); 
			MKartAltas[i].KartJetNum = KartAltasCfg["KartJetNum"].as<int>();
			KartAltasCfg.reset();
		}
	}
	catch (const std::exception&)
	{
		//printf("Load KartAltas Exception!\n");
		return;
	}
	//printf("Load KartAltas Success!\n");
}