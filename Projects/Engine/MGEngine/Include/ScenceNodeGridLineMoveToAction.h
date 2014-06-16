/******************************************************************************/
#ifndef _SCENCENODEGRIDLINEMOVETOACTION_H_
#define _SCENCENODEGRIDLINEMOVETOACTION_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "LinedState.h"
#include "ISceneNodeAction.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//�����ڵ�����ƶ���Ϊ
	/******************************************************************************/
	class SceneNodeGridLineMoveToAction : public ISceneNodeGridLineMoveToAction
	{
	public:

		SceneNodeGridLineMoveToAction( ISceneNode* sceneNode, IDynamicBlockObject* dynamicBlockobject = NULL);
		virtual ~SceneNodeGridLineMoveToAction();
		//״̬����
		static Str STATE_NAME;

	public:

		/// �����ƶ��ٶ�
		void                            setMoveSpeed( Flt speed );
		/// �ƶ���ָ��λ��
		void                            setMoveToDestination( const Vec3& dest );
		/// �����Ƿ�������
		void                            setStickTerrain( Bool isStickTerrain );
		/// �����Ƿ���Ը߶Ȳ�, ֻ����2ά����
		void				            setIgnoreHeight( Bool isIgnoreHeight );

		void							setMoveToPathFindType( MoveToPathFindType moveToPathFindType );
        /// �Ƿ�ֹͣ��
        Bool                            isBlockStop();
        /// �����Ƿ�����ײ
        void                            setBlockCheck( Bool enable );
        /// �����Ƿ�������ײ�ȴ����������false,�����ϰ����˳�action
        void                            setIsWait( Bool enable );

		Bool                            getIsWait();


		Bool							getIsMoving();

		// �����Ƿ������Ŷ���
		void							setPerturbEnable( Bool isPerturb );
		// �����Ŷ��ݰ뾶
		void							setPerturbRadiu( Flt radiu );
		// �����Ŷ���Ƶ��
		void							setPerturbFrequnce( UInt freq );

	protected:

		///�����¼�
		virtual void                    update( Flt delta );
		///�Ƿ������
		virtual Bool                    isFinished();
		///��ȥ״̬�¼�
		virtual void                    onEnter();
		///�뿪״̬�¼�
		virtual void                    onLeave();

		virtual void					onLinedStateChanged(LinedStateObject* obj);

		void							notifyMoveToStateChange();

    protected:

        // ˢ��ʽ�����ϰ�
        Bool                            checkAndRefreshBlock( Vec3 src, Vec3 dest );
        // ��ռʽ�����ϰ�
        Bool                            checkAndGrabBlock( Vec3 src, Vec3 dest );

	protected:

        // �ϰ��������
		BlockManager*		   			 mBlockManager;
        // �����ڵ����
		ISceneNode*			   			 mSceneNode;
        // ��̬�ϰ�����
		IDynamicBlockObject*			 mDynamicBlockObject;
        // ��̬�ϰ������Ƿ�����ײ
        Bool                             mBlockEnable;   
		/// �Ƿ��ƶ�
		Bool				   			 mIsMoving;
		/// �ƶ���ʼ��λ��
		Vec3				   			 mMoveStartPosition;
		/// �ƶ���Ŀ��λ��
		Vec3				   			 mMoveDestination;
		/// �ƶ��ĳ���
		Flt					   			 mMoveLength;
		/// ��ǰ�ƶ��ĳ���
		Flt					   			 mCurrMoveLength;
		/// �ƶ��ķ���
		Vec3				   			 mMoveVelocity;
        /// �ƶ��ĵ�λ����
        Vec3				   			 mMoveVelocityN;
        /// �ƶ������ײ�ķ���
        Vec3				   			 mMoveCheckBlockVelocity;

		/// �ƶ����ٶ�
		Flt					   			 mMoveSpeed;
		/// �Ƿ�������
		Bool				   			 mIsStickTerrain;
		/// �Ƿ���Ը߶�
		Bool				   			 mIsIgnoreHeight;

        // �Ƿ����ϰ�
        Bool                             mIsRefreshBlock;
		/// �Ƿ������Ŷ���
		Bool                             mIsPerturbGrass;
		/// �Ŷ��뾶
		Flt								 mPerturbRadiu;
		/// �Ŷ�Ƶ��(ÿ�뼸��)
		UInt							 mPerturbFrequnce;
		/// ���һ���Ŷ�ʱ��
		clock_t							 mLastPerturbTime;

        // �����Ƿ������ϰ�ֹͣ
        Bool                             mIsWait;
        // �����Ƿ�����ײ
        Bool                             mIsBlockCheck;

		Flt					   			 mSceneNodeRadius;
		Int					   			 mBlockDiameter;
		std::vector<PassGridBlock>		 mPassBlockGridList;
		UInt							 mCurrPassGridBlockListIndex;
		UInt							 mNextPassGridBlockIndex;

		MoveToPathFindType				mMoveToPathFindType;

	};
}

/******************************************************************************/

#endif
