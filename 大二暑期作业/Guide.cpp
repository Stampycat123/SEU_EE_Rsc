// Guide.cpp: 实现文件
//

#include "pch.h"
#include "stManagement.h"
#include "afxdialogex.h"
#include "Guide.h"


// Guide 对话框

IMPLEMENT_DYNAMIC(Guide, CDialogEx)

Guide::Guide(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Guide, pParent)
{

}

Guide::~Guide()
{
}

void Guide::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Guide, CDialogEx)
END_MESSAGE_MAP()


// Guide 消息处理程序


BOOL Guide::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
