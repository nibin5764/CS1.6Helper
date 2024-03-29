
// CSHelperDlg.h : 头文件
//

#pragma once


// CCSHelperDlg 对话框
class CCSHelperDlg : public CDialog
{
// 构造
public:
	CCSHelperDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CSHELPER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LONG OnHotKey(WPARAM wPARAM, LPARAM lPARAM);
	afx_msg void OnOk();
	afx_msg void OnCancel();
	void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

private:
	BOOL IsLockHealth;
	HANDLE hProcess;			//目标进程句柄
	DWORD pid;
	HWND hWindow;
	DWORD baseAddr;				//目标进程基址
	int func_LockHealth();
	int func_ConnectPro();
public:
	afx_msg void OnBnClickedBtnLockHealth();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnInjectTest();
	afx_msg void OnBnClickedBtnInjectCancle();
};
