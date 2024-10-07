#pragma once
#include "afxdialogex.h"


// AddBusInfo 对话框

class AddBusInfo : public CDialogEx
{
	DECLARE_DYNAMIC(AddBusInfo)

public:
	AddBusInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AddBusInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AddBusInfo };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	CString addData[9];

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	UINT_PTR timer;
};
