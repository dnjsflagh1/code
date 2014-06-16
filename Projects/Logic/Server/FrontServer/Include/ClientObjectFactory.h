

/******************************************************************************/
#ifndef _CLIENTOBJECTFACTORY_H_
#define _CLIENTOBJECTFACTORY_H_
/******************************************************************************/

#include "FrontServerPreqs.h"
//
/******************************************************************************/

namespace MG
{

	class ClientObject;
    /******************************************************************************/
    //客户端工厂
    /******************************************************************************/
    class ClientObjectFactory
    {

        friend class ClientObjectPtr;

    public:

        ClientObjectFactory();
        ~ClientObjectFactory();

    public:

        void    creatClientObject( ClientObjectPtr& ptr, I32 client_id );

    protected:  
        
        void    destroyClientObject( ClientObjectPtr& ptr );
        
    private:    

        ObjectPool<ClientObject,false> mClientObjectPool;
        Critical    mClientObjectPoolCs;
        
    };



}

#endif