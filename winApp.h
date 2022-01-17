#pragma once

#include <Windows.h>
#include <stdio.h>

class C_WINAPP
{
private:

	LRESULT (C_WINAPP::*m_arMsgTable[WM_USER])(HWND, WPARAM , LPARAM);

	static C_WINAPP* m_pApp;
	HINSTANCE	m_hinstance;
	HWND		m_hWnd;

	int m_nMousePosX;
	int m_nMousePosY;
private:
	C_WINAPP() = default;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT appProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void initMsgTable();
	LRESULT onKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
	LRESULT onPaint(HWND hWnd, WPARAM wParam, LPARAM lParam);
	LRESULT onDestroy(HWND hWnd,  WPARAM wParam, LPARAM lParam);
	LRESULT onMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);
public:
	static void createApp();
	static C_WINAPP* getApp();
	static void releaseApp();

	BOOL init(HINSTANCE hInstance);
	void updateMsg();
	

};
