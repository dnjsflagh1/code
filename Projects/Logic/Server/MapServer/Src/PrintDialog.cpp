/******************************************************************************/
#include "stdafx.h"
#include "PrintDialog.h"
#include "../resource.h"

#include "MyListView.h"
#include "SWorldManager.h"
#include "PrintWindowsCfg.h"
/******************************************************************************/

namespace MG
{

	static BOOL CALLBACK MapDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static BOOL CALLBACK PlayerDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static BOOL CALLBACK PlayerCharacterDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

	
	//-----------------------------------------------------------------------------
	PrintDialog::PrintDialog()
		:mMapDlg(NULL)
		,mPlayerDlg(NULL)
		,mPlayerCharacterDlg(NULL)
	{
	}

	//-----------------------------------------------------------------------------
	PrintDialog::~PrintDialog()
	{
	}


	//-----------------------------------------------------------------------------
	BOOL CALLBACK MapDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		HINSTANCE hInst = GetModuleHandle("MapServer_d.dll");
#else
		HINSTANCE hInst = GetModuleHandle("MapServer.dll");
#endif

	
		// Map 的打印信息
		if(PrintWindowsCfg::getInstance().getPrintMap() == 1)
		{
			mMapDlg = ::CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_MAP), GetDesktopWindow(), MapDlgProc);
			ShowWindow(mMapDlg, SW_SHOW);
			std::string	strCaption = "MapServer【Map】";
			strCaption += "[";
			strCaption += __DATE__;
			strCaption += " ";
			strCaption += __TIME__;
			strCaption += "]";
			SetWindowText(mMapDlg, strCaption.c_str());

			HMENU hMenu = GetSystemMenu(mMapDlg, FALSE);
			EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);

			//设置事件
			mWindowProcMap = (WinProc)GetWindowLong((HWND)mMapDlg,GWL_WNDPROC);
			SetWindowLong((HWND)mMapDlg, GWL_WNDPROC, (LONG)(&windowMapMsg));
		}

		// Player 的打印信息
		if(PrintWindowsCfg::getInstance().getPrintPlayer() == 1)
		{
			mPlayerDlg = ::CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_PLAYER), GetDesktopWindow(), PlayerDlgProc);
			ShowWindow(mPlayerDlg, SW_SHOW);
			std::string	strCaption = "MapServer【Player】";
			strCaption += "[";
			strCaption += __DATE__;
			strCaption += " ";
			strCaption += __TIME__;
			strCaption += "]";
			SetWindowText(mPlayerDlg, strCaption.c_str());

			HMENU hMenu = GetSystemMenu(mPlayerDlg, FALSE);
			EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);

			//设置事件
			mWindowProcPlayer = (WinProc)GetWindowLong((HWND)mPlayerDlg,GWL_WNDPROC);
			SetWindowLong((HWND)mPlayerDlg, GWL_WNDPROC, (LONG)(&windowPlayerMsg));
		}

		// PlayerCharacter 的打印信息
		if(PrintWindowsCfg::getInstance().getPrintPlayerCharacter() == 1)
		{
			mPlayerCharacterDlg = ::CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_PLAYERCHARACTER), GetDesktopWindow(), PlayerCharacterDlgProc);
			ShowWindow(mPlayerCharacterDlg, SW_SHOW);
			std::string	strCaption = "MapServer【Character】";
			strCaption += "[";
			strCaption += __DATE__;
			strCaption += " ";
			strCaption += __TIME__;
			strCaption += "]";
			SetWindowText(mPlayerCharacterDlg, strCaption.c_str());

			HMENU hMenu = GetSystemMenu(mPlayerCharacterDlg, FALSE);
			EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);

			//设置事件
			mWindowProcPlayerCharacter = (WinProc)GetWindowLong((HWND)mPlayerCharacterDlg,GWL_WNDPROC);
			SetWindowLong((HWND)mPlayerCharacterDlg, GWL_WNDPROC, (LONG)(&windowPlayerCharacterMsg));
		}


	}

	//-----------------------------------------------------------------------------
	void PrintDialog::printMapRegionObj(MyListView* listView, Int index, SInstanceRegion* realRegion)
	{
#if 0
		SRegionObjectBase* regionBase;// = realRegion->getNewRegionObject();
		DYNAMIC_ASSERT(NULL != regionBase);

		std::string strInstanceType;
		if (ROT_MAP_DISTRIBUTION == regionBase->getRegionType())
		{
			strInstanceType = " 大地图";
		}
		else
		{
			switch(realRegion->getInstanceType())
			{
			case InstanceType_Null:
				{
					strInstanceType = "Null错误";
				}
				break;
			case InstanceType_PVE:
				{
					strInstanceType = "PVE冒险";
				}
				break;
			case InstanceType_PVP:
				{
					strInstanceType = "PVP对战";
				}
				break;
			case InstanceType_Atk:
				{
					strInstanceType = "攻城Atk";
				}
				break;
			case InstanceType_Tiro:
				{
					strInstanceType = "新 手Tiro  ";
				}
				break;
			case InstanceType_HomeLand:
				{
					strInstanceType = "家园HomeLand";
				}
				break;
			//case InstanceType_Maze:
			//	{
			//		strInstanceType = "迷宫Maze";
			//	}
			//	break;
			case InstanceType_Max:
				{
					strInstanceType = "Max错误";
				}
				break;
			default:
				{
					DYNAMIC_ASSERT(0);
				}
				break;
			}
		}
		


		std::string strPlayerList;
		Int playerSize;// = regionBase->getPrintPlayerStrList(strPlayerList);

		std::string strPlayerCharList;
		Int playerCharSize;// = regionBase->getPrintPlayerCharacterStrList(strPlayerCharList);

		listView->InsertItem(index);

		listView->SetItemTextU64(index, 0, regionBase->getRegionId());
		listView->SetItemTextU64(index, 1, realRegion->getInstanceUId());
		listView->SetItemTextStr(index, 2, strInstanceType.c_str());
		listView->SetItemTextU64(index, 3, realRegion->getCreatorAccountId());
		listView->SetItemTextU64(index, 4, regionBase->getData()->getMapId());
		listView->SetItemTextU64(index, 5, realRegion->getCampaignId());

		listView->SetItemTextInt(index, 6, playerSize);
		listView->SetItemTextStr(index, 7, strPlayerList.c_str());

		listView->SetItemTextInt(index, 8, playerCharSize);
		listView->SetItemTextStr(index, 9, strPlayerCharList.c_str());
#endif
	}

	//-----------------------------------------------------------------------------
	void PrintDialog::printMap()
	{
#if 0
		static MyListView listView_Map;
		listView_Map.GetListViewHandle(mMapDlg, IDC_LIST_MAP);
		listView_Map.DeleteAllItem();
		listView_Map.DeleteAllColum();

		listView_Map.InsertColumn(0, 	"RegionId",				70);
		listView_Map.InsertColumn(1, 	"mInstanceUId",			85);
		listView_Map.InsertColumn(2, 	"mInstanceType",		90);
		listView_Map.InsertColumn(3, 	"mCreatorAccountId",	110);
		listView_Map.InsertColumn(4, 	"MapId",				80);
		listView_Map.InsertColumn(5, 	"CampaignId", 			80);
		listView_Map.InsertColumn(6, 	"playerSize", 			80);
		listView_Map.InsertColumn(7, 	"playerList", 			120);
		listView_Map.InsertColumn(8, 	"playerCharSize",		100);
		listView_Map.InsertColumn(9,	"playerCharList",		120);
		
		Int index = 0;

#if 0
		//MapDistribution信息
		{
			std::map<RegionIdType, SBigRegionObject*>* allRegionObjectInstanceList = SWorldManager::getInstance().getBigMapDistributionRegionList();
			index = printBigRegionList(&listView_Map, allRegionObjectInstanceList, index);
		}

		//Place信息
		{
			std::map<RegionIdType, SBigRegionObject*>* allRegionObjectInstanceList = SWorldManager::getInstance().getBigPlaceRegionList();
			index = printBigRegionList(&listView_Map, allRegionObjectInstanceList, index);
		}

		//Tiro信息
		{
			std::map<RegionIdType, SBigRegionObject*>* allRegionObjectInstanceList = SWorldManager::getInstance().getBigTiroRegionList();
			index = printBigRegionList(&listView_Map, allRegionObjectInstanceList, index);
		}

		//Pve信息
		{
			std::map<RegionIdType, SBigRegionObject*>* allRegionObjectInstanceList = SWorldManager::getInstance().getBigPveRegionList();
			index = printBigRegionList(&listView_Map, allRegionObjectInstanceList, index);
		}

		//Home信息
		{
			std::map<RegionIdType, SBigRegionObject*>* allRegionObjectInstanceList = SWorldManager::getInstance().getBigHomeRegionList();
			index = printBigRegionList(&listView_Map, allRegionObjectInstanceList, index);
		}
#endif
#endif
	}

	Int PrintDialog::printBigRegionList(MyListView* listView_Map, std::map<RegionIdType, SBigRegionObject*>* allRegionObjectInstanceList, Int index)
	{
#if 0
		for (std::map<RegionIdType, SBigRegionObject*>::iterator iter = allRegionObjectInstanceList->begin();
			iter != allRegionObjectInstanceList->end(); ++iter)
		{
			//主城信息
			SBigRegionObject* tempRealRegionObjInRegion = iter->second;
			if (NULL != tempRealRegionObjInRegion)
			{
				SInstanceRegion* mainRealRegion;// = tempRealRegionObjInRegion->getMainInstanceRegion();

				if (NULL != mainRealRegion)
				{
					printMapRegionObj(listView_Map, index, mainRealRegion);
					++index;
				}
			}

			//副本信息
			std::map<InstanceIdType, SInstanceRegion*>* realRegionObjList = iter->second->getInstanceRegionList();

			for (std::map<InstanceIdType, SInstanceRegion*>::iterator iterInner = realRegionObjList->begin(); 
				iterInner != realRegionObjList->end(); ++iterInner)
			{
				printMapRegionObj(listView_Map, index, iterInner->second);
				++index;
			}
		}

		return index;
#endif
		return 0;
	}

	//-----------------------------------------------------------------------------
	void PrintDialog::printPlayerList()
	{
#if 0
		static MyListView listView_Player;
		listView_Player.GetListViewHandle(mPlayerDlg, IDC_LIST_PLAYER);
		listView_Player.DeleteAllItem();
		listView_Player.DeleteAllColum();

		listView_Player.InsertColumn(0, "AccountID", 75);
		listView_Player.InsertColumn(1, "FrontServerId", 80);
		listView_Player.InsertColumn(2, "ClientNetId", 70);
		listView_Player.InsertColumn(3, "ClanId", 70);
		listView_Player.InsertColumn(4, "RegionId", 70);
		listView_Player.InsertColumn(5, "InstanceUId", 70);
		listView_Player.InsertColumn(6, "PlayerCharacterList", 110);
		listView_Player.InsertColumn(7, "CanSeeByCamera", 50);
		listView_Player.InsertColumn(8, "MonsterAIList", 100);

#if 0
		std::map<AccountIdType, SPlayer*>* playerList = SWorldManager::getInstance().getPlayerList();
		Int index = 0;
		for (std::map<AccountIdType, SPlayer*>::iterator iter = playerList->begin(); iter != playerList->end(); ++iter, ++index)
		{
			listView_Player.InsertItem(index);


			SPlayer* player = iter->second;
			listView_Player.SetItemTextU64(index, 0, player->getAccountId());
			listView_Player.SetItemTextInt(index, 1, player->getFrontServerId());
			listView_Player.SetItemTextInt(index, 2, player->getClientNetIdInFrontServer());
			listView_Player.SetItemTextU64(index, 3, player->getClanId());
			if (NULL == player->getCurrentRealRegionObj() || NULL == player->getCurrentRegionObj())
			{
				listView_Player.SetItemTextInt(index, 4, -1);
				listView_Player.SetItemTextInt(index, 5, -1);
			}
			else
			{
				listView_Player.SetItemTextInt(index, 4, player->getCurrentRegionObj()->getRegionId());
				listView_Player.SetItemTextInt(index, 5, player->getCurrentRegionObj()->getInstanceUId());
			}
			

			//遍历武将id
			{
				std::string strPlayerCharacterIds;
				std::map<PlayerCharacterIdType, SCharacter*>* playerCharacterList = player->getPlayerCharacterList();
				std::map<PlayerCharacterIdType, SCharacter*>::iterator iter = playerCharacterList->begin();
				for ( ; iter != playerCharacterList->end(); iter++)
				{
					std::string id;
					MGStrOp::toString(iter->second->getID(), id);
					if (strPlayerCharacterIds.empty())
					{
						strPlayerCharacterIds = strPlayerCharacterIds + id;
					}
					else
					{
						strPlayerCharacterIds = strPlayerCharacterIds + ", " + id;
					}
				}

				if (strPlayerCharacterIds.empty())
				{
					strPlayerCharacterIds = "空";
				}

				listView_Player.SetItemTextStr(index, 6, strPlayerCharacterIds.c_str());
			}


			// CanSeeByCamera
			listView_Player.SetItemTextInt(index, 7, player->getCanSeeByCamera());

			//遍历MonsterAI
			{
				std::string strMonsterIds;
				std::vector<GameObjectIdType>* monsterList = player->getControlAIMonsterIdList();
				std::vector<GameObjectIdType>::iterator iter = monsterList->begin();
				for ( ; iter != monsterList->end(); iter++)
				{
					std::string id;
					MGStrOp::toString(*iter, id);
					if (strMonsterIds.empty())
					{
						strMonsterIds = strMonsterIds + id;
					}
					else
					{
						strMonsterIds = strMonsterIds + ", " + id;
					}
				}

				if (strMonsterIds.empty())
				{
					strMonsterIds = "空";
				}

				listView_Player.SetItemTextStr(index, 8, strMonsterIds.c_str());
			}
		
		}		//for
#endif
#endif
	}

	//-----------------------------------------------------------------------------
	void PrintDialog::printPlayerCharacterList()
	{
		static MyListView listView_PlayerCharacter;
		listView_PlayerCharacter.GetListViewHandle(mPlayerCharacterDlg, IDC_LIST_PLAYERCHARACTER);
		listView_PlayerCharacter.DeleteAllItem();
		listView_PlayerCharacter.DeleteAllColum();

		listView_PlayerCharacter.InsertColumn(0, 	"mId",					50);
		listView_PlayerCharacter.InsertColumn(1, 	"mName",				75);
		listView_PlayerCharacter.InsertColumn(2, 	"charClanId",			75);
		listView_PlayerCharacter.InsertColumn(3, 	"TemplateID",			75);
		listView_PlayerCharacter.InsertColumn(4, 	"mLevel", 				60);
		listView_PlayerCharacter.InsertColumn(5, 	"mPos.x", 				60);
		//List_PlayerCharacter_info.InsertColumn(6, 	"mPos.y", 				60);
		listView_PlayerCharacter.InsertColumn(6, 	"mPos.z", 				60);
		listView_PlayerCharacter.InsertColumn(7, 	"mRegionID",			75);
		listView_PlayerCharacter.InsertColumn(8, 	"mInstanceUId",			90);
		listView_PlayerCharacter.InsertColumn(9,	"charHP",				50);

#if 0
		std::map<PlayerCharacterIdType, SPlayerCharacter*>* playerCharacterList = SWorldManager::getInstance().getPlayerCharacterList();

		Int index = 0;
		for (std::map<PlayerCharacterIdType, SPlayerCharacter*>::iterator iter = playerCharacterList->begin(); 
			iter != playerCharacterList->end(); ++iter, ++index)
		{

			SPlayerCharacter* playerCharacter = iter->second;
			if (playerCharacter->getCanSeeByCamera() == false)
			{
				continue;
			}
			
			listView_PlayerCharacter.InsertItem(index);

			
			PlayerCharacterData* playerCharacterData = playerCharacter->getPlayerCharacterData();

			listView_PlayerCharacter.SetItemTextInt(index, 0, playerCharacterData->mId);
			listView_PlayerCharacter.SetItemTextStr16(index, 1, playerCharacterData->mName.c_str());
			listView_PlayerCharacter.SetItemTextInt(index, 2, playerCharacterData->charClanId);
			listView_PlayerCharacter.SetItemTextInt(index, 3, playerCharacterData->mCharacterTemplateID);
			listView_PlayerCharacter.SetItemTextInt(index, 4, playerCharacterData->mLevel);
			listView_PlayerCharacter.SetItemTextInt(index, 5, playerCharacterData->mPos.x);
			//List_PlayerCharacter_info.SetItemTextInt(index, 6, playerCharacterData->mPos.y);
			listView_PlayerCharacter.SetItemTextInt(index, 6, playerCharacterData->mPos.z);
			listView_PlayerCharacter.SetItemTextU64(index, 7, playerCharacterData->mRegionID);
			listView_PlayerCharacter.SetItemTextU64(index, 8, playerCharacterData->mInstanceUId);
			listView_PlayerCharacter.SetItemTextInt(index, 9, playerCharacterData->mHp);

		}		//end for()
#endif
	}

	LRESULT CALLBACK PrintDialog::windowMapMsg( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
	{
		switch(message)
		{
		case WM_COMMAND:
			{
				switch(wParam)
				{
				case IDOK:
					{
						//SWorldManager* manager = &(SWorldManager::getInstance());
						//std::map<AccountIdType, SPlayer*>* playerList = manager->getPlayerList();
						//for (std::map<AccountIdType, SPlayer*>::iterator iter = playerList->begin(); iter != playerList->end(); ++iter)
						//{
						//	SPlayerCharacter* playerCharacter = iter->second->getMainPlayerCharacter();
						//	playerCharacter->getSAttributeSystem()->print();
						//}

						if(PrintWindowsCfg::getInstance().getPrintMap() == 1)
						{
							PrintDialog::getInstance().printMap();
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

		return (CallWindowProc((WinProc)mWindowProcMap, hwnd, message, wParam, lParam));
	}
	LRESULT CALLBACK PrintDialog::windowPlayerMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch(message)
		{
		case WM_COMMAND:
			{
				int kk = 0;
				switch(wParam)
				{
				case IDOK:
					{
						if(PrintWindowsCfg::getInstance().getPrintPlayer() == 1)
						{
							PrintDialog::getInstance().printPlayerList();
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

		return (CallWindowProc((WinProc)mWindowProcPlayer, hwnd, message, wParam, lParam));
	}

	LRESULT CALLBACK PrintDialog::windowPlayerCharacterMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch(message)
		{
		case WM_COMMAND:
			{
				int kk = 0;
				switch(wParam)
				{
				case IDOK:
					{
						if(PrintWindowsCfg::getInstance().getPrintPlayerCharacter() == 1)
						{
							PrintDialog::getInstance().printPlayerCharacterList();
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

		return (CallWindowProc((WinProc)mWindowProcPlayerCharacter, hwnd, message, wParam, lParam));
	}

	//-----------------------------------------------------------------------------

}