//**********************************************************************************************************
#ifndef _H_CITEMMANAGER_
#define _H_CITEMMANAGER_
//**********************************************************************************************************
#include "ClientPreqs.h"
#include "ItemManager.h"
#include "ItemNetPacket.h"
//**********************************************************************************************************
namespace MG
{
    class CItemManager : public ItemManager
    {
    public:
        CItemManager(){;}
        virtual ~CItemManager();
        SINGLETON_INSTANCE(CItemManager);
    public:
        void                handlDelItem(IdType itemDBID, ITEM_SITE_TYPE type, PlayerCharacterIdType charid);
        void                handlChangItem(U32 sendIndex, U32 recvIndex, ITEM_SITE_TYPE sendtype, ITEM_SITE_TYPE recvtype, PlayerCharacterIdType charid);
        void                handlAddItem(ItemRecord* pRecord);
        void                handlSplitItem(IdType itemDBId, ITEM_SITE_TYPE selftype, ITEM_SITE_TYPE splittype, U32 splitpos, U32 splitnum, PlayerCharacterIdType charid);
		void                handlSplitItem(U32 slotIndex, ITEM_SITE_TYPE selfType, ITEM_SITE_TYPE splitType, U32 selectIndex, U32 num,
			PlayerCharacterIdType id = 0);

        void                handlUseItem(IdType itemDbId, PlayerCharacterIdType charid);
		void                handlUseItem(U32 slotIndex, ITEM_SITE_TYPE itemType,PlayerCharacterIdType charid);
        void                handlRemoveItem(PlayerItem* pItem, ITEM_SITE_TYPE sendType, PlayerCharacterIdType id = 0);
        void                handlAddItem(PlayerItem* pItem);
		void				handlAddMoney(Int num, Byte type);
		void				handlAddExp(U32 num, Byte type, IdType objId, Byte objType);
        void                handUpdateItemNum(PT_ITEM_S2C_UPDATE_NUM_DATA* data, Int account);
        void                setSize();  
        U32                 getClanBagSize();
		
		//////////////////////////////////////////////////////////////////////////
		Bool                handleCheckCanAddToClanBag( U32 itemTempId,U32 num );
		void				handleClearAllItem();

	public:
		//计算属性
		void				calAttr(PlayerCharacterIdType id, PlayerItem* pPlayerItem, Bool isAdd);
		void				calAttr(CCharacter* pSCharacter, PlayerItem* pPlayerItem, Bool isAdd);
		void				calAttrAll(CCharacter* pSCharacter);
		//只计算属性累加，不做具体计算。
		void				calAttrAllBase(CCharacter* pSCharacter);
        //////////////////////////////////////////////////////////////////////////
        //根据物品判定的结果，显示信息给客服端
        void                addGameJudgeErrorMsgForClient(GAMEJUDGE_TYPE judgeType);


	private:
		void				getAttrMapBySlot(PlayerItem* pPlayerItem, std::map<U32, Flt>* pAttrMap);

    private:
        void                notifyUIAddItem( PlayerItem* pItem );
        void                notifyUIDeleteItem(PlayerItem* pItem,ITEM_SITE_TYPE type, U32 index);
        void                notifyUIUpdateItem(PlayerItem* item, ITEM_SITE_TYPE type, U32 index, U32 num);
		void                notifyUIUpdateMoney();

		
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************
