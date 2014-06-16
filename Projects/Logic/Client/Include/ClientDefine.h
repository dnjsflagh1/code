/******************************************************************************/
#ifndef _CLIENTDEFINE_H_
#define _CLIENTDEFINE_H_
/******************************************************************************/

#include "LinedState.h"

/******************************************************************************/
//游戏逻辑宏
/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	enum CampaignResult
	{
		CampaignResult_Init,

		CampaignResult_Win,
		CampaignResult_Lose,

		CampaignResult_Max
	};


    /******************************************************************************/
    //游戏幕间
    /******************************************************************************/
    class IScreen : public LinedStateObject
    {
    public:

        IScreen( Str name ):LinedStateObject(name){};

        // 当开始加载场景
        virtual void    onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType ) = 0;
        // 当结束加载场景
        virtual void    onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType ) = 0;
        /// 当卸载场景
        virtual void    onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType ) = 0;

    };

    /******************************************************************************/
    //游戏操作控制
    /******************************************************************************/
    class IOpCtrl
    {
    public:

        //操作更新
        virtual void    update( Flt delta ) = 0;
        //操作还原
        virtual void    revert(){};

        // 当开始加载场景
        virtual void    onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType ) {};
        // 当结束加载场景
        virtual void    onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType ) {};
        /// 当卸载场景
        virtual void    onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType ) {};

    };

}


/******************************************************************************/
#endif

