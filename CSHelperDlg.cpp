
// CSHelperDlg.cpp : ʵ���ļ�
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


// ��ݼ�ע����Ϣ
#define		MHK_F10		0x1001
#define		MHK_F11		0x1002



//��ʱ����Ϣ
#define		TIMER_CONNECT_PROCESS		0x2000	
#define		TIMER_LOCK_HEALTH			0x2001

//��ʱ������ʱ��

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
END_MESSAGE_MAP()


// CCSHelperDlg ��Ϣ�������

BOOL CCSHelperDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	BOOL RegSuccess = TRUE;
// 	RegSuccess = RegisterHotKey(this->GetSafeHwnd(),MHK_F10,0,VK_F10);
// 	ASSERT_EQUAL_REG(RegSuccess,FALSE);
// 	RegSuccess =  RegisterHotKey(this->GetSafeHwnd(),MHK_F11,0,VK_F11);
// 	ASSERT_EQUAL_REG(RegSuccess,FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCSHelperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCSHelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCSHelperDlg::OnBnClickedBtnLockHealth()
{
	if(!IsLockHealth){	//�������δ����
		IsLockHealth = TRUE;
		GetDlgItem(IDC_BTN_LOCK_HEALTH)->SetWindowText("�����ѿ���");
		SetTimer(TIMER_LOCK_HEALTH,ELAPSE_TIMER_NOMAL,NULL);
	}
	else{
		IsLockHealth = FALSE;
		GetDlgItem(IDC_BTN_LOCK_HEALTH)->SetWindowText("�����ѹر�");
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
	rv = mem_WriteBlock(proHandle,baseAddr,wlist,4,ReadBuffer,&ReadddLen);
	if(rv != 0){
		return rv;
	}
	return 0;
}


int CCSHelperDlg::func_ConnectPro(){
	//��ȡĿ����̴��ھ��
	hWindow = FindWindow("#32770", "HelperTest")->GetSafeHwnd();
	ASSERT_HANDLE_NULL(hWindow);
	
	//��ȡ����pid
	GetWindowThreadProcessId(hWindow, &pid);
	ASSERT_HANDLE_NULL(pid);

	//��ȡ���̾��
	proHandle = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid);
	ASSERT_HANDLE_NULL(proHandle);


	//��ȡ�����׵�ַ
	int rv = mem_GetProcessAddr(pid,baseAddr);
	if(rv != 0){
		return rv ;
	}
	KillTimer(TIMER_CONNECT_PROCESS);
	MessageBox("����Ŀ����̳ɹ���",NULL,MB_OK);
	return 0;
}
void CCSHelperDlg::OnOk(){
}
void CCSHelperDlg::OnCancel(){
	DWORD rtn;
	rtn = MessageBox("ȷ��Ҫ�˳���",NULL,MB_OKCANCEL|MB_ICONQUESTION);
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
