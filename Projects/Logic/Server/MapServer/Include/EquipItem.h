//****************************************************************************************************
#ifndef _H_EQUIP_ITEM_
#define _H_EQUIP_ITEM_
//****************************************************************************************************
#include "MapServerPreqs.h"
//****************************************************************************************************
namespace MG
{
	struct EquipItemData
	{
		const ItemInfo*			mItemInfo;
		U32						mStrengthenLv;
		U32						mRandAppendID;
		U32						mStrengthenAppendID;

		void					clear();

	};
	//---------------------------------------------------------------------------------------------
    class EquipItem
    {
    public:
        EquipItem();
        ~EquipItem();

    public:
        void setEquipItem(U32 equipid, U32 strengthenLv, U32 randAppendID, U32 strengthenAppendID, U32 pos, SCharacter* pSCharacter = NULL);
        void getEquipItemList(U32* equipListid); 
        Bool checkIsEmpty();
		//计算属性
		void calAttr(SCharacter* pSCharacter, U32 pos, Bool isAdd);
		void calAttrAll(SCharacter* pSCharacter);
		//只计算属性累加，不做具体计算。
		void calAttrAllBase(SCharacter* pSCharacter);

    private:
		void		clear();
		void		getAttrMapBySlot(U32 pos, std::map<U32, Flt>* pAttrMap);

    private:
        EquipItemData mEquipItemDataArray[ITEM_EQUIP_SLOT_TYPE_MAX];
    };
}
//****************************************************************************************************
#endif
//****************************************************************************************************