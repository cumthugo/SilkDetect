// RegLisenseDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include "RegLisenseDialog.h"
#include "afxdialogex.h"


// CRegLisenseDialog �Ի���

IMPLEMENT_DYNAMIC(CRegLisenseDialog, CDialog)

CRegLisenseDialog::CRegLisenseDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRegLisenseDialog::IDD, pParent)
	, m_StrPassword(_T(""))
{

}

CRegLisenseDialog::~CRegLisenseDialog()
{
}

void CRegLisenseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_StrPassword);
}


BEGIN_MESSAGE_MAP(CRegLisenseDialog, CDialog)
END_MESSAGE_MAP()


// CRegLisenseDialog ��Ϣ�������


void CRegLisenseDialog::OnOK()
{
	UpdateData(TRUE);
	if(m_StrPassword == "cumt#2012@tp%soft")
		CDialog::OnOK();
	else
	{
		m_StrPassword = "";
		MessageBox("�������","����",MB_ICONERROR | MB_OK);
		UpdateData(FALSE);
	}
}
