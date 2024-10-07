// AdminWin.cpp: 实现文件
//

#include "pch.h"
#include "stManagement.h"
#include "afxdialogex.h"
#include "AdminWin.h"
#include "stManagementDlg.h"
#include"AddBusInfo.h"
#include"AllBusInfo.h"
#include"CheckBusInfo.h"
#include"DelBus.h"


// AdminWin 对话框

IMPLEMENT_DYNAMIC(AdminWin, CDialogEx)

AdminWin::AdminWin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_AdminWin, pParent)
{

}

AdminWin::~AdminWin()
{
}

void AdminWin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AdminWin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ToAddBusInfo, &AdminWin::OnBnClickedButtonToaddbusinfo)
	ON_BN_CLICKED(IDC_BUTTON_Home, &AdminWin::OnBnClickedButtonHome)
	ON_WM_TIMER()
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &AdminWin::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON_ToAllBusInfo, &AdminWin::OnBnClickedButtonToallbusinfo)
	ON_BN_CLICKED(IDC_BUTTON_ToCheckBusInfo, &AdminWin::OnBnClickedButtonTocheckbusinfo)
	ON_BN_CLICKED(IDC_BUTTON_ToDelBus, &AdminWin::OnBnClickedButtonTodelbus)
END_MESSAGE_MAP()


// AdminWin 消息处理程序


BOOL AdminWin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	timer = SetTimer(1, 100, NULL);

	CStatic* pWelcomeAdmin = (CStatic*)GetDlgItem(IDC_STATIC_WelcomeAdmin);
	CString WelcomePasText;
	WelcomePasText.Format(L"Welcome! %S", "admin");
	pWelcomeAdmin->SetWindowTextW(WelcomePasText);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void AdminWin::OnBnClickedButtonToaddbusinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	AddBusInfo ABIDlg;
	ABIDlg.DoModal();
}


void AdminWin::OnBnClickedButtonHome()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void AdminWin::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SYSTEMTIME time;
	GetLocalTime(&time);
	CString str;
	str.Format(L"%d-%d-%d %d:%d:%d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	GetDlgItem(IDC_STATIC_Time)->SetWindowText(str);

	CDialogEx::OnTimer(nIDEvent);
}


void AdminWin::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void AdminWin::OnBnClickedButtonToallbusinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	AllBusInfo ABIDlg;
	ABIDlg.DoModal();
}


void AdminWin::OnBnClickedButtonTocheckbusinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CheckBusInfo CBIDlg;
	CBIDlg.DoModal();
}


void AdminWin::OnBnClickedButtonTodelbus()
{
	// TODO: 在此添加控件通知处理程序代码
	DelBus DBDlg;
	DBDlg.DoModal();
}
