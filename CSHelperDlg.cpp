
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
#define		TIMER_CONNECT_PROCESS		0x2000	
#define		TIMER_LOCK_HEALTH			0x2001

//定时器触发时间

#define		ELAPSE_TIMER_5000MS 5000
#define		ELAPSE_TIMER_1000MS 1000
#define		ELAPSE_TIMER_500MS	500
#define		ELAPSE_TIMER_200MS	200
#define		ELAPSE_TIMER_100MS	100
#define		ELAPSE_TIMER_NOMAL	ELAPSE_TIMER_5000MS


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
	ON_BN_CLICKED(IDC_BTN_START, &CCSHelperDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_INJECT_TEST, &CCSHelperDlg::OnBnClickedBtnInjectTest)
	ON_BN_CLICKED(IDC_BTN_INJECT_CANCLE, &CCSHelperDlg::OnBnClickedBtnInjectCancle)
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
	
	
	
	if (!mem_SetPrivilege(SE_DEBUG_NAME, TRUE)){
		return 1;
	}
		
	OnBnClickedBtnStart();
	
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
		IsLockHealth = TRUE;
		GetDlgItem(IDC_BTN_LOCK_HEALTH)->SetWindowText("功能已开启");
		SetTimer(TIMER_LOCK_HEALTH,ELAPSE_TIMER_NOMAL,NULL);
	}
	else{
		IsLockHealth = FALSE;
		GetDlgItem(IDC_BTN_LOCK_HEALTH)->SetWindowText("功能已关闭");
		KillTimer(TIMER_LOCK_HEALTH);
	}
	return ;
}


int CCSHelperDlg::func_LockHealth(){
// 	list<DWORD> mlist;
// 	mlist.push_front(0x160);
// 
// 	BYTE beHealth[4] = {0,0,0,255};
// 	ULONG WrittenLen = 0;
// 	int rv = 0;
// 	rv = mem_WriteBlock(proHandle,0,mlist,4,beHealth,&WrittenLen);
// 	if( rv != HELPER_ERROR_SUCCESS){
// 		return rv;
// 	}
	int rv;
// 	list<DWORD> mlist;
// 	mlist.push_back(0x1651A0);
// 	mlist.push_back(0x78);
	BYTE ReadBuffer[10] = {0};
	ULONG ReadddLen = sizeof(ReadBuffer);
// 	rv = mem_ReadBlock(proHandle,baseAddr,mlist,4,ReadBuffer,&ReadddLen);
// 	if(rv != 0){
// 		return rv;
// 	}

	int Result = 0;
	//memcpy((void*)&Result,ReadBuffer,4);


	Result = 1000;
	memcpy(ReadBuffer,(void*)&Result,4);
	list<DWORD> wlist;
	wlist.push_back(0x1651A0);
	wlist.push_back(0x78);
	rv = mem_WriteBlock(hProcess,baseAddr,wlist,4,ReadBuffer,&ReadddLen);
	if(rv != 0){
		return rv;
	}
	return 0;
}


int CCSHelperDlg::func_ConnectPro(){
	//获取目标进程窗口句柄
	hWindow = FindWindow("#32770", "HelperTest")->GetSafeHwnd();
	ASSERT_HANDLE_NULL(hWindow);
	
	//获取进程pid
	GetWindowThreadProcessId(hWindow, &pid);
	ASSERT_HANDLE_NULL(pid);

	//获取进程句柄
	hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid);
	ASSERT_HANDLE_NULL(hProcess);


	//获取进程首地址
	int rv = mem_GetProcessAddr(pid,baseAddr);
	if(rv != 0){
		return rv ;
	}
	KillTimer(TIMER_CONNECT_PROCESS);
	MessageBox("连接目标进程成功！",NULL,MB_OK);
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
		case TIMER_CONNECT_PROCESS:
			func_ConnectPro();
			break;

		default:
			break;
	}

	return;
}
void CCSHelperDlg::OnBnClickedBtnStart()
{
	SetTimer(TIMER_CONNECT_PROCESS,ELAPSE_TIMER_500MS,NULL);
}

void InjFunc(){  
	_asm{
		add dword ptr[esi+0x78],05
		add dword ptr[esi+0x78],04
	}
}


void CCSHelperDlg::OnBnClickedBtnInjectTest()
{
	//   1.申请空间   2.新空间注入代码  3.原位置注入跳转代码

	//保存初始机器码
	//此处有9个字节两个指令，因为第一条指令只有4个字节，而跳转指令需要5个字节，所以这里占用两个指令的位置，后面在新地址中将要返回的时候要把此处的第二条指令拼接上
	list<DWORD> mlist;
	DWORD OldAddr = 0x1332;
	mlist.push_back(OldAddr);
	BYTE OldCode[10] = {0};
	ULONG ReadddLen = sizeof(OldCode);
	int rv = mem_ReadBlock(hProcess,baseAddr,mlist,9,OldCode,&ReadddLen);		
	if(rv != 0){
		return;
	}

	//申请虚拟地址空间
	LPVOID virAddr = NULL;
	if (!(virAddr = VirtualAllocEx(hProcess,NULL,64,MEM_COMMIT, PAGE_EXECUTE_READWRITE))){
		CString ErrMsg;
		ErrMsg.Format("VirtualAllocEx() failed :err_code=%d/n", GetLastError());
		MessageBox(ErrMsg,NULL,MB_OK);
		return ;
	}

	//虚拟地址空间内写入新的机器码
	BYTE NewCode[128];
	memcpy(NewCode,(void*)((char*)InjFunc+3),8);
	//memset(NewCode,0x90,8);
	
	//计算新的偏移
	int oldOffset,newOffset;
	BytesToInt(OldCode+5,oldOffset);
	newOffset = baseAddr + OldAddr + 9  + oldOffset - (DWORD)virAddr - 13;
	BYTE bnewOffset[4];
	IntTo4Bytes(newOffset,bnewOffset);
	memcpy(NewCode+8,OldCode + 4,1);
	memcpy(NewCode+9,bnewOffset,4);
	//将原来的第二条指令放在操作之后

	DWORD returnAddr = baseAddr + OldAddr +9;	
	DWORD returnOffset = returnAddr - (DWORD)virAddr -18 ;
	BYTE  ByteReturnAddr[4];
	IntTo4Bytes(returnOffset,ByteReturnAddr);
	NewCode[13] = 0xE9;
	memcpy(NewCode+14,ByteReturnAddr,4);


	//8个字节汇编操作码，5个字节是复原跳转前的指令，5个字节跳转回去，一共18个字节
	if (!(WriteProcessMemory(hProcess, virAddr, (LPVOID)((char*)NewCode), 18, NULL))){
		printf("Write ThreadProc to Memory failed :err_code=%d/n", GetLastError());
		return ;
	}

	//把原来的指令改成 跳转指令 跳转地址为virAddr
	DWORD jmpOffset = (DWORD)virAddr - (baseAddr +0x1332 +5);
	BYTE ByteOffset[4];
	IntTo4Bytes(jmpOffset,ByteOffset);
	BYTE JmpToNewCode[9] = {0};
	JmpToNewCode[0] = 0xE9;			//jmp指令
	memcpy(JmpToNewCode+1,ByteOffset,4);
	memset(JmpToNewCode+5,0x90,4);	//用nop补全
	

	ULONG WrittenLen = sizeof(JmpToNewCode);
	rv = mem_WriteBlock(hProcess,baseAddr,mlist,9,JmpToNewCode,&WrittenLen);
	if(rv != 0){
		return ;
	}

}


void CCSHelperDlg::OnBnClickedBtnInjectCancle()
{
	// TODO: 在此添加控件通知处理程序代码
}
