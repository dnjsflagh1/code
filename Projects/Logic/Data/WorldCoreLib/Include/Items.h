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
        //添加
        virtual void        addItem(PlayerItem* pItem);
        //移除（放入另外一个地方）
        PlayerItem*         removeItem(IdType itemDBID);
        PlayerItem*         removeItem(U32 index);
        //销毁 添加删除标志即可
        ITEM_DELETE_ERROR   deleteItem(IdType itemID);
        ITEM_DELETE_ERROR   deleteItem(U32 index);
        //查找
        PlayerItem*         findItem(IdType itemDBID);
        PlayerItem*         findItem(U32 index);
        PlayerItem*         findItemByTemplateId(U32 itemTemplateId);
		void                findItemByTemplateId(U32 itemTemplateId,std::vector<PlayerItem*>& itemList);
		U32                 getItemCount(U32 itemTemplateId);
        //改变位置时
        U32                 getFreeIndex();
       // void              setIndex(U32 index, IdType itemDBID);
        void                removeIndex(U32 index);
        U32                 getItemNum(){return mPlayerItemMap.size();}
		U32                 getItemResidueNum(){ return (mSize - mPlayerItemMap.size());}
        Bool                checkItemFull();
        Bool                checkCanAdd(U32 num);
        //获得map
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