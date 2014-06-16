//***************************************************************************************************
#include "stdafx.h"
#include "SItemPacketProcesser.h"
#include "SWorldManager.h"
#include "SPlayer.h"
#include "MapServerMain.h"
#include "SPlayerCharacter.h"
#include "ThreadTaskManager.h"
#include "SCDManager.h"
#include "DropItemManager.h"
#include "NetTranspondPacketProcesser.h"
#include "ItemMoneyTemplate.h"
#include "ItemExpListCsv.h"
#include "SSceneGridManager.h"
#include "SBuffManager.h"
//***************************************************************************************************
namespace MG
{
    MG::Bool SItemPacketProcesser::processFrontServerPacket( I32 id, NetEventRecv* packet )
    {
        if ( packet->getChannel() == GNPC_ITEM )
        {
        	GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

        	switch (data->type)
        	{
        	case PT_ITEM_F2M_CHANGE_EQUIP:
        		recvChangeEquip( id , (PT_ITEM_F2M_CHANGE_EQUIP_DATA*)data->data);
        		break;
            case PT_ITEM_F2M_EQUIP_LIST:
				{
#ifdef MULTI_THREAD
					ThreadTaskManager::getInstance().addJumpRegionTask(packet, id);
#else
					recvEquipList(id, (PT_ITEM_F2M_EQUIP_LIST_DATA*)(data->data));
#endif
				}
                break;
            case PT_ITEM_F2M_USE_ITEM:
                recvUseItem(id, (PT_ITEM_F2M_USE_ITEM_DATA*)(data->data));
                break;
			case PT_ITEM_C2M_ATFD_REWARD:
				recvRewardItemFromClient(id, (PT_ITEM_C2M_ATFD_REWARD_DATA*)(data->data));
				break;
			case PT_ITEM_F2M_PICK_ITEM:
				recvPickItem(id, (PT_ITEM_F2M_PICK_ITEM_DATA*)(data->data));
				break;
			default:
				DYNAMIC_ASSERT(0);
				break;
        	}

        	return true;
        }
        return false;
    }
    //-----------------------------------------------------------------------------------
    void SItemPacketProcesser::broadcastEquipList( SPlayerCharacter* sender, SRegionObjectBase* region, Bool isFilterSelf )
    {
        if ( sender->getEquipItem()->checkIsEmpty() )
            return;

        NetTranspondSendDataBufferPtr dataPtr;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

        GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
        if(packet)
        {
            packet->type = PT_ITEM_M2C_EQUIP_LIST;
            packet->channel = GNPC_ITEM;

            PT_ITEM_M2C_EQUIP_LIST_DATA* sendData = (PT_ITEM_M2C_EQUIP_LIST_DATA*)packet->data;
            if(sendData)
            {
                sendData->charid = sender->getID();
                sender->getEquipItem()->getEquipItemList(sendData->equipId);
                SRegionObjectBase* tempRegion = 0;//sender->getCurrentRegionObject();

				PlayerIdType playeridtype = 0;
				if ( isFilterSelf )
				{
					playeridtype = sender->getAccountId();
				}
				if ( tempRegion )
				{
	//				NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize + PT_ITEM_M2C_EQUIP_LIST_DATA_INFO::dataSize, 
	//					sender->getSceneObjectInSceneGridsManager()->currSceneGrid, NULL, tempRegion, playeridtype);
				}
            }
        }
    }
    //-----------------------------------------------------------------------------------
    void SItemPacketProcesser::broadcastChangeEquip( I32 id, U32 putonId, U32 pos, SPlayerCharacter* sender )
    {
        NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

        GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
        if(packet)
        {
            packet->type = PT_ITEM_M2C_CHANGE_EQUIP;
            packet->channel = GNPC_ITEM;

            PT_ITEM_M2C_CHANGE_EQUIP_DATA* sendData = (PT_ITEM_M2C_CHANGE_EQUIP_DATA*)packet->data;
            if(sendData)
            {
                sendData->charid = sender->getID();
                sendData->pos = pos;
                sendData->putonEquipId = putonId;
                SRegionObjectBase* tempRegion;// = sender->getCurrentRegionObject();

				if ( tempRegion )
				{
	//				NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize + PT_ITEM_M2C_CHANGE_EQUIP_DATA_INFO::dataSize, 
	//					sender->getSceneObjectInSceneGridsManager()->currSceneGrid, NULL, tempRegion, 0);
				}
			}
        }
    }
	void    SItemPacketProcesser::recvEquipList(I32 id, PT_ITEM_F2M_EQUIP_LIST_DATA* pData)
	{
		SPlayerCharacter*  pSPlayerCharacter = NULL;//SWorldManager::getInstance().getPlayerCharacterFromMemory(pData->charid);
		DYNAMIC_ASSERT(pSPlayerCharacter);
		EquipItem* tempEquipItem = pSPlayerCharacter->getEquipItem();
		DYNAMIC_ASSERT(tempEquipItem);

		for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
		{
			tempEquipItem->setEquipItem(
				pData->equipAttr[i].equipId
				,pData->equipAttr[i].curStrengthenLv
				,pData->equipAttr[i].randAppendID
				,pData->equipAttr[i].strengthenAppendID
				,i
				,pSPlayerCharacter
				);
		} 
		//broadcastEquipList(pSPlayerCharacter, pSPlayerCharacter->getCurrentRegionObject());
	}
    //-----------------------------------------------------------------------------------
    void SItemPacketProcesser::recvChangeEquip( I32 id, PT_ITEM_F2M_CHANGE_EQUIP_DATA* pData )
    {
        SPlayerCharacter*  pSPlayerCharacter = NULL;//SWorldManager::getInstance().getPlayerCharacterFromMemory(pData->charid);
        DYNAMIC_ASSERT(pSPlayerCharacter);
        EquipItem* tempEquipItem = pSPlayerCharacter->getEquipItem();
        DYNAMIC_ASSERT(tempEquipItem);

		tempEquipItem->setEquipItem(
			pData->putonEquipAttr.equipId 
			,pData->putonEquipAttr.curStrengthenLv
			,pData->putonEquipAttr.randAppendID
			,pData->putonEquipAttr.strengthenAppendID
			,pData->pos
			,pSPlayerCharacter
			);

        //地图广播
        //SPlayer* pSPlayer = pSPlayerCharacter->getOwnerPlayer();
        //DYNAMIC_ASSERT(pSPlayer);
        broadcastChangeEquip(pSPlayerCharacter->getClientNetIdInFrontServer(), pData->putonEquipAttr.equipId, pData->pos, pSPlayerCharacter);
    }

    //-----------------------------------------------------------------------------------
    void SItemPacketProcesser::recvUseItem( I32 id, PT_ITEM_F2M_USE_ITEM_DATA* pData )
    {
		SPlayerCharacter*  pSPlayerCharacter = NULL;//SWorldManager::getInstance().getPlayerCharacterFromMemory(pData->charid);
        DYNAMIC_ASSERT(pSPlayerCharacter);
		if (pSPlayerCharacter == NULL)
		{
			return;
		}
        const ItemInfo* pInfo = ItemTemplate::getInstance().getItemInfo(pData->itemid);
        DYNAMIC_ASSERT(pInfo);

		//检查CD
		SCDManager* pSCDManager = pSPlayerCharacter->getSCDManager();
		if ( pSCDManager->checkCD(CD_MASTER_TYPE_CHARACTER, pInfo->getItemUseOwnerTimepieceId()) )
		{	
			sendUseItemToFrontServer(
				pSPlayerCharacter->getClientNetIdInFrontServer(), 
				pSPlayerCharacter->getFrontServerId(), 
				pData->charid,
				pData->slotIndex,
				pData->itemType,
				item_use_res_Error_CD
				);
			return;
		}
		//加CD
		pSCDManager->addCD(
				CD_MASTER_TYPE_CHARACTER, 
				pInfo->getItemUseOwnerTimepieceId(),
				pInfo->getItemUseOwnerTimepieceDelay(),
				pInfo->getItemUseOwnerTimepieceDelay()
			);

		//计算恢复值。
		if ( pInfo->getItemUseRestoreParameter1() != 0 )
		{
			pSPlayerCharacter->itemTreat(DT_HP, pInfo->getItemUseRestoreParameter1());
		}
		if (pInfo->getItemUseRestoreParameter2() != 0)
		{
			pSPlayerCharacter->itemTreat(DT_MP, pInfo->getItemUseRestoreParameter2());
		}
		if (pInfo->getItemUseRestoreParameter3() != 0)
		{
			pSPlayerCharacter->itemTreat(DT_SP, pInfo->getItemUseRestoreParameter3());
		}
		
		//给予的状态Id
		if (pInfo->getItemUseStateId()  &&  pInfo->getItemUseStateNum())
		{
			pSPlayerCharacter->getSBuffManager()->addNewBuff(
				pInfo->getItemUseStateId(), pInfo->getItemUseStateNum(), pSPlayerCharacter->getLevel()
				);
		}

		//给予的技能Id
		/*if ( pInfo->getItemUseSkillId() )
		{
			;
		}
		*/

		//通知FrontServer使用成功。
		sendUseItemToFrontServer(
			pSPlayerCharacter->getClientNetIdInFrontServer(),
			pSPlayerCharacter->getFrontServerId(), 
			pData->charid,
			pData->slotIndex,
			pData->itemType,
			item_use_res_Succeed
			);
    }

	//------------------------------------------------------------------------------------
	void SItemPacketProcesser::sendUseItemToFrontServer(I32 clientNetId,I32 frontNetId, PlayerCharacterIdType charid, IdType itemDBId, Byte res)
	{
		
	}

	//------------------------------------------------------------------------------------
	void SItemPacketProcesser::sendUseItemToFrontServer( I32 clientNetId,I32 frontNetId, PlayerCharacterIdType charid, U32 slotIndex, Byte itemType, Byte res )
	{
		GameNetSendDataBufferPtr dataPtr;
        MapServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr->getLogicData();
		if(packet)
		{
			packet->type = PT_ITEM_M2F_USE_ITEM;
			packet->channel = GNPC_ITEM;

			PT_ITEM_M2F_USE_ITEM_DATA* sendData = (PT_ITEM_M2F_USE_ITEM_DATA*)packet->data;
			if(sendData)
			{
				sendData->netId = clientNetId;
				sendData->charid = charid;
				sendData->slotIndex = slotIndex;
				sendData->itemType = itemType;
				sendData->res = res;

				MapServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_ITEM_M2F_USE_ITEM_DATA_INFO::dataSize, frontNetId);
			}
		}
	}

	//-----------------------------------------------------------------------------------
    void SItemPacketProcesser::recvPickItem( I32 id, PT_ITEM_F2M_PICK_ITEM_DATA* pData )
    {
        SPlayerCharacter* pSPlayerCharacter = NULL; //SWorldManager::getInstance().getPlayerCharacterFromMemory(pData->charId);
        DYNAMIC_ASSERT(pSPlayerCharacter);
        
		SPlayer* pSPlayer = NULL;//pSPlayerCharacter->getOwnerPlayer();

		SRegionObjectBase* myRegion;// = pSPlayerCharacter->getCurrentRegionObject();
		if (NULL != myRegion)
		{
			//检查道具是否在地图上。
			//如果在发送包给FrontServer处理，同步客户端去掉场景中的道具实体
			//myRegion->getDropItemManager()->handleCheckPickItem(pSPlayerCharacter, pSPlayer, pData->charId, pData->itemIndex);
		}
       
    }

    //-----------------------------------------------------------------------------------
    void SItemPacketProcesser::sendPickItemToFrontServer( I32 clientNetId, I32 frontNetId, PlayerCharacterIdType charid, U32 itemtempId, U32 num )
    {
        GameNetSendDataBufferPtr dataPtr  ;
        MapServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        GameNetPacketData* packet       = (GameNetPacketData*) dataPtr->getLogicData();
        if(packet)
        {
            packet->type = PT_ITEM_M2F_PICK_ITEM;
            packet->channel = GNPC_ITEM;

            PT_ITEM_M2F_PICK_ITEM_DATA* sendData = (PT_ITEM_M2F_PICK_ITEM_DATA*)packet->data;
            if(sendData)
            {
				sendData->netId = clientNetId;
                sendData->charid = charid;
                sendData->itemid = itemtempId;
                sendData->num = num;

				MapServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_ITEM_M2F_PICK_ITEM_DATA_INFO::dataSize, frontNetId);
            }
        }
    }

    //-----------------------------------------------------------------------------------
    void SItemPacketProcesser::broadcastPickItem( U32 itemtempId, U32 num, SPlayerCharacter* sender, Int index)
    {
        NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

        GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
        if(packet)
        {
            packet->type = PT_ITEM_M2C_PICK_ITEM;
            packet->channel = GNPC_ITEM;

            PT_ITEM_M2C_PICK_ITEM_DATA* sendData = (PT_ITEM_M2C_PICK_ITEM_DATA*)packet->data;
            if(sendData)
            {
                sendData->charid = sender->getID();
                sendData->itemid = itemtempId;
				sendData->index = index;
                sendData->num = num;
                SRegionObjectBase* tempRegion;// = sender->getCurrentRegionObject();

               	if ( tempRegion )
				{
	//				NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize + PT_ITEM_M2C_PICK_ITEM_DATA_INFO::dataSize, 
	//					sender->getSceneObjectInSceneGridsManager()->currSceneGrid, NULL, tempRegion, 0);
				}
			}
        }
    }

	//-----------------------------------------------------------------------------------
	void SItemPacketProcesser::broadcastDropItemDisappear(const dropItemData* item, SRegionObjectBase* regionObj)
	{
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if(packet)
		{
			packet->type = PT_ITEM_M2C_DROP_ITEM_DISAPPEAR;
			packet->channel = GNPC_ITEM;

			PT_ITEM_M2C_DROP_ITEM_DISAPPEAR_DATA* sendData = (PT_ITEM_M2C_DROP_ITEM_DISAPPEAR_DATA*)packet->data;
			if(sendData)
			{
				sendData->index	= item->index;
				sendData->itemid = item->itemTempId;
				sendData->num = item->num;

				if ( regionObj )
				{
					NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_ITEM_M2C_DROP_ITEM_DISAPPEAR_DATA_INFO::dataSize, regionObj);
				}
			}
		}
	}

	//-----------------------------------------------------------------------------------
	void SItemPacketProcesser::sendRewardToClient( I32 frontNetId, I32 clientNetId, PlayerIdType playerid, U32 groupItemId, Bool isShow )
	{
		NetTranspondSendDataBufferPtr dataPtr  ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if(packet)
		{
			packet->type = PT_ITEM_M2C_ATFD_REWARD;
			packet->channel = GNPC_ITEM;

			PT_ITEM_M2C_ATFD_REWARD_DATA* sendData = (PT_ITEM_M2C_ATFD_REWARD_DATA*)packet->data;
			if(sendData)
			{
				sendData->isShow = isShow;
				sendData->groupItemId = groupItemId;

				NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
						dataPtr,
						GameNetPacketData_INFO::headSize + PT_ITEM_M2C_ATFD_REWARD_DATA_INFO::dataSize, 
						frontNetId,
						clientNetId,
						playerid
					);
			}
		}
	}

	//-----------------------------------------------------------------------------------
	void SItemPacketProcesser::broadcastDropItemToClient( std::vector<dropItemData*>* tempVectorDropItem, SRegionObjectBase* regionObject )
	{
		NetTranspondSendDataBufferPtr dataPtr   ;
		GameNetPacketData* packet       = NULL;

		PT_ITEM_M2C_DROP_ITEM_LIST_DATA* sendData = NULL;

		Int elemSize = PT_ITEM_M2C_DROP_ITEM_LIST_DATA_INFO::elemSize;
		Int dataSize = PT_ITEM_M2C_DROP_ITEM_LIST_DATA_INFO::headSize;
		Int maxBuffSize = 0;

		std::vector<dropItemData*>::iterator front = tempVectorDropItem->begin();
		std::vector<dropItemData*>::iterator back = tempVectorDropItem->end();
		for ( ;front != back ; front++ )
		{

			//-----------------------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() == false )
			{
				if ( dataSize + elemSize > maxBuffSize )
				{	
					NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(
						dataPtr, 
						GameNetPacketData_INFO::headSize + dataSize, 
						regionObject
						);

					dataPtr.mDataPtr.setNull();
				}
			}

			//-----------------------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() )
			{
				NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

				packet       = (GameNetPacketData*) dataPtr.getTranspondData();
				if(!packet)
					return;

				packet->type = PT_ITEM_M2C_DROP_ITEM_LIST;
				packet->channel = GNPC_ITEM;

				sendData = (PT_ITEM_M2C_DROP_ITEM_LIST_DATA*)packet->data;
				if(!sendData)
					return;

				sendData->nCount = 0;

				elemSize = PT_ITEM_M2C_DROP_ITEM_LIST_DATA_INFO::elemSize;
				dataSize = PT_ITEM_M2C_DROP_ITEM_LIST_DATA_INFO::headSize;
				maxBuffSize = dataPtr.getTranspondDataMaxSize(100);
			}

			//-----------------------------------------------------------------------------------

			sendData->data[sendData->nCount].index			= (*front)->index;
			sendData->data[sendData->nCount].itemTempId		= (*front)->itemTempId;
			sendData->data[sendData->nCount].num			= (*front)->num;
			sendData->data[sendData->nCount].pos			= (*front)->pos;

			dataSize += elemSize;
			++(sendData->nCount);
		}

		//-----------------------------------------------------------------------------------
		if ( dataPtr.mDataPtr.isNull() == false )
		{
			NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(
					dataPtr, 
					GameNetPacketData_INFO::headSize + dataSize, 
					regionObject
				);
			dataPtr.mDataPtr.setNull();
		}
	}

	//-----------------------------------------------------------------------------------
	void SItemPacketProcesser::sendAddExpToFrontServer(const ItemInfo* itemInfo, SCharacter* playerCharacter, Int num)
	{
		GameNetSendDataBufferPtr dataPtr  ;
        MapServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr->getLogicData();
		if(NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		packet->type = PT_ITEM_M2F_DROP_ITEM_ADD_EXP;
		packet->channel = GNPC_ITEM;

		PT_ITEM_M2F_DROP_ITEM_ADD_EXP_DATA* sendData = (PT_ITEM_M2F_DROP_ITEM_ADD_EXP_DATA*)packet->data;
		if(NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		{
			//SPlayer* player			= playerCharacter->getOwnerPlayer();
			NetIdType frontNetId	= playerCharacter->getFrontServerId();
			sendData->accountId		= playerCharacter->getAccountId();
			sendData->charId		= playerCharacter->getID();
			sendData->itemId		= itemInfo->ItemId;
			sendData->itemNum		= num;

			MapServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
				GameNetPacketData_INFO::headSize + PT_ITEM_M2F_DROP_ITEM_ADD_EXP_DATA_INFO::dataSize, frontNetId);
		}
	}

	//-----------------------------------------------------------------------------------
	void SItemPacketProcesser::broadcastAddExpToFrontServer(const ItemInfo* itemInfo, SRegionObjectBase* regionObject, Int num)
	{
		GameNetSendDataBufferPtr dataPtr;
		GameNetPacketData* packet = NULL;
		PT_ITEM_M2F_DROP_ITEM_ADD_EXP_DATA* sendData = NULL;

		std::map<PlayerCharacterIdType,	SCharacter*>* playerCharacterList;// = regionObject->getPlayerCharacterList();
		std::map<PlayerCharacterIdType,	SCharacter*>::iterator iter = playerCharacterList->begin();
		for (; iter != playerCharacterList->end(); ++iter)
		{
			//-----------------------------------------------------------------------------------

			MapServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );
			packet       = (GameNetPacketData*) dataPtr->getLogicData();
			if(NULL == packet)
			{
				DYNAMIC_ASSERT(0);
				return;
			}

			packet->type = PT_ITEM_M2F_DROP_ITEM_ADD_EXP;
			packet->channel = GNPC_ITEM;

			sendData = (PT_ITEM_M2F_DROP_ITEM_ADD_EXP_DATA*)packet->data;
			if(NULL == sendData)
			{
				DYNAMIC_ASSERT(0);
				return;
			}

			//-----------------------------------------------------------------------------------

			//SPlayer* player = iter->second->getOwnerPlayer();
			NetIdType frontNetId	= iter->second->getFrontServerId();
			sendData->accountId		= iter->second->getAccountId();
			sendData->charId		= iter->second->getID();
			sendData->itemId		= itemInfo->ItemId;
			sendData->itemNum		= num;

			MapServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
				GameNetPacketData_INFO::headSize + PT_ITEM_M2F_DROP_ITEM_ADD_EXP_DATA_INFO::dataSize, frontNetId);

			dataPtr.setNull();
		}
	}

	//-----------------------------------------------------------------------------------
	void SItemPacketProcesser::sendRewardToFrontServer( I32 clientNetId, I32 frontNetId, PlayerCharacterIdType charId, U32 groupItemId )
	{
		GameNetSendDataBufferPtr dataPtr;
        MapServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr->getLogicData();
		if(packet)
		{
			packet->type = PT_ITEM_M2F_ATFD_REWARD;
			packet->channel = GNPC_ITEM;

			PT_ITEM_M2F_ATFD_REWARD_DATA* sendData = (PT_ITEM_M2F_ATFD_REWARD_DATA*)packet->data;
			if(sendData)
			{
				sendData->netId = clientNetId;
				sendData->groupItemId = groupItemId;
				sendData->playerCharId = charId;

				MapServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_ITEM_M2F_ATFD_REWARD_DATA_INFO::dataSize, frontNetId);
			}
		}
	}

	//-----------------------------------------------------------------------------------
	void SItemPacketProcesser::recvRewardItemFromClient( I32 id, PT_ITEM_C2M_ATFD_REWARD_DATA* pData )
	{
		SPlayerCharacter* pSPlayerCharacter = NULL; //SWorldManager::getInstance().getPlayerCharacterFromMemory(pData->playerCharId);
		DYNAMIC_ASSERT(pSPlayerCharacter);
		if ( pSPlayerCharacter->isDead() ) return;
		
		SPlayer* pSPlayer = NULL; //pSPlayerCharacter->getOwnerPlayer();
		DYNAMIC_ASSERT(pSPlayer);

		//找到DropItemManager，之后调用handleCheckRewardItem
		//(检查是否已经领取奖励，并作相应处理)。
		SRegionObjectBase* myRegionObj;// = pSPlayerCharacter->getCurrentRegionObject(); 
		if (NULL == myRegionObj)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		//myRegionObj->getDropItemManager()->handleCheckRewardItem(pSPlayer, pData->playerCharId, pData->groupItemId);
	}

}