//***************************************************************************************************
#include "stdafx.h"
#include "UISkillOperate.h"
#include "CPlayerCharacter.h"
#include "CCharacter.h"
#include "CSkillOwnManager.h"
#include "SkillInfoList.h"
#include "ArtIconResCsv.h"
#include "CSkillObject.h"
#include "ClientMain.h"
#include "CCDManager.h"
#include "UISkillTips.h"
#include "CPlayer.h"
#include "CSceneManager.h"
#include "CharacterList.h"
#include "CTroopEntity.h"
#include "CharacterSkillTempLate.h"
#include "CCharacter.h"
#include "CItemManager.h"
#include "GenrealItem.h"
#include "PlayerItem.h"
#include "UIItemTips.h"
#include "UIAnyIcon.h"
#include "ItemPacketProcesser.h"
#include "GameJudge.h"

//***************************************************************************************************
#define UI_SKILL_OPERATE_NUM 8
#define UI_ITEM_OPERATE_NUM 4
//***************************************************************************************************
namespace MG
{
	GAMEOBJ_TYPE UISkillOperate::mCurrCharacterType = GOT_UNKNOWN;
	IdType UISkillOperate::mCurrCharacterID = 0;
	Int UISkillOperate::mCurrCharacterIndex = 0;
	CCharacter* UISkillOperate::mCurrCharacter = NULL;

	UISkillOperate::UISkillOperate()
	{

	}
	//----------------------------------------------------------------------------------------
	UISkillOperate::~UISkillOperate()
	{

	}
	//----------------------------------------------------------------------------------------
	void UISkillOperate::setEvent()
	{

		IconInfo tempInfo;
		Char8 temStr[32] = {0};
		IImage* pIcon = NULL;
	    Int i = 1;
        for (;i<= UI_SKILL_OPERATE_NUM;i++)
        {
           SprintF(temStr,"icon-%d",i);
		   pIcon =  getLayout()->getImage(temStr);
		   pIcon->getWidget()->setNeedToolTip(true);
		   pIcon->getWidget()->setMouseButtonClickEvent(onClickKeyNum);
		   pIcon->getWidget()->setToolTipsEvent(onEventToolTips);
		   pIcon->getWidget()->setMouseSetFocusEvent(onMouseSetFocus);
		   pIcon->getWidget()->setMouseLostFocusEvent(onMouseLostFocus);
		   //设置icon信息
		   tempInfo.group = ICON_GROUP_SHORTCUT_SKILL;
		   tempInfo.type = ICON_TYPE_SKILL;
		   pIcon->getWidget()->setUserData(tempInfo);
		   
        }
		//设置物品快捷栏
		for (Int i= 1; i<= UI_ITEM_OPERATE_NUM; i++)
		{
			SprintF(temStr,"icon_item-%d",i);
			pIcon = getLayout()->getImage(temStr);
			pIcon->getWidget()->setNeedToolTip(true);
			pIcon->getWidget()->setToolTipsEvent(onEventToolTips);
			pIcon->getWidget()->setMouseButtonClickEvent(onClickItemIcon);
			pIcon->getWidget()->setMouseSetFocusEvent(onMouseSetFocus);
			pIcon->getWidget()->setMouseLostFocusEvent(onMouseLostFocus);
			//设置icon信息
			tempInfo.group = ICON_GROUP_SHORTCUT_ITEM;
			tempInfo.type = ICON_TYPE_ITEM;
			pIcon->getWidget()->setUserData(tempInfo);

			SprintF(temStr,"text-%d", i);
			IWidget* pWidget = getLayout()->getWidget( temStr );
			if ( pWidget )
				pWidget->setCaption(L"");
		}

	}

	void UISkillOperate::onClickKeyNum( void* widget )
	{
		
		IWidget* iWidget = (IWidget*)widget;
		IconInfo* pIcon = iWidget->getUserData()->castType<IconInfo>();
		UISkillOperate::getInstance().onHandleClickSkillKeyNum( pIcon );

		
	}
	
	void UISkillOperate::onClickItemIcon(void* widget)
	{
	
		DYNAMIC_ASSERT(widget);
		IWidget* pIWidget = (IWidget*)widget;
		IAny* pIAny = pIWidget->getUserData();
		IconInfo* pIconInfo = pIAny->castType<IconInfo>();
		DYNAMIC_ASSERT(pIconInfo);

		if ( pIconInfo->dbID )
		{	
			//检查CD图片是否在转动
			Char8 tempChar[32] = "";
			Sprintf_s(tempChar, 32, "item_state-%d", pIconInfo->index);
			IWidget* pCDWidget = pIWidget->findWidget(tempChar);
			if ( pCDWidget->getImage()->getImageBroadcast() != MGIMAGE_BROADCAST_TYPE_NULL )
				return;
			UISkillOperate::getInstance().onHandleClickItem(pIconInfo);
		}
	}

	void UISkillOperate::onHandleClickItem(IconInfo* pIconInfo)
	{
		const ItemInfo* pInfo = ItemTemplate::getInstance().getItemInfo(pIconInfo->tempID);
		if ( CCDManager::getInstance().checkCD(CD_MASTER_TYPE_CHARACTER, mCurrCharacterID, pInfo->getItemUsePublicTimepieceId()) )
			return;
		if ( CCDManager::getInstance().checkCD(CD_MASTER_TYPE_CHARACTER, mCurrCharacterID, pInfo->getItemUseOwnerTimepieceId()) )
			return;

		//氏族,角色判断
        U32 clanJudeId = pInfo->getItemBaseClanJudgeID();
		U32 charJudeId = pInfo->getItemBaseCharacterJudgeID();
		CClan* tempClan = CPlayer::getInstance().getActiveClan();
		DYNAMIC_ASSERT_LOG(tempClan,"error: clan == NULL!");
		if (!tempClan)
			return;
		GAMEJUDGE_TYPE judgeType = GameJudge::getInstance().checkGameJudge(tempClan,NULL,mCurrCharacter,clanJudeId,charJudeId);
		if (judgeType != GAMEJUDGE_TYPE_SUCCESS)
		{
			CItemManager::getInstance().addGameJudgeErrorMsgForClient(judgeType);
            return;
		}
		  
		PlayerItem* pItem = CItemManager::getInstance().findItem(pIconInfo->dbID);
		if (pItem ==NULL)
		{
			return;
		}
		ItemPacketProcesser::getInstance().sendUseItem(pItem->getItemIndex(),pItem->getItemSiteType(),mCurrCharacterID);
		//addCD
		CCDManager::getInstance().addCD(
			CD_MASTER_TYPE_CHARACTER, 
			mCurrCharacterID, 
			pInfo->getItemUsePublicTimepieceId(),
			pInfo->getItemUsePublicTimepieceDelay(),
			pInfo->getItemUsePublicTimepieceDelay()
			);
	}

	void UISkillOperate::addSkillIcon( GAMEOBJ_TYPE characterType, IdType characterID, Int characterIndex )
	{
		mCurrCharacterType = characterType;
		mCurrCharacterID = characterID;
		mCurrCharacterIndex = characterIndex;

		Char8 tempStr[20] = "";

		clearSkillList();

		std::vector<UInt> skillList;
		getCharacterSkillList( characterType, characterID, skillList);


		IImage* pImage = NULL;
		IconInfo* pIconInfo = NULL;
        //icon标志位
		Int iconCount = 1;
		for(UInt i = 0; i < skillList.size(); ++i)
		{
			const SkillInfo* skillInfo = SkillInfoList::getInstance().getSkillInfo(skillList[i]);
			if(!skillInfo)
			{
				continue;
			}
            if (skillInfo->skillShowType == SKILL_SHOW_TYPE_TWO)
            {
				continue;
            }
			SkillBaseInfo* skillBaseInfo = skillInfo->skillInfo;
			if(!skillBaseInfo)
			{
				continue;
			}

			const ArtIconResCsvInfo* iconInfo = ArtIconResCsv::getInstance().getIconArtResInfo(skillBaseInfo->artIconId);
			if(iconInfo)
			{
				sprintf_s(tempStr, sizeof(tempStr), "icon-%d", iconCount);
				pImage = getLayout()->getImage(tempStr);
				pIconInfo = pImage->getWidget()->getUserData()->castType<IconInfo>();
				DYNAMIC_ASSERT(pIconInfo);
				pIconInfo->resouceName = iconInfo->ResName;
				pIconInfo->groupName = iconInfo->GroupName;
				pIconInfo->itemName = iconInfo->ItemName;
				
				//pIconInfo->tempID = i;         //绑定技能在角色技能表中的索引号
				pIconInfo->tempID =skillList[i];          //绑定技能ID
				pIconInfo->index = iconCount;   //绑定icon索引号

				getLayout()->getImage(tempStr)->setTexture(iconInfo->ResName, iconInfo->GroupName, iconInfo->ItemName);
				//hide
				sprintf_s(tempStr, sizeof(tempStr), "state-%d", iconCount + 1);
				getLayout()->getImage(tempStr)->getWidget()->findWidget(tempStr)->setVisible(false);
				iconCount++;
			}
		}

	}
	//--------------------------------------------------------------------------------------
	void UISkillOperate::addCharItemIcon(GAMEOBJ_TYPE characterType, IdType characterID, Int characterIndex)
	{
		clearItemList();
		GenrealItem* pGenrealItem = CItemManager::getInstance().getGenrealItem(characterID);
		if (pGenrealItem)
		{
			const std::map<IdType, PlayerItem*>* pMapGenrealItem = pGenrealItem->getPlayerItemMap();
			std::map<IdType, PlayerItem*>::const_iterator front = pMapGenrealItem->begin();
			std::map<IdType, PlayerItem*>::const_iterator back = pMapGenrealItem->end();
		
			while (front != back)
			{
				addCharItem(front->second);

				++front;
			}
		}
	}
	//--------------------------------------------------------------------------------------
	void UISkillOperate::addCharItem( PlayerItem* pItem )
	{
		Char8 temp[24] = "";
		U32 index = pItem->getItemIndex();
		sprintf_s(temp, 24, "icon_item-%d", index);
		IImage* pIcon = getLayout()->getImage( temp );

		IconInfo*  pIconInfo = pIcon->getWidget()->getUserData()->castType<IconInfo>();
		DYNAMIC_ASSERT(pIconInfo);

		const ItemInfo* iteminfo = pItem->getItemInfo();
		DYNAMIC_ASSERT(iteminfo);

		if (pIcon)
		{
			pIconInfo->clear();
			pIconInfo->dbID = pItem->getItemDBID();
			pIconInfo->tempID = pItem->getItemTempID();
			pIconInfo->index = index;
			iteminfo->getItemBaseIconResouce(pIconInfo->resouceName, pIconInfo->groupName, pIconInfo->itemName);
			pIcon->setTexture(pIconInfo->resouceName, pIconInfo->groupName, pIconInfo->itemName);
			pIcon->getWidget()->setUserData(*pIconInfo);
		}

		//text
		if ( pItem->getItemNum() > 1 )
		{
			sprintf_s(temp, 24, "text-%d", index);
			IWidget* pWidget = getLayout()->getWidget(temp);
			DYNAMIC_ASSERT(pWidget);
			Char16 tempNum[16] = L"";
			swprintf_s( tempNum, 16, L"%d", pItem->getItemNum() );
			pWidget->setCaption(tempNum);
		}

		//CD
		if (iteminfo->ItemType != ITEM_TYPE_USE_GENERAL)
		{
			return;
		}

		//只有使用类道具才有cd
		sprintf_s(temp, 24, "item_state-%d", index);
		IWidget* pChildWidget = pIcon->getWidget()->findWidget(temp);
		//先找到CD的时间。
		CDTimerData* pCDTimerData = CCDManager::getInstance().findCD(
			CD_MASTER_TYPE_CHARACTER, 
			mCurrCharacterID, 
			iteminfo->getItemUseOwnerTimepieceId()
			);
		if ( pCDTimerData == NULL )
		{
			pCDTimerData = CCDManager::getInstance().findCD(
				CD_MASTER_TYPE_CHARACTER, 
				mCurrCharacterID, 
				iteminfo->getItemUsePublicTimepieceId()
				);
		}
		//再加CD
		if ( pCDTimerData )
		{
			Int tempLastTime = pCDTimerData->mLastTime + pCDTimerData->mStartTime - MGTimeOp::getCurrTick(); 
			if ( tempLastTime > 0 )
				pChildWidget->getImage()->setImageBroadcast(
				MGIMAGE_BROADCAST_TYPE_ONCE, 
				tempLastTime, 
				pCDTimerData->mTotalTime
				);
		}


	}
	//--------------------------------------------------------------------------------------
	void UISkillOperate::deleteCharItem( U32 index )
	{
		//清空图片。
		Char8 temp[24] = "";
		sprintf_s(temp, 24, "icon_item-%d", index);
		IImage* pIcon = getLayout()->getImage( temp );
		if (pIcon)
		{
			IconInfo*  pIconInfo = pIcon->getWidget()->getUserData()->castType<IconInfo>();
			pIcon->setTexture("", "", "");
			pIconInfo->clear();
			pIcon->getWidget()->setUserData(*pIconInfo);
		}

		//关掉CD
		sprintf_s(temp, 24, "item_state-%d", index);
		IWidget* pChildWidget = pIcon->getWidget()->findWidget(temp);
		pChildWidget->getImage()->setImageBroadcast(MGIMAGE_BROADCAST_TYPE_NULL, 0, 0);

		//清空文字
		sprintf_s(temp, 24, "text-%d", index);
		IWidget* pWidget = getLayout()->getWidget( temp );	
		if ( pWidget )
			pWidget->setCaption(L"");
		//关掉高亮显示
		
		
		Sprintf_s(temp, 24, "item-highlight%d", index);
		IWidget* pHighWidget = getLayout()->getWidget(temp);
		DYNAMIC_ASSERT(pHighWidget);
		pHighWidget->setVisible(false);
	}
	//--------------------------------------------------------------------------------------
	void UISkillOperate::updateCharItem( U32 index, U32 num )
	{
		Char8 temp[24] = "";
		sprintf_s(temp, 24, "text-%d", index);
		IWidget* pWidget = getLayout()->getWidget( temp );
		if (pWidget)
		{
			Char16 tempWStr[24] = L"";
			if ( num > 1 )
			{  
				swprintf_s(tempWStr, 24, L"%d", num);
				pWidget->setCaption(tempWStr); 
			}
			else
				pWidget->setCaption(tempWStr);
		}
	}
	//--------------------------------------------------------------------------------------
	void UISkillOperate::clearItemList()
	{
		Char8 temp[24] = "";
		for (Int i = 1; i <= UI_ITEM_OPERATE_NUM; i++)
		{
			SprintF(temp,"icon_item-%d",i);
			IImage* pIcon = getLayout()->getImage( temp );
			if ( pIcon )
			{
				IconInfo*  pIconInfo = pIcon->getWidget()->getUserData()->castType<IconInfo>();
				pIcon->setTexture("", "", "");
				pIconInfo->clear();
				pIcon->getWidget()->setUserData(*pIconInfo);
			}
			SprintF(temp,"text-%d", i);
			IWidget* pWidget = getLayout()->getWidget( temp );
			if ( pWidget )
				pWidget->setCaption(L"");
		} 
	}
	//--------------------------------------------------------------------------------------
	void UISkillOperate::clearSkillList()
	{
		Char8 temp[24] = "";
		for (Int i=1; i <= UI_SKILL_OPERATE_NUM; i++)
		{
			SprintF(temp,"icon-%d",i);
			IImage* pIcon = getLayout()->getImage( temp );
			if ( pIcon )
			{
				IconInfo*  pIconInfo = pIcon->getWidget()->getUserData()->castType<IconInfo>();
				pIcon->setTexture("", "", "");
				pIconInfo->clear();
				pIcon->getWidget()->setUserData(*pIconInfo);
			}
		} 
	}
	//--------------------------------------------------------------------------------------
	void UISkillOperate::notifyUIAddCD( U32 cdId, U32 cdtime, U32 totalTime, PlayerCharacterIdType characterId /*= 0 */ )
	{
		Char8 tempStr[32] = "";
		IImage* pImage = NULL;
		IWidget* pWidget = NULL;
		IWidget* pChildWidget = NULL;
		IconInfo* pIconInfo = NULL;
		const ItemInfo* pItemInfo = NULL;
		//道具
		for (Int i=1; i <= UI_ITEM_OPERATE_NUM; i++)
		{
			Sprintf_s(tempStr, 32, "icon_item-%d", i);
			pWidget = getLayout()->getWidget(tempStr);

			//获得icon信息
			pIconInfo = pWidget->getUserData()->castType<IconInfo>();
			DYNAMIC_ASSERT(pIconInfo);
			if ( pIconInfo->tempID == 0 )
				continue;
			//获得道具id
			pItemInfo = ItemTemplate::getInstance().getItemInfo(pIconInfo->tempID);
			DYNAMIC_ASSERT(pItemInfo);
			if ( pItemInfo->getItemBaseItemType() == ITEM_TYPE_USE_GENERAL )
			{
				Sprintf_s(tempStr, 32, "item_state-%d", i);
				pChildWidget = pWidget->findWidget(tempStr);
				if ( pItemInfo->getItemUseOwnerTimepieceId() == cdId )
				{	
					pChildWidget->getImage()->setImageBroadcast(MGIMAGE_BROADCAST_TYPE_ONCE, cdtime, totalTime);
				}
				if ( pItemInfo->getItemUsePublicTimepieceId() == cdId )
				{	
					if ( pChildWidget->getImage()->getImageBroadcast() == MGIMAGE_BROADCAST_TYPE_NULL )
						pChildWidget->getImage()->setImageBroadcast(MGIMAGE_BROADCAST_TYPE_ONCE, cdtime, totalTime);
				}
			}
		}
		//技能
		cdtime = cdtime;
		totalTime = totalTime;
		SkillData* skillData = NULL;
		SkillInfo* skillInfo =NULL;
		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = NULL;

		std::vector<UInt> skillList;
		getCharacterSkillList( mCurrCharacterType, mCurrCharacterID, skillList);

		for (UInt i = 0; i< skillList.size(); i++)
		{
			sprintf_s(tempStr, 32, "icon-%d", i+1);
			pWidget = getLayout()->getWidget(tempStr);
			
			//获得icon信息
			pIconInfo = pWidget->getUserData()->castType<IconInfo>();
			DYNAMIC_ASSERT(pIconInfo);

			if(pIconInfo->tempID == 0)
			{
				continue;
			}

			skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(pIconInfo->tempID);
			if(!skillInfo)
			{
				continue;
			}

			if(skillInfo->skillShowType == SKILL_SHOW_TYPE_TWO)
			{
				continue;
			}

			initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				continue;
			}
			if (initiativeSkillBasicInfo->publicTimepieceId == cdId )
			{
				/*公共CD 需要检查同一组的CD状态。
				没有在CD的，添加CD 判断是否属于*/
				sprintf_s(tempStr,32,"state-%d",i+1);
				pChildWidget = pWidget->findWidget(tempStr);
                if (pChildWidget->getImage()->getImageBroadcast() == MGIMAGE_BROADCAST_TYPE_NULL)
                {
					pChildWidget->setVisible(true);
					pChildWidget->getImage()->setImageBroadcast(MGIMAGE_BROADCAST_TYPE_ONCE,cdtime,totalTime);
                }
			}
			if (initiativeSkillBasicInfo->ownerTimepieceId == cdId)
			{
				sprintf_s(tempStr,32,"state-%d",i+1);
				pChildWidget = pWidget->findWidget(tempStr);
				pChildWidget->setVisible(true);
				pChildWidget->getImage()->setImageBroadcast(MGIMAGE_BROADCAST_TYPE_ONCE,cdtime,totalTime);		
			}		
			
		}


	}
	//--------------------------------------------------------------------------------------
	void UISkillOperate::notifyUIDeleteCD( U32 cdid, PlayerCharacterIdType characterId /*= 0 */ )
	{
		Char8 tempStr[32] = "";
		IWidget* pWidget = NULL;
		IWidget* pChildWidget = NULL;
		IconInfo* pIconInfo = NULL;
		const ItemInfo* pItemInfo = NULL;
		
		//道具。
		for (Int i=1; i <= UI_ITEM_OPERATE_NUM; i++)
		{
			Sprintf_s(tempStr, 32, "icon_item-%d", i);
			pWidget = getLayout()->getWidget(tempStr);

			//获得icon信息
			pIconInfo = pWidget->getUserData()->castType<IconInfo>();
			DYNAMIC_ASSERT(pIconInfo);
			//获得道具id
			pItemInfo = ItemTemplate::getInstance().getItemInfo(pIconInfo->tempID);
			DYNAMIC_ASSERT(pItemInfo);
			//删除CD
			if ( pItemInfo->getItemBaseItemType() == ITEM_TYPE_USE_GENERAL )
			{
				Sprintf_s(tempStr, 32, "item_state-%d", i);
				pChildWidget = pWidget->findWidget(tempStr);
				if ( pItemInfo->getItemUseOwnerTimepieceId() == cdid )
					pChildWidget->getImage()->setImageBroadcast(MGIMAGE_BROADCAST_TYPE_NULL, 0, 0);
			}
		}

		SkillData* skillData = NULL;
		SkillInfo* skillInfo =NULL;
		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = NULL;

		std::vector<UInt> skillList;
		getCharacterSkillList( mCurrCharacterType, mCurrCharacterID, skillList);

		for (UInt i = 0; i < skillList.size(); i++)
		{
			sprintf_s(tempStr, 32, "icon-%d", i+1);
			pWidget = getLayout()->getWidget(tempStr);

			//获得icon信息
			pIconInfo = pWidget->getUserData()->castType<IconInfo>();
			DYNAMIC_ASSERT(pIconInfo);

			if(pIconInfo->tempID == 0)
			{
				continue;
			}

			skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(pIconInfo->tempID);
			if(!skillInfo)
			{
				continue;
			}

			if(skillInfo->skillType == SKT_PASSIVENESS)
			{
				continue;
			}

			initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				continue;
			}
			
			if (initiativeSkillBasicInfo->ownerTimepieceId == cdid)
			{
				sprintf_s(tempStr,32,"state-%d",i+1);
				pChildWidget = pWidget->findWidget(tempStr);
				pChildWidget->getImage()->setImageBroadcast(MGIMAGE_BROADCAST_TYPE_NULL, 0, 0);
				
			}
		}

	}
	//--------------------------------------------------------------------------------------
	void UISkillOperate::onEventToolTips( void* pWidget, Bool isShow, Int left, Int top )
	{
         DYNAMIC_ASSERT(pWidget);
		 IWidget* pIcon = (IWidget*)pWidget;
		 IAny* pAny = pIcon->getUserData();
		 DYNAMIC_ASSERT(pAny);
		 IconInfo* pInfo = pAny->castType<IconInfo>();
		 DYNAMIC_ASSERT(pInfo);

		// std::vector<UInt> skillList;
		// getCharacterSkillList( UISkillOperate::mCurrCharacterType, UISkillOperate::mCurrCharacterID, skillList);

		 if(pInfo->tempID == 0)
		 {
			return;
		 }

		 UISkillOperate::getInstance().onHandleTips(isShow,pInfo,pIcon->getAbsoluteCoord());  
	}
	//--------------------------------------------------------------------------------------
	
	//--------------------------------------------------------------------------------------
	void UISkillOperate::onHandleTips( Bool isShow, IconInfo* pIconInfo, CoordI coord )
	{
		if ( isShow == false )
		{
			switch (pIconInfo->type)
			{
			case ICON_TYPE_ITEM:
				UIItemTips::getInstance().closeGui();
				break;
			case ICON_TYPE_SKILL:
				UISkillTips::getInstance().closeGui();
				break;
			default:    
				break;
			}
		}
		else
		{
			switch (pIconInfo->type)
			{
			case ICON_TYPE_ITEM:
				{
					PlayerItem* pItem = CItemManager::getInstance().findItem(pIconInfo->dbID);
					DYNAMIC_ASSERT(pItem);
					UIItemTips::getInstance().openItemTips(pItem, coord);
				}
				break;
			case ICON_TYPE_SKILL:  
				{
					CPlayerCharacter* pCharacter = CPlayer::getInstance().getActiveClan()->getPlayerCharacter(mCurrCharacterID);
					//DYNAMIC_ASSERT(pCharacter);
					UISkillTips::getInstance().openSkillTips(pIconInfo, coord, pCharacter);
				}
				break;
			default:    
				break;
			}
		}
	}
	//--------------------------------------------------------------------------------------
	void UISkillOperate::onMouseSetFocus( void* widget,void* param )
	{
		if (widget)
		{
			IWidget* pWidget = (IWidget*)widget;
			IconInfo* pIcon = pWidget->getUserData()->castType<IconInfo>();
			DYNAMIC_ASSERT(pIcon);

			std::vector<UInt> skillList;
			getCharacterSkillList( UISkillOperate::mCurrCharacterType, UISkillOperate::mCurrCharacterID, skillList);

			if(pIcon->tempID == 0)
			{
				return;
			}
	
			UISkillOperate::getInstance().onHandleMouseSetFocus(pIcon);  
		}

	}
	//--------------------------------------------------------------------------------------
	void UISkillOperate::onMouseLostFocus( void* widget,void* param )
	{
		if (widget)
		{
			IWidget* pWidget = (IWidget*)widget;
			IconInfo* pIcon = pWidget->getUserData()->castType<IconInfo>();
			DYNAMIC_ASSERT(pIcon);
		
			std::vector<UInt> skillList;
			getCharacterSkillList( mCurrCharacterType, mCurrCharacterID, skillList);

			if(pIcon->tempID == 0)
			{
				return;
			}

			UISkillOperate::getInstance().onHandleMouseLostFocus(pIcon);
		}

	}
	//--------------------------------------------------------------------------------------
	void UISkillOperate::onHandleMouseSetFocus( IconInfo* pIcon  )
	{
		IWidget* pHighWidget = NULL;
		Char8 tempChar[32] = "";
		switch (pIcon->type)
		{
		case ICON_TYPE_ITEM:
			{
				Int index = pIcon->index;
				Sprintf_s(tempChar, 32, "item-highlight%d", index);
				pHighWidget = getLayout()->getWidget(tempChar);
			}
			break;
		case ICON_TYPE_SKILL:
			{
				Str8 highlight = "skill-highlight%d";
				Int index = pIcon->index;
				sprintf_s(tempChar,32,highlight.c_str(),pIcon->index);
				pHighWidget = getLayout()->getWidget(tempChar);
			}
			break;
		default:    
			break;
		}
		
		DYNAMIC_ASSERT(pHighWidget);
		pHighWidget->setVisible(true);

	}
	//--------------------------------------------------------------------------------------
	void UISkillOperate::onHandleMouseLostFocus( IconInfo* pIcon )
	{
		IWidget* pHighWidget = NULL;
		Char8 tempChar[32] = "";
		switch (pIcon->type)
		{
		case ICON_TYPE_ITEM:
			{
				Int index = pIcon->index;
				Sprintf_s(tempChar, 32, "item-highlight%d", index);
				pHighWidget = getLayout()->getWidget(tempChar);
			}
			break;
		case ICON_TYPE_SKILL:
			{
				Str8 highlight = "skill-highlight%d";
				Int index = pIcon->index;
				sprintf_s(tempChar,32,highlight.c_str(),index);
				pHighWidget = getLayout()->getWidget(tempChar);
			}
			break;
		default:    
			break;
		}

		DYNAMIC_ASSERT(pHighWidget);
		pHighWidget->setVisible(false);
	}

	//--------------------------------------------------------------------------------------
	void UISkillOperate::getCharacterSkillList( GAMEOBJ_TYPE characterType, IdType characterID, std::vector<UInt>& skillList )
	{
		skillList.clear();

		if(characterType == GOT_PLAYERCHARACTER)
		{
			CPlayerCharacter* playerCharacter = CPlayer::getInstance().getActiveClan()->getPlayerCharacter(characterID);
			mCurrCharacter = static_cast<CCharacter*>(playerCharacter);
			if(!playerCharacter)
			{
				return;
			}

			CSkillOwnManager* skillOwnManager = playerCharacter->getSkillOwnManager();
			if(!skillOwnManager)
			{
				return;
			}

			IdType skillId = 0;
			for(UInt i = 0; i < skillOwnManager->getOwnSkillNum(); ++i)
			{
				skillId = skillOwnManager->getOwnerSkillByIndex(i);
				if(skillId == 0)
				{
					continue;
				}

				skillList.push_back(skillId);
			}

		}
		else if(characterType == GOT_SOLDIER)
		{
			CTroopEntity* troopObject = CSceneManager::getInstance().getTroopEntity(characterID);
			if(!troopObject)
			{
				return;
			}

			const CharacterTempInfo* characterTempInfo = CharacterTemplate::getInstance().getCharacterTempInfo(troopObject->getDynamicData()->mCharacterTemplateID);
			if(!characterTempInfo)
			{
				return;
			}

			CharSkillInfo* charSkillInfo = (CharSkillInfo*)CharacterSkillTemplate::getInstance().getCharSkillInfo(characterTempInfo->getCharacterCharacterSkillId(0));
			if(!charSkillInfo)
			{
				return;
			}

			SkillInfo* skillInfo = NULL;
			for(UInt i = 0; i < CHAR_SKILL_NUM; ++i)
			{
				skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(charSkillInfo->CharSkillList[i]);
				if(!skillInfo)
				{
					continue;
				}
				
				skillList.push_back(skillInfo->skillId);
			}
		}
	}
	//--------------------------------------------------------------------------------------
	CCharacter* UISkillOperate::getCurrCharacter()
	{
       return mCurrCharacter;

	}
	//--------------------------------------------------------------------------------------
	void UISkillOperate::updateKeyInput()
	{
		IconInfo* pIcon = NULL;
		if ( ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_1 ) )
		{
             pIcon = getSkillIconInfo(1);
			 if (pIcon)
			 {
                 onHandleClickSkillKeyNum(pIcon);
			 }
		}
		else if ( ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_2 ) )
		{
			pIcon = getSkillIconInfo(2);
			if (pIcon)
			{
				onHandleClickSkillKeyNum(pIcon);
			}

		}
		else if ( ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_3 ) )
		{
			pIcon = getSkillIconInfo(3);
			if (pIcon)
			{
				onHandleClickSkillKeyNum(pIcon);
			}

		}
		else if ( ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_4 ) )
		{
			pIcon = getSkillIconInfo(4);
			if (pIcon)
			{
				onHandleClickSkillKeyNum(pIcon);
			}

		}
		else if ( ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_5 ) )
		{
			pIcon = getSkillIconInfo(5);
			if (pIcon)
			{
				onHandleClickSkillKeyNum(pIcon);
			}

		}
		else if ( ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_6 ) )
		{
			pIcon = getSkillIconInfo(6);
			if (pIcon)
			{
				onHandleClickSkillKeyNum(pIcon);
			}

		}
		else if ( ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_7 ) )
		{
			pIcon = getSkillIconInfo(7);
			if (pIcon)
			{
				onHandleClickSkillKeyNum(pIcon);
			}

		}
		else if ( ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_8 ) )
		{
			pIcon = getSkillIconInfo(8);
			if (pIcon)
			{
				onHandleClickSkillKeyNum(pIcon);
			}

		}
		//物品快捷键的操作
		if ( ClientMain::getInstance().getEngine()->input()->isKeyReleased(KC_F1))
		{
			pIcon = getItemIconInfo(1);
			if (pIcon)
			{
				onHandleClickItem(pIcon);
			}
		}
		else if ( ClientMain::getInstance().getEngine()->input()->isKeyReleased(KC_F2))
		{
			pIcon = getItemIconInfo(2);
			if (pIcon)
			{
				onHandleClickItem(pIcon);
			}
		}
		else if ( ClientMain::getInstance().getEngine()->input()->isKeyReleased(KC_F3))
		{
			pIcon = getItemIconInfo(3);
			if (pIcon)
			{
				onHandleClickItem(pIcon);
			}
		}
		else if ( ClientMain::getInstance().getEngine()->input()->isKeyReleased(KC_F4))
		{
			pIcon = getItemIconInfo(4);
			if (pIcon)
			{
				onHandleClickItem(pIcon);
			}
		}
		
	}
	//--------------------------------------------------------------------------------------
	IconInfo* UISkillOperate::getItemIconInfo( Int index )
	{
		IconInfo* pIcon = NULL;
		if (index < 1 || index > UI_ITEM_OPERATE_NUM)
			return NULL;


		Char8 temStr[32] = {0};
		SprintF(temStr,"icon_item-%d",index);
		IImage* pImage =  getLayout()->getImage(temStr);
		DYNAMIC_ASSERT(pImage);
		pIcon = pImage->getWidget()->getUserData()->castType<IconInfo>();
		if (pIcon->tempID == 0)
		{
			return NULL;
		}
		else
		{
			return pIcon;
		}
	}
	//--------------------------------------------------------------------------------------
	IconInfo* UISkillOperate::getSkillIconInfo( Int index )
	{
		IconInfo* pIcon = NULL;
		if (index < 1 || index > UI_SKILL_OPERATE_NUM)
		  return NULL;
        
		Char8 temStr[32] = {0};
		SprintF(temStr,"icon-%d",index);
		IImage* pImage =  getLayout()->getImage(temStr);
		DYNAMIC_ASSERT(pImage);
		pIcon = pImage->getWidget()->getUserData()->castType<IconInfo>();
		if (pIcon->tempID == 0)
		{
			return NULL;
		}
		else
		{
			return pIcon;
		}
	}
	//--------------------------------------------------------------------------------------
	void UISkillOperate::onHandleClickSkillKeyNum( IconInfo* pIcon )
	{
		std::vector<UInt> skillList;
		getCharacterSkillList( UISkillOperate::mCurrCharacterType, UISkillOperate::mCurrCharacterID, skillList );

		if(skillList.size() == 0)
		{
			return;
		}

		if(pIcon->tempID == 0)
		{
			return;
		}

		GameObjectOpCtrl::getInstance().requestUseSkill(pIcon->tempID, mCurrCharacterType, mCurrCharacterID, mCurrCharacterIndex);
	}
	//--------------------------------------------------------------------------------------
	void UISkillOperate::update(Flt delta)
	{
		if (ClientMain::getInstance().getGui()->isKeyCanHoldUI())
		    return;
		
		if (this->isOpen())
		{
			updateKeyInput();
		}
	}
	//--------------------------------------------------------------------------------------
	void UISkillOperate::restore()
	{
		//清空物品栏
		clearItemList();
	}
}