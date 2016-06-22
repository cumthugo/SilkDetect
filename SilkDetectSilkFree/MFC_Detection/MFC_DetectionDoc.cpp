
// MFC_DetectionDoc.cpp : CMFC_DetectionDoc 类的实现
//

#include "stdafx.h"
#include "MFC_Detection.h"

#include "MFC_DetectionDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_DetectionDoc

IMPLEMENT_DYNCREATE(CMFC_DetectionDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFC_DetectionDoc, CDocument)
END_MESSAGE_MAP()


// CMFC_DetectionDoc 构造/析构

CMFC_DetectionDoc::CMFC_DetectionDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMFC_DetectionDoc::~CMFC_DetectionDoc()
{
}

BOOL CMFC_DetectionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMFC_DetectionDoc 序列化

void CMFC_DetectionDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CMFC_DetectionDoc 诊断

#ifdef _DEBUG
void CMFC_DetectionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFC_DetectionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFC_DetectionDoc 命令

//void CMFC_DetectionDoc::SetTitle(LPCTSTR lpszTitle)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//
//	lpszTitle = "排线检测调试程序";
//	CDocument::SetTitle(lpszTitle);
//}
