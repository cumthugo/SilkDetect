#pragma once
#include "afxwin.h"


// CSelectProgramDialog �Ի���
#include "../DetectionLib/DetectionLine.hpp"

class CSelectProgramDialog : public CDialog
{
	DECLARE_DYNAMIC(CSelectProgramDialog)

public:
	CSelectProgramDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelectProgramDialog();

// �Ի�������
	enum { IDD = IDD_SELECT_PROGRAM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_FirstStepListControl;
	CComboBox m_SecondStepListControl;
	CString m_StrFirstStepName;
	CString m_StrSecondStepName;

	DetectionLine* m_FirstStepLine;
	DetectionLine* m_SecondStepLine;

	shared_ptr<DetectionProgram> m_FirstProgram;
	shared_ptr<DetectionProgram> m_SecondProgram;

	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
