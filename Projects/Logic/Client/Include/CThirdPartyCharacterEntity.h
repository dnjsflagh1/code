/******************************************************************************/
#ifndef _CTHIRDPARTYCHARACTERENTITY_H_
#define _CTHIRDPARTYCHARACTERENTITY_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "CCharacterSceneEntity.h"
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //第三方角色
    /******************************************************************************/
    class CThirdPartyCharacterEntity : public CCharacterSceneEntity
    {
    public:

        CThirdPartyCharacterEntity(IEntity* entity);
        virtual ~CThirdPartyCharacterEntity();

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

        ThirdPartyCharacterEntityData*      getDynamicData();
    
    
    };
}

#endif
