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
		
        
        //��������������������������������������������������������������������������������������������������
        //  [��Ҫ����]
        //��������������������������������������������������������������������������������������������������
        virtual void                        	initialize();
        virtual void                        	unInitialize();

        // ����
        void						        	update(Flt delta);

		CCharacterSceneEntityDynamicData*   	getDynamicData();

        // �õ���������
        TroopData*                          	getBaseData();

		// �õ���������
		virtual Bool							getWorldPos( Vec3& worldPos );
		// �Ƿ�����Ļ��
		virtual Bool							isInScreen();

        //��������������������������������������������������������������������������������������������������
        //  [ʿ����ط���]
        //��������������������������������������������������������������������������������������������������
    public:

		void									createFlag(UInt flgModleId);

		void									destroyFlag();

        // ����ʿ��
        CTroopSoldierEntity*                	createSoldierEntitys( UInt index , TroopSoldierData* data, CCharacterSceneEntityDynamicData* dynamicData );

        // �õ�ʿ��
        CTroopSoldierEntity*                	getSoldierEntitys( ISceneObject* sceneObj );

        // �õ�ʿ��
        CTroopSoldierEntity*                	getSoldierEntitys( UInt soldierId );

		CTroopSoldierEntity*                	getSoldierEntitysByIndex( UInt index );

        // ����ʿ��
        void                                	destroySoldierEntitys( UInt soldierId );

        // ����ʿ��
        void                                	destroySoldierEntitys();

        // ����ʿ��
        void                                	updateSoldierEntitys(Flt delta);

		UInt							    	getSoldierEntitysNum();

		Vec3							    	getTroopCenterPos();
		//��������id�������ֵ
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

        //����
        CAttributeSystem						mCAttributeSystem;

		IEntity*								mFlagEntity;

		FightManager*							mFightManager;

		const FightAIGroup*						mFightAIGroup;

		std::map<UInt, UInt>					mFightAITriggerCountList;

	};
}

#endif
