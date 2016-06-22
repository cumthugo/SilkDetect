// ManualPassDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "ManualPassDialog.h"
#include "afxdialogex.h"
#include "WorkIdDialog.h"

// CManualPassDialog 对话框

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


// CManualPassDialog 消息处理程序


void CManualPassDialog::OnBnClickedBtnPass()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	if(m_MsgWnd != NULL)
		::PostMessage(m_MsgWnd,WM_NOTIFY_MANUAL_PASS,MSG_FAIL,0);
	EndDialog(0);
}
