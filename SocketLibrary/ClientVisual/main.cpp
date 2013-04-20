#include <windows.h>
#include <string>

#define ID_INPUT 1
#define ID_BUTTON 2
#define ID_OUTPUT 3
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static HWND hwndOutput;
static HWND hwndInput;
HWND hwndButton;

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

		hwndInput = CreateWindowW(L"Edit", NULL, 
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 420, 450, 20, hwnd, (HMENU) ID_INPUT,
			NULL, NULL);

		hwndButton = CreateWindowW(L"button", L"Submit",
			WS_VISIBLE | WS_CHILD, 470, 417, 100, 25,
			hwnd, (HMENU) ID_BUTTON, NULL, NULL);

		break;

	case WM_COMMAND:	

		if (HIWORD(wParam) == BN_CLICKED) {

			//int len = GetWindowTextLengthW(hwndInput) + 1;
			wchar_t buff[1024];
			GetWindowText(hwndInput, buff, 1024);
			wcscat(buff, L"\n");
			appendText(buff);
			//GetWindowTextW(hwndInput, text, len);
			//SetWindowTextW(hwndOutput, text);
		}
		break;

	case WM_KEYDOWN:		// Press a key (as in typing)
			appendText(L"Key Down");
			switch ( wParam )
			{ 
			case VK_RETURN:
				appendText(L"Enter!");

				wchar_t buff[1024];
				GetWindowText(hwndInput, buff, 1024);
				wcscat(buff, L"\n");
				appendText(buff);
				break;
			}
			break;
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}
