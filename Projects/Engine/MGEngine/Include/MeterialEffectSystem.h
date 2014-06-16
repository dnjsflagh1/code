/******************************************************************************/
#ifndef _METERIALEFFECTSYSTEM_H_
#define _METERIALEFFECTSYSTEM_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "Scene.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //材质效果系统
    /******************************************************************************/
    class MeterialEffectSystem 
    {
    public:
        MeterialEffectSystem();
        virtual ~MeterialEffectSystem();
        SINGLETON_INSTANCE(MeterialEffectSystem)
    
    public:

        // 设置高亮
        virtual void    setHightLight(Ogre::Entity* entity, Int level=1.0);
        
    };
}

/******************************************************************************/

#endif
