// F:\work\xh\MGProgram\Trunk\Projects\Robot\Src\LoginPage.cpp : 实现文件
//

#include "stdafx.h"
#include "MGRobot.h"
#include "LoginPage.h"
#include "ServerConfig.h"
#include "CClientNew.h"
#include "ClientManager.h"
#include "Operate.h"
#include "AccountDeleteConfirmDlg.h"
#include "ThreadTaskManager.h"
//using namespace MG;
//-----------------------------------------------------------------------------
MG::U32     CLoginPage::mMapListId = 0;
MG::Int      CLoginPage::mMapListType = 0;


// CLoginPage 对话框
IMPLEMENT_DYNAMIC(CLoginPage, CPropertyPage)
//-----------------------------------------------------------------------------
CLoginPage::CLoginPage()
	: CPropertyPage(CLoginPage::IDD)
{

	EnableAutomation();
	memset(mUsedIndexFlag,0,sizeof(mUsedIndexFlag));
}
//-----------------------------------------------------------------------------
CLoginPage::~CLoginPage()
{
}
//-----------------------------------------------------------------------------
void CLoginPage::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CPropertyPage::OnFinalRelease();
}
//-----------------------------------------------------------------------------
void CLoginPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SERVER, mComboService);
	DDX_Control(pDX, IDC_COMBO_CLAN, mComboClanSelect);
	DDX_Control(pDX, IDC_LIST_ACCOUNT, mAccountLoginList);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT_NAME, mEditAccountName);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT_PSW, mEditPassword);
	//DDX_Control(pDX, IDC_BUTTON_DELETE, m_BtnDelete);
	//DDX_Control(pDX, IDC_CHECK_DONT_RECONNECT, mButtonNontReconnect);
	//DDX_Control(pDX, IDC_CHECK_AUTO_CREATE_DEL, m_btnAutoCreateDel);
}
//-----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CLoginPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_ADD_ACOUNT, &CLoginPage::OnBnClickedButtonAddAcount)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ACCOUNT, &CLoginPage::OnBnClickedButtonDeleteAccount)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CLoginPage::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CLoginPage::OnBnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_ACCOUNT_LOGIN, &CLoginPage::OnBnClickedButtonAccountLogin)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_CLAN, &CLoginPage::OnBnClickedButtonCreateClan)
	ON_BN_CLICKED(IDC_BUTTON_DEL_CLAN, &CLoginPage::OnBnClickedButtonDelClan)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_CHARACTER, &CLoginPage::OnBnClickedButtonCreateCharacter)
	ON_BN_CLICKED(IDC_BUTTON_DEL_CHARACTER, &CLoginPage::OnBnClickedButtonDelCharacter)
	ON_BN_CLICKED(IDC_BUTTON_JOIN_GAME, &CLoginPage::OnBnClickedButtonJoinGame)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_ALL, &CLoginPage::OnBnClickedButtonCloseAll)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_JOIN_GAME, &CLoginPage::OnBnClickedButtonAutoJoinGame)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CLoginPage, CPropertyPage)
END_DISPATCH_MAP()
//-----------------------------------------------------------------------------
// 注意: 我们添加 IID_ILoginPage 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {982220FC-E03D-4434-B55E-97621C1D7DEC}
static const IID IID_ILoginPage =
{ 0x982220FC, 0xE03D, 0x4434, { 0xB5, 0x5E, 0x97, 0x62, 0x1C, 0x1D, 0x7D, 0xEC } };

BEGIN_INTERFACE_MAP(CLoginPage, CPropertyPage)
	INTERFACE_PART(CLoginPage, IID_ILoginPage, Dispatch)
END_INTERFACE_MAP()
//-----------------------------------------------------------------------------
BOOL CLoginPage::OnInitDialog()
{
	
	/*
	 CString mapId;
	((CEdit*)GetDlgItem(IDC_EDIT_MAPID))->GetWindowText(mapId);
	 CString mapType;
	 ((CEdit*)GetDlgItem(IDC_EDIT_MAPTYPE))->GetWindowText(mapType);

	 if (mapId.GetLength()>1)
	 {
        MG::MGStrOp::toU32((MG::Char8*)mapId.GetBuffer(),mMapListId);
	 }
	 if (mapType.GetLength()>1)
	 {
          MG::MGStrOp::toI32((MG::Char8*)mapType.GetBuffer(),mMapListType);
	 }
	 */
	
	 
	//
	UpdateData(FALSE);
	mAccountLoginList.InsertColumn(0,"ID",LVCFMT_LEFT,40);
	mAccountLoginList.InsertColumn(1,"账号",LVCFMT_LEFT,65);
	mAccountLoginList.InsertColumn(2,"登陆状态",LVCFMT_LEFT,150);
	mAccountLoginList.InsertColumn(3,"服务器地址",LVCFMT_LEFT,100);
	mAccountLoginList.InsertColumn(4,"在线人数",LVCFMT_LEFT,80);
	mAccountLoginList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_TRACKSELECT|LVS_EX_ONECLICKACTIVATE|LVS_EX_FLATSB|LVS_EX_CHECKBOXES|mAccountLoginList.GetExtendedStyle());
	for (int i = 0; true; i++)
	{
		CString strServerName=CServerConfig::getServerName(i);
		CString strServerIP=CServerConfig::getServerIP(i);
		if (strServerName.IsEmpty() || strServerIP.IsEmpty()) break;
		mComboService.InsertString(i,strServerName);
	}
	((CButton*)GetDlgItem(IDC_BUTTON_ACCOUNT_LOGIN))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_CREATE_CLAN))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_DEL_CLAN))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_CREATE_CHARACTER))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_DEL_CHARACTER))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_JOIN_GAME))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_CLOSE_ALL))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_AUTO_JOIN_GAME))->EnableWindow(TRUE);
	return TRUE;
}

//-----------------------------------------------------------------------------

void CLoginPage::OnBnClickedButtonAddAcount()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strServiceName,strAccountName,strPassword;
	mComboService.GetWindowText(strServiceName);
	strServiceName = CServerConfig::getServerIP(strServiceName);
	mEditAccountName.GetWindowText(strAccountName);
	mEditPassword.GetWindowText(strPassword);
	if (strServiceName.IsEmpty() || strAccountName.IsEmpty() || strPassword.IsEmpty())
	{
		return;
	}
	int index = allocateIndex();
	char buf[30];
	sprintf(buf,"%d",index);
	int n = mAccountLoginList.InsertItem(mAccountLoginList.GetItemCount(),buf);
	if (n!=CB_ERR)
	{
		MG::Str16 tempAccName,tempAccPsw;
		MG::MGStrOp::toString((MG::Char*)(strAccountName.GetBuffer()),tempAccName);
		MG::MGStrOp::toString((MG::Char*)(strPassword.GetBuffer()),tempAccPsw);
		
		//MG::ClientManager::getInstance().lockClients();
		MG::CClient* client = MG::ClientManager::getInstance().createOrRetrieve(
			index,strServiceName.GetBuffer(),(MG::Char16*)tempAccName.c_str(),(MG::Char16*)tempAccPsw.c_str(),0);
		//MG::ClientManager::getInstance().unLockClients();

		mAccountLoginList.SetItem(n,1,LVIF_TEXT,strAccountName,0,0,0,NULL);
		mAccountLoginList.SetItem(n,2,LVIF_TEXT|LVIF_STATE,"空闲",0,0,0,NULL);
		mAccountLoginList.SetItem(n,3,LVIF_TEXT|LVIF_STATE,strServiceName,0,0,0,NULL);
		mAccountLoginList.SetCheck(n);
		mAccountLoginList.SetItemData(n,(DWORD_PTR)client);
		GetDlgItem(IDC_BUTTON_DEL_CLAN)->EnableWindow();
	}
	mEditAccountName.SetWindowText(NULL);
	mEditPassword.SetWindowText(NULL);
	mEditAccountName.SetFocus();
}
//-----------------------------------------------------------------------------
void CLoginPage::OnBnClickedButtonDeleteAccount()
{
	// TODO: 在此添加控件通知处理程序代码
	if (MG::ClientManager::getInstance().getDataSet()->empty())
	{
		GetDlgItem(IDC_BUTTON_DEL_CLAN)->EnableWindow(FALSE);
		return;
	}
	AccountDeleteConfirmDlg *pDlg = new AccountDeleteConfirmDlg();
	int n = (int)pDlg->DoModal();
	delete pDlg;
	if (n == AccountDeleteConfirmDlg::DeleteResult_All)
	{
		MG::ClientManager::getInstance().closeAll();
		//MG::ClientManager::getInstance().lockClients();
		MG::ClientManager::getInstance().getClients()->destroyAll();
		//MG::ClientManager::getInstance().unLockClients();
		mAccountLoginList.DeleteAllItems();
		ZeroMemory(mUsedIndexFlag,sizeof(mUsedIndexFlag));
	}
	else if (n == AccountDeleteConfirmDlg::DeleteResult_Check)
	{	
		for (int i = 0; i < mAccountLoginList.GetItemCount();i++)
		{
			if (mAccountLoginList.GetCheck(i))
			{
				MG::CClient *client = reinterpret_cast<MG::CClient*>(mAccountLoginList.GetItemData(i));
				mAccountLoginList.DeleteItem(i);
				releaseIndex(client->getIndex());
				client->stateNetClose();
				MG::ClientManager::getInstance().lockClients();
				MG::ClientManager::getInstance().getClients()->destroy(client->getIndex());
				MG::ClientManager::getInstance().unLockClients();
			}
		}		
		
	}
	else if (n == AccountDeleteConfirmDlg::DeleteResult_Select)
	{
		int *index = new int[mAccountLoginList.GetItemCount()];
		int indexArraySize = 0;
		int i=0;
		for (;i<mAccountLoginList.GetItemCount();i++)
		{
			if (mAccountLoginList.GetItemState(i,LVIS_SELECTED)==LVIS_SELECTED)
			{
				MG::CClient *client = reinterpret_cast<MG::CClient*>(mAccountLoginList.GetItemData(i));
				mAccountLoginList.DeleteItem(i);
				releaseIndex(client->getIndex());
				client->stateNetClose();
				MG::ClientManager::getInstance().lockClients();
				MG::ClientManager::getInstance().getClients()->destroy(client->getIndex());
				MG::ClientManager::getInstance().unLockClients();
			}
		}
	}
	else if (n == AccountDeleteConfirmDlg::DeleteResult_Current)
	{
		// 暂时无单个账号控制
	}
	if (MG::ClientManager::getInstance().getClients()->empty())
	{
		GetDlgItem(IDC_BUTTON_DELETE_ACCOUNT)->EnableWindow(FALSE);
	}

}
//-----------------------------------------------------------------------------
void CLoginPage::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
}
//-----------------------------------------------------------------------------
void CLoginPage::OnBnClickedButtonRead()
{
	// TODO: 在此添加控件通知处理程序代码
	MG::ClientManager::getInstance().lockClients();
	CFileDialog fileDlg(TRUE,"ACC","*.ACC",OFN_FILEMUSTEXIST|OFN_NOCHANGEDIR|OFN_HIDEREADONLY,"BKop Account Files (*.ACC)|*.ACC|All Files (*.*)|*.*||",this);
	if( fileDlg.DoModal()!=IDOK )
	{
		return;
	}
	CStdioFile file;
	if (!file.Open(fileDlg.GetPathName(),CFile::modeRead|CFile::typeText))
	{
		return;
	}
	CString strServiceName,strAccountName,strPassword,strSelectClanNum;
	CString strRoleStartNum,strRoleEndNum;
	char strI[8] = {0};
	int nClan;
	if (file.ReadString(strServiceName) &&
		file.ReadString(strAccountName) &&
		file.ReadString(strRoleStartNum) &&
		file.ReadString(strRoleEndNum) &&
		file.ReadString(strPassword) &&
		file.ReadString(strSelectClanNum) &&
		0 <= (nClan = atoi(strSelectClanNum)) &&
		nClan <= CLAN_LIST_MAXNUM)
	{
		int iRoleStartNum = atoi(strRoleStartNum);
		int iRoleEndNum = atoi(strRoleEndNum);
		CString accountName;
		unsigned int threadCount = 0;
		threadCount = (iRoleEndNum - iRoleStartNum - 1) / MAX_CLIENT_COUNT_PRE_THREAD + 1;
		if (!MG::ThreadTaskManager::getInstance().initialize(threadCount))
		{
			return;
		}
		

		for (int i = iRoleStartNum; i < iRoleEndNum; ++i)
		{
			itoa(i,strI,10);			
			int index = allocateIndex();
			char buf[30] = {0};
			sprintf(buf,"%d",index);
			int n = mAccountLoginList.InsertItem(mAccountLoginList.GetItemCount(),buf);
			if (n != CB_ERR)
			{
				accountName = strAccountName + strI;
				MG::Str16 tempAccName,tempAccPsw;
				MG::MGStrOp::toString((MG::Char*)(accountName.GetBuffer()),tempAccName);
				MG::MGStrOp::toString((MG::Char*)(strPassword.GetBuffer()),tempAccPsw);

				int threadIndex = (i - iRoleStartNum) / MAX_CLIENT_COUNT_PRE_THREAD;

				MG::ThreadTaskManager::getInstance().createClient(index,strServiceName.GetBuffer(),(MG::Char16*)tempAccName.c_str(),(MG::Char16*)tempAccPsw.c_str(),nClan,threadIndex);
			
				//MG::CClient* client = MG::ClientManager::getInstance().createOrRetrieve(
				//	index,strServiceName.GetBuffer(),(MG::Char16*)tempAccName.c_str(),(MG::Char16*)tempAccPsw.c_str(),nClan);
				

				mAccountLoginList.SetItem(n,1,LVIF_TEXT,strAccountName + strI,0,0,0,NULL);
				mAccountLoginList.SetItem(n,2,LVIF_TEXT|LVIF_STATE,"空闲",0,0,0,NULL);
				mAccountLoginList.SetItem(n,3,LVIF_TEXT|LVIF_STATE,strServiceName,0,0,0,NULL);
				mAccountLoginList.SetCheck(n);
				//mAccountLoginList.SetItemData(n,(DWORD_PTR)client);
				GetDlgItem(IDC_BUTTON_DELETE_ACCOUNT)->EnableWindow();
			}
		}

		MG::ThreadTaskManager::getInstance().prepareThread();

	}
	file.Close();
	if (mComboClanSelect.GetCurSel()==CB_ERR)
	{
		mComboClanSelect.SetCurSel(0);
	}
	mComboClanSelect.SetFocus();
	//MG::ClientManager::getInstance().unLockClients();
}
//-----------------------------------------------------------------------------
void CLoginPage::OnBnClickedButtonAccountLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	//MG::ClientManager::getInstance().pushOperate(MG::OperateType_AccountLogin);
	//MG::ThreadTaskManager::getInstance().addRobotUiTask(MG::OperateType_AccountLogin);
	//MG::ThreadTaskManager::getInstance().addRobotUiTask(MG::OperateType_AccountLogin);
}
//-----------------------------------------------------------------------------
void CLoginPage::OnBnClickedButtonCreateClan()
{
	// TODO: 在此添加控件通知处理程序代码
	//MG::ClientManager::getInstance().pushOperate(MG::OperateType_CreateClan);
	//MG::ThreadTaskManager::getInstance().addRobotUiTask(MG::OperateType_CreateClan);
	//MG::ThreadTaskManager::getInstance().addRobotUiTask(MG::OperateType_CreateClan);
}
//-----------------------------------------------------------------------------
void CLoginPage::OnBnClickedButtonDelClan()
{
	//MG::ClientManager::getInstance().pushOperate(MG::OperateType_DeleteClan);
	// TODO: 在此添加控件通知处理程序代码
	//MG::ThreadTaskManager::getInstance().addRobotUiTask(MG::OperateType_DeleteClan);
	//MG::ThreadTaskManager::getInstance().addRobotUiTask(MG::OperateType_DeleteClan);
}
//-----------------------------------------------------------------------------
void CLoginPage::OnBnClickedButtonCreateCharacter()
{
	// TODO: 在此添加控件通知处理程序代码
	//MG::ClientManager::getInstance().pushOperate(MG::CLIENT_OPEARTE_CREATE_CHARACTER);

}
//-----------------------------------------------------------------------------
void CLoginPage::OnBnClickedButtonDelCharacter()
{
	// TODO: 在此添加控件通知处理程序代码
	//MG::ClientManager::getInstance().pushOperate(MG::CLIENT_OPEARTE_CHARACTER_DELETE);
}
//-----------------------------------------------------------------------------
void CLoginPage::OnBnClickedButtonJoinGame()
{
	//MG::ClientManager::getInstance().pushOperate(MG::OperateType_JoinGame);
	// TODO: 在此添加控件通知处理程序代码
	//MG::ThreadTaskManager::getInstance().addRobotUiTask(MG::OperateType_JoinGame);
	//MG::ThreadTaskManager::getInstance().addRobotUiTask(MG::OperateType_JoinGame);
}
//-----------------------------------------------------------------------------
void CLoginPage::OnBnClickedButtonCloseAll()
{
	//MG::ClientManager::getInstance().pushOperate(MG::OperateType_Close);
	// TODO: 在此添加控件通知处理程序代码
	//MG::ThreadTaskManager::getInstance().addRobotUiTask(MG::OperateType_Close);
	//MG::ThreadTaskManager::getInstance().addRobotUiTask(MG::OperateType_Close);
}
//-----------------------------------------------------------------------------
void CLoginPage::OnBnClickedButtonAutoJoinGame()
{
	//MG::ClientManager::getInstance().pushOperate(MG::OperateType_AutoJoinGame);
	// TODO: 在此添加控件通知处理程序代码
	//MG::ThreadTaskManager::getInstance().addRobotUiTask(MG::OperateType_AutoJoinGame);

}
//-----------------------------------------------------------------------------
int CLoginPage::allocateIndex()
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
void		releaseIndex(int index);

CListCtrl* CLoginPage::getAccountLoginList()
{
	return &mAccountLoginList;
}

DWORD CLoginPage::getCurSelectCount()
{
		return mAccountLoginList.GetSelectedCount();
}

DWORD CLoginPage::getCurCheckCount()
{
	DWORD n = 0;
	for (int i = 0; i < mAccountLoginList.GetItemCount(); i++)
	{
		if (mAccountLoginList.GetCheck(i))
		{
			n++;
		}
	}
	return n;
}

void CLoginPage::releaseIndex( int index )
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

//-----------------------------------------------------------------------------