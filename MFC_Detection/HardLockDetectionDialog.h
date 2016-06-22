#pragma once


// CHardLockDetectionDialog 对话框
#include "../DetectionLib/HardLockDetectionUnit.hpp"

class CHardLockDetectionDialog : public CDialog
{
	DECLARE_DYNAMIC(CHardLockDetectionDialog)

public:
	CHardLockDetectionDialog(const shared_ptr<HardLockDetectionUnit>& hld,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHardLockDetectionDialog();

// 对话框数据
	enum { IDD = IDD_HARD_LOCK_UNIT_DIALOG };
public:
	shared_ptr<HardLockDetectionUnit> m_HardLockDetectionUnit;

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
	int m_LockColorMin_R;
	int m_LockColorMin_G;
	int m_LockColorMin_B;
	int m_LockColorMax_R;
	int m_LockColorMax_G;
	int m_LockColorMax_B;
	int m_LockSearchMin;
	int m_LockSearchMax;
	int m_LockPixelCount;
	int m_LockXOffset;
	int m_LockSearchWidth;

	int m_SilkPositionSelectRadio;
	BOOL m_IsPedestalColorHSV;
	BOOL m_IsLockColorHSV;
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
	BOOL m_ImagePreProcess;

	int m_CableColorMin_R;
	int m_CableColorMin_G;
	int m_CableColorMin_B;
	int m_CableColorMax_R;
	int m_CableColorMax_G;
	int m_CableColorMax_B;
	int m_CableSearchMin;
	int m_CableSearchMax;
	BOOL m_IsCableColorHSV;
	int m_CablePixelCount;
	int m_CableXOffset;
	int m_CableSearchWidth;
};
