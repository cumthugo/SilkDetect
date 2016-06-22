// EnterPasswordDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "EnterPasswordDialog.h"
#include "afxdialogex.h"

#include "../DetectionLib/md5.h"
// CEnterPasswordDialog 对话框

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


// CEnterPasswordDialog 消息处理程序


void CEnterPasswordDialog::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
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
		MessageBox("密码错误！","错误",MB_OK | MB_ICONERROR);
		m_StrPassword = "";
		UpdateData(FALSE);
	}
}
