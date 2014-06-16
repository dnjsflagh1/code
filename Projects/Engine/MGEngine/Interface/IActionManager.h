/******************************************************************************/
#ifndef _IACTIONMANAGER_H
#define _IACTIONMANAGER_H
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "ISceneNodeAction.h"
#include "ISceneNode.h"

/******************************************************************************/

namespace MG
{
    

    /******************************************************************************/
    //”Œœ∑Actionπ‹¿Ì
    /******************************************************************************/
    class IActionManager
    {
    public:

        virtual ISceneNodeLineMoveToAction*     createSceneNodeLineMoveToAction(ISceneNode* node) = 0;
		virtual ISceneNodeGridLineMoveToAction* createSceneNodeGridLineMoveToAction(ISceneNode* node, IDynamicBlockObject* object = NULL) = 0;
        virtual ISceneNodeYawToAction*          createSceneNodeYawToAction(ISceneNode* node) = 0;
		virtual ISceneNodePitchToAction*        createSceneNodePitchToAction(ISceneNode* node) = 0;
		virtual ISceneNodeLineMoveToAction*     createSceneNodeParabolaMoveToAction(ISceneNode* node) = 0;
		virtual ISceneNodeDirectToAction*		createSceneNodeDirectToAction(ISceneNode* node) = 0;
		virtual void							destroySceneNodeDirectToAction(ISceneNodeDirectToAction* action) = 0;
        virtual ISceneNodePathFindingMoveInAdvanceAction*  
                                                createSceneNodePathFindingMoveInAdvanceAction( IDynamicBlockObject* object ) = 0;
		virtual void                            destroySceneNodePathFindingMoveInAdvanceAction(ISceneNodePathFindingMoveInAdvanceAction* action) = 0;

    };

}

/******************************************************************************/
#endif
