// BackUnitDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_Detection.h"
#include "BackUnitDialog.h"





// CBackUnitDialog 对话框

IMPLEMENT_DYNAMIC(CBackUnitDialog, CDialog)

CBackUnitDialog::CBackUnitDialog(const shared_ptr<BackDetectionUnit>& bdu,CWnd* pParent /*=NULL*/)
	: CDialog(CBackUnitDialog::IDD, pParent) , m_BackDetectionUnit(bdu)
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
	, m_BlueBoxColorMin_R(0)
	, m_BlueBoxColorMin_G(0)
	, m_BlueBoxColorMin_B(0)
	, m_BlueBoxColorMax_R(0)
	, m_BlueBoxColorMax_G(0)
	, m_BlueBoxColorMax_B(0)
	, m_BlueBoxSearchMin(0)
	, m_BlueBoxSearchMax(0)
	, m_BlueBoxPixelCount(0)
	, m_LockColorMin_R(0)
	, m_LockColorMin_G(0)
	, m_LockColorMin_B(0)
	, m_LockColorMax_R(0)
	, m_LockColorMax_G(0)
	, m_LockColorMax_B(0)
	, m_LockSearchMin(0)
	, m_LockSearchMax(0)
	, m_LockPixelCount(0)
	, m_BlueBoxPositionRadio(0)
	, m_IsPedestalColorHSV(FALSE)
	, m_IsBlueBoxHSV(FALSE)
	, m_IsLockColorHSV(FALSE)
	, m_PedestalXLeastPointNumber(0)
	, m_PedestalYLeastPointNumber(0)
	, m_bIsPedestalConstHeight(FALSE)
	, m_PedestalExpectHeight(0)
	, m_PedestalConstHeightDirection(0)
	, m_BlueBoxXOffset(0)
	, m_BlueBoxSearchWidth(0)
	, m_BlueBoxMaxGapAround(-1)
	, m_ImagePreProcess(FALSE)
	, m_CableColorMin_R(0)
	, m_CableColorMin_G(0)
	, m_CableColorMin_B(0)
	, m_CableColorMax_R(0)
	, m_CableColorMax_G(0)
	, m_CableColorMax_B(0)
	, m_CableSearchMin(0)
	, m_CableSearchMax(0)
	, m_IsCableColorHSV(FALSE)
	, m_CablePixelCount(0)
	, m_CableXOffset(0)
	, m_CableSearchWidth(0)
{

}

CBackUnitDialog::~CBackUnitDialog()
{
}

void CBackUnitDialog::DoDataExchange(CDataExchange* pDX)
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
	DDX_Text(pDX, IDC_EDIT15, m_BlueBoxColorMin_R);
	DDX_Text(pDX, IDC_EDIT16, m_BlueBoxColorMin_G);
	DDX_Text(pDX, IDC_EDIT17, m_BlueBoxColorMin_B);
	DDX_Text(pDX, IDC_EDIT18, m_BlueBoxColorMax_R);
	DDX_Text(pDX, IDC_EDIT19, m_BlueBoxColorMax_G);
	DDX_Text(pDX, IDC_EDIT20, m_BlueBoxColorMax_B);
	DDX_Text(pDX, IDC_EDIT21, m_BlueBoxSearchMin);
	DDX_Text(pDX, IDC_EDIT22, m_BlueBoxSearchMax);
	DDX_Text(pDX, IDC_EDIT23, m_BlueBoxPixelCount);
	DDX_Text(pDX, IDC_EDIT25, m_LockColorMin_R);
	DDX_Text(pDX, IDC_EDIT26, m_LockColorMin_G);
	DDX_Text(pDX, IDC_EDIT27, m_LockColorMin_B);
	DDX_Text(pDX, IDC_EDIT28, m_LockColorMax_R);
	DDX_Text(pDX, IDC_EDIT29, m_LockColorMax_G);
	DDX_Text(pDX, IDC_EDIT30, m_LockColorMax_B);
	DDX_Text(pDX, IDC_EDIT31, m_LockSearchMin);
	DDX_Text(pDX, IDC_EDIT32, m_LockSearchMax);
	DDX_Text(pDX, IDC_EDIT33, m_LockPixelCount);
	DDX_Radio(pDX, IDC_RADIO1, m_BlueBoxPositionRadio);
	DDX_Check(pDX, IDC_CHECK1, m_IsPedestalColorHSV);
	DDX_Check(pDX, IDC_CHECK2, m_IsBlueBoxHSV);
	DDX_Check(pDX, IDC_CHECK3, m_IsLockColorHSV);
	DDX_Text(pDX, IDC_EDIT34, m_PedestalXLeastPointNumber);
	DDX_Text(pDX, IDC_EDIT37, m_PedestalYLeastPointNumber);
	DDX_Check(pDX, IDC_CHECK4, m_bIsPedestalConstHeight);
	DDX_Text(pDX, IDC_EDIT24, m_PedestalExpectHeight);
	DDX_Radio(pDX, IDC_RADIO3, m_PedestalConstHeightDirection);
	DDX_Text(pDX, IDC_EDIT39, m_BlueBoxXOffset);
	DDX_Text(pDX, IDC_EDIT41, m_BlueBoxSearchWidth);
	DDX_Text(pDX, IDC_EDIT42, m_BlueBoxMaxGapAround);
	DDX_Check(pDX, IDC_CHECK6, m_ImagePreProcess);

	DDX_Text(pDX, IDC_EDIT43, m_CableColorMin_R);
	DDX_Text(pDX, IDC_EDIT51, m_CableColorMin_G);
	DDX_Text(pDX, IDC_EDIT44, m_CableColorMin_B);
	DDX_Text(pDX, IDC_EDIT45, m_CableColorMax_R);
	DDX_Text(pDX, IDC_EDIT46, m_CableColorMax_G);
	DDX_Text(pDX, IDC_EDIT47, m_CableColorMax_B);
	DDX_Text(pDX, IDC_EDIT48, m_CableSearchMin);
	DDX_Text(pDX, IDC_EDIT49, m_CableSearchMax);
	DDX_Check(pDX, IDC_CHECK7, m_IsCableColorHSV);
	DDX_Text(pDX, IDC_EDIT50, m_CablePixelCount);
	DDX_Text(pDX, IDC_EDIT52, m_CableXOffset);
	DDX_Text(pDX, IDC_EDIT53, m_CableSearchWidth);
}


BEGIN_MESSAGE_MAP(CBackUnitDialog, CDialog)
	ON_BN_CLICKED(IDC_CHECK4, &CBackUnitDialog::OnBnClickedEnableConstHeight)
END_MESSAGE_MAP()


// CBackUnitDialog 消息处理程序

BOOL CBackUnitDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_UnitName = m_BackDetectionUnit->Name.c_str();
	m_SubRect_x = m_BackDetectionUnit->SubImageRect.x;
	m_SubRect_y = m_BackDetectionUnit->SubImageRect.y;
	m_SubRect_width = m_BackDetectionUnit->SubImageRect.width;
	m_SubRect_height = m_BackDetectionUnit->SubImageRect.height;


	if(IsHSV(m_BackDetectionUnit->PedestalFinder->ColorRange.Min()))
	{
		m_IsPedestalColorHSV = TRUE;
		m_PedestalColorMin_R = cvRound(m_BackDetectionUnit->PedestalFinder->ColorRange.Min().val[0]*2);
		m_PedestalColorMin_G = cvRound(m_BackDetectionUnit->PedestalFinder->ColorRange.Min().val[1]/2.55);
		m_PedestalColorMin_B = cvRound(m_BackDetectionUnit->PedestalFinder->ColorRange.Min().val[2]/2.55);

		m_PedestalColorMax_R = cvRound(m_BackDetectionUnit->PedestalFinder->ColorRange.Max().val[0]*2);
		m_PedestalColorMax_G = cvRound(m_BackDetectionUnit->PedestalFinder->ColorRange.Max().val[1]/2.55);
		m_PedestalColorMax_B = cvRound(m_BackDetectionUnit->PedestalFinder->ColorRange.Max().val[2]/2.55);
	}
	else
	{
		m_IsPedestalColorHSV = FALSE;
		m_PedestalColorMin_R = (int)m_BackDetectionUnit->PedestalFinder->ColorRange.Min().val[2];
		m_PedestalColorMin_G = (int)m_BackDetectionUnit->PedestalFinder->ColorRange.Min().val[1];
		m_PedestalColorMin_B = (int)m_BackDetectionUnit->PedestalFinder->ColorRange.Min().val[0];

		m_PedestalColorMax_R = (int)m_BackDetectionUnit->PedestalFinder->ColorRange.Max().val[2];
		m_PedestalColorMax_G = (int)m_BackDetectionUnit->PedestalFinder->ColorRange.Max().val[1];
		m_PedestalColorMax_B = (int)m_BackDetectionUnit->PedestalFinder->ColorRange.Max().val[0];
	}
	m_PedestalScaleMin = m_BackDetectionUnit->PedestalFinder->ScaleRange.Min();
	m_PedestalScaleMax = m_BackDetectionUnit->PedestalFinder->ScaleRange.Max();

	m_PedestalSizeMin = m_BackDetectionUnit->PedestalFinder->SizeRange.Min();
	m_PedestalSizeMax = m_BackDetectionUnit->PedestalFinder->SizeRange.Max();


	m_PedestalXLeastPointNumber = m_BackDetectionUnit->PedestalFinder->XLeastPointNumber;
	m_PedestalYLeastPointNumber = m_BackDetectionUnit->PedestalFinder->YLeastPointNumber;
	shared_ptr<ConstHeightPedestalFinder> ConstHeightFinder = dynamic_pointer_cast<ConstHeightPedestalFinder>(m_BackDetectionUnit->PedestalFinder);
	if(ConstHeightFinder)
	{
		EnableConstHeightControl();
		m_bIsPedestalConstHeight = TRUE;
		m_PedestalExpectHeight = ConstHeightFinder->ExpectHeight;
		m_PedestalConstHeightDirection = ConstHeightFinder->ReferenceDirection == DIRECTION_FROM_TOP ? 0 : 1;
	}
	else
		EnableConstHeightControl(FALSE);

	//added in 2014/7/29
	if(IsHSV(m_BackDetectionUnit->CableDetector.ColorRange.Min()))
	{
		m_IsCableColorHSV = TRUE;
		m_CableColorMin_R = cvRound(m_BackDetectionUnit->CableDetector.ColorRange.Min().val[0]*2);
		m_CableColorMin_G = cvRound(m_BackDetectionUnit->CableDetector.ColorRange.Min().val[1]/2.55);
		m_CableColorMin_B = cvRound(m_BackDetectionUnit->CableDetector.ColorRange.Min().val[2]/2.55);

		m_CableColorMax_R = cvRound(m_BackDetectionUnit->CableDetector.ColorRange.Max().val[0]*2);
		m_CableColorMax_G = cvRound(m_BackDetectionUnit->CableDetector.ColorRange.Max().val[1]/2.55);
		m_CableColorMax_B = cvRound(m_BackDetectionUnit->CableDetector.ColorRange.Max().val[2]/2.55);
	}
	else
	{
		m_IsCableColorHSV = FALSE;
		m_CableColorMin_R = (int)m_BackDetectionUnit->CableDetector.ColorRange.Min().val[2];
		m_CableColorMin_G = (int)m_BackDetectionUnit->CableDetector.ColorRange.Min().val[1];
		m_CableColorMin_B = (int)m_BackDetectionUnit->CableDetector.ColorRange.Min().val[0];

		m_CableColorMax_R = (int)m_BackDetectionUnit->CableDetector.ColorRange.Max().val[2];
		m_CableColorMax_G = (int)m_BackDetectionUnit->CableDetector.ColorRange.Max().val[1];
		m_CableColorMax_B = (int)m_BackDetectionUnit->CableDetector.ColorRange.Max().val[0];
	}	
	m_CableSearchMin = m_BackDetectionUnit->CableDetector.SearchRange.Min();
	m_CableSearchMax = m_BackDetectionUnit->CableDetector.SearchRange.Max();
	m_CablePixelCount = m_BackDetectionUnit->CableDetector.PixelCount;
	m_CableXOffset = m_BackDetectionUnit->CableDetector.XOffset;
	m_CableSearchWidth = m_BackDetectionUnit->CableDetector.SearchWidth;
	//end add 2014/7/29

	if(IsHSV(m_BackDetectionUnit->BlueBox.ColorRange.Min()))
	{
		m_IsBlueBoxHSV = TRUE;
		m_BlueBoxColorMin_R = cvRound(m_BackDetectionUnit->BlueBox.ColorRange.Min().val[0]*2);
		m_BlueBoxColorMin_G = cvRound(m_BackDetectionUnit->BlueBox.ColorRange.Min().val[1]/2.55);
		m_BlueBoxColorMin_B = cvRound(m_BackDetectionUnit->BlueBox.ColorRange.Min().val[2]/2.55);

		m_BlueBoxColorMax_R = cvRound(m_BackDetectionUnit->BlueBox.ColorRange.Max().val[0]*2);
		m_BlueBoxColorMax_G = cvRound(m_BackDetectionUnit->BlueBox.ColorRange.Max().val[1]/2.55);
		m_BlueBoxColorMax_B = cvRound(m_BackDetectionUnit->BlueBox.ColorRange.Max().val[2]/2.55);
	}
	else
	{
		m_IsBlueBoxHSV = FALSE;
		m_BlueBoxColorMin_R = (int)m_BackDetectionUnit->BlueBox.ColorRange.Min().val[2];
		m_BlueBoxColorMin_G = (int)m_BackDetectionUnit->BlueBox.ColorRange.Min().val[1];
		m_BlueBoxColorMin_B = (int)m_BackDetectionUnit->BlueBox.ColorRange.Min().val[0];

		m_BlueBoxColorMax_R = (int)m_BackDetectionUnit->BlueBox.ColorRange.Max().val[2];
		m_BlueBoxColorMax_G = (int)m_BackDetectionUnit->BlueBox.ColorRange.Max().val[1];
		m_BlueBoxColorMax_B = (int)m_BackDetectionUnit->BlueBox.ColorRange.Max().val[0];
	}
	

	m_BlueBoxSearchMin = m_BackDetectionUnit->BlueBox.SearchRange.Min();
	m_BlueBoxSearchMax = m_BackDetectionUnit->BlueBox.SearchRange.Max();

	m_BlueBoxPixelCount = m_BackDetectionUnit->BlueBox.PixelCount;

	//new add
	m_BlueBoxXOffset = m_BackDetectionUnit->BlueBox.XOffset;
	m_BlueBoxSearchWidth = m_BackDetectionUnit->BlueBox.SearchWidth;
	m_BlueBoxMaxGapAround = m_BackDetectionUnit->BlueBox.MaxGapAround;


	if(IsHSV(m_BackDetectionUnit->Lock.ColorRange.Min()))
	{
		m_IsLockColorHSV = TRUE;
		m_LockColorMin_R = cvRound(m_BackDetectionUnit->Lock.ColorRange.Min().val[0]*2);
		m_LockColorMin_G = cvRound(m_BackDetectionUnit->Lock.ColorRange.Min().val[1]/2.55);
		m_LockColorMin_B = cvRound(m_BackDetectionUnit->Lock.ColorRange.Min().val[2]/2.55);

		m_LockColorMax_R = cvRound(m_BackDetectionUnit->Lock.ColorRange.Max().val[0]*2);
		m_LockColorMax_G = cvRound(m_BackDetectionUnit->Lock.ColorRange.Max().val[1]/2.55);
		m_LockColorMax_B = cvRound(m_BackDetectionUnit->Lock.ColorRange.Max().val[2]/2.55);
	}
	else
	{
		m_IsLockColorHSV = FALSE;
		m_LockColorMin_R = (int)m_BackDetectionUnit->Lock.ColorRange.Min().val[2];
		m_LockColorMin_G = (int)m_BackDetectionUnit->Lock.ColorRange.Min().val[1];
		m_LockColorMin_B = (int)m_BackDetectionUnit->Lock.ColorRange.Min().val[0];

		m_LockColorMax_R = (int)m_BackDetectionUnit->Lock.ColorRange.Max().val[2];
		m_LockColorMax_G = (int)m_BackDetectionUnit->Lock.ColorRange.Max().val[1];
		m_LockColorMax_B = (int)m_BackDetectionUnit->Lock.ColorRange.Max().val[0];
	}
	
	m_LockSearchMin = m_BackDetectionUnit->Lock.SearchRange.Min();
	m_LockSearchMax = m_BackDetectionUnit->Lock.SearchRange.Max();

	m_LockPixelCount = m_BackDetectionUnit->Lock.PixelCount;


	m_BlueBoxPositionRadio = m_BackDetectionUnit->PedestalPosition == PEDESTAL_ON_BOTTOM ? 0 : 1;
	if(m_BackDetectionUnit->NeedRotate90)
		m_BlueBoxPositionRadio += 2;

	m_ImagePreProcess = m_BackDetectionUnit->PreProcess;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CBackUnitDialog::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(TRUE);

	if(m_UnitName == "")
	{
		MessageBox("名称不能为空，请输入检测名称！","输入错误",MB_OK | MB_ICONERROR);
		return;
	}

	m_BackDetectionUnit->Name = m_UnitName.GetString();
	m_BackDetectionUnit->SubImageRect = cvRect(m_SubRect_x,m_SubRect_y,m_SubRect_width,m_SubRect_height);

	m_BackDetectionUnit->NeedRotate90 = m_BlueBoxPositionRadio >= 2 ? 1 : 0;
	m_BackDetectionUnit->PedestalPosition = (m_BlueBoxPositionRadio == 0 || m_BlueBoxPositionRadio == 2) ? PEDESTAL_ON_BOTTOM : PEDESTAL_ON_TOP;

	//这里要新建
	if(m_bIsPedestalConstHeight)
	{
		shared_ptr<ConstHeightPedestalFinder> PedestalFinder = shared_ptr<ConstHeightPedestalFinder>(new ConstHeightPedestalFinder);
		PedestalFinder->ExpectHeight = m_PedestalExpectHeight;
		PedestalFinder->ReferenceDirection = m_PedestalConstHeightDirection == 0 ? DIRECTION_FROM_TOP : DIRECTION_FROM_BOTTOM;
		m_BackDetectionUnit->PedestalFinder = PedestalFinder;
	}
	else
	{
		m_BackDetectionUnit->PedestalFinder = shared_ptr<PedestalFindAlgorithm>(new SimplePedestalFinder);
	}

	m_BackDetectionUnit->PedestalFinder->XLeastPointNumber = m_PedestalXLeastPointNumber;
	m_BackDetectionUnit->PedestalFinder->YLeastPointNumber = m_PedestalYLeastPointNumber;

	if(m_IsPedestalColorHSV)
		m_BackDetectionUnit->PedestalFinder->ColorRange = Range<CvScalar>(CV_HSV(m_PedestalColorMin_R,m_PedestalColorMin_G,m_PedestalColorMin_B),CV_HSV(m_PedestalColorMax_R,m_PedestalColorMax_G,m_PedestalColorMax_B));
	else
		m_BackDetectionUnit->PedestalFinder->ColorRange = Range<CvScalar>(CV_RGB(m_PedestalColorMin_R,m_PedestalColorMin_G,m_PedestalColorMin_B),CV_RGB(m_PedestalColorMax_R,m_PedestalColorMax_G,m_PedestalColorMax_B));
	m_BackDetectionUnit->PedestalFinder->ScaleRange = Range<double>(m_PedestalScaleMin,m_PedestalScaleMax);
	m_BackDetectionUnit->PedestalFinder->SizeRange = Range<int>(m_PedestalSizeMin,m_PedestalSizeMax);

	//added in 2014/7/29
	if(m_IsCableColorHSV)
		m_BackDetectionUnit->CableDetector.ColorRange = Range<CvScalar>(CV_HSV(m_CableColorMin_R,m_CableColorMin_G,m_CableColorMin_B),CV_HSV(m_CableColorMax_R,m_CableColorMax_G,m_CableColorMax_B));
	else
		m_BackDetectionUnit->CableDetector.ColorRange = Range<CvScalar>(CV_RGB(m_CableColorMin_R,m_CableColorMin_G,m_CableColorMin_B),CV_RGB(m_CableColorMax_R,m_CableColorMax_G,m_CableColorMax_B));
	m_BackDetectionUnit->CableDetector.SearchRange = Range<int>(m_CableSearchMin,m_CableSearchMax);
	m_BackDetectionUnit->CableDetector.PixelCount = m_CablePixelCount;
	m_BackDetectionUnit->CableDetector.XOffset = m_CableXOffset;
	m_BackDetectionUnit->CableDetector.SearchWidth = m_CableSearchWidth;
	//end add 2014/7/29

	if(m_IsBlueBoxHSV)
		m_BackDetectionUnit->BlueBox.ColorRange = Range<CvScalar>(CV_HSV(m_BlueBoxColorMin_R,m_BlueBoxColorMin_G,m_BlueBoxColorMin_B),CV_HSV(m_BlueBoxColorMax_R,m_BlueBoxColorMax_G,m_BlueBoxColorMax_B));
	else
		m_BackDetectionUnit->BlueBox.ColorRange = Range<CvScalar>(CV_RGB(m_BlueBoxColorMin_R,m_BlueBoxColorMin_G,m_BlueBoxColorMin_B),CV_RGB(m_BlueBoxColorMax_R,m_BlueBoxColorMax_G,m_BlueBoxColorMax_B));
	m_BackDetectionUnit->BlueBox.SearchRange = Range<int>(m_BlueBoxSearchMin,m_BlueBoxSearchMax);
	m_BackDetectionUnit->BlueBox.PixelCount = m_BlueBoxPixelCount;

	//new add
	m_BackDetectionUnit->BlueBox.XOffset = m_BlueBoxXOffset;
	m_BackDetectionUnit->BlueBox.SearchWidth = m_BlueBoxSearchWidth;
	m_BackDetectionUnit->BlueBox.MaxGapAround = m_BlueBoxMaxGapAround;

	if(m_IsLockColorHSV)
		m_BackDetectionUnit->Lock.ColorRange = Range<CvScalar>(CV_HSV(m_LockColorMin_R,m_LockColorMin_G,m_LockColorMin_B),CV_HSV(m_LockColorMax_R,m_LockColorMax_G,m_LockColorMax_B));
	else
		m_BackDetectionUnit->Lock.ColorRange = Range<CvScalar>(CV_RGB(m_LockColorMin_R,m_LockColorMin_G,m_LockColorMin_B),CV_RGB(m_LockColorMax_R,m_LockColorMax_G,m_LockColorMax_B));
	m_BackDetectionUnit->Lock.SearchRange = Range<int>(m_LockSearchMin,m_LockSearchMax);
	m_BackDetectionUnit->Lock.PixelCount = m_LockPixelCount;
	m_BackDetectionUnit->PreProcess = m_ImagePreProcess;
	CDialog::OnOK();
}


void CBackUnitDialog::OnBnClickedEnableConstHeight()
{
	UpdateData(TRUE);
	EnableConstHeightControl(m_bIsPedestalConstHeight);
}

void CBackUnitDialog::EnableConstHeightControl( BOOL isEnable /*= TRUE*/ )
{
	GetDlgItem(IDC_EDIT24)->EnableWindow(isEnable);
	GetDlgItem(IDC_RADIO3)->EnableWindow(isEnable);
	GetDlgItem(IDC_RADIO4)->EnableWindow(isEnable);
}
