#include "Message.h"
#include "Database.h"
#include "sqlite/sqlite3.h"
#include <string>
extern sqlite3* PlayerDB;



void ResponseBuyCommodity(ClientNode* Client, UINT Uin, UINT Time, const char* Reason, int BuyCount, ShoppingCar* aShoppingCar);


void RequestBuyCommodity(ClientNode* Client, BYTE* Body, size_t BodyLen)
{
	const char* sql = NULL;
	sqlite3_stmt* stmt = NULL;
	int result;
	std::string Reason = "";
	char buffer[16] = "";
	ItemInfo Items = { 0 };

	UINT Uin = Read32(Body);
	UINT Time = Read32(Body);

	//NickName[]
	Body += MaxNickName;


	int ReqBuySeq = Read32(Body);
	UINT DstUin = Read32(Body);
	UINT PlayerExp = Read32(Body);
	USHORT CommodityType = Read16(Body);
	int PayType = Read32(Body);
	int BuyCount = Read32(Body);
	if (BuyCount == 0)
	{
		return;
	}
	ShoppingCar* aShoppingCar = new ShoppingCar[BuyCount];
	if (!aShoppingCar)
	{
		return;
	}
	for (int i = 0; i < BuyCount; i++)
	{ //ShoppingCar
		BYTE* pShoppingCar = Body;
		size_t len = Read16(pShoppingCar);

		aShoppingCar[i].CommodityID = Read32(pShoppingCar);
		aShoppingCar[i].PriceIdx = Read32(pShoppingCar);
		aShoppingCar[i].DiscountCardID = Read32(pShoppingCar);

		_itoa_s(aShoppingCar[i].CommodityID, buffer, 10);
		Reason = Reason + "CommodityID:" + buffer;
		_itoa_s(aShoppingCar[i].PriceIdx, buffer, 10);
		Reason = Reason + ", PriceIdx:" + buffer;
		_itoa_s(aShoppingCar[i].PriceIdx, buffer, 10);
		Reason = Reason + ", DiscountCardID:" + buffer;
		Reason += "\n";

		Items.ItemNum=PlayerDB_AddItem(Client,DstUin, aShoppingCar[i].CommodityID, 1, 0, false);
		Items.ItemID = aShoppingCar[i].CommodityID;
		Items.ObtainTime = 0xFFFF;
		
		NotifyClientAddItem(Client, 1, &Items);//通知客户端添加道具
		Body += len;
	}
	
	short AttachInfoLen = Read16(Body);
	UINT OtherInfo = Read32(Body);
	UINT FirstLoginTime = Read32(Body);
	UINT BuyNum = Read32(Body);
	UINT GuildID = Read32(Body);
	int ReduceCouponsID = Read32(Body);

#ifdef ZingSpeed
	Reason += "/C03不支持此操作";
#else
	Reason += "/C03成功";
#endif

	ResponseBuyCommodity(Client, Uin, Time, Reason.c_str(), BuyCount, aShoppingCar);
	delete[] aShoppingCar;
}

void ResponseBuyCommodity(ClientNode* Client, UINT Uin, UINT Time, const char* Reason, int BuyCount, ShoppingCar* aShoppingCar)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;


	Write16(p, 0); //ResultID
	Write32(p, Uin); //Uin
	Write32(p, Time); //Time

	memset(p, 0, MaxNickName); //NickName[]
	p += MaxNickName;

	Write32(p, 0); //ReqBuySeq
	Write32(p, 0); //DstUin
	Write32(p, 0); //PlayerExp

	Write16(p, 0); //CommodityType
	Write32(p, 0); //PayType
	Write32(p, BuyCount); //BuyCount
	for (int i = 0; i < BuyCount; i++)
	{
		BYTE* pShoppingCar = p;
		Write16(pShoppingCar, 0); //len

		Write32(pShoppingCar, aShoppingCar[i].CommodityID); //CommodityID
		Write32(pShoppingCar, aShoppingCar[i].PriceIdx); //PriceIdx
		Write32(pShoppingCar, aShoppingCar[i].DiscountCardID); //DiscountCardID

		len = pShoppingCar - p;
		Set16(p, (WORD)len);
		p += len;
	}

	Write16(p, 0); //AttachInfoLen
	Write32(p, 0); //OtherInfo
	Write32(p, 0); //FirstLoginTime

	len = strlen(Reason);
	Write16(p, (WORD)len); //ReasonLen
	memcpy(p, Reason, len);
	p += len;

	Write16(p, 0); //QuerySigLen
	Write8(p, 0); //CommMbItem
	Write8(p, 0); //MbItemNum
	/*
m_stItem[].m_cMbItemId
m_stItem[].m_cUse
m_stItem[].m_wContentLen
	*/


	Write32(p, 0); //ReduceCouponsID

	{ //MoneyInfo
		BYTE* pMoneyInfo = p;
		Write16(pMoneyInfo, 0); //len

		Write32(pMoneyInfo, 0); //money
		Write32(pMoneyInfo, 0); //superMoney
		Write32(pMoneyInfo, 0); //coupons
		Write32(pMoneyInfo, 0); //luckMoney
		Write32(pMoneyInfo, 0); //qbqd

		len = pMoneyInfo - p;
		Set16(p, (WORD)len);
		p += len;
	}

	len = p - buf;
	SendToClient(Client, 20000, buf, len, -1, FE_SHOPSVRD, Client->ConnID, Response);
}
