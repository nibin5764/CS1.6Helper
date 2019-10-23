
// CSHelperDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CSHelper.h"
#include "CSHelperDlg.h"
#include "Utility.h"
#include "MemoryOperate.h"
#include "Err.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 快捷键注册消息
#define		MHK_F10		0x1001
#define		MHK_F11		0x1002



//定时器消息
#define		CONNECT_PROCESS		0x2000	
#define		TIMER_LOCK_HEALTH	0x2001

//定时器触发时间

#define		ELAPSE_TIMER_500MS	500
#define		ELAPSE_TIMER_200MS	200
#define		ELAPSE_TIMER_100MS	100
#define		ELAPSE_TIMER_NOMAL	ELAPSE_TIMER_500MS


CCSHelperDlg::CCSHelperDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCSHelperDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	IsLockHealth = FALSE;
}

void CCSHelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCSHelperDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_MESSAGE(WM_HOTKEY,OnHotKey)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_LOCK_HEALTH, &CCSHelperDlg::OnBnClickedBtnLockHealth)
END_MESSAGE_MAP()


// CCSHelperDlg 消息处理程序

BOOL CCSHelperDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	BOOL RegSuccess = TRUE;
// 	RegSuccess = RegisterHotKey(this->GetSafeHwnd(),MHK_F10,0,VK_F10);
// 	ASSERT_EQUAL_REG(RegSuccess,FALSE);
// 	RegSuccess =  RegisterHotKey(this->GetSafeHwnd(),MHK_F11,0,VK_F11);
// 	ASSERT_EQUAL_REG(RegSuccess,FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCSHelperDlg::OnPaint()
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
HCURSOR CCSHelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCSHelperDlg::OnBnClickedBtnLockHealth()
{
	if(!IsLockHealth){	//如果功能未开启
		SetTimer(TIMER_LOCK_HEALTH,ELAPSE_TIMER_NOMAL,NULL);
	}
	else{
		KillTimer(TIMER_LOCK_HEALTH);
	}
	return ;
}
int CCSHelperDlg::func_LockHealth(){
	list<DWORD> mlist;
	mlist.push_front(0x160);

	BYTE beHealth[4] = {0,0,0,255};
	ULONG WrittenLen = 0;
	int rv = 0;
	rv = mem_WriteBlock(proHandle,0,mlist,4,beHealth,&WrittenLen);
	if( rv != HELPER_ERROR_SUCCESS){
		return rv;
	}
	return 0;
}
void CCSHelperDlg::OnOk(){
}
void CCSHelperDlg::OnCancel(){
	DWORD rtn;
	rtn = MessageBox("确定要退出吗",NULL,MB_OKCANCEL|MB_ICONQUESTION);
	if(rtn == IDCANCEL){
		return;
	}
	else if( rtn == IDOK){
		CDialog::OnCancel();
	}
}
LONG CCSHelperDlg::OnHotKey(WPARAM wPARAM, LPARAM lPARAM){
	

	switch(wPARAM){
		case MHK_F10: 
			MessageBox("F10",NULL,MB_OK);
			break;
		case MHK_F11:
			MessageBox("F11",NULL,MB_OK);
			break;
	}
	return 0;
}

void CCSHelperDlg::OnTimer(UINT_PTR nIDEvent){
	switch (nIDEvent){
		case TIMER_LOCK_HEALTH:
			func_LockHealth();
			break;
		default:
			break;
	}

	return;
}