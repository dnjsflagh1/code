/******************************************************************************/
#ifndef _ICOMPOSITORMANAGER_H_
#define _ICOMPOSITORMANAGER_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //后期合成器管理器
    /******************************************************************************/
    class ICompositorManager
    {
    public:

        // 增加一个合成器
        virtual void	        addCompositor(Str name, Int addPosition=-1) = 0;

        // 设置合成器是否有效
        virtual void	        setCompositorEnable(Str name, Bool enable) = 0;
        // 设置合成器是否有效
        virtual void	        setCompositorEnable(Bool enable) = 0;
        
    };

}

/******************************************************************************/
#endif
