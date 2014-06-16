/******************************************************************************/
#ifndef _COMPOSITORMANAGER_H_
#define _COMPOSITORMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ICompositorManager.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    // 合成器管理者
    /******************************************************************************/
    class CompositorManager : public ICompositorManager
    {
    public:
        CompositorManager(Scene* scene);
        virtual ~CompositorManager();

    public:

        ////////////////////////////////////////////////////////////////////////////////////

        /// 更新
        void                    update( Flt delta );

        ////////////////////////////////////////////////////////////////////////////////////


        // 增加一个合成器
        virtual void	        addCompositor(Str name, Int addPosition=-1) ;

        // 设置合成器是否有效
        virtual void	        setCompositorEnable(Str name, Bool enable) ;
        // 设置合成器是否有效
        virtual void	        setCompositorEnable(Bool enable) ;

        // 判断是否有指定合成器
        virtual Bool	        hasCompositor(Str name) ;

        ////////////////////////////////////////////////////////////////////////////////////

    protected:		

        Scene* mScene;

        std::map<Str, CompositorInstance*> mCompositorList;
    };

}

/******************************************************************************/

#endif
