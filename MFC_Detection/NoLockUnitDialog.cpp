// NoLockUnitDialog.cpp
//

#include "stdafx.h"
#include "MFC_Detection.h"
#include "NoLockUnitDialog.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CNoLockUnitDialog, CDialog)

CNoLockUnitDialog::CNoLockUnitDialog(const shared_ptr<NoLockDetectionUnit>& nld,CWnd* pParent /*=NULL*/)
	: CDialog(CNoLockUnitDialog::IDD, pParent),m_NoLockDetectionUnit(nld)
	, m_UnitName(_T(""))
	, m_SubRect_x(0)
	, m_SubRect_y(0)
	, m_SubRect_width(0)
	, m_SubRect_height(0)
	, m_PedestalColorMin_R(0)
	, m_PedestalColorMin_G(0)
	, m_PedestalColorMin_B(0)
	, m_PedestalColorMax_R(0)
	, m_PedestalColorMax_G(0)
	, m_PedestalColorMax_B(0)
	, m_PedestalScaleMin(0)
	, m_PedestalScaleMax(0)
	, m_PedestalSizeMin(0)
	, m_PedestalSizeMax(0)
	, m_SilkColorMin_R(0)
	, m_SilkColorMin_G(0)
	, m_SilkColorMin_B(0)
	, m_SilkColorMax_R(0)
	, m_SilkColorMax_G(0)
	, m_SilkColorMax_B(0)
	, m_SilkSearchMin(0)
	, m_SilkSearchMax(0)
	, m_SilkPixelCount(0)
	, m_SilkPositionSelectRadio(0)
	, m_IsPedestalColorHSV(FALSE)
	, m_IsSilkColorHSV(FALSE)
	, m_PedestalXLeastPointNumber(0)
	, m_PedestalYLeastPointNumber(0)
	, m_bIsPedestalConstHeight(FALSE)
	, m_PedestalExpectHeight(0)
	, m_PedestalConstHeightDirection(0)
	, m_SilkXOffset(0)
	, m_SilkSearchWidth(0)
	, m_SilkMaxGapAround(-1)
	, m_ImagePreProcess(FALSE)
{

}

CNoLockUnitDialog::~CNoLockUnitDialog()
{
}

void CNoLockUnitDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT40, m_UnitName);
	DDX_Text(pDX, IDC_EDIT1, m_SubRect_x);
	DDX_Text(pDX, IDC_EDIT2, m_SubRect_y);
	DDX_Text(pDX, IDC_EDIT3, m_SubRect_width);
	DDX_Text(pDX, IDC_EDIT4, m_SubRect_height);
	DDX_Text(pDX, IDC_EDIT5, m_PedestalColorMin_R);
	DDX_Text(pDX, IDC_EDIT6, m_PedestalColorMin_G);
	DDX_Text(pDX, IDC_EDIT7, m_PedestalColorMin_B);
	DDX_Text(pDX, IDC_EDIT8, m_PedestalColorMax_R);
	DDX_Text(pDX, IDC_EDIT9, m_PedestalColorMax_G);
	DDX_Text(pDX, IDC_EDIT10, m_PedestalColorMax_B);
	DDX_Text(pDX, IDC_EDIT11, m_PedestalScaleMin);
	DDX_Text(pDX, IDC_EDIT12, m_PedestalScaleMax);
	DDX_Text(pDX, IDC_EDIT13, m_PedestalSizeMin);
	DDX_Text(pDX, IDC_EDIT14, m_PedestalSizeMax);
	DDX_Text(pDX, IDC_EDIT15, m_SilkColorMin_R);
	DDX_Text(pDX, IDC_EDIT16, m_SilkColorMin_G);
	DDX_Text(pDX, IDC_EDIT17, m_SilkColorMin_B);
	DDX_Text(pDX, IDC_EDIT18, m_SilkColorMax_R);
	DDX_Text(pDX, IDC_EDIT19, m_SilkColorMax_G);
	DDX_Text(pDX, IDC_EDIT20, m_SilkColorMax_B);
	DDX_Text(pDX, IDC_EDIT21, m_SilkSearchMin);
	DDX_Text(pDX, IDC_EDIT22, m_SilkSearchMax);
	DDX_Text(pDX, IDC_EDIT23, m_SilkPixelCount);
	DDX_Radio(pDX, IDC_RADIO1, m_SilkPositionSelectRadio);
	DDX_Check(pDX, IDC_CHECK1, m_IsPedestalColorHSV);
	DDX_Check(pDX, IDC_CHECK3, m_IsSilkColorHSV);
	DDX_Text(pDX, IDC_EDIT34, m_PedestalXLeastPointNumber);
	DDX_Text(pDX, IDC_EDIT37, m_PedestalYLeastPointNumber);
	DDX_Check(pDX, IDC_CHECK5, m_bIsPedestalConstHeight);
	DDX_Text(pDX, IDC_EDIT38, m_PedestalExpectHeight);
	DDX_Radio(pDX, IDC_RADIO4, m_PedestalConstHeightDirection);
	DDX_Text(pDX, IDC_EDIT39, m_SilkXOffset);
	DDX_Text(pDX, IDC_EDIT41, m_SilkSearchWidth);
	DDX_Text(pDX, IDC_EDIT42, m_SilkMaxGapAround);
	DDX_Check(pDX, IDC_CHECK6, m_ImagePreProcess);
}


BEGIN_MESSAGE_MAP(CNoLockUnitDialog, CDialog)
	ON_BN_CLICKED(IDC_CHECK5, &CNoLockUnitDialog::OnBnClickedEnableConstHeight)
END_MESSAGE_MAP()




BOOL CNoLockUnitDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_UnitName = m_NoLockDetectionUnit->Name.c_str();
	m_SubRect_x = m_NoLockDetectionUnit->SubImageRect.x;
	m_SubRect_y = m_NoLockDetectionUnit->SubImageRect.y;
	m_SubRect_width = m_NoLockDetectionUnit->SubImageRect.width;
	m_SubRect_height = m_NoLockDetectionUnit->SubImageRect.height;

	if(IsHSV(m_NoLockDetectionUnit->PedestalFinder->ColorRange.Min()))
	{
		m_IsPedestalColorHSV = TRUE;
		m_PedestalColorMin_R = cvRound(m_NoLockDetectionUnit->PedestalFinder->ColorRange.Min().val[0]*2);
		m_PedestalColorMin_G = cvRound(m_NoLockDetectionUnit->PedestalFinder->ColorRange.Min().val[1]/2.55);
		m_PedestalColorMin_B = cvRound(m_NoLockDetectionUnit->PedestalFinder->ColorRange.Min().val[2]/2.55);

		m_PedestalColorMax_R = cvRound(m_NoLockDetectionUnit->PedestalFinder->ColorRange.Max().val[0]*2);
		m_PedestalColorMax_G = cvRound(m_NoLockDetectionUnit->PedestalFinder->ColorRange.Max().val[1]/2.55);
		m_PedestalColorMax_B = cvRound(m_NoLockDetectionUnit->PedestalFinder->ColorRange.Max().val[2]/2.55);
	}
	else
	{
		m_IsPedestalColorHSV = FALSE;
		m_PedestalColorMin_R = (int)m_NoLockDetectionUnit->PedestalFinder->ColorRange.Min().val[2];
		m_PedestalColorMin_G = (int)m_NoLockDetectionUnit->PedestalFinder->ColorRange.Min().val[1];
		m_PedestalColorMin_B = (int)m_NoLockDetectionUnit->PedestalFinder->ColorRange.Min().val[0];

		m_PedestalColorMax_R = (int)m_NoLockDetectionUnit->PedestalFinder->ColorRange.Max().val[2];
		m_PedestalColorMax_G = (int)m_NoLockDetectionUnit->PedestalFinder->ColorRange.Max().val[1];
		m_PedestalColorMax_B = (int)m_NoLockDetectionUnit->PedestalFinder->ColorRange.Max().val[0];
	}


	m_PedestalScaleMin = m_NoLockDetectionUnit->PedestalFinder->ScaleRange.Min();
	m_PedestalScaleMax = m_NoLockDetectionUnit->PedestalFinder->ScaleRange.Max();

	m_PedestalSizeMin = m_NoLockDetectionUnit->PedestalFinder->SizeRange.Min();
	m_PedestalSizeMax = m_NoLockDetectionUnit->PedestalFinder->SizeRange.Max();

	m_PedestalXLeastPointNumber = m_NoLockDetectionUnit->PedestalFinder->XLeastPointNumber;
	m_PedestalYLeastPointNumber = m_NoLockDetectionUnit->PedestalFinder->YLeastPointNumber;
	shared_ptr<ConstHeightPedestalFinder> ConstHeightFinder = dynamic_pointer_cast<ConstHeightPedestalFinder>(m_NoLockDetectionUnit->PedestalFinder);
	if(ConstHeightFinder)
	{
		EnableConstHeightControl();
		m_bIsPedestalConstHeight = TRUE;
		m_PedestalExpectHeight = ConstHeightFinder->ExpectHeight;
		m_PedestalConstHeightDirection = ConstHeightFinder->ReferenceDirection == DIRECTION_FROM_TOP ? 0 : 1;
	}
	else
		EnableConstHeightControl(FALSE);

	if(IsHSV(m_NoLockDetectionUnit->Silk.ColorRange.Min()))
	{
		m_IsSilkColorHSV = TRUE;
		m_SilkColorMin_R = cvRound(m_NoLockDetectionUnit->Silk.ColorRange.Min().val[0]*2);
		m_SilkColorMin_G = cvRound(m_NoLockDetectionUnit->Silk.ColorRange.Min().val[1]/2.55);
		m_SilkColorMin_B = cvRound(m_NoLockDetectionUnit->Silk.ColorRange.Min().val[2]/2.55);

		m_SilkColorMax_R = cvRound(m_NoLockDetectionUnit->Silk.ColorRange.Max().val[0]*2);
		m_SilkColorMax_G = cvRound(m_NoLockDetectionUnit->Silk.ColorRange.Max().val[1]/2.55);
		m_SilkColorMax_B = cvRound(m_NoLockDetectionUnit->Silk.ColorRange.Max().val[2]/2.55);
	}

	else
	{
		m_IsSilkColorHSV = FALSE;
		m_SilkColorMin_R = (int)m_NoLockDetectionUnit->Silk.ColorRange.Min().val[2];
		m_SilkColorMin_G = (int)m_NoLockDetectionUnit->Silk.ColorRange.Min().val[1];
		m_SilkColorMin_B = (int)m_NoLockDetectionUnit->Silk.ColorRange.Min().val[0];

		m_SilkColorMax_R = (int)m_NoLockDetectionUnit->Silk.ColorRange.Max().val[2];
		m_SilkColorMax_G = (int)m_NoLockDetectionUnit->Silk.ColorRange.Max().val[1];
		m_SilkColorMax_B = (int)m_NoLockDetectionUnit->Silk.ColorRange.Max().val[0];
	}

	m_SilkSearchMin = m_NoLockDetectionUnit->Silk.SearchRange.Min();
	m_SilkSearchMax = m_NoLockDetectionUnit->Silk.SearchRange.Max();

	m_SilkPixelCount = m_NoLockDetectionUnit->Silk.PixelCount;

	//new add
	m_SilkXOffset = m_NoLockDetectionUnit->Silk.XOffset;
	m_SilkSearchWidth = m_NoLockDetectionUnit->Silk.SearchWidth;
	m_SilkMaxGapAround = m_NoLockDetectionUnit->Silk.MaxGapAround;

	m_SilkPositionSelectRadio = m_NoLockDetectionUnit->PedestalPosition == PEDESTAL_ON_BOTTOM ? 0 : 1;
	if(m_NoLockDetectionUnit->NeedRotate90)
		m_SilkPositionSelectRadio += 2;
	m_ImagePreProcess = m_NoLockDetectionUnit->PreProcess;
	UpdateData(FALSE);
	return TRUE;  
}


void CNoLockUnitDialog::OnOK()
{
	UpdateData(TRUE);

	if(m_UnitName == "")
	{
		MessageBox("名称不能为空，请输入检测名称！","输入错误",MB_OK | MB_ICONERROR);
		return;
	}

	m_NoLockDetectionUnit->Name = m_UnitName.GetString();

	m_NoLockDetectionUnit->NeedRotate90 = m_SilkPositionSelectRadio >= 2 ? 1 : 0;
	m_NoLockDetectionUnit->PedestalPosition = (m_SilkPositionSelectRadio == 0 || m_SilkPositionSelectRadio == 2) ? PEDESTAL_ON_BOTTOM : PEDESTAL_ON_TOP;

	//这里要新建
	if(m_bIsPedestalConstHeight)
	{
		shared_ptr<ConstHeightPedestalFinder> PedestalFinder = shared_ptr<ConstHeightPedestalFinder>(new ConstHeightPedestalFinder);
		PedestalFinder->ExpectHeight = m_PedestalExpectHeight;
		PedestalFinder->ReferenceDirection = m_PedestalConstHeightDirection == 0 ? DIRECTION_FROM_TOP : DIRECTION_FROM_BOTTOM;
		m_NoLockDetectionUnit->PedestalFinder = PedestalFinder;
	}
	else
	{
		m_NoLockDetectionUnit->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);
	}

	m_NoLockDetectionUnit->PedestalFinder->XLeastPointNumber = m_PedestalXLeastPointNumber;
	m_NoLockDetectionUnit->PedestalFinder->YLeastPointNumber = m_PedestalYLeastPointNumber;

	m_NoLockDetectionUnit->SubImageRect = cvRect(m_SubRect_x,m_SubRect_y,m_SubRect_width,m_SubRect_height);
	if(m_IsPedestalColorHSV)
		m_NoLockDetectionUnit->PedestalFinder->ColorRange = Range<CvScalar>(CV_HSV(m_PedestalColorMin_R,m_PedestalColorMin_G,m_PedestalColorMin_B),CV_HSV(m_PedestalColorMax_R,m_PedestalColorMax_G,m_PedestalColorMax_B));
	else
		m_NoLockDetectionUnit->PedestalFinder->ColorRange = Range<CvScalar>(CV_RGB(m_PedestalColorMin_R,m_PedestalColorMin_G,m_PedestalColorMin_B),CV_RGB(m_PedestalColorMax_R,m_PedestalColorMax_G,m_PedestalColorMax_B));
	m_NoLockDetectionUnit->PedestalFinder->ScaleRange = Range<double>(m_PedestalScaleMin,m_PedestalScaleMax);
	m_NoLockDetectionUnit->PedestalFinder->SizeRange = Range<int>(m_PedestalSizeMin,m_PedestalSizeMax);

	if(m_IsSilkColorHSV)
		m_NoLockDetectionUnit->Silk.ColorRange = Range<CvScalar>(CV_HSV(m_SilkColorMin_R,m_SilkColorMin_G,m_SilkColorMin_B),CV_HSV(m_SilkColorMax_R,m_SilkColorMax_G,m_SilkColorMax_B));
	else
		m_NoLockDetectionUnit->Silk.ColorRange = Range<CvScalar>(CV_RGB(m_SilkColorMin_R,m_SilkColorMin_G,m_SilkColorMin_B),CV_RGB(m_SilkColorMax_R,m_SilkColorMax_G,m_SilkColorMax_B));
	m_NoLockDetectionUnit->Silk.SearchRange = Range<int>(m_SilkSearchMin,m_SilkSearchMax);
	m_NoLockDetectionUnit->Silk.PixelCount = m_SilkPixelCount;

	m_NoLockDetectionUnit->PreProcess = m_ImagePreProcess;

	//new add
	m_NoLockDetectionUnit->Silk.XOffset = m_SilkXOffset;
	m_NoLockDetectionUnit->Silk.SearchWidth = m_SilkSearchWidth;
	m_NoLockDetectionUnit->Silk.MaxGapAround = m_SilkMaxGapAround;

	CDialog::OnOK();
}

void CNoLockUnitDialog::OnBnClickedEnableConstHeight()
{
	UpdateData(TRUE);
	EnableConstHeightControl(m_bIsPedestalConstHeight);
}

void CNoLockUnitDialog::EnableConstHeightControl( BOOL isEnable /*= TRUE*/ )
{
	GetDlgItem(IDC_EDIT38)->EnableWindow(isEnable);
	GetDlgItem(IDC_RADIO4)->EnableWindow(isEnable);
	GetDlgItem(IDC_RADIO5)->EnableWindow(isEnable);
}
