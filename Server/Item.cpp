#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Item.h"

#include <map>
#include "yaml-cpp/yaml.h"

std::map<UINT, Item*> Items;

void LoadItemConfig()
{
	try
	{
		YAML::Node Config = YAML::LoadFile("Item.yml");
		YAML::Node item;
		for (size_t i = 0; i < Config.size(); i++)
		{
			item = Config[i];
			Item* pItem = new Item;
			pItem->ID = item["ID"].as<UINT>();
			std::string Type = item["Type"].as<std::string>();
			pItem->Type = EAIT_Unknown;
			if (Type == "EAIT_CAR")
			{
				pItem->Type = EAIT_CAR;
			}
			Items[pItem->ID] = pItem;
			item.reset();
		}
	}
	catch (const std::exception&)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		printf("加载物品文件出错\n");
		//exit(0);
	}
}

UINT GetItemType(UINT ID)
{
	Item* pItem = Items[ID];
	UINT Type = EAIT_Unknown;
	if (pItem)
	{
		Type = pItem->Type;
	}
	return Type;
}
