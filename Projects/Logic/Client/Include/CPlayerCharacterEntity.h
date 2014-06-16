/******************************************************************************/
#ifndef _CPALYERAHRACTERENTITY_H_
#define _CPALYERAHRACTERENTITY_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CCharacterSceneEntity.h"
#include "LinedState.h"
#include "IEntityAccessory.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//��ɫʵ�����
	/******************************************************************************/
	enum player_character_attach_point
	{
		ATTACH_POINT_RIGHT_HAND = 1,
		ATTACH_POINT_LEFT_HAND,
		ATTACH_POINT_RIDE,
	};
	/******************************************************************************/
    class CPlayerCharacterEntity : public CCharacterSceneEntity
	{
	public:

		CPlayerCharacterEntity( IEntity* entity );
		virtual ~CPlayerCharacterEntity();

    public:

        //��������������������������������������������������������������������������������������������������
        //  [��Ҫ����]
        //��������������������������������������������������������������������������������������������������

        // ��ʼ��
        virtual void				        initialize();
        // ����ʼ��
        virtual void				        unInitialize();
        //����
        void				                update( Flt delta );

        //��������������������������������������������������������������������������������������������������
        //  [��������]
        //��������������������������������������������������������������������������������������������������

        // �õ���������
        PlayerCharacterEntityData*		    getDynamicData();      

		void								createFlag(UInt flgModleId);

		void								destroyFlag();

		//��������������������������������������������������������������������������������������������������
		//  [��̬����]
		//��������������������������������������������������������������������������������������������������

		Bool								isBattleState();

		//��������������������������������������������������������������������������������������������������
		//  [�¼�]
		//��������������������������������������������������������������������������������������������������

		void								onRelive();


	protected:

		// ��ʼ��ʵ��
		void                                initializeEntity();

	private:


		//��������������������������������������������������������������������������������������������������
		//  [��������]
		//��������������������������������������������������������������������������������������������������
	public:

		// �󶨵���, ����itemID��ѯ�İ���Ϣ��������λ��
		bool								attachItem(U32 itemID);
		
		// �󶨵���, ���ݰ�λ��ǿ�а���ȥ������Ѱ�Ұ���Ϣ
		bool								attachItem(U32 itemID, ITEM_EQUIP_SLOT_TYPE equip_slot);

		// ж��ָ����λ�ĵ���
		bool								detachItem(ITEM_EQUIP_SLOT_TYPE equip_slot, bool forceDetach = false);

		// Ӧ�õ�ǰ������
		void								applyActionGroup();

		// �ж��Ƿ�����
		bool								isRiding();								
		
		// ���븽��
		bool								attachEntityAccessory(Str name, U32 modelID, I32 bindPoint);

		// �����޳�
		void								detachEntityAccessory(Str name);

	protected:

		void								initBindWordMap();

		// ����һ��������
		void								setActionGroup( U32 actionGroup, Bool isRide );

		// ��ö�����
		void								getActionGroup( Str& weaponAction, Str& rideAction );

	protected:

		// ����<�󶨵�--�����ָ��>
		std::map<U32, Str>					mEntityAccessories;

		// ����<�󶨵�--���������ID>
		std::map<U32, U32>					mItemSkins;		

		// �󶨱�
		std::map<U32, Str>					mBindPointMap;

		// ���������1
		Str									mWeaponActionGroup;

		// ���������2
		Str									mRideActionGroup;


		IEntity*							mFlagEntity;
	};
}

#endif