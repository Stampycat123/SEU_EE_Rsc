#pragma once
#include "afxdialogex.h"


// Guide 对话框

class Guide : public CDialogEx
{
	DECLARE_DYNAMIC(Guide)

public:
	Guide(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Guide();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Guide };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
