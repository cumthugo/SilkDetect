#pragma once


// CEnterPasswordDialog 对话框

class CEnterPasswordDialog : public CDialog
{
	DECLARE_DYNAMIC(CEnterPasswordDialog)

public:
	CEnterPasswordDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEnterPasswordDialog();

// 对话框数据
	enum { IDD = IDD_PASSWORD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Password;
	CString m_StrPassword;
	virtual void OnOK();
};