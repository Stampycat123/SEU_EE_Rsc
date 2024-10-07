// CheckoutForReturnTicket.cpp: 实现文件
//

#include "pch.h"
#include "stManagement.h"
#include "afxdialogex.h"
#include "CheckoutForReturnTicket.h"


// CheckoutForReturnTicket 对话框

IMPLEMENT_DYNAMIC(CheckoutForReturnTicket, CDialogEx)

CheckoutForReturnTicket::CheckoutForReturnTicket(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CheckoutForReturnTicket, pParent)
{

}

CheckoutForReturnTicket::~CheckoutForReturnTicket()
{
}

void CheckoutForReturnTicket::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CheckoutForReturnTicket, CDialogEx)
END_MESSAGE_MAP()


// CheckoutForReturnTicket 消息处理程序


BOOL CheckoutForReturnTicket::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
