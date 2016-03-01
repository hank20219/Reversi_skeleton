#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <string>
#include <iostream>
#include "Reversi.h"
using namespace std;
static int cursor[2] = { 0,0 };
static Reversi *reversi = new Reversi();
LRESULT CALLBACK WindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

void clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
	SetConsoleCursorPosition(console, topLeft);
}
void DrawBoard() {
	string drawnBoard = "";
	int countOK = 0;
	int countBlack = 0, countWhite = 0;
	clear();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (cursor[0] == j && cursor[1] == i) {
				drawnBoard += "㊣";
				if (reversi->getBW(j, i) == 2) {
					countWhite++;
				}else if (reversi->getBW(j, i) == 1) {
					countBlack++;
				}
			}
			else {
				switch (reversi->getBW(j, i)) {
				case 2:
					drawnBoard += "●";
					countWhite++;
					break;
				case 1:
					drawnBoard += "○";
					countBlack++;
					break;
				default:
					if (reversi->chkBoard[j][i] == 1) {
						drawnBoard += "．";
						countOK++;
					}else{ 
						drawnBoard += "—"; 
					}
					
					break;
				}
			}
		}
		drawnBoard += "\n";
	}
	cout << drawnBoard << endl;
	if (!reversi->isPass()) {
		if (reversi->isBW()) { cout << "Now: ○" << endl; }
		else { 
			cout << "Now: ●" << endl; 
			if (reversi->isPassed&&reversi->isPass()) {
				if (countBlack > countWhite) {
					cout << "Black wins!" << endl;
				}
				else if (countBlack == countWhite) {
					cout << "Draw!" << endl;
				}
				else {
					cout << "White wins!" << endl;
				}
			}
		}
	}
	if(countOK==0){ reversi->bBW = !reversi->bBW; }
	cout << "Steps : " << reversi->curRecord << endl;
	//cout << "Target : " << reversi->mBoard[cursor[1]][cursor[0]] << endl;
	cout << "○ : " << countBlack << "● : " << countWhite << endl;
	cout << "Move : Arrow Key" << endl;
	cout << "Select : Enter" << endl;
	cout << "Undo : BackSpace" << endl;
	cout << "Redo : Tab" << endl;
}
void KeyDownEvent( WPARAM wParam )
{
	//==== Tab、Enter、Ctrl... ====//
	if( wParam == VK_TAB ){
		cout << "Tab Down" << endl;
		reversi->Redo();
	}
	else if (wParam == VK_BACK){
		cout << "Back Down" << endl;
		reversi->Undo();
	}
	else if (wParam == VK_RETURN){
		if (reversi->moveAnalyze(cursor[0], cursor[1])) {
				reversi->setBW(cursor[0], cursor[1]);
				reversi->bBW = !reversi->bBW;
		}
		cout << "Enter Down" << endl;
	}
	//==== Moving cursor ====//
	else if (wParam == '%') //left arrow
	{
		if (cursor[0] <= 0) { cursor[0] = 0; }
		else { cursor[0]--; }
	}
	else if (wParam == '&') //up arrow
	{
		if (cursor[1] <= 0) { cursor[1] = 0; }
		else { cursor[1]--; }
	}
	else if (wParam == 39) //right arrow
	{
		if (cursor[0] >= 7) { cursor[0] = 7; }
		else { cursor[0]++; }
	}
	else if (wParam == '(') //down arrow
	{
		if (cursor[1] >= 7) { cursor[1] = 7; }
		else { cursor[1]++; }
	}
	//==== 英文字母或數字 ====//
	else{
		cout << (char)wParam << " Down" << endl;
	}
}

void KeyUpEvent( WPARAM wParam )
{
	DrawBoard();
}

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow )
{
	//==== 註冊視窗類別 ====//
	const wchar_t CLASS_NAME[]  = L"Sample Window Class";

	WNDCLASS wc = {};
	
	wc.lpfnWndProc   = WindowProc;
	wc.hInstance     = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass( &wc );

	//==== 創建視窗 ====//
	HWND hwnd = CreateWindowEx(
		0,                      // Optional window styles.
		CLASS_NAME,             // 視窗類別
		L"Reversi",				// 視窗標題
		WS_OVERLAPPEDWINDOW,    // 視窗風格
		0, 0, 5, 5,				// 視窗大小及位置
		NULL,					// Parent 視窗    
		NULL,					// 選單
		hInstance,				// Instance handle
		NULL					// Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	//==== 創建 console 視窗 ====//
	AllocConsole();
	freopen( "CONOUT$", "wb", stdout );

	ShowWindow( hwnd, nCmdShow );
	UpdateWindow( hwnd );

	//==== 執行訊息迴圈 ====//
	MSG msg = { };
	while ( GetMessage(&msg, NULL, 0, 0) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	return 0;
}

LRESULT CALLBACK WindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint( hwnd, &ps );
			FillRect( hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
			DrawBoard();
			EndPaint( hwnd, &ps );
		}
		return 0;

	case WM_KEYDOWN:
		DrawBoard();
		KeyDownEvent( wParam );
		break;

	case WM_KEYUP:
		KeyUpEvent( wParam );
		DrawBoard();
		break;
	}

	return DefWindowProc( hwnd, uMsg, wParam, lParam );
}