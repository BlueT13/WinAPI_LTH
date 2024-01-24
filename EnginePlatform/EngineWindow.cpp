#include "EngineWindow.h"
#include <EngineBase\EngineDebug.h>

bool EngineWindow::WindowLive = true;
HINSTANCE EngineWindow::hInstance;


LRESULT CALLBACK EngineWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		WindowLive = false;
		// PostQuitMessage(123213);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void EngineWindow::Init(HINSTANCE _hInst)
{
	hInstance = _hInst;
}


EngineWindow::EngineWindow() 
{
}

EngineWindow::~EngineWindow() 
{
}

void EngineWindow::Open(std::string_view _Title /*= "Title"*/)
{
	// ��Ȥ���ٰ� �������̳� ���ʿ� W�� �ٰų� A�� �پ��ִ� �Լ����� ���� �ɰ̴ϴ�.
	// A�� �پ������� ��Ƽ����Ʈ �Լ�
	// W�� �پ������� ���̵� ����Ʈ �Լ�
	WNDCLASSEXA wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "DefaultWindow";
	wcex.hIconSm = nullptr;

	RegisterClassExA(&wcex);

	// const std::string& = ���ο� ����� �ִٰ� �����϶�� �߳���?
	// std::vector<char> ��� �ִٰ� �����϶�� �ߴ�.
	// _Title[0] = char&�� �������� �Ͱ� ����.
	// _Title.c_str(); => �ڿ������� ���ο��� 
	// const char* Test = &_Title[0]
	// return Test;

	hWnd = CreateWindowA("DefaultWindow", _Title.data(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		MsgBoxAssert("������ ������ �����߽��ϴ�.");
		return;
	}

	hDC = GetDC(hWnd);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

}

unsigned __int64 EngineWindow::WindowMessageLoop(void(*_Update)(), void(*_End)())
{
	MSG msg = {};

	while (WindowLive)
	{
		// �⺻ �޽��� �����Դϴ�:
		// 10���� ������� 
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// �޼��� ������ ����Ÿ���̶�� ������ ����˴ϴ�.
		if (nullptr != _Update)
		{
			_Update();
		}
	}

	if (nullptr != _End)
	{
		_End();
	}

	return msg.wParam;
}


