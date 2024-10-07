// DelBus.cpp: 实现文件
//

#include "pch.h"
#include "stManagement.h"
#include "afxdialogex.h"
#include "DelBus.h"
#include"BusData.h"
#include"PassengerData.h"
#include"OperationData.h"

// DelBus 对话框

IMPLEMENT_DYNAMIC(DelBus, CDialogEx)

DelBus::DelBus(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DelBus, pParent)
{

}

DelBus::~DelBus()
{
}

void DelBus::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DelBus, Data_DelBus);
}


BEGIN_MESSAGE_MAP(DelBus, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Ok, &DelBus::OnBnClickedButtonOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_Cancel2, &DelBus::OnBnClickedButtonCancel2)
	ON_BN_CLICKED(IDC_BUTTON_Check, &DelBus::OnBnClickedButtonCheck)
	ON_BN_CLICKED(IDC_BUTTON_Del, &DelBus::OnBnClickedButtonDel)
END_MESSAGE_MAP()


// DelBus 消息处理程序


BOOL DelBus::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	timer = SetTimer(1, 100, NULL);
	CButton* pButtonD = (CButton*)GetDlgItem(IDC_BUTTON_Del);
	pButtonD->EnableWindow(false);

	Data_DelBus.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	Data_DelBus.InsertColumn(0, L"车次号", LVCFMT_CENTER, 300);
	Data_DelBus.InsertColumn(1, L"发车时间", LVCFMT_CENTER, 200);
	Data_DelBus.InsertColumn(2, L"始发站", LVCFMT_CENTER, 250);
	Data_DelBus.InsertColumn(3, L"终点站", LVCFMT_CENTER, 250);
	Data_DelBus.InsertColumn(4, L"预计用时", LVCFMT_CENTER, 200);
	Data_DelBus.InsertColumn(5, L"票价", LVCFMT_CENTER, 150);
	Data_DelBus.InsertColumn(6, L"最大载客数", LVCFMT_CENTER, 250);
	Data_DelBus.InsertColumn(7, L"已售票数", LVCFMT_CENTER, 200);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void DelBus::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void DelBus::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SYSTEMTIME time;
	GetLocalTime(&time);
	CString str;
	str.Format(L"%d-%d-%d %d:%d:%d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	GetDlgItem(IDC_STATIC_Time)->SetWindowText(str);

	CDialogEx::OnTimer(nIDEvent);

}


void DelBus::OnBnClickedButtonCancel2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void DelBus::OnBnClickedButtonCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pButtonD = (CButton*)GetDlgItem(IDC_BUTTON_Del);
	pButtonD->EnableWindow(false);

	InfoData data;
	CString stri;

	CString DB;
	CEdit* pEditDB = (CEdit*)GetDlgItem(IDC_EDIT_DB);
	pEditDB->GetWindowText(DB);

	DATALIST_TYPE* pDataList = g_dataFile.GetDatalist();
	Data_DelBus.DeleteAllItems();

	if (g_dataFile.Find(DB))
	{
		pButtonD->EnableWindow(true);

		POSITION posi = g_dataFile.Find(DB);
		data = pDataList->GetAt(posi);

		InfoDataCStr datacstr(data);
		Data_DelBus.InsertItem(0, stri);
		Data_DelBus.SetItemText(0, 0, datacstr.no);
		Data_DelBus.SetItemText(0, 1, datacstr.hourMinnute);
		Data_DelBus.SetItemText(0, 2, datacstr.Starting_station);
		Data_DelBus.SetItemText(0, 3, datacstr.Last_station);
		Data_DelBus.SetItemText(0, 4, datacstr.time);
		Data_DelBus.SetItemText(0, 5, datacstr.fare);
		Data_DelBus.SetItemText(0, 6, datacstr.maxPas);
		Data_DelBus.SetItemText(0, 7, datacstr.sold);

		SYSTEMTIME time;
		GetLocalTime(&time);
		CString Operation("DelBusCheck");
		CString Operator("admin");
		OperationInfoDataCstr opData(data, time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, Operation, Operator);
		op_dataFile.AddOperation(opData);
	}
}


void DelBus::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	CString DB;
	CEdit* pEditDB = (CEdit*)GetDlgItem(IDC_EDIT_DB);
	pEditDB->GetWindowText(DB);
	if (g_dataFile.Find(DB))
	{
		POSITION posi = g_dataFile.Find(DB);
		DATALIST_TYPE* pDataList = g_dataFile.GetDatalist();
		InfoData data = pDataList->GetAt(posi);
		SYSTEMTIME time;
		GetLocalTime(&time);
		CString Operation("DelBus");
		CString Operator("admin");

		g_dataFile.DelInfo(DB);
		p_dataFile.DelInfo(DB);

		OperationInfoDataCstr opData(data, time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, Operation, Operator);
		op_dataFile.AddOperation(opData);

		MessageBox(TEXT("注销成功！确认以继续..."));
		OnOK();
	}
	else
	{
		MessageBox(TEXT("车次不存在！"));
	}

	CDialogEx::OnOK();
}
