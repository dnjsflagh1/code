//**********************************************************************************************************
#ifndef _H_ITEMS_
#define _H_ITEMS_
//**********************************************************************************************************
#include "WorldCorePreqs.h"
//**********************************************************************************************************
namespace MG
{
    class Items
    {
    public:
        Items();
        virtual ~Items();

    public:      

        void                clear();

    public:
        //���
        virtual void        addItem(PlayerItem* pItem);
        //�Ƴ�����������һ���ط���
        PlayerItem*         removeItem(IdType itemDBID);
        PlayerItem*         removeItem(U32 index);
        //���� ���ɾ����־����
        ITEM_DELETE_ERROR   deleteItem(IdType itemID);
        ITEM_DELETE_ERROR   deleteItem(U32 index);
        //����
        PlayerItem*         findItem(IdType itemDBID);
        PlayerItem*         findItem(U32 index);
        PlayerItem*         findItemByTemplateId(U32 itemTemplateId);
		void                findItemByTemplateId(U32 itemTemplateId,std::vector<PlayerItem*>& itemList);
		U32                 getItemCount(U32 itemTemplateId);
        //�ı�λ��ʱ
        U32                 getFreeIndex();
       // void              setIndex(U32 index, IdType itemDBID);
        void                removeIndex(U32 index);
        U32                 getItemNum(){return mPlayerItemMap.size();}
		U32                 getItemResidueNum(){ return (mSize - mPlayerItemMap.size());}
        Bool                checkItemFull();
        Bool                checkCanAdd(U32 num);
        //���map
        std::map<IdType, PlayerItem*>*
                            getPlayerItemMap() {return &mPlayerItemMap;}
        void                setSize(U32 size){mSize = size;}
        U32                 getSize(){return mSize;}

        //test
        //void                printfItemDBID();

    private:
		std::map<IdType,PlayerItem*>       mPlayerItemMap;
		std::map<U32,IdType>               mIndexMap;
        
        U32                                mSize;

    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************