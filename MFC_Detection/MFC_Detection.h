
// MFC_Detection.h : MFC_Detection Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMFC_DetectionApp:
// �йش����ʵ�֣������ MFC_Detection.cpp
//

class CMFC_DetectionApp : public CWinApp
{
public:
	CMFC_DetectionApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFC_DetectionApp theApp;
