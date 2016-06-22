#pragma once

#include "stdafx.h"

/* 串口通信的变量 */
struct CommAndClientWnd
{
	CommAndClientWnd(HANDLE h = INVALID_HANDLE_VALUE, HWND wnd = NULL):hCom(h),hClientWnd(wnd){}
	HANDLE hCom;
	HWND hClientWnd;
};

#define WM_COMM_EVENT (WM_USER+100)

class Comm
{
public:
	//operator
	bool ConnectComm(const CString& comName);
	bool SendCommData(UCHAR sendValue);
	bool StartReceive();
	//Set Wnd
	void SetClientWnd(HWND hWnd);
private:
	CommAndClientWnd itsCommAndWnd;
};