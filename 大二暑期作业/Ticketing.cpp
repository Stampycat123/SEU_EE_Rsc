// Ticketing.cpp: 实现文件
//

#include "pch.h"
#include "stManagement.h"
#include "afxdialogex.h"
#include "Ticketing.h"
#include"PassengerData.h"
#include"BusData.h"
#include"CheckoutForTicketing.h"
#include"OperationData.h"

extern CString B;

// Ticketing 对话框

IMPLEMENT_DYNAMIC(Ticketing, CDialogEx)

Ticketing::Ticketing(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Ticketing, pParent)
{

}

Ticketing::~Ticketing()
{
}

void Ticketing::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Ticketing, Data_Ticketing);
}


BEGIN_MESSAGE_MAP(Ticketing, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Ok, &Ticketing::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_Check, &Ticketing::OnBnClickedButtonCheck)
	ON_BN_CLICKED(IDC_BUTTON_Buy, &Ticketing::OnBnClickedButtonBuy)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_Cancel2, &Ticketing::OnBnClickedButtonCancel2)
END_MESSAGE_MAP()


// Ticketing 消息处理程序


BOOL Ticketing::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始
	timer = SetTimer(1, 100, NULL);
	CButton* pButtonB = (CButton*)GetDlgItem(IDC_BUTTON_Buy);
	pButtonB->EnableWindow(false);

	Data_Ticketing.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	Data_Ticketing.InsertColumn(0, L"车次号", LVCFMT_CENTER, 300);
	Data_Ticketing.InsertColumn(1, L"发车时间", LVCFMT_CENTER, 200);
	Data_Ticketing.InsertColumn(2, L"始发站", LVCFMT_CENTER, 250);
	Data_Ticketing.InsertColumn(3, L"终点站", LVCFMT_CENTER, 250);
	Data_Ticketing.InsertColumn(4, L"预计用时", LVCFMT_CENTER, 200);
	Data_Ticketing.InsertColumn(5, L"票价", LVCFMT_CENTER, 150);
	Data_Ticketing.InsertColumn(6, L"最大载客数", LVCFMT_CENTER, 250);
	Data_Ticketing.InsertColumn(7, L"已售票数", LVCFMT_CENTER, 200);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void Ticketing::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Ticketing::OnBnClickedButtonCheck()
{
	// TODO: 在此添加控件通知处理程序代
	CButton* pButtonB = (CButton*)GetDlgItem(IDC_BUTTON_Buy);
	pButtonB->EnableWindow(false);

	InfoData data;
	CString stri;

	CString B;
	CEdit* pEditB = (CEdit*)GetDlgItem(IDC_EDIT_Buy);
	pEditB->GetWindowText(B);

	DATALIST_TYPE* pDataList = g_dataFile.GetDatalist();
	Data_Ticketing.DeleteAllItems();

	if (g_dataFile.Find(B))
	{
		pButtonB->EnableWindow(true);
		POSITION posi = g_dataFile.Find(B);
		data = pDataList->GetAt(posi);

		InfoDataCStr datacstr(data);
		Data_Ticketing.InsertItem(0, stri);
		Data_Ticketing.SetItemText(0, 0, datacstr.no);
		Data_Ticketing.SetItemText(0, 1, datacstr.hourMinnute);
		Data_Ticketing.SetItemText(0, 2, datacstr.Starting_station);
		Data_Ticketing.SetItemText(0, 3, datacstr.Last_station);
		Data_Ticketing.SetItemText(0, 4, datacstr.time);
		Data_Ticketing.SetItemText(0, 5, datacstr.fare);
		Data_Ticketing.SetItemText(0, 6, datacstr.maxPas);
		Data_Ticketing.SetItemText(0, 7, datacstr.sold);

		SYSTEMTIME time;
		GetLocalTime(&time);
		CString Operation("TicketingCheck");
		CString Operator("passenger");
		OperationInfoDataCstr opData(data, time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, Operation, Operator);
		op_dataFile.AddOperation(opData);
	}
}


void Ticketing::OnBnClickedButtonBuy()
{
	// TODO: 在此添加控件通知处理程序代码
	SYSTEMTIME time;
	GetLocalTime(&time);

	CString B;
	CEdit* pEditB = (CEdit*)GetDlgItem(IDC_EDIT_Buy);
	pEditB->GetWindowText(B);
	DATALIST_TYPE* pDataList = g_dataFile.GetDatalist();
	POSITION posi = g_dataFile.Find(B);
	InfoData data = pDataList->GetAt(posi);

	int t = (data.hour * 60 + data.minute) - (time.wHour * 60 + time.wMinute);

	if (p_dataFile.Find(B))
		MessageBox(TEXT("已存在该行程！请勿重复购票！"));
	else
	{
		/*CheckoutForTicketing CFTDlg;
		CFTDlg.DoModal();*/
		if (t<=15)
		{
			if (t<= 0)
				MessageBox(TEXT("购票失败！车次已发车！"));
			else
			{
				/*string str;
				str += "购票失败！距该车次发车剩余"; str += t; str += "分钟！";
				MessageBox(TEXT(str));*/
				MessageBox(TEXT("购票失败！距该车次发车剩余不到15分钟"));
			}
		}
		else if(data.sold == data.maxPas)
		{
			MessageBox(TEXT("当前车次无余票"));
		}
		else
		{
			CString Operation("Ticketing");
			CString Operator("passenger");

			p_dataFile.AddInfo(data);

			OperationInfoDataCstr opData(data, time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, Operation, Operator);
			op_dataFile.AddOperation(opData);
			g_dataFile.Addsold(posi);

			MessageBox(TEXT("购票成功！确认以继续..."));
			OnOK();
		}
	}
}


void Ticketing::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SYSTEMTIME time;
	GetLocalTime(&time);
	CString str;
	str.Format(L"%d-%d-%d %d:%d:%d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	GetDlgItem(IDC_STATIC_Time)->SetWindowText(str);
	CDialogEx::OnTimer(nIDEvent);
}


void Ticketing::OnBnClickedButtonCancel2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
