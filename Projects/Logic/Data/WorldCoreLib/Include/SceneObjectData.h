//*****************************************************************************************************
#ifndef _H_SCENEOBJECTDATA_
#define _H_SCENEOBJECTDATA_
//*****************************************************************************************************
#include "GameObjectData.h"
//*****************************************************************************************************
namespace MG
{

	/******************************************************************************/
	//Npc基础属性
	/******************************************************************************/
	struct SceneObjectData : public GameObjectData
	{  
		Bool	isDestroy			;			//是否被销毁
		Bool	isAI				;			//是否AI控制
		FORCE   force				;           // 势力

		Flt     moveSpeed			;			//移动速度
		Flt     yawSpeed			;			//转身速度

		IdType  belongPlayerID		;			// 所属玩家
		
		//------------------------------------------------------------------------------------------------
		SceneObjectData()
			:isDestroy(false)		
			,isAI(false)			
			,force(FORCE_INIT)			
			,moveSpeed(1)		
			,yawSpeed(1)		
			,belongPlayerID(0)
		{

		}
		//------------------------------------------------------------------------------------------------
		SceneObjectData& operator=(const SceneObjectData& A)
		{
			if (this == &A)
			{
				return *this;
			}

			GameObjectData::operator =(A);

			isDestroy			=		A.isDestroy			;	
			isAI				=		A.isAI				;
			force				=		A.force				;
			moveSpeed			=		A.moveSpeed			;
			yawSpeed			=		A.yawSpeed			;
			belongPlayerID		=		A.belongPlayerID	;


			return *this;
		}
	};
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************