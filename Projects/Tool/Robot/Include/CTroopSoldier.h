/******************************************************************************/
#ifndef _CTROOPSOLDIERENTITY_H_
#define _CTROOPSOLDIERENTITY_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
//#include "CCharacterSceneEntity.h"
#include "CTroopObject.h"
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //С��ʿ��ʵ��
    /******************************************************************************/
	class CTroopObject;

	class CTroopSoldier : public GameObject
    {
    public:

        CTroopSoldier(CTroopObject* owner);
        virtual ~CTroopSoldier();

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
        TroopSoldierData*		            getBaseData();  

		CCharacterSceneEntityDynamicData*	getDynamicData(){return mCharacterDynamicData;}
        // �õ�С�����
        CTroopObject*                       getTroopEntity(){return mTroopEntity;}

		void								setPos(Vec3 pos){ mPos = pos;}
		Vec3&								getPos(){return mPos;}
    protected:

      

    private:
		CCharacterSceneEntityDynamicData*	mCharacterDynamicData;

        CTroopObject*						mTroopEntity;
		
		Vec3								mPos;
    };
}

#endif
