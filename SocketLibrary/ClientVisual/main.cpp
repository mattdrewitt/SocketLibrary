#include <windows.h>
#include <windowsx.h>
#include <string>

#define ID_INPUT	1
#define ID_OUTPUT	2
#define ID_BET		3
#define ID_HIT		4
#define ID_STAND	5
#define ID_DOUBLE	6
#define ID_SPLIT	7
#define ID_READY	8

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static HWND hwndOutput;
static HWND hwndInput;
HWND hwndBet;
HWND hwndHit;
HWND hwndStand;
HWND hwndDouble;
HWND hwndSplit;
HWND hwndReady;

void appendText(LPCTSTR newText)
{
  DWORD l,r;
  int size = GetWindowTextLength(hwndOutput);
  SendMessage(hwndOutput, EM_GETSEL,(WPARAM)&l,(LPARAM)&r);
  SendMessage(hwndOutput, EM_SETSEL, size, size);
  SendMessage(hwndOutput, EM_REPLACESEL, 0, (LPARAM)newText);
  SendMessage(hwndOutput, EM_SETSEL,l,r);

}
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					PWSTR lpCmdLine, int nCmdShow )
{
	MSG  msg;    
	WNDCLASSW wc = {0};
	wc.lpszClassName = L"Black Jack";
	wc.hInstance     = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc   = WndProc;
	wc.hCursor       = LoadCursor(0,IDC_ARROW);

	RegisterClassW(&wc);
	CreateWindowW(wc.lpszClassName, L"Black Jack",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		220, 220, 600, 490, 0, 0, hInstance, 0);  

	while(GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, 
						 WPARAM wParam, LPARAM lParam)
{
	//static HWND hwndOutput;
	//static HWND hwndInput;
	//HWND hwndButton;

	switch(msg)
	{
	case WM_CREATE:

		hwndOutput = CreateWindowW(L"Edit", NULL, 
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL,
			10, 10, 560, 400, hwnd, (HMENU) ID_OUTPUT,
			NULL, NULL);

		
		hwndHit = CreateWindowW(L"button", L"Hit",
			WS_VISIBLE | WS_CHILD, 10, 417, 50, 25,
			hwnd, (HMENU) ID_HIT, NULL, NULL);

		hwndStand = CreateWindowW(L"button", L"Stand",
			WS_VISIBLE | WS_CHILD, 65, 417, 75, 25,
			hwnd, (HMENU) ID_STAND, NULL, NULL);

		hwndDouble = CreateWindowW(L"button", L"Double Down",
			WS_VISIBLE | WS_CHILD, 145, 417, 110, 25,
			hwnd, (HMENU) ID_DOUBLE, NULL, NULL);

		hwndSplit = CreateWindowW(L"button", L"Split",
			WS_VISIBLE | WS_CHILD, 260, 417, 60, 25,
			hwnd, (HMENU) ID_SPLIT, NULL, NULL);

		hwndReady = CreateWindowW(L"button", L"Ready",
			WS_VISIBLE | WS_CHILD, 325, 417, 75, 25,
			hwnd, (HMENU) ID_READY, NULL, NULL);

		hwndInput = CreateWindowW(L"Edit", NULL, 
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			405, 420, 90, 20, hwnd, (HMENU) ID_INPUT,
			NULL, NULL);

		hwndBet = CreateWindowW(L"button", L"Bet",
			WS_VISIBLE | WS_CHILD, 500, 417, 50, 25,
			hwnd, (HMENU) ID_BET, NULL, NULL);

		break;

	case WM_COMMAND:	
		switch(wParam)
		{
		case ID_BET:
			wchar_t buff[1024];
			//Edit_Enable(hwndBet, false);
			GetWindowText(hwndInput, buff, 1024);
			appendText(L"Betting: ");
			wcscat(buff, L"\n");
			appendText(buff);
			break;
		case ID_HIT:
			appendText(L"Hit\n");
			break;
		case ID_STAND:
			appendText(L"Stand\n");
			break;
		case ID_DOUBLE:
			appendText(L"Double Down\n");
			break;
		case ID_SPLIT:
			appendText(L"Split\n");
			break;
		case ID_READY:
			appendText(L"Ready\n");
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}
