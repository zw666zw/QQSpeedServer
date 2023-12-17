#pragma once
class Map
{
public:
	UINT Head;
	UINT End;
	UINT Round;
	bool Loop;
};

void LoadMapConfig();
Map* GetMap(UINT ID);
