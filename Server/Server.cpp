#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<unordered_map>
#include <stdio.h>
#include <malloc.h>
#include<process.h>
#include "Message.h"
#include "Map.h"
#include "Item.h"
#include "Database.h"
#include <wincrypt.h>
#include<map>
#include <mutex>
#include<DbgHelp.h>
#include<time.h>
#include<iostream>
#pragma comment(lib,"advapi32.lib")
#pragma comment (lib, "ws2_32.lib")

#pragma comment (lib,"HPSocket.lib")

#include "yaml-cpp/yaml.h"
#ifdef NDEBUG
#pragma comment (lib,"yaml-cpp.lib")
#else
#pragma comment (lib,"yaml-cppd.lib")
#endif

std::string IP;
USHORT TcpPort;
USHORT UdpPort;
std::string BindIP;
USHORT BindTcpPort;
USHORT BindUdpPort;

std::string QQServerIP;
USHORT QQServerTcpPort;
extern std::string QQServerBindIP;
extern USHORT QQServerBindTcpPort;

//void StartQQServer(std::string IP, USHORT Port);

extern void StartQQServer();
//udp cs cmds
#define UDP_CMD_LOGIN_SERVER			0x01
#define UDP_CMD_P2P_GAME_DATA			0x02
#define UDP_CMD_SHOW_MY_IP_PORT			0x03
#define UDP_CMD_RECV_OTHER_IP_PORT	0x04
#define UDP_CMD_HEART_BEAT				0x05

//udp cc cmds
#define UDP_CMD_TEST_CONNECTION_NO_RECEIVE			0x20
#define UDP_CMD_TEST_CONNECTION_RECEIVED			0x21
#define UDP_CMD_UDP_BIDIRECTIONAL_OK				0x22
#define UDP_CMD_CLIENT_HELLO						0x25
#define UDP_CMD_CLIENT_P2P_DATA						0x26

#define UDP_CMD_TEST_NETSPEED						0x27
#define UDP_CMD_TEST_NETSPEED_REPLY					0x28


#include "sqlite/sqlite3.h"
extern sqlite3* PlayerDB;

//extern const char* UITitleDispInfo_ADText;
std::string UITitleDispInfo_ADText;
const char* mytext;
extern char registerflag;
extern char propflag;
extern std::map<long, ClientNode*> Clients;

extern std::recursive_mutex Mutex;
std::recursive_mutex ClientMutex;
std::string TransferModelStr;
char TransferModel = 0;//udp 0 tcp 1
extern void OnlineTest();
extern int Prob;
UINT SyncTime = 0;
UINT DanceTime = 0;
UINT GameOverTime = 0;
extern void LoadKartAltasList();
#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif  // _WIND32


// 定义64位整形
#if defined(_WIN32) && !defined(CYGWIN)
typedef __int64 int64_t;
#else
typedef long long int64t;
#endif  // _WIN32

// 获取系统的当前时间，单位微秒(us)
int64_t GetSysTimeMicros()
{
#ifdef _WIN32
	// 从1601年1月1日0:0:0:000到1970年1月1日0:0:0:000的时间(单位100ns)
#define EPOCHFILETIME   (116444736000000000UL)
	FILETIME ft;
	LARGE_INTEGER li;
	int64_t tt = 0;
	GetSystemTimeAsFileTime(&ft);
	li.LowPart = ft.dwLowDateTime;
	li.HighPart = ft.dwHighDateTime;
	// 从1970年1月1日0:0:0:000到现在的微秒数(UTC时间)
	tt = (li.QuadPart - EPOCHFILETIME) / 10;
	return tt;
#else
	timeval tv;
	gettimeofday(&tv, 0);
	return (int64_t)tv.tv_sec * 1000000 + (int64_t)tv.tv_usec;
#endif // _WIN32
	return 0;
}
int GenerateMiniDump(PEXCEPTION_POINTERS pExceptionPointers)
{
	// 定义函数指针
	typedef BOOL(WINAPI* MiniDumpWriteDumpT)(
		HANDLE,
		DWORD,
		HANDLE,
		MINIDUMP_TYPE,
		PMINIDUMP_EXCEPTION_INFORMATION,
		PMINIDUMP_USER_STREAM_INFORMATION,
		PMINIDUMP_CALLBACK_INFORMATION
		);
	// 从 "DbgHelp.dll" 库中获取 "MiniDumpWriteDump" 函数
	MiniDumpWriteDumpT pfnMiniDumpWriteDump = NULL;
	HMODULE hDbgHelp = LoadLibrary(TEXT("DbgHelp.dll"));
	if (NULL == hDbgHelp)
	{
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	pfnMiniDumpWriteDump = (MiniDumpWriteDumpT)GetProcAddress(hDbgHelp, "MiniDumpWriteDump");

	if (NULL == pfnMiniDumpWriteDump)
	{
		FreeLibrary(hDbgHelp);
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	// 创建 dmp 文件件
	WCHAR szFileName[MAX_PATH] = { 0 };
	SYSTEMTIME stLocalTime;
	GetLocalTime(&stLocalTime);
	wsprintfW(szFileName, L"%s-%04d%02d%02d-%02d%02d%02d.dmp",
		L"DumpDemo_v1.0", stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay,
		stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond);
	HANDLE hDumpFile = CreateFileW(szFileName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);
	if (INVALID_HANDLE_VALUE == hDumpFile)
	{
		FreeLibrary(hDbgHelp);
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	// 写入 dmp 文件
	MINIDUMP_EXCEPTION_INFORMATION expParam;
	expParam.ThreadId = GetCurrentThreadId();
	expParam.ExceptionPointers = pExceptionPointers;
	expParam.ClientPointers = FALSE;
	pfnMiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
		hDumpFile, MiniDumpWithDataSegs, (pExceptionPointers ? &expParam : NULL), NULL, NULL);
	// 释放文件
	CloseHandle(hDumpFile);
	FreeLibrary(hDbgHelp);
	return EXCEPTION_EXECUTE_HANDLER;
}

LONG WINAPI ExceptionFilter(LPEXCEPTION_POINTERS lpExceptionInfo)
{
	// 这里做一些异常的过滤或提示
	if (IsDebuggerPresent())
	{
		return EXCEPTION_CONTINUE_SEARCH;
	}
	return GenerateMiniDump(lpExceptionInfo);
}



ClientNode* GetClient(long Uin)
{
	ClientNode* Client= NULL;
	std::lock_guard<std::recursive_mutex> lg(ClientMutex);
	//DWORD dwStart = GetTickCount64(); //取windows启动到现在的流逝时间(毫秒)
	auto iter = Clients.find(Uin);
	if (iter != Clients.end())
	{
		Client = iter->second;
	}
	else
	{
	}
	//DWORD dwUsed = GetTickCount64() - dwStart; //计算该函数所消耗的时间
	//printf("Room Search lost:%d ms\n", dwUsed);
	return Client;


}


void Run2(void *param)
{
	char ch[4096];
	char* power = NULL;
	do
	{
		fputs(">", stdout);
		fflush(stdout);
		fgets(ch, 4096, stdin);
		fflush(stdin);
		if (_stricmp(ch, "Room\n") == 0)
		{
			PrintRoom();
		}
		else if (_stricmp(ch, "sign on\n") == 0)
		{
			registerflag = 1;
			printf("已开启注册\n");
		}
		else if (_stricmp(ch, "sign off\n") == 0)
		{
			registerflag = 0;
			printf("已关闭注册\n");
		}
		else if (_stricmp(ch, "prop on\n") == 0)
		{
			propflag = 1;
			printf("已开启抽奖\n");
		}
		else if (_stricmp(ch, "prop off\n") == 0)
		{
			propflag = 0;
			printf("已关闭抽奖\n");
		}
		else if ((power=strstr(ch,"stone:"))!=NULL)
		{
			power+=6;
			Prob = atoi(power);
			printf("重生宝石概率基数:%d\n", Prob);
		}
		else if (_stricmp(ch, "usr\n") == 0)
		{
			
			int num=Clients.size();
			
			printf("当前在线人数:%d\n",num);
		}
	} while (_stricmp(ch, "Exit\n") != 0);
	//fputs("Bye\n", stdout);

}



class GameServer : public CTcpServerListener, public CUdpNodeListener
{
public:
	CTcpServerPtr TCP;
	CUdpNodePtr UDP;
	unsigned short CheckSum(const BYTE* pBuffer, int nBufLen)
	{
		if (NULL == pBuffer || nBufLen < 1)
		{
			return 0;
		}

		unsigned long nSum = 0;
		unsigned short* pData = (unsigned short*)pBuffer;

		int nLen = nBufLen / 2;
		int nMod = nBufLen % 2;

		for (int i = 0; i < nLen; i++)
		{
			nSum += pData[i];
		}

		unsigned short nShort = 0;

		if (1 == nMod)
		{
			nShort = (unsigned short)pBuffer[nBufLen - 1];
			nSum += nShort;
		}
		nSum = (nSum >> 16) + (nSum & 0xffff);
		nSum += (nSum >> 16);
		nShort = ~((unsigned short)nSum);
		return nShort;
	}

	void SendUdpData(LPCTSTR lpszRemoteAddress, USHORT usRemotePort, short Cmd, const BYTE* Data, int Len, ULONG Seq, SHORT DialogID, ULONG Uin)
	{
		int BufferLength = sizeof(TransferHead) + Len;
		BYTE* Buffer = (BYTE*)malloc(BufferLength);
		if (!Buffer)
		{
			return;
		}
		TransferHead* ProtocolHead = (TransferHead*)Buffer;
		ProtocolHead->TotalLength = htons(BufferLength);
		ProtocolHead->Ver = 0;
		ProtocolHead->Seq = htonl(Seq);
		ProtocolHead->DialogID = htons(DialogID);
		ProtocolHead->Uin = htonl(Uin);
		ProtocolHead->TransferCmd = htons(Cmd);
		ProtocolHead->CheckSum = 0;
		ProtocolHead->OptLength = (UCHAR)Len;
		memcpy(ProtocolHead + 1, Data, Len);
		ProtocolHead->CheckSum = htons(CheckSum(Buffer, BufferLength));

		UDP->Send(lpszRemoteAddress, usRemotePort, Buffer, BufferLength);
		free(Buffer);
		//printf("[UDP:Send]Cmd:%d\n", Cmd);
		fflush(stdout);
	}

	
	

	GameServer() :TCP(this), UDP(this)
	{
		try
		{
			
			YAML::Node config = YAML::LoadFile("config.yml");

			YAML::Node Server = config["Server"];
			SyncTime= config["SyncTime"].as<UINT>();
			DanceTime= config["DanceTime"].as<UINT>();
			GameOverTime= config["GameOverTime"].as<UINT>();
			
			IP = Server["IP"].as<std::string>();
			TcpPort = Server["TcpPort"].as<USHORT>();
			UdpPort = Server["UdpPort"].as<USHORT>();
			std::string Name = Server["Name"].as<std::string>();
			UITitleDispInfo_ADText= Server["Title"].as<std::string>();
			TransferModelStr= Server["Model"].as<std::string>();
			if (_stricmp(TransferModelStr.c_str(), "tcp") == 0)
			{
				TransferModel = 1;
			}
			InitDirServer(Name.c_str(), inet_addr(IP.c_str()), TcpPort, UdpPort);

			YAML::Node Bind = Server["Bind"];
			BindIP = Bind["IP"].as<std::string>();
			BindTcpPort = Bind["TcpPort"].as<USHORT>();
			BindUdpPort = Bind["UdpPort"].as<USHORT>();


			Server = config["QQServer"];
			QQServerIP = Server["IP"].as<std::string>();
			QQServerTcpPort = Server["TcpPort"].as<USHORT>();

			Bind = Server["Bind"];
			QQServerBindIP = Bind["IP"].as<std::string>();
			QQServerBindTcpPort = Bind["TcpPort"].as<USHORT>();

		}
		catch (const std::exception&)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
			printf("加载配置文件出错\n");
			//exit(0);
		}
	}
	
	void Run()
	{
		//TCP传输优化
		//TCP->SetMaxConnectionCount(9999);
		//TCP->SetAcceptSocketCount(999);
		//TCP->SetNoDelay(TRUE);
		//TCP->SetWorkerThreadCount(100);
		//TCP->SetSendPolicy(SP_SAFE);//安全发送模式
		//TCP->SetOnSendSyncPolicy(OSSP_NONE);
		//Start开始之前设置参数才生效
		if (!TCP->Start(BindIP.c_str(), BindTcpPort))
		{
			//hpsocket.lib 接口
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
			printf("[TCP][GameServer]Start Failed\n");
			return;
		}
		
		//printf("GetMaxConnectionCount:%d\n", TCP->GetMaxConnectionCount());
		//printf("IsNoDelay:%d\n", TCP->IsNoDelay());
		//printf("工作线程 :%d\n", TCP->GetWorkerThreadCount());
		//printf("GetSendPolicy :%d\n", TCP->GetSendPolicy());
		UDP->Start(BindIP.c_str(), BindUdpPort, CM_UNICAST, nullptr);
		//StartQQServer();
		
	}
	
private:
	virtual EnHandleResult OnPrepareListen(ITcpServer* pSender, SOCKET soListen)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
		//printf("Server key:hi!!girl!!gogogo\n");
		printf("sign on/off开启或关闭注册\n");
		printf("prop on/off开启或关闭抽奖\n");
		printf("房间密码支持设置2位以上\n");
		
		if (TransferModel == 0)
		{
			printf("当前模式:udp\n");
		}
		else
		{
			printf("当前模式:tcp\n");
		}
		//printf("优化休闲区\n");
		printf("同步超时时间:%d 跳舞时间:%d 结算时间:%d\n", SyncTime, DanceTime, GameOverTime);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		//printf("禁用3D房间可能崩溃\n");
		//printf("启用g快速退出\n");
		fflush(stdout);
		
#ifdef ZingSpeed
		printf("---- Usage steps ----\n");
		printf("  1.Go to the game directory\n");
		printf("  2.Edit the DirSvrInfo1.ini file to look like this:\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("[ServerInfo1]\nIP=%s\nPorts=%d,%d,%d\nServerID=1\n\n", IP.c_str(), TcpPort, TcpPort, TcpPort);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);

		printf("  3.Edit the QQSvrInfo.ini file to look like this:\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("[ServerInfo1]\nIP=%s\nPorts=%d,%d,%d\n\n", QQServerIP.c_str(), QQServerTcpPort, QQServerTcpPort, QQServerTcpPort);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);

		printf("  4.Replace ZingSpeedLauncher.exe file\n");
		printf("  5.Run ZingSpeedLauncher.exe to launch the game\n");
#else
	
	
	
		
#endif
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		//加载配置到内存缓冲区 加速读写
		LoadMapConfig();
		LoadItemConfig();
		InitDB();
		InitChatRoom();
		InitTaskInfo();
		LoadKartAltasList();//加载车库配置到内存
		return HR_OK;
	}

	virtual EnHandleResult OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient)
	{
		ClientNode* Client;
		try {
			//printf("[GameServer][ConnID:%d]]OnAccept\n", dwConnID);
			Client = new ClientNode;//初始化一个新的客户端对象
			memset(Client, 0, sizeof(ClientNode));
			Client->Server = pSender;
			Client->ConnID = dwConnID;
			memcpy(Client->Key, "hi!!girl!!gogogo", 16);

			//Client->KartID = 10020;//默认装备板车代码

			pSender->SetConnectionExtra(dwConnID, Client);
		}
		catch (...)
		{
			printf("OnAccept Exceptoin!!!\n");
			fflush(stdout);
		}
		return HR_OK;//返回成功才执行 下面流程
	}

	virtual EnHandleResult OnHandShake(ITcpServer* pSender, CONNID dwConnID)
	{
		//printf("[GameServer][ConnID:%d]OnHandShake\n", dwConnID);
		return HR_IGNORE;
	}
	//接收客户端信息
	virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
	{
		
	
		BOOL result;
		//printf("[GameServer][ConnID:%d]OnReceive\n", dwConnID);
		ClientNode* Client;
		result=pSender->GetConnectionExtra(dwConnID, (PVOID*)&Client);
	
		long left;
		long need;
		const int MaxBuf = 8192;
		void* p;
		if (result)
		{
			try {
				do
				{
					if (Client->BufferPtr)
					{
						if (Client->BufferOffset < sizeof(int))
						{
							//printf("Client->BufferOffset:%d\n", Client->BufferOffset);
							left = min(iLength, int(sizeof(int) - Client->BufferOffset));
							//printf("left:%d\n", left);
							memcpy((void*)(Client->BufferPtr + Client->BufferOffset), pData, left);
							Client->BufferOffset += left;
							if (Client->BufferOffset < sizeof(int))
							{
								break;
							}
							pData += left;
							iLength -= left;
						}
						need = ntohl(*(u_long*)Client->BufferPtr);
						left = need - Client->BufferOffset;
						if (need > Client->BufferSize)
						{
							if (need > 65535) //If the data packet sent by the client is too large, it will not be processed.
							{
								//客户端每次最多只能处理65535字节数据 超过需要分包
								//客户端包过大丢弃
								Client->Server->Disconnect(Client->ConnID);
								//Client->Uin = NULL;
								Client->IsLogin = FALSE;
								//delete Client;
								break;
							}
							if (left > MaxBuf)
							{
								left = max(iLength, MaxBuf);
								Client->BufferSize = Client->BufferOffset + left;
							}
							else
							{
								Client->BufferSize = need;
							}
							p = realloc((void*)Client->BufferPtr, Client->BufferSize);
							if (!p)
							{
								printf("内存不足\n");
								TCP->Stop();
								break;
							}
							Client->BufferPtr = (ULONG_PTR)p;
						}
						if (left >= 0)
						{
							left = min(iLength, left);
							memcpy((void*)(Client->BufferPtr + Client->BufferOffset), pData, left);
							Client->BufferOffset += left;
							if (Client->BufferOffset < need)
							{
								break;
							}
							OnFullReceive(Client, (BYTE*)Client->BufferPtr, need);
							pData += left;
							iLength -= left;
						}
						free((void*)Client->BufferPtr);
						Client->BufferPtr = 0;
						Client->BufferOffset = 0;
					}
					while (iLength > 0)
					{
						if (iLength < sizeof(int))
						{
							need = sizeof(int);
						}
						else
						{
							need = ntohl(*(u_long*)pData);
						}
						if (need > iLength)
						{
							if (need > MaxBuf)
							{
								Client->BufferSize = max(iLength, MaxBuf);
							}
							else
							{
								Client->BufferSize = need;
							}
							p = malloc(Client->BufferSize);
							if (!p)
							{
								printf("内存不足\n");
								TCP->Stop();
								break;
							}
							Client->BufferPtr = (ULONG_PTR)p;
							memcpy((void*)Client->BufferPtr, pData, iLength);
							Client->BufferOffset = iLength;
							break;
						}
						else
						{
							OnFullReceive(Client, (BYTE*)pData, need);
							pData += need;
							iLength -= need;
						}
					}
				} while (false);
			}
			catch (...)
			{
				printf("OnReceive Exceptoin!!!\n");
				fflush(stdout);
			}
		}
	
		return HR_OK;
	}

	virtual EnHandleResult OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
	{
		//printf("[GameServer][ConnID:%d]OnSend\n", dwConnID);
		return HR_OK;
	}

	virtual EnHandleResult OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
	{
		BOOL result;
		ClientNode* Client;
		result=pSender->GetConnectionExtra(dwConnID, (PVOID*)&Client);
		//printf("[GameServer][ConnID:%d]OnClose\n", dwConnID);
		if (result)
		{
			try {
				LeaveRoom(Client, 0);
				LeaveBorderRoom(Client, 0);
				LeaveOutdoor(Client);
			
				Client->IsLogin = FALSE;
				if (Client->BufferPtr)
				{
					free((PVOID)Client->BufferPtr);
				}
				//DWORD dwStart = GetTickCount64(); //取windows启动到现在的流逝时间(毫秒)
				std::lock_guard<std::recursive_mutex> lg(ClientMutex);
				Clients.erase(Client->Uin);
				delete Client;
				//Client = NULL;
				//DWORD dwUsed = GetTickCount64() - dwStart; //计算该函数所消耗的时间
				//printf("Clients Erase lost:%d ms\n", dwUsed);
			}
			catch (...)
			{
				printf("OnClose Exceptoin!!!\n");
				fflush(stdout);
			}
		}
	
		
		return HR_OK;
	}

	virtual EnHandleResult OnShutdown(ITcpServer* pSender)
	{
		printf("[GameServer]Close\n");

		CloseDB();
		return HR_OK;
	}
private:
	virtual EnHandleResult OnPrepareListen(IUdpNode* pSender, SOCKET soListen)
	{
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
		//printf("[UDP]Start Success\n");
		//fflush(stdout);
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		return HR_OK;
	}
	virtual EnHandleResult OnSend(IUdpNode* pSender, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength)
	{
		return HR_OK;
	}
	virtual EnHandleResult OnReceive(IUdpNode* pSender, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength)
	{
		try {

		if (TransferModel == 1)
		{
			return HR_OK;
		}

		TransferHead* ProtocolHead = (TransferHead*)pData;
		if (iLength < sizeof(TransferHead) && ntohs(ProtocolHead->TotalLength) > iLength)
		{
			return HR_OK;
		}
		ClientNode* Client = NULL;
		UINT Seq = ntohl(ProtocolHead->Seq);
		short DialogID = ntohs(ProtocolHead->DialogID);
		UINT Uin = ntohl(ProtocolHead->Uin);
		
		short TransferCmd = ntohs(ProtocolHead->TransferCmd);
		UCHAR OptLength = ProtocolHead->OptLength;

		//printf("[UDP:OnReceive]Uin:%d, TransferCmd:%d, OptLength:%d\n", Uin, TransferCmd, OptLength);

		size_t len = 0;
		BYTE* p = PBYTE(ProtocolHead + 1);
		UCHAR option[1024];
		
		int num = 0;
		switch (TransferCmd)
		{
		case UDP_CMD_LOGIN_SERVER:
		{
			
			//udp服务器登录命令
			in_addr LocalIP;
			LocalIP.S_un.S_addr = Read32(p);
			USHORT LocalPort = Read16(p);
#
			//printf("lpszRemoteAddress:%s LocalIP:%s, LocalPort:%d\n", lpszRemoteAddress, inet_ntoa(LocalIP), LocalPort);
			p = option;

			Write32(p, inet_addr(lpszRemoteAddress));

			len = p - option;
			SendUdpData(lpszRemoteAddress, usRemotePort, UDP_CMD_LOGIN_SERVER, option, len, Seq, DialogID, Uin);
			
				
			
			break;
		}

		case UDP_CMD_P2P_GAME_DATA:
		{
			//UDP游戏数据 tcp传输
			Client = GetClient(Uin);
			if (!Client)
			{
				return HR_OK;
			}
			RoomNode* Room = NULL;
			if (Client->RoomID != 0)
			{
				Room =GetRoom(Client->RoomID);
			}
			else if (Client->BorderRoomID != 0)
			{
				Room = GetRoom(Client->BorderRoomID);
			}
			if (!Room)
			{
				return HR_OK;
			}
			len = iLength - sizeof(TransferHead) - OptLength;
			/*printf("TransferCmd:%d iLength:%d\n ", TransferCmd, iLength);
			for (int i = 0; i < iLength; i++)
			{
				printf("%02x ", *(pData + i));
			}
			printf("\n");*/
		
			//BYTE* pDstInfo = p;
			//SHORT PlayerID = 0;
			//UINT DstUin = 0;
			BYTE* DataBuf = p + OptLength;
			/*while (OptLength >= 14)
			{
				
			// 一个人占6个字节
				PlayerID = Read16(pDstInfo);
				DstUin = Read32(pDstInfo);
				//printf("PlayerID:%d, PlayerUin:%d  ",  PlayerID, PlayerUin);
				//DWORD dwStart = GetTickCount(); //取windows启动到现在的流逝时间(毫秒)
				for (char i2 = 0; i2 < 6; i2++)
				{
					ClientNode* RoomClient = Clients[DstUin];
					if (RoomClient)
					{
						NotifyTranferByTCP(RoomClient, Uin, 0, Seq, DataBuf, len);	
					}
				}
				
				//DWORD dwUsed = GetTickCount() - dwStart; //计算该函数所消耗的时间
				//printf("Clients Search lost:%d ms\n", dwUsed);
				OptLength -= 6;
			}*/
			//UINT Time = Read32(pDstInfo);
			//UINT Temp = Read32(pDstInfo);
			//printf("\n");
			for (char i2 = 0; i2 < 6; i2++)
			{
				ClientNode* RoomClient = Room->Player[i2];
				if (RoomClient&&RoomClient!=Client)
				{
					NotifyTranferByTCP(RoomClient, Uin, 0, Seq, DataBuf, len);
				}
			}
			break;
		}
		case UDP_CMD_SHOW_MY_IP_PORT:
		{
			short SrcPlayerID = Read16(p); //src player id
			UINT SrcUin = Read32(p); //src player uin
			in_addr LocalIP;
			LocalIP.S_un.S_addr = Read32(p);
			USHORT LocalPort = Read16(p);

			//printf("SrcPlayerID:%d, SrcUin:%d\n", SrcPlayerID, SrcUin);

			p = option;
			Write16(p, SrcPlayerID); //SrcPlayerID
			Write32(p, SrcUin); //SrcUin
			Write32(p, LocalIP.S_un.S_addr); //SrcOuterIP
			Write16(p, LocalPort); //SrcOuterPort
			Write32(p, inet_addr(lpszRemoteAddress)); //SrcInerIP
			Write16(p, usRemotePort); //SrcInnerPort


			len = p - option;
			SendUdpData(lpszRemoteAddress, usRemotePort, UDP_CMD_RECV_OTHER_IP_PORT, option, len, Seq, DialogID, Uin);
			break;
		}
		case UDP_CMD_HEART_BEAT:
		{
			//UDP心跳
			//p = option;
			//printf("TransferCmd:%d iLength:%d\n ", TransferCmd, iLength);
			len = iLength - sizeof(TransferHead);
			SendUdpData(lpszRemoteAddress, usRemotePort, UDP_CMD_HEART_BEAT, p, len, Seq, DialogID, Uin);
			break;
		}
		default:
			//printf("TransferCmd:%d iLength:%d\n ", TransferCmd , iLength);
			//len = iLength - sizeof(TransferHead);
			//SendUdpData(lpszRemoteAddress, usRemotePort, TransferCmd, p, len, Seq, DialogID, Uin);

			break;
		}

		}
		catch (...)
		{
			printf("UDP Receive Exception!!!\n");
			fflush(stdout);
		}

		return HR_OK;
	}
	virtual EnHandleResult OnError(IUdpNode* pSender, EnSocketOperation enOperation, int iErrorCode, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pBuffer, int iLength)
	{
		return HR_OK;
	}
	virtual EnHandleResult OnShutdown(IUdpNode* pSender)
	{
		return HR_OK;
	}

};


int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	srand((unsigned)time(0)+GetSysTimeMicros());  // 产生随机种子  把0换成NULL也行
	//auto v1 = "v1.1-fix";

	
	//UITitleDispInfo_ADText = v1;//自行加密标题内容
#ifdef ZingSpeed
	SetConsoleTitle(TEXT("ZingSpeedServer"));
#else
	SetConsoleTitle(TEXT("QQSpeedServer"));
#endif
	// 加入崩溃dump文件功能
	//SetUnhandledExceptionFilter(ExceptionFilter);
	
	GameServer Server;

	Server.Run();
	
	//PrintfKart127616();
	_beginthread(Run2, NULL, NULL);
	

	while (1)
	{
		//主线程计算所有客户端在线时常 60秒检测一次
		Sleep(60000);
		OnlineTest();
	}
	return 0;
}
