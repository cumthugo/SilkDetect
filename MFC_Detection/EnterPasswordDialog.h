#pragma once


// CEnterPasswordDialog �Ի���

class CEnterPasswordDialog : public CDialog
{
	DECLARE_DYNAMIC(CEnterPasswordDialog)

public:
	CEnterPasswordDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEnterPasswordDialog();

// �Ի�������
	enum { IDD = IDD_PASSWORD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_Password;
	CString m_StrPassword;
	virtual void OnOK();
};