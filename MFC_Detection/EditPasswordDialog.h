#pragma once


// CEditPasswordDialog �Ի���

class CEditPasswordDialog : public CDialog
{
	DECLARE_DYNAMIC(CEditPasswordDialog)

public:
	CEditPasswordDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditPasswordDialog();

// �Ի�������
	enum { IDD = IDD_EDIT_PASSWORD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CString m_OldPassword;
	CString m_NewPassword;
	CString m_NewPasswordConfirm;
};
