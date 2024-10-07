#pragma once
#include "afxdialogex.h"


// ExistedBusInfo 对话框

class ExistedBusInfo : public CDialogEx
{
	DECLARE_DYNAMIC(ExistedBusInfo)

public:
	ExistedBusInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ExistedBusInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ExistedBusInfo };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl Data_ExistedBusInfo;
};
