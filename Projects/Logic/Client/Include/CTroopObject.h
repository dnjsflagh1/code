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
    class CTroopObject : public CSceneEntity
	{
		friend class GameObjectOpCtrl;
	public:
        CTroopObject( IEntityGroup* entityGroup );
		virtual ~CTroopObject();
		
        
        //×××××××××××××××××××××××××××××××××××××××××××××××××
        //  [主要方法]
        //×××××××××××××××××××××××××××××××××××××××××××××××××
        virtual void                        	initialize();
        virtual void                        	unInitialize();

        // 更新
        void						        	update(Flt delta);

		CCharacterSceneEntityDynamicData*   	getDynamicData();

        // 得到基础数据
        TroopData*                          	getBaseData();

		// 得到世界坐标
		virtual Bool							getWorldPos( Vec3& worldPos );
		// 是否在屏幕中
		virtual Bool							isInScreen();

        //×××××××××××××××××××××××××××××××××××××××××××××××××
        //  [士兵相关方法]
        //×××××××××××××××××××××××××××××××××××××××××××××××××
    public:

		void									createFlag(UInt flgModleId);

		void									destroyFlag();

        // 创建士兵
        CTroopSoldierEntity*                	createSoldierEntitys( UInt index , TroopSoldierData* data, CCharacterSceneEntityDynamicData* dynamicData );

        // 得到士兵
        CTroopSoldierEntity*                	getSoldierEntitys( ISceneObject* sceneObj );

        // 得到士兵
        CTroopSoldierEntity*                	getSoldierEntitys( UInt soldierId );

		CTroopSoldierEntity*                	getSoldierEntitysByIndex( UInt index );

        // 销毁士兵
        void                                	destroySoldierEntitys( UInt soldierId );

        // 销毁士兵
        void                                	destroySoldierEntitys();

        // 更新士兵
        void                                	updateSoldierEntitys(Flt delta);

		UInt							    	getSoldierEntitysNum();

		Vec3							    	getTroopCenterPos();
		//根据属性id获得属性值
		Flt								    	getFanalValue(U32 attrId){return mCAttributeSystem.getFanalValue(attrId);}

		FightManager*							getFightManager();

		CTroopSoldierEntity*					getSoldierEntitysForMinDis( Vec3 pos );

		const FightAIGroup*						getFightAIGroup();

		///////////////////////////////////////////////////////////////////////////////////////////

		void									addFightAITriggerCount( UInt fightAIId );

		UInt									getFightAITriggerCount( UInt fightAIId );

		void									clearFightAITriggerCount();

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

	};
}

#endif
