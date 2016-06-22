#pragma once
#include "resource.h"
#include <list>
#include "afxwin.h"

using namespace std;

// CWorkIdDialog �Ի���

class CWorkIdDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CWorkIdDialog)

public:
	CWorkIdDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWorkIdDialog();

// �Ի�������
	enum { IDD = IDD_DLG_WORK_ID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	list<CString> m_arrWordIDs;
	CString m_strInputID;
	CEdit m_edtInputID;
};
