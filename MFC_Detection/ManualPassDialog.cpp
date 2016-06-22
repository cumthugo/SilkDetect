// ManualPassDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ManualPassDialog.h"
#include "afxdialogex.h"
#include "WorkIdDialog.h"

// CManualPassDialog �Ի���

IMPLEMENT_DYNAMIC(CManualPassDialog, CDialogEx)

CManualPassDialog::CManualPassDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualPassDialog::IDD, pParent),m_MsgWnd(NULL)
{

}

CManualPassDialog::~CManualPassDialog()
{
}

void CManualPassDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManualPassDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_PASS, &CManualPassDialog::OnBnClickedBtnPass)
	ON_BN_CLICKED(IDC_BTN_FAIL, &CManualPassDialog::OnBnClickedBtnFail)
END_MESSAGE_MAP()


// CManualPassDialog ��Ϣ�������


void CManualPassDialog::OnBnClickedBtnPass()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CWorkIdDialog dlg;
	if(dlg.DoModal() == IDOK)
	{
		if(m_MsgWnd != NULL)
			::PostMessage(m_MsgWnd,WM_NOTIFY_MANUAL_PASS,MSG_PASS,0);
		EndDialog(0);
	}
	
}


void CManualPassDialog::OnBnClickedBtnFail()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_MsgWnd != NULL)
		::PostMessage(m_MsgWnd,WM_NOTIFY_MANUAL_PASS,MSG_FAIL,0);
	EndDialog(0);
}
