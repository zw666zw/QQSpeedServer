#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "HPSocket/HPSocket.h"

#include <stdio.h>
#include <malloc.h>
#include <string>

extern "C" {
#include "oicq/tea.h"
}

#include "Utils.h"


std::string QQServerBindIP;
USHORT QQServerBindTcpPort;

struct ClientNode
{
	ITcpServer* Server;
	LONG_PTR BufferPtr;
	LONG_PTR BufferSize;
	LONG_PTR BufferOffset;
	int ConnID;
};

class QQServer : public CTcpServerListener
{
public:
	CTcpServerPtr TCP;
	QQServer() :TCP(this)
	{
		if (!TCP->Start(QQServerBindIP.c_str(), QQServerBindTcpPort))
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
			printf("[TCP][QQServer]Start Failed\n");
			return;
		}
	}

	void testSend(ClientNode* Client)
	{
		BYTE buf[2048]; BYTE* p = buf;
		WORD len;
		
		Write16(p, 0); //Length

		Write8(p, 2); //STX

		//Version
		Write8(p, 11);
		Write8(p, 0);

		Write16(p, 0x82); //Cmd
		Write16(p, 0); //Seq

		//body
		Write16(p, 0);
		Write16(p, 0);
		Write16(p, 1);

		BYTE MsgHead[260]; BYTE* pMsgHead = MsgHead;
		memset(MsgHead, 0, sizeof(MsgHead));
		Write8(pMsgHead, 0);
		Write8(pMsgHead, 0x28);
		Write8(pMsgHead, 0);

		int outlen = 0;
		BYTE key[16];
		//memset(key, 0, sizeof(key));
		memcpy(key, "hi!!girl!!gogogo", 16);


		memcpy(pMsgHead, "hi!!girl!!gogogo", 16); //QQKey
		pMsgHead += 16;

		pMsgHead += 28; //???

		Write8(pMsgHead, 1); //SignKeyLength
		memcpy(pMsgHead, "!", 1);
		pMsgHead += 1;


		oi_symmetry_encrypt2(MsgHead, sizeof(MsgHead), key, p, &outlen);
		p += outlen;


		Write8(p, 3); //end

		len = p - buf;
		Set16(buf, len);


		TCP->Send(Client->ConnID, buf, len);
	}

	void OnFullReceive(ClientNode* Client, BYTE* Data, int Length)
	{
		Read16(Data); //Length
		Read8(Data); //STX 02开始标志
		Read16(Data); //Version
		short Cmd = Read16(Data);
		Read16(Data); //Seq
		Read32(Data); //uin
		Read16(Data);
		BYTE* key = Data;
		Data += 16;

		int len = Length - 2 - 1 - 2 - 2 - 4 - 2 - 16 - 1;
		BYTE* out = (BYTE*)malloc(len);
		oi_symmetry_decrypt2(Data, len, key, out, &len);

		//Data += len;
		//Read8(Data); //03结束标志
		printf("[QQServer][ConnID:%d]RecvCmd:%d\n", Client->ConnID, Cmd);
		free(out);

		//testSend(Client);
	}

private:
	virtual EnHandleResult OnPrepareListen(ITcpServer* pSender, SOCKET soListen)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
		//printf("[TCP][QQServer]Start Success\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		return HR_OK;
	}

	virtual EnHandleResult OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient)
	{
		ClientNode* Client = new ClientNode;
		memset(Client, 0, sizeof(ClientNode));
		Client->Server = pSender;
		Client->ConnID = dwConnID;
		pSender->SetConnectionExtra(dwConnID, Client);
		return HR_OK;
	}

	virtual EnHandleResult OnHandShake(ITcpServer* pSender, CONNID dwConnID)
	{
		return HR_IGNORE;
	}

	virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
	{
		ClientNode* Client;
		pSender->GetConnectionExtra(dwConnID, (PVOID*)&Client);

		long left;
		long need;
		const int MaxBuf = 8192;
		void* p;
		do
		{
			if (Client->BufferPtr)
			{
				if (Client->BufferOffset < sizeof(short))
				{
					left = min(iLength, int(sizeof(short) - Client->BufferOffset));
					memcpy((void*)(Client->BufferPtr + Client->BufferOffset), pData, left);
					Client->BufferOffset += left;
					if (Client->BufferOffset < sizeof(short))
					{
						break;
					}
					pData += left;
					iLength -= left;
				}
				need = ntohs(*(u_short*)Client->BufferPtr);
				left = need - Client->BufferOffset;
				if (need > Client->BufferSize)
				{
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
				if (iLength < sizeof(short))
				{
					need = sizeof(short);
				}
				else
				{
					need = ntohs(*(u_short*)pData);
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
		return HR_OK;
	}

	virtual EnHandleResult OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
	{
		return HR_OK;
	}

	virtual EnHandleResult OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
	{
		ClientNode* Client;
		pSender->GetConnectionExtra(dwConnID, (PVOID*)&Client);
		printf("[QQServer][ConnID:%d]OnClose\n", dwConnID);

		if (Client->BufferPtr)
		{
			free((PVOID)Client->BufferPtr);
		}
		delete Client;
		//Client = NULL;
		return HR_OK;
	}

	virtual EnHandleResult OnShutdown(ITcpServer* pSender)
	{
		printf("[QQServer]Close\n");
		return HR_OK;
	}
};


QQServer* Server = NULL;

/*void StartQQServer(std::string IP, USHORT Port)
{
	QQServerBindIP = IP;
	QQServerBindTcpPort = Port;
	Server = new QQServer;
}*/
void StartQQServer()
{
	Server = new QQServer;
}
