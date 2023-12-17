// Launcher.cpp : 定义应用程序的入口点。
//

#include "Launcher.h"
//#include "MetaString.h"
#include <shlobj_core.h>
#include <shlwapi.h>
#pragma comment (lib,"Shlwapi.lib")
#include <shellapi.h>
#pragma comment (lib,"Shell32.lib")


#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;									// 当前实例
WCHAR szTitle[MAX_LOADSTRING];						// 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING] = L"QQSpeed";	// 主窗口类名
HDC hMemDC;
HANDLE hLoaderBG;
HANDLE hRunSpeedGameEvent = NULL;
HANDLE hFileMap = NULL;
SharedData* pMapData = NULL;
HANDLE hGameProcess = NULL;
TCHAR GamePath[MAX_PATH] = L".";
TCHAR GameAppFile[MAX_PATH];

UINT LoginUin;
char LoginPwd[128];
wchar_t* Msg = NULL;


wchar_t* UTF8ToW(char* str, int len)
{
	wchar_t* result = new wchar_t[len + 1];
	len = MultiByteToWideChar(CP_UTF8, 0, str, len, result, len);
	result[len] = 0;
	return result;
}

char* WToUTF8(wchar_t* str, int len)
{
	int len2 = len * 6; //UTF-8：每个字符用1-6个字节表示。
	char* result = new char[len2 + 1];
	len2 = WideCharToMultiByte(CP_UTF8, 0, str, len, result, len2, 0, NULL);
	result[len2] = 0;
	return result;
}

wchar_t* AToW(char* str, int len)
{
	wchar_t* result = new wchar_t[len + 1];
	len = MultiByteToWideChar(CP_ACP, 0, str, len, result, len);
	result[len] = 0;
	return result;
}

char* WToA(wchar_t* str, int len)
{
	int len2 = len * 2; //Ansi：每个字符用1-2个字节表示。
	char* result = new char[len2 + 1];
	len2 = WideCharToMultiByte(CP_ACP, 0, str, len, result, len2, 0, NULL);
	result[len2] = 0;
	return result;
}


VOID myprintf(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	char bufer[1024];
	memset(bufer, 0, sizeof(bufer));
	int length = wvsprintfA(bufer, format, ap);
	va_end(ap);

	OutputDebugStringA(bufer);
}

void OnCopyData(HWND hWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	//printf("pCopyDataStruct->lpData:%d\n", pCopyDataStruct->lpData);
	switch (pCopyDataStruct->dwData)
	{
	case 1: //EDT_NotifyLoginResult 
	{
		NotifyLoginResult* pLoginResult = (NotifyLoginResult*)pCopyDataStruct->lpData;

		LPCSTR pstrMsg = NULL;
		switch (pLoginResult->LoginResult)
		{
		case eLoginSuccessed:
		case eLoginRequireReg:
		case eLoginVersionRecommend:
			//登录成功
			break;
		case eLoginFailed:
			pstrMsg = "登录失败，请确认用户名密码是否正确";
			break;
		case eLoginTimeout:
			pstrMsg = "对不起，登录超时，请确认网络状况";
			break;
		case eLoginCanceled:
			pstrMsg = "登录被取消";
			break;
		case eLoginIdentityLimit:
			pstrMsg = "由于身份限制，你无法进行登录";
			break;
		case eLoginVersionLimit:
			pstrMsg = "由于版本限制，你无法进行登录";
			break;
		case eLoginFileCracked:
			pstrMsg = "客户端文件损坏，无法登录";
			break;
		default:
			pstrMsg = "未知";
			break;
		}
		if (strlen(pLoginResult->ErrorMessage) > 0)
		{
			pstrMsg = pLoginResult->ErrorMessage;
		}
		if (pstrMsg)
		{
			MessageBoxA(pMapData->hWnd, pstrMsg, nullptr, MB_OK | MB_ICONHAND);
			DestroyWindow(pMapData->hWnd);
		}
		else
		{
			if (pLoginResult->Entity == eGameServer)
			{
				ShowWindow(pLoginResult->hWnd, SW_SHOW);
				DestroyWindow(pMapData->hWnd);
			}
		}
		//ShowWindow(pLoginResult->hWnd, SW_SHOW);
		DestroyWindow(pMapData->hWnd);
		break;
	}
	case 2: //提示
	{
		size_t len = pCopyDataStruct->cbData;
		char* str = (char*)pCopyDataStruct->lpData;
		if (str)
		{
			wchar_t* temp = Msg;
			Msg = NULL;
			if (temp)
			{
				delete[] temp;
			}
#ifdef ZingSpeed
			temp = new wchar_t[len + 1];
			memcpy(temp, str, len);
			temp[len] = 0;
			Msg = temp;
#else
			Msg = AToW(str, len);
#endif
			InvalidateRect(pMapData->hWnd, NULL, FALSE);

		}
		break;
	}
	case 3: //结束
		break;
	case 5: //?
		break;
	case 6: //开始
		break;
	default:
		break;
	}
}


void Cleanup()
{
	if (pMapData)
	{
		UnmapViewOfFile(pMapData);
	}
	if (hFileMap)
	{
		CloseHandle(hFileMap);
	}
	if (hRunSpeedGameEvent)
	{
		CloseHandle(hRunSpeedGameEvent);
	}
	if (hLoaderBG)
	{
		DeleteObject(hLoaderBG);
	}
	if (hMemDC)
	{
		DeleteDC(hMemDC);
	}
}




BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中
	TCHAR Buffer[1024];

	wsprintf(GameAppFile, TEXT("%s\\Releasephysx27\\GameApp.exe"), GamePath);
	if (!PathFileExists(GameAppFile))
	{
		DWORD sizo = MAX_PATH;
		if (ERROR_SUCCESS == RegGetValue(HKEY_LOCAL_MACHINE,
#ifdef ZingSpeed
			TEXT("Software\\VinaGame\\Zing Speed\\SYS"), TEXT("PathRoot")
#else
			TEXT("SOFTWARE\\Tencent\\QQ飞车\\SYS"), TEXT("PathRoot")
#endif
			, RRF_RT_REG_SZ | RRF_ZEROONFAILURE, NULL, &GamePath, &sizo))
		{
			wsprintf(GameAppFile, TEXT("%s\\Releasephysx27\\GameApp.exe"), GamePath);
			wsprintf(Buffer, TEXT("运行目录不正确, 但我们找到了正确的目录:\n%s\n\n以此目录启动游戏吗?"), GamePath);
			if (MessageBox(nullptr, Buffer, szTitle, MB_ICONINFORMATION | MB_YESNO) == IDNO)
			{
				return FALSE;
			}
		}
		else
		{
			MessageBox(nullptr, TEXT("无法找到游戏! 请尝试将本程序放入游戏目录运行."), szTitle, MB_ICONERROR);
			return FALSE;
		}
	}


	wsprintf(Buffer, TEXT("%s\\Loader\\LoaderBG.bmp"), GamePath);
	hLoaderBG = LoadImage(nullptr, Buffer, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	hMemDC = CreateCompatibleDC(NULL);
	SelectObject(hMemDC, hLoaderBG);


	INT x = 0; INT y = 0; INT w = 300; INT h = 200;
	RECT WorkAreaRect = { 0,0,0,0 };
	SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkAreaRect, 0);
	x = (WorkAreaRect.right - w) / 2 + x;
	y = (WorkAreaRect.bottom - h) / 2 + y;
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_POPUP, x, y, w, h, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd)
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	wsprintf(Buffer, L"RunSpeedGameEvent_%d", GetCurrentProcessId());
	hRunSpeedGameEvent = CreateEvent(NULL, TRUE, FALSE, Buffer);
	if (!hRunSpeedGameEvent)
	{
		MessageBox(hWnd, TEXT("创建事件失败"), szTitle, MB_ICONERROR);
		DestroyWindow(hWnd);
		return FALSE;
	}

	wsprintf(Buffer, TEXT("%d"), GetCurrentProcessId());
	SHELLEXECUTEINFO ShExecInfo{};
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = 0;
	ShExecInfo.lpVerb = L"runas";
	ShExecInfo.lpFile = GameAppFile;
	ShExecInfo.lpParameters = Buffer;
	ShExecInfo.nShow = SW_SHOWDEFAULT;
	if (ShellExecuteEx(&ShExecInfo))
	{
		hGameProcess = ShExecInfo.hProcess;
	}
	else
	{
		MessageBox(hWnd, TEXT("无法启动游戏"), szTitle, MB_ICONERROR);
		DestroyWindow(hWnd);
		return FALSE;
	}

	wsprintf(Buffer,
#ifdef ZingSpeed
		L"ZingSpeedMap_Shared_%d"
#else
		L"KartMap_Shared_%d"
#endif
		, GetCurrentProcessId());
	hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SharedData), Buffer);
	if (!hFileMap)
	{
		MessageBox(hWnd, L"共享内存建立失败，无法启动客户端", NULL, MB_ICONHAND | MB_OK);
		DestroyWindow(hWnd);
		return FALSE;
	}
	pMapData = (SharedData*)MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);
	if (!pMapData)
	{
		CloseHandle(hFileMap);
		MessageBox(hWnd, L"共享内存映射失败，无法启动客户端", NULL, MB_ICONHAND | MB_OK);
		DestroyWindow(hWnd);
		return FALSE;
	}
	else
	{
		LoginDialog(hWnd);//创建登录对话框
		if (LoginUin == 0)
		{
			if (hGameProcess)
			{
				TerminateProcess(hGameProcess, 0);
				CloseHandle(hGameProcess);
				hGameProcess = NULL;
			}
			DestroyWindow(hWnd);
			return FALSE;
		}

		char MyDocuments[MAX_PATH];
		pMapData->hWnd = hWnd;
		pMapData->Uin = LoginUin;
		pMapData->WorldID = 1;
		if (SHGetSpecialFolderPathA(NULL, MyDocuments, CSIDL_MYDOCUMENTS, false))
		{
			wsprintfA(pMapData->UserDir,
#ifdef ZingSpeed
				"%s\\Zing Speed\\%d"
#else
				"%s\\QQ飞车\\%d"
#endif
				, MyDocuments, pMapData->Uin);
		}
		pMapData->CommodityListCRC = 0;
		//lstrcpyA(pMapData->CommodityListURL, "http://update.zing.vcdn.vn/update/zs/commoditylist.201703231746.save.spd");
#ifdef ZingSpeed
		memcpy(pMapData->PwdMD5, "hi!!girl!!gogogo", 16);
		memset(pMapData->Key, 0, 16);
#else
		memcpy(pMapData->Key, "hi!!girl!!gogogo", 16);
#endif
		pMapData->SignKeyLen = strlen(lstrcpyA(pMapData->SignKey, LoginPwd));

	}
	SetEvent(hRunSpeedGameEvent);//运行客户端

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//GameApp窗口初始化的消息过程
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		BitBlt(hdc, 0, 0, 300, 200, hMemDC, 0, 0, SRCCOPY | CAPTUREBLT);
		if (Msg)
		{
			RECT Rect = { 0,0,300,200 };
			SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));
			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(255, 255, 255));
			DrawTextExW(hdc, Msg, -1, &Rect, DT_NOPREFIX | DT_NOCLIP | DT_EDITCONTROL, NULL);
		}
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_COPYDATA:
		OnCopyData((HWND)wParam, (COPYDATASTRUCT*)lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		SendMessage(hWnd, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAUNCHER));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = nullptr;

	return RegisterClassExW(&wcex);
}

int APIENTRY wWinMain(
	_In_ HINSTANCE		hInstance,
	_In_opt_ HINSTANCE	hPrevInstance,
	_In_ LPWSTR			lpCmdLine,
	_In_ int			nCmdShow
)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);

	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAUNCHER));

	MSG msg;

	// 主消息循环:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	Cleanup();
	return (int) msg.wParam;
}
