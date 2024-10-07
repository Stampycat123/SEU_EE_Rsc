// ExistedBusInfo.cpp: 实现文件
//

#include "pch.h"
#include "stManagement.h"
#include "afxdialogex.h"
#include "ExistedBusInfo.h"
#include"PassengerData.h"


// ExistedBusInfo 对话框

IMPLEMENT_DYNAMIC(ExistedBusInfo, CDialogEx)

ExistedBusInfo::ExistedBusInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ExistedBusInfo, pParent)
{

}

ExistedBusInfo::~ExistedBusInfo()
{
}

void ExistedBusInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ExistedBusInfo, Data_ExistedBusInfo);
}


BEGIN_MESSAGE_MAP(ExistedBusInfo, CDialogEx)
END_MESSAGE_MAP()


// ExistedBusInfo 消息处理程序


BOOL ExistedBusInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InfoData data;
	CString stri;
	int i = 0;

	Data_ExistedBusInfo.DeleteAllItems();
	DATALIST_TYPE* pDataList = p_dataFile.GetDatalist();
	if (!pDataList->IsEmpty())
	{
		POSITION posi = pDataList->GetHeadPosition();
		data = pDataList->GetAt(posi);

		//表头
		Data_ExistedBusInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		Data_ExistedBusInfo.InsertColumn(0, L"车次号", LVCFMT_CENTER, 300);
		Data_ExistedBusInfo.InsertColumn(1, L"发车时间", LVCFMT_CENTER, 200);
		Data_ExistedBusInfo.InsertColumn(2, L"始发站", LVCFMT_CENTER, 250);
		Data_ExistedBusInfo.InsertColumn(3, L"终点站", LVCFMT_CENTER, 250);
		Data_ExistedBusInfo.InsertColumn(4, L"预计用时", LVCFMT_CENTER, 200);
		Data_ExistedBusInfo.InsertColumn(5, L"票价", LVCFMT_CENTER, 150);
		Data_ExistedBusInfo.InsertColumn(6, L"最大载客数", LVCFMT_CENTER, 250);
		Data_ExistedBusInfo.InsertColumn(7, L"已售票数", LVCFMT_CENTER, 200);
		while (posi != NULL)
		{
			data = pDataList->GetNext(posi);
			InfoDataCStr datacstr(data);
			stri.Format(L"%d", i);
			Data_ExistedBusInfo.InsertItem(i, stri);
			Data_ExistedBusInfo.SetItemText(i, 0, datacstr.no);
			Data_ExistedBusInfo.SetItemText(i, 1, datacstr.hourMinnute);
			Data_ExistedBusInfo.SetItemText(i, 2, datacstr.Starting_station);
			Data_ExistedBusInfo.SetItemText(i, 3, datacstr.Last_station);
			Data_ExistedBusInfo.SetItemText(i, 4, datacstr.time);
			Data_ExistedBusInfo.SetItemText(i, 5, datacstr.fare);
			Data_ExistedBusInfo.SetItemText(i, 6, datacstr.maxPas);
			Data_ExistedBusInfo.SetItemText(i, 7, datacstr.sold);
			i++;
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
