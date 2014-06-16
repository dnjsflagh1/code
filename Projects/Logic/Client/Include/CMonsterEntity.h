/******************************************************************************/
#ifndef _CMONSTERENTITY_H_
#define _CMONSTERENTITY_H_
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
	class CMonsterEntity : public CCharacterSceneEntity
	{
	public:

		CMonsterEntity( IEntity* entity );
		virtual ~CMonsterEntity();

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
		MonsterEntityData*					getDynamicData();      

		//×××××××××××××××××××××××××××××××××××××××××××××××××
		//  [动态属性]
		//×××××××××××××××××××××××××××××××××××××××××××××××××

		Bool								isBattleState();


	protected:

		// 初始化实体
		void                                initializeEntity();

		void								checkAndPlayIdleAnim( Flt delta );

	private:

		Flt									mPauseThinkTime;

	};
}

#endif