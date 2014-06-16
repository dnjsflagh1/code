//********************************************************************************************************************
#ifndef _H_ACCESS_LIST_
#define _H_ACCESS_LIST_
//********************************************************************************************************************
#include "GameFilePreqs.h"
//********************************************************************************************************************
namespace MG
{
    //英文名	中文名	        用途简述
    //AccessId	线路ID	        线路的id
    //RoadName	线路名称	    线路的中文名称，16汉字以内
    //Type	    线路类型	    线路使用对象的类型，分为类型1：普通路（军队和角色都能通行）；类型2：军队专用路；类型3：角色专用路
    //PlaceAId	A地点ID	        线路一端地点的PlaceId
    //PlaceBId	B地点ID	        线路另一端地点的PlaceId
    //MapId	    副本id	        遭遇战时选用的副本地图id

    struct AccessInfo 
    {
        U32             AccessId    ;
        Str16           RoadName    ;
        ACCESS_TYPE     Type	    ;
        U32             PlaceAId    ;
        U32             PlaceBId    ;
        U32             MapId	    ;
    };
    //------------------------------------------------------------------------------------
    class AccessListCsv
    {
    public:
        AccessListCsv(){;}
        ~AccessListCsv();
        SINGLETON_INSTANCE(AccessListCsv);

    public:
		// MG_CN_MODIFY
        //加载place节点板表
        Bool                        load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        //获得place节点信息
        const AccessInfo*           getAccessInfo( U32 accessId );
        //获得place节点信息
        Bool                        getAccessInfo( U32 accessId, const AccessInfo*& info );
        //获得place的所有节点。
        std::map<U32, AccessInfo*>* getMapAccessInfo(){return &mMapAccessInfo;}

    protected:
        void                        clear();

    private:
        std::map<U32, AccessInfo*>  mMapAccessInfo;

    };
}
//********************************************************************************************************************
#endif
//********************************************************************************************************************