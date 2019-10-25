
// HelperTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HelperTest.h"
#include "HelperTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHelperTestDlg 对话框

#define		MTIMER_1	WM_USER +100



CHelperTestDlg::CHelperTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHelperTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	ival = 100;
}

void CHelperTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHelperTestDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CHelperTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CHelperTestDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CHelperTestDlg 消息处理程序

BOOL CHelperTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHelperTestDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHelperTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CHelperTestDlg::OnBnClickedButton1()
{
	SetTimer(MTIMER_1,1000,NULL);
}


void CHelperTestDlg::OnBnClickedButton2()
{
	KillTimer(MTIMER_1);
}

void CHelperTestDlg::SetValue(){
	ival +=2;
	CString strVal;
	strVal.Format("%d",ival);
	GetDlgItem(IDC_EDIT1)->SetWindowText(strVal);
	GetDlgItem(IDC_STATIC)->SetWindowText(strVal);
}
void CHelperTestDlg::OnTimer(UINT_PTR nIDEvent){
	switch (nIDEvent){
		case MTIMER_1:
			SetValue();
			break;
		default:
			break;
	}

	return;
}