//*****************************************************************************************************************
#ifndef _H_ITEMSITETEMPLATE_
#define _H_ITEMSITETEMPLATE_
//*****************************************************************************************************************
#include "GameFilePreqs.h"
//*****************************************************************************************************************
namespace MG
{
    struct ItemSiteInfo
    {
	   U32                  Id              ;                
       ITEM_SITE_TYPE       SiteType        ;                //格位类型
       ITEM_REPLACE_TYPE    ReplaceType     ;                //替换类型
       U32                  MaxNum          ;                //上限
       U32                  DefaultNum      ;                //默认格数
       //-------------------------------------------------------------------------------
       ItemSiteInfo()
		   :Id(0)
		   ,SiteType(ITEM_SITE_TYPE_NULL)
           ,ReplaceType(ITEM_REPLACE_TYPE_NULL)
            ,MaxNum(0)    
            ,DefaultNum(0)
       {
           ;
       }
       //-------------------------------------------------------------------------------
       ItemSiteInfo& operator=(const ItemSiteInfo& A)
       {
		    Id                          =  A.Id             ;
			SiteType                    =  A.SiteType       ;
            ReplaceType                 =  A.ReplaceType    ;
            MaxNum                      =  A.MaxNum         ;
            DefaultNum                  =  A.DefaultNum     ;

            return *this;
       }
    };
    //-------------------------------------------------------------------------------------------
    class ItemSiteTemplate
    {
    public:
        ItemSiteTemplate(){;}
        ~ItemSiteTemplate(){;}
        SINGLETON_INSTANCE(ItemSiteTemplate);

    public:
		// MG_CN_MODIFY
        Bool                load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        const ItemSiteInfo* getItemSiteInfo(ITEM_SITE_TYPE siteID);
        Bool                getItemSiteInfo(ITEM_SITE_TYPE siteID, const ItemSiteInfo* info);

    private:   
        ItemSiteInfo  mItemSiteInfoMap[ITEM_SITE_TYPE_MAX];

    };
}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************