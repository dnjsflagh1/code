/******************************************************************************/
#include "stdafx.h"
#include "SceneNodeAction.h"
#include "MGSceneNode.h"
#include "MGEngineUtility.h"
#include "ISceneNode.h"
#include "IScene.h"
#include "ActionManager.h"
#include "LinedState.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    ActionManager::ActionManager( Scene* scene )
        :mScene(scene)
    {

    }

    //-----------------------------------------------------------------------
    ActionManager::~ActionManager()
    {

    }

    //-----------------------------------------------------------------------
    SceneNodeLineMoveToAction* ActionManager::createSceneNodeLineMoveToAction(ISceneNode* node)
    {
        SceneNodeLineMoveToAction* action = MG_POOL_NEW(mSceneNodeLineMoveToActionPool, SceneNodeLineMoveToAction, (node));

        action->setManagedLifeTime( false );
        action->addListener( this );

        return action;
    }

    //-----------------------------------------------------------------------
    void ActionManager::destroySceneNodeLineMoveToAction(SceneNodeLineMoveToAction* action)
    {
        MG_POOL_DELETE(mSceneNodeLineMoveToActionPool, action);
    }

	//-----------------------------------------------------------------------
	ISceneNodeGridLineMoveToAction* ActionManager::createSceneNodeGridLineMoveToAction(ISceneNode* node, IDynamicBlockObject* object)
	{
		SceneNodeGridLineMoveToAction* action = MG_POOL_NEW(mSceneNodeGridLineMoveToActionPool, SceneNodeGridLineMoveToAction, (node, object));

		action->setManagedLifeTime( false );
		action->addListener( this );

		return action;
	}

	//-----------------------------------------------------------------------
	void ActionManager::destroySceneNodeGridLineMoveToAction(SceneNodeGridLineMoveToAction* action)
	{
		MG_POOL_DELETE(mSceneNodeGridLineMoveToActionPool, action);
	}

	//-----------------------------------------------------------------------
	SceneNodeParabolaMoveToAction* ActionManager::createSceneNodeParabolaMoveToAction(ISceneNode* node)
	{
		SceneNodeParabolaMoveToAction* action = MG_POOL_NEW(mSceneNodeParabolaMoveToActionPool, SceneNodeParabolaMoveToAction, (node));

		action->setManagedLifeTime( false );
		action->addListener( this );

		return action;
	}

	//-----------------------------------------------------------------------
	void ActionManager::destroySceneNodeParabolaMoveToAction(SceneNodeParabolaMoveToAction* action)
	{
		MG_POOL_DELETE(mSceneNodeParabolaMoveToActionPool, action);
	}


    //-----------------------------------------------------------------------
    SceneNodeYawToAction* ActionManager::createSceneNodeYawToAction(ISceneNode* node)
    {
        SceneNodeYawToAction* action = MG_POOL_NEW(mSceneNodeYawToActionPool, SceneNodeYawToAction, (node));

        action->setManagedLifeTime( false );
        action->addListener( this );

        return action;
    }

	//-----------------------------------------------------------------------
	SceneNodePitchToAction* ActionManager::createSceneNodePitchToAction(ISceneNode* node)
	{
		SceneNodePitchToAction* action = MG_POOL_NEW(mSceneNodeYawToActionPool, SceneNodePitchToAction, (node));

		action->setManagedLifeTime( false );
		action->addListener( this );

		return action;
	}


	//-----------------------------------------------------------------------
	SceneNodeDirectToAction* ActionManager::createSceneNodeDirectToAction(ISceneNode* node)
	{
		SceneNodeDirectToAction* action = MG_POOL_NEW(mSceneNodeDirectToActionPool, SceneNodeDirectToAction, (node));

		action->setManagedLifeTime( false );
		action->addListener( this );

		return action;
	}

    //-----------------------------------------------------------------------
    void ActionManager::destroySceneNodeYawToAction(SceneNodeYawToAction* action)
    {
        MG_POOL_DELETE(mSceneNodeYawToActionPool, action);
    }

	//-----------------------------------------------------------------------
	void ActionManager::destroySceneNodePitchToAction(SceneNodePitchToAction* action)
	{
		MG_POOL_DELETE(mSceneNodePitchToActionPool, action);
	}

	//-----------------------------------------------------------------------
	void ActionManager::destroySceneNodeDirectToAction(ISceneNodeDirectToAction* iaction)
	{
		SceneNodeDirectToAction* action = dynamic_cast<SceneNodeDirectToAction*>(iaction);
		MG_POOL_DELETE(mSceneNodeDirectToActionPool, action);
	}

    //-----------------------------------------------------------------------
    SceneNodePathFindingMoveInAdvanceAction* ActionManager::createSceneNodePathFindingMoveInAdvanceAction( IDynamicBlockObject* object)
    {
        SceneNodePathFindingMoveInAdvanceAction* action = MG_POOL_NEW(mSceneNodePathFindingMoveInAdvanceActionPool, SceneNodePathFindingMoveInAdvanceAction, (object));

        return action;
    }

    //-----------------------------------------------------------------------
    void ActionManager::destroySceneNodePathFindingMoveInAdvanceAction(ISceneNodePathFindingMoveInAdvanceAction* action)
    {
		SceneNodePathFindingMoveInAdvanceAction* tempAction = (SceneNodePathFindingMoveInAdvanceAction*)action;
        MG_POOL_DELETE(mSceneNodePathFindingMoveInAdvanceActionPool, tempAction);
    }

    //-----------------------------------------------------------------------
    void ActionManager::onLinedStateLifeTimeOver(LinedStateObject* obj)
    {
        if ( obj->getName() == SceneNodeLineMoveToAction::STATE_NAME )
        {
            destroySceneNodeLineMoveToAction((SceneNodeLineMoveToAction*)obj);
        }else
        if ( obj->getName() == SceneNodeGridLineMoveToAction::STATE_NAME )
        {
            destroySceneNodeGridLineMoveToAction((SceneNodeGridLineMoveToAction*)obj);
        }else 
        if ( obj->getName() == SceneNodeParabolaMoveToAction::STATE_NAME )
        {
            destroySceneNodeParabolaMoveToAction((SceneNodeParabolaMoveToAction*)obj);
        }else 
        if ( obj->getName() == SceneNodeYawToAction::STATE_NAME )
        {
            destroySceneNodeYawToAction((SceneNodeYawToAction*)obj);
        }else 
        if ( obj->getName() == SceneNodePitchToAction::STATE_NAME )
		{
			destroySceneNodePitchToAction((SceneNodePitchToAction*)obj);
		}
		else
		if ( obj->getName() == SceneNodeDirectToAction::STATE_NAME  )
		{
			destroySceneNodeDirectToAction((SceneNodeDirectToAction*)obj);
		}
    }

	//-----------------------------------------------------------------------

}