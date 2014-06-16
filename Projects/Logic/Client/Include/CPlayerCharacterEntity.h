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
	//角色实体对象
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

        //×××××××××××××××××××××××××××××××××××××××××××××××××
        //  [主要方法]
        //×××××××××××××××××××××××××××××××××××××××××××××××××

        // 初始化
        virtual void				        initialize();
        // 反初始化
        virtual void				        unInitialize();
        //更新
        void				                update( Flt delta );

        //×××××××××××××××××××××××××××××××××××××××××××××××××
        //  [基础属性]
        //×××××××××××××××××××××××××××××××××××××××××××××××××

        // 得到基础属性
        PlayerCharacterEntityData*		    getDynamicData();      

		void								createFlag(UInt flgModleId);

		void								destroyFlag();

		//×××××××××××××××××××××××××××××××××××××××××××××××××
		//  [动态属性]
		//×××××××××××××××××××××××××××××××××××××××××××××××××

		Bool								isBattleState();

		//×××××××××××××××××××××××××××××××××××××××××××××××××
		//  [事件]
		//×××××××××××××××××××××××××××××××××××××××××××××××××

		void								onRelive();


	protected:

		// 初始化实体
		void                                initializeEntity();

	private:


		//×××××××××××××××××××××××××××××××××××××××××××××××××
		//  [附件管理]
		//×××××××××××××××××××××××××××××××××××××××××××××××××
	public:

		// 绑定道具, 根据itemID查询的绑定信息来决定绑定位置
		bool								attachItem(U32 itemID);
		
		// 绑定道具, 根据绑定位置强行绑定上去，不用寻找绑定信息
		bool								attachItem(U32 itemID, ITEM_EQUIP_SLOT_TYPE equip_slot);

		// 卸载指定部位的道具
		bool								detachItem(ITEM_EQUIP_SLOT_TYPE equip_slot, bool forceDetach = false);

		// 应用当前动作组
		void								applyActionGroup();

		// 判断是否骑马
		bool								isRiding();								
		
		// 加入附件
		bool								attachEntityAccessory(Str name, U32 modelID, I32 bindPoint);

		// 附件剔除
		void								detachEntityAccessory(Str name);

	protected:

		void								initBindWordMap();

		// 设置一个动作组
		void								setActionGroup( U32 actionGroup, Bool isRide );

		// 获得动作组
		void								getActionGroup( Str& weaponAction, Str& rideAction );

	protected:

		// 附件<绑定点--绑定物件指针>
		std::map<U32, Str>					mEntityAccessories;

		// 附件<绑定点--绑定物件道具ID>
		std::map<U32, U32>					mItemSkins;		

		// 绑定表
		std::map<U32, Str>					mBindPointMap;

		// 动作组参数1
		Str									mWeaponActionGroup;

		// 动作组参数2
		Str									mRideActionGroup;


		IEntity*							mFlagEntity;
	};
}

#endif