#pragma once

enum ItemType
{
	EAIT_Unknown,
	EAIT_CAR
};

class Item
{
public:
	UINT ID;
	UINT Type;
};

void LoadItemConfig();
UINT GetItemType(UINT ID);
