/******************************************************************************/
#ifndef _PATHFINDINGMANAGER_H_
#define _PATHFINDINGMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "PathFinder.h"
#include "PathFinder2.h"
#include "PathFinder21.h"
#include "IPathFindingManager.h"

/******************************************************************************/
namespace MG
{



    /******************************************************************************/
    //碰撞系统
    /******************************************************************************/
	class PathFindingManager : public IPathFindingManager
    {
    public:
        PathFindingManager( Scene* scene );
        virtual ~PathFindingManager();

        virtual void            load();
        virtual void            unLoad();
        
        void                    update(Flt delta);
		
		virtual PathFinder2*    getStaticPathFinder();
		virtual PathFinder21*    getDynamicPathFinder();

    protected:


    private:

        // 游戏场景
        Scene*                  mScene;
		PathFinder2*            mStaticPathFinder;
		PathFinder21*            mDynamicPathFinder;

    };
}

/******************************************************************************/

#endif
