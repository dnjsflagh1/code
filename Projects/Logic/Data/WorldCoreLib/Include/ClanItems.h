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
        //���
        void        addItem(PlayerItem* pItem, Bool isServer);

        Bool        checkClanItemsCanAdd(U32 itemTemplateId,U32 num);
		Bool        checkClanItemsCanAdd(std::vector<ItemNum>& itemVector);
		//�Ƿ������Ʒʱ��Ҫ�жϵ���
        Bool        checkIsNeedOverlay(U32 itemTemplateId);
		//����ʱ�Ƿ��������Ʒ
		Bool        checkCanAddWhenNeddOverlay(U32 itemTemplateId,U32 itemAddNum);

		Bool        checkItemExistInClanBag(U32 itemTemplateId,U32 num);
		//
        
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************