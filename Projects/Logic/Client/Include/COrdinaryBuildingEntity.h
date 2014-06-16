/******************************************************************************/
#ifndef _CORDINARYBUILDINGENTITY_H_
#define _CORDINARYBUILDINGENTITY_H_
/******************************************************************************/
#include "ClientPreqs.h"
#include "NoCharacterSceneEntity.h"
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //普通建筑显示对象
    /******************************************************************************/
    class COrdinaryBuildingEntity : public CNoCharacterSceneEntity
    {
    public:
        COrdinaryBuildingEntity( IEntity* entity );
        virtual ~COrdinaryBuildingEntity();

    public:

        //×××××××××××××××××××××××××××××××××××××××××××××××××
        //  [主要方法]
        //×××××××××××××××××××××××××××××××××××××××××××××××××

        // 初始化
        virtual void				        initialize();
        // 反初始化
        virtual void				        unInitialize();

        //×××××××××××××××××××××××××××××××××××××××××××××××××
        //  [基础属性]
        //×××××××××××××××××××××××××××××××××××××××××××××××××

        // 得到数据
        OrdinaryBuildingEntityData*         getDynamicData();

    };
}

#endif