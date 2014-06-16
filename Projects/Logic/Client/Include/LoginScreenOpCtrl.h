/******************************************************************************/
#ifndef _LOGINSCREENOPCTRL_H_
#define _LOGINSCREENOPCTRL_H_
/******************************************************************************/

#include "ClientPreqs.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //��Ϸ�������ϵͳ
    /******************************************************************************/
    class LoginScreenOpCtrl : public IOpCtrl, public LinedStateObjectListener
    {
    public:
        SINGLETON_INSTANCE(LoginScreenOpCtrl)
        LoginScreenOpCtrl();
        virtual ~LoginScreenOpCtrl();

        // ����
        void			    update(Flt delta);
        // ���
        void			    clear();
        // ��ԭ
        virtual void        revert();

		//////////////////////////////////////////////////////////////////////////////

		// �������л���

        // ����ʼ���س���
        virtual void        onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );
        // ���������س���
        virtual void        onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType ) ;
        /// ��ж�س���
        virtual void        onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );
		
		//////////////////////////////////////////////////////////////////////////////
		
		// ������״̬����״̬֪ͨ��

		// ��ͷ��������֪ͨ
		virtual void		onLinedStateLeave(LinedStateObject* obj);

		//////////////////////////////////////////////////////////////////////////////

		// ������ģʽ�л���

	public:

		enum
		{
							CTRL_STATE_SEL_NONE = 0,
							CTRL_STATE_SEL_CLAN,
							CTRL_STATE_SEL_CHAR,
							CTRL_STATE_CREATE_CHAR,
		};

		Int					getCtrlState() { return mCtrlState; }
		void				setCtrlState(Int state) { mCtrlState = state; }

	protected:

		Int					mCtrlState;

	//////////////////////////////////////////////////////////////////////////////

	//	��ѡ�����塿

    public:

		void				updateSelClanOperation(Flt delta);

		void				turnCamera(Bool isReverse = false,Flt turnSpeed = 0.5f);
		void				turnCamera(Str entityName,Flt turnSpeed = 0.5f);
		void				turnCameraImmediately(Str entityName);

	protected:

		//	��ǰѡ�е��������
		int					mCurrFocusIndex;
		//  ��һ��ѡ�е��������
		int					mNextFocusIndex;
		//	Ŀ������
		int					mTargetFocusIndex;

	//////////////////////////////////////////////////////////////////////////////
		
	//	��ѡ���ɫ��

	public:

		void				updateSelCharOperation(Flt delta);

	//////////////////////////////////////////////////////////////////////////////

	//	��������ɫ��

	public:

		void				updateCreateCharOperation(Flt delta);

	//////////////////////////////////////////////////////////////////////////////

	//  ��������Ϣ������ء�

	protected:

		void				onLeftMouseClick(CCharacterSceneEntity* entity);
		void				onLeftMousePress(CCharacterSceneEntity* entity);
		void				onLeftMouseHold(CCharacterSceneEntity* entity);
		void				onLeftMouseReleased(CCharacterSceneEntity* entity);
		void				onMouseOver( CCharacterSceneEntity*	entity );
		void				onMouseLeave( CCharacterSceneEntity* entity );

	protected:

		CCharacterSceneEntity*			mLeftMousePressEntity;

		CCharacterSceneEntity*			mMouseHoldEntity;

	//////////////////////////////////////////////////////////////////////////////
        
    };
}

#endif