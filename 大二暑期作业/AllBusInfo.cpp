// AllBusInfo.cpp: 实现文件
//

#include "pch.h"
#include "stManagement.h"
#include "afxdialogex.h"
#include "AllBusInfo.h"
#include"BusData.h"


// AllBusInfo 对话框

IMPLEMENT_DYNAMIC(AllBusInfo, CDialogEx)

AllBusInfo::AllBusInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_AllBusInfo, pParent)
{

}

AllBusInfo::~AllBusInfo()
{
}

void AllBusInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_AllBusInfo, Data_AllBusInfo);
}


BEGIN_MESSAGE_MAP(AllBusInfo, CDialogEx)
END_MESSAGE_MAP()


// AllBusInfo 消息处理程序


BOOL AllBusInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//g_dataFile.Read();
	InfoData data;
	CString stri;
	int i = 0;

	Data_AllBusInfo.DeleteAllItems();
	DATALIST_TYPE* pDataList = g_dataFile.GetDatalist();
	if(!pDataList->IsEmpty())
	{
		POSITION posi = pDataList->GetHeadPosition();
		data = pDataList->GetAt(posi);

		//表头
		Data_AllBusInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		Data_AllBusInfo.InsertColumn(0, L"车次号", LVCFMT_CENTER, 300);
		Data_AllBusInfo.InsertColumn(1, L"发车时间", LVCFMT_CENTER, 200);
		Data_AllBusInfo.InsertColumn(2, L"始发站", LVCFMT_CENTER, 250);
		Data_AllBusInfo.InsertColumn(3, L"终点站", LVCFMT_CENTER, 250);
		Data_AllBusInfo.InsertColumn(4, L"预计用时", LVCFMT_CENTER, 200);
		Data_AllBusInfo.InsertColumn(5, L"票价", LVCFMT_CENTER, 150);
		Data_AllBusInfo.InsertColumn(6, L"最大载客数", LVCFMT_CENTER, 250);
		Data_AllBusInfo.InsertColumn(7, L"已售票数", LVCFMT_CENTER, 200);
		/*for (int i=0; posi; data=pDataList->GetNext(posi),i++)
		{
			Data_AllBusInfo.SetItemText(i, 0, data.no);
			Data_AllBusInfo.SetItemText(i, 1, data.hourMinnute);
			Data_AllBusInfo.SetItemText(i, 2, data.Starting_station);
			Data_AllBusInfo.SetItemText(i, 3, data.Last_station);
			Data_AllBusInfo.SetItemText(i, 4, data.time);
			Data_AllBusInfo.SetItemText(i, 5, data.fare);
			Data_AllBusInfo.SetItemText(i, 6, data.maxPas);
			Data_AllBusInfo.SetItemText(i, 7, data.sold);
		}*/
		//for (; posi!=NULL; data = pDataList->GetNext(posi), i++)
		while(posi != NULL)
		{
			data = pDataList->GetNext(posi);
			InfoDataCStr datacstr(data);
			stri.Format(L"%d", i);
			Data_AllBusInfo.InsertItem(i, stri);
			Data_AllBusInfo.SetItemText(i, 0, datacstr.no);
			Data_AllBusInfo.SetItemText(i, 1, datacstr.hourMinnute);
			Data_AllBusInfo.SetItemText(i, 2, datacstr.Starting_station);
			Data_AllBusInfo.SetItemText(i, 3, datacstr.Last_station);
			Data_AllBusInfo.SetItemText(i, 4, datacstr.time);
			Data_AllBusInfo.SetItemText(i, 5, datacstr.fare);
			Data_AllBusInfo.SetItemText(i, 6, datacstr.maxPas);
			Data_AllBusInfo.SetItemText(i, 7, datacstr.sold);
			i++;
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
