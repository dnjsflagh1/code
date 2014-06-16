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
    // �����ڵ����Ѱ���ƶ���Ϊ
    // ֻ��Ϊ���߼��㣬����Ϊ��Ϊ
    /******************************************************************************/
    class SceneNodePathFindingMoveInAdvanceAction : public ISceneNodePathFindingMoveInAdvanceAction
    {
    public:
        SceneNodePathFindingMoveInAdvanceAction( IDynamicBlockObject* object );
        virtual ~SceneNodePathFindingMoveInAdvanceAction();

        /// ����Ŀ��� ���Ե���Ŀ����λ�õ������ƶ�����λ��
        virtual Bool        				setMoveToDestination( Vec3& dest, Bool isAdjuest );

        // ���㾲̬Ѱ·����
        virtual PathFindingResult           calculateStaticPathFinding();

        // ���㶯̬Ѱ·����
        virtual PathFindingResult           calculateDynamicPathFindingBetweenStaticNode();

		// ȥ��һ����̬Ŀ���
		virtual Vec3						goNextStaticDestination();
		// �Ƿ��Ѿ���������̬Ŀ���
		virtual Bool						isLastStaticDestination();
		// �������ڵľ�̬Ŀ���
		virtual void						setCurrStaticDestination( Vec3 pos );
		// ȥ��һ����̬Ŀ���
		virtual Vec3						getCurrStaticDestination();

		// ȥ��һ����̬Ŀ���
		virtual Vec3						goNextDynamicDestination();
		// �Ƿ��Ѿ���������̬Ŀ���
		virtual Bool						isLastDynamicDestination();
        // �õ����ڵĶ�̬Ŀ���
        virtual Vec3						getCurrDynamicDestination();

   
		// �������յľ�̬Ŀ���
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