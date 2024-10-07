// ReturnTicket.cpp: 实现文件
//

#include "pch.h"
#include "stManagement.h"
#include "afxdialogex.h"
#include "ReturnTicket.h"
#include"PassengerData.h"
#include"CheckoutForReturnTicket.h"
#include"OperationData.h"

// ReturnTicket 对话框

IMPLEMENT_DYNAMIC(ReturnTicket, CDialogEx)

ReturnTicket::ReturnTicket(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ReturnTicket, pParent)
{

}

ReturnTicket::~ReturnTicket()
{
}

void ReturnTicket::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ReturnTicket, Data_ReturnTicket);
}


BEGIN_MESSAGE_MAP(ReturnTicket, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Check, &ReturnTicket::OnBnClickedButtonCheck)
	ON_BN_CLICKED(IDC_BUTTON_Return, &ReturnTicket::OnBnClickedButtonReturn)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_Cancel2, &ReturnTicket::OnBnClickedButtonCancel2)
END_MESSAGE_MAP()


// ReturnTicket 消息处理程序


BOOL ReturnTicket::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	timer = SetTimer(1, 100, NULL);

	CButton* pButtonR = (CButton*)GetDlgItem(IDC_BUTTON_Return);
	pButtonR->EnableWindow(false);
	Data_ReturnTicket.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	Data_ReturnTicket.InsertColumn(0, L"车次号", LVCFMT_CENTER, 300);
	Data_ReturnTicket.InsertColumn(1, L"发车时间", LVCFMT_CENTER, 200);
	Data_ReturnTicket.InsertColumn(2, L"始发站", LVCFMT_CENTER, 250);
	Data_ReturnTicket.InsertColumn(3, L"终点站", LVCFMT_CENTER, 250);
	Data_ReturnTicket.InsertColumn(4, L"预计用时", LVCFMT_CENTER, 200);
	Data_ReturnTicket.InsertColumn(5, L"票价", LVCFMT_CENTER, 150);
	Data_ReturnTicket.InsertColumn(6, L"最大载客数", LVCFMT_CENTER, 250);
	Data_ReturnTicket.InsertColumn(7, L"已售票数", LVCFMT_CENTER, 200);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ReturnTicket::OnBnClickedButtonCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pButtonR = (CButton*)GetDlgItem(IDC_BUTTON_Return);
	pButtonR->EnableWindow(false);

	InfoData data;
	CString stri;

	CString R;
	CEdit* pEditR = (CEdit*)GetDlgItem(IDC_EDIT_Return);
	pEditR->GetWindowText(R);

	DATALIST_TYPE* pDataList = g_dataFile.GetDatalist();
	Data_ReturnTicket.DeleteAllItems();

	if (g_dataFile.Find(R))
	{
		pButtonR->EnableWindow(true);

		POSITION posi = g_dataFile.Find(R);
		data = pDataList->GetAt(posi);

		InfoDataCStr datacstr(data);
		Data_ReturnTicket.InsertItem(0, stri);
		Data_ReturnTicket.SetItemText(0, 0, datacstr.no);
		Data_ReturnTicket.SetItemText(0, 1, datacstr.hourMinnute);
		Data_ReturnTicket.SetItemText(0, 2, datacstr.Starting_station);
		Data_ReturnTicket.SetItemText(0, 3, datacstr.Last_station);
		Data_ReturnTicket.SetItemText(0, 4, datacstr.time);
		Data_ReturnTicket.SetItemText(0, 5, datacstr.fare);
		Data_ReturnTicket.SetItemText(0, 6, datacstr.maxPas);
		Data_ReturnTicket.SetItemText(0, 7, datacstr.sold);

		SYSTEMTIME time;
		GetLocalTime(&time);
		CString Operation("ReturnTicketCheck");
		CString Operator("passenger");
		OperationInfoDataCstr opData(data, time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, Operation, Operator);
		op_dataFile.AddOperation(opData);
	}
}


void ReturnTicket::OnBnClickedButtonReturn()
{
	// TODO: 在此添加控件通知处理程序代码
	CString R;
	CEdit* pEditR = (CEdit*)GetDlgItem(IDC_EDIT_Return);
	pEditR->GetWindowText(R);
	if (p_dataFile.Find(R))
	{
		p_dataFile.DelInfo(R);

		POSITION posi = g_dataFile.Find(R);
		DATALIST_TYPE* pDataList = g_dataFile.GetDatalist();
		InfoData data = pDataList->GetAt(posi);
		SYSTEMTIME time;
		GetLocalTime(&time);
		CString Operation("ReturnTicket");
		CString Operator("passenger");
		OperationInfoDataCstr opData(data, time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, Operation, Operator);
		op_dataFile.AddOperation(opData);

		pDataList->GetAt(posi).sold--;
		MessageBox(TEXT("退票成功！确认以继续..."));

		OnOK();
	}
	else 
	{
		MessageBox(TEXT("不存在该行程！"));
	}
	/*CheckoutForReturnTicket CFRTDlg;
	CFRTDlg.DoModal();*/
}


void ReturnTicket::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SYSTEMTIME time;
	GetLocalTime(&time);
	CString str;
	str.Format(L"%d-%d-%d %d:%d:%d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	GetDlgItem(IDC_STATIC_Time)->SetWindowText(str);
	CDialogEx::OnTimer(nIDEvent);
}


void ReturnTicket::OnBnClickedButtonCancel2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
