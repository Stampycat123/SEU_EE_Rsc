#pragma once
#include "afxdialogex.h"


// ReturnTicket 对话框

class ReturnTicket : public CDialogEx
{
	DECLARE_DYNAMIC(ReturnTicket)

public:
	ReturnTicket(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ReturnTicket();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ReturnTicket };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl Data_ReturnTicket;
	afx_msg void OnBnClickedButtonCheck();
	afx_msg void OnBnClickedButtonReturn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	UINT_PTR timer;
	afx_msg void OnBnClickedButtonCancel2();
};
