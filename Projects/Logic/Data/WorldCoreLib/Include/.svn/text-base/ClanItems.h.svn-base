//**********************************************************************************************************
#ifndef _H_CLANITEMS_
#define _H_CLANITEMS_
//**********************************************************************************************************
#include "Items.h"
//**********************************************************************************************************
namespace MG
{
    class ClanItems  : public Items
    {
    public:
        ClanItems(){;}
        virtual ~ClanItems(){;}

    public:
        //添加
        void        addItem(PlayerItem* pItem, Bool isServer);

        Bool        checkClanItemsCanAdd(U32 itemTemplateId,U32 num);
		Bool        checkClanItemsCanAdd(std::vector<ItemNum>& itemVector);
		//是否添加物品时需要判断叠加
        Bool        checkIsNeedOverlay(U32 itemTemplateId);
		//叠加时是否能添加物品
		Bool        checkCanAddWhenNeddOverlay(U32 itemTemplateId,U32 itemAddNum);

		Bool        checkItemExistInClanBag(U32 itemTemplateId,U32 num);
		//
        
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************