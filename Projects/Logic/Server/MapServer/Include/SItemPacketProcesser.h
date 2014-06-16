//***************************************************************************************************
#ifndef _H_SITEM_PACKET_PROCESSER_
#define _H_SITEM_PACKET_PROCESSER_
//***************************************************************************************************
#include "MapServerPreqs.h"
#include "ItemNetPacket.h"
//***************************************************************************************************
namespace MG
{
    class SItemPacketProcesser
    {
    public:
        SItemPacketProcesser(){;}
        ~SItemPacketProcesser(){;}
        SINGLETON_INSTANCE(SItemPacketProcesser);

    public:
        Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);

    public:
        void    broadcastEquipList(SPlayerCharacter* sender, SRegionObjectBase* region, Bool isFilterSelf = false);
        void    broadcastChangeEquip(I32 id, U32 putonId, U32 pos, SPlayerCharacter* sender);
        void    sendPickItemToFrontServer(I32 clientNetId, I32 frontNetId, PlayerCharacterIdType charid, U32 itemtempId, U32 num);
        void    broadcastPickItem(U32 itemtempId, U32 num, SPlayerCharacter* sender, Int index);
		void	sendUseItemToFrontServer(I32 clientNetId,I32 frontNetId, PlayerCharacterIdType charid, IdType itemDBId, Byte res);
		void	sendUseItemToFrontServer(I32 clientNetId,I32 frontNetId, PlayerCharacterIdType charid, U32 slotIndex, Byte itemType, Byte res);
		void	sendRewardToClient(I32 frontNetId, I32 clientNetId, PlayerIdType playerId, U32 groupItemId, Bool isShow);
		void    broadcastDropItemToClient(std::vector<dropItemData*>* tempVectorDropItem, SRegionObjectBase* regionObject);
		void	sendRewardToFrontServer(I32 clientNetId, I32 frontNetId, PlayerCharacterIdType charId, U32 groupItemId);

		void    sendAddExpToFrontServer(const ItemInfo* itemInfo, SCharacter* playerCharacter, Int num);
		void    broadcastAddExpToFrontServer(const ItemInfo* itemInfo, SRegionObjectBase* regionObject, Int num);
    
		//时间到了， 掉落物品自动消失	ylh
		void    broadcastDropItemDisappear(const dropItemData* item, SRegionObjectBase* regionObj);

	public:
        void    recvEquipList(I32 id, PT_ITEM_F2M_EQUIP_LIST_DATA* pData);
        void    recvChangeEquip(I32 id, PT_ITEM_F2M_CHANGE_EQUIP_DATA* pData);
        void    recvUseItem(I32 id, PT_ITEM_F2M_USE_ITEM_DATA* pData);
        void    recvPickItem(I32 id, PT_ITEM_F2M_PICK_ITEM_DATA* pData);
		void	recvRewardItemFromClient(I32, PT_ITEM_C2M_ATFD_REWARD_DATA* pData);

    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************