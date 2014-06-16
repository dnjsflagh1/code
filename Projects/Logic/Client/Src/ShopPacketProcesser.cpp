//**************************************************************************************************************
#include "stdafx.h"
#include "ShopPacketProcesser.h"
#include "ClientNetApplyManager.h"
#include "CItemShopManager.h"
#include "CItemShop.h"
#include "UIItemShop.h"
#include "UIMessageBox.h"
#include "CPlayer.h"
#include "MessageManager.h"
//**************************************************************************************************************
namespace MG
{
    MG::Bool ShopPacketProcesser::processFrontServerPacket( I32 id, NetEventRecv* packet )
    {
        if ( packet->getChannel() == GNPC_SHOP )
        {
            GameNetPacketData* data = (GameNetPacketData*)( packet->getData() );
            DYNAMIC_ASSERT( data );

            switch (data->type)
            {
            case PT_SHOP_S2C_OPEN:
                recvOpenShop( id, (PT_SHOP_S2C_OPEN_DATA*)(data->data) );
                break;
            case PT_SHOP_F2C_BUY_ITEM:
                recvShopBuyItem(id, (PT_SHOP_F2C_BUY_ITEM_DATA*)data->data);
                break;
            case PT_SHOP_F2C_SELL_ITEM:
                recvShopSellItem( id, (PT_SHOP_F2C_SELL_ITEM_DATA*)(data->data) );
                break;
            case PT_SHOP_F2C_REPAIR_ITEM:
                recvShopRepairItem(id, (PT_SHOP_F2C_REPAIR_ITEM_DATA*)data->data);
                break;
            case PT_SHOP_F2C_BUYBACK_ITEM:
                recvShopBuybackItem(id, (PT_SHOP_F2C_BUYBACK_ITEM_DATA*)data->data);
                break;
			default:
				DYNAMIC_ASSERT(0);
				break;
            }
            return true;
        }
        return false;
    }
    //----------------------------------------------------------------------------------------------
    void ShopPacketProcesser::sendOpenShop( U32 shopID )
    {
        // ���һ�����͡�����ˡ�����
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_SHOP;
            packet->type    = PT_SHOP_C2S_OPEN;

            // ת���߼���
            PT_SHOP_C2S_OPEN_DATA* sendData = (PT_SHOP_C2S_OPEN_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->accountID = CPlayer::getInstance().getAccountID();
                sendData->shopID = shopID;

                // ��������
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_SHOP_C2S_OPEN_DATA_INFO::dataSize );
            }
        }
    }
    //----------------------------------------------------------------------------------------------
    //void ShopPacketProcesser::sendCloseShop( U32 shopID )
    //{
    //    // ���һ�����͡�����ˡ�����
    //    GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

    //    // ת���ɱ�׼����ʽ
    //    GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
    //    if ( packet )
    //    {
    //        // ���ñ�ǩ
    //        packet->channel = GNPC_SHOP;
    //        packet->type    = PT_SHOP_C2S_CLOSE;

    //        // ת���߼���
    //        PT_SHOP_C2S_CLOSE_DATA* sendData = (PT_SHOP_C2S_CLOSE_DATA*)(packet->data);
    //        if ( sendData )
    //        {
    //            // ����߼���
    //            sendData->accountID = CPlayer::getInstance().getAccountID();
    //            sendData->shopID = shopID;

    //            // ��������
    //            ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
    //                GameNetPacketData_INFO::headSize + PT_SHOP_C2S_CLOSE_DATA_INFO::dataSize );
    //        }
    //    }
    //}
    //----------------------------------------------------------------------------------------------
    void ShopPacketProcesser::sendShopBuyItem( U32 shopID, U32 itemTempID, U32 num )
    {
        // ���һ�����͡�����ˡ�����
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_SHOP;
            packet->type    = PT_SHOP_C2M_BUY_ITEM;

            // ת���߼���
            PT_SHOP_C2M_BUY_ITEM_DATA* sendData = (PT_SHOP_C2M_BUY_ITEM_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->accountID = CPlayer::getInstance().getAccountID();
                sendData->shopID = shopID;
                sendData->itemNum.itemTemplate = itemTempID;
                sendData->itemNum.num = num;

                // ��������
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_SHOP_C2M_BUY_ITEM_DATA_INFO::dataSize );
            }
        }
    }
    //----------------------------------------------------------------------------------------------
    void ShopPacketProcesser::sendShopSellItem( U32 shopID, IdType itemDBId )
    {
        // ���һ�����͡�����ˡ�����
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_SHOP;
            packet->type    = PT_SHOP_C2F_SELL_ITEM;

            // ת���߼���
            PT_SHOP_C2F_SELL_ITEM_DATA* sendData = (PT_SHOP_C2F_SELL_ITEM_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->shopID = shopID;
                sendData->itemDBID = itemDBId;

                // ��������
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_SHOP_C2F_SELL_ITEM_DATA_INFO::dataSize );
            }
        }
    }
    //----------------------------------------------------------------------------------------------
    void ShopPacketProcesser::sendShopRepairItem( U32 shopID, IdType itemDBId, ITEM_SITE_TYPE type, PlayerCharacterIdType charid )
    {
        // ���һ�����͡�����ˡ�����
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_SHOP;
            packet->type    = PT_SHOP_C2F_REPAIR_ITEM;

            // ת���߼���
            PT_SHOP_C2F_REPAIR_ITEM_DATA* sendData = (PT_SHOP_C2F_REPAIR_ITEM_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->shopID = shopID;
                sendData->itemDBID = itemDBId;
                sendData->itemSiteType = type;
                sendData->charid = charid;

                // ��������
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_SHOP_C2F_REPAIR_ITEM_DATA_INFO::dataSize );
            }
        }
    }
    //----------------------------------------------------------------------------------------------
    void ShopPacketProcesser::recvOpenShop( I32 id, PT_SHOP_S2C_OPEN_DATA* pData )
    {
		if ( pData->isOpen )
		{
			CItemShop* pCItemShop = CItemShopManager::getInstance().handleOpenShop(pData->shopID);
			UIItemShop::getInstance().openShop(pCItemShop);
		}
        else
		{
			//��ʾ
		}
    }
    //----------------------------------------------------------------------------------------------
    void ShopPacketProcesser::recvShopBuyItem( I32 id, PT_SHOP_F2C_BUY_ITEM_DATA* pData )
    {
        if ( pData->res == shop_buy_res_success )
            CItemShopManager::getInstance().handleBuyItem(pData->shopID, pData->itemNum.itemTemplate, pData->itemNum.num);
		else if (pData->res == shop_buy_res_not_enough_money)
		{
			MessageManager::getInstance().addChatMsgForTest(L"������Ǯ����,���ܹ���ǰ��Ʒ!");
		}
		else if (pData->res == shop_buy_res_bag_capacity_not_enough)
		{
			MessageManager::getInstance().addChatMsgForTest(L"�����ռ䲻��,���ܹ���ǰ��Ʒ!");
		}
        //ϵͳ֪ͨ
        //��
    }
    //----------------------------------------------------------------------------------------------
    void ShopPacketProcesser::recvShopSellItem( I32 id, PT_SHOP_F2C_SELL_ITEM_DATA* pData )
    {
        if ( pData->res == shop_sell_item_res_suc )
            CItemShopManager::getInstance().handleSellItem(pData->shopID, pData->itemDBID);

        //ϵͳ֪ͨ��
        //��
    }
    //----------------------------------------------------------------------------------------------
    void ShopPacketProcesser::recvShopRepairItem( I32 id, PT_SHOP_F2C_REPAIR_ITEM_DATA* pData )
    {
        if ( pData->res == shop_repair_res_suc )
            CItemShopManager::getInstance().handleRepairItem(pData->shopID, pData->itemDBID, (ITEM_SITE_TYPE)pData->itemSiteType, pData->charid);
        
        //ϵͳ֪ͨ��
        //��
    }

    void ShopPacketProcesser::sendShopBuybackItem( U32 shopID, IdType itemDBId )
    {
        // ���һ�����͡�����ˡ�����
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_SHOP;
            packet->type    = PT_SHOP_C2F_REPAIR_ITEM;

            // ת���߼���
            PT_SHOP_C2F_REPAIR_ITEM_DATA* sendData = (PT_SHOP_C2F_REPAIR_ITEM_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->shopID = shopID;
                sendData->itemDBID = itemDBId;

                // ��������
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_SHOP_C2F_REPAIR_ITEM_DATA_INFO::dataSize );
            }
        }
    }

    void ShopPacketProcesser::recvShopBuybackItem( U32 shopID, PT_SHOP_F2C_BUYBACK_ITEM_DATA* pData )
    {
        if ( pData->res == shop_buyback_res_suc )
            CItemShopManager::getInstance().handleBuybackItem(pData->shopID, pData->itemDBID, pData->index);

        //ϵͳ֪ͨ��
        //��
    }
    //----------------------------------------------------------------------------------------------
}