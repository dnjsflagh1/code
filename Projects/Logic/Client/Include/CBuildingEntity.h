/******************************************************************************/
#ifndef _CBATTLEBUILDINGENTITY_H_
#define _CBATTLEBUILDINGENTITY_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "CCharacterSceneEntity.h"
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //战斗建筑显示对象，只在据点地图中会出现
    /******************************************************************************/
    class CBuildingEntity : public CCharacterSceneEntity
    {
    public:

        CBuildingEntity(IEntity* entity);
        virtual ~CBuildingEntity();

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

        BuildingEntityData*         getDynamicData();

		CHAR_BUILD_TYPE				getBuildingType();

		Bool						isWall();


    };
}

#endif
