//*****************************************************************************************************
#ifndef _H_ITEM_RANDOM_TEMPLATE_
#define _H_ITEM_RANDOM_TEMPLATE_
//*****************************************************************************************************
#include "GameFilePreqs.h"
//*****************************************************************************************************
namespace MG
{
#define ITEM_RANDOM_NUM_BASE	100000		//随机概率	十万分比
    //--------------------------------------------------------------------------------------
    struct  ItemRandomInfo
    {
        U32                     ItemRandomID;                                       //随机id
        ITEM_RANDOM_USETYPE     useType;                                            //应用的类型id
        ITEM_RANDOM_TYPE        randomType;                                         //随机方式
        RandomGroup             groupArray[ITEM_RANDOM_GROUP_NUM];                  //随机群
    };
    //--------------------------------------------------------------------------------------
    class ItemRandomTemplate
    {
    public:
        ItemRandomTemplate(){;}
        ~ItemRandomTemplate();
        SINGLETON_INSTANCE(ItemRandomTemplate);

    public:
		// MG_CN_MODIFY
        Bool                    load(Str16 fileName, IMGExternalPackManager* packManager = NULL);                 
        Bool                    getItemRandomInfo(U32 randomId, std::vector<ItemNum>& info);
        Bool                    getItemRandomInfo(U32 randomId, std::list<ItemNum>& info);

    private:
        void                    clear();
        void                    randOnce(const ItemRandomInfo*& pInfo, std::vector<ItemNum>& info);
        void                    randOnce(const ItemRandomInfo*& pInfo, std::list<ItemNum>& info);
        void                    randEvery(const ItemRandomInfo*& pInfo, std::vector<ItemNum>& info);  
        void                    randEvery(const ItemRandomInfo*& pInfo, std::list<ItemNum>& info);

    private:
        std::map<U32, ItemRandomInfo*>    mItemRandomInfoMap;

    };
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************