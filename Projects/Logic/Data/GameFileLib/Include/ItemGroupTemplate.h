//*****************************************************************************************************
#ifndef _H_ITEM_GROUP_TEMPLATE_
#define _H_ITEM_GROUP_TEMPLATE_
//*****************************************************************************************************
#include "GameFilePreqs.h"
//*****************************************************************************************************
namespace MG
{
    //--------------------------------------------------------------------------------------
    struct  ItemGroupInfo
    {
        ITEM_GROUP_USETYPE type;                                //使用类型
        U32     GroupID;                                        //群id
        IdType  ItemTemplateId;                                 //模板id
        U32     ItemNum;                                        //道具数量
    };
    //--------------------------------------------------------------------------------------
    class ItemGroupTemplate
    {
    public:
        ItemGroupTemplate(){;}
        ~ItemGroupTemplate();
        SINGLETON_INSTANCE(ItemGroupTemplate);

    public:
		// MG_CN_MODIFY
        Bool                                        load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        Bool                                        getItemGroupInfo(U32 groupId, std::vector<ItemNum>& info);
        Bool                                        getItemGroupInfo(U32 groupId, std::list<ItemNum>& info);
        Bool                                        getItemAndNum(U32 groupId, ItemNum& item);

		//yuanlinhu
		std::vector<const ItemGroupInfo*>*			getItemGroupListByGroupId(U32 groupId);

    private:
        void                                        clear();
        void                                        addItemGroupInfo(const ItemGroupInfo* pInfo);

    private:
        std::map<U32, std::vector<const ItemGroupInfo*>*>    mItemGroupInfoMap;
    };
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************