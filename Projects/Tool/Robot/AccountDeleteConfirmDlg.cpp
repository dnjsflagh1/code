// AccountDeleteConfirmDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MGRobot.h"
#include "AccountDeleteConfirmDlg.h"
#include "MainFrm.h"
#include "LoginPage.h"

// AccountDeleteConfirmDlg �Ի���

IMPLEMENT_DYNAMIC(AccountDeleteConfirmDlg, CDialog)

AccountDeleteConfirmDlg::AccountDeleteConfirmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AccountDeleteConfirmDlg::IDD, pParent)
{

}

AccountDeleteConfirmDlg::~AccountDeleteConfirmDlg()
{
}

void AccountDeleteConfirmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL AccountDeleteConfirmDlg::OnInitDialog()
{
	int n = 0;
	CString str;
	GetDlgItem(IDC_BUTTON_TOTAL_COUNT)->SetWindowText("ɾ��ȫ��");
	GetDlgItem(IDC_BUTTON_SELECTED_COUNT)->SetWindowText("ɾ���б�ѡ��");
	GetDlgItem(IDC_BUTTON_CHECK_COUNT)->SetWindowText("ɾ���б�ѡ");
	GetDlgItem(IDC_BUTTON_NOW_COUNT)->SetWindowText("ɾ����ǰѡ��");
	GetDlgItem(IDC_BUTTON_DEL_CANCLE)->SetWindowText("ȡ��");

	CLoginPage *pPage=((CMainFrame*)theApp.m_pMainWnd)->GetLoginPage();
	n = pPage->getAccountLoginList()->GetItemCount();
	str.Format("�˺�����:%d",n);
	GetDlgItem(IDC_STATIC_TOTAL_COUNT)->SetWindowText(str);
	//((CMainFrame*)theApp.m_pMainWnd)->GetItemView()->GetComboSelectMainRole()->GetWindowText(str);
	GetDlgItem(IDC_STATIC_NOW_COUNT)->SetWindowText("��ǰ�˺�:0");
	n = pPage->getCurSelectCount();
	str.Format("�˺���Ŀ:%d",n);
	GetDlgItem(IDC_STATIC_SELECTED_COUNT)->SetWindowText(str);
	if (n == 0)
	{
		GetDlgItem(IDC_BUTTON_SELECTED_COUNT)->EnableWindow(FALSE);
	}
	n = pPage->getCurCheckCount();
	str.Format("�˺���Ŀ:%d",n);
	GetDlgItem(IDC_STATIC_CHECK_COUNT)->SetWindowText(str);
	if (n == 0)
	{
		GetDlgItem(IDC_BUTTON_CHECK_COUNT)->EnableWindow(FALSE);
	}

	return CDialog::OnInitDialog();
}
BEGIN_MESSAGE_MAP(AccountDeleteConfirmDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TOTAL_COUNT, &AccountDeleteConfirmDlg::OnBnClickedButtonTotalCount)
	ON_BN_CLICKED(IDC_BUTTON_SELECTED_COUNT, &AccountDeleteConfirmDlg::OnBnClickedButtonSelectedCount)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_COUNT, &AccountDeleteConfirmDlg::OnBnClickedButtonCheckCount)
	ON_BN_CLICKED(IDC_BUTTON_NOW_COUNT, &AccountDeleteConfirmDlg::OnBnClickedButtonNowCount)
	ON_BN_CLICKED(IDC_BUTTON_DEL_CANCLE, &AccountDeleteConfirmDlg::OnBnClickedButtonDelCancle)
END_MESSAGE_MAP()


// AccountDeleteConfirmDlg ��Ϣ�������

void AccountDeleteConfirmDlg::OnBnClickedButtonTotalCount()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(DeleteResult_All);
}

void AccountDeleteConfirmDlg::OnBnClickedButtonSelectedCount()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(DeleteResult_Select);
}

void AccountDeleteConfirmDlg::OnBnClickedButtonCheckCount()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(DeleteResult_Check);
}

void AccountDeleteConfirmDlg::OnBnClickedButtonNowCount()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(DeleteResult_Current);
}

void AccountDeleteConfirmDlg::OnBnClickedButtonDelCancle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(DeleteResult_Cancel);
}
