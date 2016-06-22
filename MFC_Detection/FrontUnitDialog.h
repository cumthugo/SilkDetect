#pragma once


#include "../DetectionLib/FrontDetectionUnit.hpp"

// CFrontUnitDialog 对话框

class CFrontUnitDialog : public CDialog
{
	DECLARE_DYNAMIC(CFrontUnitDialog)

public:
	CFrontUnitDialog(const shared_ptr<FrontDetectionUnit>& fdu, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFrontUnitDialog();

// 对话框数据
	enum { IDD = IDD_FRONT2_UNIT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	shared_ptr<FrontDetectionUnit> m_FrontDetectionUnit;

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

	virtual BOOL OnInitDialog();
protected:
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
