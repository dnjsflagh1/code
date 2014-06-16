/******************************************************************************/
#ifndef _ACTIONMANAGER_H_
#define _ACTIONMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "LinedState.h"
#include "ObjectPool.h"

#include "IActionManager.h"

#include "SceneNodePathFindingAction.h"
#include "SceneNodeSpecialMoveAction.h"
#include "SceneNodeAction.h"
#include "ScenceNodeGridLineMoveToAction.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //场景节点对象移动行为
    /******************************************************************************/
    class ActionManager : public IActionManager , public LinedStateObjectListener
    {
    public:
        ActionManager( Scene* scene );
        virtual ~ActionManager();

    public:
        
        virtual SceneNodeLineMoveToAction*          createSceneNodeLineMoveToAction(ISceneNode* node);
        virtual void                                destroySceneNodeLineMoveToAction(SceneNodeLineMoveToAction* action);

        virtual ISceneNodeGridLineMoveToAction*     createSceneNodeGridLineMoveToAction(ISceneNode* node, IDynamicBlockObject* object = NULL);
        virtual void                                destroySceneNodeGridLineMoveToAction(SceneNodeGridLineMoveToAction* action);

		virtual SceneNodeParabolaMoveToAction*		createSceneNodeParabolaMoveToAction(ISceneNode* node);
		virtual void                                destroySceneNodeParabolaMoveToAction(SceneNodeParabolaMoveToAction* action);

        virtual SceneNodeYawToAction*               createSceneNodeYawToAction(ISceneNode* node);
        virtual void                                destroySceneNodeYawToAction(SceneNodeYawToAction* action);

		virtual SceneNodePitchToAction*             createSceneNodePitchToAction(ISceneNode* node);
		virtual void                                destroySceneNodePitchToAction(SceneNodePitchToAction* action);

		virtual SceneNodeDirectToAction*			createSceneNodeDirectToAction(ISceneNode* node);
		virtual void								destroySceneNodeDirectToAction(ISceneNodeDirectToAction* action);

        virtual SceneNodePathFindingMoveInAdvanceAction* 
                                                    createSceneNodePathFindingMoveInAdvanceAction( IDynamicBlockObject* object );
        virtual void                                destroySceneNodePathFindingMoveInAdvanceAction(ISceneNodePathFindingMoveInAdvanceAction* action);

        ///////////////////////////////////////////////////////////////////////////////////

    protected:

        virtual void    onLinedStateLifeTimeOver(LinedStateObject* obj);

    protected:

        ObjectPool<SceneNodeGridLineMoveToAction>	        mSceneNodeGridLineMoveToActionPool;
		ObjectPool<SceneNodeLineMoveToAction>	            mSceneNodeLineMoveToActionPool;
		ObjectPool<SceneNodeParabolaMoveToAction>	        mSceneNodeParabolaMoveToActionPool;
        ObjectPool<SceneNodeYawToAction>	                mSceneNodeYawToActionPool;
		ObjectPool<SceneNodePitchToAction>					mSceneNodePitchToActionPool;
        ObjectPool<SceneNodePathFindingMoveInAdvanceAction>	mSceneNodePathFindingMoveInAdvanceActionPool;
		ObjectPool<SceneNodeDirectToAction>					mSceneNodeDirectToActionPool;

    private:

        // 游戏场景
        Scene*                  mScene;

    };

}

/******************************************************************************/

#endif