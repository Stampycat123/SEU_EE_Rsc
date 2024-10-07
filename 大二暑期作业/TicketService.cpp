// TicketService.cpp: 实现文件
//

#include "pch.h"
#include "stManagement.h"
#include "afxdialogex.h"
#include "TicketService.h"
#include "stManagementDlg.h"
#include"CheckBusInfo.h"
#include"Ticketing.h"
#include"ReturnTicket.h"
#include"ExistedBusInfo.h"
//#include"ReturnTicket.h"


// TicketService 对话框

IMPLEMENT_DYNAMIC(TicketService, CDialogEx)

TicketService::TicketService(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TicketService, pParent)
{

}

TicketService::~TicketService()
{
}

void TicketService::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TicketService, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Home, &TicketService::OnBnClickedButtonHome)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_ToCheckBusInfo, &TicketService::OnBnClickedButtonTocheckbusinfo)
	ON_BN_CLICKED(IDC_BUTTON_ToTicketing, &TicketService::OnBnClickedButtonToticketing)
	ON_BN_CLICKED(IDC_BUTTON_ToReturnTicket, &TicketService::OnBnClickedButtonToreturnticket)
	ON_BN_CLICKED(IDC_BUTTON_ToExistedBusInfo, &TicketService::OnBnClickedButtonToexistedbusinfo)
END_MESSAGE_MAP()


// TicketService 消息处理程序


BOOL TicketService::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	timer = SetTimer(1, 100, NULL);

	CStatic* pWelcomePas = (CStatic*)GetDlgItem(IDC_STATIC_WelcomePas);
	CString WelcomePasText;
	WelcomePasText.Format(L"Welcome! %S", "passenger");
	pWelcomePas->SetWindowTextW(WelcomePasText);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void TicketService::OnBnClickedButtonHome()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void TicketService::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SYSTEMTIME time;
	GetLocalTime(&time);
	CString str;
	str.Format(L"%d-%d-%d %d:%d:%d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	GetDlgItem(IDC_STATIC_Time)->SetWindowText(str);

	CDialogEx::OnTimer(nIDEvent);
}


void TicketService::OnBnClickedButtonTocheckbusinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CheckBusInfo CBIDlg;
	CBIDlg.DoModal();
}


void TicketService::OnBnClickedButtonToticketing()
{
	// TODO: 在此添加控件通知处理程序代码
	Ticketing TDlg;
	TDlg.DoModal();
}


void TicketService::OnBnClickedButtonToreturnticket()
{
	// TODO: 在此添加控件通知处理程序代码
	ReturnTicket RTDlg;
	RTDlg.DoModal();
}


void TicketService::OnBnClickedButtonToexistedbusinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	ExistedBusInfo EBIDlg;
	EBIDlg.DoModal();
}
