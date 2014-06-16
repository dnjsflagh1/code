// SettingPage.cpp : implementation file
//

#include "stdafx.h"
#include "MGRobot.h"
#include "SettingPage.h"
#include "ThreadTaskManager.h"
#include "RepeatedlyOrderOpPage.h"
#include "RepeatetlyRandomOpPage.h"
#include "OnceOpPage.h"
#include "MainFrm.h"
#include "CClientNew.h"
// CSettingPage dialog

IMPLEMENT_DYNAMIC(CSettingPage, CPropertyPage)

CSettingPage::CSettingPage()
	: CPropertyPage(CSettingPage::IDD)
{

}

CSettingPage::~CSettingPage()
{
}

void CSettingPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ACCOUNT1, mAccountLoginList);
}

BOOL CSettingPage::OnInitDialog()
{
	UpdateData(FALSE);
	mAccountLoginList.InsertColumn(0,"ID",LVCFMT_LEFT,40);
	mAccountLoginList.InsertColumn(1,"账号",LVCFMT_LEFT,65);
	mAccountLoginList.InsertColumn(2,"状态",LVCFMT_LEFT,150);
	mAccountLoginList.InsertColumn(3,"在线人数",LVCFMT_LEFT,80);
	mAccountLoginList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_TRACKSELECT|LVS_EX_ONECLICKACTIVATE|LVS_EX_FLATSB|LVS_EX_CHECKBOXES|mAccountLoginList.GetExtendedStyle());
	
	memset(mUsedIndexFlag,0,sizeof(mUsedIndexFlag));
	GetDlgItem(IDC_IP_SERVER)->SetWindowText("192.168.1.217");
	GetDlgItem(IDC_EDT_PORT)->SetWindowText("2000");
	GetDlgItem(IDC_EDT_ACCOUNT)->SetWindowText("robot");
	GetDlgItem(IDC_EDT_ACCOUNT_START)->SetWindowText("0");
	GetDlgItem(IDC_EDT_ACCOUNT_END)->SetWindowText("100");
	GetDlgItem(IDC_EDT_PSW)->SetWindowText("1");
	return CPropertyPage::OnInitDialog();
}
BEGIN_MESSAGE_MAP(CSettingPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_SETSETTING, &CSettingPage::OnBnClickedBtnSetsetting)
	ON_BN_CLICKED(IDC_BTN_REFLASH, &CSettingPage::OnBnClickedBtnReflash)
END_MESSAGE_MAP()


// CSettingPage message handlers

void CSettingPage::OnBnClickedBtnSetsetting()
{
	// TODO: Add your control notification handler code here
	CString Ip,strPort;
	int port;
	CString account;
	CString accountStart;
	CString accountEnd;
	CString psw;

	bool isOk = true;
	CIPAddressCtrl* ipCtrl = ((CIPAddressCtrl*)GetDlgItem(IDC_IP_SERVER));
	ipCtrl->GetWindowText(Ip);
	if (Ip.IsEmpty())
	{
		isOk = false;
		MessageBox("请输入地址");
	}
	
	CEdit* editPort = ((CEdit*)GetDlgItem(IDC_EDT_PORT));
	editPort->GetWindowText(strPort);
	if (strPort.IsEmpty())
	{
		isOk = false;
		MessageBox("请输入端口");
	}
	port = atoi(strPort.GetBuffer());

	CEdit* editAccount = ((CEdit*)GetDlgItem(IDC_EDT_ACCOUNT));
	editAccount->GetWindowText(account);
	CEdit* editAccountS = ((CEdit*)GetDlgItem(IDC_EDT_ACCOUNT_START));
	editAccountS->GetWindowText(accountStart);
	CEdit* editAccountE = ((CEdit*)GetDlgItem(IDC_EDT_ACCOUNT_END));
	editAccountE->GetWindowText(accountEnd);
	CEdit* editPsw = ((CEdit*)GetDlgItem(IDC_EDT_PSW));
	editPsw->GetWindowText(psw);

	if (account.IsEmpty() || accountStart.IsEmpty() || accountEnd.IsEmpty())
	{
		isOk = false;
		MessageBox("请输入帐号");
	}
	if (isOk)
	{
		int startIndex = atoi(accountStart.GetBuffer());
		int endIndex = atoi(accountEnd.GetBuffer());
		if (endIndex <= startIndex)
		{
			MessageBox("输入的帐号不合法");
			return;
		}
		char strIndex[8] = {0};

		CString accountName;
		unsigned int threadCount = 0;
		threadCount = (endIndex - startIndex - 1) / MAX_CLIENT_COUNT_PRE_THREAD + 1;
		if (MG::ThreadTaskManager::getInstance().initialize(threadCount))
		{

			for (int i = startIndex; i < endIndex; ++i)
			{
				itoa(i,strIndex,10);
				int index = allocateIndex();
				char buf[30] = {0};
				sprintf(buf,"%d",index);
				int n = mAccountLoginList.InsertItem(mAccountLoginList.GetItemCount(),buf);
				if (n != CB_ERR)
				{
					accountName = account + strIndex;
					MG::Str16 tempAccName,tempAccPsw;
					MG::MGStrOp::toString((MG::Char*)(accountName.GetBuffer()),tempAccName);
					MG::MGStrOp::toString((MG::Char*)(psw.GetBuffer()),tempAccPsw);

					int threadIndex = (i - startIndex) / MAX_CLIENT_COUNT_PRE_THREAD;

					MG::ThreadTaskManager::getInstance().createClient(index,Ip.GetBuffer(),(MG::Char16*)tempAccName.c_str(),(MG::Char16*)tempAccPsw.c_str(),0,threadIndex);

					//MG::CClient* client = MG::ClientManager::getInstance().createOrRetrieve(
					//	index,strServiceName.GetBuffer(),(MG::Char16*)tempAccName.c_str(),(MG::Char16*)tempAccPsw.c_str(),nClan);


					mAccountLoginList.SetItem(n,1,LVIF_TEXT,accountName,0,0,0,NULL);
					mAccountLoginList.SetItem(n,2,LVIF_TEXT|LVIF_STATE,"空闲",0,0,0,NULL);
					mAccountLoginList.SetItem(n,3,LVIF_TEXT|LVIF_STATE,"0",0,0,0,NULL);


					mAccountLoginList.SetCheck(n);
					//mAccountLoginList.SetItemData(n,(DWORD_PTR)client);
					
				}
				
			}
			MG::ThreadTaskManager::getInstance().prepareThread();
			GetDlgItem(IDC_IP_SERVER)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDT_PORT)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDT_ACCOUNT)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDT_ACCOUNT_START)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDT_ACCOUNT_END)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDT_PSW)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_SETSETTING)->EnableWindow(FALSE);

			((CMainFrame*)theApp.m_pMainWnd)->GetOnceOpPage()->enableAllWindow(FALSE);
			((CMainFrame*)theApp.m_pMainWnd)->GetRepeatetlyRandomOpPage()->enableAllWindow(FALSE);
			((CMainFrame*)theApp.m_pMainWnd)->GetRepeatedlyOrderOpPage()->enableAllWindow(FALSE);

		}
	}

}


int CSettingPage::allocateIndex()
{
	for (int i = 1; i <= ACCOUNT_MAXNUM; i++)
	{
		if (!mUsedIndexFlag[i])
		{
			mUsedIndexFlag[i] = true;
			return i;
		}
	}
	//DYNAMIC_ASSERT(false);
	MessageBox("超过最大数");
	return -1;
}

void CSettingPage::releaseIndex( int index )
{
	if (index<=0 ||index>ACCOUNT_MAXNUM)
	{
		ASSERT(false);
	}
	if (mUsedIndexFlag[index] == false)
	{
		ASSERT(false);
	}
	mUsedIndexFlag[index] = false;
}
void CSettingPage::OnBnClickedBtnReflash()
{
	// TODO: Add your control notification handler code here
	//IDC_LIST_ACCOUNT1
	std::map<MG::I32,MG::CClient*>* clients = MG::ThreadTaskManager::getInstance().getClientMap();
	if (clients)
	{
		std::map<MG::I32,MG::CClient*>::iterator it = clients->begin();
		for (; it != clients->end(); it++)
		{
			mAccountLoginList.SetItem(it->first - 1,2,LVIF_TEXT|LVIF_STATE,it->second->getStateName().c_str(),0,0,0,NULL);
		}
	}
		
}
