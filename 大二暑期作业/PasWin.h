#pragma once
#include "afxdialogex.h"


// PasWin 对话框

class PasWin : public CDialogEx
{
	DECLARE_DYNAMIC(PasWin)

public:
	PasWin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PasWin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PasWin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	UINT_PTR timer;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonHome();
	afx_msg void OnBnClickedButtonTocheckbusinfo();
	afx_msg void OnBnClickedButtonToticketservice();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
