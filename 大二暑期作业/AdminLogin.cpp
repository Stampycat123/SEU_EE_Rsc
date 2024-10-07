// AdminLogin.cpp: 实现文件
//

#include "pch.h"
#include "stManagement.h"
#include "afxdialogex.h"
#include "AdminLogin.h"
#include "AdminWin.h"
#include "stManagementDlg.h"
#include"OperationData.h"


// AdminLogin 对话框

IMPLEMENT_DYNAMIC(AdminLogin, CDialogEx)

AdminLogin::AdminLogin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_AdminLogin, pParent)
{

}

AdminLogin::~AdminLogin()
{
}

void AdminLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AdminLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_NextStepToAdminWin, &AdminLogin::OnBnClickedButtonNextsteptoadminwin)
	ON_BN_CLICKED(IDC_BUTTON_Home, &AdminLogin::OnBnClickedButtonHome)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// AdminLogin 消息处理程序


BOOL AdminLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	timer = SetTimer(1, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void AdminLogin::OnBnClickedButtonNextsteptoadminwin()
{
	// TODO: 在此添加控件通知处理程序代码

	//密码正确
	CEdit* pEditAdminName = (CEdit*)GetDlgItem(IDC_EDIT_AdminName);
	pEditAdminName->GetWindowText(AdminName);
	CEdit* pEditAdminPW = (CEdit*)GetDlgItem(IDC_EDIT_AdminPW);
	pEditAdminPW->GetWindowText(AdminPW);

	if (AdminName == "admin" && AdminPW == "123")
	{
		SYSTEMTIME time;
		GetLocalTime(&time);
		CString Operation("adminLogin");
		CString Operator("admin");
		OperationInfoDataCstr opData(time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, Operation, Operator);
		op_dataFile.AddOperation(opData);

		AdminWin AdminWinDlg;
		AdminWinDlg.DoModal();
		OnCancel();
	}
	else
	{
		SYSTEMTIME time;
		GetLocalTime(&time);
		CString Operation("adminLoginFailed");
		CString Operator("  /  ");
		OperationInfoDataCstr opData(time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, Operation, Operator);
		op_dataFile.AddOperation(opData);
		//CStatic* pStaticError = (CStatic*)GetDlgItem(IDC_STATIC_ERROR);
		////pStaticError->OnCtlColor(RGB(255, 0, 0));
		////pStaticError->SetTextColor(RGB(255, 0, 0));
		//pStaticError->ShowWindow(SW_RESTORE);
		MessageBox(TEXT("账号或密码错误！"));
	}

}


void AdminLogin::OnBnClickedButtonHome()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}




HBRUSH AdminLogin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void AdminLogin::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SYSTEMTIME time;
	GetLocalTime(&time);
	CString str;
	str.Format(L"%d-%d-%d %d:%d:%d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	GetDlgItem(IDC_STATIC_Time)->SetWindowText(str);

	CDialogEx::OnTimer(nIDEvent);
}
