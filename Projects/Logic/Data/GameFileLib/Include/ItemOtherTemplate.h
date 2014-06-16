//*****************************************************************************************************************
#ifndef _H_ITEM_OTHER_TEMPLATE_
#define _H_ITEM_OTHER_TEMPLATE_
//*****************************************************************************************************************
#include "GameFilePreqs.h"
//*****************************************************************************************************************
namespace MG
{

    //���	    ��������	                            ������
    //1	        ItemUseId                               ��������Ʒid
    //3	        Name                                    ��������Ʒ�����ƣ�16��������
    //4	        Text                                    "����������64�����ڣ�֧��ת�壬�ṩָ����ɫ�����������Ĺ��ܡ�"
    //5	        ArtIconId                               ��������Ʒ��icon����ӦIcon���Icon
    //6	        ArtMashId                               ��������Ʒ�������ģ��
    //7	        Price                                   ��������Ʒ�Ļ�����ֵ
    //8	        BuyPrice                                ��������Ʒ���򻨷ѣ����ĵ�����Ϸ��
    //9	        SellPrice                               ��������Ʒ���ۻ��ѣ����ĵ�����Ϸ��
    //11	    MaxPlieNum                              ��������Ʒ�����ѵ�������
    //12	    Score                                   ��������Ʒ�����ֵȼ�
    //13	    Rank                                    "��������Ʒ��Ʒ����𣬵�ѡ 1~�ס�2~�̡�3~����4~��"
    //14	    Class                                   "��������Ʒ�����ͣ���ѡ ����������"
    //16	    DisappearType                           "������λ�ж�����ʧ��ʽ����ѡ����������ʧ��������Ʒ�����Զ���ʧ"
    //17	    ForBidType                              "������λ�ж���֧�ֹ��ܣ���ѡ������λ�ж��ģ���֧����Ӧ����"
    //18	    ExistenceTimeType                       "��������Ʒ�Ĵ���ʱ�����ͣ���ѡ 1~��ʵʱ�䣬2~��Ϸʱ��"
    //19	    ExistenceTime                           ���ڵ�������ʱ�䵽����Ʒ��ʧ��ʧЧ
    //20	    ClanJudgeid                             ʹ��ʱ�������Ҫ��
    //21	    CharacterJudgeid                        ʹ��ʱ�Խ�ɫ��Ҫ��

    //-------------------------------------------------------------------------------
    struct ItemOtherInfo 
    {
        ItemIdType						ItemOtherId            	           ;
        Str16                           Name                               ;
        Str16                           Text                               ;
		Int								ArtIconId;
        U32                             ArtMeshId                          ;
        U64                             Price                              ;
        U64                             BuyPrice                           ;
        U64                             SellPrice                          ;
        U32                             MaxPileNum                         ;
        U64                             Score                              ;
        ITEM_RANK                       Rank                               ;
        ITEM_OTHER_CLASS                Class                              ;
        ITEM_BIND_TYPE                  BindType                           ;
        U32                             DisappearType                      ;
        U32                             ForBidType                         ;
        ITEM_EXISTENCE_TIME_TYPE        ExistenceTimeType                  ;
        U64                             ExistenceTime                      ;
		SkillIdType						SkillId								;

    };
    //-------------------------------------------------------------------------------
    class ItemOtherTemplate
    {
		enum ItemOtherCsvRow
		{
			ItemOtherCsvRow_ItemOtherId,
			ItemOtherCsvRow_ItemNotes,
			ItemOtherCsvRow_ItemName,
			ItemOtherCsvRow_ItemText,
			ItemOtherCsvRow_ArtIconId,
			ItemOtherCsvRow_ArtMeshId,
			ItemOtherCsvRow_Price,
			ItemOtherCsvRow_BuyPrice,
			ItemOtherCsvRow_SellPrice,
			ItemOtherCsvRow_MaxPileNum,
			ItemOtherCsvRow_Score,
			ItemOtherCsvRow_Rank,
			ItemOtherCsvRow_Class,
			ItemOtherCsvRow_BindType,
			ItemOtherCsvRow_DisappearType,
			ItemOtherCsvRow_ForbidType,
			ItemOtherCsvRow_ExistenceTimeType,
			ItemOtherCsvRow_ExistenceTime,
			ItemOtherCsvRow_SkillId,

			ItemOtherCsvRow_Max
		};
    public:
        ItemOtherTemplate(){;}
        ~ItemOtherTemplate();
        SINGLETON_INSTANCE(ItemOtherTemplate);

    public:
        Bool                    load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        const ItemOtherInfo*    getItemOtherInfo(ItemIdType tempID);



    private:
       SimpleMapDataSetManager<ItemIdType, ItemOtherInfo>        mItemOtherList;

    };

}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************