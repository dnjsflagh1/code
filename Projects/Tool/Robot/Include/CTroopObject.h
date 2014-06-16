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
	//��̬����
	/******************************************************************************/
	struct CSceneObjectDynamicData
	{
		Flt     moveSpeed;
		Flt     yawSpeed;

		IdType  belongPlayerID;     // �������
		FORCE   force;              // ����

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
	//��̬����
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
		
        
        //��������������������������������������������������������������������������������������������������
        //  [��Ҫ����]
        //��������������������������������������������������������������������������������������������������
        virtual void						initialize();
        // ����
        void								update(Flt delta);

        // �õ�״̬����
        //LinedStateManager&              getAIStateManager(){return mLinedStateManagerForAI;};

		CCharacterSceneEntityDynamicData*   getDynamicData();

        // �õ���������
        TroopData*							getBaseData();

        //��������������������������������������������������������������������������������������������������
        //  [ʿ����ط���]
        //��������������������������������������������������������������������������������������������������
    public:

        // ����ʿ��
        CTroopSoldier*						createSoldierEntitys( UInt index , TroopSoldierData* data, CCharacterSceneEntityDynamicData* dynamicData );

        // �õ�ʿ��
        CTroopSoldier*						getSoldierEntitys( UInt soldierId );

		CTroopSoldier*						getSoldierEntitysByIndex( UInt index );

        // ����ʿ��
        void								destroySoldierEntitys( UInt soldierId );

        // ����ʿ��
        void								destroySoldierEntitys();

        // ����ʿ��
        void								updateSoldierEntitys(Flt delta);

		UInt								getSoldierEntitysNum();

		Vec3								getTroopCenterPos();
		//��������id�������ֵ
		Flt									getFanalValue(U32 attrId){return mCAttributeSystem.getFanalValue(attrId);}

		std::map<UInt, CTroopSoldier*>*		getTroopSoldiers(){return &mTroopSoldierEntityList;}
		typedef std::map<UInt, CTroopSoldier*>::iterator TroopSoldierIt;
	private:
        std::map<UInt, CTroopSoldier*>		mTroopSoldierEntityList;

        //CD
        CDTimer								mCDTimer;

        //����
        CAttributeSystem					mCAttributeSystem;

		//
		CCharacterSceneEntityDynamicData*	mCharacterDynaicData;
	};
}

#endif
