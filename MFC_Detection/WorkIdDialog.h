#pragma once
#include "resource.h"
#include <list>
#include "afxwin.h"

using namespace std;

// CWorkIdDialog 对话框

class CWorkIdDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CWorkIdDialog)

public:
	CWorkIdDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWorkIdDialog();

// 对话框数据
	enum { IDD = IDD_DLG_WORK_ID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	list<CString> m_arrWordIDs;
	CString m_strInputID;
	CEdit m_edtInputID;
};
