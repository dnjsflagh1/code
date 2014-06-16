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
			ItemMoneyRow_ItemMoneyId,	//��Ǯ�ĵ���Id
			ItemMoneyRow_Notes,
			ItemMoneyRow_Name,			//��Ǯ����������
			ItemMoneyRow_Text,			//"��Ǯ�������ı� ֧��ת�壬�ṩָ����ɫ�����еȹ���"
			ItemMoneyRow_UnitName,		//��Ǯ�����ֵ�λ
			ItemMoneyRow_ArtIconId,		//��Ǯ��ArtIcon��������Ӧ��IconId
			ItemMoneyRow_ArtMeshId,		//��Ǯ��Mesh��������Ӧ����ʾģ��Id
			ItemMoneyRow_Price,			//��Ǯ�Ļ�����ֵ
			ItemMoneyRow_Rank,			//��Ǯ��Ʒ����𣬵�ѡ 	1~�ף�2~�̣�3~����4~�� ����4��
			ItemMoneyRow_Class,			//��Ǯ����Ʒ���࣬��ѡ
			
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