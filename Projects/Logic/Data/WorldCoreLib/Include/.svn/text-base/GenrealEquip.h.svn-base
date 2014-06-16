//***********************************************************************************************************
#ifndef _H_GENREAL_EQUIP_
#define _H_GENREAL_EQUIP_
//***********************************************************************************************************
#include "WorldCorePreqs.h"
//***********************************************************************************************************
namespace MG
{
    class GenrealEquip
    {
    public:
        GenrealEquip();
        ~GenrealEquip();

    public:
        void            clear();

    public:
        void            addItem(PlayerItem* pItem, PlayerCharacterIdType charid, Bool isServer);
        PlayerItem*     removeItem(IdType itemid);
        PlayerItem*     removeItem(ITEM_EQUIP_SLOT_TYPE type);
        PlayerItem*     findItem(ITEM_EQUIP_SLOT_TYPE type);
        PlayerItem*     findItem(IdType itemid);

        PlayerItem**     getEquipItemArray();

    private:
        PlayerItem*         mItemEquipArray[ITEM_EQUIP_SLOT_TYPE_MAX];          
    };
}
//***********************************************************************************************************
#endif
//***********************************************************************************************************