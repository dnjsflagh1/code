#pragma once


// AccountDeleteConfirmDlg �Ի���

class AccountDeleteConfirmDlg : public CDialog
{
	DECLARE_DYNAMIC(AccountDeleteConfirmDlg)

public:
	enum DeleteResult
	{
		DeleteResult_Cancel,
		DeleteResult_All,
		DeleteResult_Current,
		DeleteResult_Select,
		DeleteResult_Check
	};
	AccountDeleteConfirmDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AccountDeleteConfirmDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_DELETE_CONFIRM };

protected:
	BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTotalCount();
	afx_msg void OnBnClickedButtonSelectedCount();
	afx_msg void OnBnClickedButtonCheckCount();
	afx_msg void OnBnClickedButtonNowCount();
	afx_msg void OnBnClickedButtonDelCancle();
};
