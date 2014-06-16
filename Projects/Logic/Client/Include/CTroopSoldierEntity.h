/******************************************************************************/
#ifndef _CTROOPSOLDIERENTITY_H_
#define _CTROOPSOLDIERENTITY_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "CCharacterSceneEntity.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //С��ʿ��ʵ��
    /******************************************************************************/
    class CTroopSoldierEntity : public CCharacterSceneEntity
    {
    public:

        CTroopSoldierEntity(CTroopEntity* owner, IEntity* entity);
        virtual ~CTroopSoldierEntity();

    public:

        //��������������������������������������������������������������������������������������������������
        //  [��Ҫ����]
        //��������������������������������������������������������������������������������������������������

        // ��ʼ��
        virtual void				        initialize();
        // ����ʼ��
        virtual void				        unInitialize();

        //��������������������������������������������������������������������������������������������������
        //  [��������]
        //��������������������������������������������������������������������������������������������������

        // �õ���������
        TroopSoldierEntityData*		        getDynamicData();   

        // �õ�С�����
        CTroopEntity*                       getTroopEntity(){return mTroopEntity;};

		//��������������������������������������������������������������������������������������������������
		//  [��̬����]
		//��������������������������������������������������������������������������������������������������

		Bool								isBattleState();

		void								setTarget( GAMEOBJ_TYPE gameType, GameObjectIdType id, UInt index = 0 );

		void								getTarget( GAMEOBJ_TYPE& gameType, GameObjectIdType& id, UInt& index );

    protected:

		GAMEOBJ_TYPE						mTargetType;

		GameObjectIdType					mTargetId;

		UInt								mTargetIndex;
      
    private:

        CTroopEntity*						mTroopEntity;

    };
}

#endif
