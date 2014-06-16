/******************************************************************************/
#ifndef _GAMEOBJECTOPCTRL_H_
#define _GAMEOBJECTOPCTRL_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "ISceneObject.h"
#include "OperationObjectGroup.h"
#include "CAIManager.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //游戏对象操作系统
    /******************************************************************************/
	class GameObjectOpCtrl : public IOpCtrl
	{
        friend class OperationObjectGroup;
	public:
        SINGLETON_INSTANCE(GameObjectOpCtrl)
		GameObjectOpCtrl();
		virtual ~GameObjectOpCtrl();

        // 更新
		void			    update(Flt delta);
		// 清空
		void			    clear();
        // 还原
        virtual void        revert();

        //////////////////////////////////////////////////////////////////////////////

        // 当开始加载场景
        virtual void        onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );
        // 当结束加载场景
        virtual void        onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType ) ;
        /// 当卸载场景
        virtual void        onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );


        //////////////////////////////////////////////////////////////////////////////

        // 得到AI组管理
        LinedStateManager&      getAIGroupManager(){ return mAIGroupManager; }

        OperationObjectGroup*   getCurrOperationObjectGroup();

        // 设置状态
        void                    setState(GAMEOBJECT_OP_STATE state);

    public:

        //////////////////////////////////////////////////////////////////////////////

        // 增加选择
        void			    addSelected( CSceneEntity* entity );
        // 清空选择             
        void                clearSelected();

        //////////////////////////////////////////////////////////////////////////////

        // 请求使用技能
        // 一般界面调用
        void			    requestUseSkill( IdType skillId, GAMEOBJ_TYPE userType, IdType userId, UInt userIndex = 0 );

		void				createPointSkillDecal( UInt pointSkillDecalID, UInt size );
		void				destroyPointSkillDecal();

		Int					getIntersectionResult();


        //////////////////////////////////////////////////////////////////////////////

	protected:
		
        // 更新地表圈
        void			    updateDecal();

        // 清空点击地表模型
        void			    updateClickTerrainSign();

        // 更新框选线框
        void			    updateRectSelectWireframe();

    //////////////////////////////////////////////////////////////////////////////

	protected:

        // 检测键盘输入操作
        Bool			    checkKeyInput();

        // 检测快捷键
        void                checkShortcutKey();

    protected:

        // 检测鼠标输入操作
        Bool			    checkMouseInput();

        // 鼠标悬停事件
        void                onMouseOver( CSceneEntity* entity );
        void                onMouseOver( Vec3 pos );
    
        // 鼠标左键点击
        void                onLeftMousePressed( CSceneEntity* entityt );
        void                onLeftMouseReleased( CSceneEntity* entity );
        void                onLeftMouseClick( CSceneEntity* entity );
        void                onLeftMousePressed( Vec3 pos );
        void                onLeftMouseReleased( Vec3 pos );
        void                onLeftMouseClick( Vec3 pressedPos, Vec3 releasePos );
        void                onLeftMouseHoled( Vec3 pressedPos, Vec3 holedPos );
        void                onLeftMouseHoled( Vec2 pressedScreenPos, Vec2 holedScreenPos );

        // 鼠标右键点击
        void                onRightMousePressed( CSceneEntity* entity );
        void                onRightMouseReleased( CSceneEntity* entity );
        void                onRightMouseClick( CSceneEntity* entity );
        void                onRightMousePressed( Vec3 pos );
        void                onRightMouseReleased( Vec3 pos );
        void                onRightMouseClick( Vec3 pressedPos, Vec3 releasePos );
        void                onRightMouseHoled( Vec3 pressedPos, Vec3 holedPos );
        void                onRightMouseHoled( Vec2 pressedScreenPos, Vec2 holedScreenPos );

    //////////////////////////////////////////////////////////////////////////////

    protected:
        
        // 设置高亮
        void                setHightLight( CSceneEntity* entity );
        // 框选
        void                rectSelect( Vec2 pressedPos, Vec2 releasedPos );
		// 框选
		Bool                isInRect( RectF& rect, CSceneEntity* entity );

        // 显示点击地面特效
        void                showClickTerrainEffect( Vec3 pos );

        // 保存编队
        void                addGroup( UInt groupIndex );
        // 选择编队
        void                selectGroup( UInt groupIndex );

   //////////////////////////////////////////////////////////////////////////////
	
	protected:
			
        // AI组管理
        LinedStateManager               mAIGroupManager;

		// 当前控制对象组指针
		OperationObjectGroup*           mCurrOperationObjectGroup;
		// 默认的控制组
		OperationObjectGroup            mDefaultOperationObjectGroup;
		// 自定义的控制组队列
		std::map<UInt, OperationObjectGroup>	
                                        mOperationObjectGroupList;	

		// 框选列表
		std::vector<CSceneEntity*>		mGameObjectList;

        // 查询结果
        std::vector<ISceneObject*>      mQueryRes;

        CSceneEntity*                   mLeftMousePressedObj;
        CSceneEntity*                   mRightMousePressedObj;

        Vec3                            mLeftMousePressedPos;
        Vec3                            mRightMousePressedPos;
		Vec2                            mLeftMousePressedScreenPos;
		Vec2                            mRightMousePressedScreenPos;

        UInt                            mMaxNumInGroup;

        // 我方选中圈
        IDecalSet*						mMySelectDecalGroup;
        UInt                            mMySelectDecalNum;

        // 敌方选中圈
        IDecalSet*						mEnemySelectDecalGroup;
        UInt                            mEnemySelectDecalNum;

        // 友方选中圈
        IDecalSet*						mFriendSelectDecalGroup;
        UInt                            mFriendSelectDecalNum;

        // 点选地面模型
        IEntity*                        mClickTerrainSign;
        // 是否框选中
        Bool                            mIsFocusEnable;
        Bool                            mIsFocusRect;
        Vec2                            mRectPressedMousePos;
        Vec2                            mRectHoledMousePos;

		std::map<UInt, IDecalSet*>		mPointSkillDecalList;
		IDecalSet*						mCurrPointSkillDecal;
		//UInt							mPointSkillDecalID;

		Int								mIntersectionResult;

        GAMEOBJECT_OP_STATE             mState;
	};
}

#endif