#pragma once
#include "afxdialogex.h"


// CheckoutForReturnTicket 对话框

class CheckoutForReturnTicket : public CDialogEx
{
	DECLARE_DYNAMIC(CheckoutForReturnTicket)

public:
	CheckoutForReturnTicket(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CheckoutForReturnTicket();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CheckoutForReturnTicket };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
