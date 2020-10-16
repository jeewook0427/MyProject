
#include "pch.h"
#include "MainGame.h"

// ��������
HINSTANCE	g_hInstance;	// ���α׷� �ν��Ͻ� �ڵ�
HWND		g_hWnd;			// ������ �ڵ�
LPSTR		g_lpszClass = (LPSTR)TEXT("Factorio");

POINT		g_ptMouse;
MainGame mainGame;

//void SetWindowSize(int x, int y, int width, int height);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);

// �����츦 �����ϱ� ���� �Լ�
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
	LPSTR _lpszCmdParam, int nCmdShow)
{
	// ������ ������ ���� �⺻����
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;	// Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;	// ������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	// ������ Ŭ���� ���
	RegisterClass(&wndClass);

	// ������ ����
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass,
		WS_OVERLAPPEDWINDOW,
		WINSTART_X, WINSTART_Y,
		WINSIZE_X, WINSIZE_Y,
		NULL,
		NULL,
		g_hInstance,
		NULL);

	// ������ ���
	ShowWindow(g_hWnd, nCmdShow);

	// ������ �۾����� ����
	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

	// ���ΰ��� �ʱ�ȭ
	if (mainGame.Init())
	{
		return 0;
	}

	// �޽��� ť�� �ִ� �޽��� ó��
	MSG message;

	while (true)
	{
		if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)	break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TimeManager::GetSingleton()->Update(FPS);

			mainGame.Update();
			mainGame.Render();
		}
	}

	//while (GetMessage(&message, 0, 0, 0))
	//{
	//	TranslateMessage(&message);
	//	DispatchMessage(&message);
	//}

	// ����
	mainGame.Release();

	return message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	return mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}