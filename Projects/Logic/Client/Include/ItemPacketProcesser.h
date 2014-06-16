//**************************************************************************************************************
#ifndef _H_ITEMPACKETPROCESSER_
#define _H_ITEMPACKETPROCESSER_
//**************************************************************************************************************
#include "ClientPreqs.h"
#include "ItemNetPacket.h"
#include "GameNetEvent.h"
//**************************************************************************************************************
namespace MG
{
    class ItemPacketProcesser
    {
    public:
        ItemPacketProcesser(){;}
        ~ItemPacketProcesser(){;}
        SINGLETON_INSTANCE(ItemPacketProcesser);

    public:
        Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);

    public:
        void    sendDelItem(ITEM_SITE_TYPE type, IdType itemDBID, PlayerCharacterIdType charid = 0);
        void    sendChangePos(U32 sendIndex, U32 recvIndex, ITEM_SITE_TYPE sendtype, ITEM_SITE_TYPE recvtype, PlayerCharacterIdType charid);
       
		void    sendSplitItem(IdType itemid, ITEM_SITE_TYPE selftype, ITEM_SITE_TYPE splittype, UInt splitpos, UInt splitnum, PlayerCharacterIdType charid);
        
		void    sendSplitItem(U32 slotIndex, ITEM_SITE_TYPE selfType, ITEM_SITE_TYPE splitType, U32 selectSlot, U32 num,
			PlayerCharacterIdType id = 0);
        void    sendUseItem(IdType itemid, PlayerCharacterIdType charid);
		void    sendUseItem(U32 slotIndex,ITEM_SITE_TYPE itemType, PlayerCharacterIdType charid);
        void    sendPickItem(U32 itemIndex, PlayerCharacterIdType charId, Int itemTemplateId, Int itemNum);
		void	sendRewardItem(U32 groupItemId, PlayerCharacterIdType playerCharId);
		void    sendRewardItemAssociateQuest(U32 groupItemId, PlayerCharacterIdType playerCharId);

    private:
		void	recvBeginAddItemList();
        void    recvItemList(I32 id, PT_ITEM_S2C_ADDLIST_DATA* pData);
        void    recvAddItem(I32 id, PT_ITEM_S2C_ADD_DATA* pData);
        void    recvDelItem(I32 id, PT_ITEM_S2C_DELETE_DATA* pData);
        void    recvChangePos(I32 id, PT_ITEM_S2C_CHANGEPOS_DATA* pData);
        void    recvSplitItem(I32 id, PT_ITEM_S2C_SPLIT_DATA* pData);
        void    recvUseItem(I32 id, PT_ITEM_F2C_USE_ITEM_DATA* pData);
        void    recvEquipListFromMS(I32 id, PT_ITEM_M2C_EQUIP_LIST_DATA* pData);
        void    recvChangeEquipFromMS(I32 id, PT_ITEM_M2C_CHANGE_EQUIP_DATA* pData);
        void    recvPickItemFromMS(I32 id, PT_ITEM_M2C_PICK_ITEM_DATA* pData);
		void	recvDropItemListFromMS(I32 id, PT_ITEM_M2C_DROP_ITEM_LIST_DATA* pData);
		void	recvRewardFromMS(I32 id, PT_ITEM_M2C_ATFD_REWARD_DATA* pData);
		void	recvAddMoney(I32 id, PT_ITEM_F2C_ADD_MONEY_DATA* pData);
		void	recvAddExp(I32 id, PT_ITEM_F2C_ADD_EXP_DATA* pData);
		void	recvRewardFromFS(I32 id);
		void	recvPickItemFromFS(I32 id);
        void    recvUpdateItemNum(I32 id,PT_ITEM_S2C_UPDATE_NUM_lIST_DATA* pData);
		//掉落物品 时间超时 消失
		void	recvDropItemDisappear(I32 id, PT_ITEM_M2C_DROP_ITEM_DISAPPEAR_DATA* pData);

    };

}
//**************************************************************************************************************
#endif
//**************************************************************************************************************