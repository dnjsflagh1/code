//*****************************************************************************************************************
#ifndef _H_ITEM_MONEY_TEMPLATE_
#define _H_ITEM_MONEY_TEMPLATE_
//*****************************************************************************************************************
#include "GameFilePreqs.h"
//*****************************************************************************************************************
namespace MG
{
    //-------------------------------------------------------------------------------
    struct ItemMoneyInfo 
    {
        ItemIdType						ItemMoneyId		;
        Str16							Name			;
        Str16                           Text			;
		Str16                           UnitName		;
		Int								atrIconId		;
        U32                             ArtMeshId		;
		U32                             Price			;
		ITEM_RANK                       Rank			;
		ITEM_MONEY_CLASS                Class			;
    };
    //-------------------------------------------------------------------------------
    class ItemMoneyTemplate
    {
		enum ItemMoneyRow
		{
			ItemMoneyRow_ItemMoneyId,	//金钱的调用Id
			ItemMoneyRow_Notes,
			ItemMoneyRow_Name,			//金钱的中文命名
			ItemMoneyRow_Text,			//"金钱的描述文本 支持转义，提供指定颜色、换行等功能"
			ItemMoneyRow_UnitName,		//金钱的文字单位
			ItemMoneyRow_ArtIconId,		//金钱在ArtIcon表中所对应的IconId
			ItemMoneyRow_ArtMeshId,		//金钱在Mesh表中所对应的显示模型Id
			ItemMoneyRow_Price,			//金钱的基础价值
			ItemMoneyRow_Rank,			//金钱的品质类别，单选 	1~白，2~绿，3~蓝，4~紫 仅有4种
			ItemMoneyRow_Class,			//金钱的物品分类，单选
			
			ItemMoneyRow_Max
		};
    public:
        ItemMoneyTemplate(){;}
        ~ItemMoneyTemplate();
        SINGLETON_INSTANCE(ItemMoneyTemplate);

    public:
        Bool                    load(Str16 fileName, IMGExternalPackManager* packManager = NULL );
        const ItemMoneyInfo*    getItemMoneyInfo(ItemIdType tempID);

    private:
        SimpleMapDataSetManager<ItemIdType, ItemMoneyInfo>        mItemMoneyList;

    };

}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************