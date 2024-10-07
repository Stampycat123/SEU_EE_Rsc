#pragma once
#include "afxdialogex.h"


// CheckBusInfo 对话框

class CheckBusInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CheckBusInfo)

public:
	CheckBusInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CheckBusInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CheckBusInfo };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	CListCtrl Data_CheckBusInfo;
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCheck();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	UINT_PTR timer;
	afx_msg void OnBnClickedButtonCancel2();
};
