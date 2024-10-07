
// stManagementDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "stManagement.h"
#include "stManagementDlg.h"
#include "afxdialogex.h"
#include "AdminLogin.h"
#include "PasWin.h"
#include "Guide.h"
#include"BusData.h"
#include"PassengerData.h"
#include"Operation.h"
#include"OperationData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

CString g_name("hczcpgl.txt");
BusData g_dataFile(g_name);
CString p_name("pas.txt");
PassengerData p_dataFile(p_name);
int c = 0;
OperationData op_dataFile(c);
//extern UINT_PTR Ttimer;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	UINT_PTR timer;
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CstManagementDlg 对话框



CstManagementDlg::CstManagementDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STMANAGEMENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CstManagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CstManagementDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ToAdminLogin, &CstManagementDlg::OnBnClickedButtonToadminlogin)
	ON_BN_CLICKED(IDC_BUTTON_ToPasWin, &CstManagementDlg::OnBnClickedButtonTopaswin)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_ToGuide, &CstManagementDlg::OnBnClickedButtonToguide)
	ON_BN_CLICKED(IDC_BUTTON_Operation, &CstManagementDlg::OnBnClickedButtonOperation)
END_MESSAGE_MAP()


// CstManagementDlg 消息处理程序

BOOL CstManagementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	timer = SetTimer(1, 100, NULL);
	//Ttimer = SetTimer(1, 100, NULL);

	g_dataFile.WriteExample();
	g_dataFile.Read();
	p_dataFile.WriteExample();
	p_dataFile.Read();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CstManagementDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CstManagementDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CstManagementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CstManagementDlg::OnBnClickedButtonToadminlogin()
{
	// TODO: 在此添加控件通知处理程序代码
	AdminLogin AdminLoginDlg;
	AdminLoginDlg.DoModal();
}


void CstManagementDlg::OnBnClickedButtonTopaswin()
{
	// TODO: 在此添加控件通知处理程序代码
	PasWin PasWinDlg;
	PasWinDlg.DoModal();
}

//string timeFormat(int t)
//{
//	char c = '0' + t;
//	if (t >= 0 && t < 60)
//	{
//		if (t < 10)
//			string str=""
//		else
//			str = c;
//	}
//	else
//		str = "时间信息错误！";
//	return str;
//}

void CstManagementDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SYSTEMTIME time;
	GetLocalTime(&time);
	CString str;
	
	str.Format(L"%d-%d-%d %d:%d:%d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	GetDlgItem(IDC_STATIC_Time)->SetWindowText(str);

	CDialogEx::OnTimer(nIDEvent);
}


void CstManagementDlg::OnBnClickedButtonToguide()
{
	// TODO: 在此添加控件通知处理程序代码
	Guide GDlg;
	GDlg.DoModal();
}


void CstManagementDlg::OnBnClickedButtonOperation()
{
	// TODO: 在此添加控件通知处理程序代码
	Operation ODlg;
	ODlg.DoModal();
}
