//*****************************************************************************************************
#ifndef _H_SCENEOBJECTDATA_
#define _H_SCENEOBJECTDATA_
//*****************************************************************************************************
#include "GameObjectData.h"
//*****************************************************************************************************
namespace MG
{

	/******************************************************************************/
	//Npc��������
	/******************************************************************************/
	struct SceneObjectData : public GameObjectData
	{  
		Bool	isDestroy			;			//�Ƿ�����
		Bool	isAI				;			//�Ƿ�AI����
		FORCE   force				;           // ����

		Flt     moveSpeed			;			//�ƶ��ٶ�
		Flt     yawSpeed			;			//ת���ٶ�

		IdType  belongPlayerID		;			// �������
		
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