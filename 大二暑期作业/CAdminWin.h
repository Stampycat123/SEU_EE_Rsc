#pragma once
#include "afxdialogex.h"


// CAdminWin 对话框

class CAdminWinDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdminWinDlg)

public:
	CAdminWinDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAdminWinDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AdminWin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	// 管理员账号
	CString Admin_name;
	// 管理员密码
	CString Admin_password;
public:
	afx_msg void OnEnChangeEdit1();
};
