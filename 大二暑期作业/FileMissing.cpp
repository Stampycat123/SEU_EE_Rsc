// FileMissing.cpp: 实现文件
//

#include "pch.h"
#include "stManagement.h"
#include "afxdialogex.h"
#include "FileMissing.h"


// FileMissing 对话框

IMPLEMENT_DYNAMIC(FileMissing, CDialogEx)

FileMissing::FileMissing(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FileMissing, pParent)
{

}

FileMissing::~FileMissing()
{
}

void FileMissing::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FileMissing, CDialogEx)
	ON_BN_CLICKED(IDOK, &FileMissing::OnBnClickedOk)
END_MESSAGE_MAP()


// FileMissing 消息处理程序


BOOL FileMissing::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void FileMissing::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
