#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <iostream>
#include <C:\Users\admin\Downloads\Introduction of graphics\Reversi_skeleton\Reversi\Reversi.h>
using namespace std;

LRESULT CALLBACK WindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );


void KeyDownEvent( WPARAM wParam )
{
	
	//==== Tab�BEnter�BCtrl... ====//
	if( wParam == VK_TAB ){
		cout << "Tab Down" << endl;
	}
	else if (wParam == VK_BACK){
		cout << "Back Down" << endl;
	}
	else if (wParam == VK_RETURN){
		cout << "Enter Down" << endl;
	}
	//==== �^��r���μƦr ====//
	else{
		cout << (char)wParam << " Down" << endl;
	}
}

void KeyUpEvent( WPARAM wParam )
{
	//==== Tab�BEnter�BCtrl... ====//
	if( wParam == VK_TAB )
	{
		cout << "Tab Up" << endl;
	}
	else if (wParam == VK_BACK){
		cout << "Back Up" << endl;
	}
	else if (wParam == VK_RETURN){
		cout << "Enter Up" << endl;
	}
	//==== �^��r���μƦr ====//
	else{
		cout << (char)wParam << " Up" << endl;
	}
}

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow )
{
	//==== ���U�������O ====//
	const wchar_t CLASS_NAME[]  = L"Sample Window Class";

	WNDCLASS wc = {};

	wc.lpfnWndProc   = WindowProc;
	wc.hInstance     = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass( &wc );

	//==== �Ыص��� ====//
	HWND hwnd = CreateWindowEx(
		0,                      // Optional window styles.
		CLASS_NAME,             // �������O
		L"Reversi",				// �������D
		WS_OVERLAPPEDWINDOW,    // ��������
		0, 0, 5, 5,				// �����j�p�Φ�m
		NULL,					// Parent ����    
		NULL,					// ���
		hInstance,				// Instance handle
		NULL					// Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	//==== �Ы� console ���� ====//
	AllocConsole();
	freopen( "CONOUT$", "wb", stdout );

	ShowWindow( hwnd, nCmdShow );
	UpdateWindow( hwnd );

	//==== ����T���j�� ====//
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
			EndPaint( hwnd, &ps );
		}
		return 0;

	case WM_KEYDOWN:
		system("cls");
		KeyDownEvent( wParam );
		break;

	case WM_KEYUP:
		system("cls");
		KeyUpEvent( wParam );		
		break;
	}

	return DefWindowProc( hwnd, uMsg, wParam, lParam );
}
