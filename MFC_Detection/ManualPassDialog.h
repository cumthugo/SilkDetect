#pragma once

#include "resource.h"

// CManualPassDialog �Ի���

#define WM_NOTIFY_MANUAL_PASS (WM_USER+101)
#define MSG_PASS 1
#define MSG_FAIL 2

class CManualPassDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CManualPassDialog)

public:
	CManualPassDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CManualPassDialog();

// �Ի�������
	enum { IDD = IDD_DLG_MANUAL_PASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnPass();
	afx_msg void OnBnClickedBtnFail();
	HWND m_MsgWnd;
};
