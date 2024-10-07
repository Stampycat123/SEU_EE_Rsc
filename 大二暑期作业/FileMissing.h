#pragma once
#include "afxdialogex.h"


// FileMissing 对话框

class FileMissing : public CDialogEx
{
	DECLARE_DYNAMIC(FileMissing)

public:
	FileMissing(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~FileMissing();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FileMissing };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
