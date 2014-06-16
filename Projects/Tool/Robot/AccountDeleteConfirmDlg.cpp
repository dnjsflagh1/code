// AccountDeleteConfirmDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MGRobot.h"
#include "AccountDeleteConfirmDlg.h"
#include "MainFrm.h"
#include "LoginPage.h"

// AccountDeleteConfirmDlg 对话框

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
	GetDlgItem(IDC_BUTTON_TOTAL_COUNT)->SetWindowText("删除全部");
	GetDlgItem(IDC_BUTTON_SELECTED_COUNT)->SetWindowText("删除列表选择");
	GetDlgItem(IDC_BUTTON_CHECK_COUNT)->SetWindowText("删除列表勾选");
	GetDlgItem(IDC_BUTTON_NOW_COUNT)->SetWindowText("删除当前选择");
	GetDlgItem(IDC_BUTTON_DEL_CANCLE)->SetWindowText("取消");

	CLoginPage *pPage=((CMainFrame*)theApp.m_pMainWnd)->GetLoginPage();
	n = pPage->getAccountLoginList()->GetItemCount();
	str.Format("账号总数:%d",n);
	GetDlgItem(IDC_STATIC_TOTAL_COUNT)->SetWindowText(str);
	//((CMainFrame*)theApp.m_pMainWnd)->GetItemView()->GetComboSelectMainRole()->GetWindowText(str);
	GetDlgItem(IDC_STATIC_NOW_COUNT)->SetWindowText("当前账号:0");
	n = pPage->getCurSelectCount();
	str.Format("账号数目:%d",n);
	GetDlgItem(IDC_STATIC_SELECTED_COUNT)->SetWindowText(str);
	if (n == 0)
	{
		GetDlgItem(IDC_BUTTON_SELECTED_COUNT)->EnableWindow(FALSE);
	}
	n = pPage->getCurCheckCount();
	str.Format("账号数目:%d",n);
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


// AccountDeleteConfirmDlg 消息处理程序

void AccountDeleteConfirmDlg::OnBnClickedButtonTotalCount()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(DeleteResult_All);
}

void AccountDeleteConfirmDlg::OnBnClickedButtonSelectedCount()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(DeleteResult_Select);
}

void AccountDeleteConfirmDlg::OnBnClickedButtonCheckCount()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(DeleteResult_Check);
}

void AccountDeleteConfirmDlg::OnBnClickedButtonNowCount()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(DeleteResult_Current);
}

void AccountDeleteConfirmDlg::OnBnClickedButtonDelCancle()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(DeleteResult_Cancel);
}
