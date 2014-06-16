/******************************************************************************/
#ifndef _ISCENENODEACTION_H
#define _ISCENENODEACTION_H
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "LinedState.h"
#include "IPathFinder.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //ISceneNodeLineMoveAction
    /******************************************************************************/
    class ISceneNodeLineMoveToAction : public LinedStateObject, public LinedStateObjectListener
    {
    public:

        ISceneNodeLineMoveToAction(Str name)
            :LinedStateObject( name )
        {
        }
        /// �����ƶ��ٶ�
        virtual void                    setMoveSpeed( Flt speed ) = 0;
        /// �ƶ���ָ��λ��
        virtual void                    setMoveToDestination( const Vec3& dest ) = 0;
        /// �����Ƿ�������
        virtual void                    setStickTerrain( Bool isStickTerrain ) = 0;
		// �����Ƿ���Ը߶ȣ� ֻ����2ά��������
		virtual void		            setIgnoreHeight( Bool isIgnoreHeight ) = 0;
		// �����Ƿ������Ŷ���
		virtual void		            setPerturbEnable( Bool isPerturb ) = 0;
		// �����Ŷ��ݰ뾶
		virtual void		            setPerturbRadiu( Flt radiu ) = 0;
		// �����Ŷ���Ƶ��
		virtual void		            setPerturbFrequnce( UInt freq ) = 0;
    };

    /******************************************************************************/
    //ISceneNodeGridLineMoveToAction
    /******************************************************************************/
    class ISceneNodeGridLineMoveToAction : public ISceneNodeLineMoveToAction
    {
    public:
		enum MoveToPathFindType
		{
			PFT_NULL,
			PFT_DYNAMIC,
			PFT_STATIC,
			PFT_NOPATHFIND,
		};


		////////////////////////////////////////////////////////

        ISceneNodeGridLineMoveToAction(Str name)
            :ISceneNodeLineMoveToAction( name )
        {
        }
        /// �����Ƿ�����ײ
        virtual void                    setBlockCheck( Bool enable ) = 0;
        /// �����Ƿ�������ײ�ȴ����������false,�����ϰ����˳�action
        virtual void                    setIsWait( Bool enable ) = 0;

		virtual void					setMoveToPathFindType( MoveToPathFindType moveToPathFindType ) = 0;

        /// �Ƿ�ֹͣ��
        virtual Bool                    isBlockStop() = 0;
    };

    /******************************************************************************/
    //ISceneNodeYawToAction
    /******************************************************************************/
    class ISceneNodeYawToAction : public LinedStateObject
    {
    public:
        ISceneNodeYawToAction(Str name)
            :LinedStateObject( name )
        {
        }

        /// ����Y��ת���ٶ�
        virtual void        setYawSpeed( Flt speed ) = 0;
        /// Χ��Y��ת��ָ������������ʾ��ʱ��ת����������ʾ˳ʱ��ת��
        virtual void        setYawToDirection( const Vec3& dir ) = 0;
        /// Χ��Y��ת��ָ������������ʾ��ʱ��ת����������ʾ˳ʱ��ת��
        virtual void        setYawToDirection( const Vec3& startPos, const Vec3& endPos ) = 0;
        /// Χ��Y��ת��ָ��λ��
        virtual void        setYawToPosition( const Vec3& pos ) = 0;
        /// �����Ƿ�����
        virtual void        setIsImmediately( Bool isImmediately ) = 0;
    };

	/******************************************************************************/
	//ISceneNodePitchToAction
	/******************************************************************************/
	class ISceneNodePitchToAction : public LinedStateObject
	{
	public:
		ISceneNodePitchToAction(Str name)
			:LinedStateObject( name )
		{
		}

		/// ����X��ת���ٶ�
		virtual void        setPitchSpeed( Flt speed ) = 0;
		/// Χ��X��ת��ָ��λ��
		virtual void        setDestAngle( Flt angle ) = 0;
		/// ���Ƿ�����
		virtual void        setIsImmediately( Bool isImmediately ) = 0;
	};

	/******************************************************************************/
	//ISceneNodeLookAtToAction
	/******************************************************************************/
	class ISceneNodeDirectToAction : public LinedStateObject
	{
	public:
		ISceneNodeDirectToAction(Str name)
			:LinedStateObject( name )
		{
		}
		/// �Ƿ����
		virtual Bool		isFinished() = 0;

		/// ����ת���ٶ�
		virtual void		setShiftSpeed( Flt speed ) = 0;

		/// ��ȡת���ٶ�
		virtual Flt			getShiftSpeed() = 0;

		/// ����ת��Ŀ��
		virtual void		setDestDirection( Vec3 dir ) = 0;

		/// ��ȡĿ�귽��
		virtual Vec3		getDestDirection() = 0;

		/// �Ƿ�������Ч
		virtual void		setImmediately(bool immediately) = 0;

	};

    /******************************************************************************/
    // ISceneNodePathFindingMoveInAdvanceAction
    // Ѱ··������
    /******************************************************************************/

    class ISceneNodePathFindingMoveInAdvanceAction
    {
    public:
        /// ����Ŀ���,
        virtual Bool                setMoveToDestination( Vec3& dest, Bool isAdjuest ) = 0;

        // ���㾲̬Ѱ·����
        virtual PathFindingResult   calculateStaticPathFinding() = 0;

        // ���㶯̬Ѱ·����
        virtual PathFindingResult   calculateDynamicPathFindingBetweenStaticNode() = 0; 

        // �õ����ڵĶ�̬Ŀ���
        virtual Vec3                getCurrDynamicDestination() = 0;

		// �õ����ڵľ�̬Ŀ���
		virtual Vec3		        getCurrStaticDestination() = 0;

        // ȥ��һ����̬Ŀ���
        virtual Vec3                goNextDynamicDestination() = 0;
		// �Ƿ��Ѿ���������̬Ŀ���
		virtual Bool		        isLastDynamicDestination() = 0;

		// ȥ��һ����̬Ŀ���
		virtual Vec3		        goNextStaticDestination() = 0;
		// �Ƿ��Ѿ���������̬Ŀ���
		virtual Bool		        isLastStaticDestination() = 0;


		// �������ڵľ�̬Ŀ���
		virtual void		        setCurrStaticDestination( Vec3 pos ) = 0;

		// �������յľ�̬Ŀ���
		virtual void		        setFinalStaticDestination( Vec3 pos ) = 0;
    };

	/******************************************************************************/
	// ISceneNodeParabolaMoveToAction
	/******************************************************************************/
	class ISceneNodeParabolaMoveToAction : public LinedStateObject
	{
	public:

		ISceneNodeParabolaMoveToAction(Str name)
			:LinedStateObject( name )
		{
		}
		/// �����ƶ��ٶ�
		virtual void                setMoveSpeed( Flt speed ) = 0;
		/// �ƶ���ָ��λ��
		virtual void                setMoveToDestination( const Vec3& dest ) = 0;
	};
    
    


}

/******************************************************************************/
#endif
