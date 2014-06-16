/******************************************************************************/
#ifndef _ICOLLISIONOBJECT_H_
#define _ICOLLISIONOBJECT_H_
/******************************************************************************/
#include "MGEngineInterfacePreqs.h"
/******************************************************************************/

namespace MG
{

    class ICollisionObject
    {
    public:
        virtual void						setEnable(Bool enable) = 0;
    };
    
}

/******************************************************************************/
#endif