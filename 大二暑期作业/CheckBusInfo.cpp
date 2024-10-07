// CheckBusInfo.cpp: 实现文件
//

#include "pch.h"
#include "stManagement.h"
#include "afxdialogex.h"
#include "CheckBusInfo.h"
#include"BusData.h"
#include"OperationData.h"

// CheckBusInfo 对话框

IMPLEMENT_DYNAMIC(CheckBusInfo, CDialogEx)

CheckBusInfo::CheckBusInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CheckBusInfo, pParent)
{
	
}

CheckBusInfo::~CheckBusInfo()
{
}

void CheckBusInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_LIST1, Data_CheckBusInfo);
	DDX_Control(pDX, IDC_LIST_CheckBusInfo, Data_CheckBusInfo);
}


BEGIN_MESSAGE_MAP(CheckBusInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Ok, &CheckBusInfo::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_Check, &CheckBusInfo::OnBnClickedButtonCheck)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_Cancel2, &CheckBusInfo::OnBnClickedButtonCancel2)
END_MESSAGE_MAP()


// CheckBusInfo 消息处理程序


BOOL CheckBusInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	timer = SetTimer(1, 100, NULL);

	Data_CheckBusInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	Data_CheckBusInfo.InsertColumn(0, L"车次号", LVCFMT_CENTER, 300);
	Data_CheckBusInfo.InsertColumn(1, L"发车时间", LVCFMT_CENTER, 200);
	Data_CheckBusInfo.InsertColumn(2, L"始发站", LVCFMT_CENTER, 250);
	Data_CheckBusInfo.InsertColumn(3, L"终点站", LVCFMT_CENTER, 250);
	Data_CheckBusInfo.InsertColumn(4, L"预计用时", LVCFMT_CENTER, 200);
	Data_CheckBusInfo.InsertColumn(5, L"票价", LVCFMT_CENTER, 150);
	Data_CheckBusInfo.InsertColumn(6, L"最大载客数", LVCFMT_CENTER, 250);
	Data_CheckBusInfo.InsertColumn(7, L"已售票数", LVCFMT_CENTER, 200);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CheckBusInfo::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码
	/*POSITION posi = Data_CheckBusInfo.GetFirstSelectedItemPosition();
	int nSelItem = Data_CheckBusInfo.GetNextSelectedItem(posi);

	if (nSelItem >= 0)
	{
		InfoData data;
		Data_CheckBusInfo.GetItemText(n)
	}*/
	CDialogEx::OnOK();
}


void CheckBusInfo::OnBnClickedButtonCheck()
{
	// TODO: 在此添加控件通知处理程序代码

	InfoData data;
	CString stri;

	CString CBI;
	CEdit* pEditCBI = (CEdit*)GetDlgItem(IDC_EDIT_CBI);
	pEditCBI->GetWindowText(CBI);

	DATALIST_TYPE* pDataList = g_dataFile.GetDatalist();
	Data_CheckBusInfo.DeleteAllItems();
	////表头
	//Data_CheckBusInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//Data_CheckBusInfo.InsertColumn(0, L"车次号", LVCFMT_CENTER, 300);
	//Data_CheckBusInfo.InsertColumn(1, L"发车时间", LVCFMT_CENTER, 200);
	//Data_CheckBusInfo.InsertColumn(2, L"始发站", LVCFMT_CENTER, 250);
	//Data_CheckBusInfo.InsertColumn(3, L"终点站", LVCFMT_CENTER, 250);
	//Data_CheckBusInfo.InsertColumn(4, L"预计用时", LVCFMT_CENTER, 200);
	//Data_CheckBusInfo.InsertColumn(5, L"票价", LVCFMT_CENTER, 150);
	//Data_CheckBusInfo.InsertColumn(6, L"最大载客数", LVCFMT_CENTER, 250);
	//Data_CheckBusInfo.InsertColumn(7, L"已售票数", LVCFMT_CENTER, 200);

	/*if (g_dataFile.Find(CBI))
	{
		POSITION posi = g_dataFile.Find(CBI);
		data = pDataList->GetAt(posi);

		InfoDataCStr datacstr(data);
		Data_CheckBusInfo.InsertItem(0, stri);
		Data_CheckBusInfo.SetItemText(0, 0, datacstr.no);
		Data_CheckBusInfo.SetItemText(0, 1, datacstr.hourMinnute);
		Data_CheckBusInfo.SetItemText(0, 2, datacstr.Starting_station);
		Data_CheckBusInfo.SetItemText(0, 3, datacstr.Last_station);
		Data_CheckBusInfo.SetItemText(0, 4, datacstr.time);
		Data_CheckBusInfo.SetItemText(0, 5, datacstr.fare);
		Data_CheckBusInfo.SetItemText(0, 6, datacstr.maxPas);
		Data_CheckBusInfo.SetItemText(0, 7, datacstr.sold);
	}*/
	//else

	POSITION* storage = new POSITION[10];

	if (g_dataFile.FindTrue(CBI))
	{
		int count = g_dataFile.Find(CBI, storage);
		for (int i = 0; i < count; i++)
		{
			InfoData temp = pDataList->GetAt(storage[i]);

			InfoDataCStr datacstr(temp);
			stri.Format(L"%d", i);
			Data_CheckBusInfo.InsertItem(i, stri);
			Data_CheckBusInfo.SetItemText(i, 0, datacstr.no);
			Data_CheckBusInfo.SetItemText(i, 1, datacstr.hourMinnute);
			Data_CheckBusInfo.SetItemText(i, 2, datacstr.Starting_station);
			Data_CheckBusInfo.SetItemText(i, 3, datacstr.Last_station);
			Data_CheckBusInfo.SetItemText(i, 4, datacstr.time);
			Data_CheckBusInfo.SetItemText(i, 5, datacstr.fare);
			Data_CheckBusInfo.SetItemText(i, 6, datacstr.maxPas);
			Data_CheckBusInfo.SetItemText(i, 7, datacstr.sold);

		}
	}
	delete[] storage;
}


void CheckBusInfo::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SYSTEMTIME time;
	GetLocalTime(&time);
	CString str;
	str.Format(L"%d-%d-%d %d:%d:%d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	GetDlgItem(IDC_STATIC_Time)->SetWindowText(str);

	CDialogEx::OnTimer(nIDEvent);
}


void CheckBusInfo::OnBnClickedButtonCancel2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
