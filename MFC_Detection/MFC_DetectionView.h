
// MFC_DetectionView.h : CMFC_DetectionView 类的接口
//


#pragma once

#include "../DetectionLib/DetectionLine.hpp"
#include "afxwin.h"


class CMFC_DetectionView : public CFormView
{
protected: // 仅从序列化创建
	CMFC_DetectionView();
	DECLARE_DYNCREATE(CMFC_DetectionView)

public:
	enum{ IDD = IDD_MFC_DETECTION_FORM };

// 属性
public:
	CMFC_DetectionDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

//自己的接口
	bool Detect( IplImage_Ptr img,shared_ptr<DetectionProgram> dp );
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

// 实现
public:
	virtual ~CMFC_DetectionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGetPic();

	afx_msg LRESULT OnCommProc(WPARAM wParam, LPARAM lParam);
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
};

#ifndef _DEBUG  // MFC_DetectionView.cpp 中的调试版本
inline CMFC_DetectionDoc* CMFC_DetectionView::GetDocument() const
   { return reinterpret_cast<CMFC_DetectionDoc*>(m_pDocument); }
#endif

