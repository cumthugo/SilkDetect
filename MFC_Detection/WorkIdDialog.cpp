// WorkIdDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WorkIdDialog.h"
#include "afxdialogex.h"
#include "CSpreadSheet.h"
#include <algorithm>

// CWorkIdDialog �Ի���

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


// CWorkIdDialog ��Ϣ�������


BOOL CWorkIdDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CWorkIdDialog::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData(TRUE);
	if(find(m_arrWordIDs.begin(),m_arrWordIDs.end(),m_strInputID) != m_arrWordIDs.end())
	{
		CDialogEx::OnOK();
	}
	else
	{	
		MessageBox("�೤���δ�����ݿ��У����������룡","����",MB_OK | MB_ICONERROR);
		m_strInputID = "";
		GetDlgItem(IDC_EDIT1)->SetFocus();
	}
}
