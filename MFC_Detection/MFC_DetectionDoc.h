
// MFC_DetectionDoc.h : CMFC_DetectionDoc ��Ľӿ�
//


#pragma once


class CMFC_DetectionDoc : public CDocument
{
protected: // �������л�����
	CMFC_DetectionDoc();
	DECLARE_DYNCREATE(CMFC_DetectionDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CMFC_DetectionDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	virtual void SetTitle(LPCTSTR lpszTitle);
};


