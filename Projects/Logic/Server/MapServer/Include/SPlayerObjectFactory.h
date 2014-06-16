

/******************************************************************************/
#ifndef _SPLAYER_OBJECT_FACTORY_H_
#define _SPLAYER_OBJECT_FACTORY_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "ObjectPool.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //Íæ¼Ò¹¤³§
    /******************************************************************************/
    class SPlayerFactory
    {

        friend class SPlayerPtr;

    public:

        SPlayerFactory();
        ~SPlayerFactory();

    public:

        void    createSPlayerPtr( SPlayerPtr& ptr, 
                                    AccountIdType accountId, 
                                    I32 frontId, 
                                    I32 client_id,
                                    U64 clanId  );

    protected:  

        void    destroySPlayerPtr( SPlayerPtr& ptr );

    private:    

        ObjectPool<SPlayer,false> mSPlayerPool;
        Critical    mSPlayerPoolCs;

    };



}

#endif