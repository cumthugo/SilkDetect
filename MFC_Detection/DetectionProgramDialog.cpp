// DetectionProgramDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_Detection.h"
#include "DetectionProgramDialog.h"

#include "FrontUnitDialog.h"
#include "BackUnitDialog.h"
#include "HardLockDetectionDialog.h"
#include "NoLockUnitDialog.h"


// CDetectionProgramDialog 对话框

IMPLEMENT_DYNAMIC(CDetectionProgramDialog, CDialog)

CDetectionProgramDialog::CDetectionProgramDialog(const DetectionProgram& dp,CWnd* pParent /*=NULL*/)
	: CDialog(CDetectionProgramDialog::IDD, pParent)
{
	m_DetectionProgram.CopyOf(dp);
}

CDetectionProgramDialog::~CDetectionProgramDialog()
{
}

void CDetectionProgramDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_DetectionUnitList);
}


BEGIN_MESSAGE_MAP(CDetectionProgramDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CDetectionProgramDialog::OnBnClickedEdit)
	ON_LBN_DBLCLK(IDC_LIST2, &CDetectionProgramDialog::OnLbnDblclkList2)
END_MESSAGE_MAP()


// CDetectionProgramDialog 消息处理程序

BOOL CDetectionProgramDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText("编辑当前检测程序");

	RefreshDetectionUnits();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDetectionProgramDialog::OnBnClickedEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	DetectionProgram::iterator edit_it  = GetCurrentSelectedItem();
	if(edit_it != m_DetectionProgram.end())		// find it
	{
		shared_ptr<DetectionUnit> du = *edit_it;
		if(du->GetTypeId() == FrontDetectionUnit::TYPE_ID)
		{

			shared_ptr<FrontDetectionUnit> front_unit = dynamic_pointer_cast<FrontDetectionUnit>(du->Clone());
			assert(front_unit);
			CFrontUnitDialog fud(front_unit);
			if(fud.DoModal() == IDOK)
			{
				*edit_it = fud.m_FrontDetectionUnit;
				RefreshDetectionUnits();
			}
		}
		else if(du->GetTypeId() == BackDetectionUnit::TYPE_ID)
		{
			shared_ptr<BackDetectionUnit> back_unit = dynamic_pointer_cast<BackDetectionUnit>(du->Clone());
			assert(back_unit);
			CBackUnitDialog bud(back_unit);
			if(bud.DoModal() == IDOK)
			{
				*edit_it = bud.m_BackDetectionUnit;
				RefreshDetectionUnits();
			}
		}
		else if(du->GetTypeId() == HardLockDetectionUnit::TYPE_ID)
		{
			shared_ptr<HardLockDetectionUnit> hard_unit = dynamic_pointer_cast<HardLockDetectionUnit>(du->Clone());
			assert(hard_unit);
			CHardLockDetectionDialog hl_dialog(hard_unit);
			if(hl_dialog.DoModal() == IDOK)
			{
				*edit_it = hl_dialog.m_HardLockDetectionUnit;
				RefreshDetectionUnits();
			}
		}
		else if(du->GetTypeId() == NoLockDetectionUnit::TYPE_ID)
		{
			shared_ptr<NoLockDetectionUnit> nolock_unit = dynamic_pointer_cast<NoLockDetectionUnit>(du->Clone());
			assert(nolock_unit);
			CNoLockUnitDialog NLD(nolock_unit);
			if(NLD.DoModal() == IDOK)
			{
				*edit_it = NLD.m_NoLockDetectionUnit;
				RefreshDetectionUnits();
			}
		}
	}

}

DetectionProgram::iterator CDetectionProgramDialog::GetCurrentSelectedItem()
{
	CString strSelected;
	int sel = m_DetectionUnitList.GetCurSel();
	if(sel >= 0)
	{
		m_DetectionUnitList.GetText(sel,strSelected);
		return find_if(m_DetectionProgram.begin(),m_DetectionProgram.end(),bind2nd(NamedItem_Ptr_Find_PD<shared_ptr<DetectionUnit> >(),strSelected.GetString()));
	}
	else
		return m_DetectionProgram.end();
}

void CDetectionProgramDialog::RefreshDetectionUnits()
{
	m_DetectionUnitList.ResetContent();
	foreach(const shared_ptr<DetectionUnit>& du,m_DetectionProgram)
	{
		m_DetectionUnitList.AddString(du->Name.c_str());
	}
}
void CDetectionProgramDialog::OnLbnDblclkList2()
{
	OnBnClickedEdit();
}
