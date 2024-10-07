// CheckoutForTicketing.cpp: 实现文件
//

#include "pch.h"
#include "stManagement.h"
#include "afxdialogex.h"
#include "CheckoutForTicketing.h"
#include"PassengerData.h"
#include"Ticketing.h"

// CheckoutForTicketing 对话框

IMPLEMENT_DYNAMIC(CheckoutForTicketing, CDialogEx)

CheckoutForTicketing::CheckoutForTicketing(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CheckoutForTicketing, pParent)
{

}

CheckoutForTicketing::~CheckoutForTicketing()
{
}

void CheckoutForTicketing::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CheckoutForTicketing, CDialogEx)
	ON_BN_CLICKED(IDOK, &CheckoutForTicketing::OnBnClickedOk)
END_MESSAGE_MAP()


// CheckoutForTicketing 消息处理程序


BOOL CheckoutForTicketing::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CheckoutForTicketing::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//p_dataFile.AddInfo(B);

	CDialogEx::OnOK();
}
