//**************************************************************************************************************
#ifndef _H_ITEMPACKETPROCESSER_
#define _H_ITEMPACKETPROCESSER_
//**************************************************************************************************************
#include "FrontServerPreqs.h"
#include "ItemNetPacket.h"
//**************************************************************************************************************
namespace MG
{
	class SClanPtr;

    class ItemPacketProcesser
    {
    public:
        ItemPacketProcesser(){;}
        ~ItemPacketProcesser(){;}
        SINGLETON_INSTANCE(ItemPacketProcesser);

    public:
        Bool	processClientPacket(I32 id, NetEventRecv* packet);
        Bool    processMapServerPacket(I32 id, NetEventRecv* packet);

    public:
		void    sendBeginAddItemListToClient(I32 id);
        void    sendAddItemToClient(I32 id, PlayerItem* pItem);
		void    sendItemUpdateNumListToClient(I32 id,std::vector<PlayerItem*>* pItemList);

        void    sendItemDelToClient(I32 id, ITEM_SITE_TYPE type, IdType itemDBID, itembag_del_res res, PlayerCharacterIdType charid = 0);  
        void    sendItemChangePosToClient(I32 id, ITEM_SITE_TYPE sendtype, ITEM_SITE_TYPE recvtype, U32 sendIndex, U32 recvIndex, item_changepos_res res, PlayerCharacterIdType charid);
        
        void    sendAllClanItemInfoToClient(I32 id, SClanPtr& clanPtr );
        void    sendItemToClient(I32 id, std::vector<ItemRecord*>* ItemRecordList);
        void    sendItemSplitToClient(I32 id, UInt selfSlotIndex, ITEM_SITE_TYPE selfType, ITEM_SITE_TYPE splitType, UInt selectIndex, U32 num,
			                    item_split_res res, PlayerCharacterIdType charid);

        void    sendChangeEquipToMapServer(I32 id, PlayerCharacterIdType charid, PlayerItem* pItem, U32 pos);
        void    sendEquipListToMapServer(I32 id, SPlayerCharacter* pSPlayerCharacter);

	    void    sendItemUseToClient(I32 id, PlayerCharacterIdType charid, U32 slotIndex,ITEM_SITE_TYPE type, item_use_res res);
	    void    sendItemUseToMapServer( I32 id, PlayerCharacterIdType charid, U32 itemid, U32 slotIndex,ITEM_SITE_TYPE itemType );
        void    sendPickItemToMapServer(I32 id, PlayerCharacterIdType charid, U32 itemindex);
		void	sendAddMoneyToClient(I32 id, Int num, Byte type);
		void	sendAddExpToClient(I32 id, U32 num, Byte type, IdType charId, Byte charType);
		void	sendRewardItemToMapServer(I32 id, PlayerCharacterIdType charid, U32 groupItemId);
		void	sendRewardItemToClient(I32 id);
		void	sendPickItemToClient(I32 id);

    private:
        void    recvItemDel(I32 id, PT_ITEM_C2S_DELETE_DATA* pData);
        void    recvItemChangePos(I32 id, PT_ITEM_C2S_CHANGEPOS_DATA* pData);
        void    recvItemSplit(I32 id, PT_ITEM_C2S_SPLIT_DATA* pData);
        void    recvItemUseFromClient(I32 id, PT_ITEM_C2F_USE_ITEM_DATA* pData);
		void    recvItemUseFromMapServer(I32 id, PT_ITEM_M2F_USE_ITEM_DATA* pData);
        void    recvPickItemFromClient(I32 id, PT_ITEM_C2F_PICK_ITEM_DATA* pData);
        void    recvPickItemFromMapServer(I32 id, PT_ITEM_M2F_PICK_ITEM_DATA* pData);
		void	recvRewardItemFromMapServer(I32, PT_ITEM_M2F_ATFD_REWARD_DATA* pData);

		//ylh 怪物死后直接加经验
		void	recvDropItemAddExpFromMapServer(I32, PT_ITEM_M2F_DROP_ITEM_ADD_EXP_DATA* pData);

		void	recvRewardItemFromClient(I32, PT_ITEM_C2M_ATFD_REWARD_DATA* pData);
        
		//quest reward item
		void    recvRewardItemAssociateQuestFromClient(I32 id,PT_ITEM_C2F_QUEST_REWARD_DATA* pData);



    };

}
//**************************************************************************************************************
#endif
//**************************************************************************************************************