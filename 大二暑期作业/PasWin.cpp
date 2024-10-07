// PasWin.cpp: 实现文件
//

#include "pch.h"
#include "stManagement.h"
#include "afxdialogex.h"
#include "PasWin.h"
#include "PasLogin.h"
#include "stManagementDlg.h"
#include"CheckBusInfo.h"

// PasWin 对话框

IMPLEMENT_DYNAMIC(PasWin, CDialogEx)

PasWin::PasWin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PasWin, pParent)
{

}

PasWin::~PasWin()
{
}

void PasWin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PasWin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Home, &PasWin::OnBnClickedButtonHome)
	ON_BN_CLICKED(IDC_BUTTON_ToCheckBusInfo, &PasWin::OnBnClickedButtonTocheckbusinfo)
	ON_BN_CLICKED(IDC_BUTTON_ToTicketService, &PasWin::OnBnClickedButtonToticketservice)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// PasWin 消息处理程序


BOOL PasWin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	timer = SetTimer(1, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void PasWin::OnBnClickedButtonHome()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void PasWin::OnBnClickedButtonTocheckbusinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CheckBusInfo CBIDlg;
	CBIDlg.DoModal();
}


void PasWin::OnBnClickedButtonToticketservice()
{
	// TODO: 在此添加控件通知处理程序代码
	PasLogin PasLoginDlg;
	PasLoginDlg.DoModal();
}


void PasWin::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SYSTEMTIME time;
	GetLocalTime(&time);
	CString str;
	str.Format(L"%d-%d-%d %d:%d:%d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	GetDlgItem(IDC_STATIC_Time)->SetWindowText(str);

	CDialogEx::OnTimer(nIDEvent);
}
