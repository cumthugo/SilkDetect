#pragma once


// CNoLockUnitDialog 对话框

#include "../DetectionLib/NoLockDetectionUnit.hpp"

class CNoLockUnitDialog : public CDialog
{
	DECLARE_DYNAMIC(CNoLockUnitDialog)

public:
	CNoLockUnitDialog(const shared_ptr<NoLockDetectionUnit>& nld,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNoLockUnitDialog();

// 对话框数据
	enum { IDD = IDD_NO_LOCK_UNIT_DIALOG };
public:
	shared_ptr<NoLockDetectionUnit> m_NoLockDetectionUnit;
	CString m_UnitName;
	int m_SubRect_x;
	int m_SubRect_y;
	int m_SubRect_width;
	int m_SubRect_height;
	int m_PedestalColorMin_R;
	int m_PedestalColorMin_G;
	int m_PedestalColorMin_B;
	int m_PedestalColorMax_R;
	int m_PedestalColorMax_G;
	int m_PedestalColorMax_B;
	double m_PedestalScaleMin;
	double m_PedestalScaleMax;
	int m_PedestalSizeMin;
	int m_PedestalSizeMax;
	int m_SilkColorMin_R;
	int m_SilkColorMin_G;
	int m_SilkColorMin_B;
	int m_SilkColorMax_R;
	int m_SilkColorMax_G;
	int m_SilkColorMax_B;
	int m_SilkSearchMin;
	int m_SilkSearchMax;
	int m_SilkPixelCount;

	int m_SilkPositionSelectRadio;
	BOOL m_IsPedestalColorHSV;
	BOOL m_IsSilkColorHSV;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
public:

	int m_PedestalXLeastPointNumber;
	int m_PedestalYLeastPointNumber;
	BOOL m_bIsPedestalConstHeight;
	int m_PedestalExpectHeight;
	int m_PedestalConstHeightDirection;
	afx_msg void OnBnClickedEnableConstHeight();
	void EnableConstHeightControl(BOOL isEnable = TRUE);
	int m_SilkXOffset;
	int m_SilkSearchWidth;
	int m_SilkMaxGapAround;
};
