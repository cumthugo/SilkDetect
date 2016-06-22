#pragma once


// CEditPasswordDialog 对话框

class CEditPasswordDialog : public CDialog
{
	DECLARE_DYNAMIC(CEditPasswordDialog)

public:
	CEditPasswordDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEditPasswordDialog();

// 对话框数据
	enum { IDD = IDD_EDIT_PASSWORD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CString m_OldPassword;
	CString m_NewPassword;
	CString m_NewPasswordConfirm;
};
