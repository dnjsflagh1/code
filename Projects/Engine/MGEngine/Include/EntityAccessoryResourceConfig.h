/******************************************************************************/
#ifndef _ENTITY_ACCESSORY_RESOURCE_CONFIG_H_
#define _ENTITY_ACCESSORY_RESOURCE_CONFIG_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IResourceManager.h"

/******************************************************************************/

namespace MG
{
	enum
	{
		ENTITY_ACCESSORY_ID = 0,
		ENTITY_ACCESSORY_PARENT_ID,
		ENTITY_ACCESSORY_RESOURCE_TYPE,
		ENTITY_ACCESSORY_RESOURCE_ID,

		ENTITY_ACCESSORY_BIND_BONE,

		ENTITY_ACCESSORY_DERIVED_POS_X,
		ENTITY_ACCESSORY_DERIVED_POS_Y,
		ENTITY_ACCESSORY_DERIVED_POS_Z,

		ENTITY_ACCESSORY_DERIVED_QUA_X,
		ENTITY_ACCESSORY_DERIVED_QUA_Y,
		ENTITY_ACCESSORY_DERIVED_QUA_Z,

		//是否和父实体同步动画文件
		ENTITY_ACCESSORY_SYNC_ANIM,
		
		//是否把生命周期让父实体管理
		ENTITY_ACCESSORY_DEP_LIFE,
	};

	/******************************************************************************/
	//This is a interface class for reading CSV table of entity accessory resource .
	/******************************************************************************/
	class EntityAccessoryResourceConfig
	{
	public:
		EntityAccessoryResourceConfig(){};
		~EntityAccessoryResourceConfig(){};
		SINGLETON_INSTANCE(EntityAccessoryResourceConfig);

	public:

		//Load file for initializing model declaration maps of resource manager;
		Bool							load(CChar* filename);
		//UnLoad model declaration maps;
		void							unLoad();
	};
}

#endif