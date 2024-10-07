#pragma once
#include "afxdialogex.h"


// DelBus 对话框

class DelBus : public CDialogEx
{
	DECLARE_DYNAMIC(DelBus)

public:
	DelBus(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DelBus();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DelBus };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	CListCtrl Data_DelBus;
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	UINT_PTR timer;
	afx_msg void OnBnClickedButtonCancel2();
	afx_msg void OnBnClickedButtonCheck();
	afx_msg void OnBnClickedButtonDel();
};
