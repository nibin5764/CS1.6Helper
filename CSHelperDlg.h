
// CSHelperDlg.h : ͷ�ļ�
//

#pragma once


// CCSHelperDlg �Ի���
class CCSHelperDlg : public CDialog
{
// ����
public:
	CCSHelperDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CSHELPER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	HANDLE proHandle;			//Ŀ����̾��
	int func_LockHealth();

public:
	afx_msg void OnBnClickedBtnLockHealth();
};
