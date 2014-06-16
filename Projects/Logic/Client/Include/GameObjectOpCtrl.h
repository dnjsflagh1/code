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
    //��Ϸ�������ϵͳ
    /******************************************************************************/
	class GameObjectOpCtrl : public IOpCtrl
	{
        friend class OperationObjectGroup;
	public:
        SINGLETON_INSTANCE(GameObjectOpCtrl)
		GameObjectOpCtrl();
		virtual ~GameObjectOpCtrl();

        // ����
		void			    update(Flt delta);
		// ���
		void			    clear();
        // ��ԭ
        virtual void        revert();

        //////////////////////////////////////////////////////////////////////////////

        // ����ʼ���س���
        virtual void        onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );
        // ���������س���
        virtual void        onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType ) ;
        /// ��ж�س���
        virtual void        onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );


        //////////////////////////////////////////////////////////////////////////////

        // �õ�AI�����
        LinedStateManager&      getAIGroupManager(){ return mAIGroupManager; }

        OperationObjectGroup*   getCurrOperationObjectGroup();

        // ����״̬
        void                    setState(GAMEOBJECT_OP_STATE state);

    public:

        //////////////////////////////////////////////////////////////////////////////

        // ����ѡ��
        void			    addSelected( CSceneEntity* entity );
        // ���ѡ��             
        void                clearSelected();

        //////////////////////////////////////////////////////////////////////////////

        // ����ʹ�ü���
        // һ��������
        void			    requestUseSkill( IdType skillId, GAMEOBJ_TYPE userType, IdType userId, UInt userIndex = 0 );

		void				createPointSkillDecal( UInt pointSkillDecalID, UInt size );
		void				destroyPointSkillDecal();

		Int					getIntersectionResult();


        //////////////////////////////////////////////////////////////////////////////

	protected:
		
        // ���µر�Ȧ
        void			    updateDecal();

        // ��յ���ر�ģ��
        void			    updateClickTerrainSign();

        // ���¿�ѡ�߿�
        void			    updateRectSelectWireframe();

    //////////////////////////////////////////////////////////////////////////////

	protected:

        // �������������
        Bool			    checkKeyInput();

        // ����ݼ�
        void                checkShortcutKey();

    protected:

        // �������������
        Bool			    checkMouseInput();

        // �����ͣ�¼�
        void                onMouseOver( CSceneEntity* entity );
        void                onMouseOver( Vec3 pos );
    
        // ���������
        void                onLeftMousePressed( CSceneEntity* entityt );
        void                onLeftMouseReleased( CSceneEntity* entity );
        void                onLeftMouseClick( CSceneEntity* entity );
        void                onLeftMousePressed( Vec3 pos );
        void                onLeftMouseReleased( Vec3 pos );
        void                onLeftMouseClick( Vec3 pressedPos, Vec3 releasePos );
        void                onLeftMouseHoled( Vec3 pressedPos, Vec3 holedPos );
        void                onLeftMouseHoled( Vec2 pressedScreenPos, Vec2 holedScreenPos );

        // ����Ҽ����
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
        
        // ���ø���
        void                setHightLight( CSceneEntity* entity );
        // ��ѡ
        void                rectSelect( Vec2 pressedPos, Vec2 releasedPos );
		// ��ѡ
		Bool                isInRect( RectF& rect, CSceneEntity* entity );

        // ��ʾ���������Ч
        void                showClickTerrainEffect( Vec3 pos );

        // ������
        void                addGroup( UInt groupIndex );
        // ѡ����
        void                selectGroup( UInt groupIndex );

   //////////////////////////////////////////////////////////////////////////////
	
	protected:
			
        // AI�����
        LinedStateManager               mAIGroupManager;

		// ��ǰ���ƶ�����ָ��
		OperationObjectGroup*           mCurrOperationObjectGroup;
		// Ĭ�ϵĿ�����
		OperationObjectGroup            mDefaultOperationObjectGroup;
		// �Զ���Ŀ��������
		std::map<UInt, OperationObjectGroup>	
                                        mOperationObjectGroupList;	

		// ��ѡ�б�
		std::vector<CSceneEntity*>		mGameObjectList;

        // ��ѯ���
        std::vector<ISceneObject*>      mQueryRes;

        CSceneEntity*                   mLeftMousePressedObj;
        CSceneEntity*                   mRightMousePressedObj;

        Vec3                            mLeftMousePressedPos;
        Vec3                            mRightMousePressedPos;
		Vec2                            mLeftMousePressedScreenPos;
		Vec2                            mRightMousePressedScreenPos;

        UInt                            mMaxNumInGroup;

        // �ҷ�ѡ��Ȧ
        IDecalSet*						mMySelectDecalGroup;
        UInt                            mMySelectDecalNum;

        // �з�ѡ��Ȧ
        IDecalSet*						mEnemySelectDecalGroup;
        UInt                            mEnemySelectDecalNum;

        // �ѷ�ѡ��Ȧ
        IDecalSet*						mFriendSelectDecalGroup;
        UInt                            mFriendSelectDecalNum;

        // ��ѡ����ģ��
        IEntity*                        mClickTerrainSign;
        // �Ƿ��ѡ��
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