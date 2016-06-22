#pragma once

#include "resource.h"

// CManualPassDialog 对话框

#define WM_NOTIFY_MANUAL_PASS (WM_USER+101)
#define MSG_PASS 1
#define MSG_FAIL 2

class CManualPassDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CManualPassDialog)

public:
	CManualPassDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CManualPassDialog();

// 对话框数据
	enum { IDD = IDD_DLG_MANUAL_PASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnPass();
	afx_msg void OnBnClickedBtnFail();
	HWND m_MsgWnd;
};
