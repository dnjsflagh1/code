//*************************************************************************************************************
#include "stdafx.h"
#include "DropItemManager.h"
#include "SItemPacketProcesser.h"
#include "SWorldManager.h"
#include "ItemRandomTemplate.h"
#include "ItemTemplate.h"
#include "ItemMoneyTemplate.h"
#include "ItemExpListCsv.h"

#include "SPlayerManager.h"
//*************************************************************************************************************
namespace MG
{
	DropItemManager::~DropItemManager()
	{
		clear();
	}

	void DropItemManager::setRegionObject(SRegionObjectBase* regionObj)
	{
		mRegionObject = regionObj;
	}

	SRegionObjectBase* DropItemManager::getRegionObject()
	{
		DYNAMIC_ASSERT(NULL != mRegionObject);
		return mRegionObject;
	}

	void DropItemManager::update()
	{
		for(std::map<U32, dropItemData*>::iterator pos = mMapDropItemData.begin(); pos != mMapDropItemData.end(); )
		{
			dropItemData* tempItem = pos->second;
			U64 curTime = GetCurrentTime();
			if(curTime >= tempItem->disappearTime)
			{
				//时间到了， 道具消失
				SItemPacketProcesser::getInstance().broadcastDropItemDisappear(tempItem, getRegionObject());
				mMapDropItemData.erase(pos++);
			}
			else
			{
				++pos;
			}
		}
	}

	void DropItemManager::handleRewardItemInRegion(SRegionObjectBase* regionObject, U32 groupItemId)
	{
		//DYNAMIC_ASSERT(NULL != regionObject);
		//std::map<PlayerCharacterIdType, SCharacter*>* playerCharacterList = regionObject->getPlayerCharacterList();
		//std::map<PlayerCharacterIdType, SCharacter*>::iterator iter = playerCharacterList->begin();
		//for ( ; iter != playerCharacterList->end(); ++iter)
		//{
		//	SPlayerCharacter* playerCharacter = (SPlayerCharacter*)iter->second;
		//	handleRewardItem(playerCharacter->getPlayerIdentifyInfo()->accountId, playerCharacter->getID(), groupItemId);
		//}
	}
	//---------------------------------------------------------------------------------------
	void DropItemManager::handleRewardItem(AccountIdType accountId, PlayerCharacterIdType playerCharId, U32 groupItemId )
	{
		SPlayerPtr player;
		if (false == SPlayerManager::getInstance().getPlayer(player, accountId))
		{
			return;
		}

		DYNAMIC_ASSERT(false == player.isNull());
		if ( player.isNull() )
			return;

		//记录奖励数据
		mMapRewardItem[playerCharId] = groupItemId;

		//将记录数据发送到客户端，客户端自己解析。
		SItemPacketProcesser::getInstance().sendRewardToClient(
				player->getFrontServerId(),
				player->getClientNetIdInFrontServer(),
				accountId, 
				groupItemId,
				true
			);	
	}
	//---------------------------------------------------------------------------------------
	void DropItemManager::handleDropItemMonster(U32 randItemId, SRegionObjectBase* regionObject, Vec3& pos, SCharacter* murderer)
	{
		//取出随机物品。
		std::vector<ItemNum> tempItemVector;
		ItemRandomTemplate::getInstance().getItemRandomInfo(randItemId, tempItemVector);
		
		//加到副本。
		dropItemData* pDropItemData = NULL;
		std::vector<dropItemData*> tempdropItemDataVector;
		
		static U32 index = 1;
		if (index > 40000)
		{
			index = 1;
		}
		for (std::vector<ItemNum>::iterator iter = tempItemVector.begin(); iter != tempItemVector.end(); ++iter)
		{
			//实例化掉落物品数据。
			pDropItemData = MG_NEW dropItemData;
			pDropItemData->index = index++;
			pDropItemData->itemTempId = (*iter).itemTemplate;
		
			const ItemInfo* itemInfo = ItemTemplate::getInstance().getItemInfo(pDropItemData->itemTempId);
			DYNAMIC_ASSERT(NULL != itemInfo);
			if (ITEM_TYPE_EXP == itemInfo->ItemType)
			{
				continue;
			}

			U64 disappearTime = 0;
			switch (itemInfo->getItemBaseRank())
			{
			case ITEM_RANK_WHITE:	//白装
				{
					disappearTime = GetCurrentTime() + 30*1000;	//白色品阶物品掉落后消失时间为30秒
				}
				break;
			case ITEM_RANK_GREEN:	//绿装
				{
					disappearTime = GetCurrentTime() + 2*60*1000;	//绿色品阶物品掉落后消失时间为2分钟

				}
				break;
			case ITEM_RANK_BLUE:	//蓝装
				{
					disappearTime = GetCurrentTime() + 5*60*1000;	//蓝色品阶物品掉落后消失时间为5分钟

				}
				break;
			case ITEM_RANK_PURPLE:	//紫装
				{
					disappearTime = GetCurrentTime() + 10*60*1000;	//紫色品阶物品掉落后消失时间为10分钟

				}
				break;
			default:
				{
					DYNAMIC_ASSERT(0);
				}
				break;
			}

			pDropItemData->disappearTime = disappearTime;
			pDropItemData->num = (*iter).num;
			//位置策略。
			pDropItemData->pos = Vec2(pos.x, pos.z);

			//填充到临时vector，用作同步用
			tempdropItemDataVector.push_back(pDropItemData);

			//填充到副本掉落物品表中。
			mMapDropItemData[pDropItemData->index] = pDropItemData;
		}

		//加经验， 临时
		checkMoneyAndAddExpToFrontServer(&tempItemVector, murderer);
		
		//同步掉落物品
		SItemPacketProcesser::getInstance().broadcastDropItemToClient(&tempdropItemDataVector, regionObject);
	}

	void DropItemManager::checkMoneyAndAddExpToFrontServer(std::vector<ItemNum>* tempVectorDropItem, SCharacter* playerCharacter)
	{
		//检查角色死亡,就不能的经验。
		if ( playerCharacter->isDead() ) return;

		for (std::vector<ItemNum>::iterator iter = tempVectorDropItem->begin(); iter != tempVectorDropItem->end(); )
		{
			U32 itemTempId = (*iter).itemTemplate;
			const ItemInfo* itemInfo = ItemTemplate::getInstance().getItemInfo(itemTempId);
			if (NULL == itemInfo)
			{
				++iter;
				continue;
			}

			if(itemInfo->ItemType != ITEM_TYPE_EXP)
			{
				++iter;
				continue;
			}

			const ItemExpListCsvInfo* itemExpInfo = ItemExpListCsv::getInstance().getInfoById(itemInfo->ItemListId);
			
			if (NULL != itemExpInfo)
			{
				//经验 【只给自己加经验】
				SItemPacketProcesser::getInstance().sendAddExpToFrontServer(itemInfo, playerCharacter,(*iter).num );
				//SItemPacketProcesser::getInstance().broadcastAddExpToFrontServer(itemInfo, regionObject,(*iter).num );
				iter = tempVectorDropItem->erase(iter);
			}
			else
			{
				 ++iter;
			}
		}
	}

	//---------------------------------------------------------------------------------------
	MG::Bool DropItemManager::getDropItemData( U32 index, U32& itemTmpId, U32& num )
	{
		std::map<U32, dropItemData*>::iterator iter = mMapDropItemData.find(index);
		if ( iter != mMapDropItemData.end() )
		{
			itemTmpId = iter->second->itemTempId;
			num = iter->second->num;

			MG_DELETE(iter->second);
			mMapDropItemData.erase(iter);
			return true;
		}
		return false;
	}
	//---------------------------------------------------------------------------------------
	MG::Bool DropItemManager::getRewardItem( PlayerCharacterIdType playerCharId )
	{
		std::map<PlayerCharacterIdType, U32>::iterator  iter = mMapRewardItem.find(playerCharId);
		if ( iter != mMapRewardItem.end() )
		{
			mMapRewardItem.erase(iter);
			return true;
		}
		return false;
	}
	//---------------------------------------------------------------------------------------
	void DropItemManager::clear()
	{
		mMapRewardItem.clear();
		std::map<U32, dropItemData*>::iterator front = mMapDropItemData.begin();
		std::map<U32, dropItemData*>::iterator back = mMapDropItemData.end();
		while (front != back)
		{
			MG_DELETE front->second;
			++front;
		}
		mMapDropItemData.clear();
	}
	//---------------------------------------------------------------------------------------
	void DropItemManager::handleCheckRewardItem( SPlayer* pSPlayer, PlayerCharacterIdType playerCharId, U32 groupItemId )
	{
		if ( getRewardItem( playerCharId ) )
		{
			SItemPacketProcesser::getInstance().sendRewardToFrontServer(
					pSPlayer->getClientNetIdInFrontServer(),
					pSPlayer->getFrontServerId(),
					playerCharId,
					groupItemId
				);
		}
		else
		{
			SItemPacketProcesser::getInstance().sendRewardToClient(
					pSPlayer->getFrontServerId(),
					pSPlayer->getClientNetIdInFrontServer(),
					pSPlayer->getAccountId(),
					groupItemId,
					false
				);
		}
	}
	//---------------------------------------------------------------------------------------
	void DropItemManager::handleCheckPickItem( SPlayerCharacter* pSPlayerCharacter, SPlayer* pSPlayer, PlayerCharacterIdType playerCharId, U32 index )
	{
		U32 tempItemId = 0;
		U32 tempNum = 0;

		if ( getDropItemData(index, tempItemId, tempNum) )
		{
			SItemPacketProcesser::getInstance().sendPickItemToFrontServer(
					pSPlayer->getClientNetIdInFrontServer(),
					pSPlayer->getFrontServerId(),
					playerCharId,
					tempItemId,
					tempNum
				);
			SItemPacketProcesser::getInstance().broadcastPickItem(
					tempItemId,
					tempNum,
					pSPlayerCharacter,
					index
				);
		}
	}
}