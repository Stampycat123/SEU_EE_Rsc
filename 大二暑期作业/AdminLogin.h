#pragma once
#include "afxdialogex.h"


// AdminLogin 对话框

class AdminLogin : public CDialogEx
{
	DECLARE_DYNAMIC(AdminLogin)

public:
	AdminLogin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AdminLogin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AdminLogin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	UINT_PTR timer;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonNextsteptoadminwin();
	afx_msg void OnBnClickedButtonHome();
	CString AdminName;
	CString AdminPW;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
