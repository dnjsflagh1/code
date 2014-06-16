

/******************************************************************************/
#ifndef _SPLAYER_FACTORY_H_
#define _SPLAYER_FACTORY_H_
/******************************************************************************/

#include "FrontServerPreqs.h"
#include "SPlayer.h"
/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //��ҹ���
    /******************************************************************************/
    class SPlayerFactory
    {
        friend class SPlayerPtr;
    public:
        SPlayerFactory();
        ~SPlayerFactory();

    public:

        void    createSPlayerPtr( SPlayerPtr& ptr,  AccountIdType accountId, I32 client_id, Str16& accName );
    
    protected:  

        void    destroySPlayerPtr( SPlayerPtr& ptr );

    private:    

        ObjectPool<SPlayer,false> mSPlayerPool;
        Critical    mSPlayerPoolCs;

    };



}

#endif