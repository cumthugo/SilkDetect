#pragma once


// CRegLisenseDialog �Ի���

class CRegLisenseDialog : public CDialog
{
	DECLARE_DYNAMIC(CRegLisenseDialog)

public:
	CRegLisenseDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegLisenseDialog();

// �Ի�������
	enum { IDD = IDD_REG_PASSWORD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CString m_StrPassword;
};
