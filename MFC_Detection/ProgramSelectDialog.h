#pragma once
#include "afxwin.h"

enum DialogType{DIALOG_SELECT,DIALOG_ADD,DIALOG_EDIT,DIALOG_DEL};

// CProgramSelectDialog 对话框

class CProgramSelectDialog : public CDialog
{
	DECLARE_DYNAMIC(CProgramSelectDialog)

public:
	CProgramSelectDialog(DialogType dt,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProgramSelectDialog();

// 对话框数据
	enum { IDD = IDD_DLG_PROGRAM_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_LineList;
	CComboBox m_ProgramList;

	CString m_LineName;
	CString m_ProgramName;
	virtual BOOL OnInitDialog();
private:
	void CreateCtrl(CComboBox& box,UINT mCtrlID, const CRect& rect,DWORD style);
	void CreateLineCtrl(DWORD style);
	void CreateProgramCtrl(DWORD style);
	DialogType m_DialogType;
};
