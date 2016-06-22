#pragma once


// CBackUnitDialog 对话框

#include "../DetectionLib/BackDetectionUnit.hpp"


class CBackUnitDialog : public CDialog
{
	DECLARE_DYNAMIC(CBackUnitDialog)

public:
	CBackUnitDialog(const shared_ptr<BackDetectionUnit>& bdu, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBackUnitDialog();

// 对话框数据
	enum { IDD = IDD_BACK_UNIT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void EnableConstHeightControl(BOOL isEnable = TRUE);
	shared_ptr<BackDetectionUnit> m_BackDetectionUnit;

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
	int m_BlueBoxColorMin_R;
	int m_BlueBoxColorMin_G;
	int m_BlueBoxColorMin_B;
	int m_BlueBoxColorMax_R;
	int m_BlueBoxColorMax_G;
	int m_BlueBoxColorMax_B;
	int m_BlueBoxSearchMin;
	int m_BlueBoxSearchMax;
	int m_BlueBoxPixelCount;
	int m_LockColorMin_R;
	int m_LockColorMin_G;
	int m_LockColorMin_B;
	int m_LockColorMax_R;
	int m_LockColorMax_G;
	int m_LockColorMax_B;
	int m_LockSearchMin;
	int m_LockSearchMax;
	int m_LockPixelCount;
protected:
	virtual void OnOK();
public:
	int m_BlueBoxPositionRadio;
	BOOL m_IsPedestalColorHSV;
	BOOL m_IsBlueBoxHSV;
	BOOL m_IsLockColorHSV;
	int m_PedestalXLeastPointNumber;
	int m_PedestalYLeastPointNumber;
	BOOL m_bIsPedestalConstHeight;
	afx_msg void OnBnClickedEnableConstHeight();
	int m_PedestalExpectHeight;
	int m_PedestalConstHeightDirection;
	int m_BlueBoxXOffset;
	int m_BlueBoxSearchWidth;
	int m_BlueBoxMaxGapAround;
};
