#include "stdafx.h"
#include "Comm.h"


bool Comm::ConnectComm( const CString& comName )
{
	HANDLE hCom;
	hCom=CreateFile(comName,
		GENERIC_READ|GENERIC_WRITE, //允许读和写
		0, //独占方式
		NULL,
		OPEN_EXISTING, //打开而不是创建
		FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, //重叠方式
		NULL);
	if( hCom== INVALID_HANDLE_VALUE) return false;

	SetupComm(hCom,100,100); //输入缓冲区和输出缓冲区的大小都是100

	COMMTIMEOUTS TimeOuts;
	//设定读超时
	TimeOuts.ReadIntervalTimeout=MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier=50;
	TimeOuts.ReadTotalTimeoutConstant=100;

	//设定写超时
	TimeOuts.WriteTotalTimeoutMultiplier=100;
	TimeOuts.WriteTotalTimeoutConstant=500;
	SetCommTimeouts(hCom,&TimeOuts); //设置超时

	DCB dcb;
	GetCommState(hCom,&dcb);
	dcb.BaudRate=9600; //波特率为9600
	dcb.ByteSize=8; //每个字节有8位
	dcb.Parity=NOPARITY; //无奇偶校验位
	dcb.StopBits=ONESTOPBIT; //1个停止位
	SetCommState(hCom,&dcb);
	PurgeComm(hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	itsCommAndWnd.hCom = hCom;
	return true;
}

bool Comm::SendCommData( UCHAR sendValue )
{
	if(itsCommAndWnd.hCom == INVALID_HANDLE_VALUE) return false;

	OVERLAPPED m_osWrite;
	memset(&m_osWrite,0,sizeof(OVERLAPPED));
	m_osWrite.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);

	char lpOutBuffer[1];
	lpOutBuffer[0]=sendValue;

	DWORD dwBytesWrite=1;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	ClearCommError(itsCommAndWnd.hCom,&dwErrorFlags,&ComStat);
	bWriteStat=WriteFile(itsCommAndWnd.hCom,lpOutBuffer,
		dwBytesWrite,& dwBytesWrite,&m_osWrite);

	if(!bWriteStat)
	{
		if(GetLastError()==ERROR_IO_PENDING)
		{
			WaitForSingleObject(m_osWrite.hEvent,800);
			GetOverlappedResult(itsCommAndWnd.hCom,&m_osWrite,&dwBytesWrite,TRUE);
		}
	}
	CloseHandle(m_osWrite.hEvent);
	if(dwBytesWrite != 1) //something wrong!
		return false;
	else
		return true;
}




UINT ReadReportThread(LPVOID pParam)
{
	CommAndClientWnd *pCommAndClientWnd;
	DWORD Length;
	CString Str;
	//接收报告用的OVERLAPPED。
	OVERLAPPED ReadOverlapped;
	ReadOverlapped.Offset=0;
	ReadOverlapped.OffsetHigh=0;
	//创建一个事件，提供给ReadFile使用，当ReadFile完成时，
	//会设置该事件为触发状态。
	ReadOverlapped.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	//接收报告的缓冲区，1字节
	UCHAR ReadReportBuffer[1];

	pCommAndClientWnd=(CommAndClientWnd*)pParam;
	while(1)
	{
		ResetEvent(ReadOverlapped.hEvent);
		if(pCommAndClientWnd->hCom != INVALID_HANDLE_VALUE) 
		{
			ReadFile(pCommAndClientWnd->hCom,ReadReportBuffer,1,NULL,&ReadOverlapped);
			//等待事件触发
			DWORD dwWaitObj = WaitForSingleObject(ReadOverlapped.hEvent,100);
			GetOverlappedResult(pCommAndClientWnd->hCom,&ReadOverlapped,&Length,TRUE);
			if(dwWaitObj == WAIT_OBJECT_0 || dwWaitObj == WAIT_TIMEOUT)
			{
				if(Length==1)
					::PostMessage(pCommAndClientWnd->hClientWnd,WM_COMM_EVENT,(WPARAM)ReadReportBuffer[0],NULL);
				PurgeComm(pCommAndClientWnd->hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
			}
		}

	}
	return 0;
}

bool Comm::StartReceive()
{
	if(itsCommAndWnd.hClientWnd == NULL) return false;
	if(itsCommAndWnd.hCom == INVALID_HANDLE_VALUE) return false;
	CWinThread * pReadReportThread;
	pReadReportThread=AfxBeginThread(ReadReportThread,
		&itsCommAndWnd,
		THREAD_PRIORITY_NORMAL,
		0,
		CREATE_SUSPENDED,
		NULL);
	if(pReadReportThread==NULL) return false;
	pReadReportThread->ResumeThread();
	return true;
}
void Comm::SetClientWnd( HWND hWnd )
{
	itsCommAndWnd.hClientWnd = hWnd;
}
