#pragma once
#include "afxdialogex.h"

// Ticketing 对话框

class Ticketing : public CDialogEx
{
	DECLARE_DYNAMIC(Ticketing)

public:
	Ticketing(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Ticketing();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Ticketing };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl Data_Ticketing;
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCheck();
	afx_msg void OnBnClickedButtonBuy();
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	UINT_PTR timer;
	afx_msg void OnBnClickedButtonCancel2();
};
//extern CString B;