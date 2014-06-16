

/******************************************************************************/
#ifndef _SWORLDOBJECTFACTORYMANAGER_H_
#define _SWORLDOBJECTFACTORYMANAGER_H_
/******************************************************************************/

#include "MapServerPreqs.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // 世界对象工厂管理器
    /******************************************************************************/
    class SWorldObjectFactoryManager
    {
    public:

        SWorldObjectFactoryManager();
        ~SWorldObjectFactoryManager();
        SINGLETON_INSTANCE(SWorldObjectFactoryManager);

        //-----------------------------------------------------------------------------

        Bool    initialize();
        Bool    unInitialize();
        void    update(Flt delta);

        //-----------------------------------------------------------------------------

        SPlayerFactory*     createSPlayerFactory();
        void                destroySPlayerFactory( SPlayerFactory* factory );


    protected:

        ObjectPool<SPlayerFactory,false> mSPlayerFactoryPool;
        Critical    mSPlayerFactoryPoolCs;
        
    };


}

#endif