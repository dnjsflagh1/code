/******************************************************************************/
#ifndef _CTROOPOBJECT_H_
#define _CTROOPOBJECT_H_
/******************************************************************************/
#include "ClientPreqs.h"
#include "LinedState.h"
//#include "CCharacterSceneEntity.h"
#include "CDTimer.h"
#include "CAttributeSystem.h"
#include "GameObject.h"
/******************************************************************************/


namespace MG
{
	/******************************************************************************/
	//动态属性
	/******************************************************************************/
	struct CSceneObjectDynamicData
	{
		Flt     moveSpeed;
		Flt     yawSpeed;

		IdType  belongPlayerID;     // 所属玩家
		FORCE   force;              // 势力

		CSceneObjectDynamicData()
			: moveSpeed(1)
			,yawSpeed(1)
			,belongPlayerID(0)
			,force(FORCE_INIT)
		{
		}

		CSceneObjectDynamicData& operator=(const CSceneObjectDynamicData& A)
		{
			if (this == &A)
			{
				return *this;
			}

			moveSpeed		=    A.moveSpeed;
			yawSpeed		=    A.yawSpeed;
			belongPlayerID	=    A.belongPlayerID;
			force			=    A.force;

			return *this;
		};
	};
	/******************************************************************************/
	//动态属性
	/******************************************************************************/
	struct CCharacterSceneEntityDynamicData : public CSceneObjectDynamicData
	{
		Bool    isDied;

		Int     hp;
		Int     mp;
		Int     sp;
		Int     hpmax;
		Int     mpmax;
		Int     spmax;

		CCharacterSceneEntityDynamicData()
			:isDied(false)
			,hp(0)
			,mp(0)
			,sp(0)
			,hpmax(0)
			,mpmax(0)
			,spmax(0)
		{
		}

		CCharacterSceneEntityDynamicData& operator=(const CCharacterSceneEntityDynamicData& A)
		{
			if (this == &A)
			{
				return *this;
			}

			CSceneObjectDynamicData::operator =(A);

			isDied	=    A.isDied;
			hp		=    A.hp;
			mp		=    A.mp;
			sp		=    A.sp;
			hpmax	=	 A.hpmax;
			mpmax	=	 A.mpmax;
			spmax	=	 A.spmax;


			return *this;
		};
	};

	/******************************************************************************/
	/// CTroopObject
	/******************************************************************************/
	class CTroopSoldier;
	class CTroopObject : public GameObject
	{
	public:
        CTroopObject();
		virtual ~CTroopObject();
		
        
        //×××××××××××××××××××××××××××××××××××××××××××××××××
        //  [主要方法]
        //×××××××××××××××××××××××××××××××××××××××××××××××××
        virtual void						initialize();
        // 更新
        void								update(Flt delta);

        // 得到状态管理
        //LinedStateManager&              getAIStateManager(){return mLinedStateManagerForAI;};

		CCharacterSceneEntityDynamicData*   getDynamicData();

        // 得到基础数据
        TroopData*							getBaseData();

        //×××××××××××××××××××××××××××××××××××××××××××××××××
        //  [士兵相关方法]
        //×××××××××××××××××××××××××××××××××××××××××××××××××
    public:

        // 创建士兵
        CTroopSoldier*						createSoldierEntitys( UInt index , TroopSoldierData* data, CCharacterSceneEntityDynamicData* dynamicData );

        // 得到士兵
        CTroopSoldier*						getSoldierEntitys( UInt soldierId );

		CTroopSoldier*						getSoldierEntitysByIndex( UInt index );

        // 销毁士兵
        void								destroySoldierEntitys( UInt soldierId );

        // 销毁士兵
        void								destroySoldierEntitys();

        // 更新士兵
        void								updateSoldierEntitys(Flt delta);

		UInt								getSoldierEntitysNum();

		Vec3								getTroopCenterPos();
		//根据属性id获得属性值
		Flt									getFanalValue(U32 attrId){return mCAttributeSystem.getFanalValue(attrId);}

		std::map<UInt, CTroopSoldier*>*		getTroopSoldiers(){return &mTroopSoldierEntityList;}
		typedef std::map<UInt, CTroopSoldier*>::iterator TroopSoldierIt;
	private:
        std::map<UInt, CTroopSoldier*>		mTroopSoldierEntityList;

        //CD
        CDTimer								mCDTimer;

        //属性
        CAttributeSystem					mCAttributeSystem;

		//
		CCharacterSceneEntityDynamicData*	mCharacterDynaicData;
	};
}

#endif
