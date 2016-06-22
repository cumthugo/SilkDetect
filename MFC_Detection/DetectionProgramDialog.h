#pragma once
#include "afxwin.h"

#include "../DetectionLib/DetectionProgram.hpp"

// CDetectionProgramDialog �Ի���

class CDetectionProgramDialog : public CDialog
{
	DECLARE_DYNAMIC(CDetectionProgramDialog)

public:
	CDetectionProgramDialog(const DetectionProgram& dp,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDetectionProgramDialog();

// �Ի�������
	enum { IDD = IDD_DETECTION_PROGRAM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_DetectionUnitList;
	virtual BOOL OnInitDialog();

	void RefreshDetectionUnits();
	DetectionProgram m_DetectionProgram;
	afx_msg void OnBnClickedEdit();
	DetectionProgram::iterator GetCurrentSelectedItem();
	afx_msg void OnLbnDblclkList2();
};
