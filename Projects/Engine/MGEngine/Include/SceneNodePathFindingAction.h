/******************************************************************************/
#ifndef _SCENENODEPATHFINDINGACTION_H_
#define _SCENENODEPATHFINDINGACTION_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ISceneNodeAction.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    // 场景节点对象寻径移动行为
    // 只作为离线计算，不作为行为
    /******************************************************************************/
    class SceneNodePathFindingMoveInAdvanceAction : public ISceneNodePathFindingMoveInAdvanceAction
    {
    public:
        SceneNodePathFindingMoveInAdvanceAction( IDynamicBlockObject* object );
        virtual ~SceneNodePathFindingMoveInAdvanceAction();

        /// 设置目标点 可以调整目标点的位置到可以移动到的位置
        virtual Bool        				setMoveToDestination( Vec3& dest, Bool isAdjuest );

        // 计算静态寻路数据
        virtual PathFindingResult           calculateStaticPathFinding();

        // 计算动态寻路数据
        virtual PathFindingResult           calculateDynamicPathFindingBetweenStaticNode();

		// 去下一个静态目标点
		virtual Vec3						goNextStaticDestination();
		// 是否已经是最后个静态目标点
		virtual Bool						isLastStaticDestination();
		// 设置现在的静态目标点
		virtual void						setCurrStaticDestination( Vec3 pos );
		// 去下一个动态目标点
		virtual Vec3						getCurrStaticDestination();

		// 去下一个动态目标点
		virtual Vec3						goNextDynamicDestination();
		// 是否已经是最后个动态目标点
		virtual Bool						isLastDynamicDestination();
        // 得到现在的动态目标点
        virtual Vec3						getCurrDynamicDestination();

   
		// 设置最终的静态目标点
		virtual void						setFinalStaticDestination( Vec3 pos );

    protected:

        ISceneNode*							mSceneNode;

		IDynamicBlockObject*				mDynamicBlockObject;

		Vec3								mMoveDestination;

		Int									mCurrStaticDestinationIndex;
		Int									mCurrDynamicDestinationIndex;

		std::vector<Vec3>				    mStaticMoveNodeList;
		std::vector<Vec3>				    mDynamicMoveNodeList;

    };



}

/******************************************************************************/

#endif