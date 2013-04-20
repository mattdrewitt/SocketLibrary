#include <TCPClient.hpp>
#include <windows.h>
#include <windowsx.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <ostream>
#include <sstream>



using namespace std;

#define ID_INPUT	1
#define ID_OUTPUT	2
#define ID_BET		3
#define ID_HIT		4
#define ID_STAND	5
#define ID_DOUBLE	6
#define ID_SPLIT	7
#define ID_READY	8


//globals 
TCPClient tcpclient;
map<int, string> acceptedMoves;
string acceptedMoveMessage = "";

//Helper Functions. 
int checkForInt(std::string bet){
	bool check = std::all_of(bet.begin(), bet.end(), ::isdigit);
	if(check){
		return atoi(bet.c_str());
	}
	else{
		return 0;
	}
}


pair<int, string> ProcessChoice(){
	std::string choice;
	cin >> choice;
	int numCheck = checkForInt(choice);
	while(numCheck == 0){
		//cout << "Incorrect choice. please chose again." << endl;
		string choice = "";
		//cin >> choice;
		numCheck = checkForInt(choice);
		if(numCheck != 0){
			break;
		}
	}

	if(acceptedMoves.count(numCheck)== 1 ){
		return pair<int, string>(numCheck, acceptedMoves.find(numCheck)->second);
	}
	else{
		return pair<int, string>(0,"");
	}
	//now check if the number is in our map. 	
}


//gonna change to disable the choice buttons 
void ouputChoices(std::string choices) {
	//choices sperated based on "|"
	string word;
	stringstream stream(choices);
	acceptedMoveMessage = "Please Chose an option to procceed in the game:\n";
	int count = 0;
	while( getline(stream, word, '|') ){
		count++;
		acceptedMoveMessage +=	"Choose" + std::to_string(count) + " for " + word + "\n";
		acceptedMoves.insert(pair<int, string>(count, word));
	}
	cout << acceptedMoveMessage << endl;
	cout << "" << endl;
	cout << "Your Choice is: " << endl;
}

BOOL WINAPI ConsoleHandler(DWORD CEvent)
{
    char mesg[128];
	//in each of these cases we want to send a message to the server telling it to
	//kill our legacy. 
    switch(CEvent)
    {
    case CTRL_CLOSE_EVENT:
		tcpclient.Send("x");
        break;
    case CTRL_LOGOFF_EVENT:
        
        break;
    case CTRL_SHUTDOWN_EVENT:
       
        break;

    }
    return TRUE;
}


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

	SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler,TRUE);

	//need to start doing client stuff here. 
	unsigned int clientId;
	std::string revCommand = "";
	pair<int, string> choiceToSend;
	std::string choice;
	tcpclient = TCPClient("127.0.0.1", 80);
	//2) Client Connects 
	tcpclient.Connect();
	//4) Client Recvs Id. 	client.clientId
	clientId = atoi((tcpclient.Recv()).c_str()); 
	string messageData = "";
	int goodData = 0;
	appendText(L" Client Id recieved...");
	appendText(std::to_wstring(clientId).c_str());

	for(;;){
	char command = (tcpclient.Recv())[0];
	  Edit_Enable(hwndBet,false);
	  Edit_Enable(hwndHit, false);
      Edit_Enable(hwndStand, false);
      Edit_Enable(hwndDouble, false);
      Edit_Enable(hwndSplit, false);
      Edit_Enable(hwndReady, false);
	  if(command == 'q'){
		}
	  if(command == 'b'){
		  appendText(L"Please make a bet now.");
		  Edit_Enable(hwndBet,true);
		  break;
		}
	}
	while(GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}




LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, 
						 WPARAM wParam, LPARAM lParam)
{
	wstring tw;
	std::string t;
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
		case WM_DESTROY:
		PostQuitMessage(0);
		break;
	  	
	   case ID_BET:
			  wchar_t buff[1024];			
			  GetWindowText(hwndInput, buff, 1024);
			  tcpclient.Send("b");
			  tw = wcscat(buff, L"\n");
			  t = string(tw.begin(), tw.end());
			  tcpclient.Send(t);
			  appendText(L"Bet Sent to Server.");
			break;
		case ID_HIT:
			//appendText(L"Hit\n");
			break;
		case ID_STAND:
			//appendText(L"Stand\n");
			break;
		case ID_DOUBLE:
			//appendText(L"Double Down\n");
			break;
		case ID_SPLIT:
			//appendText(L"Split\n");
			break;
		case ID_READY:
			//appendText(L"Ready\n");
			break;
		}
	break;
	}//end outer switch 

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}
