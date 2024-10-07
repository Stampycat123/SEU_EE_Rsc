#pragma once
#include "afxdialogex.h"


// AdminWin 对话框

class AdminWin : public CDialogEx
{
	DECLARE_DYNAMIC(AdminWin)

public:
	AdminWin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AdminWin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AdminWin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	UINT_PTR timer;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonToaddbusinfo();
	afx_msg void OnBnClickedButtonHome();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonToallbusinfo();
	afx_msg void OnBnClickedButtonTocheckbusinfo();
	afx_msg void OnBnClickedButtonTodelbus();
};
