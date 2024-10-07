#pragma once
#include "afxdialogex.h"


// Operation 对话框

class Operation : public CDialogEx
{
	DECLARE_DYNAMIC(Operation)

public:
	Operation(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Operation();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Operation };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl Data_Operation;
};
