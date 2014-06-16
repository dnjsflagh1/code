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
    //��Ϸ��������״̬
    /******************************************************************************/
    enum	GAMEOBJECT_OP_STATE
    {
        GOS_NONE    = 0,    // ������
        GOS_NORMAL  ,       // ��ͨ״̬
        GOS_SKILL_PREPARE,  // ����׼��״̬
		GOS_SKILL_USE,
    };


    /******************************************************************************/
    //��Ϸ��������
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
	//��Ϸ���������ϵͳ
	/******************************************************************************/
	class OperationObjectGroup
	{

        friend class GameObjectOpCtrl;

	public:

		OperationObjectGroup();
		virtual ~OperationObjectGroup();


        //////////////////////////////////////////////////////////////////////////////

        // ����
        void                update(Flt delta);
        void                revert();
        void                clear();


        //////////////////////////////////////////////////////////////////////////////

        void                setState(GAMEOBJECT_OP_STATE state);
		GAMEOBJECT_OP_STATE getState();

        //////////////////////////////////////////////////////////////////////////////

        // ����ʹ�ü���
        // һ��������
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

        // ����ʧЧ����Ϸ�����б�
        void            filterOperationObjectList();

        // ����ѡ�п����Ч
        void            updateSelectDecalEffect();

    protected:

        // �����ͣ�¼�
        void            onMouseOver( CSceneEntity* entity );
        void            onMouseOver( Vec3 pos );

        // ���������
        void            onLeftMousePressed( CSceneEntity* entity );
        void            onLeftMouseReleased( CSceneEntity* entity );
        void            onLeftMouseClick( CSceneEntity* entity );
        void            onLeftMousePressed( Vec3 pos );
        void            onLeftMouseReleased( Vec3 pos );
        void            onLeftMouseClick( Vec3 pressedPos, Vec3 releasedPos );

        // ����Ҽ����
        void            onRightMousePressed( CSceneEntity* entity );
        void            onRightMouseReleased( CSceneEntity* entity );
        void            onRightMouseClick( CSceneEntity* entity );
        void            onRightMousePressed( Vec3 pos );
        void            onRightMouseReleased( Vec3 pos );
        void            onRightMouseClick( Vec3 pressedPos, Vec3 releasedPos );

		void			clearState();

        //////////////////////////////////////////////////////////////////////////////

        // ����
        void            interact( CSceneEntity* entity );
        // ����
        void            attack( CSceneEntity* entity );
        // ����
        void            attack( Vec3 pos );
        // �ƶ�
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