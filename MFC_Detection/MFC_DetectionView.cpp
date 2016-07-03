
// MFC_DetectionView.cpp : CMFC_DetectionView 类的实现
//

#include "stdafx.h"
#include "MFC_Detection.h"

#include "MFC_DetectionDoc.h"
#include "MFC_DetectionView.h"
#include "ProgramSelectDialog.h"

#include "DetectionProgramDialog.h"
#include "EnterPasswordDialog.h"
#include "EditPasswordDialog.h"
#include "SelectProgramDialog.h"
#include "Comm.h"
#include "RegLisenseDialog.h"

#include "../DetectionLib/FrontDetectionUnit.hpp"
#include "../DetectionLib/BackDetectionUnit.hpp"
#include "../DetectionLib/HardLockDetectionUnit.hpp"
#include "../DetectionLib/NoLockDetectionUnit.hpp"
#include "../DetectionLib/ImageSourceFactory.hpp"
#include "../DetectionLib/License.h"

#include <boost/foreach.hpp>
#include <sstream>


#ifdef _DEBUG
#pragma comment(lib,"cxcore200d.lib")
#pragma comment(lib,"cv200d.lib")
#pragma comment(lib,"highgui200d.lib")
#else
#pragma comment(lib,"cxcore200.lib")
#pragma comment(lib,"cv200.lib")
#pragma comment(lib,"highgui200.lib")
#endif

#pragma comment(lib,"HVDAILT.lib")
#pragma comment(lib,"Raw2Rgb.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


Comm gCommObject;

// CMFC_DetectionView

IMPLEMENT_DYNCREATE(CMFC_DetectionView, CFormView)

BEGIN_MESSAGE_MAP(CMFC_DetectionView, CFormView)
	ON_BN_CLICKED(IDC_GET_PIC, &CMFC_DetectionView::OnBnClickedGetPic)
//	ON_WM_PAINT()
ON_WM_SIZE()
ON_WM_PAINT()
ON_MESSAGE(WM_COMM_EVENT,&CMFC_DetectionView::OnCommProc)
ON_MESSAGE(WM_NOTIFY_MANUAL_PASS,&CMFC_DetectionView::OnManualPassProc)
ON_BN_CLICKED(IDC_GET_PIC2, &CMFC_DetectionView::OnBnClickedGetPic2)
ON_BN_CLICKED(IDC_GET_PIC3, &CMFC_DetectionView::OnBnClickedGetPic3)
ON_COMMAND(ID_MENU_SELECT_PROGRAM, &CMFC_DetectionView::OnMenuSelectProgram)
ON_COMMAND(ID_MENU_ADD_PROGRAM, &CMFC_DetectionView::OnMenuAddProgram)
ON_COMMAND(ID_MENU_EDIT_PROGRAM, &CMFC_DetectionView::OnMenuEditProgram)
ON_COMMAND(ID_MENU_DEL_PROGRAM, &CMFC_DetectionView::OnMenuDelProgram)
ON_COMMAND(ID_EDIT_CURRENT, &CMFC_DetectionView::OnEditCurrent)
ON_UPDATE_COMMAND_UI(ID_MENU_ADD_PROGRAM, &CMFC_DetectionView::OnUpdateMenuAddProgram)
ON_UPDATE_COMMAND_UI(ID_MENU_EDIT_PROGRAM, &CMFC_DetectionView::OnUpdateMenuEditProgram)
ON_UPDATE_COMMAND_UI(ID_MENU_DEL_PROGRAM, &CMFC_DetectionView::OnUpdateMenuDelProgram)
ON_UPDATE_COMMAND_UI(ID_MENU_SELECT_PROGRAM, &CMFC_DetectionView::OnUpdateMenuSelectProgram)
ON_COMMAND(ID_EDIT_SECOND, &CMFC_DetectionView::OnEditSecond)
ON_COMMAND(ID_MENU_EDIT_PASSWORD, &CMFC_DetectionView::OnMenuEditPassword)
ON_COMMAND(ID_REG_SOFT, &CMFC_DetectionView::OnRegSoft)
ON_UPDATE_COMMAND_UI(ID_REG_SOFT, &CMFC_DetectionView::OnUpdateRegSoft)
ON_WM_SETFOCUS()
END_MESSAGE_MAP()

// CMFC_DetectionView 构造/析构

CMFC_DetectionView::CMFC_DetectionView()
	: CFormView(CMFC_DetectionView::IDD)
	, m_ErrorString(_T(""))
	, m_strBarCode(_T(""))
	, itsCurrentCheckStep(0)
{
	// TODO: 在此处添加构造代码

}

CMFC_DetectionView::~CMFC_DetectionView()
{
}

void CMFC_DetectionView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ERROR_STRING, m_ErrorString);
	DDX_Control(pDX, IDC_ERROR_STRING, m_editError);
	DDX_Control(pDX, IDC_EDIT_NUMBER, m_BarCodeEdit);
	DDX_Text(pDX, IDC_EDIT_NUMBER, m_strBarCode);
}

BOOL CMFC_DetectionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CMFC_DetectionView::OnInitialUpdate()
{
	//CFormView::OnInitialUpdate();
	//GetParentFrame()->RecalcLayout();
	//ResizeParentToFit();


	UpdateData(FALSE);

	m_ManualPassDlg.Create(IDD_DLG_MANUAL_PASS,this);
	m_ManualPassDlg.m_MsgWnd = m_hWnd;
	
	m_editFont.CreatePointFont(200,"宋体");
	m_editError.SetFont(&m_editFont);


	m_FirstProgram = shared_ptr<DetectionProgram>(new DetectionProgram);
	m_SecondProgram = shared_ptr<DetectionProgram>(new DetectionProgram);
	wptree pt_read;
	CString ProgramName;
	try
	{
		//读取所有程序，选择默认程序
		read_xml("./FirstConfigLine.xml",pt_read);
		m_FirstStepLine.ReadFromTree(pt_read);
		::GetPrivateProfileString("Program","FirstProgramName","",ProgramName.GetBuffer(100),100,".\\Config.ini");
		ProgramName.ReleaseBuffer();
		foreach(shared_ptr<DetectionProgram> dp,m_FirstStepLine)
		{
			if(dp->Name == string(ProgramName.GetString()))
			{	
				m_FirstProgram = dp;
				break;
			}
		}
	}
	catch (...)
	{
		MessageBox("读取检测参数失败");
	}
	try
	{
		//读取所有程序，选择默认程序
		read_xml("./SecondConfigLine.xml",pt_read);
		m_SecondStepLine.ReadFromTree(pt_read);
		::GetPrivateProfileString("Program","SecondProgramName","",ProgramName.GetBuffer(200),200,".\\Config.ini");
		ProgramName.ReleaseBuffer();
		foreach(shared_ptr<DetectionProgram> dp,m_SecondStepLine)
		{
			if(dp->Name == string(ProgramName.GetString()))
			{	
				m_SecondProgram = dp;
				break;
			}
		}
	}
	catch (...)
	{
	}

	//add in 2015/4/30
	CString strScreenShotPath;
	::GetPrivateProfileString("ScreenShot","Path","D:\\ScreenShot",strScreenShotPath.GetBuffer(255),255,".\\Config.ini");
	strScreenShotPath.ReleaseBuffer();
	strScreenShotPath.TrimRight("\\");
	::WritePrivateProfileString("ScreenShot","Path",strScreenShotPath,".\\Config.ini");
	itsScreenShotPath = strScreenShotPath.GetString();
	itsMaxImagesPerFolder = ::GetPrivateProfileInt("ScreenShot","MaxImages",400,".\\Config.ini");
	CString strMaxImage;
	strMaxImage.Format("%d",itsMaxImagesPerFolder);
	::WritePrivateProfileString("ScreenShot","MaxImages",strMaxImage,".\\Config.ini");

	//读取配置文件
	int comPort = ::GetPrivateProfileInt("COM","Port",1,".\\Config.ini");
	CString StrPort;
	StrPort.Format("COM%d",comPort);
	while(!gCommObject.ConnectComm(StrPort))
	{
		if(++comPort > 10)
		{
			MessageBox("串口打开失败！");
			return;			
		}
		StrPort.Format("COM%d",comPort);
	}
	StrPort.Format("%d",comPort);
	::WritePrivateProfileString("COM","Port",StrPort,".\\Config.ini");
	//打开串口成功，开始接受数据
	gCommObject.SetClientWnd(m_hWnd);
	gCommObject.StartReceive();
	//请不要在这增加代码，因为串口打开失败可能不执行。
}


// CMFC_DetectionView 诊断

#ifdef _DEBUG
void CMFC_DetectionView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFC_DetectionView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFC_DetectionDoc* CMFC_DetectionView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_DetectionDoc)));
	return (CMFC_DetectionDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_DetectionView 消息处理程序
void CMFC_DetectionView::OnBnClickedGetPic()
{	
	IplImage_Ptr img = cvLoadImage("d:\\test.jpg");
	Detect(img,GetDetectionProgram());
	
}
void CMFC_DetectionView::OnBnClickedGetPic2()
{
	/*IplImage_Ptr img = cvLoadImage("H:\\project\\天宝电子\\排线检测\\testWholePic\\4.jpg");
	Detect(img);*/
	shared_ptr<ImageSource> camera_source = ImageSourceFactory::GetImageFromCamera();
	IplImage_Ptr img = camera_source->GetImage();
	if(img)
		cvSaveImage("d:\\test.jpg",img);
}


DetectionResultList CMFC_DetectionView::Detect( IplImage_Ptr img ,shared_ptr<DetectionProgram> dp )
{
	DetectionResultList drl;
	m_NeedManualCheck = false;
	UpdateData(TRUE);
	if(PassLicense())
	{
		if(m_strBarCode != "")
		{
			if(img)
			{
				try
				{
					dp->SetScreenShot(itsScreenShotPath+ "\\" +dp->Name,itsMaxImagesPerFolder); //add in 2015/4/28
					dp->Detect(img,drl);
					if(!FirstErrorResult(drl).IsPass)
						m_NeedManualCheck = true;
				}
				catch(const cv::Exception& e)
				{
					FirstErrorResult(drl).IsPass = false;
					FirstErrorResult(drl).ErrorString = e.err;
					m_NeedManualCheck = true;
				}				
			}
			else
			{
				FirstErrorResult(drl).IsPass = false;
				FirstErrorResult(drl).ErrorString = "获取图片错误！请检查摄像头的连接！";
			}
		}
		else
		{
			FirstErrorResult(drl).IsPass = false;
			FirstErrorResult(drl).ErrorString = "请扫条码！";
		}
		ForNextNumberInput();
	}
	else
	{
		FirstErrorResult(drl).IsPass = false;
		FirstErrorResult(drl).ErrorString = "无法使用检测程序，软件未注册！";
	}
	ShowResult(FirstErrorResult(drl));
	return drl;
}


shared_ptr<DetectionProgram> CMFC_DetectionView::GetDetectionProgram()
{	
	if(1 == itsCurrentCheckStep)
		return m_FirstProgram;
	else if(2 == itsCurrentCheckStep)
		return m_SecondProgram;
	else
		return m_FirstProgram;
}





void CMFC_DetectionView::OnBnClickedGetPic3()
{
	shared_ptr<ImageSource> camera_source = ImageSourceFactory::GetImageFromCamera();
	IplImage_Ptr img = camera_source->GetImage();
	Detect(img,GetDetectionProgram());
	
}


void CMFC_DetectionView::ShowResult(DetectionResult& dr)
{
	itsResultImage.CopyOf(dr.ResultImage);
	m_ErrorString = dr.ErrorString.c_str();
	m_Brush.DeleteObject();
	if(dr.IsPass)
		m_Brush.CreateSolidBrush(RGB(0,255,0));
	else
		m_Brush.CreateSolidBrush(RGB(255,0,0));
	UpdateData(FALSE);
	Invalidate();
}



void CMFC_DetectionView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	if(GetDlgItem(IDC_RESULT_PIC) != NULL)
	{
		int result_x = cx - 250;
		int result_y = cy;
		if((double)result_y/result_x > 0.75)
			result_y = int(double(result_x * 0.75));
		else
			result_x = int(double(result_y * 4 / 3));
		GetDlgItem(IDC_RESULT_PIC)->SetWindowPos(NULL,0,0,result_x,result_y,SWP_NOZORDER | SWP_NOMOVE);

		int center_x = (result_x + cx )/2;

		GetDlgItem(IDC_TXT_NUMBER)->SetWindowPos(NULL,center_x - 85,25,0,0,SWP_NOZORDER | SWP_NOSIZE);
		GetDlgItem(IDC_EDIT_NUMBER)->SetWindowPos(NULL,center_x - 40,20,0,0,SWP_NOZORDER | SWP_NOSIZE);
		GetDlgItem(IDC_GET_PIC)->SetWindowPos(NULL,center_x - 40,20 + 50,0,0,SWP_NOZORDER | SWP_NOSIZE);
		GetDlgItem(IDC_GET_PIC2)->SetWindowPos(NULL,center_x - 40, 50+ 50,0,0,SWP_NOZORDER | SWP_NOSIZE);
		GetDlgItem(IDC_GET_PIC3)->SetWindowPos(NULL,center_x - 40, 80+ 50,0,0,SWP_NOZORDER | SWP_NOSIZE);
		GetDlgItem(IDC_STATE_PIC)->SetWindowPos(NULL,center_x - 40,result_y / 2,0,0,SWP_NOZORDER | SWP_NOSIZE);
		GetDlgItem(IDC_ERROR_STRING)->SetWindowPos(NULL,center_x - 110,result_y - 100,0,0,SWP_NOZORDER | SWP_NOSIZE);
	}
	
}

void CMFC_DetectionView::OnPaint()
{
	CPaintDC dc(this); 
	CWnd* pResultPic = GetDlgItem(IDC_RESULT_PIC);
	CRect result_pic_rect;
	pResultPic->GetClientRect(&result_pic_rect);
	if(itsResultImage.GetImage())
	{
		itsResultImage.DrawToHDC(pResultPic->GetDC()->GetSafeHdc(),result_pic_rect);
	}
	CRgn DrawRgn;
	DrawRgn.CreateEllipticRgn(0,0,80,80);
	GetDlgItem(IDC_STATE_PIC)->GetDC()->FillRgn(&DrawRgn,&m_Brush);
}







void CMFC_DetectionView::OnMenuSelectProgram()
{
	//CProgramSelectDialog dlg(DIALOG_SELECT);
	//dlg.DoModal();
	CSelectProgramDialog dlg;
	dlg.m_FirstStepLine = &m_FirstStepLine;
	dlg.m_SecondStepLine = &m_SecondStepLine;
	dlg.m_FirstProgram = m_FirstProgram;
	dlg.m_SecondProgram = m_SecondProgram;
	if(dlg.DoModal() == IDOK)
	{
		m_FirstProgram = dlg.m_FirstProgram;
		m_SecondProgram = dlg.m_SecondProgram;
		::WritePrivateProfileString("Program","FirstProgramName",m_FirstProgram->Name.c_str(),".\\Config.ini");
		::WritePrivateProfileString("Program","SecondProgramName",m_SecondProgram->Name.c_str(),".\\Config.ini");
	}
}

void CMFC_DetectionView::OnMenuAddProgram()
{
	CProgramSelectDialog dlg(DIALOG_ADD);
	dlg.DoModal();
}

void CMFC_DetectionView::OnMenuEditProgram()
{
	CProgramSelectDialog dlg(DIALOG_EDIT);
	dlg.DoModal();
}

void CMFC_DetectionView::OnMenuDelProgram()
{
	CProgramSelectDialog dlg(DIALOG_DEL);
	dlg.DoModal();
}

void CMFC_DetectionView::OnEditCurrent()
{
	//加密
	if(PassPassword())
	{
		shared_ptr<DetectionProgram> dp = GetDetectionProgram();

		CDetectionProgramDialog dpd(*dp);

		if(dpd.DoModal() == IDOK)
		{
			dp->CopyOf(dpd.m_DetectionProgram);
			write_xml("./FirstConfigLine.xml",m_FirstStepLine.GetTree());
		}
	}
}

void CMFC_DetectionView::OnEditSecond()
{
	if(PassPassword())
	{
		shared_ptr<DetectionProgram> dp = m_SecondProgram;

		CDetectionProgramDialog dpd(*dp);

		if(dpd.DoModal() == IDOK)
		{
			dp->CopyOf(dpd.m_DetectionProgram);
			write_xml("./SecondConfigLine.xml",m_SecondStepLine.GetTree());
		}
	}
}


void CMFC_DetectionView::OnUpdateMenuAddProgram(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

void CMFC_DetectionView::OnUpdateMenuEditProgram(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

void CMFC_DetectionView::OnUpdateMenuDelProgram(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

void CMFC_DetectionView::OnUpdateMenuSelectProgram(CCmdUI *pCmdUI)
{
	//pCmdUI->Enable(FALSE);
}

LRESULT CMFC_DetectionView::OnCommProc( WPARAM wParam, LPARAM lParam )
{
		//process last result first
		if (itsInManualConfirming)
		{
			m_ManualPassDlg.EndDialog(0);
			itsInManualConfirming = false;
			itsManualTimer.Stop();
			//write report
			DetectionResult manual_result; //manual_result is used for report
			manual_result.IsPass = false;
			manual_result.AddItemReport(GetDetectionProgram()->Name,"ManualCheckCancel",manual_result.IsPass,itsManualTimer.GetTime());
			if(1 == itsCurrentCheckStep)
			{
				itsFirstDetectResult.push_back(manual_result);
				m_stopTimer = std::time(NULL);
				WriteReport(itsFirstDetectResult);
			}
			else if(2 == itsCurrentCheckStep)
			{
				MergeFirstResult2SecondResult();
				FirstErrorResult(itsSecondDetectResult).IsPass = FirstErrorResult(itsSecondDetectResult).IsPass & FirstErrorResult(itsFirstDetectResult).IsPass;
				itsSecondDetectResult.push_back(manual_result);
				m_stopTimer = std::time(NULL);
				WriteReport(itsSecondDetectResult);
			}
		}
		UCHAR cmd = (UCHAR)wParam;
		shared_ptr<ImageSource> camera_source = ImageSourceFactory::GetImageFromCamera();
		IplImage_Ptr img = camera_source->GetImage();
		if(cmd == 0xA0)
		{			
			itsCurrentCheckStep = 1;
			m_startTimer = std::time(NULL); //anyway, start time from here
			itsFirstDetectResult = Detect(img,GetDetectionProgram());


			if(m_NeedManualCheck)
				StartManualJudge();
			if(FirstErrorResult(itsFirstDetectResult).IsPass) // if only one step and passed, done here
			{
				gCommObject.SendCommData(0x01); 
				if(!HasSecondStep())
				{
					m_stopTimer = std::time(NULL);
					//输出report, 
					WriteReport(itsFirstDetectResult);
				}
			}			
		}
		else if(cmd == 0xA1)
		{
			itsCurrentCheckStep = 2;
			itsSecondDetectResult = Detect(img,GetDetectionProgram());
			
			if(m_NeedManualCheck)
				StartManualJudge();
			if(FirstErrorResult(itsSecondDetectResult).IsPass) //pass, done here
			{
				gCommObject.SendCommData(0x01);
				//sure has second step,
				MergeFirstResult2SecondResult();
				FirstErrorResult(itsSecondDetectResult).IsPass = FirstErrorResult(itsSecondDetectResult).IsPass & FirstErrorResult(itsFirstDetectResult).IsPass;
				m_stopTimer = std::time(NULL);
				//输出report,
				WriteReport(itsSecondDetectResult);
				FirstErrorResult(itsFirstDetectResult).Report.clear();
				FirstErrorResult(itsFirstDetectResult).IsPass = false;
			}			
		}
	return 0;
}

bool CMFC_DetectionView::PassPassword()
{
	CEnterPasswordDialog dlg;
	return dlg.DoModal() == IDOK;
}




void CMFC_DetectionView::OnMenuEditPassword()
{
	CEditPasswordDialog dlg;
	dlg.DoModal();
}

bool CMFC_DetectionView::PassLicense()
{
	CString ExpertLicense;
	::GetPrivateProfileString("Manage","Lisense","",ExpertLicense.GetBuffer(100),100,".\\Config.ini");
	ExpertLicense.ReleaseBuffer();
	return GetLicenseCode() == string(ExpertLicense.GetString());
}


void CMFC_DetectionView::OnRegSoft()
{
	CRegLisenseDialog dlg;
	if(dlg.DoModal() == IDOK)
	{
		::WritePrivateProfileString("Manage","Lisense",GetLicenseCode().c_str(),".\\Config.ini");
		MessageBox("软件注册成功！");
	}
}


void CMFC_DetectionView::OnUpdateRegSoft(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!PassLicense());
}



void CMFC_DetectionView::ForNextNumberInput()
{
	SetThisWindowForground();
	GetDlgItem(IDC_EDIT_NUMBER)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_NUMBER)->SetFocus();
	m_BarCodeEdit.SetSel(0,-1);
}

void CMFC_DetectionView::SetThisWindowForground()
{
	HWND hForeWnd = NULL; 
	HWND hWnd= this->m_hWnd;
	DWORD dwForeID; 
	DWORD dwCurID; 

	hForeWnd =  ::GetForegroundWindow(); 
	dwCurID =  ::GetCurrentThreadId(); 
	dwForeID =  ::GetWindowThreadProcessId( hForeWnd, NULL ); 
	::AttachThreadInput( dwCurID, dwForeID, TRUE); 
	::ShowWindow( hWnd, SW_SHOWNORMAL ); 
	::SetWindowPos( hWnd, HWND_TOPMOST, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE ); 
	::SetWindowPos( hWnd, HWND_NOTOPMOST, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE ); 
	::SetForegroundWindow( hWnd ); 
	::AttachThreadInput( dwCurID, dwForeID, FALSE);
}


void CMFC_DetectionView::OnSetFocus(CWnd* pOldWnd)
{
	CFormView::OnSetFocus(pOldWnd);
	GetDlgItem(IDC_EDIT_NUMBER)->SetFocus();	
}





CString FormatTimeNomal(time_t t)
{
	CString str;
	struct tm local;  
	time_t temp = t;
	localtime_s(&local,&temp);   
	str.Format("%4d-%02d-%02d %02d:%02d:%02d",local.tm_year+1900,local.tm_mon+1,local.tm_mday,local.tm_hour,local.tm_min,local.tm_sec);
	return str;
}


CString FormatTimeOnlyNumber(time_t t)
{
	CString str;
	time_t temp = t;
	struct tm local;;    
	localtime_s(&local,&temp);
	str.Format("%4d%02d%02d%02d%02d%02d",local.tm_year+1900,local.tm_mon+1,local.tm_mday,local.tm_hour,local.tm_min,local.tm_sec);
	return str;
}

string BuildFileName(const string& strBarCode, const string& extention)
{
	string str;
	str = strBarCode + '_' + FormatTimeOnlyNumber(time(NULL)).GetString() + '.' + extention;
	return str;
}



void CMFC_DetectionView::WriteReport(DetectionResultList& drl)
{
	int unitID(0),itemID(0);

	bool first_error_result_replaced = false;
	ostringstream report_string;
	BOOST_FOREACH(DetectionResult dr, NormalResultList(drl))
	{
		ReportLineList report_line;
		if(!first_error_result_replaced && !dr.IsPass) // replace first error result
		{
			report_line = FirstErrorResult(drl).Report;
			first_error_result_replaced = true;
		}
		else
			report_line = dr.Report;
		BOOST_FOREACH(ReportLine_Ptr& l, report_line)
		{
			if(auto item = std::dynamic_pointer_cast<ReportItem>(l))
			{
				report_string << ++itemID << "\t" << item->GetReportString() << "\n";
			}
		}
	}

	string filepath = string("D:\\TestData\\") + BuildFileName(m_strBarCode.GetString(),"dat");
	ofstream dataFile(filepath.c_str());
	dataFile << "ObjectID=" << m_strBarCode.GetString() << "\n";
	dataFile << "StartTime=" << FormatTimeNomal(m_startTimer).GetString() << "\n";
	dataFile << "TestSteps="<<itemID <<"\n";
	dataFile << "No.\tTest Item\tLow Limit\tCriterion\tHigh Limit Unit\tP/F\tRemark\tValue1\tTime(ms)\n";
	dataFile << report_string.str();
	dataFile << "EndTime=" << FormatTimeNomal(m_stopTimer).GetString() << "\n";
	dataFile.close();

	filepath = string("D:\\TestFlag\\") + BuildFileName(m_strBarCode.GetString(),"flg");
	ofstream flagFile(filepath.c_str());
	if(FirstErrorResult(drl).IsPass)
		flagFile << 1;
	else
		flagFile << 0;
	flagFile.close();
}

bool CMFC_DetectionView::HasSecondStep()
{
	return m_SecondProgram->Name != "";
}

void CMFC_DetectionView::StartManualJudge()
{	
	itsManualTimer.Start();
	itsInManualConfirming = true;
	m_ManualPassDlg.ShowWindow(SW_SHOWNORMAL);
}

LRESULT CMFC_DetectionView::OnManualPassProc( WPARAM wParam, LPARAM lParam )
{
	itsInManualConfirming = false;
	if(MSG_PASS == wParam)
		gCommObject.SendCommData(0x01);
	else
		gCommObject.SendCommData(0x02);
	itsManualTimer.Stop();

	DetectionResult manual_result; //manual_result is used for report
	manual_result.IsPass = bool(MSG_PASS == wParam);
	manual_result.AddItemReport(GetDetectionProgram()->Name,"ManualCheck",manual_result.IsPass,itsManualTimer.GetTime());

	if(1 == itsCurrentCheckStep)
	{
		itsFirstDetectResult.push_back(manual_result);
		FirstErrorResult(itsFirstDetectResult).IsPass =  bool(MSG_PASS == wParam);
		if(FirstErrorResult(itsFirstDetectResult).IsPass)
		{
			FirstErrorResult(itsFirstDetectResult).ErrorString = "人工检查通过！";
			ShowResult(FirstErrorResult(itsFirstDetectResult));
		}
		if(!HasSecondStep()) //only one step, done here
		{
			m_stopTimer = std::time(NULL);
			WriteReport(itsFirstDetectResult);
		}
	}
	else if (2 == itsCurrentCheckStep)
	{
		itsSecondDetectResult.push_back(manual_result);
		FirstErrorResult(itsSecondDetectResult).IsPass = bool(MSG_PASS == wParam);
		if(FirstErrorResult(itsSecondDetectResult).IsPass)
		{
			FirstErrorResult(itsSecondDetectResult).ErrorString = "人工检查通过！";
			ShowResult(FirstErrorResult(itsSecondDetectResult));
		}
		//write report
		MergeFirstResult2SecondResult();
		FirstErrorResult(itsSecondDetectResult).IsPass = FirstErrorResult(itsSecondDetectResult).IsPass & FirstErrorResult(itsFirstDetectResult).IsPass;
		m_stopTimer = std::time(NULL);
		//输出report,
		WriteReport(itsSecondDetectResult);
		FirstErrorResult(itsFirstDetectResult).Report.clear();
		FirstErrorResult(itsFirstDetectResult).IsPass = false;
	}
	
	return 0;
}

void CMFC_DetectionView::MergeFirstResult2SecondResult()
{
	DetectionResult second_error_result = itsSecondDetectResult.front();
	itsSecondDetectResult.pop_front();
	DetectionResultList first_normal_result = NormalResultList(itsFirstDetectResult);
	std::copy(first_normal_result.rbegin(),first_normal_result.rend(),front_inserter(itsSecondDetectResult)); // insert first result
	itsSecondDetectResult.push_front(second_error_result);
}
