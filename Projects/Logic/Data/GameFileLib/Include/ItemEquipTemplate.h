//*****************************************************************************************************************
#ifndef _H_ITEM_EQUIP_TEMPLATE_
#define _H_ITEM_EQUIP_TEMPLATE_
//*****************************************************************************************************************
#include "GameFilePreqs.h"
//*****************************************************************************************************************
namespace MG
{
    //���	    ��������	                            ������
    //1	        ItemEquipId                          װ������Ʒid
    //2	        Name                                 װ�����ƣ�16��������
    //3	        Text                                 "����������64�����ڣ�֧��ת�壬
    //4	        ArtIconId                            �ṩָ����ɫ�����������Ĺ��ܡ�"
    //5	        ArtMashId1                           װ����icon����ӦIcon���Icon
    //6	        ArtMashId2                           װ������ʾ��ģ��id,����������ʱ��ģ��
    //7	        ArtMashId3                           װ������ʾ��ģ��id,������Ů��ʱ��ģ��װ���������ģ��
    //8	        Price                                װ���Ļ�����ֵ
    //9	        BuyPrice                             װ�����򻨷ѣ����ĵ�����Ϸ��
    //10	    SellPrice                            װ�����ۻ��ѣ����ĵ�����Ϸ��
    //11	    RepairPrice                          װ�������ѣ����ĵ�����Ϸ�ң�100%�𻵵ķ���
    //13	    MaxUpGrade                           װ�������ǿ��������0��ʾ����ǿ��
    //14	    MaxFixNum                            װ��������������
    //15	    MaxEquipDurable                      װ��������;ã�0��ʾ���;�
    //16	    Score                                װ�����ֵȼ�
    //17	    Rank                                 "װ����Ʒ����𣬵�ѡ1~�ס�2~�̡�3~����4~��"
    //18	    Class                                "װ�������ͣ���ѡ����������"
    //19	    EquipSlotType                        "װ����Ӧ�ĵĸ�λ����ѡ���ݶ�Ϊ1~��������2~��������3~������4~����5~ͷ����6~���壬7~�㲿��8~����"
    //20	    SuitId                               ��װ����Ʒ��������һ����װ����װ�����
    //22	    DisappearType                        "������λ�ж�����ʧ��ʽ����ѡ����������ʧ��������Ʒ�����Զ���ʧ"
    //23	    ForBidType                           "������λ�ж���֧�ֹ��ܣ���ѡ������λ�ж��ģ���֧����Ӧ����"
    //24	    ExistenceTimeType                    "��Ʒ���ڵ�ʱ�����ͣ���ѡ1~��ʵʱ�䣬2~��Ϸʱ��"
    //25	    ExistenceTime                        ���ڵ�������ʱ�䵽��װ����ʧ��ʧЧ
    //26	    ClanJudgeid                          װ��ʱ�������Ҫ��
    //27	    CharacterJudgeid                     װ��ʱ�Խ�ɫ��Ҫ��
    //28	    AbilityAppendId1                     װ������������Ը���id
    //29	    AbilityAppendGroupId1                װ������ʱ����������Ը���id
    //30	    AbilityAppendId2                     װ��ǿ�������Ը���id
    //31	    AbilityAppendGroupId2                װ�����ǿ�������Ը���id
    //32	    SkillTemplateID                      װ�������ļ���id
    //33	    StateTemplateID                      װ��������״̬id
    //34	    StateTemplateNum                     �����״̬����
    //35	    WeaponActionId                       װ�����µĹ��������ı�
    //36	    EquipSprit                           װ������������ܽű�
                                            
    //-------------------------------------------------------------------------------
    struct ItemEquipInfo                  
    {                                
        ItemIdType						ItemEquipId               	            ;                            
        Str16                           Name                                    ;
        Str16                           Text                                    ;
		Int								ArtIconId								;
        U32                             ArtMashId1                              ;
        U32                             ArtMashId2                              ;
        U32                             ArtMashId3                              ;
        U64                             Price                                   ;
        U64                             BuyPrice                                ;
        U64                             SellPrice                               ;
        U64                             RepairPrice                             ;
        U64                             MaxUpGrade                              ;
        U64                             MaxFixNum                               ;
        U64                             MaxEquipDurable                         ;
        U64                             Score                                   ;
        ITEM_RANK                       Rank                                    ;
        ITEM_EQUIP_CLASS                Class                                   ;
        ITEM_EQUIP_SLOT_TYPE            EquipSlotType                           ;
        U32                             SuitId                                  ;
        ITEM_BIND_TYPE                  BindType                                ;
        U32                             DisappearType                           ;
        U32                             ForBidType                              ;
        ITEM_EXISTENCE_TIME_TYPE        ExistenceTimeType                       ;
        U32                             ExistenceTime                           ;
        U32                             ClanJudgeid                             ;
        U32                             CharacterJudgeid                        ;
        U32                             AbilityAppendId1                        ;
        U32                             AbilityAppendGroupId1                   ;  
        U32                             AbilityAppendId2                        ;
        U32                             AbilityAppendGroupId2                   ;
        U32                             SkillTemplateID                         ;  
        U32                             StateTemplateID                         ;
        U64                             StateTemplateNum                        ;
        U32                             WeaponActionId                          ;
        Str16                           EquipSprit                              ;
    };
    //-------------------------------------------------------------------------------
    class ItemEquipTemplate
    {
		enum ItemEquipCsvRow
		{
			ItemEquipCsvRow_ItemEquipId               	,
			ItemEquipCsvRow_Notes						,
			ItemEquipCsvRow_Name                        ,
			ItemEquipCsvRow_Text                        ,
			ItemEquipCsvRow_ArtIconId					,
			ItemEquipCsvRow_ArtMashId1					,                 
			ItemEquipCsvRow_ArtMashId2					,                
			ItemEquipCsvRow_ArtMashId3					,               
			ItemEquipCsvRow_Price						,              
			ItemEquipCsvRow_BuyPrice					,             
			ItemEquipCsvRow_SellPrice					,            
			ItemEquipCsvRow_RepairPrice					,           
			ItemEquipCsvRow_MaxUpGrade					,          
			ItemEquipCsvRow_MaxFixNum					,         
			ItemEquipCsvRow_MaxEquipDurable				,        
			ItemEquipCsvRow_Score						,       
			ItemEquipCsvRow_Rank						,      
			ItemEquipCsvRow_Class						,     
			ItemEquipCsvRow_EquipSlotType				,    
			ItemEquipCsvRow_SuitId						,   
			ItemEquipCsvRow_BindType					,  
			ItemEquipCsvRow_DisappearType				, 
			ItemEquipCsvRow_ForBidType                  ,
			ItemEquipCsvRow_ExistenceTimeType           ,
			ItemEquipCsvRow_ExistenceTime               ,
			ItemEquipCsvRow_ClanJudgeid                 ,
			ItemEquipCsvRow_CharacterJudgeid            ,
			ItemEquipCsvRow_AbilityAppendId1            ,
			ItemEquipCsvRow_AbilityAppendGroupId1       ,
			ItemEquipCsvRow_AbilityAppendId2            ,
			ItemEquipCsvRow_AbilityAppendGroupId2       ,
			ItemEquipCsvRow_SkillTemplateID             ,
			ItemEquipCsvRow_StateTemplateID             ,
			ItemEquipCsvRow_StateTemplateNum            ,
			ItemEquipCsvRow_WeaponActionId              ,
			ItemEquipCsvRow_EquipSprit                  ,
			
			ItemEquipCsvRow_Max
		};
    public:
        ItemEquipTemplate(){;}
        ~ItemEquipTemplate();
        SINGLETON_INSTANCE(ItemEquipTemplate);

    public:
        Bool                    load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        const ItemEquipInfo*    getItemEquipInfo(ItemIdType tempID);

    private:
        SimpleMapDataSetManager<ItemIdType, ItemEquipInfo>        mItemEquipList;

    };

}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************