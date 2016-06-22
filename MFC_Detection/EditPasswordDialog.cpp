// EditPasswordDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include "EditPasswordDialog.h"
#include "afxdialogex.h"

#include "../DetectionLib/md5.h"

// CEditPasswordDialog �Ի���

IMPLEMENT_DYNAMIC(CEditPasswordDialog, CDialog)

CEditPasswordDialog::CEditPasswordDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEditPasswordDialog::IDD, pParent)
	, m_OldPassword(_T(""))
	, m_NewPassword(_T(""))
	, m_NewPasswordConfirm(_T(""))
{

}

CEditPasswordDialog::~CEditPasswordDialog()
{
}

void CEditPasswordDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_OldPassword);
	DDX_Text(pDX, IDC_EDIT2, m_NewPassword);
	DDX_Text(pDX, IDC_EDIT3, m_NewPasswordConfirm);
}


BEGIN_MESSAGE_MAP(CEditPasswordDialog, CDialog)
END_MESSAGE_MAP()


// CEditPasswordDialog ��Ϣ�������


void CEditPasswordDialog::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData(TRUE);
	MD5 md5;
	CString ExpertPassword;
	::GetPrivateProfileString("Manage","Password","",ExpertPassword.GetBuffer(100),100,".\\Config.ini");
	ExpertPassword.ReleaseBuffer();
	md5.update(m_OldPassword.GetString());
	md5.update(md5.toString());
	if(md5.toString() == string(ExpertPassword.GetString())) // Old password ok
	{
		if(m_NewPassword != m_NewPasswordConfirm) 
		{
			MessageBox("��������β�һ�£����������룡");
			m_NewPassword = m_NewPasswordConfirm = "";
			UpdateData(FALSE);
			return;
		}
		if(m_NewPassword.GetLength() < 4)
		{
			MessageBox("���벻��С��4λ�����������룡");
			m_NewPassword = m_NewPasswordConfirm = "";
			UpdateData(FALSE);
			return;
		}
		MD5 write_md5;
		write_md5.update(m_NewPassword.GetString());
		write_md5.update(write_md5.toString());
		::WritePrivateProfileString("Manage","Password",write_md5.toString().c_str(),".\\Config.ini");
		MessageBox("�����޸ĳɹ���");
		CDialog::OnOK();
	}
}
