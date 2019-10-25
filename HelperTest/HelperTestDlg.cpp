
// HelperTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HelperTest.h"
#include "HelperTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHelperTestDlg �Ի���

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


// CHelperTestDlg ��Ϣ�������

BOOL CHelperTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHelperTestDlg::OnPaint()
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