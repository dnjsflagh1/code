/******************************************************************************/
#include "stdafx.h"
#include "PrintDialog.h"
#include "../resource.h"

#include "MyListView.h"
#include "SWorldManager.h"

#include "SCampaignManager.h"
#include "PrintWindowsCfg.h"
/******************************************************************************/

namespace MG
{
	static BOOL CALLBACK CampaignDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static BOOL CALLBACK PlayerDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static BOOL CALLBACK PlayerCharacterDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);


	//-----------------------------------------------------------------------------
	PrintDialog::PrintDialog()
		:mCampaignDlg(NULL)
		,mPlayerDlg(NULL)
		,mPlayerCharacterDlg(NULL)
	{
	}

	//-----------------------------------------------------------------------------
	PrintDialog::~PrintDialog()
	{
	}


	//-----------------------------------------------------------------------------
	BOOL CALLBACK CampaignDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch(uMsg)
		{
		case WM_INITDIALOG:
			{
				break;
			}
		case WM_COMMAND:
			{
				break;
			}
		case WM_CLOSE:
			{
				PostQuitMessage(0);
				break;
			}
		}
		return FALSE;
	}

	//-----------------------------------------------------------------------------
	BOOL CALLBACK PlayerDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch(uMsg)
		{
		case WM_INITDIALOG:
			{
				break;
			}
		case WM_KEYDOWN:
			{
				break;
			}
		case WM_COMMAND:
			{
				break;
			}

		case WM_CLOSE:
			{
				PostQuitMessage(0);
				break;
			}
		}
		return FALSE;	
	}
	//-----------------------------------------------------------------------------
	BOOL CALLBACK PlayerCharacterDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch(uMsg)
		{
		case WM_INITDIALOG:
			{
				break;
			}
		case WM_KEYDOWN:
			{
				break;
			}
		case WM_COMMAND:
			{
				break;
			}

		case WM_CLOSE:
			{
				PostQuitMessage(0);
				break;
			}
		}
		return FALSE;	
	}

	//-----------------------------------------------------------------------------
	void PrintDialog::createMainDialog()
	{
#ifdef _DEBUG
		HINSTANCE hInst = GetModuleHandle("CenterServer_d.dll");
#else
		HINSTANCE hInst = GetModuleHandle("CenterServer.dll");
#endif


		// Map 的打印信息
		if(PrintWindowsCfg::getInstance().getPrintMap() == 1)
		{
			mCampaignDlg = ::CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_CAMPAIGN), GetDesktopWindow(), CampaignDlgProc);
			ShowWindow(mCampaignDlg, SW_SHOW);
			std::string	strCaption = "CenterServer【Campaign】";
			strCaption += "[";
			strCaption += __DATE__;
			strCaption += " ";
			strCaption += __TIME__;
			strCaption += "]";
			SetWindowText(mCampaignDlg, strCaption.c_str());

			HMENU hMenu = GetSystemMenu(mCampaignDlg, FALSE);
			EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);

			//设置事件
			mWindowProcCampaign = (WinProc)GetWindowLong((HWND)mCampaignDlg,GWL_WNDPROC);
			SetWindowLong((HWND)mCampaignDlg, GWL_WNDPROC, (LONG)(&windowCampaignMsg));
		}

	}

	LRESULT CALLBACK PrintDialog::windowCampaignMsg( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
	{
		switch(message)
		{
		case WM_COMMAND:
			{
				switch(wParam)
				{
				case IDOK:
					{
						if(PrintWindowsCfg::getInstance().getPrintMap() == 1)
						{
							PrintDialog::getInstance().printCampaign();
						}
					}
					break;
				}
			}
			break;
		default:
			{

			}
			break;;
		}

		return (CallWindowProc((WinProc)mWindowProcCampaign, hwnd, message, wParam, lParam));
	}

	//-----------------------------------------------------------------------------
	void PrintDialog::printCampaign()
	{
		static MyListView listView_Campaign;
		listView_Campaign.GetListViewHandle(mCampaignDlg, IDC_LIST_CAMPAIGN);
		listView_Campaign.DeleteAllItem();
		listView_Campaign.DeleteAllColum();


		listView_Campaign.InsertColumn(0, 	"战斗状态",							50);
		listView_Campaign.InsertColumn(1, 	"mAttackCampOwnerAccountId",		70);
		listView_Campaign.InsertColumn(2, 	"mDefenseCampOwnerAccountId",		85);
		listView_Campaign.InsertColumn(3, 	"mCampaignCreatorAccountId",		90);
		listView_Campaign.InsertColumn(4, 	"CampaignId",						80);
		listView_Campaign.InsertColumn(5, 	"mCampaignCreatorClanName",			80);
		listView_Campaign.InsertColumn(6, 	"mCampaignName", 					80);
		listView_Campaign.InsertColumn(7, 	"mCampaignTargetRegionId", 			80);
		listView_Campaign.InsertColumn(8, 	"mCampaignInstanceUid", 			120);
		
		listView_Campaign.InsertColumn(9, 	"mAttackMemberNum",					100);
		listView_Campaign.InsertColumn(10,	"mDefenseMemberNum",				120);
		
		listView_Campaign.InsertColumn(11, 	"mClanAttackHost",					100);
		listView_Campaign.InsertColumn(12,	"mClanAttackList",					120);
		listView_Campaign.InsertColumn(13,	"mClanDenfenseList",				120);
		

		Int index = 0;

		//准备列表
		{
			std::map<ClanIdType, SCampaign*>* prepareCampaignList = SCampaignManager::getInstance().getPrepareCampaignList();
			for (std::map<ClanIdType, SCampaign*>::iterator iter = prepareCampaignList->begin(); 
				iter != prepareCampaignList->end(); ++iter)
			{
				printSigleCampaignInfo(&listView_Campaign, index, iter->second, BattleType_Prepare);
				++index;
			}
		}
		

		//战斗列表
		{
			std::map<ClanIdType, SCampaign*>* onBattleCampaignList = SCampaignManager::getInstance().getOnBattleCampaignList();
			for (std::map<ClanIdType, SCampaign*>::iterator iter = onBattleCampaignList->begin(); 
				iter != onBattleCampaignList->end(); ++iter)
			{
				printSigleCampaignInfo(&listView_Campaign, index, iter->second, BattleType_Battle);
				++index;
			}
		}
		
		//结算列表
		{
			std::map<ClanIdType, SCampaign*>* onEndCampaignList = SCampaignManager::getInstance().getEndCampaignList();
			for (std::map<ClanIdType, SCampaign*>::iterator iter = onEndCampaignList->begin(); 
				iter != onEndCampaignList->end(); ++iter)
			{
				printSigleCampaignInfo(&listView_Campaign, index, iter->second, BattleType_End);
				++index;
			}
		}
	}

	//-----------------------------------------------------------------------------
	void PrintDialog::printSigleCampaignInfo(MyListView* listView_Campaign, Int index, SCampaign* campaign, BattleType battleType)
	{
		listView_Campaign->InsertItem(index);

		std::string strBattleType;
		if (BattleType_Prepare == battleType)
		{
			strBattleType = "准备中";
		}
		else if(BattleType_Battle == battleType)
		{
			strBattleType = "已开战";
		}
		else if(BattleType_End == battleType)
		{
			strBattleType = "结算";
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}

		listView_Campaign->SetItemTextStr(index, 	0, 	strBattleType.c_str());
		listView_Campaign->SetItemTextU64(index, 	1, 	campaign->getAttackCampOwnerAccountId());
		listView_Campaign->SetItemTextU64(index, 	2, 	campaign->getDefenseCampOwnerAccountId());
		listView_Campaign->SetItemTextU64(index, 	3, 	campaign->getCampaignCreatorAccountId());
		listView_Campaign->SetItemTextU64(index, 	4, 	campaign->getCampaignId());
		listView_Campaign->SetItemTextStr16(index, 	5, 	campaign->getCampaignCreatorClanName().c_str());
		listView_Campaign->SetItemTextStr16(index, 	6, 	campaign->getCampaignName().c_str());
		listView_Campaign->SetItemTextU64(index, 	7, 	campaign->getCampaignTargetRegionId());
		listView_Campaign->SetItemTextU64(index, 	8, 	campaign->getCampaignTargetInstance());

		listView_Campaign->SetItemTextInt(index, 	9, 	campaign->getAttackRealMemberNum());
		listView_Campaign->SetItemTextInt(index, 	10, campaign->getDefenseRealMemberNum());

		// attack Host 列表 信息
		{
			std::map<POSITION, ClanArmy*>* attackHostList = campaign->getAttackHostList();

			std::string strAttackList;
			Int attackNum = getPosInfoStr(attackHostList, &strAttackList);

			listView_Campaign->SetItemTextStr(index, 11, strAttackList.c_str());
		}

		// attack 列表 信息
		{
			std::map<POSITION, ClanArmy*>* attackMemberList = campaign->getAttackMemberList();

			std::string strAttackList;
			Int attackNum = getPosInfoStr(attackMemberList, &strAttackList);

			listView_Campaign->SetItemTextStr(index, 12, strAttackList.c_str());
		}

		// defense 列表 信息
		{
			std::map<POSITION, ClanArmy*>* defenseHostList = campaign->getDefenseMemberList();

			std::string strDefenseList;
			getPosInfoStr(defenseHostList, &strDefenseList);

			listView_Campaign->SetItemTextStr(index, 13, strDefenseList.c_str());
		}
		
		

	}

	//-----------------------------------------------------------------------------
	Int PrintDialog::getPosInfoStr(std::map<POSITION, ClanArmy*>* posListInfo, std::string* outStr)
	{
		DYNAMIC_ASSERT(NULL != posListInfo);
		std::map<POSITION, ClanArmy*>::iterator iter = posListInfo->begin();
		
		int allNum = 0;
		
		
		std::string strPosInfo;
		strPosInfo.clear();

		for ( ; iter != posListInfo->end(); iter++)
		{
			if (iter->second->accountId <= 0)
			{
				continue;
			}

			std::string strAccountId;
			MGStrOp::toString(iter->second->accountId, strAccountId);

			std::string strIsLeave;
			if (iter->second->isLeave == true)
			{
				strIsLeave = "[离开]";
			}
			else
			{
				strIsLeave = "[在线]";
			}

			std::string strPos;
			MGStrOp::toString(iter->first + 1, strPos);
			strPosInfo = strPosInfo + "<Pos[" + strPos + "]: ";	//Pos[1]	格式

			
			strPosInfo = strPosInfo + strIsLeave;
			strPosInfo = strPosInfo + "[" + strAccountId + "]" + ">;";
			
			allNum++;
			
		}

		if (strPosInfo.empty())
		{
			strPosInfo = "空";
		}

		*outStr = strPosInfo;
		return allNum;
	}

	//-----------------------------------------------------------------------------
}