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
    //小组士兵实体
    /******************************************************************************/
    class CTroopSoldierEntity : public CCharacterSceneEntity
    {
    public:

        CTroopSoldierEntity(CTroopEntity* owner, IEntity* entity);
        virtual ~CTroopSoldierEntity();

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
        TroopSoldierEntityData*		        getDynamicData();   

        // 得到小组对象
        CTroopEntity*                       getTroopEntity(){return mTroopEntity;};

		//×××××××××××××××××××××××××××××××××××××××××××××××××
		//  [动态属性]
		//×××××××××××××××××××××××××××××××××××××××××××××××××

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
