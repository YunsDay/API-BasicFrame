// WindowsProject7.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "winApp.h"


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    C_WINAPP::createApp();
    C_WINAPP::getApp()->init(hInstance);
    C_WINAPP::getApp()->updateMsg();
    C_WINAPP::releaseApp();

	return 0;
}


