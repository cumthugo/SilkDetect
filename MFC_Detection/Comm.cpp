#include "stdafx.h"
#include "Comm.h"


bool Comm::ConnectComm( const CString& comName )
{
	HANDLE hCom;
	hCom=CreateFile(comName,
		GENERIC_READ|GENERIC_WRITE, //�������д
		0, //��ռ��ʽ
		NULL,
		OPEN_EXISTING, //�򿪶����Ǵ���
		FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, //�ص���ʽ
		NULL);
	if( hCom== INVALID_HANDLE_VALUE) return false;

	SetupComm(hCom,100,100); //���뻺����������������Ĵ�С����100

	COMMTIMEOUTS TimeOuts;
	//�趨����ʱ
	TimeOuts.ReadIntervalTimeout=MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier=50;
	TimeOuts.ReadTotalTimeoutConstant=100;

	//�趨д��ʱ
	TimeOuts.WriteTotalTimeoutMultiplier=100;
	TimeOuts.WriteTotalTimeoutConstant=500;
	SetCommTimeouts(hCom,&TimeOuts); //���ó�ʱ

	DCB dcb;
	GetCommState(hCom,&dcb);
	dcb.BaudRate=9600; //������Ϊ9600
	dcb.ByteSize=8; //ÿ���ֽ���8λ
	dcb.Parity=NOPARITY; //����żУ��λ
	dcb.StopBits=ONESTOPBIT; //1��ֹͣλ
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
	//���ձ����õ�OVERLAPPED��
	OVERLAPPED ReadOverlapped;
	ReadOverlapped.Offset=0;
	ReadOverlapped.OffsetHigh=0;
	//����һ���¼����ṩ��ReadFileʹ�ã���ReadFile���ʱ��
	//�����ø��¼�Ϊ����״̬��
	ReadOverlapped.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	//���ձ���Ļ�������1�ֽ�
	UCHAR ReadReportBuffer[1];

	pCommAndClientWnd=(CommAndClientWnd*)pParam;
	while(1)
	{
		ResetEvent(ReadOverlapped.hEvent);
		if(pCommAndClientWnd->hCom != INVALID_HANDLE_VALUE) 
		{
			ReadFile(pCommAndClientWnd->hCom,ReadReportBuffer,1,NULL,&ReadOverlapped);
			//�ȴ��¼�����
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
