// WorkIdDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "WorkIdDialog.h"
#include "afxdialogex.h"
#include "CSpreadSheet.h"
#include <algorithm>

// CWorkIdDialog 对话框

IMPLEMENT_DYNAMIC(CWorkIdDialog, CDialogEx)

CWorkIdDialog::CWorkIdDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWorkIdDialog::IDD, pParent)
	, m_strInputID(_T(""))
{

}

CWorkIdDialog::~CWorkIdDialog()
{
}

void CWorkIdDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strInputID);
	DDX_Control(pDX, IDC_EDIT1, m_edtInputID);
}


BEGIN_MESSAGE_MAP(CWorkIdDialog, CDialogEx)
END_MESSAGE_MAP()


// CWorkIdDialog 消息处理程序


BOOL CWorkIdDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CSpreadSheet SS(".\\ID.xls", "Sheet1");
	int rows = SS.GetTotalRows();
	CString strID;
	for (int i = 2;i<= rows ; i++)
	{
		SS.ReadCell(strID,2,i);
		m_arrWordIDs.push_back(strID);		
	}

	if(m_strInputID != "")
		UpdateData(FALSE);
	GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT1)->SetFocus();
	m_edtInputID.SetSel(0,-1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CWorkIdDialog::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(TRUE);
	if(find(m_arrWordIDs.begin(),m_arrWordIDs.end(),m_strInputID) != m_arrWordIDs.end())
	{
		CDialogEx::OnOK();
	}
	else
	{	
		MessageBox("班长编号未在数据库中，请重新输入！","错误",MB_OK | MB_ICONERROR);
		m_strInputID = "";
		GetDlgItem(IDC_EDIT1)->SetFocus();
	}
}
