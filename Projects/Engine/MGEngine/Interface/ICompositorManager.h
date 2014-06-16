/******************************************************************************/
#ifndef _ICOMPOSITORMANAGER_H_
#define _ICOMPOSITORMANAGER_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //���ںϳ���������
    /******************************************************************************/
    class ICompositorManager
    {
    public:

        // ����һ���ϳ���
        virtual void	        addCompositor(Str name, Int addPosition=-1) = 0;

        // ���úϳ����Ƿ���Ч
        virtual void	        setCompositorEnable(Str name, Bool enable) = 0;
        // ���úϳ����Ƿ���Ч
        virtual void	        setCompositorEnable(Bool enable) = 0;
        
    };

}

/******************************************************************************/
#endif
