#pragma once
#include "afxdialogex.h"


// AllBusInfo 对话框

class AllBusInfo : public CDialogEx
{
	DECLARE_DYNAMIC(AllBusInfo)

public:
	AllBusInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AllBusInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AllBusInfo };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	CListCtrl Data_AllBusInfo;
};
