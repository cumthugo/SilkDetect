#pragma once


// CRegLisenseDialog 对话框

class CRegLisenseDialog : public CDialog
{
	DECLARE_DYNAMIC(CRegLisenseDialog)

public:
	CRegLisenseDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRegLisenseDialog();

// 对话框数据
	enum { IDD = IDD_REG_PASSWORD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CString m_StrPassword;
};
