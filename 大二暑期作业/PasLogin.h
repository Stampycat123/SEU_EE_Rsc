#pragma once
#include "afxdialogex.h"


// PasLogin 对话框

class PasLogin : public CDialogEx
{
	DECLARE_DYNAMIC(PasLogin)

public:
	PasLogin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PasLogin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PasLogin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	UINT_PTR timer;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBacktopaswin();
	afx_msg void OnBnClickedButtonNextsteptoticketservice();
	CString PasName;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
