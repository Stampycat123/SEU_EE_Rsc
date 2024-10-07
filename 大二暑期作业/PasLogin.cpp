// PasLogin.cpp: 实现文件
//

#include "pch.h"
#include "stManagement.h"
#include "afxdialogex.h"
#include "PasLogin.h"
#include "TicketService.h"
#include "stManagementDlg.h"
#include"OperationData.h"
// PasLogin 对话框

IMPLEMENT_DYNAMIC(PasLogin, CDialogEx)

PasLogin::PasLogin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PasLogin, pParent)
{

}

PasLogin::~PasLogin()
{
}

void PasLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PasLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BackToPasWin, &PasLogin::OnBnClickedButtonBacktopaswin)
	ON_BN_CLICKED(IDC_BUTTON_NextStepToTicketService, &PasLogin::OnBnClickedButtonNextsteptoticketservice)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// PasLogin 消息处理程序


BOOL PasLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	timer = SetTimer(1, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void PasLogin::OnBnClickedButtonBacktopaswin()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void PasLogin::OnBnClickedButtonNextsteptoticketservice()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit* pEditPasName = (CEdit*)GetDlgItem(IDC_EDIT_PasName);
	pEditPasName->GetWindowText(PasName);

	if (PasName == "passenger")
	{
		SYSTEMTIME time;
		GetLocalTime(&time);
		CString Operation("pasLogin");
		CString Operator("passenger");
		OperationInfoDataCstr opData(time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, Operation, Operator);
		op_dataFile.AddOperation(opData);

		TicketService TicketServiceDlg;
		TicketServiceDlg.DoModal();
		OnCancel();
		//特定用户登录提示
		/*CStatic* pStaticWelcomePas = (CStatic*)GetDlgItem(IDC_STATIC_WelcomePas);
		
		CFont font;
		int n = sizeof("passenger");
		font.CreatePointFont(n, _T"欢迎！%s用户", "passenger");*/
	}
	else
	{
		SYSTEMTIME time;
		GetLocalTime(&time);
		CString Operation("pasLoginFailed");
		CString Operator("  /  ");
		OperationInfoDataCstr opData(time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, Operation, Operator);
		op_dataFile.AddOperation(opData);

		CStatic* pStaticError2 = (CStatic*)GetDlgItem(IDC_STATIC_ERROR2);
		//pStaticError->OnCtlColor(RGB(255, 0, 0));
		//pStaticError->SetTextColor(RGB(255, 0, 0));
		pStaticError2->ShowWindow(SW_RESTORE);
	}
}


void PasLogin::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SYSTEMTIME time;
	GetLocalTime(&time);
	CString str;
	str.Format(L"%d-%d-%d %d:%d:%d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	GetDlgItem(IDC_STATIC_Time)->SetWindowText(str);

	CDialogEx::OnTimer(nIDEvent);
}
