
// MFC_DetectionDoc.cpp : CMFC_DetectionDoc ���ʵ��
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


// CMFC_DetectionDoc ����/����

CMFC_DetectionDoc::CMFC_DetectionDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CMFC_DetectionDoc::~CMFC_DetectionDoc()
{
}

BOOL CMFC_DetectionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMFC_DetectionDoc ���л�

void CMFC_DetectionDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CMFC_DetectionDoc ���

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


// CMFC_DetectionDoc ����

//void CMFC_DetectionDoc::SetTitle(LPCTSTR lpszTitle)
//{
//	// TODO: �ڴ����ר�ô����/����û���
//
//	lpszTitle = "���߼����Գ���";
//	CDocument::SetTitle(lpszTitle);
//}
