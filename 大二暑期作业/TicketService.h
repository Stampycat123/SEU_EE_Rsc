#pragma once
#include "afxdialogex.h"


// TicketService 对话框

class TicketService : public CDialogEx
{
	DECLARE_DYNAMIC(TicketService)

public:
	TicketService(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~TicketService();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TicketService };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	UINT_PTR timer;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonHome();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonTocheckbusinfo();
	afx_msg void OnBnClickedButtonToticketing();
	afx_msg void OnBnClickedButtonToreturnticket();
	afx_msg void OnBnClickedButtonToexistedbusinfo();
};
