// ProgramSelectDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_Detection.h"
#include "ProgramSelectDialog.h"


// CProgramSelectDialog �Ի���

IMPLEMENT_DYNAMIC(CProgramSelectDialog, CDialog)

CProgramSelectDialog::CProgramSelectDialog(DialogType dt,CWnd* pParent /*=NULL*/)
	: CDialog(CProgramSelectDialog::IDD, pParent),m_DialogType(dt)
{

}

CProgramSelectDialog::~CProgramSelectDialog()
{
}

void CProgramSelectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProgramSelectDialog, CDialog)
END_MESSAGE_MAP()


// CProgramSelectDialog ��Ϣ�������

BOOL CProgramSelectDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(m_DialogType == DIALOG_ADD)
	{
		CreateLineCtrl(CBS_DROPDOWN);
		CreateProgramCtrl(CBS_DROPDOWN);
	}
	else
	{
		CreateLineCtrl(CBS_DROPDOWNLIST);
		CreateProgramCtrl(CBS_DROPDOWNLIST);
	}
	if(m_DialogType == DIALOG_ADD)
		SetWindowText("����-��Ӽ�����");
	else if(m_DialogType == DIALOG_EDIT)
		SetWindowText("����-�༭������");
	else if(m_DialogType == DIALOG_DEL)
		SetWindowText("����-ɾ��������");
	else
		SetWindowText("ѡ�������");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CProgramSelectDialog::CreateCtrl(CComboBox& box, UINT mCtrlID, const CRect& rect,DWORD style )
{
	DWORD box_style = WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP | style;
	box.CreateEx(NULL,"ComboBox",NULL,box_style,rect,this,mCtrlID);

}

void CProgramSelectDialog::CreateLineCtrl( DWORD style )
{
	CreateCtrl(m_LineList,10001,CRect(130,45,300,195),style);
}

void CProgramSelectDialog::CreateProgramCtrl( DWORD style )
{
	CreateCtrl(m_ProgramList,10002,CRect(130,90,300,240),style);
}