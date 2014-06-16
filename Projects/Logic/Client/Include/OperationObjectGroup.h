/******************************************************************************/
#ifndef _OPERATIONOBJECTGROUP_H_
#define _OPERATIONOBJECTGROUP_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "ISceneObject.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //游戏操作对象状态
    /******************************************************************************/
    enum	GAMEOBJECT_OP_STATE
    {
        GOS_NONE    = 0,    // 无意义
        GOS_NORMAL  ,       // 普通状态
        GOS_SKILL_PREPARE,  // 技能准备状态
		GOS_SKILL_USE,
    };


    /******************************************************************************/
    //游戏操作对象
    /******************************************************************************/
    enum OperationObjectType
    {
        OOT_NULL,
        OOT_MY,
        OOT_FRIEND,
        OOT_ENEMY,
    };

    //struct  OperationObject
    //{
    //    OperationObjectType type;
    //    CSceneEntity*       entity;
    //};

	struct OperationEntity
	{
		CSceneEntity*  sceneEntity;
		UInt		   row;  
	};

	struct  OperationObject
	{
		OperationObjectType type;
		 std::map<IdType, OperationEntity> entityList;
	};

    struct OperationObjectList
    {
        GAMEOBJ_TYPE                        type;
        std::map<IdType, OperationObject>   objectList;
    };


	/******************************************************************************/
	//游戏对象组操作系统
	/******************************************************************************/
	class OperationObjectGroup
	{

        friend class GameObjectOpCtrl;

	public:

		OperationObjectGroup();
		virtual ~OperationObjectGroup();


        //////////////////////////////////////////////////////////////////////////////

        // 更新
        void                update(Flt delta);
        void                revert();
        void                clear();


        //////////////////////////////////////////////////////////////////////////////

        void                setState(GAMEOBJECT_OP_STATE state);
		GAMEOBJECT_OP_STATE getState();

        //////////////////////////////////////////////////////////////////////////////

        // 请求使用技能
        // 一般界面调用
        void			requestUseSkill( IdType skillId, GAMEOBJ_TYPE userType, IdType userId, UInt userIndex = 0 );

		//////////////////////////////////////////////////////////////////////////////
		
		void			pickItem( CItemEntity* itemEntity );

 
        //////////////////////////////////////////////////////////////////////////////

        void            selectGameObject( CSceneEntity* entity , Bool isOne = false );
		void            addGameObject( CSceneEntity* entity, Bool isOne = false );
		Bool            removeGameObject( GAMEOBJ_TYPE objType, IdType id );
		Bool            removeGameObject( CSceneEntity* entity );
        Bool            hasGameObject( CSceneEntity* entity );
		
        //////////////////////////////////////////////////////////////////////////////

    protected:

        // 过滤失效的游戏对象列表
        void            filterOperationObjectList();

        // 更新选中框的特效
        void            updateSelectDecalEffect();

    protected:

        // 鼠标悬停事件
        void            onMouseOver( CSceneEntity* entity );
        void            onMouseOver( Vec3 pos );

        // 鼠标左键点击
        void            onLeftMousePressed( CSceneEntity* entity );
        void            onLeftMouseReleased( CSceneEntity* entity );
        void            onLeftMouseClick( CSceneEntity* entity );
        void            onLeftMousePressed( Vec3 pos );
        void            onLeftMouseReleased( Vec3 pos );
        void            onLeftMouseClick( Vec3 pressedPos, Vec3 releasedPos );

        // 鼠标右键点击
        void            onRightMousePressed( CSceneEntity* entity );
        void            onRightMouseReleased( CSceneEntity* entity );
        void            onRightMouseClick( CSceneEntity* entity );
        void            onRightMousePressed( Vec3 pos );
        void            onRightMouseReleased( Vec3 pos );
        void            onRightMouseClick( Vec3 pressedPos, Vec3 releasedPos );

		void			clearState();

        //////////////////////////////////////////////////////////////////////////////

        // 交互
        void            interact( CSceneEntity* entity );
        // 攻击
        void            attack( CSceneEntity* entity );
        // 攻击
        void            attack( Vec3 pos );
        // 移动
        void            moveTo( Vec3 pos );

        //////////////////////////////////////////////////////////////////////////////

		OperationObjectList*		getFirstGameObj();

		CSceneEntity*				getFirstSceneEntity();

        //////////////////////////////////////////////////////////////////////////////

	private:

        //GameObjectOpCtrl*                           mOwner;

		std::map<GAMEOBJ_TYPE,OperationObjectList>  mGameObjectList;

        GAMEOBJECT_OP_STATE                         mState;

        IdType                         	            mPreparedSkillId;
	};
}

#endif