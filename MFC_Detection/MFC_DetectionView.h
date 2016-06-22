
// MFC_DetectionView.h : CMFC_DetectionView ��Ľӿ�
//


#pragma once

#include "../DetectionLib/DetectionLine.hpp"
#include "../DetectionLib/DetectionResult.hpp"

#include "afxwin.h"

#include "ManualPassDialog.h"


class CMFC_DetectionView : public CFormView
{
protected: // �������л�����
	CMFC_DetectionView();
	DECLARE_DYNCREATE(CMFC_DetectionView)

public:
	enum{ IDD = IDD_MFC_DETECTION_FORM };

// ����
public:
	CMFC_DetectionDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

//�Լ��Ľӿ�

	DetectionResult Detect( IplImage_Ptr img,shared_ptr<DetectionProgram> dp);
	shared_ptr<DetectionProgram> GetDetectionProgram();
	void ShowResult(DetectionResult& dr);
	CvvImage itsResultImage;
	CBrush m_Brush;
	bool PassPassword();
	bool PassLicense();

	DetectionLine m_FirstStepLine;
	DetectionLine m_SecondStepLine;
	shared_ptr<DetectionProgram> m_FirstProgram;
	shared_ptr<DetectionProgram> m_SecondProgram;

	//add in 2015/4/30 for param of save sample images
	string itsScreenShotPath;
	int itsMaxImagesPerFolder;
// ʵ��
public:
	virtual ~CMFC_DetectionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGetPic();

	afx_msg LRESULT OnCommProc(WPARAM wParam, LPARAM lParam);

	void StartManualJudge();

	CString m_ErrorString;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedGetPic2();
	afx_msg void OnBnClickedGetPic3();
	CEdit m_editError;
	CFont m_editFont;
	afx_msg void OnMenuSelectProgram();
	afx_msg void OnMenuAddProgram();
	afx_msg void OnMenuEditProgram();
	afx_msg void OnMenuDelProgram();
	afx_msg void OnEditCurrent();
	afx_msg void OnUpdateMenuAddProgram(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuEditProgram(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuDelProgram(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuSelectProgram(CCmdUI *pCmdUI);
	afx_msg void OnEditSecond();
	afx_msg void OnMenuEditPassword();
	afx_msg void OnRegSoft();
	afx_msg void OnUpdateRegSoft(CCmdUI *pCmdUI);
//��������ӿ�
public:
	void ForNextNumberInput();
	void SetThisWindowForground();
	void WriteReport(DetectionResult& dr);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	CEdit m_BarCodeEdit;
	CString m_strBarCode;
	time_t m_startTimer;
	time_t m_stopTimer;
//new report function
	bool HasSecondStep();
//add in 2015/10/13 for save first step report
//�˹����Ի���
	DetectionResult itsFirstDetectResult;
	DetectionResult itsSecondDetectResult;
	int itsCurrentCheckStep;
	Clock_MS itsManualTimer;
	bool itsInManualConfirming;

	CManualPassDialog m_ManualPassDlg;
	afx_msg LRESULT OnManualPassProc(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // MFC_DetectionView.cpp �еĵ��԰汾
inline CMFC_DetectionDoc* CMFC_DetectionView::GetDocument() const
   { return reinterpret_cast<CMFC_DetectionDoc*>(m_pDocument); }
#endif

