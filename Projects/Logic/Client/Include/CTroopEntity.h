/******************************************************************************/
#ifndef _CTROOPOBJECT_H_
#define _CTROOPOBJECT_H_
/******************************************************************************/
#include "ClientPreqs.h"
#include "LinedState.h"
#include "CCharacterSceneEntity.h"
#include "CDTimer.h"
#include "CAttributeSystem.h"
/******************************************************************************/


namespace MG
{

	/******************************************************************************/
	/// CTroopObject
	/******************************************************************************/
    class CTroopEntity : public CCharacterSceneEntity
	{
		friend class GameObjectOpCtrl;

	public:

		struct MoveToPosRow
		{
			std::vector<Vec3>					moveToPos;
		};


        CTroopEntity( IEntityGroup* entityGroup );
		virtual ~CTroopEntity();
		
        
        //×××××××××××××××××××××××××××××××××××××××××××××××××
        //  [主要方法]
        //×××××××××××××××××××××××××××××××××××××××××××××××××
        virtual void                        	initialize();
        virtual void                        	unInitialize();

        // 更新
        void						        	update(Flt delta);

        // 得到基础数据
        TroopEntityData*						getDynamicData();

		// 得到世界坐标
		virtual Bool							getWorldPos( Vec3& worldPos );
		// 是否在屏幕中
		virtual Bool							isInScreen();

		IEntityGroup*							getEntityGroup();

        //×××××××××××××××××××××××××××××××××××××××××××××××××
        //  [士兵相关方法]
        //×××××××××××××××××××××××××××××××××××××××××××××××××
    public:

		void									createFlag(UInt flgModleId);

		void									destroyFlag();

        // 创建士兵
        CTroopSoldierEntity*                	createSoldierEntitys( UInt index , TroopSoldierEntityData* data );

        // 得到士兵
        CTroopSoldierEntity*                	getSoldierEntitys( ISceneObject* sceneObj );

        // 得到士兵
        CTroopSoldierEntity*                	getSoldierEntitys( UInt soldierId );

		CTroopSoldierEntity*                	getSoldierEntitysByIndex( UInt index );

		std::map<UInt, CTroopSoldierEntity*>*	getSoldierEntitysList();

        // 销毁士兵
        void                                	destroySoldierEntitys( UInt soldierId );

        // 销毁士兵
        void                                	destroySoldierEntitys();

        // 更新士兵
        void                                	updateSoldierEntitys(Flt delta);

		UInt							    	getSoldierEntitysNum();

		Vec3							    	getTroopCenterPos();
		//根据属性id获得属性值
		CAttributeSystem*						getCAttributeSystem(){return &mCAttributeSystem;}

		FightManager*							getFightManager();

		CTroopSoldierEntity*					getSoldierEntitysForMinDis( Vec3 pos );

		const FightAIGroup*						getFightAIGroup();

		///////////////////////////////////////////////////////////////////////////////////////////

		void									addFightAITriggerCount( UInt fightAIId );

		UInt									getFightAITriggerCount( UInt fightAIId );

		void									clearFightAITriggerCount();

		///////////////////////////////////////////////////////////////////////////////////////////

		virtual void							doMoveToAction( Vec3 destination, Flt startTime, Bool isBlockCheck = true, ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType = ISceneNodeGridLineMoveToAction::PFT_DYNAMIC );

		virtual void							doMoveToAction( Vec3 startPos, Vec3 destination, Flt startTime, Bool isBlockCheck = true, ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType = ISceneNodeGridLineMoveToAction::PFT_DYNAMIC );

		virtual void							stopMoveToAction();

		void									stopAttack();

		//void									clacTroopSoldierPos( Vec3 pos, Vec3 dir, std::map<UInt, MoveToPosRow>& soldierPosList );

		//void									clacTroopSoldierPos( Vec3 pos, std::vector<Vec3>& soldierPosList );

		//void									clacTroopSoldierMoveToPos( Vec3 pos, Vec3 dir, std::map<UInt, Vec3>& soldierPosList );

		void									clearAIState();

		void									clearActionState();

		///////////////////////////////////////////////////////////////////////////////////////////

		void									playAnimation(Str animName,  Bool randomTimePlaye = true, Bool isLoop=false, Bool isLastFrameStop = false, Bool isReset = true );

		void									stopAnimation(Str animName); 

		///////////////////////////////////////////////////////////////////////////////////////////

		void									useSkill( IdType skillId, Byte targetType, IdType targetId, Vec3 taegetPos );

		///////////////////////////////////////////////////////////////////////////////////////////

		void									setBattleState(Bool isBattle);

		void									setMoveSpeed(Flt moveSpeed);

		///////////////////////////////////////////////////////////////////////////////////////////

		CAISoldierInTroopMove*					getCAISoldierInTroopMove();

	protected:

		void									checkTroopMove();

	protected:

        IEntityGroup*							mEntityGroup;

        std::map<UInt, CTroopSoldierEntity*>	mTroopSoldierEntityList;

        //CD
        CDTimer									mCDTimer;

        //属性
        CAttributeSystem						mCAttributeSystem;

		IEntity*								mFlagEntity;

		FightManager*							mFightManager;

		const FightAIGroup*						mFightAIGroup;

		std::map<UInt, UInt>					mFightAITriggerCountList;

		CAISoldierInTroopMove*					mAISoldierInTroopMove;
		CAISoldierInTroopAttack*				mAISoldierInTroopAttack;

		Bool									mIsWaitMove;

	};
}

#endif
