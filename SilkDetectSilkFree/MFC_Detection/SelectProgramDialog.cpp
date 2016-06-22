// SelectProgramDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "SelectProgramDialog.h"
#include "afxdialogex.h"


// CSelectProgramDialog 对话框

IMPLEMENT_DYNAMIC(CSelectProgramDialog, CDialog)

CSelectProgramDialog::CSelectProgramDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectProgramDialog::IDD, pParent)
	, m_StrFirstStepName(_T(""))
	, m_StrSecondStepName(_T(""))
{

}

CSelectProgramDialog::~CSelectProgramDialog()
{
}

void CSelectProgramDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_FirstStepListControl);
	DDX_Control(pDX, IDC_COMBO2, m_SecondStepListControl);
	DDX_CBString(pDX, IDC_COMBO1, m_StrFirstStepName);
	DDX_CBString(pDX, IDC_COMBO2, m_StrSecondStepName);
}


BEGIN_MESSAGE_MAP(CSelectProgramDialog, CDialog)
END_MESSAGE_MAP()


// CSelectProgramDialog 消息处理程序


const CString EmptyString = "空";

BOOL CSelectProgramDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_FirstStepListControl.Clear();
	foreach(shared_ptr<DetectionProgram> dp,*m_FirstStepLine)
	{
		m_FirstStepListControl.AddString(dp->Name.c_str());
	}
	m_FirstStepListControl.AddString(EmptyString);
	//set default
	if(m_FirstProgram->Name != "")
		m_FirstStepListControl.SelectString(0,m_FirstProgram->Name.c_str());
	else
		m_FirstStepListControl.SelectString(0,EmptyString);


	m_SecondStepListControl.Clear();
	foreach(shared_ptr<DetectionProgram> dp,*m_SecondStepLine)
	{
		m_SecondStepListControl.AddString(dp->Name.c_str());
	}
	m_SecondStepListControl.AddString(EmptyString);
	//set default
	if(m_SecondProgram->Name != "")
		m_SecondStepListControl.SelectString(0,m_SecondProgram->Name.c_str());
	else
		m_SecondStepListControl.SelectString(0,EmptyString);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSelectProgramDialog::OnOK()
{
	UpdateData(TRUE);
	if(m_StrFirstStepName == EmptyString)
		m_FirstProgram = shared_ptr<DetectionProgram>(new DetectionProgram);
	else
	{
		foreach(shared_ptr<DetectionProgram> dp,*m_FirstStepLine)
		{
			if(dp->Name == string(m_StrFirstStepName.GetString()))
			{
				m_FirstProgram = dp;
				break;
			}
		}
	}


	if(m_StrSecondStepName == EmptyString)
		m_SecondProgram = shared_ptr<DetectionProgram>(new DetectionProgram);
	else
	{
		foreach(shared_ptr<DetectionProgram> dp,*m_SecondStepLine)
		{
			if(dp->Name == string(m_StrSecondStepName.GetString()))
			{
				m_SecondProgram = dp;
				break;
			}
		}
	}
	CDialog::OnOK();
}
