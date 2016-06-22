// EnterPasswordDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include "EnterPasswordDialog.h"
#include "afxdialogex.h"

#include "../DetectionLib/md5.h"
// CEnterPasswordDialog �Ի���

IMPLEMENT_DYNAMIC(CEnterPasswordDialog, CDialog)

CEnterPasswordDialog::CEnterPasswordDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEnterPasswordDialog::IDD, pParent)
	, m_StrPassword(_T(""))
{

}

CEnterPasswordDialog::~CEnterPasswordDialog()
{
}

void CEnterPasswordDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_StrPassword);
}


BEGIN_MESSAGE_MAP(CEnterPasswordDialog, CDialog)
END_MESSAGE_MAP()


// CEnterPasswordDialog ��Ϣ�������


void CEnterPasswordDialog::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData(TRUE);
	MD5 md5;
	CString ExpertPassword;
	::GetPrivateProfileString("Manage","Password","",ExpertPassword.GetBuffer(100),100,".\\Config.ini");
	ExpertPassword.ReleaseBuffer();
	md5.update(m_StrPassword.GetString());
	md5.update(md5.toString());
	if(md5.toString() == string(ExpertPassword.GetString()))
		CDialog::OnOK();
	else
	{	
		MessageBox("�������","����",MB_OK | MB_ICONERROR);
		m_StrPassword = "";
		UpdateData(FALSE);
	}
}
