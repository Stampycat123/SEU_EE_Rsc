// AddBusInfo.cpp: 实现文件
//

#include "pch.h"
#include "stManagement.h"
#include "afxdialogex.h"
#include "AddBusInfo.h"
#include "BusData.h"
#include"OperationData.h"

// AddBusInfo 对话框

IMPLEMENT_DYNAMIC(AddBusInfo, CDialogEx)

AddBusInfo::AddBusInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_AddBusInfo, pParent)
{

}

AddBusInfo::~AddBusInfo()
{
}

void AddBusInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AddBusInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Ok, &AddBusInfo::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_Cancel, &AddBusInfo::OnBnClickedButtonCancel)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// AddBusInfo 消息处理程序


BOOL AddBusInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	timer = SetTimer(1, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void AddBusInfo::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码
	/*CEdit* pEditaddData[8];

	for (int i = 0; i < 8; i++)
	{
		pEditaddData[i] = (CEdit*)GetDlgItem(IDC_EDIT_AddBusInfoNum);
		pEditaddData[i]->GetWindowText(AddData.addData[i]);
	}*/
	
	/*GetDlgItem(IDC_EDIT_AddBusInfoNum)->GetWindowText(addData[0]);
	GetDlgItem(IDC_EDIT_AddBusInfoTime)->GetWindowText(addData[1]);
	GetDlgItem(IDC_EDIT_AddBusInfoStartS)->GetWindowText(addData[2]);
	GetDlgItem(IDC_EDIT_AddBusInfoEndS)->GetWindowText(addData[3]);
	GetDlgItem(IDC_EDIT_AddBusInfoExpect)->GetWindowText(addData[4]);
	GetDlgItem(IDC_EDIT_AddBusInfoPrice)->GetWindowText(addData[5]);
	GetDlgItem(IDC_EDIT_AddBusInfoMaxPas)->GetWindowText(addData[6]);
	GetDlgItem(IDC_EDIT_AddBusInfoSold)->GetWindowText(addData[7]);*/

	GetDlgItem(IDC_EDIT_AddBusInfoNum)->GetWindowText(addData[0]);
	GetDlgItem(IDC_EDIT_AddBusInfoHour)->GetWindowText(addData[1]);
	GetDlgItem(IDC_EDIT_AddBusInfoMinute)->GetWindowText(addData[2]);
	GetDlgItem(IDC_EDIT_AddBusInfoStartS)->GetWindowText(addData[3]);
	GetDlgItem(IDC_EDIT_AddBusInfoEndS)->GetWindowText(addData[4]);
	GetDlgItem(IDC_EDIT_AddBusInfoExpect)->GetWindowText(addData[5]);
	GetDlgItem(IDC_EDIT_AddBusInfoPrice)->GetWindowText(addData[6]);
	GetDlgItem(IDC_EDIT_AddBusInfoMaxPas)->GetWindowText(addData[7]);
	GetDlgItem(IDC_EDIT_AddBusInfoSold)->GetWindowText(addData[8]);

	InfoData data(addData[0], addData[1], addData[2], addData[3], addData[4], addData[5], addData[6], addData[7], addData[8]);
	g_dataFile.AddInfo(data);

	SYSTEMTIME time;
	GetLocalTime(&time);
	CString Operation("AddInfo");
	CString Operator("admin");
	OperationInfoDataCstr opData(data, time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, Operation, Operator);
	op_dataFile.AddOperation(opData);

	CDialogEx::OnOK();
}


void AddBusInfo::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < 9; i++)
		addData[i].Empty();

	CDialogEx::OnCancel();
}


void AddBusInfo::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SYSTEMTIME time;
	GetLocalTime(&time);
	CString str;
	str.Format(L"%d-%d-%d %d:%d:%d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	GetDlgItem(IDC_STATIC_Time)->SetWindowText(str);

	CDialogEx::OnTimer(nIDEvent);
}
