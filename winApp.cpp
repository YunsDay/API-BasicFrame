#include "winApp.h"
#include "resource.h"

C_WINAPP* C_WINAPP::m_pApp{};

BOOL C_WINAPP::init(HINSTANCE hInstance)
{
	initMsgTable();

	m_hinstance = hInstance;
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hinstance;
	wcex.hIcon = LoadIcon(m_hinstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT7));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = L"name";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassExW(&wcex);


	m_hWnd= CreateWindowW(L"name", nullptr, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hinstance, nullptr);

	if (!m_hWnd)
		return FALSE;

	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hWnd);

	return TRUE;
}

void C_WINAPP::updateMsg()
{
	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK C_WINAPP::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return m_pApp->appProc(hWnd, message, wParam, lParam);
}

LRESULT C_WINAPP::appProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(message < WM_USER && m_arMsgTable[message])
		return (this->*m_arMsgTable[message])(hWnd, wParam,lParam);

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void C_WINAPP::initMsgTable()
{
	m_arMsgTable[WM_KEYDOWN] = &C_WINAPP::onKeyDown;
	m_arMsgTable[WM_PAINT] = &C_WINAPP::onPaint;
	m_arMsgTable[WM_DESTROY] = &C_WINAPP::onDestroy;
	m_arMsgTable[WM_MOUSEMOVE] = &C_WINAPP::onMouseMove;
}

LRESULT C_WINAPP::onKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (wParam == VK_ESCAPE)
		DestroyWindow(hWnd);

	return S_OK;
}

LRESULT C_WINAPP::onPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);


	// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
	EndPaint(hWnd, &ps);

	return S_OK;
}

LRESULT C_WINAPP::onDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return S_OK;
}

LRESULT C_WINAPP::onMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	m_nMousePosX = lParam & 0x0000ffff;
	m_nMousePosY = (lParam >> 16) & 0x0000ffff;

	InvalidateRect(hWnd, nullptr, TRUE);

	return S_OK;
}

void C_WINAPP::createApp()
{
	if(!m_pApp)
		m_pApp = new C_WINAPP{};
}

C_WINAPP* C_WINAPP::getApp()
{
	return m_pApp;
}

void C_WINAPP::releaseApp()
{
	if (m_pApp)
	{
		delete m_pApp;
		m_pApp = nullptr;
	}
}
