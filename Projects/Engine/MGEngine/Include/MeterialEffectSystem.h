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
    //����Ч��ϵͳ
    /******************************************************************************/
    class MeterialEffectSystem 
    {
    public:
        MeterialEffectSystem();
        virtual ~MeterialEffectSystem();
        SINGLETON_INSTANCE(MeterialEffectSystem)
    
    public:

        // ���ø���
        virtual void    setHightLight(Ogre::Entity* entity, Int level=1.0);
        
    };
}

/******************************************************************************/

#endif
