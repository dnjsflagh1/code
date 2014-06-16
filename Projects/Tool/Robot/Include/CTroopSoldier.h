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
    //小组士兵实体
    /******************************************************************************/
	class CTroopObject;

	class CTroopSoldier : public GameObject
    {
    public:

        CTroopSoldier(CTroopObject* owner);
        virtual ~CTroopSoldier();

    public:

        //×××××××××××××××××××××××××××××××××××××××××××××××××
        //  [主要方法]
        //×××××××××××××××××××××××××××××××××××××××××××××××××

        // 初始化
        virtual void				        initialize();
        // 反初始化
        virtual void				        unInitialize();

        //×××××××××××××××××××××××××××××××××××××××××××××××××
        //  [基础属性]
        //×××××××××××××××××××××××××××××××××××××××××××××××××

        // 得到基础属性
        TroopSoldierData*		            getBaseData();  

		CCharacterSceneEntityDynamicData*	getDynamicData(){return mCharacterDynamicData;}
        // 得到小组对象
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
