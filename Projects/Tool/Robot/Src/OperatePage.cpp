// F:\work\xh\MGProgram\Trunk\Projects\Robot\Src\OperatePage.cpp : 实现文件
//

#include "stdafx.h"
#include "MGRobot.h"
#include "OperatePage.h"
#include "ClientManager.h"
#include "CampaignPage.h"
#include "MainFrm.h"
#include "OperateManager.h"
#include "RandMoveOperate.h"
#include "ChatOperate.h"
#include "ChannelInfo.h"
#include "ThreadTaskManager.h"



// COperatePage 对话框
OperateMode					 COperatePage::mOperateMode = OperateMode_NULL;
bool						 COperatePage::mIsStartOperate = false;
std::vector<MG::OperateType> COperatePage::mOperates;
MG::Int						 COperatePage::mOperateIndex = 0;
MG::Int						 COperatePage::mCurrOperateIndex = 0;
std::map<MG::OperateType,OperateModeAttribute*> COperatePage::mOperateModeAttrMap;
IMPLEMENT_DYNAMIC(COperatePage, CPropertyPage)

COperatePage::COperatePage()
	: CPropertyPage(COperatePage::IDD)
{

}

COperatePage::~COperatePage()
{
}

void COperatePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COperatePage, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_STATR_OPERATE, &COperatePage::OnBnClickedBtnStatrOperate)
	ON_BN_CLICKED(IDC_BTN_END_OPERATE, &COperatePage::OnBnClickedBtnEndOperate)
	ON_BN_CLICKED(IDC_CHECK_USE_SKILL, &COperatePage::OnBnClickedCheckUseSkill)
	ON_BN_CLICKED(IDC_CHECK_JUMP_MAP, &COperatePage::OnBnClickedCheckJumpMap)
	ON_BN_CLICKED(IDC_CHECK_TEST_NET, &COperatePage::OnBnClickedCheckTestNet)
	ON_BN_CLICKED(IDC_CHECK_RAND_TEST, &COperatePage::OnBnClickedCheckRandTest)
	ON_BN_CLICKED(IDC_CHECK_ORDER_TEST, &COperatePage::OnBnClickedCheckOrderTest)
	ON_BN_CLICKED(IDC_RADIO_RAND_TEST, &COperatePage::OnBnClickedRadioRandTest)
	ON_BN_CLICKED(IDC_RADIO_ORDER_TEST, &COperatePage::OnBnClickedRadioOrderTest)
	ON_BN_CLICKED(IDC_CHECK_TEST_RANDMOVE, &COperatePage::OnBnClickedCheckTestRandmove)

	ON_BN_CLICKED(IDC_BTN_CREATESOLDIER, &COperatePage::OnBnClickedBtnCreatesoldier)
	ON_BN_CLICKED(IDC_CHECK_TEST_LOGINANDOUT, &COperatePage::OnBnClickedCheckTestLoginandout)
	ON_BN_CLICKED(IDC_CHECK_TEST_CREATECAM, &COperatePage::OnBnClickedCheckTestCreatecam)
	ON_BN_CLICKED(IDC_BTN_CREATESOLDIER2, &COperatePage::OnBnClickedBtnCreatesoldier2)
	ON_BN_CLICKED(IDC_TEST_LOGIN_NET, &COperatePage::OnBnClickedTestLoginNet)
	ON_BN_CLICKED(IDC_CHECK_FULLSERVER_CHAT, &COperatePage::OnBnClickedCheckFullserverChat)
	ON_BN_CLICKED(IDC_CHECK_REGION_CHAT, &COperatePage::OnBnClickedCheckRegionChat)
END_MESSAGE_MAP()


// COperatePage 消息处理程序

void COperatePage::OnBnClickedBtnStatrOperate()
{
	// TODO: 在此添加控件通知处理程序代码
	COperatePage::mIsStartOperate = true;
	((CButton*)GetDlgItem(IDC_BTN_STATR_OPERATE))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BTN_END_OPERATE))->EnableWindow(TRUE);
	BOOL isRandMoveCheck = ((CButton*)GetDlgItem(IDC_CHECK_TEST_RANDMOVE))->GetCheck();
	if (isRandMoveCheck)
	{
		CString moveTime;
		((CEdit*)GetDlgItem(IDC_EDIT_RANDMOVETIME))->GetWindowText(moveTime);
		MG::U32 moveTimeInt = 0;
		if ( moveTime.GetLength() > 0 )
		{
			MG::MGStrOp::toU32((MG::Char8*)moveTime.GetBuffer(),moveTimeInt);
		}
		mOperateModeAttrMap[MG::OperateType_RandMove]->lifePeriod = moveTimeInt;

	}
	BOOL isNetTestLogin = ((CButton*)GetDlgItem(IDC_TEST_LOGIN_NET))->GetCheck();
	BOOL isFullServerChat = ((CButton*)GetDlgItem(IDC_CHECK_FULLSERVER_CHAT))->GetCheck();
	BOOL isOneRegionChat = ((CButton*)GetDlgItem(IDC_CHECK_REGION_CHAT))->GetCheck();
	if (isNetTestLogin || isFullServerChat || isOneRegionChat)
	{
		CString sendSize;
		((CEdit*)GetDlgItem(IDC_EDIT_SEND_SIZE))->GetWindowText(sendSize);
		MG::U32 size = 0;
		if ( sendSize.GetLength() > 0 )
		{
			MG::MGStrOp::toU32((MG::Char8*)sendSize.GetBuffer(),size);
		}
		{
			MG::NetTestLoginOperate::mSize = size;
			MG::ChatOperate::mSize = size;
		}
		
	}
}

void COperatePage::OnBnClickedBtnEndOperate()
{
	// TODO: 在此添加控件通知处理程序代码
	COperatePage::mIsStartOperate = false;
	((CButton*)GetDlgItem(IDC_BTN_STATR_OPERATE))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BTN_END_OPERATE))->EnableWindow(FALSE);
}

void COperatePage::OnBnClickedCheckUseSkill()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL isCheck = ((CButton*)GetDlgItem(IDC_CHECK_USE_SKILL))->GetCheck();
	if(isCheck)
		pushOperate(MG::OperateType_UseSkill);
	else
		removeOperate(MG::OperateType_UseSkill);

	//mOperateIndex = 0;

}

void COperatePage::OnBnClickedCheckJumpMap()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL isCheck = ((CButton*)GetDlgItem(IDC_CHECK_JUMP_MAP))->GetCheck();
	if(isCheck)
		pushOperate(MG::OperateType_JumpRegion);
	else
		removeOperate(MG::OperateType_JumpRegion);
	//mOperateIndex = 0;
}

void COperatePage::OnBnClickedCheckTestNet()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL isCheck = ((CButton*)GetDlgItem(IDC_CHECK_TEST_NET))->GetCheck();
	if(isCheck)
		pushOperate(MG::OperateType_NetTest);
	else
		removeOperate(MG::OperateType_NetTest);
	//mOperateIndex = 0;
}

void COperatePage::OnBnClickedCheckRandTest()
{
	// TODO: 在此添加控件通知处理程序代码
}

void COperatePage::OnBnClickedCheckOrderTest()
{
	// TODO: 在此添加控件通知处理程序代码
}

void COperatePage::OnBnClickedRadioRandTest()
{
	// TODO: Add your control notification handler code here
	COperatePage::mOperateMode = OperateMode_Random;
}

void COperatePage::OnBnClickedRadioOrderTest()
{
	// TODO: Add your control notification handler code here
	COperatePage::mOperateMode = OperateMode_Order;
}


OperateMode COperatePage::getOperateMode()
{
	return mOperateMode;
}

bool COperatePage::isOperateStart()
{
	return mIsStartOperate;
}

MG::OperateType COperatePage::getOneOperate(MG::Int index)
{
	
	if (mOperates.empty())
	{
		return MG::OperateType_null;
	}
	if (mOperateMode == OperateMode_Order)
	{
		MG::OperateType operateType = mOperates[index];
		//mCurrOperateIndex++;
		return operateType;
	}
	else if(mOperateMode == OperateMode_Random)
	{
		unsigned int index = MG::MGRandom::getInstance().rand_ab_One(0,mOperates.size());
		if (index == mOperates.size())
		{
			index--;
		}
		return mOperates[index];
	}

	return MG::OperateType_null;

}

void COperatePage::pushOperate( MG::OperateType operate )
{
	mOperates.push_back(operate);
}

void COperatePage::removeOperate( MG::OperateType operate )
{
	std::vector<MG::OperateType>::iterator it = mOperates.begin();
	for (; it != mOperates.end(); it++)
	{
		if ((*it) == operate)
		{
			mOperates.erase(it);
			return;
		}
	}
}
void COperatePage::OnBnClickedCheckTestRandmove()
{
	// TODO: Add your control notification handler code here
	// TODO: 在此添加控件通知处理程序代码
	 
	
	BOOL isCheck = ((CButton*)GetDlgItem(IDC_CHECK_TEST_RANDMOVE))->GetCheck();
	if(isCheck)
	{    pushOperate(MG::OperateType_RandMove);
	       
	     OperateModeAttribute* operateAttribute = new OperateModeAttribute();
		 pushOperateModeAttr(MG::OperateType_RandMove,operateAttribute);
		
	}
	else
	{
		removeOperate(MG::OperateType_RandMove);
	    clearOperateModeAttribute(MG::OperateType_RandMove);
	}
	    
	//mOperateIndex = 0;
}

BOOL COperatePage::OnInitDialog()
{

	((CButton*)GetDlgItem(IDC_RADIO_RAND_TEST))->SetCheck(TRUE);
	COperatePage::mOperateMode = OperateMode_Random;
	return  CPropertyPage::OnInitDialog();
}

void COperatePage::OnBnClickedBtnCreatesoldier()
{
	// TODO: Add your control notification handler code here
	//MG::ClientManager::getInstance().pushOperate(MG::OperateType_CreateTroop);
	//MG::ThreadTaskManager::getInstance().addRobotUiTask(MG::OperateType_CreateTroop);
}

void COperatePage::OnBnClickedCheckTestLoginandout()
{
	// TODO: Add your control notification handler code here
	BOOL isCheck = ((CButton*)GetDlgItem(IDC_CHECK_TEST_LOGINANDOUT))->GetCheck();
	if(isCheck)
	{   
		
		pushOperate(MG::OperateType_AutoJoinGame);
		OperateModeAttribute* operateAttribute = new OperateModeAttribute();
		pushOperateModeAttr(MG::OperateType_AutoJoinGame,operateAttribute);
		

	}
		//pushOperate(MG::OperateType_JumpRegion);
	else
	{
		removeOperate(MG::OperateType_AutoJoinGame);
        clearOperateModeAttribute(MG::OperateType_AutoJoinGame);

	}
		//removeOperate(MG::OperateType_JumpRegion);
	//mOperateIndex = 0;
}

void COperatePage::OnBnClickedCheckTestCreatecam()
{
	// TODO: Add your control notification handler code here
    BOOL isCheck = ((CButton*)GetDlgItem(IDC_CHECK_TEST_CREATECAM))->GetCheck();
	if (isCheck)
	{
        //
		 CCampaignPage* campaignPageInstance = NULL;
		 campaignPageInstance = (CCampaignPage*)((CMainFrame*)theApp.m_pMainWnd)->GetCampaignPage();
		 campaignPageInstance->handleCreateCampagin(CCampaignPage::CONTINUOUS_CREATE_CAMPAGIN);
		//CCampaignPage* campaignPageInstance = NULL;
		//campaignPageInstance = (CCampaignPage*)((CMainFrame*)theApp.m_pMainWnd)->GetCampaignPage();
		 pushOperate(MG::OperateType_CreateCampaign);

	}
	else
	{
		removeOperate(MG::OperateType_CreateCampaign);
	}
	
	//mOperateIndex = 0;
}


void COperatePage::clearOperateModeAttribute( MG::OperateType type )
{
	std::map<MG::OperateType,OperateModeAttribute*>::iterator It = mOperateModeAttrMap.find(type);
	if (It != mOperateModeAttrMap.end())
	{
		delete (It->second);
		mOperateModeAttrMap.erase(It);
	}
}

void COperatePage::clearAllOperateModeAttribute()
{
      std::map<MG::OperateType,OperateModeAttribute*>::iterator front = mOperateModeAttrMap.begin();
	  std::map<MG::OperateType,OperateModeAttribute*>::iterator back = mOperateModeAttrMap.end();
	  while(front != back)
	  {
          delete (front->second);

		  front++;
	  }
      mOperateModeAttrMap.clear();
	  mOperateIndex--;
	  
    
}

void COperatePage::pushOperateModeAttr( MG::OperateType operate,OperateModeAttribute* operateAttr )
{
	
	std::map<MG::OperateType,OperateModeAttribute*>::iterator It = mOperateModeAttrMap.find(operate);
	if (It != mOperateModeAttrMap.end())
	{
		return;
	}
	operateAttr->index = mOperateIndex;
	mOperateIndex++;
    mOperateModeAttrMap[operate] = operateAttr;

}
//void COperatePage::OnBnClickedCheckTestNetl()
//{
//	// TODO: Add your control notification handler code here
//	BOOL isCheck = ((CButton*)GetDlgItem(IDC_CHECK_TEST_NETL))->GetCheck();
//	if(isCheck)
//	{   
//		pushOperate(MG::OperateType_TestNetLogin);
//		OperateModeAttribute* operateAttribute = new OperateModeAttribute();
//		pushOperateModeAttr(MG::OperateType_TestNetLogin,operateAttribute);
//
//	}
//	else
//	{
//		removeOperate(MG::OperateType_TestNetLogin);
//		clearOperateModeAttribute(MG::OperateType_TestNetLogin);
//	}
//}

void COperatePage::OnBnClickedBtnCreatesoldier2()
{
	// TODO: Add your control notification handler code here
	//MG::ClientManager::getInstance().pushOperate(MG::OperateType_connectLogin);
	//MG::ThreadTaskManager::getInstance().addRobotUiTask(MG::OperateType_connectLogin);
}

void COperatePage::OnBnClickedTestLoginNet()
{
	// TODO: Add your control notification handler code here
	BOOL isCheck = ((CButton*)GetDlgItem(IDC_TEST_LOGIN_NET))->GetCheck();
	if(isCheck)
	{   
		pushOperate(MG::OperateType_TestNetLogin);
		OperateModeAttribute* operateAttribute = new OperateModeAttribute();
		pushOperateModeAttr(MG::OperateType_TestNetLogin,operateAttribute);

	}
	else
	{
		removeOperate(MG::OperateType_TestNetLogin);
		clearOperateModeAttribute(MG::OperateType_TestNetLogin);
	}
}
void COperatePage::OnBnClickedCheckFullserverChat()
{
	/*
	*chat channel name
	*GM,公告,广播,全服,国家,同州
	*城市,同盟,队伍,密语,大喊
	*/
	// TODO: Add your control notification handler code here
	BOOL isCheck = ((CButton*)GetDlgItem(IDC_CHECK_FULLSERVER_CHAT))->GetCheck();
	if (isCheck)
	{
		pushOperate(MG::OperateType_netChat);	
		OperateModeAttribute* operateAttribute = new OperateModeAttribute();
		pushOperateModeAttr(MG::OperateType_netChat,operateAttribute);

		//--
		MG::ChannelInfo* info = MG::ChannelInfos::getInstance().getChannelInfo(L"全服");
        if (info != NULL)
        {
			MG::ChatOperate::mSelectChannelInfo = info;
			MG::ChatOperate::mIntervalTime = 2000;
        }
 
	}
	else
	{
		removeOperate(MG::OperateType_netChat);
		clearOperateModeAttribute(MG::OperateType_netChat);
	}
}

void COperatePage::OnBnClickedCheckRegionChat()
{
	// TODO: Add your control notification handler code hereIDC_CHECK_REGION_CHAT
	BOOL isCheck = ((CButton*)GetDlgItem(IDC_CHECK_REGION_CHAT))->GetCheck();
	if (isCheck)
	{
		pushOperate(MG::OperateType_netChat);	
		OperateModeAttribute* operateAttribute = new OperateModeAttribute();
		pushOperateModeAttr(MG::OperateType_netChat,operateAttribute);

		//--
		MG::ChannelInfo* info = MG::ChannelInfos::getInstance().getChannelInfo(L"大喊");
		if (info != NULL)
		{
			MG::ChatOperate::mSelectChannelInfo = info;
			MG::ChatOperate::mIntervalTime = 1000;
		}

	}
	else
	{
		removeOperate(MG::OperateType_netChat);
		clearOperateModeAttribute(MG::OperateType_netChat);
	}

}
