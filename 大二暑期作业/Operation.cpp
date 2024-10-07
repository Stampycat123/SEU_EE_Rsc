// Operation.cpp: 实现文件
//

#include "pch.h"
#include "stManagement.h"
#include "afxdialogex.h"
#include "Operation.h"
#include"busData.h"
#include"OperationData.h"

// Operation 对话框

IMPLEMENT_DYNAMIC(Operation, CDialogEx)

Operation::Operation(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Operation, pParent)
{

}

Operation::~Operation()
{
}

void Operation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Operation, Data_Operation);
}


BEGIN_MESSAGE_MAP(Operation, CDialogEx)
END_MESSAGE_MAP()


// Operation 消息处理程序


BOOL Operation::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	Data_Operation.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	Data_Operation.InsertColumn(0, L"操作时间", LVCFMT_CENTER, 400);
	Data_Operation.InsertColumn(1, L"操作", LVCFMT_CENTER, 400);
	Data_Operation.InsertColumn(2, L"操作人", LVCFMT_CENTER, 250);
	Data_Operation.InsertColumn(3, L"车次号", LVCFMT_CENTER, 300);
	Data_Operation.InsertColumn(4, L"发车时间", LVCFMT_CENTER, 200);
	Data_Operation.InsertColumn(5, L"始发站", LVCFMT_CENTER, 250);
	Data_Operation.InsertColumn(6, L"终点站", LVCFMT_CENTER, 250);
	Data_Operation.InsertColumn(7, L"预计用时", LVCFMT_CENTER, 200);
	Data_Operation.InsertColumn(8, L"票价", LVCFMT_CENTER, 150);
	Data_Operation.InsertColumn(9, L"最大载客数", LVCFMT_CENTER, 250);
	Data_Operation.InsertColumn(10, L"已售票数", LVCFMT_CENTER, 200);

	OperationInfoDataCstr Opdata;
	CString stri;
	int i = 0;

	Data_Operation.DeleteAllItems();
	ODATALIST_TYPE* pOpDataList = op_dataFile.GetDatalist();
	if (!pOpDataList->IsEmpty())
	{
		POSITION posi = pOpDataList->GetHeadPosition();
		Opdata = pOpDataList->GetAt(posi);
		
		while (posi != NULL)
		{
			Opdata = pOpDataList->GetNext(posi);
			InfoDataCStr tempCstr(Opdata.data);
			stri.Format(L"%d", i);
			Data_Operation.InsertItem(i, stri);
			Data_Operation.SetItemText(i, 0, Opdata.time);
			Data_Operation.SetItemText(i, 1, Opdata.Operation);
			Data_Operation.SetItemText(i, 2, Opdata.Operator);
			Data_Operation.SetItemText(i, 3, tempCstr.no);
			Data_Operation.SetItemText(i, 4, tempCstr.hourMinnute);
			Data_Operation.SetItemText(i, 5, tempCstr.Starting_station);
			Data_Operation.SetItemText(i, 6, tempCstr.Last_station);
			Data_Operation.SetItemText(i, 7, tempCstr.time);
			Data_Operation.SetItemText(i, 8, tempCstr.fare);
			Data_Operation.SetItemText(i, 9, tempCstr.maxPas);
			Data_Operation.SetItemText(i, 10, tempCstr.sold);
			i++;
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
