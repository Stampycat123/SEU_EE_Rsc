#pragma once
#include "afxdialogex.h"


// CheckoutForTicketing 对话框

class CheckoutForTicketing : public CDialogEx
{
	DECLARE_DYNAMIC(CheckoutForTicketing)

public:
	CheckoutForTicketing(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CheckoutForTicketing();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CheckoutForTicketing };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
