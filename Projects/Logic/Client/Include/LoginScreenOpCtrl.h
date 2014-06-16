/******************************************************************************/
#ifndef _LOGINSCREENOPCTRL_H_
#define _LOGINSCREENOPCTRL_H_
/******************************************************************************/

#include "ClientPreqs.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //游戏对象操作系统
    /******************************************************************************/
    class LoginScreenOpCtrl : public IOpCtrl, public LinedStateObjectListener
    {
    public:
        SINGLETON_INSTANCE(LoginScreenOpCtrl)
        LoginScreenOpCtrl();
        virtual ~LoginScreenOpCtrl();

        // 更新
        void			    update(Flt delta);
        // 清空
        void			    clear();
        // 还原
        virtual void        revert();

		//////////////////////////////////////////////////////////////////////////////

		// 【场景切换】

        // 当开始加载场景
        virtual void        onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );
        // 当结束加载场景
        virtual void        onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType ) ;
        /// 当卸载场景
        virtual void        onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );
		
		//////////////////////////////////////////////////////////////////////////////
		
		// 【动作状态调用状态通知】

		// 镜头动作结束通知
		virtual void		onLinedStateLeave(LinedStateObject* obj);

		//////////////////////////////////////////////////////////////////////////////

		// 【操作模式切换】

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

	//	【选择氏族】

    public:

		void				updateSelClanOperation(Flt delta);

		void				turnCamera(Bool isReverse = false,Flt turnSpeed = 0.5f);
		void				turnCamera(Str entityName,Flt turnSpeed = 0.5f);
		void				turnCameraImmediately(Str entityName);

	protected:

		//	当前选中的物件索引
		int					mCurrFocusIndex;
		//  下一个选中的物件索引
		int					mNextFocusIndex;
		//	目标索引
		int					mTargetFocusIndex;

	//////////////////////////////////////////////////////////////////////////////
		
	//	【选择角色】

	public:

		void				updateSelCharOperation(Flt delta);

	//////////////////////////////////////////////////////////////////////////////

	//	【创建角色】

	public:

		void				updateCreateCharOperation(Flt delta);

	//////////////////////////////////////////////////////////////////////////////

	//  【各种消息函数相关】

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