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
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_SHOP;
            packet->type    = PT_SHOP_C2S_OPEN;

            // 转换逻辑包
            PT_SHOP_C2S_OPEN_DATA* sendData = (PT_SHOP_C2S_OPEN_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->accountID = CPlayer::getInstance().getAccountID();
                sendData->shopID = shopID;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_SHOP_C2S_OPEN_DATA_INFO::dataSize );
            }
        }
    }
    //----------------------------------------------------------------------------------------------
    //void ShopPacketProcesser::sendCloseShop( U32 shopID )
    //{
    //    // 获得一个发送【服务端】缓存
    //    GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

    //    // 转换成标准包格式
    //    GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
    //    if ( packet )
    //    {
    //        // 设置标签
    //        packet->channel = GNPC_SHOP;
    //        packet->type    = PT_SHOP_C2S_CLOSE;

    //        // 转换逻辑包
    //        PT_SHOP_C2S_CLOSE_DATA* sendData = (PT_SHOP_C2S_CLOSE_DATA*)(packet->data);
    //        if ( sendData )
    //        {
    //            // 填充逻辑包
    //            sendData->accountID = CPlayer::getInstance().getAccountID();
    //            sendData->shopID = shopID;

    //            // 发送数据
    //            ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
    //                GameNetPacketData_INFO::headSize + PT_SHOP_C2S_CLOSE_DATA_INFO::dataSize );
    //        }
    //    }
    //}
    //----------------------------------------------------------------------------------------------
    void ShopPacketProcesser::sendShopBuyItem( U32 shopID, U32 itemTempID, U32 num )
    {
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_SHOP;
            packet->type    = PT_SHOP_C2M_BUY_ITEM;

            // 转换逻辑包
            PT_SHOP_C2M_BUY_ITEM_DATA* sendData = (PT_SHOP_C2M_BUY_ITEM_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->accountID = CPlayer::getInstance().getAccountID();
                sendData->shopID = shopID;
                sendData->itemNum.itemTemplate = itemTempID;
                sendData->itemNum.num = num;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_SHOP_C2M_BUY_ITEM_DATA_INFO::dataSize );
            }
        }
    }
    //----------------------------------------------------------------------------------------------
    void ShopPacketProcesser::sendShopSellItem( U32 shopID, IdType itemDBId )
    {
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_SHOP;
            packet->type    = PT_SHOP_C2F_SELL_ITEM;

            // 转换逻辑包
            PT_SHOP_C2F_SELL_ITEM_DATA* sendData = (PT_SHOP_C2F_SELL_ITEM_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->shopID = shopID;
                sendData->itemDBID = itemDBId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_SHOP_C2F_SELL_ITEM_DATA_INFO::dataSize );
            }
        }
    }
    //----------------------------------------------------------------------------------------------
    void ShopPacketProcesser::sendShopRepairItem( U32 shopID, IdType itemDBId, ITEM_SITE_TYPE type, PlayerCharacterIdType charid )
    {
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_SHOP;
            packet->type    = PT_SHOP_C2F_REPAIR_ITEM;

            // 转换逻辑包
            PT_SHOP_C2F_REPAIR_ITEM_DATA* sendData = (PT_SHOP_C2F_REPAIR_ITEM_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->shopID = shopID;
                sendData->itemDBID = itemDBId;
                sendData->itemSiteType = type;
                sendData->charid = charid;

                // 发送数据
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
			//提示
		}
    }
    //----------------------------------------------------------------------------------------------
    void ShopPacketProcesser::recvShopBuyItem( I32 id, PT_SHOP_F2C_BUY_ITEM_DATA* pData )
    {
        if ( pData->res == shop_buy_res_success )
            CItemShopManager::getInstance().handleBuyItem(pData->shopID, pData->itemNum.itemTemplate, pData->itemNum.num);
		else if (pData->res == shop_buy_res_not_enough_money)
		{
			MessageManager::getInstance().addChatMsgForTest(L"背包金钱不足,不能购买当前物品!");
		}
		else if (pData->res == shop_buy_res_bag_capacity_not_enough)
		{
			MessageManager::getInstance().addChatMsgForTest(L"背包空间不足,不能购买当前物品!");
		}
        //系统通知
        //？
    }
    //----------------------------------------------------------------------------------------------
    void ShopPacketProcesser::recvShopSellItem( I32 id, PT_SHOP_F2C_SELL_ITEM_DATA* pData )
    {
        if ( pData->res == shop_sell_item_res_suc )
            CItemShopManager::getInstance().handleSellItem(pData->shopID, pData->itemDBID);

        //系统通知。
        //？
    }
    //----------------------------------------------------------------------------------------------
    void ShopPacketProcesser::recvShopRepairItem( I32 id, PT_SHOP_F2C_REPAIR_ITEM_DATA* pData )
    {
        if ( pData->res == shop_repair_res_suc )
            CItemShopManager::getInstance().handleRepairItem(pData->shopID, pData->itemDBID, (ITEM_SITE_TYPE)pData->itemSiteType, pData->charid);
        
        //系统通知。
        //？
    }

    void ShopPacketProcesser::sendShopBuybackItem( U32 shopID, IdType itemDBId )
    {
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_SHOP;
            packet->type    = PT_SHOP_C2F_REPAIR_ITEM;

            // 转换逻辑包
            PT_SHOP_C2F_REPAIR_ITEM_DATA* sendData = (PT_SHOP_C2F_REPAIR_ITEM_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->shopID = shopID;
                sendData->itemDBID = itemDBId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_SHOP_C2F_REPAIR_ITEM_DATA_INFO::dataSize );
            }
        }
    }

    void ShopPacketProcesser::recvShopBuybackItem( U32 shopID, PT_SHOP_F2C_BUYBACK_ITEM_DATA* pData )
    {
        if ( pData->res == shop_buyback_res_suc )
            CItemShopManager::getInstance().handleBuybackItem(pData->shopID, pData->itemDBID, pData->index);

        //系统通知。
        //？
    }
    //----------------------------------------------------------------------------------------------
}