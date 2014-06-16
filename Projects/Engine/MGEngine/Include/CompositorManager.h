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
    // �ϳ���������
    /******************************************************************************/
    class CompositorManager : public ICompositorManager
    {
    public:
        CompositorManager(Scene* scene);
        virtual ~CompositorManager();

    public:

        ////////////////////////////////////////////////////////////////////////////////////

        /// ����
        void                    update( Flt delta );

        ////////////////////////////////////////////////////////////////////////////////////


        // ����һ���ϳ���
        virtual void	        addCompositor(Str name, Int addPosition=-1) ;

        // ���úϳ����Ƿ���Ч
        virtual void	        setCompositorEnable(Str name, Bool enable) ;
        // ���úϳ����Ƿ���Ч
        virtual void	        setCompositorEnable(Bool enable) ;

        // �ж��Ƿ���ָ���ϳ���
        virtual Bool	        hasCompositor(Str name) ;

        ////////////////////////////////////////////////////////////////////////////////////

    protected:		

        Scene* mScene;

        std::map<Str, CompositorInstance*> mCompositorList;
    };

}

/******************************************************************************/

#endif
