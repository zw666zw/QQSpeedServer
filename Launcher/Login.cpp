#include "framework.h"
#include "Resource.h"
//#include "MetaString.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include <shlwapi.h>
#pragma comment (lib,"Shlwapi.lib")

#include "..\Server\Utils.h"
#include "..\Server\oicq\tea.h"

extern HINSTANCE hInst;
extern TCHAR GamePath[MAX_PATH];
extern TCHAR GameAppFile[MAX_PATH];
extern UINT LoginUin;
extern char LoginPwd[128];
UINT IP = 0;
USHORT Port = 0;
BYTE Key[16];

HDC hMemDC2;
HANDLE hLoaderBG2;


constexpr int WM_MY_ASYNCSOCKET = (WM_APP + 1);
SOCKET hSocket = NULL;
LONG_PTR BufferPtr = NULL;
LONG_PTR BufferSize = 0;
LONG_PTR BufferOffset = 0;


char* domainip = NULL;
//char *downip[32] = { NULL };


void lookdns(char* domain)
{
	char** pptr = NULL;
	HOSTENT* pHostEntry = gethostbyname(domain);
	if (pHostEntry != NULL)
	{
		int i = 0;
		//将主机地址列表输出，可含多个 
		char* szIpBuff = NULL;
		for (i = 0, pptr = pHostEntry->h_addr_list; *pptr != NULL; ++pptr, i++)
		{
			szIpBuff = new char[32];
			memset(szIpBuff, 0, 32);
			//inet_ntop的返回值为NULL，则表示失败，否则返回相应的IP地址（此时szIpRet指向的是szIpBuff） 
			const char* szIpRet = inet_ntop(pHostEntry->h_addrtype, *pptr, szIpBuff, 32);
			domainip = szIpBuff;
			//MessageBoxA(NULL, domainip, NULL, NULL);
		}
	}
	return;
}

void CloseConnect()
{
	if (hSocket)
	{
		closesocket(hSocket);
		hSocket = 0;
	}
}

void ConnectServer(HWND hWnd)
{
	CloseConnect();
	sockaddr_in addr;
	hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	addr.sin_family = PF_INET;
	addr.sin_addr.S_un.S_addr = IP;
	addr.sin_port = htons(Port);

	connect(hSocket, (sockaddr*)&addr, sizeof(addr));

	WSAAsyncSelect(hSocket, hWnd, WM_MY_ASYNCSOCKET, FD_READ | FD_WRITE | FD_CLOSE);
}


void MyResponseGetUin(HWND hDlg, BYTE* Body, DWORD BodyLen)
{
	//获取Uin 等信息
	USHORT Result = Read16(Body);
	UINT Uin = Read32(Body);

	if (Uin == 0)
	{
		MessageBoxW(hDlg, L"The username is invalid", L"Login", MB_OK);
	}
	else
	{
		LoginUin = Uin;
		EndDialog(hDlg, 0);
	}
}

void MyResponseRegister(HWND hDlg, BYTE* Body, DWORD BodyLen)
{
	USHORT Result = Read16(Body);

	if (Result == 0)
	{
		MessageBoxW(hDlg, L"Register Success", L"Register", MB_OK);
		EndDialog(hDlg, 0);
	}
	else
	{
		MessageBoxW(hDlg, L"Register Failed", L"Register", MB_OK);
	}
}

void OnRecvFromServer(HWND hDlg, USHORT MsgID, BYTE* Body, DWORD BodyLen)
{
	switch (MsgID)
	{
	case 1:
		MyResponseGetUin(hDlg, Body, BodyLen);
		break;
	case 2:
		MyResponseRegister(hDlg, Body, BodyLen);
		break;
	default:
		break;
	}
}

void SendToServer(short MsgID, const BYTE* Data, DWORD Length, short SrcID, char DstFE, short DstID, short MsgType, char Encrypt)
{
	CSHEAD* ProtocolHead;
	MSGHEAD* MsgHead;
	void* MsgBody;
	int TotalLength;

	int MsgLen = sizeof(MSGHEAD) + USHORT(Length);
	MsgHead = (MSGHEAD*)malloc(MsgLen);
	if (!MsgHead)
	{
		return;
	}
	MsgHead->MsgID = htons(MsgID);
	MsgHead->MsgType = htons(MsgType);
	MsgHead->MsgSeq = ntohl(-1);
	MsgHead->SrcFE = 1;
	MsgHead->DstFE = DstFE;
	MsgHead->SrcID = htons(SrcID);
	MsgHead->DstID = htons(DstID);
	MsgHead->BodyLen = ntohs(sizeof(USHORT) + USHORT(Length));
	MsgBody = (void*)(MsgHead + 1);
	memcpy(MsgBody, Data, Length);
	if (Encrypt)
	{
		int EncryptLen = oi_symmetry_encrypt2_len(MsgLen);
		TotalLength = sizeof(CSHEAD) + EncryptLen;
		if (!(ProtocolHead = (CSHEAD*)malloc(TotalLength)))
		{
			return;
		}
		oi_symmetry_encrypt2((BYTE*)MsgHead, MsgLen, Key, (BYTE*)(ProtocolHead + 1), &EncryptLen);
		TotalLength = sizeof(CSHEAD) + EncryptLen;
	}
	else
	{
		TotalLength = sizeof(CSHEAD) + MsgLen;
		if (!(ProtocolHead = (CSHEAD*)malloc(TotalLength)))
		{
			return;
		}
		memcpy((MSGHEAD*)(ProtocolHead + 1), MsgHead, MsgLen);
	}
	free(MsgHead);

	ProtocolHead->TotalLength = htonl(TotalLength);
	ProtocolHead->Ver = ntohs(116);
	ProtocolHead->DialogID = htons(SrcID);
	ProtocolHead->Seq = ntohl(0);
	ProtocolHead->Uin = ntohl(0);
	ProtocolHead->BodyFlag = Encrypt;
	ProtocolHead->OptLength = 0;

	int LeftoverLength = TotalLength;
	int SendLength;
	char* p = (char*)ProtocolHead;
	while (LeftoverLength > 0)
	{
		SendLength = send(hSocket, p, LeftoverLength, 0);
		if (SendLength <= 0)
		{
			break;
		}
		p += SendLength;
		LeftoverLength -= SendLength;
	}
	free(ProtocolHead);
}

void OnFullReceive(HWND hDlg, void* Data, ULONG_PTR Length)
{
	CSHEAD* ProtocolHead = (CSHEAD*)Data;
	MSGHEAD* MsgHead;
	BYTE* Body;

	DWORD HeadLen = sizeof(CSHEAD) + ProtocolHead->OptLength;
	DWORD BodyLen = Length - HeadLen;
	if (BodyLen)
	{
		MsgHead = (MSGHEAD*)((DWORD)Data + HeadLen);
		if (ProtocolHead->BodyFlag)
		{
			Body = (BYTE*)malloc(BodyLen);
			if (!Body)
			{
				return;
			}
			if (oi_symmetry_decrypt2((BYTE*)MsgHead, BodyLen, Key, Body, (int*)&BodyLen) == false)
			{
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

		OnRecvFromServer(hDlg, ntohs(MsgHead->MsgID), Body, ntohs(MsgHead->BodyLen));

		free(MsgHead);
	}
}

void OnAsyncSocket(HWND hDlg, SOCKET hSocket, WORD Event, WORD Error)
{
	switch (Event)
	{
	case FD_READ:
	{
		char buf[4096];
		char* pData = buf;
		int iLength = recv(hSocket, buf, sizeof(buf), 0);
		if (iLength <= 0)
		{
			break;
		}
		long left;
		long need;
		void* p;
		do
		{
			if (BufferPtr)
			{
				if (BufferOffset < sizeof(int))
				{
					left = min(iLength, int(sizeof(int) - BufferOffset));
					memcpy((void*)(BufferPtr + BufferOffset), pData, left);
					BufferOffset += left;
					if (BufferOffset < sizeof(int))
					{
						break;
					}
					pData += left;
					iLength -= left;
				}
				need = ntohl(*(u_long*)BufferPtr);
				left = need - BufferOffset;
				if (need > BufferSize)
				{
					BufferSize = need;
					p = realloc((void*)BufferPtr, BufferSize);
					if (!p)
					{
						//printf("内存不足\n");
						break;
					}
					BufferPtr = (ULONG_PTR)p;
				}
				if (left >= 0)
				{
					left = min(iLength, left);
					memcpy((void*)(BufferPtr + BufferOffset), pData, left);
					BufferOffset += left;
					if (BufferOffset < need)
					{
						break;
					}
					OnFullReceive(hDlg, (BYTE*)BufferPtr, need);
					pData += left;
					iLength -= left;
				}
				free((void*)BufferPtr);
				BufferPtr = 0;
				BufferOffset = 0;
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
					BufferSize = need;
					p = malloc(BufferSize);
					if (!p)
					{
						//printf("内存不足\n");
						break;
					}
					BufferPtr = (ULONG_PTR)p;
					memcpy((void*)BufferPtr, pData, iLength);
					BufferOffset = iLength;
					break;
				}
				else
				{
					OnFullReceive(hDlg, (BYTE*)pData, need);
					pData += need;
					iLength -= need;
				}
			}
		} while (false);
		break;
	}
	case FD_WRITE:
		//已连接服务器
		break;
	case FD_CLOSE:
		//连接关闭
		break;
	}
}


void MyRequestGetUin(char* u)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	len = strlen(u);
	Write8(p, (BYTE)len);
	memcpy(p, u, len);
	p += len;

	len = p - buf;
	SendToServer(1, buf, len, 0, 0, 0, 0, true);
}

void MyRequestRegister(char* u, char* pwd)
{
	BYTE buf[8192];
	BYTE* p = buf;
	size_t len;

	len = strlen(u);
	Write8(p, (BYTE)len);
	memcpy(p, u, len);
	p += len;

	len = strlen(pwd);
	Write8(p, (BYTE)len);
	memcpy(p, pwd, len);
	p += len;

	len = p - buf;
	SendToServer(2, buf, len, 0, 0, 0, 0, true);
}


INT_PTR CALLBACK Register(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MY_ASYNCSOCKET:
	{
		OnAsyncSocket(hDlg, (SOCKET)wParam, WSAGETSELECTEVENT(lParam), WSAGETSELECTERROR(lParam));
		return (INT_PTR)TRUE;
	}
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hWnd;
			int Length;

			hWnd = GetDlgItem(hDlg, IDC_EDITUN);
			Length = GetWindowTextLengthA(hWnd);
			if (Length == 0)
			{
				MessageBoxW(hDlg, L"Please enter a username", L"Register", MB_OK);
				break;
			}
			if (Length > 128)
			{
				MessageBoxW(hDlg, L"The username is too long", L"Register", MB_OK);
				break;
			}
			Length++;
			char* u = new char[Length];
			GetWindowTextA(hWnd, u, Length);

			hWnd = GetDlgItem(hDlg, IDC_EDITPWD);
			Length = GetWindowTextLengthA(hWnd);
			if (Length == 0)
			{
				MessageBoxW(hDlg, L"Please enter a password", L"Register", MB_OK);
				break;
			}
			if (Length > 128)
			{
				MessageBoxW(hDlg, L"The password is too long", L"Register", MB_OK);
				break;
			}
			Length++;
			char* p = new char[Length];
			GetWindowTextA(hWnd, p, Length);

			ConnectServer(hDlg);
			MyRequestRegister(u, p);

			delete[] u;
			delete[] p;

			return (INT_PTR)TRUE;
		}
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		default:
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Login(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MY_ASYNCSOCKET:
	{
		OnAsyncSocket(hDlg, (SOCKET)wParam, WSAGETSELECTEVENT(lParam), WSAGETSELECTERROR(lParam));
		return (INT_PTR)TRUE;
	}
	case WM_PAINT:
	{
		char user[127] = { 0 };
		char pass[127] = { 0 };
		HWND hWnd;
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hDlg, &ps);
		BitBlt(hdc, 0, 0, 520, 159, hMemDC2, 0, 0, SRCCOPY | CAPTUREBLT);
		EndPaint(hDlg, &ps);
		hWnd = GetDlgItem(hDlg, IDC_EDITUN);

		GetPrivateProfileStringA("ServerInfo1", "user", "1", user, 127, ".\\DirSvrInfo1.ini");
		SetWindowTextA(hWnd, user);
		hWnd = GetDlgItem(hDlg, IDC_EDITPWD);
		GetPrivateProfileStringA("ServerInfo1", "pwd", "1", pass, 127, ".\\DirSvrInfo1.ini");
		SetWindowTextA(hWnd, pass);
		return (INT_PTR)TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		HDC hdc = (HDC)wParam;
		SetBkMode(hdc, TRANSPARENT);
		RECT rc;
		GetClientRect((HWND)lParam, &rc);
		MapWindowPoints((HWND)lParam, hDlg, (POINT*)&rc, CWP_SKIPDISABLED);

		return (INT_PTR)GetStockObject(HOLLOW_BRUSH);
	}
	case WM_INITDIALOG:
		//ConnectServer(hDlg);
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hWnd;
			int Length;
			
			hWnd = GetDlgItem(hDlg, IDC_EDITUN);
			Length = GetWindowTextLengthA(hWnd);
			if (Length == 0)
			{
				MessageBoxW(hDlg, L"Please enter a username", L"Login", MB_OK);
				break;
			}
			if (Length > 128)
			{
				MessageBoxW(hDlg, L"The username is too long", L"Login", MB_OK);
				break;
			}
			Length++;
			char* u = new char[Length];
			GetWindowTextA(hWnd, u, Length);
			//SetWindowTextA(hWnd,)
			WritePrivateProfileStringA("ServerInfo1", "user", u, ".\\DirSvrInfo1.ini");
			hWnd = GetDlgItem(hDlg, IDC_EDITPWD);
			
			Length = GetWindowTextLengthA(hWnd);
			if (Length == 0)
			{
				MessageBoxW(hDlg, L"Please enter a password", L"Login", MB_OK);
				break;
			}
			if (Length > 128)
			{
				MessageBoxW(hDlg, L"The password is too long", L"Login", MB_OK);
				break;
			}
			Length++;
			char* p = new char[Length];
			GetWindowTextA(hWnd, p, Length);
			WritePrivateProfileStringA("ServerInfo1", "pwd", p, ".\\DirSvrInfo1.ini");
			StrCpyA(LoginPwd, p);

			ConnectServer(hDlg);
			MyRequestGetUin(u);

			delete[] u;
			delete[] p;

			return (INT_PTR)TRUE;
		}
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		case IDC_BUTTONREGISTER:
			DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_REGISTER), hDlg, Register, NULL);
			break;
		default:
			break;
		}
		break;
	case WM_DESTROY:
		CloseConnect();
		return (INT_PTR)TRUE;
	}
	return (INT_PTR)FALSE;
}


BOOL LoginDialog(HWND hWnd)
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return FALSE;
	}

	TCHAR ini[MAX_PATH];
	lstrcpy(ini, GamePath);
	lstrcat(ini,TEXT("\\DirSvrInfo1.ini"));

	TCHAR ret[64];
	char domain[64] = { 0 };
	GetPrivateProfileString(TEXT("ServerInfo1"), TEXT("IP"), TEXT("127.0.0.1"), ret, 64, ini);
	GetPrivateProfileStringA("ServerInfo1", "Domain", "127.0.0.1", domain, 64, ".\\DirSvrInfo1.ini");
	lookdns(domain);
	char* plong = (char*)&IP;
	CHAR* pdomain = domainip;
	TCHAR* p = ret;
	if(domainip)
	{
		//inet_addr 1
		WritePrivateProfileStringA("ServerInfo1", "IP", domainip, ".\\DirSvrInfo1.ini");
		//解析并写入
		for (size_t i = 0; i < 4; i++)
		{
			*plong++ = atoi(pdomain);
			pdomain = StrChrA(pdomain, '.');
			if (pdomain)
			{
				++pdomain;
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		//inet_addr 2
		for (size_t i = 0; i < 4; i++)
		{
			*plong++ = _ttoi(p);
			p = StrChr(p, '.');
			if (p)
			{
				++p;
			}
			else
			{
				break;
			}
		}
	}
	

	GetPrivateProfileString(TEXT("ServerInfo1"), TEXT("Ports"), TEXT("27015,27015,27015"), ret, 64, ini);
	p = StrChr (ret, ',');
	if (p)
	{
		*p = 0;
	}
	Port = _ttoi(ret);

	memcpy(Key, "hi!!girl!!gogogo", 16);
	hLoaderBG2 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_LOGIN));
	hMemDC2 = CreateCompatibleDC(NULL);
	SelectObject(hMemDC2, hLoaderBG2);

	DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_LOGIN), hWnd, Login, NULL);

	DeleteObject(hLoaderBG2);
	DeleteDC(hMemDC2);

	WSACleanup();
	return FALSE;
}