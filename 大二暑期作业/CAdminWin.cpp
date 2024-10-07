// CAdminWin.cpp: 实现文件
//

#include "pch.h"
#include "stManagement.h"
#include "afxdialogex.h"
#include "CAdminWin.h"


// CAdminWin 对话框

IMPLEMENT_DYNAMIC(CAdminWinDlg, CDialogEx)

CAdminWinDlg::CAdminWinDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_AdminWin, pParent)
{

}

CAdminWinDlg::~CAdminWinDlg()
{
}

void CAdminWinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAdminWinDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CAdminWinDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CAdminWin 消息处理程序


BOOL CAdminWinDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CAdminWinDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
